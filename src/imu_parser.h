#pragma once
#include <string>
#include <optional>
#include <cstdint>
#include <vector>
#include "imu_data.hpp"  // generado por idlc (ruta según tu build)

namespace imuapp {

// Parser minimalista para frames de IMU en texto (CSV) o NMEA-like.
// Formato de ejemplo (CSV):
// TS(us),yaw,pitch,roll,gyro_x,gyro_y,gyro_z,accel_x,accel_y,accel_z,mag_x,mag_y,mag_z
// 172493812345678,12.34,1.23,-3.21,0.01,0.02,0.03,0.10,0.20,0.30,45.1,22.0,-5.3
//
// NOTA: adapta 'decode' a tu formato real del VN-100 si usas binario o ASCII propietario.

class ImuParser {
public:
  explicit ImuParser(uint32_t sensor_id = 1) : sensor_id_(sensor_id) {}

  // Intenta parsear un frame textual; devuelve sample listo para publicar.
  std::optional<imu::ImuData> parseFrame(const std::string& frame);

  // Permite cambiar el ID de sensor cuando sea multi-IMU
  void setSensorId(uint32_t sid) { sensor_id_ = sid; }

private:
  uint32_t sensor_id_;

  static bool splitCSV(const std::string& s, std::vector<std::string>& out);
  static bool toDouble(const std::string& s, double& v);
  static bool toUint64(const std::string& s, uint64_t& v);
};

} // namespace imuapp
