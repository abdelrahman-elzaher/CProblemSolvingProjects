#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>
#include <WiFiClient.h> 
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#define interruptPin D8
#include <Ticker.h> //Ticker Library
//-----------------array buffer-----------------
String rasp_buffer[4]{"","","",""};
char id_medicine[2]={'0','0'};
//timer objects
Ticker try_connecting ;
Ticker medicine ;
//-------------------tcp socket for buzzering---------------------------
IPAddress server2(10,10,10,100); 
WiFiClient client;


//
int counter_medicine=0;
//SoftwareSerial NodeMCU(D4,D5);
//======================================WIFI CREDENTIALS for Hotspot==================================
const char* APssid = "server3";
const char* APpassword = "qwertyuiop"; 
 String ssid = "tesla";
 String password = "10@tesla.com";
int max_connection = 8;
String msgBody = "";
 int serms;
String BPM="";
String ID="2";
String Day="0";
int id;
char day;
int pbm2;
int volatile flag=0;
bool connecting=1;
//flag buzzer
bool flag_buzz=0;
//=============================================define the objects======================================
ESP8266WebServer server(80);
HTTPClient http;
//===============================================dafine the IP Address of the hotspot==================
IPAddress ip (10, 10, 10, 1);
IPAddress gateway (10, 10, 10, 1);
IPAddress subnet (255, 255, 255, 0);
//=========================================SETUP PART==================================================
void sendBPM(String ID,String BPM);
void getPrescribtion(String ID,String Day);
void ICACHE_RAM_ATTR test(){
  flag=1;


   detachInterrupt(D8);



attachInterrupt(digitalPinToInterrupt(interruptPin), test, RISING);
      
}
void send_buzzer()
{
flag_buzz=1;
medicine.detach();
    }
    
void trying()
{
  connecting=0;  
  }
  void new_pass()
  {
    if(WiFi.status()!=WL_CONNECTED)
    {
      Serial.print('x');
      
      }
      else
      Serial.print('o');

          try_connecting.detach ();

    
    }
bool wifi_password(String &ssid ,String &password)
{
  
   while(WiFi.status()!=WL_CONNECTED)
{

  if(connecting==0)
  {
   try_connecting.detach ();
   connecting=1;
  Serial.println("x ");
  return 0;
  }
  if(Serial.available()){
    String my_string=Serial.readString();
    ssid=my_string.substring(1,my_string.indexOf(','));
    password=my_string.substring(my_string.indexOf(',')+1,my_string.indexOf('\n'));
   
    //Serial.println(my_string);
   // Serial.println(ssid);
    //Serial.println(password);
    WiFi.begin(ssid,password);
    try_connecting.detach ();
      try_connecting.attach(7,trying); 


  }
  else
  {
    server.handleClient();
    }
}
  return 1;
  
  
  }

void setup() {
  
  pinMode(interruptPin, INPUT);
   
attachInterrupt(digitalPinToInterrupt(interruptPin), test, RISING);
 Serial.begin(115200);
  pinMode(D4,INPUT);
  pinMode(D5,OUTPUT);
  Serial.println("hello");
  WiFi.mode(WIFI_AP_STA);
  //Serial.println("Setup Access point");
  //Serial.println("Disconnect from any other modes");
  WiFi.disconnect();
  //Serial.println("stating access point with SSID" +String(ssid)); 
  WiFi.softAP(APssid, APpassword, 1, false, max_connection); 
  
  WiFi.softAPConfig(ip, gateway, subnet);
  IPAddress myIP = WiFi.softAPIP();
//  Serial.println(myIP);
    server.on("/",handleroot);
  server.on ( "/message", handleMessage );
  server.begin();
    //Serial.println("x");
  WiFi.begin(ssid,password);
  if(WiFi.status()!=WL_CONNECTED)
  {
    while(!wifi_password(ssid,password));
    Serial.print("o");
    }
    else
    {  
      Serial.print("o");
      }
 
//Serial.println();
//Serial.println("connected sucessfully");
//Serial.print("IP of ESP is");
//Serial.println(WiFi.localIP());

  flag=0;
}
//=====================================handle root page================================================
void handleroot(){

  server.send(200,"text/plain","hello");
}
//===================================handle massege===========================================

void handleMessage(){
  
  // Check for valid request with a message (in the expected format)
  if(server.hasArg("AM")){
    //digitalWrite(D5, HIGH);
    Serial.println("Message received from fall sensor:");
    msgBody = server.arg("AM");
    Serial.println(msgBody);
 Serial.print(msgBody);
    sendBPM(ID,msgBody);   

    // Generate and send back an acknowledgement response
    msgBody = "Hi, this is the Server. I got your message saying : " + msgBody;
    Serial.print(msgBody);
    server.send ( 200, "text/plain", msgBody);
    //digitalWrite(D5, LOW);
  }
  // handle messages with invalid bodies
  else {
    Serial.println("Invalid message received");
    server.send ( 200, "text/plain", "Recevied a message without a body!");
  }

  Serial.println("-------------------------------------");
}

// handle invalid requests
void handleNotFound() {
  server.send ( 404, "text/plain", "404, No resource found");
}
//String read_rasppery()
//{
  
  
  //}
