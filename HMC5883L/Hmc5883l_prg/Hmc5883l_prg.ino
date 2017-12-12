#include<Hmc5883l_Lib.h>
#include<Wire.h>
 
HMC5883L mag;

magValues ma;
float zdeg,zdegree;


void setup() {
  Wire.begin();
  Serial.begin(250000);

  //hmc588l
  Serial.println(mag.check());
  mag.configs(-24.5,-63); //(max-min)/2
  mag.mode();
  ma=mag.magScaled();
  zdegree = atan2(ma.z, ma.x);
  if(zdegree<0){zdegree=zdegree+2*3.14;}
}


void loop() {
  ma=mag.magScaled();
  axisprint(ma.x,ma.y,ma.z,"mag:  ");

  float zdeg = atan2(ma.z, ma.x);
  
  if(zdeg<0){zdeg=zdeg+2*3.14;}
  float magYaw =(zdeg-zdegree)*180/3.14;
  if(magYaw<0){magYaw=magYaw+360;}
  
  Serial.print("         refdegree = ");
  Serial.print((zdegree)*180/3.14,5);
  Serial.print("         degree = ");
  Serial.print((zdeg)*180/3.14,5);
  Serial.print("         cdegree = ");
  Serial.print(magYaw,5);
  
  Serial.println();
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
