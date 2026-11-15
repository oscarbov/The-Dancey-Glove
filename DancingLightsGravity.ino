#include "Modulino.h"
#define LED_PIN_R 10
#define LED_PIN_G 11
#define LED_PIN_B 12

ModulinoMovement movement;

float gx = 0, gy = 0, gz = 0;
bool  gOn = false;

const float alpha = 0.9;
const float M = 0.2;             
const float brightscale = 8.0;    

void setup() {
  Serial.begin(9600);
  Modulino.begin();
  movement.begin();

  pinMode(LED_PIN_R, OUTPUT);
  pinMode(LED_PIN_G, OUTPUT);
  pinMode(LED_PIN_B, OUTPUT);
}

void loop() {
  movement.update();

  float x = movement.getX();
  float y = movement.getY();
  float z = movement.getZ();

  if (!gOn) {
    gx = x; gy = y; gz = z;
    gOn = true;
  }

  /*Low pass filter*/
  gx = alpha * gx + (1 - alpha) * x;
  gy = alpha * gy + (1 - alpha) * y;
  gz = alpha * gz + (1 - alpha) * z;

  float lx = x - gx;
  float ly = y - gy;
  float lz = z - gz;

  float ax = abs(lx);
  float ay = abs(ly);
  float az = abs(lz);
  float xyzmax = max(max(ax, ay), az);

  Serial.print("Acceleration (w/o g): ");
  Serial.print(lx, 3); Serial.print(", ");
  Serial.print(ly, 3); Serial.print(", ");
  Serial.println(lz, 3);


  int r = 0, g = 0, b = 0;
  if (xyzmax > M) {
    int brightness = constrain((xyzmax / brightscale) * 255, 0, 255);
    if (xyzmax == ax)      r = brightness;
    else if (xyzmax == ay) g = brightness * 0.75;
    else                    b = brightness;
  }

  analogWrite(LED_PIN_R, r);
  analogWrite(LED_PIN_G, g);
  analogWrite(LED_PIN_B, b);

  delay(20);
}
