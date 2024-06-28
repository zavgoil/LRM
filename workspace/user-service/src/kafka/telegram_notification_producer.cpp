#include "kafka/telegram_notification_producer.hpp"

#include <memory>

TelegramNotificationProducer::TelegramNotificationProducer(std::string brokers,
                                                           std::string topic) {
  std::string errstr;

  auto conf = std::unique_ptr<RdKafka::Conf>(
      RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL));
  auto tconf = std::unique_ptr<RdKafka::Conf>(
      RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC));

  if (conf->set("bootstrap.servers", brokers, errstr) !=
      RdKafka::Conf::CONF_OK) {
  }

  producer_ = std::unique_ptr<RdKafka::Producer>(
      RdKafka::Producer::create(conf.get(), errstr));
  if (!producer_) {
  }

  kafka_topic_ = std::unique_ptr<RdKafka::Topic>(
      RdKafka::Topic::create(producer_.get(), topic, tconf.get(), errstr));
  if (!kafka_topic_) {
  }
}

void TelegramNotificationProducer::sendMessage(std::string username,
                                               std::string message) {
  RdKafka::ErrorCode resp = producer_->produce(
      kafka_topic_.get(), RdKafka::Topic::PARTITION_UA,
      RdKafka::Producer::RK_MSG_COPY, const_cast<char *>(message.c_str()),
      message.size(), &username, NULL);

  if (resp != RdKafka::ERR_NO_ERROR) {
  }

  producer_->poll(0);
}