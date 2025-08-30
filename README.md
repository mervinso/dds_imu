# DDS IMU Publishing Interface

[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Build](https://img.shields.io/badge/build-CMake%20%2B%20GCC-blue)]()
[![DDS](https://img.shields.io/badge/middleware-CycloneDDS-orange)]()

Implementation of a **native DDS-based publishing interface** for inertial sensor data, validated with a VectorNav VN-100 IMU.  
This repository accompanies the paper:

> **M. J. Sosa Borrero, J. E. Serrano Castañeda, J. C. Martinez Santos, E. A. Puertas Del Castillo**.  
> *Implementation of a DDS-Based Publishing Interface for Real-Time Inertial Sensor Data in Navigation Systems*.  
> Proceedings of **IEEE Caribbean Colombian Conference (C3 2025)**, IEEE Xplore (forthcoming).  

---

## 📑 Features
- Serial parsing of IMU data (yaw, pitch, roll, gyro, accel, mag).
- DDS publishing via [Eclipse Cyclone DDS](https://projects.eclipse.org/projects/iot.cyclonedds).
- IDL 4.2 schemas for type-safe communication.
- QoS configuration via XML profiles (`qos/imu_qos.xml`).
- Example subscriber for validation with **DDS Spy**.
- Modular and portable design, aligned with OMG specifications.

---

## 📂 Repository Structure

```bash
dds-imu-dds-interface/
│── CMakeLists.txt
│── README.md
│── LICENSE
│
├── idl/ # IDL schemas
│ └── imu_data.idl
│
├── src/ # C++ source code
│ ├── imu_parser.cpp
│ ├── dds_publisher.cpp
│ ├── dds_subscriber.cpp
│ └── main.cpp
│
├── include/ # Header files
│ └── imu_parser.hpp
│
├── qos/ # QoS profiles for Cyclone DDS
│ └── imu_qos.xml
│
├── config/ # Setup and run scripts
│ ├── setup.sh
│ └── run.sh
│
├── docs/ # Documentation
│ ├── INSTALL.md
│ ├── USAGE.md
│ └── ARCHITECTURE.md
│
└── datasets/ # Example logs from lab validation
├── imu_sample_log.csv
└── dds_output_log.csv
```