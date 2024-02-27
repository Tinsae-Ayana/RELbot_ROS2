#include "brightness_node.hpp"

BrightnessNode::BrightnessNode() : Node("brightness_node") {
    // 声明亮度阈值参数
    this->declare_parameter<double>("threshold", 100.0);

    image_subscriber_ = this->create_subscription<sensor_msgs::msg::Image>(
        "image", 10, std::bind(&BrightnessNode::imageCallback, this, std::placeholders::_1));
    light_publisher_ = this->create_publisher<std_msgs::msg::String>("brightness", 10);
}


void BrightnessNode::imageCallback(const sensor_msgs::msg::Image::SharedPtr msg) {
    // 获取亮度阈值参数
    double brightness_threshold;
    this->get_parameter("threshold", brightness_threshold);

    cv_bridge::CvImagePtr cv_ptr;
    try {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    } catch (cv_bridge::Exception& e) {
        RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
        return;
    }

    cv::Mat frame = cv_ptr->image;
    cv::Mat grayScale;
    cv::cvtColor(frame, grayScale, cv::COLOR_BGR2GRAY);
    cv::Scalar meanValue = cv::mean(grayScale);
    double brightness = meanValue[0];
    auto light_msg = std_msgs::msg::String();
    RCLCPP_INFO(this->get_logger(), "Brightness: %f, Threshold: %f", brightness, brightness_threshold);
    if (brightness > brightness_threshold) {
        light_msg.data = "It is light";
        light_publisher_->publish(light_msg);
    } else {
        light_msg.data = "It is dark";
        light_publisher_->publish(light_msg);
    }
}

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<BrightnessNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
