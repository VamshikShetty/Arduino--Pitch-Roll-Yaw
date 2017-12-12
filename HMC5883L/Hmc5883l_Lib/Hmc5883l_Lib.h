#define Hmc5883l_Lib.h


#include <Arduino.h> // for byte data type

// register addresses
#define HMC5883L_ADDRESS              (0x1E)

#define HMC5883L_CONFIG_A         (0x00)
#define HMC5883L_CONFIG_B         (0x01)
#define HMC5883L_MODE             (0x02)

#define HMC5883L_OUT_X_M          (0x03)
#define HMC5883L_OUT_X_L          (0x04)
#define HMC5883L_OUT_Z_M          (0x05)
#define HMC5883L_OUT_Z_L          (0x06)
#define HMC5883L_OUT_Y_M          (0x07)
#define HMC5883L_OUT_Y_L          (0x08)

#define HMC5883L_STATUS           (0x09)
#define HMC5883L_IDENT_A          (0x0A)
#define HMC5883L_IDENT_B          (0x0B)
#define HMC5883L_IDENT_C          (0x0C)


struct magValues
{
			float x, y, z;
};

class HMC5883L
{
	
	private:
		double _xoffset;
		double _yoffset;
		double _zoffset;
		float     gaussScale;
		
	
	public:
		
		void configs(double ,double);
		
		void mode();
		
		void magWrite(byte reg, byte value);
		
		byte magRead(byte reg);
		
		bool check();
		
		magValues magRead3(void);
		
		magValues magScaled(void);
		
		//void magConstant(float a,float b,float c,float d,float e,float f);
		
};
