#include <chrono>
#include <functional>
#include <memory>
#include <random>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"

using namespace std::chrono_literals;

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

    // create timer
    timer = this->create_wall_timer(
        100ms, std::bind(&SetpointsPublisher::timer_callback, this));
  }

private:
  rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr left_motor_vel_pub;
  rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr right_motor_vel_pub;
  rclcpp::TimerBase::SharedPtr timer;

  std::mt19937 generator;
  std::uniform_real_distribution<> dist;

  // functions
  void timer_callback() {

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
