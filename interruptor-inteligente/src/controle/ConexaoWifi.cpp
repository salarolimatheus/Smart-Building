#include "ConexaoWifi.hpp"
#include "../../chaves/Wifi-keys.h"

void ConfiguraWifi () {
    delay(10);

    DBG_PRINTLN()
    DBG_PRINT("[Wifi] Conectando a rede: ")
    DBG_PRINTLN(ssid)

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        DBG_PRINT(".")
    }

    DBG_PRINTLN()
    DBG_PRINTLN("[Wifi] Contectado!")
    DBG_PRINT("[Wifi] Endereco IP: ")
    DBG_PRINTLN(WiFi.localIP())
}
