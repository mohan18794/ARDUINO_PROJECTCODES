#define BLYNK_TEMPLATE_ID "TMPL3EX3bld4c" 
#define BLYNK_TEMPLATE_NAME "IOT PARKING" 
#define BLYNK_AUTH_TOKEN "L7APlp6FP6LzF1AAEbnysbtpoBbPHaRc" 
#define BLYNK_PRINT Serial 
#include <WiFi.h> 
#include <BlynkSimpleEsp32.h> 
#include <Wire.h>  
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27, 16, 2); 
int slot1 = 34; 
int slot2 = 35; 
int slot3 = 32; 
int slot4 = 33; 
int slot1_state; 
int slot2_state; 
int slot3_state; 
int slot4_state; 
/* 
int gate_in = 25; 
int gate_out = 26;*/ 
// Your WiFi credentials. 
// Set password to "" for open networks. 
char auth[] = BLYNK_AUTH_TOKEN; 
char ssid[] = "xxxxxx";// network credentials as per your router ssid 
char pass[] = "xxxxxxx"; //network credentials as per your router password 
bool myflag1 = false; 
bool myflag2 = false; 
BlynkTimer timer; 
WidgetLED led1  (V0); 
WidgetLED led2  (V1); 
WidgetLED led3  (V2); 
WidgetLED led4  (V3); 
void setup() 
{ 
// Debug console 
Serial.begin(115200); 
pinMode(slot1,INPUT); 
pinMode(slot2,INPUT); 
pinMode(slot3,INPUT); 
pinMode(slot4,INPUT); 
//  pinMode(gate_in,INPUT); 
// pinMode(gate_out,INPUT); 
lcd.begin(); 
lcd.backlight(); 
lcd.setCursor(0,0); 
lcd.print(" car parking "); 
delay(1000); 
lcd.clear(); 
Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass); 
// You can also specify server: 
// Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80); 
//Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 
8080); 
} 
void loop() 
{ 
Blynk.run(); 
SLOT1(); 
SLOT2(); 
SLOT3(); 
SLOT4(); 
lcd.setCursor(0,0); 
lcd.print("S1:"); 
lcd.setCursor(9,0); 
lcd.print("S2:"); 
lcd.setCursor(0,1); 
lcd.print("S3:"); 
lcd.setCursor(9,1); 
lcd.print("S4:"); 
delay(500);    
}void SLOT1(){ 
slot1_state = digitalRead(slot1); 
Serial.print("slot1_state:"); 
Serial.println(slot1_state); 
if(slot1_state  == 0 &&  myflag1 == false){ 
lcd.setCursor(3,0); 
lcd.print("FULL "); 
led1.on(); 
Blynk.logEvent("slot1"); 
myflag1 =true; 
//Serial.print("nagu"); 
}if(slot1_state  == 1 &&  myflag1 == true ){ 
lcd.setCursor(3,0); 
lcd.print("EMPTY"); 
led1.off(); 
// Serial.println("nagu1"); 
Blynk.logEvent("slot1_empty"); 
myflag1 =false; 
} 
} 
void SLOT2(){ 
slot2_state = digitalRead(slot2); 
Serial.print("slot2_state:"); 
Serial.println(slot2_state); 
if(slot2_state  == 0){ 
lcd.setCursor(12,0); 
lcd.print("FULL "); 
led2.on(); 
// Serial.print("nagu"); 
}if(slot2_state  == 1){ 
lcd.setCursor(12,0); 
lcd.print("EMPTY "); 
led2.off(); 
} 
} 
void SLOT3(){ 
slot3_state = digitalRead(slot3); 
Serial.print("slot3_state:"); 
Serial.println(slot3_state); 
if(slot3_state  == 0){ 
lcd.setCursor(3,1); 
lcd.print("FULL "); 
led3.on(); 
}if(slot3_state  == 1){ 
lcd.setCursor(3,1); 
lcd.print("EMPTY "); 
led3.off(); 
} 
} 
void SLOT4(){ 
slot4_state = digitalRead(slot4); 
Serial.print("slot4_state:"); 
Serial.println(slot4_state); 
if(slot4_state  == 0){ 
lcd.setCursor(12,1); 
lcd.print("FULL "); 
led4.on(); 
} 
if(slot4_state  == 1){ 
lcd.setCursor(12,1); 
lcd.print("EMPTY "); 
led4.off(); 
} 
} 
