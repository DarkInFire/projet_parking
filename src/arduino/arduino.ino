#include <SoftwareSerial.h>

/* --- Communication Android --- */
uint8_t androidToken;
bool androidConnected;
uint8_t transmissionBytes[5];

unsigned long lastTimerHit;
bool correctPacket;
const int BUFFER_LIMIT = 4;

const int baudRate = 9600;
#define DEBUG_ENABLED 1
#define RxD 6
#define TxD 7

int i;

SoftwareSerial bluetoothSerial(RxD, TxD);

void updateNbrePlaces();
void sendMessage(const uint8_t messageId, const uint8_t message1 = 0, const uint8_t message2 = 0);
void handleCommand(const uint8_t cmd, const uint8_t data1 = 0, const uint8_t data2 = 0);

/*
Ajout/retrait d'une voiture

sendMessage(msg_carParkedOnPosition, AndroidToken, !!numero de la place dans une variable!!, tableaudesempalcementsdalois[numerodelaplace]);
*/

//liste des messages du protocole de communication
enum COMMANDS {
  cmd_getNbrPlacesDispo = 1,
  cmd_carParkedOnPosition,
  cmd_getEtatParking,
  cmd_invalidMsg,
};

enum MESSAGES {
  msg_NbrPlacesDispo = 1,
  msg_carParkedOnPosition,
  msg_etatParking,
  msg_resend,
};

//liste des infos d'un paquet
enum PACKET_DETAILS {
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

void setup()
{

  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  setupBluetoothConnection();

  dataPacket.data[CMD] = 0;
  dataPacket.data[DATA_1] = 0;
  dataPacket.data[DATA_2] = 0;
  androidToken = 18;
  lastTimerHit = 0;
  dataPacket.curLoc = 0;
  androidConnected = false;


  Serial.print("initialisé");
}

/* ------------ GESTION ANDROID ----------------- */
void sendMessage(const uint8_t messageId, const uint8_t message1, const uint8_t message2)
{
  Serial.println("sendMessage");

  if (messageId == msg_resend)
  {
    bluetoothSerial.write(transmissionBytes, 5);
    bluetoothSerial.flush();
    return;
  }

  transmissionBytes[0] = 255;
  transmissionBytes[1] = messageId;
  transmissionBytes[2] = androidToken;
  transmissionBytes[3] = message1;
  transmissionBytes[4] = message2;

  Serial.print(255);
  Serial.print(messageId);
  Serial.print(androidToken);
  Serial.print(message1);
  Serial.println(message2);

  bluetoothSerial.write(transmissionBytes, 5);
  bluetoothSerial.flush();
}

void handleCommand(const uint8_t cmd, const uint8_t data1, const uint8_t data2)
{
  Serial.println("handleCommand");
  switch ( cmd )
  {
    case cmd_getNbrPlacesDispo:
      sendMessage(msg_NbrPlacesDispo, nbrPlacesDispo, 0);
      break;
    case cmd_carParkedOnPosition:
      sendMessage(msg_carParkedOnPosition, data1, tableauEmplacements[data1]);
      break;

    case cmd_getEtatParking:
      sendMessage(msg_etatParking, etatParking);
      break;

    case cmd_invalidMsg:
      sendMessage(msg_resend);
      break;

    case 255:
      androidConnected = true;
      Serial.print("androidConnected");
      break;

    default:
      //Si la commande est incorrecte
      correctPacket = false;
      dataPacket.curLoc = 0;
      while (Serial.available())
        Serial.read();
      break;
  }
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
  Serial.print("Bluetooth OK");
  delay(2000); // This delay is required.
  bluetoothSerial.flush();
}

void loop()
{
  if (bluetoothSerial.available() > 3)
  {
    Serial.println("Bluetooth Data available");
    checkAndroidCommand();
  }
}

//QUAND LE NOMBRE DE PLACES CHANGE
void updateNbrePlaces()
{
  Serial.println("updateNbrePlaces");

  i = random(0, 15);

  tableauEmplacements[i] =  random(0, 2);
  Serial.println("i");
  Serial.println(i);
  Serial.println(tableauEmplacements[i]);

  sendMessage(msg_carParkedOnPosition, i, tableauEmplacements[i]);
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

    handleCommand(dataPacket.data[CMD], dataPacket.data[DATA_1], dataPacket.data[DATA_2]);

    if (correctPacket == true )
    {
      Serial.print("Paquet OK\n");
      correctPacket = false;
    }
  }
}
