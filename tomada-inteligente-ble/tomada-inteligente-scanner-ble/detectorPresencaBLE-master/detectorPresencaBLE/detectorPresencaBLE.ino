/*
   Detector de presena utilizando a tecnologia de Bluetooth Low Energy
   Microcontrolador utilizado: ESP32
*/

// --- Bluetooth ---
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
int scanTime = 5; //Em Segundos
int nivelRSSI = -100; //Ajustar conforme o ambiente!
String dispositivosAutorizados = "d8:80:3c:21:6f:80";
bool dispositivoPresente = false;
unsigned long ultimoTempoMedido = 0;
const long intervaloPublicacao = 20000; //Ajustar o tempo de desligamento


// --- Setup ---
void setup() {
  Serial.begin(115200);
  Serial.println("Scanning...");
  BLEDevice::init("ScanerBLE");

}

// --- Loop ---
void loop() {
  scanBLE();
  publicarStatusnoTopico();
  delay(2000);
}

// -- Funções Auxiliares ---
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      String dispositivosEncontrados = advertisedDevice.getAddress().toString().c_str();
      if ( dispositivosEncontrados == dispositivosAutorizados  && advertisedDevice.getRSSI() > nivelRSSI) {
        Serial.println("Identificador DETECTADO!");
        Serial.print("RSSI: ");
        Serial.println(advertisedDevice.getRSSI());
        dispositivoPresente = true;
        ultimoTempoMedido = millis();
      }
      else{
        dispositivoPresente = false;
      }
    }
};

// --- Scan Bluetooth LE ---
void scanBLE(){
  BLEScan* pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  BLEScanResults foundDevices = pBLEScan->start(scanTime);
}


void publicarStatusnoTopico(){
  if(dispositivoPresente == 1){
    Serial.println("Power ON");
  }
  else {
    if (millis() - ultimoTempoMedido > intervaloPublicacao) {
      Serial.println("Power OFF");
    }
  }
}
