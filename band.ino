#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#include<Wire.h>
#define FIREBASE_HOST "band-76a7a.firebaseio.com"
#define FIREBASE_AUTH "kZSXgrvEVDKDv8TPzyaAjyXL7sXvf4lsC4HG233u"
#define WIFI_SSID "rameet"
#define WIFI_PASSWORD "0142PPpp"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET D5
#define motor D6
#define motor2 D7
#define motor3 D8
int buz=0;
String ch;
const int buzzer = D3;


Adafruit_SSD1306 display(OLED_RESET);



void setup() {
  Serial.begin(9600);
  // connect to wifi.
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
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C); /* Initialize display with address 0x3C */
  display.clearDisplay(); 
  pinMode(buzzer, OUTPUT);
   pinMode(motor,OUTPUT);
    pinMode(motor2,OUTPUT); 
    pinMode(motor3,OUTPUT);
}

void loop() {

  
   String ch=Firebase.getString("logs");
  buz=Firebase.getInt("num");
display.setTextSize(2);
    display.setTextColor(WHITE);
      display.setCursor(0,0);
      
        display.println(ch);
        Serial.println(ch);
          display.display();
          delay(1000);
          
  display.clearDisplay(); 
  if(buz==1){
   tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(500);        // ...for 1 sec
   noTone(buzzer); 
    
  digitalWrite(motor,HIGH);
  delay(1000);
    digitalWrite(motor,LOW);
     digitalWrite(motor2,HIGH);
  delay(1000);
    digitalWrite(motor2,LOW);
     digitalWrite(motor3,HIGH);
  delay(1000);
    digitalWrite(motor3,LOW);
    
      
  }
  
  
  
   if (Firebase.failed()) {
    Serial.print("setting /message failed:");
    Serial.println(Firebase.error());
    return;
  }
}
