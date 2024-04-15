#define BLYNK_TEMPLATE_ID "TMPL23MQPrfNt"
#define BLYNK_TEMPLATE_NAME "e3tmad"
#define BLYNK_AUTH_TOKEN "y3x1LhhMD7qOs3vCRJP3HG7Xfu_d1XER"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "WE_834781";  // type your wifi name
char pass[] = "11c2c1a6";  // type your wifi password
 
#define PIR_SENSOR  4

BlynkTimer timer;
bool motionDetected = false;
unsigned long lastDetectionTime = 0;
const unsigned long detectionCooldown = 5000; // 5 seconds cooldown

void notifyOnTheft()
{
  int isTheftAlert = digitalRead(PIR_SENSOR);
  if (isTheftAlert == HIGH && !motionDetected && millis() - lastDetectionTime > detectionCooldown) {
    Serial.println("Motion Detected!");
    motionDetected = true;
    lastDetectionTime = millis();
    Blynk.logEvent("theft_alert", "Motion Detected!");
  }
  else if (isTheftAlert == LOW) {
    motionDetected = false;
  }
}

void setup(){
  pinMode(PIR_SENSOR, INPUT);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, notifyOnTheft); // Check motion every second
}

void loop(){
  Blynk.run();
  timer.run();
}
