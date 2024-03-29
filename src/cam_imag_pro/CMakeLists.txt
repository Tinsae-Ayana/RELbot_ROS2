cmake_minimum_required(VERSION 3.8)
project(cam_imag_pro)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)
find_package(geometry_msgs REQUIRED)

add_executable(brightness_node src/brightness_node.cpp)
add_executable(light_pos_indicator_node src/light_pos_indicator_node.cpp)

ament_target_dependencies(light_pos_indicator_node rclcpp std_msgs sensor_msgs cv_bridge OpenCV geometry_msgs)
ament_target_dependencies(brightness_node rclcpp std_msgs sensor_msgs cv_bridge OpenCV)

target_include_directories(brightness_node  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/cam_imag_pro>)


target_include_directories(light_pos_indicator_node  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/cam_imag_pro>)

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)

install(TARGETS 
   brightness_node
   light_pos_indicator_node
   DESTINATION lib/${PROJECT_NAME})


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()


ament_package()