//======================================================vibration================================================
/*void handlevibration() {
  if(Serial.available())
  {  serms=Serial.read();
  if(serms==1)
  server.send ( 200, "text/plain", "vibration");}
}*/
//==============================================LOOP===================================================
void loop (){
  if(Serial.available()<=0)
  {
 
     server.handleClient();  
     }
     else       
     {//Serial.println("hamada");
      String buffering="";
     
      while(Serial.available()>0)
     {
      buffering=Serial.readStringUntil('\n');
      
      if(buffering.substring(0,1)=="W")
      {
        rasp_buffer[0]=buffering;        
        
        }
        else if(buffering.substring(0,1)=="M")
        {
          rasp_buffer[1]=buffering;
        }
        else if( buffering.substring(0,1)=="T")
          {
            rasp_buffer[2]=buffering;
            } 
             else if( buffering.substring(0,1)=="B")
          {
            rasp_buffer[3]=buffering;
            }   
            } 
      
    //we have put it in buffer now we check the condition 
    if(rasp_buffer[0].substring(0,1)=="W")
    {    ssid=rasp_buffer[0].substring(1,rasp_buffer[0].indexOf(','));
    password=rasp_buffer[0].substring(rasp_buffer[0].indexOf(',')+1);
   
 
    WiFi.begin(ssid,password);
    try_connecting.detach ();
      try_connecting.attach(7,new_pass); 



      
      rasp_buffer[0]="";
      }
      if(rasp_buffer[1].substring(0,1)=="M")
      {
        if(WiFi.status()!=WL_CONNECTED)
        {
          delay(1000);
        Serial.print("x");
        }
        else{
        getPrescribtion("2","0");
           rasp_buffer[1]="";}
        
        }
        if(rasp_buffer[2].substring(0,1)=="T")
        {
           if(WiFi.status()!=WL_CONNECTED)
           {
            Serial.println("x");
            
            
            }
            else
             Serial.println("o");
             
            rasp_buffer[2]="";
            
          }
          if(rasp_buffer[3].substring(0,1)=="B")
        {
        if(rasp_buffer[3].substring(1,2)=="1")
        {Serial.print("buzzer");
          medicine.attach(3,send_buzzer);
        while(flag_buzz==0){
 
     server.handleClient();             
     if (client.connect(server2, 80)) {
     
      Serial.println("connected");
      // Make a HTTP request:
      client.print(1);
      flag_buzz=1;
      }
          
          }
        flag_buzz=0;
rasp_buffer[3]="";
    }
      }
    
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     }

          
          
        
     
           
          
      
      
      
      
      
      
      
      
      
      /*  int e=0;

  Serial.println("New interrupt");
  if(Serial.available()>0)
  {id=Serial.read();
  pbm2=Serial.read();
  Serial.println(id);
  sendBPM(String(id),String(pbm2));
    //Serial.print("d=");
    //Serial.println(id);
    
    //Serial.print("day=");
    //Serial.println(day-1);
    
//getPrescribtion("2","0");
    //Serial.println(Serial.read());
    //day=Serial.read();
    
    //*/

     
}
void sendBPM(String ID,String BPM){
HTTPClient http;
Serial.println("id ="+ID);

Serial.println("BPM ="+BPM);
//Declare object of class HTTPClient
String uploadlink="http://iotnursing.azurewebsites.net/myapp/sensorsupload.php?ID="+ID+"&BPM="+BPM;
http.begin(uploadlink);
int httpcode;
a : httpcode = http.GET();//Send the request
  if(httpcode!=200)
  { goto a;    //untill receive ok
    }
  http.end(); 
   //Serial.println("*****************");
  Serial.println("Data Base Updated");//Close connectionx
}

void getPrescribtion(String ID,String Day){
 // int pervioustime=millis();
  //Serial.println("function of ");
HTTPClient http;    //Declare object of class HTTPClient
  String  getlink;
  getlink = "http://iotnursing.azurewebsites.net/myapp/returnprescription.php?ID="+ID+"&Day="+Day;
  http.begin(getlink);     //Specify request destination
 b: int httpCode = http.GET();            //Send the request
  String payload = http.getString();//Get the response payload
  //Serial.println(httpCode);   //Print HTTP return code
 if(httpCode!=200)
  { goto b;
    } 
    //Serial.println(sizeof(payload));


  //Serial.println(payload);
  Serial.println(payload);
  
//json parsifier

//const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(5) + 80;
/*DynamicJsonBuffer jsonBuffer(capacity);
JsonArray& root = jsonBuffer.parseArray(payload);
JsonObject& root_0 = root[0];
const char* MedicineName = root_0["MedicineName"]; // "Medicine1"
const char* BoxNumber = root_0["BoxNumber"]; // "1"
const char* Time = root_0["Time"]; // "06:30:41"
const char* Dose = root_0["Dose"]; // "2"
const char* Repeating = root_0["Repeating"]; // "6"
    Serial.println(MedicineName);
    Serial.println(BoxNumber);
        Serial.println(Time);
    Serial.println(Dose);
    Serial.println(Repeating);*/
http.end();
}
