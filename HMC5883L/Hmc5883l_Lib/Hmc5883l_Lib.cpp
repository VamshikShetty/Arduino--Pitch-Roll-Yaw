#include "Hmc5883l_Lib.h"
#include <Wire.h>

void HMC5883L::configs(double x,double y)
{
	magWrite(HMC5883L_CONFIG_A, 0b01111000);  
	magWrite(HMC5883L_CONFIG_B, 0b10000000);
	gaussScale=440;
	_xoffset=x;
	_yoffset=y;
}

void HMC5883L::mode()
{
	magWrite(HMC5883L_MODE, 0b00000000);
}

bool HMC5883L::check()
{
	if( 0x48==magRead(HMC5883L_IDENT_A) & 0x34==magRead(HMC5883L_IDENT_B) & 0x33==magRead(HMC5883L_IDENT_C) )
	{
		return true;		
	}
		return false; 	
}

// write to a register
void HMC5883L::magWrite(byte reg, byte value)
{
	Wire.beginTransmission(HMC5883L_ADDRESS);
	Wire.write(reg);
	Wire.write(value);
	Wire.endTransmission();
}

// Reads a register
byte HMC5883L::magRead(byte reg)
{
	byte value;
	
	Wire.beginTransmission(HMC5883L_ADDRESS);
	Wire.write(reg);
	Wire.endTransmission();
	
	Wire.requestFrom(HMC5883L_ADDRESS, 1);
	value = Wire.read();
	Wire.endTransmission();
	
	return value;
}



// Reads the 3 channels 
magValues HMC5883L::magRead3()
{
	magValues mg;
	
	Wire.beginTransmission(HMC5883L_ADDRESS);
	// assert the MSB of the address to get the gyro 
	// to do slave-transmit subaddress updating.
	Wire.write(HMC5883L_OUT_X_M); 
	//ending transmission
	Wire.endTransmission();
	
	//get data for all axis
	Wire.requestFrom(HMC5883L_ADDRESS, 6);
	
	while (Wire.available() < 6);
	
	uint8_t xha = Wire.read();
	uint8_t xla = Wire.read();
	
	uint8_t yha = Wire.read();
	uint8_t yla = Wire.read();
	
	uint8_t zha = Wire.read();
	uint8_t zla = Wire.read();

	mg.x = xha << 8 | xla;
	mg.y = yha << 8 | yla;
	mg.z = zha << 8 | zla;
	
	return mg;
}

magValues HMC5883L::magScaled()
{
	magValues mg,sc;
	mg=magRead3();
	
	sc.x=(mg.x - _xoffset)/gaussScale*1000;  
	sc.y=(mg.y - _yoffset)/gaussScale*1000;
	sc.z=mg.z/gaussScale*1000;
	
	return sc;
}

