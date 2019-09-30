int i = 0;

void setup() {
  // open the serial port and set the data rate to 9600 bps
  Serial.begin(9600);
  Serial.println("Hello, World!");
}

void loop() {
  // print the number
  Serial.print("i = ");
  Serial.println(i);

  // sleep 10 msec
  delay(10);

  // next
  i++;
}
