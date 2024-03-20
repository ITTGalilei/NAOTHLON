#include <WiFiNINA.h>
#include "ICMPPing.h"
char ssid[] = "ITIS Wifi";     // SSID della rete WiFi
char password[] = "wifiitis2023"; // Password della rete WiFi
int port = 9559;

#include <SPI.h>
#include <RFID.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h" 

#define SDA_DIO 10
#define RESET_DIO 9
#define delayRead 1000
#define LED_ON_DURATION 1000 // 3 secondi
#define BUZZER_PIN 3
#define LED_PIN_1 5
#define LED_PIN_2 6
#define NAOPORT 7071
#define NOTE_A5 880
#define NOTE_A6 300








RFID RC522(SDA_DIO, RESET_DIO);

unsigned long previousMillis = 0;
unsigned long currentMillis = 0;

//char server[] = "192.168.2.5";    // name address for Google (using DNS)
String nome=" Alessandro";

WiFiClient client;
int status = WL_IDLE_STATUS;

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
  
  
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  
  SPI.begin();
  RC522.init();
  Serial.println("Setup");

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }


  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
  
  Serial.println("Connected to WiFi");
  printWifiStatus();

  Serial.println("\nStarting connection to server...");
  
}

void loop() {
  currentMillis = millis();
  byte i;
  if (RC522.isCard())
  {
    delay(300);
    RC522.readCardSerial();
    String codiceLetto = "";
    for (i = 0; i < 5; i++)
    {
      codiceLetto += String(RC522.serNum[i], HEX);
    }
    codiceLetto.toUpperCase();

    Serial.println("Codice della tessera letto:");
    Serial.println(codiceLetto);

    if (codiceLetto == "D326617A0"){nome="Hello, Alessandro.";
    tone(BUZZER_PIN, NOTE_A5, 300);
    invioDati();
  
    }
  
    else
     if (codiceLetto == "AC77E92B19")   {nome="Hello, Mario.";
     tone(BUZZER_PIN, NOTE_A5, 300);
     invioDati();}
     else 
     {
      tone(BUZZER_PIN, NOTE_A6, 600);
      digitalWrite(LED_PIN_1, LOW);
      digitalWrite(LED_PIN_2, HIGH);
      Serial.println("Cliente non riconosciuto");
       delay(500);
       digitalWrite(LED_PIN_2, LOW);
     }

    
    delay(delayRead);
    Serial.println();
    Serial.println();
  }

  // Spegni i LED dopo 3 secondi
 /* if (currentMillis - previousMillis >= LED_ON_DURATION)
  {
    digitalWrite(LED_PIN_1, LOW);
    digitalWrite(LED_PIN_2, LOW);
  }

/*
  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();
    Serial.println("Disconnected from server.");
    return; // Exiting loop() to disconnect from server and wait for card scan
  }
}*/



}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void invioDati() {
   
      digitalWrite(LED_PIN_1, HIGH);
      digitalWrite(LED_PIN_2, LOW);
      previousMillis = currentMillis;

      Serial.println("mi sto per connettere ");
      // if you get a connection, report back via serial:
      delay(1000);
      digitalWrite(LED_PIN_1, LOW);
      if (client.connect(server, NAOPORT)) {
        Serial.println("connected to server");

        client.println(nome);
        client.println();

        Serial.println();
        Serial.println("disconnecting from server.");

        client.stop();
      }

Serial.println("fine trasmissione ");
}
