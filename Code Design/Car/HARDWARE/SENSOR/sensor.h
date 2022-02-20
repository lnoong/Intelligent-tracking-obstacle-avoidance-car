#ifndef __SENSOR_H
#define __SENSOR_H	 
#include "sys.h"

//用SENSOR0读取红外循迹传感器0的输入值
#define SENSOR0 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)
//用SENSOR1读取红外循迹传感器1的输入值
#define SENSOR1 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)
//用SENSOR2读取红外循迹传感器2的输入值
#define SENSOR2 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)

void Sensor_Init(void);//声明Sensor初始化函数
		 				    
#endif

