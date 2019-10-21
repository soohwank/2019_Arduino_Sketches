// Motors
#define ENA 6
#define IN1 7
#define IN2 5
#define IN3 4
#define IN4 2
#define ENB 3

// IR Sensors
#define IR_L 10 
#define IR_C 9
#define IR_R 8

// Ultrasonic Sensor
#define Trigger 11
#define Echo 12

int speed = 100; // 0~255

void forwardLeftMotors()
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  analogWrite(ENA, speed);    
}

void backwardLeftMotors()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  analogWrite(ENA, speed);    
}

void stopLeftMotors()
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,HIGH);
  analogWrite(ENA, speed);    
}

void forwardRightMotors()
{
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  analogWrite(ENB, speed);    
}

void backwardRightMotors()
{
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  analogWrite(ENB, speed);    
}

void stopRightMotors()
{
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  analogWrite(ENB, speed);    
}

void turnRight()
{
  forwardLeftMotors();
  stopRightMotors();
}

void turnRightQuickly()
{
  forwardLeftMotors();
  backwardRightMotors();
}

void turnLeft()
{
  backwardLeftMotors();
  stopLeftMotors();
}

void turnLeftQuickly()
{
  backwardLeftMotors();
  forwardRightMotors();
}

void goStraight()
{
  forwardLeftMotors();
  forwardRightMotors();
}

void stop()
{
  stopLeftMotors();
  stopRightMotors();  
}

void setup() {
  // Serial
  Serial.begin(9600);
  Serial.println("Hello, My Car!");

  // Motor
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // IR Sensor
  pinMode(IR_L, INPUT);
  pinMode(IR_C, INPUT);
  pinMode(IR_R, INPUT);

  // Ultrasonic Sensor
  pinMode(Trigger, OUTPUT);
  pinMode(Echo, INPUT);
}

//void loop() { stop(); }
void loop() {
  int L = digitalRead(IR_L);
  int C = digitalRead(IR_C);
  int R = digitalRead(IR_R);
  Serial.print("IR Left: ");  Serial.print(L);
  Serial.print(", IR Center: ");  Serial.print(C);
  Serial.print(", IR Right: ");  Serial.println(R);

  // 101: go forward
  // 011: turn left quick
  // 001: turn left
  // 110: turn right quick
  // 100: turn right
  // 000: stop

  // 101: go forward
  if      (L == 1 && C == 0 && R == 1) return goStraight();
  else if (L == 0 && C == 1 && R == 1) return turnLeftQuickly();
  else if (L == 0 && C == 0 && R == 1) return turnLeft();
  else if (L == 1 && C == 1 && R == 0) return turnRightQuickly();
  else if (L == 1 && C == 0 && R == 0) return turnRight();
  else if (L == 0 && C == 0 && R == 0) return stop();
}
