#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include<Servo.h>
SoftwareSerial gsm (10,11);//rx,tx
LiquidCrystal_I2C lcd(0x27,16,2);
Servo myservo;
bool linear;
int 
temp = A0,
gas = A2;
int led=13;

const int flamepin=A1;
const int threshold=200;// sets threshold value for flame sensor
int flamesensvalue=0; // initialize flamesensor reading

int gas_data,temp_data;
void setup() {
Serial.begin(9600);
 gsm.begin(9600);
 lcd.init(); 
 lcd.backlight();
 
 lcd.setCursor(0,0);
lcd.print("   Automatic " );
lcd.setCursor(0,1);
lcd.print(" Window System");
delay(5000);

pinMode(led,OUTPUT);
pinMode(2,OUTPUT);
pinMode(temp,INPUT);
pinMode(gas,INPUT);
pinMode(flamepin,INPUT);
myservo.attach(6);
myservo.write(90);
}

void loop() {
  // put your main code here, to run repeatedly:
  //// gsm /////////

temp_data = analogRead(A0);
  int t = temp_data * 0.201;
Serial.print(" TEMP:      ");
lcd.clear();
lcd.print("TEMP: Normal");
lcd.setCursor(0,1);
lcd.print("SYSTEM NORMAL");

  Serial.println(t);
 if (Serial.available()>0)
   {
  nsms();
    //break;
    Serial.println("system message");
  }
 
  if (gsm.available()>0)
  Serial.write(gsm.read());
  /////
    temperature();
  gase();
  Rain();
    flame();
 
delay(100);
//lcd.clear();
//  lcd.setCursor(0,0);
//lcd.print("   Automatic " );
//lcd.setCursor(0,1);
//lcd.print(" Window System");
  digitalWrite(2,1);
  delay(500);
  digitalWrite(2,0);
  delay(50);

}

void Rain(){
   int Value = analogRead(A3);
  Serial.print(" Rain_Value: ");
  Serial.print( Value);
  if (Value<350){
    myservo.write(180);
    Serial.print("Heavy rain led on");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("  Rain Detect");
    lcd.setCursor(0,1);
    lcd.print(" Closing Window ");
   // delay(5000);
    
  }
else {
  digitalWrite(led, LOW);
  myservo.write(90);
}
}

void gase(){
  gas_data=analogRead(A2);
  Serial.print("Gas:  ");
  Serial.print(gas_data);
 
  if(gas_data>32 && gas_data<38){
    if(gas_data>32 && gas_data<38){
    Serial.print("  Gas present");
    delay(1000);
  }
  }

else if (gas_data>500 && gas_data<1020){
  if(gas_data> 500&& gas_data<1020)
Serial.print("  Gas overflow");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("GAS Presents");
 
lcd.setCursor(0,1);
lcd.print("Gas Overflow");
digitalWrite(led,HIGH);
delay(2000);
    nsms();
     delay(8000);
delay(5000);
}
}
void temperature(){
  
  
temp_data = analogRead(A0);
  int t = temp_data * 0.221;
//Serial.print(" TEMP:      ");
  //Serial.println(t);
  delay(500);
  if(t>30){
    Serial.print("  HIGH TEMP");
    digitalWrite(led,HIGH);
 delay(5000);
    
  }
  else if (t<=29){
    Serial.println("  LOW TEMP");
     digitalWrite(led,LOW);
    }
}
void flame(){
  flamesensvalue=analogRead(flamepin); // reads analog data from flame sensor
if (flamesensvalue<=threshold) { // compares reading from flame sensor with the threshold value
digitalWrite(led,HIGH); //turns on led and buzzer

lcd.clear();
lcd.setCursor(0,0);
lcd.print("  Fire Detect");
lcd.setCursor(0,1);
lcd.print(" Check System");
delay(2000); //stops program for 1 second
nsms();
delay(8000);
delay(5000);
}
else{
digitalWrite(led,LOW); //turns led off led and buzzer

}
}

 void nsms()
{
  Serial.println("SMS loop entering");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("sms loop entering   ");
 gsm.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  gsm.println("AT+CMGS=\"+01626531530\"\r"); // Replace x with mobile number
  delay(1000);
  gsm.println("please check your device immediately sir fault was detected ");// The SMS text you want to send
  delay(100); 
  lcd.setCursor(0,1);
  lcd.print("SMS Sending");
   gsm.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  
  
} 
