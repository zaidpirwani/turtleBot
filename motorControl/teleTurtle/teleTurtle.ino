#include <ros.h>
#include <geometry_msgs/Twist.h>
ros::NodeHandle  nh;
void messageCb2( const geometry_msgs::Twist& msg){
  int x = msg.linear.x;
  int z = msg.angular.z;
  if(x>0 && z==0){
    forward();
  }else if(x<0 && z==0){
    backward();
  }else if(x==0 && z>0){
    rotateLeft();
  }else if(x==0 && z<0){
    rotateRight();
  }else{
    stopMotors();
  }
}
ros::Subscriber<geometry_msgs::Twist> sub2("cmd_vel", messageCb2 );


// Sketch to test basic TELEOP
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

//    FRONT
// LEFT   RIGHT
//  M4      M1
//
//  M3      M2

//SIMPLE MOVEMENTS
// FORWARD  = all motors forward
// BACKWARD = all motors backward
// ROTATE RIGHT = right motors forward,  left motors backward
// ROTATE LEFT  = right motors backward, left motors forward

int globalPWM = 0;
int lastCmd = -1; // stop=0, fwd=1, rev=2, left=3, right=4

void stopMotors(void){
  if(lastCmd==0){
    return;
  }else{
    lastCmd = 0;
    digitalWrite(stdby1, HIGH);
    digitalWrite(stdby2, HIGH);
    for(int a=globalPWM; a>0; a--){
      analogWrite(pwm1, a);
      analogWrite(pwm2, a);
      analogWrite(pwm3, a);
      analogWrite(pwm4, a);
      globalPWM = a;
      delay(2);
    }
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    digitalWrite(in5, LOW);
    digitalWrite(in6, LOW);
    digitalWrite(in7, LOW);
    digitalWrite(in8, LOW);
    digitalWrite(stdby1, LOW);
    digitalWrite(stdby2, LOW);    
  }
}

void forward(void){
  if(lastCmd==1){
    return;
  }else{
    lastCmd = 1;
    stopMotors();
    lastCmd = 1;
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    digitalWrite(in5, HIGH);
    digitalWrite(in6, LOW);
    digitalWrite(in7, HIGH);
    digitalWrite(in8, LOW);
    digitalWrite(stdby1, HIGH);
    digitalWrite(stdby2, HIGH);
    for(int a=0; a<150; a++){
      analogWrite(pwm1, a);
      analogWrite(pwm2, a);
      analogWrite(pwm3, a);
      analogWrite(pwm4, a);
      globalPWM = a;
      delay(5);
    }
  }
}

void backward(void){
  if(lastCmd==2){
    return;
  }else{
    lastCmd = 2;
    stopMotors();
    lastCmd = 2;
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    digitalWrite(in5, LOW);
    digitalWrite(in6, HIGH);
    digitalWrite(in7, LOW);
    digitalWrite(in8, HIGH);
    digitalWrite(stdby1, HIGH);
    digitalWrite(stdby2, HIGH);
    for(int a=0; a<150; a++){
      analogWrite(pwm1, a);
      analogWrite(pwm2, a);
      analogWrite(pwm3, a);
      analogWrite(pwm4, a);
      globalPWM = a;
      delay(5);
    }
  }
}

void rotateLeft(void){
  if(lastCmd==3){
    return;
  }else{
    lastCmd = 3;
    stopMotors();
    lastCmd = 3;
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    digitalWrite(in5, LOW);
    digitalWrite(in6, HIGH);
    digitalWrite(in7, LOW);
    digitalWrite(in8, HIGH);
    digitalWrite(stdby1, HIGH);
    digitalWrite(stdby2, HIGH);
    for(int a=0; a<100; a++){
      analogWrite(pwm1, a);
      analogWrite(pwm2, a);
      analogWrite(pwm3, a);
      analogWrite(pwm4, a);
      globalPWM = a;
      delay(5);
    }
  }
}
void rotateRight(void){
  if(lastCmd==4){
    return;
  }else{
    lastCmd = 4;
    stopMotors();
    lastCmd = 4;
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    digitalWrite(in5, HIGH);
    digitalWrite(in6, LOW);
    digitalWrite(in7, HIGH);
    digitalWrite(in8, LOW);
    digitalWrite(stdby1, HIGH);
    digitalWrite(stdby2, HIGH);
    for(int a=0; a<100; a++){
      analogWrite(pwm1, a);
      analogWrite(pwm2, a);
      analogWrite(pwm3, a);
      analogWrite(pwm4, a);
      globalPWM = a;
      delay(5);
    }
  }
}


void setup() {
  nh.initNode();
  nh.subscribe(sub2);

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
  nh.spinOnce();
  delay(1);
}
