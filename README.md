A senha para todas as aplicações é:

Para utilizar o homeassistant no docker:
docker run -d --name homeassistant -p 8123:8123 --privileged --restart=unless-stopped -e TZ=America/Sao_Paulo -v D:\Docker\homeassistant_config:/config ghcr.io/home-assistant/home-assistant:stable

http://localhost:8123
usuario: admin
senha: senha

Mais informações:
https://www.home-assistant.io/installation/linux

mosquitto_sub -t "interruptor/touch0_status"
mosquitto_sub -t "interruptor/touch2_status"
mosquitto_sub -t "interruptor/touch0_click"
mosquitto_sub -t "interruptor/touch2_click"
