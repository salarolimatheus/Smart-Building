import 'package:flutter/material.dart';
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
    return const MaterialApp(
      title: _title,
      home: TelaPrincipal(),
    );
  }
}

class TelaPrincipal extends StatefulWidget {
  const TelaPrincipal({Key? key}) : super(key: key);

  @override
  State<TelaPrincipal> createState() => _TelaPrincipalState();
}

class _TelaPrincipalState extends State<TelaPrincipal> {
  int _selectedIndex = 0;

  static const List<Widget> _widgetOptions = <Widget>[
    conteudoPaginaAdicionarObjeto(),
    conteudoPaginaPrincipal(),
    conteudoPaginaConfiguracoes(),
  ];

  void _onItemTapped(int index) {
    setState(() {
      _selectedIndex = index;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Center(
        child: _widgetOptions.elementAt(_selectedIndex),
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
