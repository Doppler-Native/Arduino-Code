#include "control_logic.h"


/*** SETUP WIFI BY COMMENT/UNCOMMENTING DESIRED OPTION ***/
// 1. Connect to existing WiFi network
#define STATION_MODE 1
// 2. Set up esp8266 as a WiFi network. The mobile device will connect directly to the eso8266
// #define ACCESS_POINT 1

/***  SET WIFI SSID AND PASSWORD  ***/
const char SSID[] = "Doppler";
const char PASSWORD[] = "shift";


/*** ADD ANY OTHER DEFINE STATEMENTS HERE ***/
// e.g. #define PIN_PWM D6


/*** DEFINE ANY VARIABLES HERE ***/
// e.g. int ledState = 0;


/*** void setupIO (void)
 *** This function is called by setup()
 *** Place your usual setup() code here
 ***/
void setupIO (void) {
  /* EXAMPLE:
    pinMode(PIN_PWM, OUTPUT);
    pinMode(PIN_DIR, OUTPUT);
  */
  pinMode(PIN_PWM, OUTPUT);
  digitalWrite(PIN_PWM, 1);
};

/*** void wifiSetup(void)  ***/
void wifiSetup(void) {
     #ifdef STATION_MODE
    WiFi.begin(SSID, PASSWORD);
  #endif
  #ifndef STATION_MODE
    #ifdef ACCESS_POINT
      WiFi.softAP(SSID, PASSWORD);
    #endif
#endif
};

/*** CONTROL FUNCTIONS
 ***
 *** Does something with the data recieved through the websocket
 *** these functions are called in the switch - case in controlActions
 ***
 *** SLIDER: (VALUE) - needs a int value
 ***
 *** BUTTON: (VOID) - passes integer 1 when pressed
 ***
 *** SWITCH: (VOID) - passes 0 when switched of, 1 when switched on
 ***/
void control_1 (int num) {
};
void control_2 (int num) {
};
void control_3 (int num) {
};
void control_4 (int num) {
};
void control_5 (int num) {
};
void control_6 (int num) {
};


/*** void controlAction(char, int)
 ***
 *** This dispatches actions based on data sent through the websocket
 *** The server code will call this function when a message is recieved
 *** passing the control id and value parameters to it.
 ***/
void controlAction(char id, int value) {
  switch (id) {
    case '1':
      control_1(value);
      break;
    case '2':
      control_2(value);
      break;
    case '3':
      control_3(value);
      break;
    case '4':
      control_4(value);
      break;
    case '5':
      control_5(value);
      break;
    case '6':
      control_6(value);
      break;
    default:
      // some Error
      break;
  };
};



/*** void onDisconnect(void)
 ***
 *** NOT YET IMPLEMENTED - SAFETY CODE
 *** This will be called when websocket connection is lost disconnects
 ***/
void onDisconnect(void) {
};
