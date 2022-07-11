#!/bin/sh
docker-compose down

docker container prune
docker volume prune
docker image prune
