#!/bin/sh

/create_rpc_map_config.sh $RPC_MAP_PATH && \
/create_db_config.sh $DB_OPTION_PATH && \
/create_kafka_config.sh $KAFKA_OPTION_PATH && \
user-service