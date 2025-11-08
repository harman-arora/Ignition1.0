#include <Wire.h>
#include <MPU6050.h>
#include <math.h>

MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while (1);
  }

  Serial.println("MPU6050 - Accelerometer + Gyroscope + Tilt + Acceleration Magnitude");
  delay(1000);
}

void loop() {
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
 // Convert raw data to real-world units
  float axg = ax / 16384.0;  // acceleration in g
  float ayg = ay / 16384.0;
  float azg = az / 16384.0;
  float gxds = gx / 131.0;   // rotation rate in deg/sec
  float gyds = gy / 131.0;
  float gzds = gz / 131.0;

  // Calculate total acceleration magnitude
  float totalAccel = sqrt(axg * axg + ayg * ayg + azg * azg);

  // Calculate tilt angles (in degrees)
  float pitch = atan2(axg, sqrt(ayg * ayg + azg * azg)) * 180 / PI;
  float roll  = atan2(ayg, sqrt(axg * axg + azg * azg)) * 180 / PI;

  // Print readings
  Serial.print("Accel (g): ");
  Serial.print(axg); Serial.print("\t");
  Serial.print(ayg); Serial.print("\t");
  Serial.print(azg); Serial.print("\t");

  Serial.print("Gyro (°/s): ");
  Serial.print(gxds); Serial.print("\t");
  Serial.print(gyds); Serial.print("\t");
  Serial.print(gzds); Serial.print("\t");

  Serial.print("Tilt (°): Pitch=");
  Serial.print(pitch); Serial.print("\tRoll=");
  Serial.print(roll); Serial.print("\t");

  Serial.print("Total Accel (g): ");
  Serial.println(totalAccel);

  delay(200);
}
