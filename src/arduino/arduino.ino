#include <SoftwareSerial.h>   //Software Serial Port
#define RxD 6
#define TxD 7
 
#define DEBUG_ENABLED  1

//Enumération des commandes recevables
enum COMMANDS {
  cmd_getNbrPlacesDispo = 0
};

enum MESSAGES {
  msg_NbrPlacesDispo = 0
};

const int BUFFER_LIMIT = 4; // Buffer de 4 octets (1 cmd, 3 data)

//Enumération du packet reçu
enum PACKET_DETAILS{
  CMD = 0,
  BYTE_1,
  BYTE_2,
  BYTE_3
};

struct
{
  byte data[BUFFER_LIMIT]; //Données reçues
  byte curLoc; //compteur
} dataPacket; 

unsigned long lastTimerHit;

const int baudRate = 9600;
 
SoftwareSerial bluetoothSerial(RxD,TxD);

bool correctPacket = false;

uint8_t nbrPlacesDispo;

char Message[32] = 

void setup() 
{ 
  Serial.begin(baudRate);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  setupBluetoothConnection();
  
  lastTimerHit = 0;
  dataPacket.curLoc = 0;
  
  nbrPlacesDispo = 5;
} 
 
void loop() 
{ 
  if(bluetoothSerial.available() > 0)
  {
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
    
    switch ( dataPacket.data[CMD] )
    {
      case cmd_getNbrPlacesDispo:
        sendMessage(msg_NbrPlacesDispo, nbrPlacesDispo);
        Serial.println();
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
      Serial.print("z\n");
      correctPacket = false;
    }
  }
}

void sendMessage(const uint8_t messageId, const uint32_t message)
{
  Message = String(messageId);
  bluetoothSerial.print(msgId);
  Serial.print(msgId);
  
  String msg;
  msgId = String(message);
  bluetoothSerial.print(msg);
  Serial.print(message);
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
