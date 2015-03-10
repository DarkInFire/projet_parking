#include <SoftwareSerial.h>   //Software Serial Port
#include <stdio.h>
#include <stdint.h>
#include "utilisateur.h"
#include "communicationandroid.h"

#define DEBUG_ENABLED  1
#define RxD 6
#define TxD 7

using namespace Android;

SoftwareSerial bluetoothSerial(RxD,TxD);

uint8_t nbrPlacesDispo;

int tableauEmplacements[23];

uint8_t etatParking;

const int baudRate = 9600;

int i;

void setup() 
{ 
  Serial.begin(baudRate);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  Android::setupBluetoothConnection();

  lastTimerHit = 0;
  dataPacket.curLoc = 0;

  nbrPlacesDispo = 5;

  androidToken = B10010;
  
  etatParking = 0;
  
  dataPacket.data[CMD] = 0;
  dataPacket.data[DATA_1] = 0;
  dataPacket.data[DATA_2] = 0;
  
  for(i=0;i<23;i++)
  {
	tableauEmplacements[i] = 0;
  }
} 

void loop() 
{
  if(bluetoothSerial.available() > 3)
  {
    Serial.println("Bluetooth Data available");
    checkAndroidCommand();
  }
  
  nbrPlacesDispo = random(1, 42);
}

void checkAndroidCommand()
{
  /* Si plus de 500 ms entre la réception de bytes, réception annulée */
  if ( (lastTimerHit + 500) < millis() )
  {
    dataPacket.curLoc = 0;
    correctPacket = false;
    Serial.println("Timeout");
  }

  lastTimerHit = millis(); //MaJ du timer de timeout

  dataPacket.data[dataPacket.curLoc] = bluetoothSerial.read();

  dataPacket.curLoc++; // Incrémentation du compteur

  if ( dataPacket.curLoc == BUFFER_LIMIT )
  { 
    correctPacket = true;
    dataPacket.curLoc = 0;

    Serial.println("---RECEPTION d'UNE COMMANDE");
    Serial.print("ID commande: ");
    Serial.println(dataPacket.data[CMD]);
    Serial.print("Token: ");
    Serial.println(dataPacket.data[TOKEN]);
    Serial.print("Message1: ");
    Serial.println(dataPacket.data[DATA_1]);
    Serial.print("Message2: ");
    Serial.println(dataPacket.data[DATA_2]);

    Android::handleCommand(dataPacket.data[CMD], dataPacket.data[DATA_1], dataPacket.data[DATA_2]);

    if (correctPacket == true )
    {
      Serial.print("Paquet OK\n");
      correctPacket = false;
    }
  }
}