/* FILE:    RC522_RFID_Module_Example
   DATE:    13/07/2016
   VERSION: 0.1
    
Autore Fancello Salvatore

PINOUT:
RC522 MODULE    Uno/Nano    
SDA             D10
SCK             D13
MOSI            D11
MISO            D12
IRQ             N/A
GND             GND
RST             D9
3.3V            3.3V

*/
 
#include <SPI.h>
#include <RFID.h>
/* Vengono definiti PIN del RFID reader*/
#define SDA_DIO 10  // 53 per Arduino Mega
#define RESET_DIO 9
#define delayRead 1000 // Time of delay 
 
#define BUZZER_PIN 3 //Pin generico
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784
#define NOTE_A5  880
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_LA 440

/* Viene creata una istanza della RFID libreria */
RFID RC522(SDA_DIO, RESET_DIO); 
 
 
 
void setup()
{ 
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  /* Abilita SPI*/
  SPI.begin(); 
  /* Viene inizilizzato RFID reader */
  RC522.init();
  Serial.println("Setup");
}
 
void loop()
{
  /* Temporary loop counter */
  byte i;
   
  // Se viene letta una tessera
  if (RC522.isCard())
  {
    // Viene letto il suo codice 
    delay(300);
    RC522.readCardSerial();
    //Serial.println(RC522.readCardSerial());

    String codiceLetto ="";
    Serial.println("Codice delle tessera letto:");
     
    // Viene caricato il codice della tessera, all'interno di una Stringa
    for(i = 0; i <= 4; i++)
    {
      codiceLetto+= String (RC522.serNum[i],HEX);
      codiceLetto.toUpperCase();
    }
    Serial.println(codiceLetto);
   tone(BUZZER_PIN,NOTE_A5 , 300);
    delay(delayRead);
    Serial.println();
    Serial.println();
  }
}
