//int a=A0;
#include<Servo.h>
Servo servo1;
void setup() {
  servo1.attach(A0);
  

}

void loop() {
  servo1.write(0);
  delay(5000);
  servo1.write(180);
  delay(5000);
  
  

}
