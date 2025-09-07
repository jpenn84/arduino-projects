void setup() {
  pinMode(14, OUTPUT); // Red LED
  pinMode(15, OUTPUT); // Green LED
  pinMode(16, OUTPUT); // Blue LED
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  // Red
  Serial.println("Red");
  analogWrite(14, 250);
  delay(1000);

  // Off
  analogWrite(14, 255);
  delay(1000);

  // Yellow
  Serial.println("Yellow");
  analogWrite(14, 250);
  analogWrite(15, 250);
  delay(1000);

  // OFF
  analogWrite(14, 255);
  analogWrite(15, 255);
  delay(1000);

  // Green
  Serial.println("Green");
  analogWrite(15, 250);
  delay(1000);

  // Off
  analogWrite(15, 255);
  delay(1000);

  // Cyan
  Serial.println("Cyan");
  analogWrite(15, 250);
  analogWrite(16, 250);
  delay(1000);

  // OFF
  analogWrite(15, 255);
  analogWrite(16, 255);
  delay(1000);

  // Blue
  Serial.println("Blue");
  analogWrite(16, 250);
  delay(1000);

  // Off
  analogWrite(16, 255);
  delay(1000);

  // Magenta
  Serial.println("Magenta");
  analogWrite(14, 250);
  analogWrite(16, 250);
  delay(1000);

  // Off
  analogWrite(14, 255);
  analogWrite(16, 255);
  delay(1000);

}