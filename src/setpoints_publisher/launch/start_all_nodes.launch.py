from launch import LaunchDescription
from launch_ros.actions import Node

def  generate_launch_description() :
    return LaunchDescription(
        [     Node(
                package = "image_tools",
                executable = "cam2image",     
            ),
            Node(
                package = "RELbot_simulator",
                executable = "RELbot_simulator",
            ),
             Node(
                package = "setpoints_publisher",
                executable = "setpoints_publisher",  
            ), 
            Node(
                package = "cam_imag_pro",
                executable= "light_pos_indicator_node"
            ),
            Node (
                    package="image_tools",
                    executable="showimage",                # original camera output
            ),
            Node (
                package="image_tools",
                executable="showimage",
                remappings=[
                    ("/image", "/image_with_marker")      # image with center of gravity 
            ]
            ),
        ]
    )