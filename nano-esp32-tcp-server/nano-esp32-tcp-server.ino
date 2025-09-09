/*
  nano-esp32-tcp-server.ino
  This software is licensed under the GLPv3 license: https://www.gnu.org/licenses/gpl-3.0.en.html

  This sketch is written for the Arduino Nano ESP32.
  This is a TCP server that will echo back messages which it receives. Press the "Enter" key after each message.
  Additionally, sending "r", "g", or "b" will toggle the respective colors in the RGB LED.
  Requires a WiFiCredentials.h header file which defines SSID, PASSWORD, and PORT. See readme for more info.

  !!! Important note: RGB LEDs are active low, so they will turn on with LOW/0/false and off with HIGH/1/true !!!

  LED_BUILTIN States:
    - Steady on when not connected to WiFi
    - Blinking when connected to WiFi but no TCP connection
    - Off when connected to TCP
*/
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include "WiFiCredentials.h"

const char* ssid = SSID;
const char* password = PASSWORD;
const int tcpPort = PORT; // Example port

WiFiServer server(tcpPort); // For TCP server

// Initial state of Built-in LEDs
bool ledRed = true;     // RGB LED is common anode, will be inverse of the pin state
bool ledGreen = true;   // RGB LED is common anode, will be inverse of the pin state
bool ledBlue = true;    // RGB LED is common anode, will be inverse of the pin state
bool ledBuiltin = true; // LED_BUILTIN Initial state on while connecting to WiFi

// For blinking the Built In LED
unsigned long previousMillis = 0;
const long interval = 500;

void setup() {
  // Set pin modes for LEDs
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // Turn off RGB LEDs on startup
  digitalWrite(LED_RED, ledRed);
  digitalWrite(LED_GREEN, ledGreen);
  digitalWrite(LED_BLUE, ledBlue);

  digitalWrite(LED_BUILTIN, ledBuiltin); // Turn on LED_BUILTIN for WiFi not connected status

  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Print WiFi status to Console
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Waiting for client to connect...");

  server.begin(); // Start the TCP server
}

void loop() {
  WiFiClient client = server.available();

  // Blink LED_BUILTIN while connected to WiFi but not connected to TCP client
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    ledBuiltin = !ledBuiltin;
    previousMillis = currentMillis;
    digitalWrite(LED_BUILTIN, ledBuiltin);
  }

  if (client) {
    Serial.print("New client connected: ");
    Serial.print(client.remoteIP());
    Serial.print(":");
    Serial.println(client.remotePort());

    // Turn of LED_BUILTIN when connected to TCP:
    ledBuiltin = false;
    digitalWrite(LED_BUILTIN, ledBuiltin);

    while (client.connected()) {
      if (client.available()) {
        String receivedData = client.readStringUntil('\n');
        Serial.print("Received from client: ");
        Serial.println(receivedData);
        client.print("Received: ");
        client.println(receivedData);

        // If receivedData is r, g, or b, also toggle the respective LED
        if (receivedData == "r" || receivedData == "g" || receivedData == "b") {
          toggleRgbLed(receivedData, client);
        }
      }
    }
    Serial.println("Client disconnected");
  }
}

void toggleRgbLed(String receivedData, WiFiClient client) {
  if (receivedData == "r") {
    ledRed = !ledRed;
  } else if (receivedData == "g") {
    ledGreen = !ledGreen;
  } else if (receivedData == "b") {
    ledBlue = !ledBlue;
  }
  digitalWrite(LED_RED, ledRed);
  digitalWrite(LED_GREEN, ledGreen);
  digitalWrite(LED_BLUE, ledBlue);

  // Print LED status to the Serial console
  Serial.print("** RGB Status: ");
  Serial.print((int)!ledRed);
  Serial.print((int)!ledGreen);
  Serial.print((int)!ledBlue);
  Serial.println(" **");

  // Print LED status to the TCP client
  client.print("** RGB Status: ");
  client.print((int)!ledRed);
  client.print((int)!ledGreen);
  client.print((int)!ledBlue);
  client.println(" **");
}