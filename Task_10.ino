#include <Wire.h>


const int MPU6050_ADDR = 0x68;
const int GYRO_ZOUT_H = 0x47;
const int PWR_MGMT_1 = 0x6B;


int16_t gyroX;
float yawAngle = 0.0;
float gyroScaleFactor = 131.0;  
unsigned long lastTime;

void setup() {
  Wire.begin();
  Serial.begin(9600);


  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(PWR_MGMT_1);
  Wire.write(0);  
  Wire.endTransmission(true);

  
  lastTime = millis();
}

void loop() {

  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(GYRO_ZOUT_H);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADDR, 6, true);

  gyroZ = Wire.read() << 8 | Wire.read();
  

  unsigned long currentTime = millis();
  float time_difference = (currentTime - lastTime) / 1000.0;  // Convert ms to seconds
  lastTime = currentTime;


  float gyroZrate = (float)gyroZ / gyroScaleFactor;  // Convert to degrees/sec
  yawAngle += gyroZrate * time_difference;  


  Serial.print("Yaw: ");
  Serial.println(yawAngle);

  delay(100);  
}
