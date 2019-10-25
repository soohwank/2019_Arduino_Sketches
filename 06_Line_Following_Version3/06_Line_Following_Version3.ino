// Arduino Uno, PWM: 3, 5, 6, 9, 10, 11

// Motors
#define ENA 6 // PWM
#define IN1 7
#define IN2 5
#define IN3 4
#define IN4 2
#define ENB 3 // PWM

// IR Sensors
#define IR_L 8 
#define IR_C 9
#define IR_R 10

// Ultrasonic Sensor
#define TRIGGER 11
#define ECHO 12

uint8_t isFinished = 0;
uint8_t hasPassedCrossSection = 0;

double getDistanceToObjectInCm();

void forwardLeftMotor(uint8_t motorSpeed);
void backwardLeftMotor(uint8_t motorSpeed);
void stopLeftMotor();

void forwardRightMotor(uint8_t motorSpeed);
void backwardRightMotor(uint8_t motorSpeed);
void stopRightMotor();

void goForward();
void turnLeft();
void turnRight();
void stop();

void setup()
{
  Serial.begin(9600);
  Serial.println("Hello, Ultrasonic");

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
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop()
{ 
  if (isFinished)
  {
    stop();
    return;
  }

  if (hasPassedCrossSection)
  {
    if (getDistanceToObjectInCm() < 20)
    {
      stop();
      return;
    }
  }
  
  int L = digitalRead(IR_L);
  int C = digitalRead(IR_C);
  int R = digitalRead(IR_R);
  Serial.print("IR Left: ");  Serial.print(L);
  Serial.print(", IR Center: ");  Serial.print(C);
  Serial.print(", IR Right: ");  Serial.println(R);

  if (L == 1 && C == 0 && R == 1) goForward();
  if (L == 0 && C == 1 && R == 1) turnLeft();
  if (L == 0 && C == 0 && R == 1) turnLeft();
  if (L == 1 && C == 1 && R == 0) turnRight();
  if (L == 1 && C == 0 && R == 0) turnRight();

  // if we pass a cross section,
  if (L == 0 && C == 0 && R == 0)
  {
    // this is our first time
    if (hasPassedCrossSection == 0)
    {
      // flag it
      hasPassedCrossSection = 1;
      
      // pass the cross section to avoid multiple detections
      goForward();
      delayMicroseconds(100);
    }
    else // final goal
    {
      stop();
      isFinished = 1;
    }
  }
}

double getDistanceToObjectInCm()
{
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);

  long duration = pulseIn(ECHO, HIGH);
  double distanceToObjectInCm = duration * 0.034 / 2.0; // cm
  Serial.print("Distance: ");
  Serial.print(distanceToObjectInCm); 
  Serial.println(" [cm]");

  return distanceToObjectInCm;
}

void forwardLeftMotor(uint8_t motorSpeed)
{
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);    
  analogWrite(ENB, motorSpeed);
}

void backwardLeftMotor(uint8_t motorSpeed)
{
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);  
  analogWrite(ENB, motorSpeed);
}

void stopLeftMotor()
{
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);  
  analogWrite(ENB, 0);
}

void forwardRightMotor(uint8_t motorSpeed)
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);    
  analogWrite(ENA, motorSpeed);
}

void backwardRightMotor(uint8_t motorSpeed)
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);  
  analogWrite(ENA, motorSpeed);
}

void stopRightMotor()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);  
  analogWrite(ENA, 0);    
}

void goForward()
{
  forwardLeftMotor(85);
  forwardRightMotor(70);  
}

void turnLeft()
{
  stopLeftMotor();
  forwardRightMotor(120);  
}

void turnRight()
{
  forwardLeftMotor(130);
  stopRightMotor();  
}

void stop()
{
  stopLeftMotor();
  stopRightMotor();  
}
