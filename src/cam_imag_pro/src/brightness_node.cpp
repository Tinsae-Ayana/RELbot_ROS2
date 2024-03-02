#include "brightness_node.hpp"

BrightnessNode::BrightnessNode() : Node("brightness_node") {
  this->declare_parameter(PARAMETER_NAME, 100);
  publisher = this->create_publisher<std_msgs::msg::String>("brightness", 10);
  subscriber = this->create_subscription<sensor_msgs::msg::Image>(
      "image", 10, std::bind(&BrightnessNode::callback, this, _1));
}

void BrightnessNode::callback(const sensor_msgs::msg::Image &cam_frame) {
  // convert the ros image to opencv image
  cv_bridge::CvImagePtr cv_image =
      cv_bridge::toCvCopy(cam_frame, sensor_msgs::image_encodings::BGR8);
  cv::Mat frame = cv_image->image;

  // convert the image to grayscale image
  cv::Mat grayScale;
  cv::cvtColor(frame, grayScale, cv::COLOR_BGR2GRAY);
  cv::Scalar meanValue = cv::mean(grayScale);

  // calculate the mean value of the grayscale
  double avg_brightness = meanValue[0];
  auto msg = std_msgs::msg::String();

  // check if it bright or dark and publish it
  if (avg_brightness > this->get_parameter(PARAMETER_NAME).as_int()) {
    msg.data = "It is light";
    publisher->publish(msg);
  } else {
    msg.data = "It is dark";
    publisher->publish(msg);
  }
}

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<BrightnessNode>());
  rclcpp::shutdown();
  return 0;
}
