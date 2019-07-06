#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#include<Wire.h>
#define FIREBASE_HOST "band-2.firebaseio.com"
#define FIREBASE_AUTH "DiOzSzTAMloe8WE1OfdbH9EBgYSpqhObcuECj1es"
#define WIFI_SSID "Rameet"
#define WIFI_PASSWORD "0142PPpp"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET D5
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
}

void loop() {

   String ch=Firebase.getString("logs");
  buz=Firebase.getInt("num");
display.setTextSize(1);
    display.setTextColor(WHITE);
      display.setCursor(0,0);
      
        display.println(ch);
        Serial.println(ch);
          display.display();
          delay(1000);
          
  display.clearDisplay(); 
  if(buz==1){
   tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
   noTone(buzzer); 
      
  }
  
  
  
   if (Firebase.failed()) {
    Serial.print("setting /message failed:");
    Serial.println(Firebase.error());
    return;
  }
}
