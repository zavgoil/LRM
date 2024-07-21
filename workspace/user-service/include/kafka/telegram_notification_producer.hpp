#pragma once

#include <librdkafka/rdkafkacpp.h>

#include <memory>
#include <string>

/// @brief Apache Kafka producer для отправки уведомлений в телеграм
/// Имейте ввиду, что отправка возможна лишь тем пользователям, которые
/// инициализировали общение с телеграм ботом
class TelegramNotificationProducer {
 public:
  TelegramNotificationProducer(std::string brokers, std::string topic);

  /// @brief Отправить сообщение в телеграм
  /// @param username Пользователь, которому отправляем сообщение
  /// @param message Сообщение
  void sendMessage(std::string username, std::string message);

 private:
  std::unique_ptr<RdKafka::Producer> producer_;
  std::unique_ptr<RdKafka::Topic> kafka_topic_;
};