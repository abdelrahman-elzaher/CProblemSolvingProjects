#include <Wire.h>
#include "MAX30105.h"
#include <LiquidCrystal.h>
#include "heartRate.h"
#include <SoftwareSerial.h>

MAX30105 particleSensor;
const unsigned long thirtyseconds=30000;
unsigned long perviousTime=0;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred
float beatsPerMinute;
int beatAvg;
const int Up = 14;
const int Down =10;
const int Submit =13;
int ID=0;
String reading="";
int count=1;
double avered = 0; double aveir = 0;
double sumirrms = 0;
double sumredrms = 0;
int i = 0;
int Num = 100;
double ESpO2 = 95.0;//initial value of estimated SpO2
double FSpO2 = 0.7; //filter factor for estimated SpO2
double frate = 0.95; //low pass filter for IR/red LED value to eliminate AC component
#define TIMETOBOOT 3000
#define SAMPLING 5
#define FINGER_ON 30000 // if red signal is lower than this , it indicates your finger is not on the sensor
#define MINIMUM_SPO2 80.0


#define SCALE 88.0  
SoftwareSerial espserial(17,16); // RX | TX
 void checking(const char * command ,String expected)
  {   espserial.write(command); 

    String buffe = espserial.readString();
     int counter=0;
  while((buffe.indexOf(expected))==-1&&counter<=5)
  {
    delay(4000);
    espserial.write(command); 
  buffe = espserial.readString();
  counter++;
    }
    Serial.println("Sucess of"+buffe);
    
    }
     
     void checking(const char * command ,String expected,String expected2)
  {   espserial.write(command); 

    String buffe = espserial.readString();
     int counter=0;
  while(((buffe.indexOf(expected)==-1)&&(buffe.indexOf(expected2)==-1))&&counter<=5)
  {buffe="";
    delay(4000);
    espserial.write(command); 
  buffe = espserial.readString();
  counter++;
 
    }
    Serial.println("Sucess of"+buffe);
    
    }
    void esptest(){
  checking("AT\r\n","OK");
}
void buzzersetup(){
  checking("AT+CWMODE=3\r\n","OK","no change");
     espserial.write("AT+CIFSR\r\n");
  reading = espserial.readString();
  Serial.print(reading);
 // delay(3000);
        checking("AT+CIPMUX=1\r\n","OK");
        checking("AT+CIPSERVER=1,80\r\n","OK");


}
void connecttoLocalNode(){
  checking("AT+CWJAP=\"server3\",\"qwertyuiop\"\r\n","OK");
}





