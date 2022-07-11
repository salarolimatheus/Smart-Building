#!/bin/sh
docker --version

docker-compose build
docker-compose up -d
docker-compose down

cp ./mosquitto-conf/mosquitto.conf /var/lib/docker/volumes/sb-docker_mosquitto-conf/_data/mosquitto.conf

rm /var/lib/docker/volumes/sb-docker_node-red-data/_data/settings.js
cp ./node-red-data/settings.js /var/lib/docker/volumes/sb-docker_node-red-data/_data/settings.js

chmod 777 /var/lib/docker/volumes/sb-docker_node-red-data/_data/settings.js
chown 1000:1000 /var/lib/docker/volumes/sb-docker_node-red-data/_data/settings.js

chmod 777 /var/lib/docker/volumes/sb-docker_mosquitto-conf/_data/mosquitto.conf
chown 1000:1000 /var/lib/docker/volumes/sb-docker_mosquitto-conf/_data/mosquitto.conf

docker-compose up -d
