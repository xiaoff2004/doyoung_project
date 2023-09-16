#include "mpu6050.h"
#include "main.h"
#include "i2c.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"



uint8_t MPU_WriteByte(uint8_t RegAddr,uint8_t data)
{
	while(HAL_I2C_Mem_Write(&hi2c_mpu,MPU_WRITE,RegAddr,I2C_MEMADD_SIZE_8BIT,&data,1,1000)!=0)
	{
		HAL_I2C_DeInit(&hi2c_mpu);        
    HAL_I2C_Init(&hi2c_mpu);
	}
	return 0;
//	uint8_t result =HAL_I2C_Mem_Write(&hi2c_mpu,MPU_WRITE,RegAddr,I2C_MEMADD_SIZE_8BIT,&data,1,1000);
//	if(result!=0)
//	{
//		HAL_I2C_DeInit(&hi2c_mpu);        
//    HAL_I2C_Init(&hi2c_mpu);
//	}
//	return result;
}

uint8_t MPU_ReadByte(uint8_t RegAddr,uint8_t *pdata)
{
	while(HAL_I2C_Mem_Read(&hi2c_mpu,MPU_READ,RegAddr,I2C_MEMADD_SIZE_8BIT,pdata,1,1000)!=0)
	{
		HAL_I2C_DeInit(&hi2c_mpu);        
    HAL_I2C_Init(&hi2c_mpu);
	}
	return 0;
//	uint8_t result =HAL_I2C_Mem_Read(&hi2c_mpu,MPU_READ,RegAddr,I2C_MEMADD_SIZE_8BIT,pdata,1,1000);
//	if(result!=0)
//	{
//		HAL_I2C_DeInit(&hi2c_mpu);        
//    HAL_I2C_Init(&hi2c_mpu);
//	}
//	return result;
}

uint8_t MPU_WritLen(uint8_t SlaveAddr,uint8_t RegAddr,uint8_t Len,uint8_t *pdata)
{
	while(HAL_I2C_Mem_Write(&hi2c_mpu,SlaveAddr,RegAddr,I2C_MEMADD_SIZE_8BIT,pdata,Len,1000)!=0)
	{
		HAL_I2C_DeInit(&hi2c_mpu);        
    HAL_I2C_Init(&hi2c_mpu);
	}
	return 0;
//	uint8_t result =HAL_I2C_Mem_Write(&hi2c_mpu,SlaveAddr,RegAddr,I2C_MEMADD_SIZE_8BIT,pdata,Len,1000);
//	if(result!=0)
//	{
//		HAL_I2C_DeInit(&hi2c_mpu);        
//    HAL_I2C_Init(&hi2c_mpu);
//		
//	}
//	return result;
}

uint8_t MPU_ReadLen(uint8_t SlaveAddr,uint8_t RegAddr,uint8_t Len,uint8_t *pdata)
{
	while(HAL_I2C_Mem_Read(&hi2c_mpu,SlaveAddr,RegAddr,I2C_MEMADD_SIZE_8BIT,pdata,Len,1000)!=0)
	{
		HAL_I2C_DeInit(&hi2c_mpu);        
    HAL_I2C_Init(&hi2c_mpu);
	}
	return 0;
//	uint8_t result =HAL_I2C_Mem_Read(&hi2c_mpu,SlaveAddr,RegAddr,I2C_MEMADD_SIZE_8BIT,pdata,Len,1000);
//	if(result!=0)
//	{
//		HAL_I2C_DeInit(&hi2c_mpu);        
//    HAL_I2C_Init(&hi2c_mpu);
//	}
//	return result;
}

//设置低通滤波 
uint8_t MPU_SetLPF(uint16_t lpf)
{
	uint8_t data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	return MPU_WriteByte(MPU_CFG_REG,data);
}

//设置采样率
uint8_t MPU_SetRate(uint16_t rate)
{
	uint8_t data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	data=MPU_WriteByte(MPU_SAMPLE_RATE_REG,data);	//设置低通滤波 
 	return MPU_SetLPF(rate/2);	//设置LPF为采样率的一半
}

uint8_t MPU_Init(void)
{

	MPU_WriteByte(MPU_PWR_MGMT1_REG,0x80);
	HAL_Delay(100);
	MPU_WriteByte(MPU_PWR_MGMT1_REG,0x00);
	MPU_WriteByte(MPU_GYRO_CFG_REG,(MPU_Gyro_Fsr<<3));
	MPU_WriteByte(MPU_ACCEL_CFG_REG,(MPU_Accel_Fsr<<3));					
	MPU_SetRate(50);
	MPU_WriteByte(MPU_INT_EN_REG,0x00);
	MPU_WriteByte(MPU_USER_CTRL_REG,0x00);
	MPU_WriteByte(MPU_FIFO_EN_REG,0x00);
	MPU_WriteByte(MPU_INTBP_CFG_REG,0x80);
	uint8_t addr=0;
	MPU_ReadByte(MPU_DEVICE_ID_REG,&addr);
	if(addr ==MPU_ADDR)
	{
		MPU_WriteByte(MPU_PWR_MGMT1_REG,0x01);
		MPU_WriteByte(MPU_PWR_MGMT2_REG,0x00);
		MPU_SetRate(50);
	}
	else 
		return HAL_ERROR;
	return HAL_OK;		
}

short MPU_GetTemp(void)
{
	uint8_t buff[2]={0};
	short raw;
	float temp;
	MPU_ReadLen(MPU_READ,MPU_TEMP_OUTH_REG,2,buff);
	raw=(uint16_t)buff[0]<<8|buff[1];
	temp=36.53+((double)raw)/340;
	return temp*100;
}

uint8_t MPU_GetGyro(short *gx,short *gy,short *gz)
{
	uint8_t buff[6]={0},result=0;
	result=MPU_ReadLen(MPU_READ,MPU_GYRO_XOUTH_REG,6,buff);
	if(result==HAL_OK)
	{
		*gx=((uint16_t)buff[0]<<8)|buff[1];  
		*gy=((uint16_t)buff[2]<<8)|buff[3];  
		*gz=((uint16_t)buff[4]<<8)|buff[5];
	}
	return result;
}

short MPU_GetGyro2(short gx)
{
	return 2000*gx*10000/32768;
}

uint8_t MPU_GetAccel(short *ax,short *ay,short *az)
{
	uint8_t buff[6]={0},result=0;
	result=MPU_ReadLen(MPU_READ,MPU_ACCEL_XOUTH_REG,6,buff);
	if(result==HAL_OK)
	{
		*ax=((uint16_t)buff[0]<<8)|buff[1];  
		*ay=((uint16_t)buff[2]<<8)|buff[3];  
		*az=((uint16_t)buff[4]<<8)|buff[5];
	}
	return result;
}

short MPU_GetAccel2(short ax)
{
	return 2*98000*ax/32768;
}

