
#include <Wire.h>
#include "Adxl345_lib.h"

#include <math.h>

void ADXL345::ADXL345_set(void)
{
	accel_Write(Register_2D,8);
	accel_Write(Register_DataFormat,0b00101011);	

} 

void ADXL345::ADXL345_set(int _2D,int DataFormat)
{	
	accel_Write(Register_2D, _2D);
	accel_Write(Register_DataFormat,  DataFormat);
}

void ADXL345::accel_constant(float a,float b,float c,float d,float e,float f) 
{
	 accel_x_pos=a; accel_x_neg=b; 
	 accel_y_pos=c; accel_y_neg=d;
	 accel_z_pos=e; accel_z_neg=f;	
}
 
 void ADXL345::hardwareOffset(char x_offset, char y_offset, char z_offset)
{   
	accel_Write(ADXL345_OFSX, x_offset);
	accel_Write(ADXL345_OFSY, y_offset);
	accel_Write(ADXL345_OFSZ, z_offset);  
}
 
 int ADXL345::accel_Read(int add,int number)
{ 
		  int buffers;
	
	
	
		  //FOR UNO
    	  Wire.beginTransmission(ADXLadd);
		  Wire.write(add);
		  Wire.endTransmission();
		  
		  Wire.beginTransmission(ADXLadd);
		  Wire.requestFrom(ADXLadd,number);
		  if(Wire.available()<=number)
		  {buffers=Wire.read();}
		  Wire.endTransmission();
		  return buffers; 

		  
		  
		  
		  // FOR DUE
		  /*
          Wire1.beginTransmission(ADXLadd);
		  Wire1.write(add);
		  Wire1.endTransmission();
		  
		  Wire1.beginTransmission(ADXLadd);
		  Wire1.requestFrom(ADXLadd,number);
		  if(Wire1.available()<=number)
		  {buffers=Wire1.read();}
		  Wire1.endTransmission();
		  return buffers;
		  */
	
} 

void ADXL345::accel_Write(int add,int value)
{

		//FOR UNO
		Wire.beginTransmission(ADXLadd);
		Wire.write(add);
		Wire.write(value);
		Wire.endTransmission();

		//FOR  DUE
         /*
		Wire1.beginTransmission(ADXLadd);
		Wire1.write(add);
		Wire1.write(value);
		Wire1.endTransmission();
		*/ 
	
}

AccelerometerVal ADXL345::rawvalue()
{  
  AccelerometerVal raw= AccelerometerVal();
  
  accel_X0 = accel_Read(Register_accel_X0,1); accel_X1 = accel_Read(Register_accel_X1,1); 
  accel_X1=accel_X1<<8;
  
  raw.XAxis=accel_X0+accel_X1;   
  accel_Y0 = accel_Read(Register_accel_Y0,1); accel_Y1 = accel_Read(Register_accel_Y1,1); 
  accel_Y1=accel_Y1<<8;
  raw.YAxis=accel_Y0+accel_Y1;
  
  accel_Z0 = accel_Read(Register_accel_Z0,1); accel_Z1 = accel_Read(Register_accel_Z1,1); 
  accel_Z1=accel_Z1<<8;
  raw.ZAxis=accel_Z0+accel_Z1;  
 
  return raw;
}

AccelerometerVal ADXL345::scalevalue()
{
 AccelerometerVal raw= rawvalue();
 AccelerometerVal sc;

 if(raw.XAxis>0){sc.XAxis=(float)raw.XAxis/accel_x_pos;} else {sc.XAxis=(float)raw.XAxis/accel_x_neg;}
 if(raw.YAxis>0){sc.YAxis=(float)raw.YAxis/accel_y_pos;} else {sc.YAxis=(float)raw.YAxis/accel_y_neg;} 
 if(raw.ZAxis>0){sc.ZAxis=(float)raw.ZAxis/accel_z_pos;} else {sc.ZAxis=(float)raw.ZAxis/accel_z_neg;} 
  sc.XAxis=sc.XAxis;
  sc.YAxis=sc.YAxis;
  sc.ZAxis=sc.ZAxis;
 return sc;
}

AccelerometerRotation ADXL345::accel_RollPitch()
{  
	AccelerometerVal ac = scalevalue(); 
	
    AccelerometerRotation rp;
	rp.pitch = (atan2(ac.XAxis,sqrt(ac.YAxis*ac.YAxis+ac.ZAxis*ac.ZAxis)) * 180.0) / PI;
	rp.roll    = (atan2(ac.YAxis,(sqrt(ac.XAxis*ac.XAxis+ac.ZAxis*ac.ZAxis))) * 180.0) / PI;	
	return rp;
}

AccelerometerRotation ADXL345::accel_RollPitch(AccelerometerVal ac)
{  	
    AccelerometerRotation rp;
	
	rp.pitch = (atan2(ac.XAxis,sqrt(ac.YAxis*ac.YAxis+ac.ZAxis*ac.ZAxis)) * 180.0) / PI;
	rp.roll    = (atan2(ac.YAxis,(sqrt(ac.XAxis*ac.XAxis+ac.ZAxis*ac.ZAxis))) * 180.0) / PI;	
	return rp;
}

