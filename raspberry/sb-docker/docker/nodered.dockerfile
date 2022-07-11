FROM nodered/node-red:1.3.5-10

USER node-red

RUN npm install node-red-contrib-re-postgres
RUN npm install node-red-node-email

EXPOSE 1880