void sendBPM(int ID ,int BPM){
if(count==1){
  char p[20];
    checking("AT+CIPSTART=0,\"TCP\",\"10.10.10.1\",80\r\n","OK");
  sprintf(p,"AT+CIPSEND=0,%d\r\n",int(strlen("GET /message?BPM=&ID= HTTP/1.1\r\n Host:10.10.10.1\r\nConnection: Keep-alive\r\n")+(String(BPM)).length()+(String(ID)).length()));
  espserial.write(p);
   reading = espserial.readString();
Serial.print(reading);
  sprintf(p,"BPM=%d&ID=%d",BPM,ID);
  
 espserial.write("GET /message?");
 espserial.write(p);
 espserial.write(" HTTP/1.1\r\n Host:10.10.10.1\r\nConnection: Keep-alive\r\n");
 //espserial.write("GET /message?temp=50 HTTP/1.1\r\n Host:10.10.10.1\r\nConnection: Keep-alive\r\n");
 reading = espserial.readString();
 Serial.print(reading);

 while(reading.indexOf("OK")==-1)
 {delay(2000);
     checking("AT+CIPSTART=0,\"TCP\",\"10.10.10.1\",80\r\n","OK");

  sprintf(p,"AT+CIPSEND=0,%d\r\n",int(strlen("GET /message?BPM=&ID= HTTP/1.1\r\n Host:10.10.10.1\r\nConnection: Keep-alive\r\n")+(String(BPM)).length()+(String(ID)).length()));
  espserial.write(p);
  sprintf(p,"BPM=%d&ID=%d",BPM,ID);
  reading = espserial.readString();
  Serial.print(reading);

 espserial.write("GET /message?");
 espserial.write(p);
 espserial.write(" HTTP/1.1\r\n Host:10.10.10.1\r\nConnection: Keep-alive\r\n");
 reading = espserial.readString();
  
  
  
  }
espserial.write("AT+CIPCLOSE=0\r\n");
  reading = espserial.readString();
  Serial.print(reading);
count=0;

}
else
count=1;
}
void sendSPO2(int ID ,double SPO2){
int spo2=round(SPO2);
Serial.println(spo2);
if(count==1){
  char p[20];
    checking("AT+CIPSTART=0,\"TCP\",\"10.10.10.1\",80\r\n","OK");

  sprintf(p,"AT+CIPSEND=0,%d\r\n",int(strlen("GET /message?SPO2=&ID= HTTP/1.1\r\n Host:10.10.10.1\r\nConnection: Keep-alive\r\n")+(String(spo2)).length()+(String(ID)).length()));
  espserial.write(p);
   reading = espserial.readString();
Serial.print(reading);
  sprintf(p,"SPO2=%d&ID=%d",spo2,ID);
  
 espserial.write("GET /message?");
 espserial.write(p);
 espserial.write(" HTTP/1.1\r\n Host:10.10.10.1\r\nConnection: Keep-alive\r\n");
 reading = espserial.readString();
 Serial.print(reading);

 while(reading.indexOf("OK")==-1)
 {delay(2000);
  checking("AT+CIPSTART=0,\"TCP\",\"10.10.10.1\",80\r\n","OK");
  sprintf(p,"AT+CIPSEND=0,%d\r\n",int(strlen("GET /message?SPO2=&ID= HTTP/1.1\r\n Host:10.10.10.1\r\nConnection: Keep-alive\r\n")+(String(spo2)).length()+(String(ID)).length()));
  espserial.write(p);
  sprintf(p,"SPO2=%d&ID=%d",spo2,ID);
  reading = espserial.readString();
  Serial.print(reading);

 espserial.write("GET /message?");
 espserial.write(p);
 espserial.write(" HTTP/1.1\r\n Host:10.10.10.1\r\nConnection: Keep-alive\r\n");
 //espserial.write("GET /message?temp=50 HTTP/1.1\r\n Host:10.10.10.1\r\nConnection: Keep-alive\r\n");
 reading = espserial.readString();
  }
espserial.write("AT+CIPCLOSE=0\r\n");
reading = espserial.readString();
count=0;

}
else
count=1;
}
    

void setup()
{espserial.begin(9600);
  Serial.begin(9600);

  esptest();
connecttoLocalNode();
  buzzersetup();
  pinMode(Up,INPUT);
pinMode(Down,INPUT);
pinMode(Submit,INPUT);
  Serial.println("Initializing...");
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Enter Your ID");
  lcd.setCursor(0, 1);
    lcd.print(String(ID));  
    while(digitalRead(Submit)==HIGH){
  lcd.setCursor(0, 1);
   lcd.print(String(ID));
   if(digitalRead(Up)==LOW){
    ID=ID+1;
    Serial.println(ID);
    delay(400);
   }
   if(digitalRead(Down)==LOW){
    ID=ID-1;
        Serial.println(ID);
    delay(400);
   }
    }
    delay(200);
Serial.println("ID="+String(ID));
lcd.clear();

  // Initialize sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }
  Serial.println("Place your index finger on the sensor with steady pressure.");
byte ledBrightness = 0x7F; //Options: 0=Off to 255=50mA
  byte sampleAverage = 4; //Options: 1, 2, 4, 8, 16, 32
  byte ledMode = 2; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
  //Options: 1 = IR only, 2 = Red + IR on MH-ET LIVE MAX30102 board
  int sampleRate = 200; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
  int pulseWidth = 411; //Options: 69, 118, 215, 411
  int adcRange = 16384; //Options: 2048, 4096, 8192, 16384
lcd.clear();
  lcd.setCursor(0, 0);
lcd.print("Put your finger");
lcd.setCursor(0, 1);
lcd.print("for 30s");
//particleSensor.setup(); //Configure sensor with default settings
  //particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  //particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED
  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings

}

