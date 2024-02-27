#include "light_pose_indicator_node.hpp"

LightPositionNode::LightPositionNode() : Node("light_pose_indicator_node") {
    this->declare_parameter<double>("threshold", 150.0);

    image_subscriber_ = this->create_subscription<sensor_msgs::msg::Image>(
        "image", 10, std::bind(&LightPositionNode::imageCallback, this, std::placeholders::_1));
    light_position_publisher_ = this->create_publisher<geometry_msgs::msg::Point>("light_pose", 10);
    marked_image_publisher_ = this->create_publisher<sensor_msgs::msg::Image>("image_with_marker", 10);
};

void LightPositionNode::imageCallback(const sensor_msgs::msg::Image::SharedPtr msg) {
    double brightness_threshold_;
    brightness_threshold_ = this->get_parameter("threshold").as_double();

    cv_bridge::CvImagePtr cv_ptr;
    try {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    } catch (cv_bridge::Exception& e) {
        RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
        return;
    }

    cv::Mat gray_image, binary_image;
    cv::cvtColor(cv_ptr->image, gray_image, cv::COLOR_BGR2GRAY);
    cv::threshold(gray_image, binary_image, brightness_threshold_, 255, cv::THRESH_BINARY);

    cv::Moments m = cv::moments(binary_image, true);
    if (m.m00 > 0) {
        int x = int(m.m10 / m.m00);
        int y = int(m.m01 / m.m00);

        // 发布COG
        geometry_msgs::msg::Point center_of_gravity;
        center_of_gravity.x = x;
        center_of_gravity.y = y;
        center_of_gravity.z = 0.0; // 因为我们处理的是二维图像，所以z值可以设置为0
        light_position_publisher_->publish(center_of_gravity);

        cv::Mat colored_image;
        cv::cvtColor(binary_image, colored_image, cv::COLOR_GRAY2BGR);
        cv::rectangle(colored_image, cv::Point(x-10, y-10), cv::Point(x+10, y+10), cv::Scalar(0, 255, 0), 3);

        cv_bridge::CvImage colored_image_bridge(msg->header, "bgr8", colored_image);
        sensor_msgs::msg::Image ros_image;
        colored_image_bridge.toImageMsg(ros_image);
        marked_image_publisher_->publish(ros_image);
    };
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<LightPositionNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}