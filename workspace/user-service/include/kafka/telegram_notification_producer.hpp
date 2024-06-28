#pragma once

#include <librdkafka/rdkafkacpp.h>

#include <memory>
#include <string>

class TelegramNotificationProducer {
 public:
  TelegramNotificationProducer(std::string brokers, std::string topic);

  void sendMessage(std::string username, std::string message);

 private:
  std::unique_ptr<RdKafka::Producer> producer_;
  std::unique_ptr<RdKafka::Topic> kafka_topic_;
};