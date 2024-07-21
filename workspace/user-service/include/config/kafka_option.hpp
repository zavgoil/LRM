#pragma once

#include <project-util/format/yaml.hpp>
#include <project-util/format/yaml_macro.hpp>
#include <string>

struct KafkaOption : public YamlFormat<KafkaOption> {
  std::string brokers = "";
  std::string telegram_notification_topic = "";
};
DEFINE_YAML(KafkaOption, brokers, telegram_notification_topic)
