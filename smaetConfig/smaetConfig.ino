#include "WiFi.h"
void setup() {
  Serial.begin(115200); //< シリアルの初期化

  // WiFI を AP + STA モードにする
  WiFi.mode(WIFI_AP_STA);
  WiFi.beginSmartConfig(); //< SmartConfigの初期化

  // スマホからのアクセスを待つ
  Serial.println("Waiting for SmartConfig.");
  while (!WiFi.smartConfigDone()) {
    delay(500);
    Serial.print(".");
  }
  // スマホからSSIDとパスワードが送られてきた
  Serial.println("SmartConfig received.");

  // WiFiに接続
  Serial.println("Waiting for WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // 接続成功
  Serial.println("WiFi Connected.");
}

void loop() {
}
