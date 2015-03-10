#ifndef COMMUNICATIONANDROID
#define COMMUNICATIONANDROID

#include <stdint.h>

unsigned long lastTimerHit;
bool correctPacket;
const int BUFFER_LIMIT = 4;

//Variables nécessaires à la communication Android;
uint8_t androidToken;
bool androidConnected;
uint8_t transmissionBytes[4];

namespace Android
{
  typedef unsigned char uint8_t; 
  
  //liste des messages du protocole de communication
  enum COMMANDS {
    cmd_getNbrPlacesDispo = 1,
    cmd_carParkedOnPosition,
    cmd_getEtatParking,
  };

  enum MESSAGES {
    msg_NbrPlacesDispo = 1,
    msg_carParkedOnPosition,
    msg_etatParking,
  };

  //liste des infos d'un paquet
  enum PACKET_DETAILS{
    CMD = 0,
    TOKEN,
    DATA_1,
    DATA_2,
  };
  
  struct
  {
    uint8_t data[BUFFER_LIMIT]; //Données reçues
    uint8_t curLoc; //compteur
  } dataPacket;

  static void handleCommand(const uint8_t cmd, const uint8_t data1 = 0, const uint8_t data2 = 0);
  static void setupBluetoothConnection();

  static void sendMessage(const uint8_t messageId, const uint8_t message1 = 0, const uint8_t message2 = 0);
};
#endif