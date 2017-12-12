#include "L3g4200d_Lib.h"
#include <Wire.h>
#include <math.h>


#define GYRO_ADDRESS (0xD2 >> 1)



// normal mode.
void L3G4200D::enableDefault(void)
{
	// Normal power mode, all axes enabled
	gyro_write(L3G4200D_CTRL_REG1, 0x0F);
	

	//  7     6     5    4    3   2     1     0
	//BDU BLE FS1 FS0  -  ST1 ST0 SIM
	//Full Scale selection. Default value: 00 (00: 250 dps; 01: 500 dps; 10: 2000 dps; 11: 2000 dps)
	gyro_write(L3G4200D_CTRL_REG4, 0b00110000);
}

bool L3G4200D::check()
{
	
	if(0b11010011==gyro_read(L3G4200D_WHO_AM_I))
	{
		return true;		
	}
		return false; 
	
}

void L3G4200D::gyro_write(byte reg, byte value)
{
	Wire.beginTransmission(GYRO_ADDRESS);
	Wire.write(reg);
	Wire.write(value);
	Wire.endTransmission();
}

// Reads a gyro register
byte L3G4200D::gyro_read(byte reg)
{
	byte value;
	
	Wire.beginTransmission(GYRO_ADDRESS);
	Wire.write(reg);
	Wire.endTransmission();
	Wire.requestFrom(GYRO_ADDRESS, 1);
	value = Wire.read();
	Wire.endTransmission();
	
	return value;
}

// Reads the 3 gyro channels and stores them in vector g
void L3G4200D::read()
{
	Wire.beginTransmission(GYRO_ADDRESS);
	// assert the MSB of the address to get the gyro 
	// to do slave-transmit subaddress updating.
	Wire.write(L3G4200D_OUT_X_L | (1 << 7)); 
	
	Wire.endTransmission();
	//get data for all axis
	Wire.requestFrom(GYRO_ADDRESS, 6);

	while (Wire.available() < 6);
	
	uint8_t xla = Wire.read();
	uint8_t xha = Wire.read();
	uint8_t yla = Wire.read();
	uint8_t yha = Wire.read();
	uint8_t zla = Wire.read();
	uint8_t zha = Wire.read();

	gyro.x = xha << 8 | xla;
	gyro.y = yha << 8 | yla;
	gyro.z = zha << 8 | zla;
}


void L3G4200D::degree(double time)
{
	read();
	deg.x=gyro.x*time;
	deg.y=gyro.y*time;
	deg.z=gyro.z*time;	
}