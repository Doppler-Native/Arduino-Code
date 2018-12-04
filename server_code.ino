

//#define PIN_DIR D6
//#define PIN_PWM D0

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <Hash.h>
#include "control_logic.h"

ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

#define USE_SERIAL Serial
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
    onDisconnect();
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        USE_SERIAL.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        webSocket.sendTXT(num, "Connected");
      }
      break;
    case WStype_TEXT:
      {
        String really = (char *) payload;
        char controlID = really[0];
        int data = really.substring(2).toInt();
        controlAction(controlID, data);
      }
      break;
    case WStype_BIN:
      {
        USE_SERIAL.printf("[%u] get binary length: %u\n", num, length);
        hexdump(payload, length);
      }
      break;
  }
};


void setup() {
  setupIO();

  USE_SERIAL.begin(115200);

  USE_SERIAL.println();
  USE_SERIAL.println();
  USE_SERIAL.println();

  wifiSetup();

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  /*
  for (uint8_t t = 4; t > 0; t--) {
    USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
    USE_SERIAL.flush();
    delay(1000);
  };
  */
  USE_SERIAL.print("\n\n");

  Serial.printf("Connect to http://%s.local");
  Serial.println(WiFi.localIP());


  server.begin();
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
};

void loop() {
  webSocket.loop();
  server.handleClient();
};
