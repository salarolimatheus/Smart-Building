import 'package:flutter/material.dart';

class conteudoPaginaPrincipal extends StatelessWidget {
  const conteudoPaginaPrincipal({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Center(
      child: botao(),
    );
  }
}

class botao extends StatefulWidget {
  @override
  State<botao> createState() => _botaoState();
}

class _botaoState extends State<botao> {
  Color cor_botao = Colors.red;
  @override
  Widget build(BuildContext context) {
    return Container(
      child: ElevatedButton.icon(
        onPressed: () {
          if (cor_botao == Colors.red) {
            cor_botao = Colors.green;
          } else {
            cor_botao = Colors.red;
          }
          setState(() {});
        },
        icon: Icon(Icons.power_settings_new, size: 25),
        label: Text("Tomada 1"),
        style: ElevatedButton.styleFrom(primary: cor_botao),
      ),
    );
  }
}
