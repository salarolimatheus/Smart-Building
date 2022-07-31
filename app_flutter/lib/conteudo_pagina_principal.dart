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
              rele1(),
              Padding(padding: EdgeInsets.all(10)),
              timer1_on(),
              Padding(padding: EdgeInsets.all(10)),
              timer1_off(),
              Padding(padding: EdgeInsets.all(10)),
              touch1(),
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
              rele2(),
              Padding(padding: EdgeInsets.all(10)),
              timer2_on(),
              Padding(padding: EdgeInsets.all(10)),
              timer2_off(),
              Padding(padding: EdgeInsets.all(10)),
              touch2(),
            ],
          ),
        ],
      ),
    );
  }
}

//Parâmetros do botão
double largura = 120;
double altura = 80;
double raio_borda = 30;
double tamanho_icone = 50;

//Definindo os botões
class rele1 extends StatefulWidget {
  @override
  State<rele1> createState() => _rele1State();
}

class _rele1State extends State<rele1> {
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
      child: Icon(Icons.power_settings_new, size: tamanho_icone),
      style: TextButton.styleFrom(
        primary: Colors.white,
        backgroundColor: cor_botao,
        fixedSize: Size(largura, altura),
        shape: RoundedRectangleBorder(
            borderRadius: BorderRadius.circular(raio_borda)),
      ),
    );
  }
}

class rele2 extends StatefulWidget {
  @override
  State<rele2> createState() => _rele2State();
}

class _rele2State extends State<rele2> {
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
      child: Icon(Icons.power_settings_new, size: tamanho_icone),
      style: TextButton.styleFrom(
        primary: Colors.white,
        backgroundColor: cor_botao,
        fixedSize: Size(largura, altura),
        shape: RoundedRectangleBorder(
            borderRadius: BorderRadius.circular(raio_borda)),
      ),
    );
    ;
  }
}

class timer1_on extends StatefulWidget {
  @override
  State<timer1_on> createState() => _timer1_onState();
}

class _timer1_onState extends State<timer1_on> {
  String tempo = '2';
  @override
  Widget build(BuildContext context) {
    return Column(children: [
      Column(children: [
        Text("Ligar por ",
            style: TextStyle(
              fontSize: 16,
              fontWeight: FontWeight.bold,
            )),
        Container(
            width: 60,
            height: 20,
            child: TextField(
                onChanged: (Time) {
                  tempo = Time;
                },
                keyboardType: TextInputType.number,
                style: TextStyle(
                  fontSize: 16,
                ),
                decoration: InputDecoration(
                  //filled: true,
                  //fillColor: Colors.white,
                  border: OutlineInputBorder(),
                ))),
        Text("segundos",
            style: TextStyle(
              fontSize: 16,
              fontWeight: FontWeight.bold,
            ))
      ]),
      TextButton(
        onPressed: () {
          print("ligar por $tempo segundos");
          setState(() {});
        },
        child: Icon(Icons.access_time_outlined, size: tamanho_icone),
        style: TextButton.styleFrom(
          primary: Colors.white,
          backgroundColor: Colors.greenAccent,
          fixedSize: Size(largura, altura),
          shape: RoundedRectangleBorder(
              borderRadius: BorderRadius.circular(raio_borda)),
        ),
      )
    ]);
  }
}

class timer2_on extends StatefulWidget {
  @override
  State<timer2_on> createState() => _timer2_onState();
}

class _timer2_onState extends State<timer2_on> {
  String tempo = '2';
  @override
  Widget build(BuildContext context) {
    return Column(children: [
      Column(children: [
        Text("Ligar por ",
            style: TextStyle(
              fontSize: 16,
              fontWeight: FontWeight.bold,
            )),
        Container(
            width: 60,
            height: 20,
            child: TextField(
                onChanged: (Time) {
                  tempo = Time;
                },
                keyboardType: TextInputType.number,
                style: TextStyle(
                  fontSize: 16,
                ),
                decoration: InputDecoration(
                  //filled: true,
                  //fillColor: Colors.white,
                  border: OutlineInputBorder(),
                ))),
        Text("segundos",
            style: TextStyle(
              fontSize: 16,
              fontWeight: FontWeight.bold,
            ))
      ]),
      TextButton(
        onPressed: () {
          print("ligar por $tempo segundos");
          setState(() {});
        },
        child: Icon(Icons.access_time_outlined, size: tamanho_icone),
        style: TextButton.styleFrom(
          primary: Colors.white,
          backgroundColor: Colors.greenAccent,
          fixedSize: Size(largura, altura),
          shape: RoundedRectangleBorder(
              borderRadius: BorderRadius.circular(raio_borda)),
        ),
      )
    ]);
  }
}

class timer1_off extends StatefulWidget {
  @override
  State<timer1_off> createState() => _timer1_offState();
}

