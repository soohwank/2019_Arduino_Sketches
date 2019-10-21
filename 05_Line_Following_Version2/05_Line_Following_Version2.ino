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

void motorControl(int directionLeft, int pwmLeft,
                  int directionRight, int pwmRight)
{
  // left motors
  if (directionLeft > 0)
  {
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);    
  }
  else if (directionLeft < 0)
  {
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);  
  }
  else
  {
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,HIGH);  
  }  
  analogWrite(ENA, pwmLeft);    

  // right motors
  if (directionRight > 0)
  {
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);    
  }
  else if (directionRight < 0)
  {
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);  
  }
  else
  {
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);  
  }
  analogWrite(ENB, pwmRight);    
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
  if      (L == 1 && C == 0 && R == 1) return motorControl( 1, 140,  1, 140); // go forward
  else if (L == 0 && C == 1 && R == 1) return motorControl(-1, 100,  1, 230); // turn left quickly
  else if (L == 0 && C == 0 && R == 1) return motorControl( 0,   0,  1, 140); // turn left
  else if (L == 1 && C == 1 && R == 0) return motorControl( 1, 230, -1, 100); // turn right quickly
  else if (L == 1 && C == 0 && R == 0) return motorControl( 1, 140,  0,   0); // turn right
  else if (L == 0 && C == 0 && R == 0) return motorControl( 0,   0,  1, 140); // stop
}
