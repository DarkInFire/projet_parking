#include <SoftwareSerial.h>   //Software Serial Port
#include "utilisateur.h"
#include <stdio.h>

#define DEBUG_ENABLED  1
#define RxD 6
#define TxD 7

SoftwareSerial bluetoothSerial(RxD,TxD);

unsigned long lastTimerHit;

const int baudRate = 9600;

bool correctPacket = false;

const int BUFFER_LIMIT = 4;

byte nbrPlacesDispo;

//Variables nécessaires à la communication Android;
byte androidToken;
bool androidConnected = true;
byte transmissionBytes[4];

//liste des messages du protocole de communication
enum COMMANDS {
  cmd_getNbrPlacesDispo = 1,
};

enum MESSAGES {
  msg_NbrPlacesDispo = 1,
};

//Enumération du packet reçu
enum PACKET_DETAILS{
  CMD = 0,
  TOKEN,
  DATA_1,
  DATA_2,
};

struct
{
  byte data[BUFFER_LIMIT]; //Données reçues
  byte curLoc; //compteur
} 
dataPacket; 

void setup() 
{ 
  Serial.begin(baudRate);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  setupBluetoothConnection();

  lastTimerHit = 0;
  dataPacket.curLoc = 0;

  nbrPlacesDispo = 5;

  androidToken = B10010;
} 

void loop() 
{
  if(bluetoothSerial.available() > 0)
  {
    Serial.println("Bluetooth Data available");
    checkAndroidCommand();
  }
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

    switch ( dataPacket.data[CMD] )
    {
    case cmd_getNbrPlacesDispo:
      sendMessage(msg_NbrPlacesDispo, nbrPlacesDispo, 200);

      break;

    default:
      //Si la commande est incorrecte
      correctPacket = false;
      dataPacket.curLoc = 0;
      Serial.println("invalid cmd");
      break;
    }

    if (correctPacket == true )
    {
      Serial.print("Paquet OK\n");
      correctPacket = false;
    }
  }
}

void sendMessage(const uint8_t messageId, const uint8_t message1, const uint8_t message2)
{
  if (!androidConnected)
    return;
  uint8_t buf[] = {messageId,androidToken,message1,message2};
  Serial.println("---ENVOI D'UN MESSAGE");
  Serial.print("ID Message: ");
  Serial.println(messageId);
  Serial.print("Token: ");
  Serial.println(androidToken);
  Serial.print("Message1: ");
  Serial.println(message1);
  Serial.print("Message2: ");
  Serial.println(message2);
  
  bluetoothSerial.write(buf[0]);
  bluetoothSerial.write(buf[1]);
  bluetoothSerial.write(buf[2]);
  bluetoothSerial.write(buf[3]);
}

void setupBluetoothConnection()
{
  bluetoothSerial.begin(38400); //Set BluetoothBee BaudRate to default baud rate 38400
  bluetoothSerial.print("\r\n+STWMOD=0\r\n"); //set the bluetooth work in slave mode
  bluetoothSerial.print("\r\n+STNA=arduino_parking\r\n"); //set the bluetooth name as "SeeedBTSlave"
  bluetoothSerial.print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
  bluetoothSerial.print("\r\n+STAUTO=0\r\n"); // Auto-connection should be forbidden here
  delay(2000); // This delay is required.
  bluetoothSerial.print("\r\n+INQ=1\r\n"); //make the slave bluetooth inquirable 
  Serial.println("bluetooth ok ");
  delay(2000); // This delay is required.
  bluetoothSerial.flush();
}
