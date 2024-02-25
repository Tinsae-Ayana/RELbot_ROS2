from launch import LaunchDescription
from launch_ros.actions import Node

def  generate_launch_description() :
    return LaunchDescription(
        [
            Node(
                package = "RELbot_simulator",
                executable = "RELbot_simulator",
            ),
             Node(
                package = "image_tools",
                executable = "cam2image",     
            ),
             Node(
                package = "setpoints_publisher",
                executable = "setpoints_publisher",  
            ), 
            Node(
                package = "cam_imag_pro",
                executable= "light_pos_indicator_node"
            )
        ]
    )