# iLMBt - Intelligent Line Marking Bot
iLMBt (intelligent Line Marking Bot) is an autonomous wheeled mobile robot designed specifically for marking lines on sports fields without the need for human intervention. This GitHub repository contains all the necessary code, documentation, and design files to build and operate the iLMBt robot.

## Project Overview
The primary objective of iLMBt is to automate the line marking process in sports fields. By eliminating the need for human labor, iLMBt offers increased efficiency, precision, and reliability in line marking tasks. The robot utilizes a hopper mechanism controlled by a motorized lead screw to control the flow of marking powder. It also incorporates an effective dampening system for smooth and consistent line marking operations.

## Features
**Autonomous line marking**: iLMBt is capable of autonomously marking lines on sports fields based on given coordinates. It calculates the desired path and precisely marks the required lines.
**Collision avoidance**: The robot is equipped with a collision avoidance program that works in conjunction with the path tracking algorithm. This allows iLMBt to maneuver smoothly around obstacles while reaching the designated starting point.
**Improved accuracy**: With the use of advanced navigation technologies such as GPS, IMU, and encoders, iLMBt ensures high accuracy in line marking, resulting in professionally marked sports fields.
**Sensor integration**: iLMBt incorporates various sensors, including LIDAR, for obstacle avoidance and local mapping. These sensors enable the robot to navigate safely and efficiently. Accurate localisation was achieved using Kalman filter.

## Hardware and Electronics
**Raspberry Pi**: The Raspberry Pi serves as the main controller for iLMBt, handling higher-level tasks such as path planning and communication.
**Arduino Mega**: The Arduino Mega is responsible for low-level control and interfacing with the robot's actuators and sensors.
**GPS**: A GPS module is used for global positioning, allowing iLMBt to determine its precise location on the sports field.
**IMU**: An IMU (Inertial Measurement Unit) provides orientation and motion data, contributing to accurate navigation.
**Encoder**: Encoders are employed for precise wheel odometry, enabling the robot to track its position and distance traveled.
**LIDAR**: The LIDAR sensor enables iLMBt to detect obstacles and create a local map of its surroundings for effective collision avoidance.

## Contributions
Contributions to the iLMBt project are welcome! If you have any improvements, bug fixes, or new features to contribute, please follow the guidelines outlined in the Contribution document. Your contributions will be greatly appreciated and help advance the capabilities of iLMBt.

## Contact
For any questions, suggestions, or collaborations, please feel free to contact the project maintainers:

Ashiq Rahman: ashiqrahmanab@gmail.com
Thank you for your interest in iLMBt! We hope this project brings automation and improved line marking capabilities to sports fields worldwide.
