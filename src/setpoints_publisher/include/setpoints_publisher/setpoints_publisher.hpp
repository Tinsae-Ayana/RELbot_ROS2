#pragma once

#include "geometry_msgs/msg/point_stamped.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"
#include <chrono>
#include <functional>
#include <memory>
#include <random>

using namespace std::chrono_literals;
using namespace std::placeholders;

class SetpointsPublisher : public rclcpp::Node {
private:
  // create angular velcoity publishers to the relbot
  rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr left_motor_vel_pub;
  rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr right_motor_vel_pub;

  // create light pose reciever from light pose indicator node
  rclcpp::Subscription<geometry_msgs::msg::PointStamped>::SharedPtr
      light_pose_topic;

  // create current camera position from /output/moving_camera topic of relbot
  rclcpp::Subscription<geometry_msgs::msg::PointStamped>::SharedPtr
      curr_pose_receiver;

  // create callback for coming light position
  void light_pose_callback(
      const geometry_msgs::msg::PointStamped &center_of_gravity);

  // create callback for coming current camera position
  void curr_pose_callback(
      const geometry_msgs::msg::PointStamped &current_camera_pose);

  // brightlight position
  geometry_msgs::msg::PointStamped light_pose;

public:
  std::string LEFT_MOTOR_TOPIC = "/input/left_motor/setpoint_vel";
  std::string RIGHT_MOTOR_TOPIC = "/input/right_motor/setpoint_vel";

  SetpointsPublisher();
};
