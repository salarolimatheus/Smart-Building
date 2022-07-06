#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLECharacteristic *Dados; //declaração das caracteristicas do BLE
BLECharacteristic *Add; 
bool deviceConnected = false;//estado do dispositivo 
float txValue = 0;
float Alt = 0;

// criação dos serviços e caracteristicas do ble
#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E" //UUID das caracteristicas usadas
#define CHARACTERISTIC_UUID_RX1 "6E400005-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX1 "6E400004-B5A3-F393-E0A9-E50E24DCCA9E"
#define ONBOARD_LED  27

// callback para alterar o estado do dispositivo para conectado
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {//caso o dispositivos esteja ligado seta a variavel booleana para 1
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {//caso o dispositivos esteja desligado seta a variavel booleana para 0
      deviceConnected = false;
    }
};

//callback para recebimento de dados
class MyCallbacks1: public BLECharacteristicCallbacks {
    void onWrite (BLECharacteristic*Dados){
      std::string rxValue=Dados->getValue();//pegamos dos dados recebidos com o getvalue e transferimos para uma string
      if (rxValue.length()>0){//caso o comprimento do dado recebido seja maior que zero estaremos considerando que o sinal foi recebido com sucesso
        Serial.println("===Start Receive===");
        Serial.print("Received Value: ");
        for (int i=0 ; i<rxValue.length();i++) {//e devemos escrever o sinal um caracter por vez
          Serial.print(rxValue[i]);
        }
        Serial.println (" ");
        Serial.println("====End====");
      }
    }
};

//callback para recebimento de dados
class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite (BLECharacteristic*Add){
      std::string rxValue=Add->getValue();
       if ((rxValue.length())==1){//nesse caso o aplicativo envia o caracter 1 ou 0 para o acionamento do LED, desse modo consideramos o comprimento da variavel de apenas 1
        if(rxValue[0]=='1'){
           digitalWrite(ONBOARD_LED,HIGH);
        }
        if (rxValue[0]=='0'){
           digitalWrite(ONBOARD_LED,LOW);
        }
      }
    }
};

// definir pinos usados nos sensores
const int trigPin = 4;
const int echoPin = 5;

// definir variáveis
long duration;
int distance;

void setup() {
pinMode(ONBOARD_LED,OUTPUT);
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input  
  Serial.begin(115200);

// Create the BLE Device
  BLEDevice::init("ESP32 BLE"); // Give it a name

// Create the BLE Server
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

// Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

// Create a BLE Characteristic
  Dados = pService->createCharacteristic(
                      CHARACTERISTIC_UUID_TX,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_NOTIFY
                    );

  Dados->addDescriptor(new BLE2902());

  Add = pService->createCharacteristic(
                      CHARACTERISTIC_UUID_TX1,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_NOTIFY
                    );

  Add->addDescriptor(new BLE2902());
  
// Create a BLE Characteristic
  BLECharacteristic*Dados = pService->createCharacteristic(
                      CHARACTERISTIC_UUID_RX,
                      BLECharacteristic::PROPERTY_WRITE
                    );
                      
 Dados->setCallbacks (new MyCallbacks1());

 BLECharacteristic*Add = pService->createCharacteristic(
                      CHARACTERISTIC_UUID_RX1,
                      BLECharacteristic::PROPERTY_WRITE
                    );
                      
 Add->setCallbacks (new MyCallbacks());
      
// Start the service
  pService->start();

// Start advertising
  pServer->getAdvertising()->start();
  Serial.println("Waiting a client connection to notify...");
}

void loop() {
  if (deviceConnected) { 
// informação transferida
digitalWrite(trigPin, LOW);
delayMicroseconds(5);

// Pulso no pino Trigger
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Leitura do pino ECHO
duration = pulseIn(echoPin, HIGH);

// Calcular distancia
distance= duration*0.034/2;

//imprimir distancia no monitor serial e no serialBT
    txValue = distance;
   
//coverter para array
    char txString[8]; // make sure this is big enuffz
    dtostrf(txValue, 1, 2, txString); // float_val, min_width, digits_after_decimal, char_buffer
    Dados->setValue(txString);

//não existe necessidade de callback para enviar arquivo
    Dados->notify(); // Send the value to the app!
    Serial.print("*** Sent Value: ");
    Serial.print(txString);
    Serial.println(" ***");

// informação transferida
    Alt = random(-10,20);
//coverter para array
    char txAlt[8]; // make sure this is big enuffz
    dtostrf(Alt, 1, 2, txAlt); // float_val, min_width, digits_after_decimal, char_buffer
    Add->setValue(txAlt);

//não existe necessidade de callback para enviar arquivo
    Add->notify(); // Send the value to the app!
    Serial.print("*** Sent Value: ");
    Serial.print(txAlt);
    Serial.println(" ***");
  }
  delay(1000);
}
