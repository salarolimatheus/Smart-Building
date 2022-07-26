import 'package:flutter/material.dart';

class conteudoPaginaPrincipal extends StatelessWidget {
  const conteudoPaginaPrincipal({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Center(
      child: Row(
        mainAxisAlignment: MainAxisAlignment.center,
        children: [
          Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              Text(
                "Tomada 1",
                style: TextStyle(
                  fontSize: 24,
                  fontWeight: FontWeight.bold,
                ),
              ),
              Padding(padding: EdgeInsets.all(10)),
              botao(),
              Padding(padding: EdgeInsets.all(10)),
              botao(),
              Padding(padding: EdgeInsets.all(10)),
              botao(),
              Padding(padding: EdgeInsets.all(10)),
              botao(),
            ],
          ),
          Padding(padding: EdgeInsets.all(20)),
          Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              Text(
                "Tomada 2",
                style: TextStyle(
                  fontSize: 24,
                  fontWeight: FontWeight.bold,
                ),
              ),
              Padding(padding: EdgeInsets.all(10)),
              botao(),
              Padding(padding: EdgeInsets.all(10)),
              botao(),
              Padding(padding: EdgeInsets.all(10)),
              botao(),
              Padding(padding: EdgeInsets.all(10)),
              botao(),
            ],
          ),
        ],
      ),
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
    return TextButton(
      onPressed: () {
        if (cor_botao == Colors.red) {
          cor_botao = Colors.green;
        } else {
          cor_botao = Colors.red;
        }
        setState(() {});
      },
      child: Icon(Icons.power_settings_new, size: 50),
      style: TextButton.styleFrom(
        primary: Colors.white,
        backgroundColor: cor_botao,
        fixedSize: Size(150, 100),
        shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(30)),
      ),
    );
  }
}
