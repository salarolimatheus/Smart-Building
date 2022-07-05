Para utilizar o homeassistant no docker:
docker run -d --name homeassistant --privileged --restart=unless-stopped -e TZ=America/Sao_Paulo -v D:\Docker\homeassistant_config:/config --network=host ghcr.io/home-assistant/home-assistant:stable

http://<host>:8123

Mais informações:
https://www.home-assistant.io/installation/linux
