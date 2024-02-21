#include <chrono>
#include <functional>
#include <memory>
#include <random>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"
#include "std_msgs/msg/int32_multi_array.hpp"

using namespace std::chrono_literals;
using namespace std::placeholders;

class SetpointsPublisher : public rclcpp::Node {
public:
  std::string LEFT_MOTOR_TOPIC = "/input/left_motor/setpoint_vel";
  std::string RIGHT_MOTOR_TOPIC = "/input/right_motor/setpoint_vel";

  SetpointsPublisher() : Node("setpoints_publisher") {

    //
    std::random_device seed;
    generator = std::mt19937(seed());
    dist = std::uniform_real_distribution<>(-100, 100);

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

private:
  rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr left_motor_vel_pub;
  rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr right_motor_vel_pub;
  rclcpp::Subscription<std_msgs::msg::Int32MultiArray>::SharedPtr light_pose;
  rclcpp::TimerBase::SharedPtr timer;

  std::mt19937 generator;
  std::uniform_real_distribution<> dist;

  // functions

  void call_back(const std_msgs::msg::Int32MultiArray &center_of_gravity) {
    // TODO: instead of genrating random vel valus to motors we subscribe to
    // light_pose_node and calculate the pose value from that and publish to
    // motor nodes
    RCLCPP_INFO(this->get_logger(), "this is being sent by light pose %d",
                center_of_gravity.data[0]);
  }

  void timer_callback() {

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
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SetpointsPublisher>());
  rclcpp::shutdown();
  return 0;
}
