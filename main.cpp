#include <Arduino.h>
#include <NewPing.h>
//紅 vcc 黑gnd
//5橙 A1 6黃 B1 (左)
//9綠 A2 10藍 B2 (右)
//白 vcc 灰 gnd
//2紫 trig 3咖 echo
//11橙 左D0 12黃 右D0
//黑咖 GND 藍綠 VCC


int motorPin_left_forward = 5;//V
int motorPin_left_backward = 6;
int motorPin_right_forward = 10;
int motorPin_right_backward = 9;
// int init_speed = 0;
int current_speed = 0;

int trigPin = 3;
int echoPin = 2;
int maxDistance = 200;
NewPing sonar(trigPin, echoPin, maxDistance);
int reaction_time = 10;
unsigned long time;

// int leftD0Pin = 11;
int rightD0Pin = 12;
int leftA0Pin = A5;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(motorPin_left_backward, OUTPUT);
  pinMode(motorPin_left_forward, OUTPUT);
  pinMode(motorPin_right_backward, OUTPUT);
  pinMode(motorPin_right_forward, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(leftA0Pin, INPUT);

  // pinMode(leftD0Pin, INPUT);
  pinMode(rightD0Pin, INPUT);
}

void stop() {
  // put your main code here, to run repeatedly:
  analogWrite(motorPin_left_backward, 255);
  analogWrite(motorPin_left_forward, 255);
  analogWrite(motorPin_right_backward, 255);
  analogWrite(motorPin_right_forward, 255);
}

void forward(int speed){
  if (speed>255){
    speed=255;
  }
  analogWrite(motorPin_left_backward, 0);
  analogWrite(motorPin_left_forward, speed);
  analogWrite(motorPin_right_backward, 0);
  analogWrite(motorPin_right_forward, speed);
}

void backward(int speed){
  analogWrite(motorPin_left_backward, speed);
  analogWrite(motorPin_left_forward, 0);
  analogWrite(motorPin_right_backward, speed);
  analogWrite(motorPin_right_forward, 0);
}

void model1(int distance_delta, int time_delta, float alpha){
  float a = alpha*(distance_delta*100/time_delta);
  current_speed += static_cast<int>(a*100);
}

void dirver(){
  if (current_speed>100){
    current_speed=100;
  }
  else if (current_speed<-100){
    current_speed=-100;
  }
  if (current_speed>0){
    forward(current_speed);
  }
  else{
    backward(current_speed);
  }
}
int distance_to_speed(int distance){
  if (distance==0){
    return 255;
  }
  else if (distance<3){
    return -255;
  }
  else if (distance<5){
    return -150;
  }
  else if (distance<25){
    return 10*distance;
  }
  else {
    return 255;
  }
}
void car_run(int speed){
  if (speed==-150){
    stop();
    // analogWrite(motorPin_left_backward, 255);
    // analogWrite(motorPin_left_forward, 100);
    // analogWrite(motorPin_right_backward, 255);
    // analogWrite(motorPin_right_forward, 100);
    // delay(100);
  }
  else if (speed<0){
    stop();
    // backward(255);
    // delay(100);
  }
  else if (speed<255){
    analogWrite(motorPin_left_backward, 255-speed);
    analogWrite(motorPin_left_forward, 255);
    analogWrite(motorPin_right_backward, 255-speed);
    analogWrite(motorPin_right_forward, 255);
  }
  else{
    forward(255);
  }
}

void loop() {

  unsigned int us=sonar.ping_median();     
  int distance = sonar.convert_cm(us);
  //car_run(distance_to_speed(distance));

  Serial.println(analogRead(leftA0Pin));
  Serial.println(digitalRead(rightD0Pin));
  // Serial.println(distance);
  // if (distance==0){
  //   analogWrite(motorPin_left_backward, 0);
  //   analogWrite(motorPin_left_forward, 255);
  //   analogWrite(motorPin_right_backward, 0);
  //   analogWrite(motorPin_right_forward, 255);
  // }
  // else if (distance<5){
  //   analogWrite(motorPin_left_backward, 255);
  //   analogWrite(motorPin_left_forward, 0);
  //   analogWrite(motorPin_right_backward, 255);
  //   analogWrite(motorPin_right_forward, 0);
  //   Serial.println(5);
  // }
  // else if (distance<10){
  //   analogWrite(motorPin_left_backward, 255);
  //   analogWrite(motorPin_left_forward, 100);
  //   analogWrite(motorPin_right_backward, 255);
  //   analogWrite(motorPin_right_forward, 100);
  //   Serial.println(10);
  // }
  // else{
  //   analogWrite(motorPin_left_backward, 0);
  //   analogWrite(motorPin_left_forward, 255);
  //   analogWrite(motorPin_right_backward, 0);
  //   analogWrite(motorPin_right_forward, 255);
  //   Serial.println(999);
  // }
  // else if (distance<30){
  //   backward(150);
  //   delay(100);
  // }
  // // else if (distance<10&&distance>5){
  // //   stop();要兩個配合才能漫溢點
  // // }
  // else{
  //   forward(255);             
  //   delay(50);
  // delay(500);     
  // float distance = sonar.ping_cm();
  // Serial.println(distance);
  // delay(500);
  // float distance_ = sonar.ping_cm();
  // Serial.println(distance_);
  // float distance_delta = distance_ - distance;
  // model1(distance_delta, 500, 0.5);
  // Serial.println(current_speed);
  // dirver();

  // put your main code here, to run repeatedly:
  // boolean leftD0 = digitalRead(leftD0Pin);
  // boolean rightD0 = digitalRead(rightD0Pin);
  // Serial.print("left:");
  // Serial.println(leftD0);
  // Serial.print("right:");
  // Serial.println(rightD0);
  // delay(500);
  // return;

}
