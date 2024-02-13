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

  // function
  void callback(const sensor_msgs::msg::Image &cam_frame) {
    // TODO:: implementation
  }

public:
  // constructor
  LightPoseNode() : Node("light_pos_indicator_node") {
    publisher = this->create_publisher<std_msgs::msg::Int32MultiArray>(
        "light_pose", 10);
    subscription = this->create_subscription<sensor_msgs::msg::Image>(
        "image", 10, std::bind(&LightPoseNode::callback, this, _1));
  }
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<LightPoseNode>());
  rclcpp::shutdown();
  return 0;
}
