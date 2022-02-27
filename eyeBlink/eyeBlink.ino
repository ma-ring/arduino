#define LGFX_USE_V1
#include "LGFX_ESP32.hpp"
#include "BluetoothSerial.h"

static LGFX lcd;
static LGFX_Sprite canvas(&lcd);       //main
static LGFX_Sprite eye(&canvas);       
static LGFX_Sprite eyebrow(&eye);

static int eyeR = 100;
static int irisOuterR = 60;
static int irisInnterR = 40;

static int buf = 5;
static int cX = eyeR + buf;
static int cY = eyeR + buf;
static int eyebrowH = eyeR;

int drawX = 240 / 2 - cX;
int drawY = 320 / 2 - cY;

int oX,oY,iX,iY;
float bs;

BluetoothSerial SerialBT;

void setup(void)
{
  SerialBT.begin("EYE BLINK"); 
  oX = cX; oY = cY;
  iX = cX; iY = cY;
  bs = 1;
  
  lcd.init();
  
  canvas.createSprite(cX *2, cY * 2);
  eye.createSprite(cX *2,cY * 2);  
  eyebrow.createSprite(cX,cY);
  
  lcd.fillScreen(lcd.color888(50,50,50));
  canvas.fillScreen(lcd.color888(30,30,30));
  eye.fillScreen(lcd.color888(30,30,30));
  //eyebrow.fillScreen(lcd.color888(10,10,10));
  
  lcd.startWrite();

   xTaskCreatePinnedToCore(drawEye,     "Task0", 4096, NULL, 1, NULL, 0);
   xTaskCreatePinnedToCore(serialLoop,  "Task1", 4096, NULL, 1, NULL, 1);
}

void eyeBrow(float s){
  eyebrow.fillScreen(TFT_BLUE);
  eyebrow.drawCircle(cX/2,cY/2,eyeR/2, TFT_BLACK);

  //float s = sin(millis()/100);
  eyebrow.drawBezier((cX - eyeR)/2, cY/2, cX/2, (cY + eyebrowH *s)/2,(cX + eyeR)/2, cY/2);
  eyebrow.drawBezier((cX - eyeR)/2, cY/2, cX/2, (cY - eyebrowH)/2,   (cX + eyeR)/2, cY/2);
  
  eyebrow.floodFill(cX/2, 10 / 2,    TFT_BLACK);
  eyebrow.floodFill(cX/2, cY -10 /2, TFT_BLACK); 
}

void baseEye(int ix,int iy, int ox, int oy){
  eye.fillScreen(lcd.color888(50,50,50));
  eye.fillCircle(cX,cY,eyeR-2, TFT_WHITE);
  eye.fillCircle(ox,oy,irisOuterR, lcd.color888(130,0,0));
  eye.fillCircle(ix,iy,irisInnterR, TFT_BLACK);
}

void serialLoop(void* arg){
  while(1){
    if (SerialBT.available()) {}
  }
}

void drawEye(void* arg)
{
  while(1){
    bs = sin(millis()/100);
  
    baseEye(iX,iY,oX,oY);
    eyeBrow(bs);
    
    eyebrow.pushRotateZoomWithAA(cX, cY,0,2,2,TFT_BLUE);
    eye.pushSprite(0, 0);
    canvas.pushSprite(drawX, drawY);
    
    lcd.display();
  }
  
}

void loop(){
}
