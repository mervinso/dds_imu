#pragma once
#include <chrono>
#include <string>
#include <dds/dds.hpp>
#include "imu_data.hpp" // tipo generado (namespace imu)

namespace imuapp {

struct QosConfig {
  // Valores por defecto pensados para 200 Hz (VN-100)
  std::chrono::milliseconds deadline{5};
  std::chrono::milliseconds latency_budget{1};
  int history_depth{10};
};

class ImuPublisher {
public:
  ImuPublisher(const std::string& topic_name,
               const QosConfig& cfg = QosConfig(),
               int domain_id = 0);

  void write(const imu::ImuData& sample);

private:
  dds::domain::DomainParticipant participant_;
  dds::topic::Topic<imu::ImuData> topic_;
  dds::pub::Publisher publisher_;
  dds::pub::DataWriter<imu::ImuData> writer_;
};

} // namespace imuapp
