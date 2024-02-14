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

  // function that is called everytime cam2image node publish image
  void callback(const sensor_msgs::msg::Image &cam_frame) {
    cv_bridge::CvImagePtr cv_image =
        cv_bridge::toCvCopy(cam_frame, sensor_msgs::image_encodings::BGR8);
    cv::Mat frame = cv_image->image;
    cv::Mat grayScale;
    cv::cvtColor(frame, grayScale, cv::COLOR_BGR2GRAY);
    cv::Scalar meanValue = cv::mean(grayScale);
    double avg_brightness = meanValue[0];
    auto msg = std_msgs::msg::String();
    if (avg_brightness > this->get_parameter(parameter_name).as_int()) {
      msg.data = "It is light";
      publisher->publish(msg);
    } else {
      msg.data = "It is dark";
      publisher->publish(msg);
    }
  }

public:
  const std::string parameter_name = "brightness_param";
  // constructor
  BrightnessNode() : Node("brightness_node") {
    this->declare_parameter(parameter_name, 100);
    publisher = this->create_publisher<std_msgs::msg::String>("brightness", 10);
    subscriber = this->create_subscription<sensor_msgs::msg::Image>(
        "image", 10, std::bind(&BrightnessNode::callback, this, _1));
  }
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<BrightnessNode>());
  rclcpp::shutdown();
  return 0;
}
