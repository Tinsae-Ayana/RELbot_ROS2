#include "setpoints_publisher.hpp"

SetpointsPublisher::SetpointsPublisher() : Node("setpoints_publisher") {

  // random number generator
  std::random_device seed;
  generator = std::mt19937(seed());
  dist = std::uniform_real_distribution<>(-0.2, 0.2);

  // create publishers
  left_motor_vel_pub =
      this->create_publisher<std_msgs::msg::Float64>(LEFT_MOTOR_TOPIC, 10);
  right_motor_vel_pub =
      this->create_publisher<std_msgs::msg::Float64>(RIGHT_MOTOR_TOPIC, 10);
  light_pose = this->create_subscription<std_msgs::msg::Int32MultiArray>(
      "light_pose", 10, std::bind(&SetpointsPublisher::call_back, this, _1));

  // create timer
  timer = this->create_wall_timer(
      100ms, std::bind(&SetpointsPublisher::timer_callback, this));
}

void SetpointsPublisher::call_back(
    const std_msgs::msg::Int32MultiArray &center_of_gravity) {
  // TODO: instead of genrating random vel valus to motors we subscribe to
  // light_pose_node and calculate the pose value from that and publish to
  // motor nodes
  RCLCPP_INFO(this->get_logger(), "this is being sent by light pose %d",
              center_of_gravity.data[0]);
}

void SetpointsPublisher::timer_callback() {

  // TODO: to be removed once the call_back function is completely implemented

  // generate random values
  float left_motor_vel = dist(generator);
  float right_motor_vel = dist(generator);

  // create std_msgs types to be published
  auto left_msg = std_msgs::msg::Float64();
  left_msg.data = left_motor_vel;
  auto right_msg = std_msgs::msg::Float64();
  right_msg.data = right_motor_vel;

  // publish the data
  left_motor_vel_pub->publish(left_msg);
  right_motor_vel_pub->publish(right_msg);
}

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SetpointsPublisher>());
  rclcpp::shutdown();
  return 0;
}
