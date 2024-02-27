#pragma once
#include <chrono>
#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "std_msgs/msg/string.hpp"
#include "opencv2/opencv.hpp"
#include "cv_bridge/cv_bridge.h"

class BrightnessNode : public rclcpp::Node {
public:
    BrightnessNode();

private:
    void imageCallback(const sensor_msgs::msg::Image::SharedPtr msg);

    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_subscriber_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr light_publisher_;
};