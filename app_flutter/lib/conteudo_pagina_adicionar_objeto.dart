import 'package:flutter/material.dart';

class conteudoPaginaAdicionarObjeto extends StatelessWidget {
  const conteudoPaginaAdicionarObjeto({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    const double cardElevation = 3.0;
    const double tileElevation = 3.0;

    return Center(
      child: Container(
        child: Column(
          children: [
            Padding(padding: EdgeInsets.all(30)),
            Text(
              'Adicione um Objeto',
              style: TextStyle(
                fontSize: 36,
                fontWeight: FontWeight.bold,
              ),
            ),
            Padding(padding: EdgeInsets.all(10)),
            Ink(
              decoration: const ShapeDecoration(
                color: Colors.lightBlue,
                shape: CircleBorder(),
              ),
              child: IconButton(
                icon: const Icon(Icons.wifi),
                color: Colors.white,
                iconSize: 30,
                onPressed: () {},
              ),
            ),
            Padding(padding: EdgeInsets.all(10)),
            Padding(
              padding: EdgeInsets.only(left: 30, right: 30),
              child: Text(
                "Encontre objetos com o Wifi para integrá-los a casa inteligente e configurá-los de acordo com o seu desejo",
                style: TextStyle(),
                textAlign: TextAlign.center,
              ),
            ),
            Padding(padding: EdgeInsets.all(5)),
            Card(
              margin: EdgeInsets.only(left: 30, right: 30),
              elevation: cardElevation,
              child: Column(
                children: [
                  Padding(padding: EdgeInsets.all(5)),
                  Card(
                    margin: EdgeInsets.all(5),
                    elevation: tileElevation,
                    child: ListTile(
                      leading: Icon(
                        Icons.lightbulb_circle,
                        size: 40,
                        color: Colors.blue.shade500,
                      ),
                      title: Text(
                        "Lampada",
                        style: TextStyle(fontWeight: FontWeight.bold),
                      ),
                      subtitle: Text("a617bc737b"),
                      onTap: () {},
                    ),
                  ),
                  Card(
                    margin: EdgeInsets.all(5),
                    elevation: tileElevation,
                    child: ListTile(
                      leading: Icon(
                        Icons.touch_app,
                        size: 40,
                        color: Colors.blue.shade500,
                      ),
                      title: Text(
                        "Interruptor",
                        style: TextStyle(fontWeight: FontWeight.bold),
                      ),
                      subtitle: Text("a3715d735"),
                      onTap: () {},
                    ),
                  ),
                  Card(
                    margin: EdgeInsets.all(5),
                    elevation: tileElevation,
                    child: ListTile(
                      leading: Icon(
                        Icons.outlet,
                        size: 40,
                        color: Colors.blue.shade500,
                      ),
                      title: Text(
                        "Tomada",
                        style: TextStyle(fontWeight: FontWeight.bold),
                      ),
                      subtitle: Text("e21d73e5"),
                      onTap: () {},
                    ),
                  ),
                  Card(
                    margin: EdgeInsets.all(5),
                    elevation: tileElevation,
                    child: ListTile(
                      leading: Icon(
                        Icons.lightbulb_circle,
                        size: 40,
                        color: Colors.blue.shade500,
                      ),
                      title: Text(
                        "Lampada",
                        style: TextStyle(fontWeight: FontWeight.bold),
                      ),
                      subtitle: Text("a37bd71c4"),
                      onTap: () {},
                    ),
                  ),
                  Padding(padding: EdgeInsets.all(5)),
                ],
              ),
            )
          ],
        ),
      ),
    );
  }
}
