#!/bin/sh

if [[ $# -eq 0 ]] ; then
    echo 'No arguments supplied'
    exit 1
fi

PATH=$1

echo "Creating config file ${PATH}"
echo -e "db:
  db_name: ${DB_NAME}
  user: ${DB_USERNAME}
  password: ${DB_PASSWORD}
  host: ${DB_HOST}
  port: ${DB_PORT}
  telegram_user_table_name: ${DB_TELEGRAM_USER_TABLE_NAME}
  
kafka:
  broker: ${KAFKA_BROKERS}
  telegram_notification_topic: ${KAFKA_TELEGRAM_NOTIFICATION_TOPIC}
  consumer_group: ${KAFKA_CONSUMER_GROUP}

telegram:
  bot_token: ${TELEGRAM_BOT_TOKEN}" > ${PATH}