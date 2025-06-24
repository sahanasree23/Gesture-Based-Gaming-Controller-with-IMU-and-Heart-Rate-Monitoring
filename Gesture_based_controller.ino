#include <Wire.h>
const int MPU = 0x68; // MPU6500 I2C address
int16_t AccX, AccY, AccZ, GyroX, GyroY, GyroZ;
const int pulsePin = A0; // Pin for heart rate sensor
int pulseValue; // Stores the heart rate sensor reading
void setup() {
 // Initialize MPU6500
 Wire.begin();
 Wire.beginTransmission(MPU);
 Wire.write(0x6B); // Wake up MPU6500
 Wire.write(0);
 Wire.endTransmission(true);
 // Initialize Serial Communication
 Serial.begin(9600); // Match with Python script baud rate
 // Initialize Pulse Sensor Pin
 pinMode(pulsePin, INPUT);
}
void loop() {
 // Retrieve MPU6500 Data
 Wire.beginTransmission(MPU);
 Wire.write(0x3B); // Starting with accelerometer registers
 Wire.endTransmission(false);
 Wire.requestFrom(MPU, 14, true); // Read accelerometer and gyroscope data
 AccX = Wire.read() << 8 | Wire.read();
 AccY = Wire.read() << 8 | Wire.read();
 AccZ = Wire.read() << 8 | Wire.read();
 GyroX = Wire.read() << 8 | Wire.read();
 GyroY = Wire.read() << 8 | Wire.read();
 GyroZ = Wire.read() << 8 | Wire.read();
 // Retrieve Heart Rate Sensor Data
 pulseValue = analogRead(pulsePin);
 // Send MPU6500 Data Over Serial
 Serial.print("AX:"); Serial.print(AccX);
 Serial.print("|AY:"); Serial.print(AccY);
 Serial.print("|AZ:"); Serial.print(AccZ);
 Serial.print("|GX:"); Serial.print(GyroX);
 Serial.print("|GY:"); Serial.print(GyroY);
 Serial.print("|GZ:"); Serial.print(GyroZ);
// Send Heart Rate Data Over Serial
 Serial.print("|HR:"); Serial.println(pulseValue);
delay(20); // Adjust for smooth performance
}
