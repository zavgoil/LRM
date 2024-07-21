#!/bin/sh

if [[ $# -eq 0 ]] ; then
    echo 'No arguments supplied'
    exit 1
fi

PATH=$1

echo "Creating rpc map config file ${PATH}"
echo -e "user_service:
  uri: "user-service"
  port: 50051" > ${PATH}