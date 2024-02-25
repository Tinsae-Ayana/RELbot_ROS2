#include "brightness_node.hpp"
#include <gtest/gtest.h>

class BrightnessNodeTest : public ::testing::Test {

protected:
  void SetUp() override {
    std::shared_ptr<rclcpp::Node> test_node =
        std::make_shared<rclcpp::Node>("test_image_pulishing_node");
    std::shared_ptr<rclcpp::Node> brightness_node =
        std::make_shared<BrightnessNode>("brightness_node");
  }
  void TearDown() override { rclcpp::shutdown(); }

  std::shared_ptr<rclcpp::Node> test_node;
  std::shared_ptr<rclcpp::Node> brightness_node;
  const std::string DEFAULT_MSG_TOPIC = "brightness";
  const std::string DEFAULT_IMAGE_TOPIC = "image";
  const std::string MSG_VALUE_DARK = "It is dark";
  const std::string MSG_VALUE_LIGHT = "It is light";
};

TEST_F(BrightnessNodeTest, dark_test) {
  auto darkimage_publisher =
      test_node->create_publisher<sensor_msgs::msg::Image>(DEFAULT_IMAGE_TOPIC,
                                                           10);

  // create a subscriber node that accepts message sent by BrightnessNode
  auto callback = [this](const std_msgs::msg::String &msg) {
    ASSERT_EQ(MSG_VALUE_DARK, msg.data);
  };
  auto darkimage_subcriber =
      test_node->create_subscription<std_msgs::msg::String>(DEFAULT_MSG_TOPIC,
                                                            10, callback);

  // prepare a dark image to be published by test node
  auto dark_image = sensor_msgs::msg::Image();
  dark_image.header.stamp = test_node->now();
  dark_image.height = 480;
  dark_image.width = 480;
  dark_image.encoding = "rgb8";
  dark_image.data.assign(dark_image.height * dark_image.width * 3, 0);
}

TEST_F(BrightnessNodeTest, light_test) {}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}