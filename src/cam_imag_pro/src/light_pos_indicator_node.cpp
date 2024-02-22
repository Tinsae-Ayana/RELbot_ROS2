#include "light_pos_indicator_node.hpp"

LightPoseNode::LightPoseNode() : Node("light_pose_indicator_node") {
  publisher =
      this->create_publisher<std_msgs::msg::Int32MultiArray>("light_pose", 10);
  publish_with_mark =
      this->create_publisher<sensor_msgs::msg::Image>("image_with_marker", 10);
  subscription = this->create_subscription<sensor_msgs::msg::Image>(
      "image", 10, std::bind(&LightPoseNode::callback, this, _1));
  this->declare_parameter("threshold", 155);
}

void LightPoseNode::callback(const sensor_msgs::msg::Image &cam_frame) {
  cv_bridge::CvImagePtr cv_image =
      cv_bridge::toCvCopy(cam_frame, sensor_msgs::image_encodings::BGR8);
  cv::Mat frame = cv_image->image;
  cv::Mat grayScale;
  cv::cvtColor(frame, grayScale, cv::COLOR_BGR2GRAY);
  cv::Mat blackn_white;
  cv::threshold(grayScale, blackn_white,
                this->get_parameter("threshold").as_int(), 255,
                cv::THRESH_BINARY);

  std::vector<cv::Point> white_pixels_indices;
  cv::findNonZero(blackn_white, white_pixels_indices);
  cv::Scalar center = cv::mean(white_pixels_indices);
  if (white_pixels_indices.size()) {
    // the center of gravity of white pixels
    int centerx = static_cast<int>(center[0]);
    int centery = static_cast<int>(center[1]);
    center_of_gravity.data = {centerx, centery};

    // create a small box
    int width = 20;
    int topLeftX = centerx - width / 2;
    int topLeftY = centery - width / 2;
    int bottomRightX = centerx + width / 2;
    int bottomRightY = centery + width / 2;

    // insert a box around the center
    cv::rectangle(frame, cv::Point(topLeftX, topLeftY),
                  cv::Point(bottomRightX, bottomRightY), cv::Scalar(0, 0, 255),
                  5);
    auto cvImage = std::make_shared<cv_bridge::CvImage>();
    cvImage->encoding = "mono8";
    cvImage->header.frame_id = cam_frame.header.frame_id;
    cvImage->image = frame;
    auto im = cvImage->toImageMsg();

    // publish the coordinate and the image with rectangle
    publisher->publish(center_of_gravity);
    publish_with_mark->publish(*im);
  }
}

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<LightPoseNode>());
  rclcpp::shutdown();
  return 0;
}
