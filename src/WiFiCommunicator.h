//Definiere die Bibliothek
#ifndef WifiCommunicator_h
#define WifiCommunicator_h

//Einbinden der benötigten Bibliotheken
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <string>

//Definierung der Klasse und deren Objekte
class WiFiCommunicator
{
public: //Das hier kann man in der Arduino IDE aufrufen
	WiFiCommunicator(int sendPin, int rcvPin, IPAddress address);
	String receive();
	void send(String message);
	void begin();
private: //Das kann man nur in der Klasse aufrufen
	int _sendPort;
	int _rcvPort;
	WiFiUDP udp;
	char _incomingPacket[255];
	int _len;
	IPAddress _address;
};

#endif