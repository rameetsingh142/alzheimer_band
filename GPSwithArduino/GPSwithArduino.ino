#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
const int buttonPin = D2;
int buttonState = 0;    
#include<Wire.h>
#define FIREBASE_HOST "band-76a7a.firebaseio.com"
#define FIREBASE_AUTH "kZSXgrvEVDKDv8TPzyaAjyXL7sXvf4lsC4HG233u"
#define WIFI_SSID "rameet"
#define WIFI_PASSWORD "0142PPpp"
SoftwareSerial gpsSerial(D7,D8);
TinyGPSPlus gps;
float lattitude,longitude;

void setup() {

 gpsSerial.begin(9600);
 Serial.begin(9600);
 WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED){ 
    Serial.print(".");
    delay(500);
  /* Clear display */
}
  
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Wire.begin();
 
Wire.write(0x6B); // PWR_MGMT_1 register
Wire.write(0); // set to zero (wakes up the MPU-6050)
Wire.endTransmission(true);
  pinMode(buttonPin, INPUT); 
  }

void loop()
{ 
  while (gpsSerial.available())
  {
    int data = gpsSerial.read();
    if (gps.encode(data))
    {
      lattitude = (gps.location.lat());
      longitude = (gps.location.lng());
      Serial.print ("lattitude: ");
      Serial.println (lattitude);
      Serial.print ("longitude: ");
      Serial.println (longitude);
        buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    
     Firebase.pushString("SoS","help me");}
        
          if(lattitude==0&&longitude==0)
      {  Serial.println("no location");
        
        
        }
        else{
     Firebase.pushFloat("lattitude",lattitude);
     Firebase.pushFloat("longitude",longitude);}
  
     delay(5000);
   
 
}
    }
      
}