void loop()
{
    lcd.setCursor(0, 0);
    int counter=0;
  long irValue = particleSensor.getIR();
/*while (irValue < 50000)
{
  irValue = particleSensor.getIR();
  if (espserial.available()>0)
  {
    if (espserial.available()>0){
  reading = espserial.readString();
  Serial.print(reading);
 if(reading.indexOf("1:1"))
 {
 Serial.print("buzzer");
 digitalWrite(8,HIGH);
}
}
    
    
    }
}*/
 
  //particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange);
 //raw SpO2 before low pass filtered
 //Check the sensor
  //currentTime = millis();
 //perviousTime=currentTime;
 int countee=0;
 
  while (1) {
    double spo2_average=0;

    long irValue = particleSensor.getIR();
while (irValue < 50000)
{
    irValue = particleSensor.getIR();
    Serial.print("IR=");
 Serial.println(irValue);
}
    countee++;
    if( countee==101)
    {break;}
      uint32_t ir, red , green;
  double fred, fir;
  double SpO2 = 0;
      particleSensor.check();
    //Serial.println("kkkkkkkkkkkkkkkkkk");
  while (particleSensor.available()) {
   red = particleSensor.getFIFORed(); 
    ir = particleSensor.getFIFOIR();  
    i++;
    fred = (double)red;
    fir = (double)ir;
    avered = avered * frate + (double)red * (1.0 - frate);//average red level by low pass filter
    aveir = aveir * frate + (double)ir * (1.0 - frate); //average IR level by low pass filter
    sumredrms += (fred - avered) * (fred - avered); //square sum of alternate component of red level
    sumirrms += (fir - aveir) * (fir - aveir);
   // Serial.println(i);
    //Serial.println(i%Num);
 if ((i % SAMPLING) == 0) {//slow down graph plotting speed for arduino Serial plotter by thin out
      if ( millis() > TIMETOBOOT) {
           if (ir < FINGER_ON) ESpO2 = MINIMUM_SPO2; //indicator for finger detached
      
      }
    }
    if ((i % Num) == 0) {
      double R = (sqrt(sumredrms) / avered) / (sqrt(sumirrms) / aveir);
      // Serial.println(R);
      SpO2 = -15.3 * (R - 0.6) + 100; //http://ww1.microchip.com/downloads/jp/AppNotes/00001525B_JP.pdf
      ESpO2 = FSpO2 * ESpO2 + (1.0 - FSpO2) * SpO2+3;//low pass filter
      Serial.print("spo2=");
  Serial.println(ESpO2);
      sumredrms = 0.0; sumirrms = 0.0; i = 0;
      break;
    }
  particleSensor.nextSample();
  }
    spo2_average+=ESpO2;
    spo2_average/=counter;
  
  //Serial.print(", Spo2Avg=");
  //Serial.print(spo2_average);
//currentTime = millis();  
  }
   
      Serial.println("finger released");
delay(3000);
Serial.println(ESpO2);
sendSPO2(ID,ESpO2);
  particleSensor.setup(); //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0);
  
    long ireValue = particleSensor.getIR();
while (ireValue < 50000)
{
    ireValue = particleSensor.getIR();
    Serial.print("IR=");
 Serial.println(ireValue);
}
unsigned long currentTime = millis();
 perviousTime=currentTime;
 //Serial.print("PreviousTime=");
 //Serial.print(perviousTime);
 //Serial.print(",CurrentTime=");
 //Serial.print(currentTime);
 //Serial.println();
while (currentTime - perviousTime <= thirtyseconds) {
     ireValue = particleSensor.getIR();
     
  if (checkForBeat(ireValue) == true)
  {
    //We sensed a beat!
    long delta = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);

    if (beatsPerMinute < 255 && beatsPerMinute > 40)
    {
      rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
      rateSpot %= RATE_SIZE; //Wrap variable

      //Take average of readings
      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
    }
  }
  
  Serial.print("IR=");
  Serial.print(ireValue);
  Serial.print(", BPM=");
  Serial.print(beatsPerMinute);
  Serial.print(", Avg BPM=");
  Serial.print(beatAvg);
 Serial.println();
  //if (irValue < 50000)
    //Serial.print(" No finger?");
currentTime = millis();
}
Serial.println("finger released");
delay(3000);
Serial.println(beatAvg);
lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("BPM="+String(beatAvg));
  

 if (espserial.available()>0)
  {
    if (espserial.available()>0){
  reading = espserial.readString();
  Serial.print(reading);
 if(reading.indexOf("1:1"))
 {
 Serial.print("buzzer");
 digitalWrite(8,HIGH);
}
}   
    }
  sendBPM(ID,beatAvg);
  beatAvg=0;
  beatsPerMinute=0;
}
