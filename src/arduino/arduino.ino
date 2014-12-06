#include <SoftwareSerial.h>

const int baudRate = 9600; //Vitesse

//Parking
uint8_t placesDisponibles = 0;

//Bluetooth
#define Bt_Rx 6
#define Bt_Tx 7
#define DEBUG_ENABLED 1
char BtRecvChar = '0';
SoftwareSerial Bt(Bt_Rx, Bt_Tx); 

void setup()
{
  
  //Bluetooth
  setupBlueToothConnection();
  pinMode(Bt_Rx, INPUT);
  pinMode(Bt_Tx, OUTPUT);
}

void loop()
{
  if (Bt.available())
  {
    BtRecvChar = Bt.read();
    
    if (BtRecvChar = 'a')
    {
      Bt.print('a');
      Bt.print(placesDisponibles);
    }
  }
}

void setupBlueToothConnection() 
{ 
  Bt.begin(38400);                       // vitesse comm bluetooth 38400 bauds
  Bt.print( "\r\n+STWMOD=0\r\n" );       // mode esclave 
  Bt.print( "\r\n+STNA=ARDUINO_parkingX\r\n" ); // nom du shield
  Bt.print("\r\n+STPIN=0000\r\n");       // pincode"0000"
  Bt.print( "\r\n+STOAUT=1\r\n" );       // appareil appairé autorisé à se connecter 
  Bt.print( "\r\n+STAUTO=0\r\n" );       // Auto-connection interdite 
  delay(2000);                           // This delay is required. 
  Bt.print( "\r\n+INQ=1\r\n" );          // esclave en attente 
  Serial.println( "Le module Bluetooth est prêt à recevoir !" ); 
  delay(2000);                           // This delay is required. 
  Bt.flush();                            // vider le tampon
} 
