from setuptools import setup, find_packages

setup(
    name='mqyt',
    version='1.0',
    install_requires=["paho-mqtt", "numpy", "opencv-contrib-python"],
    packages=find_packages()
)