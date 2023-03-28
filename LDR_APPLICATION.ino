int ldr_pin=A0;
int ldr_value;
int led=A1;
void setup() {
  pinMode(ldr_pin,INPUT);
  Serial.begin(9600);
  
}

void loop() {
  ldr_value=analogRead(ldr_pin);
  //Serial.print(ldr_value);
  delay(200);
  Serial.println(ldr_value);
  if(ldr_value<100)
  {
    digitalWrite(led,1);
    delay(200);
  }
  else{
    digitalWrite(led,0);
    delay(200);
  }
  }
