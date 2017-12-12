#include<Adxl345_Lib.h>
#include<Wire.h>
 
ADXL345 adxl;
//for uno
void setup()
{ 
 Wire.begin();
 Serial.begin(250000);
 adxl.ADXL345_set();
 adxl.accel_constant(263.00,250.32,255.50,260.8,232.3950,268.52);
 adxl.hardwareOffset(-2, 0, 0);
 delay(500);
}

void loop()
{
  AccelerometerVal ac = adxl.scalevalue(); 
     
  Serial.print(ac.XAxis);Serial.print("       ");
  Serial.print(ac.YAxis);Serial.print("       ");
  Serial.print(ac.ZAxis);

  AccelerometerRotation accelRot = adxl.accel_RollPitch(ac);
  Serial.print("      pitch: ");
  Serial.print(accelRot.pitch);
  Serial.print("  roll:  ");
  Serial.println(accelRot.roll);
}
