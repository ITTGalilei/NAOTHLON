#include <SPI.h>
#include <RFID.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h" 

#define SDA_DIO 10
#define RESET_DIO 9
#define delayRead 1000
#define LED_ON_DURATION 3000          //3 secondi
#define BUZZER_PIN 3
#define LED_PIN_1 5
#define LED_PIN_2 6
#define NAOPORT 8080
#define NOTE_A5 880

RFID RC522(SDA_DIO, RESET_DIO);

unsigned long previousMillis = 0;
unsigned long currentMillis = 0;

char ssid[] = SECRET_SSID;                 // your network SSID (name)
char pass[] = SECRET_PASS;                // your network password (use for WPA, or use as key for WEP)
char server[] = "192.168.1.34";   
String nome=" Alessandro";
String codiceLetto = "";
WiFiClient client;
int status = WL_IDLE_STATUS;

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  
  SPI.begin();
  RC522.init();
  delay(2000);
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
    
  }
  
  Serial.println("Connected to WiFi");
  printWifiStatus();

  Serial.println("\nStarting connection to server...");
  
}

void loop() {
  currentMillis = millis();
  byte i;
  codiceLetto = "";
  if (RC522.isCard())
  {
    delay(300);
    RC522.readCardSerial();
    
    for (i = 0; i < 5; i++)
    {
      codiceLetto += String(RC522.serNum[i], HEX);
    }
    codiceLetto.toUpperCase();
    
    Serial.println("Codice della tessera letto:");
    Serial.println(codiceLetto);
    tone(BUZZER_PIN, NOTE_A5, 300);
    digitalWrite(LED_PIN_1, HIGH);
    digitalWrite(LED_PIN_2, LOW);
    delay(3000);
    digitalWrite(LED_PIN_1, LOW);

    if (codiceLetto == "D326617A0")     {nome="Hello, Valentino.";invioDati();}     //alessandro
  
    else
     if (codiceLetto == "AC77E92B19")   {nome="Hello, Franco.";invioDati();}   //mario
     else 
     {
      digitalWrite(LED_PIN_1, LOW);
      digitalWrite(LED_PIN_2, HIGH);
      delay(3000);
      digitalWrite(LED_PIN_2, LOW);
     }
    delay(delayRead);
    Serial.println();
    

  }
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
   
      previousMillis = currentMillis;
      Serial.println("mi sto per connettere ");
      // if you get a connection, report back via serial:
      if (client.connect(server, NAOPORT)) {
        Serial.println("connected to server");

        client.println(codiceLetto);
        client.println();

        Serial.println();
        Serial.println("disconnecting from server.");

        client.stop();
      }


}
