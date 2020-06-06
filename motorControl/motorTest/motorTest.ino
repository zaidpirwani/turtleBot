// Sketch to test Motor Pins
int in1 = 23; //right front, IN1==HIGH is FORWARD
int in2 = 22; //right front

int in3 = 24; //right back, IN3==HIGH is FORWARD
int in4 = 25; //right back

int stdby1 = 27; //for both right motors

int in5 = 28; //left back, IN5==HIGH is FORWARD
int in6 = 29; //left back

int in7 = 31; //left front, IN7==HIGH is FORWARD
int in8 = 30; //left front
int stdby2 = 26; // left motors

int pwm1   = 8;
int pwm2   = 9;
int pwm3   = 10;
int pwm4   = 11;


void setup() {
  Serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(pwm1, OUTPUT);
  pinMode(stdby1, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(pwm2, OUTPUT);

  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);
  pinMode(pwm3, OUTPUT);
  pinMode(stdby2, OUTPUT);
  pinMode(in7, OUTPUT);
  pinMode(in8, OUTPUT);
  pinMode(pwm4, OUTPUT);
}

void loop() {
  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);
  digitalWrite(stdby2, HIGH);
  
  for(int a=0; a<255; a++){
    analogWrite(pwm3, a);
    delay(25);  
  }
  Serial.println("FULL SPEED ACHIEVED, DIRECTION 1");
  delay(2000);
  Serial.println("DECREASING SPEED, DIRECTION 1");
  for(int a=255; a>1; a--){
    analogWrite(pwm3, a);
    delay(25);
  }
  Serial.println("STOPPED, DIRECT ION 1");
  digitalWrite(stdby2, LOW);
  delay(2000);

  digitalWrite(stdby2, HIGH);
  
  for(int a=0; a<255; a++){
    analogWrite(pwm3, a);
    delay(25);  
  }
  Serial.println("FULL SPEED ACHIEVED, DIRECTION 1");
  delay(2000);
  Serial.println("DECREASING SPEED, DIRECTION 1");
  for(int a=255; a>1; a--){
    analogWrite(pwm3, a);
    delay(25);
  }
  Serial.println("STOPPED, DIRECT ION 1");
  digitalWrite(stdby2, LOW);
  delay(10000);
}
