from setuptools import setup
import os
from glob import glob

package_name = 'infrared_sensor'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name), glob('launch/*_launch.py')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='toshikifukui',
    maintainer_email='toshikifukui@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'infrared_publisher=infrared_sensor.infrared_publisher:main',
            'infrared_subscriber=infrared_sensor.infrared_subscriber:main'
        ],
    },
)
