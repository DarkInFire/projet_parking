namespace Android
{
typedef unsigned char uint8_t; 
  void handleCommand(const uint8_t cmd, const uint8_t data1, const uint8_t data2)
  {
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

        default:
          //Si la commande est incorrecte
          correctPacket = false;
          dataPacket.curLoc = 0;
          Serial.println("invalid cmd");
          break;
      }
  }

  Android::void sendMessage(const uint8_t messageId, const uint8_t message1, const uint8_t message2)
  {
    if (!androidConnected)
      return;
    byte buf[] = {255, messageId, androidToken, message1, message2};
    
    Serial.println("---ENVOI D'UN MESSAGE");
    Serial.print("ID Message: ");
    Serial.println(messageId);
    Serial.print("Token: ");
    Serial.println(androidToken);
    Serial.print("Message1: ");
    Serial.println(message1);
    Serial.print("Message2: ");
    Serial.println(message2);
    
    bluetoothSerial.write(buf, 5);
  }

  Android::void setupBluetoothConnection()
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
}