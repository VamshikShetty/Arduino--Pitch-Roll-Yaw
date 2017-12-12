#define Adxl345_Lib.h




//register definiation

#define Register_2D 0x2D
#define ADXL345_OFSX 0x1E
#define ADXL345_OFSY 0x1F
#define ADXL345_OFSZ 0x20
#define Register_accel_X0 0x32
#define Register_accel_X1 0x33
#define Register_accel_Y0 0x34
#define Register_accel_Y1 0x35
#define Register_accel_Z0 0x36
#define Register_accel_Z1 0x37
#define Register_DataFormat 0x31
#define ADXLadd 0x53

#define PI 3.14159

struct AccelerometerVal
{
	float XAxis;
	float YAxis;
	float ZAxis;
};

struct AccelerometerRotation
{
   double pitch;
   double roll;
};

class ADXL345
{
// constants
private: 
	float accel_x_pos , accel_x_neg; 
	float accel_y_pos , accel_y_neg;
	float accel_z_pos , accel_z_neg;
	
	int16_t accel_X0,accel_X1;
	int16_t accel_Y0,accel_Y1;
	int16_t accel_Z1,accel_Z0;
	
	
	
	//Accelometer Axis: Lo/Hi readings
public:

	//Register_2D & Register_DataFormat
	void ADXL345_set(void);

	//first parameter is for Register_2D & Register_DataFormat
	void ADXL345_set(int,int);
	
	void hardwareOffset(char x_offset=0, char y_offset=0, char z_offset=0);

	void accel_constant(float a,float b,float c,float d,float e,float f);
	
	void accel_Write(int,int);
	
	 int accel_Read(int,int);
	  
	 AccelerometerVal rawvalue();
	 
	 AccelerometerVal scalevalue();
	 
	 AccelerometerRotation accel_RollPitch();
	 
	 AccelerometerRotation accel_RollPitch(AccelerometerVal ac);
};

 

 
