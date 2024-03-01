#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"
#include <chrono>
#include <cmath>

using namespace std::chrono_literals;
using std::placeholders::_1;

class SequenceController : public rclcpp::Node
{
public:
    SequenceController();

private:
    void timer_callback();

    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr left_motor_publisher_;
    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr right_motor_publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    int counter_;
};