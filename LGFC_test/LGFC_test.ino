#define LGFX_USE_V1
#include "LGFX_ESP32.hpp"

static LGFX lcd;
static LGFX_Sprite canvas(&lcd);       //main
static LGFX_Sprite eye(&canvas);       
static LGFX_Sprite eyebrow(&eye);

static int eyeR = 50;
static int irisOuterR = 25;
static int irisInnterR = 15;

static int buf = 2;
static int cX = eyeR + buf;
static int cY = eyeR + buf;
static int eyebrowH = eyeR;

static int scale = 2;

int drawX = 240 / 2 - cX * scale;
int drawY = 320 / 2 - cY * scale;

void setup(void)
{
  lcd.init();
  
  canvas.createSprite(cX *2 * scale, cY * 2 * scale);
  eye.createSprite(cX *2,cY *2);  
  eyebrow.createSprite(cX *2,cY *2);
  
  canvas.fillScreen(lcd.color888(10,10,10));
  eye.fillScreen(lcd.color888(10,10,10));
  //eyebrow.fillScreen(lcd.color888(10,10,10));
  
  lcd.startWrite();
}

void eyeBrow(){
  eyebrow.fillScreen(TFT_BLUE);
  eyebrow.drawCircle(cX,cY,eyeR, TFT_BLACK);
  
  float s = sin(millis()/100);
  eyebrow.drawBezier(cX - eyeR, cY, cX, cY + eyebrowH *s, cX + eyeR, cY);
  eyebrow.drawBezier(cX - eyeR, cY, cX, cY - eyebrowH,    cX + eyeR, cY);
  
  eyebrow.floodFill(cX, 5,     TFT_BLACK);
  eyebrow.floodFill(cX, cY -5, TFT_BLACK); 
}


void drawEye(){
  eye.fillScreen(TFT_BLACK);
  eye.fillCircle(cX,cY,eyeR, TFT_WHITE);
  eye.fillCircle(cX,cY,irisOuterR, lcd.color888(130,0,0));
  eye.fillCircle(cX,cY,irisInnterR, TFT_BLACK);
}

void loop(void)
{
  drawEye();
  eyeBrow();
  
  eyebrow.pushSprite(0,0,TFT_BLUE);
  eye.pushRotateZoomWithAA(cX, cY,0,scale,scale);
  canvas.pushSprite(drawX, drawY);
  
  lcd.display();
}
