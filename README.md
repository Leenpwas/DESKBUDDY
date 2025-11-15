

#![WhatsApp Image 2025-11-15 at 23 17 51_d2a02337](https://github.com/user-attachments/assets/fec63ba6-c664-41bb-9e53-126982d598b0)


# 6-DOF Robotic Arm (ST3215 Servos + ESP32)

This project implements a fully functional 6-DOF robotic manipulator powered by 
high-torque ST3215 digital servos and an ESP32 microcontroller. The arm supports 
manual angle control, Wi-Fi control, and expandable inverse kinematics.

---

##  Features

- 6 Degrees of Freedom (base, shoulder, elbow, wrist pitch, wrist roll, gripper)
- High-torque **ST3215 digital servos** (25kg·cm)
- **ESP32-based control** with PWM generation
- Stable external servo power supply (6–7.4V, 10A peak)
- Web dashboard for wireless control
- Smooth motion sequencing with acceleration limits
- Expandable to inverse kinematics and object tracking

---

##  Hardware Used

| Component        | Description                                       |
|------------------|---------------------------------------------------|
| ESP32 DevKit     | Main controller, WiFi + PWM generation            |
| ST3215 Servos    | 25kg·cm torque for all 6 joints                   |
| Servo Power Rail | 6–7.4V DC supply, ≥10A                            |
| 3D Printed Frame | Custom links + mounting brackets                  |
| Buck Converter   | Power regulation                                  |



---

##  System Architecture

The ESP32 controls all six servos using dedicated PWM channels. The system 
accepts angle commands from the onboard web interface or serial inputs.
##  ROS Integration (ROS1/ROS2 Compatible)

This robotic arm includes full support for ROS, enabling high-level motion 
control, visualization, trajectory planning, and integration with computer vision 
pipelines.

### ✔ Supported ROS Capabilities
- Real-time joint state publishing from the ESP32
- Control of all 6 servos via `/joint_commands` topic
- URDF description of the full 6-DOF manipulator
- RViz visualization of joint positions
- MoveIt! integration for:
  - IK solving
  - Collision-aware planning
  - Trajectory generation
- Modular ROS nodes for serial communication



