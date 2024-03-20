#include <WiFiNINA.h>
#include "ICMPPing.h"
char ssid[] = "ITIS Wifi";     // SSID della rete WiFi
char password[] = "wifiitis2023"; // Password della rete WiFi

int port = 9559;                   // Porta da controllare

WiFiClient client;
//SOCKET pingSocket = 0;
//ICMPEchoReply echoReply ; 
//ICMPPing ping(pingSocket, (uint16_t)random(0, 255));
//byte basenetwork[] = {192,168,0,1};
//byte ip[] = {192,168,137,1};


void setup() {
  Serial.begin(9600);
  Serial.println("INZIO");
  while (!Serial);

  // Connessione alla rete WiFi
  Serial.print("Connessione a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connessione in corso...");
  }
  
  Serial.println("Connesso alla rete WiFi");
}

void loop() {
  Serial.println("Inizio scansione della rete...");
  IPAddress ip;

  uint8_t mac[6];
  if (WiFi.status() == WL_CONNECTED) {
    ip = WiFi.localIP();
    Serial.println(ip);
    ip[3] = 1; // Imposta il suffisso dell'indirizzo IP del gateway su 1 (tipico per una subnet /24)
  
  client.setTimeout(500);
  while (ip[3] < 255) {
  //echoReply=ping(ip, 2);  // ping test
//client.connect(serverIP, portNumber, 2000);
      Serial.print("connect IP: ");
      Serial.print(ip);
     if (client) {
    client.setTimeout(555);  // set the timeout duration for client.connect() and client.stop()
  }
  WiFi.setTimeout(100);
  if (WiFi.ping(ip)>0) {
    Serial.println(" PING OK");
        if(client.connect(ip, port)) {
        Serial.print("****** TROVATO! ***** IP NAO: ");
        Serial.println(ip);
        client.stop();
        break;
      }
    }
    else Serial.println(" PING NOT OK");
      ip[3]++;
    }
  }
  Serial.println("Fine scansione della rete.");
  delay(60000); // Scansiona la rete ogni 60 secondi
}