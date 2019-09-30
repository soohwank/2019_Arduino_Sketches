const int PIN_TRIGGER = 13;
const int PIN_ECHO = 12;

void setup() {
  // open the serial port and set the data rate to 9600 bps
  Serial.begin(9600);
  Serial.println("Ultrasonic HC-SR04");

  // set the pin mode
  pinMode(PIN_TRIGGER, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
}

void loop() {
  // [1] trigger input

  // clear the trigger pin
  digitalWrite(PIN_TRIGGER, LOW);
  delayMicroseconds(2);

  // set the trigger pin HIGH for 10 micro seconds
  digitalWrite(PIN_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIGGER, LOW);

  // [2] read the echo pin in microseconds
  long duration = pulseIn(PIN_ECHO, HIGH); // [us]

  // [3] calculate the distance
  // distance [m] = return time [sec] * velocity (340 [m/sec]) / 2 (round-trip)
  // distance [cm] = return time [us] * 0.001 [ms/us] * velocity (340 [mm/ms]) * 0.1 [cm/mm] / 2 (round-trip)
  double distance = duration * 0.034 / 2.0; // [cm]
  
  // [4] print the distance
  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.println(" [cm]");

  // sleep 60 microseconds
  delayMicroseconds(60);
}
