#pragma once
#include <chrono>
#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "geometry_msgs/msg/point.hpp"
#include "opencv2/opencv.hpp"
#include "cv_bridge/cv_bridge.h"

class LightPositionNode : public rclcpp::Node {
public:
    LightPositionNode();

private:
    void imageCallback(const sensor_msgs::msg::Image::SharedPtr msg);
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_subscriber_;
    rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr light_position_publisher_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr marked_image_publisher_;
};