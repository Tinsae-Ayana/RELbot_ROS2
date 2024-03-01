from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='sequence_controller',  
            executable='sequence_controller', 
            name='sequence_controller',
        ),
        Node(
            package='image_tools_sdfr',
            executable='cam2image',
            name='cam2image',
            parameters=['cam2image.yaml'],
            arguments=['--ros-args', '-p', 'depth:=1', '-p', 'history:=keep_last']
        ),
        Node(
            package='RELbot_simulator',
            executable='RELbot_simulator',
            name='RELbot_simulator',
        ),
        Node (
            package="image_tools",
            executable="showimage",
            name='showimage',
        #     remappings=[
        #         ("/image", "/image_with_marker")     
        # ]
        )
    ])
