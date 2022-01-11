#include "Arduino.h"
#include "WifiCommunicator.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <string>

//Instanziierung und Bildung eines Objektes
WiFiCommunicator::WiFiCommunicator(int sendPort, int rcvPort, IPAddress address)
{
	_sendPort = sendPort;	//Port auf dem wir senden
	_rcvPort = rcvPort;		//Port auf dem wir empfangen
	_address = address;

}

void WiFiCommunicator::begin() {
	udp.begin(_rcvPort);
}

String WiFiCommunicator::receive() {
	int _packetSize = udp.parsePacket(); //Ermittle Packet-Größe (falls vorhanden)
	if (_packetSize)
	{
		// Wenn ein Paket vorhanden ist, wird dieses Ausgelesen
		_len = udp.read(_incomingPacket, 255);

		//Bildung eines Char-Arrays aus den einzelnen bytes
		_incomingPacket[_len] = 0; 

		//Umwandlung des Char Arrays in ein String
		String packet(_incomingPacket);

		//Rückgabe des Strings
		return packet;
	}

	//Leeren String zurückgeben, wenn kein Paket vorhanden
	return "";

}

void WiFiCommunicator::send(String message) {

	//Überprüfen, ob überhaupt eine Nachricht vorhanden ist

		udp.beginPacket(_address, _sendPort);	//UDP Packet "beginnen" hier werden dem Paket noch Empfänger und port mitgeteilt
		udp.write(message.c_str());					//Schreiben desStrings als Char-Array in das Paket
		udp.endPacket();						//Beenden und Sendes des Paket

}