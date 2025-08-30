#include <iostream>
#include <string>
#include <fstream>
#include "imu_parser.h"
#include "dds_publisher.h"

int main(int argc, char** argv) {
  using namespace imuapp;

  const std::string topic = "imu/ImuData";
  ImuPublisher pub(topic);

  ImuParser parser(/*sensor_id=*/1);

  std::istream* in = &std::cin;
  std::ifstream file;
  if (argc > 1) {
    file.open(argv[0 + 1]);
    if (!file) {
      std::cerr << "Cannot open file: " << argv[1] << std::endl;
      return 1;
    }
    in = &file;
  }

  std::string line;
  while (std::getline(*in, line)) {
    auto sample = parser.parseFrame(line);
    if (sample) {
      pub.write(*sample);
    }
  }
  return 0;
}
