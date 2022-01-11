//Importieren der Bibliotheken
#include <WiFiCommunicator.h>
#include <ESP8266WiFi.h>

//IP Adresse des "Ziels"
IPAddress addr(192, 168, 20, 28);

//Instanziieren des Objekts, die beiden Zahlen repräsentieren die Ports, auf denen gesendet wird.
WiFiCommunicator com(49001, 49000, addr);

//WiFi Login-Daten
#ifndef STASSID
#define STASSID "PowerLine-Unitymedia"
#define STAPSK  "Alleswirdgut1"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

void setup() {

  //Starten des seriellen Monitors
  Serial.begin(9600);
  Serial.print("Verbinde zu Netzwerk: "); Serial.println(ssid);

  //Wlan Modul explizit in den Client-Modus setzen
  WiFi.mode(WIFI_STA);

  //Verbindungsversuch
  WiFi.begin(ssid, password);

  //Warten, bis eine Verbindung aufgebaut wurde
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //Anzeigen der WiFi-Infos im seriellen Monitor
  Serial.println("");
  Serial.println("Verbunden!");
  Serial.println("IP Adresse: ");
  Serial.println(WiFi.localIP());
  
  //Starte den UDP Listener
  com.begin();
}

void loop() {
  //Lese UDP aus
  String response = com.receive();

  //Wenn eine Nachricht empfangen wird, wird diese im seriellen Monitor angezeigt, außerdem wird die selbe Nachricht zurückgesendet
  if (response != "") {
    Serial.println("Paket erhalten: " + response);
    Serial.println("Sende Paket: " + response);
    com.send(response);
  }

}
