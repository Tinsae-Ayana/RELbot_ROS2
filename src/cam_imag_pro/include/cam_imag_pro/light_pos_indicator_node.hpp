#pragma once
#include <chrono>
#include <memory>
#include <string>

#include "cv_bridge/cv_bridge.h"
#include "opencv2/opencv.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "std_msgs/msg/int32_multi_array.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

class LightPoseNode : public rclcpp::Node {
private:
  // attributes
  rclcpp::Publisher<std_msgs::msg::Int32MultiArray>::SharedPtr publisher;
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription;
  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr
      publish_with_mark; // to visually check
  std_msgs::msg::Int32MultiArray center_of_gravity;

  // functions
  void callback(const sensor_msgs::msg::Image &cam_frame);

public:
  LightPoseNode();
};