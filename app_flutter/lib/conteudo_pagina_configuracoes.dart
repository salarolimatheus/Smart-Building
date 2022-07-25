import 'package:flutter/material.dart';

class conteudoPaginaConfiguracoes extends StatelessWidget {
  const conteudoPaginaConfiguracoes({Key? key}) : super(key: key);

  static String mqttEndereco = "sb-docker.duckdns.org";
  static String mqttPorta = "1883";
  static String mqttClientID = "mobile_client_id";

  @override
  Widget build(BuildContext context) {
    return Center(
      child: Column(
        children: [
          const Padding(padding: EdgeInsets.all(20)),
          const Card(
            margin: EdgeInsets.only(left: 100, right: 100),
            child: ListTile(
              leading: Icon(Icons.face, size: 50),
              title: Text('Matheus Salaroli'),
              subtitle: Text('Avenida São Paulo, 521'),
            ),
          ),
          const Padding(padding: EdgeInsets.all(20)),
          Card(
            margin: const EdgeInsets.only(left: 20, right: 20),
            child: Padding(
              padding: const EdgeInsets.only(
                  left: 20, right: 20, top: 20, bottom: 10),
              child: Column(
                mainAxisAlignment: MainAxisAlignment.center,
                children: [
                  const Text(
                    'Configurações MQTT',
                    style: TextStyle(
                      fontSize: 20,
                      fontWeight: FontWeight.bold,
                    ),
                  ),
                  const Padding(padding: EdgeInsets.all(20)),
                  TextField(
                    controller: TextEditingController(text: mqttEndereco),
                    onChanged: (value) {
                      mqttEndereco = value;
                    },
                    decoration: const InputDecoration(
                      filled: true,
                      fillColor: Colors.white,
                      labelText: "Endereço MQTT",
                      border: OutlineInputBorder(),
                    ),
                  ),
                  const Padding(padding: const EdgeInsets.all(10)),
                  TextField(
                    controller: TextEditingController(text: mqttPorta),
                    onChanged: (value) {
                      mqttPorta = value;
                    },
                    decoration: const InputDecoration(
                      filled: true,
                      fillColor: Colors.white,
                      labelText: "Porta",
                      border: OutlineInputBorder(),
                    ),
                  ),
                  const Padding(padding: EdgeInsets.all(10)),
                  TextField(
                    controller: TextEditingController(text: mqttClientID),
                    onChanged: (value) {
                      mqttClientID = value;
                    },
                    decoration: const InputDecoration(
                      filled: true,
                      fillColor: Colors.white,
                      labelText: "Client ID",
                      border: OutlineInputBorder(),
                    ),
                  ),
                  const Padding(padding: EdgeInsets.all(10)),
                  OutlinedButton(
                    style: OutlinedButton.styleFrom(
                      padding: const EdgeInsets.all(5),
                      fixedSize: const Size(120, 40),
                      textStyle: const TextStyle(fontSize: 25),
                    ),
                    onPressed: () {},
                    child: const Text("Conectar"),
                  ),
                ],
              ),
            ),
          ),
        ],
      ),
    );
  }
}
