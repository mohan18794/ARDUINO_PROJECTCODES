int trig=2;
int echo=3;
#include<Servo.h>;
Servo servo;
void setup() {
  
pinMode(2,OUTPUT);
pinMode(3,INPUT);
servo.attach(A0);
Serial.begin(9600);
}

void loop() {
  digitalWrite(trig,0);
  delayMicroseconds(10);
  digitalWrite(trig,1);
  delayMicroseconds(10);
  digitalWrite(trig,0);
  long time=pulseIn(echo,1);
  int distance=0.0343*time/2;
  Serial.println(distance);
  delay(200);
  if(distance<=50){
  servo.write(180);
  delay(2000);
  }
  else{
    servo.write(0);
  }
  

}
