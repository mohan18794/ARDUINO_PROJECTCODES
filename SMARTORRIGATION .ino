int a= A0;
int m1=3;
int m2=5;
int ledR=8;
int ledG=9;
void setup() {
  pinMode(a,INPUT);
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
  int a=analogRead(a);
  Serial.println(a);
  delay(300);
  if(a<=800){
   analogWrite(m1,0);
   analogWrite(m2,0);
   digitalWrite(ledR,1);
   digitalWrite(ledG,0);
  }
  else{
   analogWrite(m1,255);
   analogWrite(m2,0);
   digitalWrite(ledG,1);
   digitalWrite(ledR,0);
  }
//alogWrite(
  
  
}
