#include <Arduino.h>
#include "Communication\WebSocket.h"
#include "StateController.h"
#include "WiFi.h"
#include "Command\Rover.h"
#include "Command\Queue.h"

const char *ssid = "Step";
const char *password = "@2805_1984@";
const char *URL = "ws://192.168.1.20:6969/api/FrontSockets/RoverData";
WebSocket *_socketHandler;
ByteQueue DataQueue;
StateController state;
void setup()
{
  Serial.begin(115200);
  // Sensors::SetupDHT();
  // Sensors::SetupMPU();
  // Sensors::SetupUltrasonic();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    WiFi.begin(ssid, password);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected");
  _socketHandler = new WebSocket(URL, &DataQueue);
  Serial.println("Established");
}

void loop()
{
  state.SendOnlineDataState();
  delay(1000);
}
