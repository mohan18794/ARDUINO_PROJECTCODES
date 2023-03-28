int lmp=2;
int lmn=3;
int rmp=4;
int rmn=5;
int sl=6;
int sr=7;
void setup() {
  pinMode(lmp,OUTPUT);
  pinMode(lmn,OUTPUT);
  pinMode(rmp,OUTPUT);
  pinMode(rmn,OUTPUT);
  pinMode(sl,INPUT);
  pinMode(sr,INPUT);
}

void loop() {
  //FORWARD
  if(digitalRead(sl)==1&&digitalRead(sr)==1){
  digitalWrite(lmp,1);
  digitalWrite(lmn,0);
  digitalWrite(rmp,1);
  digitalWrite(rmn,0);
  }
  //left
  if(digitalRead(sl)==0&&digitalRead(sr)==1){
    digitalWrite(lmp,0);
    digitalWrite(lmn,0);
    digitalWrite(rmp,1);
    digitalWrite(rmn,0);
    
  }
  //RIGHT
  if(digitalRead(sl)==1&&digitalRead(sr)==0){
    digitalWrite(lmp,1);
    digitalWrite(lmn,0);
    digitalWrite(rmp,0);
    digitalWrite(rmn,0);
  }
  //STOP
  if(digitalRead(sl)==0&&digitalRead(sr)==0){
    digitalWrite(lmp,0);
    digitalWrite(lmn,0);
    digitalWrite(rmp,0);
    digitalWrite(rmn,0);
    
  }
  
  
}
