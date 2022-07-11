#!/bin/sh
clear
apt install -y curl
curl -fsSL https://get.docker.com -o get-docker.sh
sudo bash get-docker.sh
apt-get update
usermod -aG docker pi
sudo apt install -y docker-compose
echo "------------ Docker esta instalado ------------\n\n\n"

sudo usermod -aG docker pi