class _timer1_offState extends State<timer1_off> {
  String tempo = '2';
  @override
  Widget build(BuildContext context) {
    return Column(children: [
      Column(children: [
        Text("Desligar por ",
            style: TextStyle(
              fontSize: 16,
              fontWeight: FontWeight.bold,
            )),
        Container(
            width: 60,
            height: 20,
            child: TextField(
                onChanged: (Time) {
                  tempo = Time;
                },
                keyboardType: TextInputType.number,
                style: TextStyle(
                  fontSize: 16,
                ),
                decoration: InputDecoration(
                  //filled: true,
                  //fillColor: Colors.white,
                  border: OutlineInputBorder(),
                ))),
        Text("segundos",
            style: TextStyle(
              fontSize: 16,
              fontWeight: FontWeight.bold,
            ))
      ]),
      TextButton(
        onPressed: () {
          print("Desligar por $tempo segundos");
          setState(() {});
        },
        child: Icon(Icons.access_time_outlined, size: tamanho_icone),
        style: TextButton.styleFrom(
          primary: Colors.white,
          backgroundColor: Colors.redAccent,
          fixedSize: Size(largura, altura),
          shape: RoundedRectangleBorder(
              borderRadius: BorderRadius.circular(raio_borda)),
        ),
      )
    ]);
  }
}

class timer2_off extends StatefulWidget {
  @override
  State<timer2_off> createState() => _timer2_offState();
}

class _timer2_offState extends State<timer2_off> {
  String tempo = '2';
  @override
  Widget build(BuildContext context) {
    return Column(children: [
      Column(children: [
        Text("Desligar por ",
            style: TextStyle(
              fontSize: 16,
              fontWeight: FontWeight.bold,
            )),
        Container(
            width: 60,
            height: 20,
            child: TextField(
                onChanged: (Time) {
                  tempo = Time;
                },
                keyboardType: TextInputType.number,
                style: TextStyle(
                  fontSize: 16,
                ),
                decoration: InputDecoration(
                  //filled: true,
                  //fillColor: Colors.white,
                  border: OutlineInputBorder(),
                ))),
        Text("segundos",
            style: TextStyle(
              fontSize: 16,
              fontWeight: FontWeight.bold,
            ))
      ]),
      TextButton(
        onPressed: () {
          print("Desligar por $tempo segundos");
          setState(() {});
        },
        child: Icon(Icons.access_time_outlined, size: tamanho_icone),
        style: TextButton.styleFrom(
          primary: Colors.white,
          backgroundColor: Colors.redAccent,
          fixedSize: Size(largura, altura),
          shape: RoundedRectangleBorder(
              borderRadius: BorderRadius.circular(raio_borda)),
        ),
      )
    ]);
  }
}

class touch1 extends StatefulWidget {
  @override
  State<touch1> createState() => _touch1State();
}

class _touch1State extends State<touch1> {
  Color cor_botao = Colors.red;
  @override
  Widget build(BuildContext context) {
    return Column(
      children: [
        Text(
          "Habilitar Touch 1",
          style: TextStyle(
            fontSize: 16,
            fontWeight: FontWeight.bold,
          ),
        ),
        Padding(padding: EdgeInsets.all(5)),
        TextButton(
          onPressed: () {
            if (cor_botao == Colors.red) {
              cor_botao = Colors.green;
              print('Touch 1 Habilitato');
            } else {
              cor_botao = Colors.red;
              print('Touch 1 Desabilitado');
            }
            setState(() {});
          },
          child: Icon(Icons.fingerprint, size: tamanho_icone),
          style: TextButton.styleFrom(
            primary: Colors.white,
            backgroundColor: cor_botao,
            fixedSize: Size(largura, altura),
            shape: RoundedRectangleBorder(
                borderRadius: BorderRadius.circular(raio_borda)),
          ),
        ),
      ],
    );
  }
}

class touch2 extends StatefulWidget {
  @override
  State<touch2> createState() => _touch2State();
}

class _touch2State extends State<touch2> {
  Color cor_botao = Colors.red;
  @override
  Widget build(BuildContext context) {
    return Column(
      children: [
        Text(
          "Habilitar Touch 2",
          style: TextStyle(
            fontSize: 16,
            fontWeight: FontWeight.bold,
          ),
        ),
        Padding(padding: EdgeInsets.all(5)),
        TextButton(
          onPressed: () {
            if (cor_botao == Colors.red) {
              cor_botao = Colors.green;
              print('Touch 2 Habilitato');
            } else {
              cor_botao = Colors.red;
              print('Touch 2 Desabilitado');
            }
            setState(() {});
          },
          child: Icon(Icons.fingerprint, size: tamanho_icone),
          style: TextButton.styleFrom(
            primary: Colors.white,
            backgroundColor: cor_botao,
            fixedSize: Size(largura, altura),
            shape: RoundedRectangleBorder(
                borderRadius: BorderRadius.circular(raio_borda)),
          ),
        ),
      ],
    );
  }
}
