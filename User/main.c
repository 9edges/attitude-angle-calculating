#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MyI2C.h"
#include "MPU6050.h"
#include "Sqrt.h"
#include "stdlib.h"
#include "math.h"

#define G 9.8
#define PI 3.14159


uint16_t ID;
int16_t  AX,AY,AZ,GX,GY,GZ;
double ax,ay,az,gz;
double law;

long double Pitch , Roll , Yaw;
static long double dt = 0.45;

int main(void){	
	OLED_Init();
	MPU6050_Init();
	
	OLED_ShowString(1,1,"ID:");
	ID = MPU6050_GetID();
	OLED_ShowHexNum(1,4,ID,2);
	Yaw = 0 ;
	while (1){		
		MPU6050_GetData(&AX,&AY,&AZ,&GX,&GY,&GZ);
		ax=(double)AX*16/32768*G;
		ay=(double)AY*16/32768*G;
		az=(double)AZ*16/32768*G;
		gz=(double)GZ*16/32768*G;
		ax=(ax*100.0+0.5)/100;
		ay=(ay*100.0+0.5)/100;
		az=(az*100.0+0.5)/100;
		gz=(gz*100.0+0.5)/100;
		Pitch = (atan(-ax/Sqrt(az*az+ay*ay)))/(PI/180.0);
		long double k = gz*dt;
		Yaw   = Yaw + gz * dt ;
		Roll   = (atan(ay/az))/(PI/180.0);
		
		OLED_ShowString(2,1,"Pitch:");
		OLED_ShowString(3,1,"Roll:");
		OLED_ShowString(4,1,"Yaw:");
		OLED_ShowSignedNum(2,8,Pitch,5);
		OLED_ShowSignedNum(3,8,Roll,5);
		OLED_ShowSignedNum(4,8,Yaw,5);
		
	}
}
