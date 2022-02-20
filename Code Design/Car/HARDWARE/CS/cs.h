#ifndef __CS_H
#define __CS_H 	

#include "stm32f10x.h"
#include "delay.h"

#include "sys.h"
#define uint unsigned int
#define TRIG_Send PBout(8)
#define ECHO_Reci PBin(9)
#define distance Senor_Using()
void CH_SR04_Init(void);  //超声波模块相关配置初始化
float Senor_Using(void);  //测距函数，返回值即为距离
void NVIC_Config(void);   //中断配置


#endif

