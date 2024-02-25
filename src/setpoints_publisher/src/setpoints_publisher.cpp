#include "setpoints_publisher.hpp"

SetpointsPublisher::SetpointsPublisher() : Node("setpoints_publisher") {

  // create motor velocity publishers
  left_motor_vel_pub =
      this->create_publisher<std_msgs::msg::Float64>(LEFT_MOTOR_TOPIC, 10);
  right_motor_vel_pub =
      this->create_publisher<std_msgs::msg::Float64>(RIGHT_MOTOR_TOPIC, 10);
  light_pose_topic =
      this->create_subscription<geometry_msgs::msg::PointStamped>(
          "light_pose", 10,
          std::bind(&SetpointsPublisher::light_pose_callback, this, _1));

  // create current camera position reciever
  curr_pose_receiver =
      this->create_subscription<geometry_msgs::msg::PointStamped>(
          "output/camera_position", 1,
          std::bind(&SetpointsPublisher::curr_pose_callback, this, _1));
}

void SetpointsPublisher::light_pose_callback(
    const geometry_msgs::msg::PointStamped &center_of_gravity) {
  this->light_pose.point = center_of_gravity.point;
}

void SetpointsPublisher::curr_pose_callback(
    const geometry_msgs::msg::PointStamped &current_camera_pose) {

  // get the difference betweeen current position the camera and light position
  double x_difference =
      (double)(current_camera_pose.point.x - this->light_pose.point.x);

  // double y_difference =
  //     (double)(this->light_pose.point.y -
  //              current_camera_pose.point
  //                  .y); // it does not have any effect since we can't move
  //                  the
  //                       // robot in z axis of the world (y axis of the image)

  auto left_motor_vel = std_msgs::msg::Float64();
  left_motor_vel.data = -0.01 * x_difference;
  auto right_motor_vel = std_msgs::msg::Float64();
  right_motor_vel.data = 0.01 * x_difference;

  // publish the data
  left_motor_vel_pub->publish(left_motor_vel);
  right_motor_vel_pub->publish(right_motor_vel);
}

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SetpointsPublisher>());
  rclcpp::shutdown();
  return 0;
}
