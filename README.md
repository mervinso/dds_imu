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

---

## ⚙️ Requirements
- Ubuntu 22.04 (tested)
- GCC / G++ ≥ 11
- CMake ≥ 3.16
- [Cyclone DDS](https://github.com/eclipse-cyclonedds/cyclonedds)
- Git

---

## 🛠️ Build Instructions
```bash
# Clone repo
git https://github.com/mervinso/dds_imu.git
cd dds-imu

# Create build directory
mkdir build && cd build
cmake ..
make
```

---

## ▶️ Run Example
```bash
# Publisher
./dds_imu_publisher datasets/imu_sample_log.csv

# Subscriber
./dds_imu_subscriber

# Monitor with DDS Spy
ddsspy -t imu/ImuData
```

---

## 📊 QoS Profiles
Default QoS for the publisher is defined in  `qos/imu_qos.xml `:
- Reliable delivery
- KeepLast = 10
- Deadline = 5 ms
- LatencyBudget = 1 ms
- Liveliness = Automatic (1 s)

To use this profile:
```bash
export DDS_QOS_PROFILES=file://$PWD/qos/imu_qos.xml
```

---
## 📜 Citation

If you use this repository, please cite:
```bibtex
@inproceedings{Sosa2025-DDS-IMU,
  author    = {Mervin Jesus Sosa Borrero and Jairo Enrique Serrano Castañeda and Juan Carlos Martinez Santos and Edwin Alexander Puertas Del Castillo},
  title     = {Implementation of a DDS-Based Publishing Interface for Real-Time Inertial Sensor Data in Navigation Systems},
  booktitle = {Proc. IEEE Caribbean Colombian Conference (C3)},
  year      = {2025},
  publisher = {IEEE},
  doi       = {10.1109/C3.2025.XXXXXXX}
}
```

---
## 📖 License
This project is licensed under the ![MIT License.](https://github.com/mervinso/dds_imu/blob/main/LICENSE)

---

## 🔗 Related References
- OMG DDS Specification: [Official Website](https://www.omg.org/spec/DDS)
- OMG IDL4 to C++ Mapping: [Official Website](https://www.omg.org/spec/IDL4-CPPS)
- Eclipse Cyclone DDS: [Official Repository](https://github.com/eclipse-cyclonedds/cyclonedds)