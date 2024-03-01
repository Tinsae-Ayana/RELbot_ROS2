#include "sequence_controller.hpp"

SequenceController::SequenceController() : Node("sequence_controller"), counter_(0)
{
    left_motor_publisher_ = this->create_publisher<std_msgs::msg::Float64>("/input/left_motor/setpoint_vel", 10);
    right_motor_publisher_ = this->create_publisher<std_msgs::msg::Float64>("/input/right_motor/setpoint_vel", 10);

    timer_ = this->create_wall_timer(
        10ms, std::bind(&SequenceController::timer_callback, this));
}

void SequenceController::timer_callback()
{
    auto left_setpoint_msg = std_msgs::msg::Float64();
    auto right_setpoint_msg = std_msgs::msg::Float64();

/*
    if ((counter_ % 40 < 10) || (counter_ % 40 >= 30)) {
        left_setpoint_msg.data = 0.3;
        right_setpoint_msg.data = 0.7;
    } else {
        left_setpoint_msg.data = 0.7;
        right_setpoint_msg.data = 0.3;
    }
*/

    if (counter_ < 800) {
        left_setpoint_msg.data = 0.0;
        right_setpoint_msg.data = 0.0;
    } else {
        left_setpoint_msg.data = 1;
        right_setpoint_msg.data = 1;
}
    
    left_motor_publisher_->publish(left_setpoint_msg);
    right_motor_publisher_->publish(right_setpoint_msg);

    counter_++;
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SequenceController>());
    rclcpp::shutdown();
    return 0;
}
