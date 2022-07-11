FROM postgres:11

COPY ./postgres-data/init.sql /docker-entrypoint-initdb.d/
