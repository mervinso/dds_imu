#include "dds_publisher.h"

namespace imuapp {

using dds::core::Time;
using dds::core::policy::Reliability;
using dds::core::policy::History;
using dds::core::policy::ResourceLimits;
using dds::core::policy::Deadline;
using dds::core::policy::LatencyBudget;
using dds::core::policy::Liveliness;

ImuPublisher::ImuPublisher(const std::string& topic_name,
                           const QosConfig& cfg,
                           int domain_id)
  : participant_(domain_id),
    topic_(participant_, topic_name),
    publisher_(participant_)
{
  // QoS del DataWriter
  auto qos = publisher_.default_datawriter_qos();

  qos << Reliability::Reliable()
      << History::KeepLast(cfg.history_depth)
      << Deadline(dds::core::Duration::from_millis(cfg.deadline.count()))
      << LatencyBudget(dds::core::Duration::from_millis(cfg.latency_budget.count()))
      << Liveliness::Automatic(dds::core::Duration::from_secs(1));

  // Límites de recursos conservadores
  qos << ResourceLimits().max_samples(100).max_instances(32).max_samples_per_instance(100);

  writer_ = dds::pub::DataWriter<imu::ImuData>(publisher_, topic_, qos);
}

void ImuPublisher::write(const imu::ImuData& sample) {
  writer_.write(sample);
}

} // namespace imuapp
