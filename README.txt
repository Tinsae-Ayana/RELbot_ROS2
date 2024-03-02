# Assignment one for Advanced Software Development for Robotics

## Installation Guide

1. unzip the .zip file and go to assignment1_ws directory
2. open the folder in terminal
3. run rosdep install incase if all the necessary packages are not installed
4. run 'colcon build'

## Image processing with ROS2

## 1.1.1 Camera input with standard ROS2 tools 

* We used linux machine for this assignment. Therefore, we didn't use multipass and did not need to publish the webcam video stream to UDP
* Regular ROS2 installation comes with image_tools package. 
  1. first we run 'ros2 run image_tools cam2image' commmand
  2. then 'ros2 run image_tools cam2image --ros-args -p depth:-1 history:-keep_last'
* The answers to the questions are provided in the report


## 1.1.2 Adding a brightness node

* after colcon build source the overlay using source /install/setup.bash when you are still in assignment1_ws directory
* run   'ros2 launch cam_imag_pro brightness_node.launch.py', this should launch cam2image node, showimage node and brightness_node 
  which publishes if it is dark or light based on the light condition
* open new terminal and 'run ros2 topic echo /brightness' to see the message and 'rqt_graph' to see the node graph. Refresh the graph if all nodes is not shown

## 1.1.3 Adding ROS2 parameters

* run 'ros2 launch cam_imag_pro brightness_node.launch.py'
* run "ros2 param set /brightness_node threshold threshold_value". 'threshold_value' is number between 0 and 255
* alternatively, run 'ros2 run image_tools cam2image' and then 'ros2 run cam_imag_pro --ros-args -p threshold:=threshold_value'

## 1.1.4 Simple light position indicator

* run 'ros2 launch cam_imag_pro light_pose.launch.py'
* run 'rqt_graph' to see the node graph, you should see cam2image, light_pos_indicator_node and two imageshow node which display the "center of mass" of the bright light


## 1.2 Sequence controller

* run 'ros launch setpoints_publisher start_all_nodes.launch.py'

