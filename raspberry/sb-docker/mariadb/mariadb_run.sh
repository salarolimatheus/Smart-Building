docker run -d \
 --hostname=mariadb \
 --name=mariadb \
 --net=host \
 -v $PWD/config:/etc/mysql/conf.d \
 -v $PWD/data:/var/lib/mysql \
 -e MYSQL_ROOT_PASSWORD=PASSWD \
 -e TZ="Europe/Amsterdam" \
 --restart=unless-stopped \
 mariadb