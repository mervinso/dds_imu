#include "imu_parser.h"
#include <sstream>
#include <charconv>

namespace imuapp {

bool ImuParser::splitCSV(const std::string& s, std::vector<std::string>& out) {
  out.clear();
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, ',')) out.emplace_back(item);
  return !out.empty();
}

bool ImuParser::toDouble(const std::string& s, double& v) {
  // std::from_chars para double aún no está ampliamente soportado; usamos stod con try/catch.
  try { v = std::stod(s); return true; } catch (...) { return false; }
}

bool ImuParser::toUint64(const std::string& s, uint64_t& v) {
  try { v = static_cast<uint64_t>(std::stoull(s)); return true; } catch (...) { return false; }
}

std::optional<imu::ImuData> ImuParser::parseFrame(const std::string& frame) {
  // Ignora líneas vacías/comentarios
  if (frame.empty() || frame[0] == '#') return std::nullopt;

  std::vector<std::string> f;
  if (!splitCSV(frame, f)) return std::nullopt;

  // Esperamos 13 campos (timestamp + 12 valores). Ajusta si tu IMU emite menos/más.
  if (f.size() < 13) return std::nullopt;

  imu::ImuData sample{};
  sample.sensor_id(sensor_id_);

  uint64_t ts; if (!toUint64(f[0], ts)) return std::nullopt;
  sample.timestamp(ts);

  // Orientación (deg)
  double v=0;
  if (!toDouble(f[1], v)) return std::nullopt; sample.yaw(static_cast<float>(v));
  if (!toDouble(f[2], v)) return std::nullopt; sample.pitch(static_cast<float>(v));
  if (!toDouble(f[3], v)) return std::nullopt; sample.roll(static_cast<float>(v));

  // Giros (deg/s)
  if (!toDouble(f[4], v)) return std::nullopt; sample.gyro_x(static_cast<float>(v));
  if (!toDouble(f[5], v)) return std::nullopt; sample.gyro_y(static_cast<float>(v));
  if (!toDouble(f[6], v)) return std::nullopt; sample.gyro_z(static_cast<float>(v));

  // Aceleraciones (m/s^2)
  if (!toDouble(f[7], v))  return std::nullopt; sample.accel_x(static_cast<float>(v));
  if (!toDouble(f[8], v))  return std::nullopt; sample.accel_y(static_cast<float>(v));
  if (!toDouble(f[9], v))  return std::nullopt; sample.accel_z(static_cast<float>(v));

  // Magnetómetro (µT) — opcional
  if (!toDouble(f[10], v)) v = 0; sample.mag_x(static_cast<float>(v));
  if (!toDouble(f[11], v)) v = 0; sample.mag_y(static_cast<float>(v));
  if (!toDouble(f[12], v)) v = 0; sample.mag_z(static_cast<float>(v));

  return sample;
}

} // namespace imuapp
