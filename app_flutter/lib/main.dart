import 'dart:io';

import 'package:flutter/material.dart';
import 'package:mqtt_client/mqtt_client.dart';
import 'package:mqtt_client/mqtt_server_client.dart';
import 'conteudo_pagina_principal.dart';
import 'conteudo_pagina_configuracoes.dart';
import 'conteudo_pagina_adicionar_objeto.dart';

void main() {
  runApp(const SmartBuilding());
}

class SmartBuilding extends StatelessWidget {
  const SmartBuilding({Key? key}) : super(key: key);

  static const String _title = "Smart Building";

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: _title,
      home: TelaPrincipal(),
    );
  }
}

class TelaPrincipal extends StatefulWidget {
  MqttServerClient mqttClient = MqttServerClient('', '');

  TelaPrincipal({Key? key}) : super(key: key) {
    conectarComMqtt();
  }

  Future<bool> conectarComMqtt() async {
    mqttClient.setProtocolV311();
    mqttClient.keepAlivePeriod = 20;

    //TODO: ESSE DADOS VÃO VIR DE UM BANCO DE DADOS NO APLICATIVO
    mqttClient.port = 1883;
    mqttClient.server = "10.0.0.100";
    mqttClient.clientIdentifier = "android-ABE651561D";
    // TODO: ARRUMAR ISSO DAQUI EM OUTUBRO

    try {
      await mqttClient.connect();
    } on NoConnectionException catch (e) {
      mqttClient.disconnect();
    } on SocketException catch (e) {
      mqttClient.disconnect();
    }

    if (mqttClient.connectionStatus!.state != MqttConnectionState.connected) {
      print('MQTT DESCONECTADO');
      mqttClient.disconnect();
      return false;
    }

    print('MQTT CONECTADO');
    const pubTopic = 'Dart/Mqtt_client/testtopic';
    final builder = MqttClientPayloadBuilder();
    builder.addString('Hello from mqtt_client');
    mqttClient.publishMessage(pubTopic, MqttQos.exactlyOnce, builder.payload!);
    return true;
  }

  @override
  State<TelaPrincipal> createState() => _TelaPrincipalState();
}

class _TelaPrincipalState extends State<TelaPrincipal> {
  int _selectedIndex = 1;

  late Widget fragment = conteudoPaginaPrincipal();

  void _onItemTapped(int index) {
    if (index == 0) {
      fragment = conteudoPaginaAdicionarObjeto();
    } else if (index == 1) {
      fragment = conteudoPaginaPrincipal();
    } else if (index == 2) {
      fragment = conteudoPaginaConfiguracoes(widget.mqttClient);
    } else {
      fragment = conteudoPaginaPrincipal();
    }
    setState(() {
      _selectedIndex = index;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Center(
        child: fragment,
      ),
      bottomNavigationBar: BottomNavigationBar(
        items: const <BottomNavigationBarItem>[
          BottomNavigationBarItem(
            icon: Icon(Icons.add),
            label: 'Adicionar',
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.home),
            label: 'Home',
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.settings),
            label: 'Ajustes',
          ),
        ],
        currentIndex: _selectedIndex,
        selectedItemColor: Colors.blue,
        onTap: _onItemTapped,
      ),
    );
  }
}
