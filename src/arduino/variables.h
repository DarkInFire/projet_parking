#ifndef VARIABLES
#define VARIABLES

#include <SoftwareSerial.h> 
#define DEBUG_ENABLED  1
#define RxD 6
#define TxD 7

SoftwareSerial bluetoothSerial(RxD,TxD);

extern uint8_t etatParking;
extern uint8_t nbrPlacesDispo;
extern int tableauEmplacements[23];

extern const int baudRate = 9600;

#endif