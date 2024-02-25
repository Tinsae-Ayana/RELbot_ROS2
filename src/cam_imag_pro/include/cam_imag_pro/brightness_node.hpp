#include <chrono>
#include <functional>
#include <memory>

#include "cv_bridge/cv_bridge.h"
#include "opencv2/opencv.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

class BrightnessNode : public rclcpp::Node {
private:
  // attribute
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscriber;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher;

  // functions
  void callback(const sensor_msgs::msg::Image &cam_frame);

public:
  // parameter name for the brightness threshold
  const std::string PARAMETER_NAME = "threshold";
  BrightnessNode();
};
