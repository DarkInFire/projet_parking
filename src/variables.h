/* Variables disponibles dans le programme */
  
/* --- Fonctionnement interne --- */

uint8_t etatParking;
uint8_t nbrPlacesDispo;
int tableauEmplacements[23];

/* --- Communication Android --- */
uint8_t androidToken;
bool androidConnected;
uint8_t transmissionBytes[5];

unsigned long lastTimerHit;
bool correctPacket;
const int BUFFER_LIMIT = 4;

const int baudRate = 9600;