# nano-esp32-tcp-server

This is a TCP server that will echo back messages which it receives. Press the "Enter" key after each message.

Additionally, sending "r", "g", or "b" will toggle the respective colors in the RGB LED.

This also Requires a WiFiCredentials.h header file which defines `SSID`, `PASSWORD`, and `PORT`. See readme for more info. An example file is provided, and has been added to .gitignore to prevent accidentally committing secrets.

## Features

Sending 

Built-in LED shows communication state
- LED steady on: WiFi not connected
- LED Blinking: WiFi Connected, TCP not connected
- LED off: WiFi and TCP port connected

RGB LEDs: Send an `r`, `g`, or `b` to toggle the states of the RGB LEDs. It will also print the LED states to the console and the TCP client.

**Important note:** The RGB LEDs are active low, so sending HIGH/1/true will turn the LED off, and sending LOW/0/false, will turn the LED on. In the console and communications, this will be normalized. E.g., if the Red LED is on, the code will send a 0 to the LED pin, but the console messages will show a 1.
## Run Locally

Navigate to the `nano-esp32-tcp-server` directory and open the `WiFiCredentials.h` file. Update your SSID, WiFi Password, and TCP port.

After this, you can compile and upload this sketch.

### Send/Receive TCP

You will need a TCP client. You can use netcat, with the following command:
```
nc <IP_ADDRESS> <PORT>
```
Once connected, you can write a message and then press return/enter. The TCP Server should echo back your message, prepending `Received: `
