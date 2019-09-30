#include <Servo.h>

const int PIN_SERVO_MOTOR = 11;

// servo object to control the SG90 servo
Servo servo;

void setup() {
  // open the serial port and set the data rate to 9600 bps
  Serial.begin(9600);
  Serial.println("Servo Motol Control");

  // set the servo pin
  servo.attach(PIN_SERVO_MOTOR);
}

void loop() {
  // go from 0 degree to 180 degrees
  for (int angle = 0; angle <=180; angle++)
  {
    servo.write(angle);
    delay(20);
  }

  // go from 180 degrees to 0 degree
  for (int angle = 180; angle >= 0; angle--)
  {
    servo.write(angle);
    delay(20);
  }
}
