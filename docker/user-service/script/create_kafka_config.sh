#!/bin/sh

if [[ $# -eq 0 ]] ; then
    echo 'No arguments supplied'
    exit 1
fi

PATH=$1

echo "Creating kafka config file ${PATH}"
echo -e "brokers: ${KAFKA_BROKERS}
telegram_notification_topic: ${KAFKA_TELEGRAM_NOTIFICATION_TOPIC}" > ${PATH}