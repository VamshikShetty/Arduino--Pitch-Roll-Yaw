#include<Adxl345_Lib.h>
#include <L3g4200d_Lib.h>
#include<Hmc5883l_Lib.h>
#include<Wire.h>
 
ADXL345 adxl;
L3G4200D gyro3;
HMC5883L mag;
//for uno

gyroValues gy;
AccelerometerVal ac;
AccelerometerRotation accelRot;
magValues ma;


double i,t,tim,dt;
float sumx=0,sumy=0,sumz=0,zdegree,magZset;

void setup()
{ 
 delay(400); 
 Wire.begin();
 Serial.begin(250000);

 //adxl345
 adxl.ADXL345_set();
 adxl.accel_constant(263.00,250.32,255.50,260.8,232.3950,268.52);
 adxl.hardwareOffset(-2, 0, 0);

 //l3g4200d
 gyro3.enableDefault();
 while(!gyro3.check());
 Serial.println("gyro ready ");
 delay(200);
 float dcount=7.5; 
 gyroValues sum,off;
 for(i=0;i<4;i++)
 {
  dcount=dcount+2.5;
  sum = gyro3.printCalibrationValues(2000,1-i/dcount);
  off = gyro3.offset();
  
  axisprint(sum.x,sum.y,sum.z,"   sum: ");
  axisprint(off.x,off.y,off.z,"   off: ");  
  Serial.println("\n");
 }
 

  //hmc588l
  Serial.println(mag.check());
  mag.configs(-24.5,-63); //(max-min)/2
  mag.mode();
  ma=mag.magScaled();
  magZset = atan2(ma.z, ma.x);
  if(magZset<0){magZset=magZset+2*3.14;}

  tim=t=micros(); 
}



void loop()
{
  dt=(micros()-t)/1000000;  t=micros();


  //adxl
  ac = adxl.scalevalue(); 
  //axisprint(ac.XAxis,ac.YAxis,ac.ZAxis,"  ac: ");  
  accelRot = adxl.accel_RollPitch(ac);


  //gyro
  gy=gyro3.degree(dt);
  //axisprint(gy.x,gy.y,gy.z,"   gy: ");
  

  
  //mag
  ma=mag.magScaled();
  //axisprint(ma.x,ma.y,ma.z,"mag:  ");
  zdegree=atan2(ma.z, ma.x);  
  if(zdegree<0){zdegree=zdegree+2*3.14;}
  float magYaw =(zdegree-magZset)*180/3.14;
  if(magYaw<0){magYaw=magYaw+360;}

  
  
  //filter
  sumx = compFilter(sumx + gy.x, accelRot.pitch, 0.95);
  sumy = compFilter(sumy + gy.y,  accelRot.roll, 0.95);
  sumz = compFilter(sumz + gy.z, magYaw, 0.2);
  
  
  
  axisprint(sumx,sumy,sumz," sum: ");
  Serial.print("    time: ");
  Serial.print((t-tim)/1000000,7);
  Serial.print("    dt: ");
  Serial.println(dt,7);
}

void axisprint(double x,double y,double z,String str)
{
  Serial.print(str);
  Serial.print(" X: ");
  Serial.print(x,3);
  Serial.print("    Y: ");
  Serial.print(y,3);
  Serial.print("    Z: ");
  Serial.print(z,3);
  
}

double compFilter(double f,double s,float fg)
{
  return fg*f+(1-fg)*s;
}

