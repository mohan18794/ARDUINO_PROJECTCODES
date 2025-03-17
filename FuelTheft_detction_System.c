#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Wire.h> 
#define FIREBASE_HOST "kitsfuel-default-rtdb.firebaseio.com"
#define WIFI_SSID "fueliot"
#define WIFI_PASSWORD "fueliot01"

int buz=D0;
int motor=D1;
int water=A0;

String msg;


int sw=D2;

int s_v,E_V,T_V;
int i,j,k,l,u,v;
int m,n,o,p,mode_l;
int q,r,s,z,t;


void setup() 
{
Serial.begin(9600);
//lcd.begin();
pinMode(motor,OUTPUT);
pinMode(water,INPUT);
pinMode(buz,OUTPUT);

pinMode(sw,INPUT_PULLUP);

digitalWrite(motor,LOW);
digitalWrite(buz,HIGH);


    Serial.print("Connecting");
    while(WiFi.status() != WL_CONNECTED)
{    
        Serial.print(".");
        delay(500);
      }
      Serial.println();
      Serial.print("connected: ");
      Serial.println(WiFi.localIP());

      Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);  

delay(1000);

}

void loop() 
{

   if(Firebase.failed())
     {
       Serial.print("Firebase error");
       Serial.println(Firebase.error());
     }

     
Serial.print("sw: ");
Serial.println(digitalRead(sw));
Serial.print("fuel: ");
Serial.println(analogRead(water));
delay(500);
ss:

if(!digitalRead(sw) )
{
digitalWrite(motor,HIGH);  
Serial.println("VEHICLE-START");
 Firebase ("FUEL_IOT/VSTART",v);
 v++;

 while(1)
{
if(analogRead(water)>800)
{
  Serial.println("low fuel");

 digitalWrite(buz,LOW);  
delay(500);
  digitalWrite(buz,HIGH);  
delay(500);
Firebase ("FUEL_IOT/LFUEL",v);
 v++;
}
if(analogRead(water)<800 &&  analogRead(water)>600 )
{
  Serial.println("midil-fuel");

   //digitalWrite(buz,LOW);  
Firebase ("FUEL_IOT/MFUEL",v);
 v++;
}

if(analogRead(water)<500  )
{
  Serial.println("full fuel");

   //digitalWrite(buz,LOW);  
Firebase ("FUEL_IOT/FFUEL",v);
 v++;
}
if(digitalRead(sw))
{
goto ss;  
}
delay(500);
}
}




if(digitalRead(sw))
{
digitalWrite(motor,LOW);  
Serial.println("VEHICLE-STOP");
Firebase ("FUEL_IOT/VSTOP",v);
 v++;
while(1)
{
  Serial.print("fuel: ");
Serial.println(analogRead(water));
delay(500);
if(analogRead(water)>800)
{
  Serial.println("FUEL THEFT-STOP");
 digitalWrite(buz,LOW);  
delay(500);
  digitalWrite(buz,HIGH);  
delay(500);

Firebase ("FUEL_IOT/TFUEL",v);
 v++;
}
if(analogRead(water)<800 &&  analogRead(water)>600 )
{
   //digitalWrite(buz,LOW);  
Firebase ("FUEL_IOT/MFUEL",v);
 v++;
}

if(analogRead(water)<500  )
{
   //digitalWrite(buz,LOW);  
Firebase ("FUEL_IOT/FFUEL",v);
 v++;
}
if(!digitalRead(sw))
{
goto ss;  
}
delay(500);
}
}
}
