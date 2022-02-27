#include <WiFi.h>
#include <WiFiUDP.h>
#include "SPI.h"
#include "Adafruit_ILI9341.h"


#define TFT_DC 16
#define TFT_CS 17

const char ssid[] = "mhWifi_2.4GHz";
const char pass[] = "mhhomewifi884";
static WiFiUDP wifiUdp;
static const char *ip = "";
static const int port = 5000;

IPAddress remoteIP(192,168,11,11);
int remotePort = 5000;
static int dataLen = 4;

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

static void WiFi_setup(){
  static const int localPort = 5000;
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED){
    Serial.println("connecting.....");
    delay(500);
  }
  Serial.println("WiFi Connected");
  wifiUdp.begin(localPort);

  
  wifiUdp.beginPacket(remoteIP, remotePort);
  wifiUdp.write('1');
  wifiUdp.endPacket();  
  
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  Serial.println("START");
  WiFi_setup();

  //LCD
  tft.begin();
  //pinMode(TFT_BACKLIGHT_PIN,OUTPUT);
  //digitalWrite(TFT_BACKLIGHT_PIN,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //WiFi
  char i[4];

  int packet = wifiUdp.parsePacket();
  if(packet > 0){
    
    wifiUdp.read(i,4);
    //remoteIP = wifiUdp.remoteIP();
    //remotePort = wifiUdp.remotePort();

    Serial.println(packet);
  }

  //LCD
  tft.fillScreen(ILI9341_BLACK);
  yield();
  for(int y = 0; y < 200; y++){
    tft.drawFastVLine(y,0,200,ILI9341_YELLOW);
  }

  delay(100);
  
}
