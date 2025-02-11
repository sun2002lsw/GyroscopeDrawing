#include "MPU9250.h"
#include <Mouse.h>

MPU9250 mpu;                           // gyroscope
const int LED = 17;                    // led pin number for leonardo micro
const uint32_t CHECK_INTERVAL = 100;   // interval for gyroscope check
const double MOUSE_SENSITIVITY_X = 30; // mouse move sensitivity X pos
const double MOUSE_SENSITIVITY_Y = 20; // mouse move sensitivity Y pos

void setup() {
  Serial.begin(115200);
  Mouse.begin();
  Wire.begin();
  delay(2000);
  
  // setup MPU
  bool setupFailed = !mpu.setup(0x68);
  while (setupFailed) {
    Serial.println("MPU setup failed");
    delay(5000);
  }

  // consume buffer for 3 seconds
  uint32_t setupTime = millis();
  while (millis() < setupTime + 3000) {
    mpu.update();
  }

  // turn on LED
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
}

void loop() {
  if (!mpu.update()) {
    return;
  }

  // check for every CHECK_INTERVAL ms
  static uint32_t prevCheckTime;
  uint32_t currentTime = millis();
  if (currentTime < prevCheckTime + CHECK_INTERVAL) {
    return;
  }
  prevCheckTime = currentTime;

  // check for 2D mouse movement
  double curX = mpu.getYaw();
  double curY = mpu.getRoll() * cos(mpu.getPitch() * PI / 180.0);
  static double oldX = curX;
  static double oldY = curY;

  double moveX = curX - oldX; // minus for left, plus for right
  double moveY = oldY - curY; // minus for down, plus for up
  Mouse.move(moveX * MOUSE_SENSITIVITY_X, moveY * MOUSE_SENSITIVITY_Y, 0);

  oldX = curX;
  oldY = curY;
}
