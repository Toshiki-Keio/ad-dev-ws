from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='infrared_sensor',
            executable='infrared_publisher'
        )
    ])
