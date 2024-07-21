#!/bin/sh

if [[ $# -eq 0 ]] ; then
    echo 'No arguments supplied'
    exit 1
fi

PATH=$1

echo "Creating db config file ${PATH}"
echo -e "db_name: ${DB_NAME}
user: ${DB_USERNAME}
password: ${DB_PASSWORD}
host: ${DB_HOST}
port: ${DB_PORT}
user_table_name: ${DB_USER_TABLE_NAME}" > ${PATH}