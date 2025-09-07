#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>

const char* ssid = SSID;
const char* password = PASSWORD;
const int tcpPort = 80; // Example port

WiFiServer server(tcpPort); // For TCP server

bool ledRed = false;
bool ledGreen = false;
bool ledBlue = false;

void setup() {
  pinMode(14, OUTPUT); // Red LED
  pinMode(15, OUTPUT); // Green LED
  pinMode(16, OUTPUT); // Blue LED
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
  digitalWrite(16, HIGH);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Waiting for client to connect...");

  server.begin(); // Start the TCP server
}

void loop() {
  // TCP Server example
  WiFiClient client = server.available();
  if (client) {
    Serial.print("New client connected: ");
    Serial.print(client.remoteIP());
    Serial.print(":");
    Serial.println(client.remotePort());
    while (client.connected()) {
      if (client.available()) {
        String receivedData = client.readStringUntil('\n');
        Serial.print("Received from client: ");
        Serial.println(receivedData);
        client.print("Echo: ");
        client.println(receivedData);
        if (receivedData == "r") {
          ledRed = !ledRed;
        } else if (receivedData == "g") {
          ledGreen = !ledGreen;
        } else if (receivedData == "b") {
          ledBlue = !ledBlue;
        }
        if (receivedData == "r" || receivedData == "g" || receivedData == "b" ) {
          if (ledRed) {
            digitalWrite(14, LOW);
            client.println("*** RED   ON  ***");
            Serial.println("*** RED   ON  ***");
          } else {
            digitalWrite(14, HIGH);
            client.println("*** RED   OFF ***");
            Serial.println("*** RED   OFF ***");
          }
          if (ledGreen) {
            digitalWrite(15, LOW);
            client.println("*** GREEN ON  ***");
            Serial.println("*** GREEN ON  ***");
          } else {
            digitalWrite(15, HIGH);
            client.println("*** GREEN OFF ***");
            Serial.println("*** GREEN OFF ***");
          }
          if (ledBlue) {
            digitalWrite(16, LOW);
            client.println("*** BLUE  ON  ***");
            Serial.println("*** BLUE  ON  ***");
          } else {
            digitalWrite(16, HIGH);
            client.println("*** BLUE  OFF ***");
            Serial.println("*** BLUE  OFF ***");
          }
        }
      }
    }
    Serial.println("Client disconnected");
  }

  // TCP Client example (sending to a remote server)
  // WiFiClient client;
  // if (client.connect("REMOTE_SERVER_IP", tcpPort)) {
  //   Serial.println("Connected to remote server");
  //   client.println("Hello from ESP32!");
  //   String response = client.readStringUntil('\n');
  //   Serial.print("Response from server: ");
  //   Serial.println(response);
  //   client.stop();
  // } else {
  //   Serial.println("Connection to remote server failed");
  // }
  // delay(5000); // Wait before attempting reconnect/resend
}