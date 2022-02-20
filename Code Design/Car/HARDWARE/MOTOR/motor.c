#include "motor.h"

/*
参考来源：
CSDN 蚂蚁的希望 2019-04-15 19:50:46
STM32控制SG90舵机
*/


void motor_init(void)//电机转动函数
{
	GPIO_InitTypeDef GPIO_InitStructure;

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure; 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8 , ENABLE);		//开启TIM8时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);	//使能GPIOC
	
	
	TIM_TimeBaseStructure.TIM_Period = 1000;		//周期1000
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;		//向上计数
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseInit(TIM8 , &TIM_TimeBaseStructure);
	
	//端口复用，配置TIM8的CH1、CH2、CH3、CH4为C组6、7、8、9口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7| GPIO_Pin_8| GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	
	GPIO_Init(GPIOC, &GPIO_InitStructure);   



	//PWM通道1	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = 900;
	TIM_OC1Init(TIM8 , &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM8 , TIM_OCPreload_Enable);
	TIM_CtrlPWMOutputs(TIM8,ENABLE);	//MOE 主输出使能	
	

	//PWM通道2	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = 900;
	TIM_OC2Init(TIM8 , &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM8 , TIM_OCPreload_Enable);
	TIM_CtrlPWMOutputs(TIM8,ENABLE);	//MOE 主输出使能	
	
	
	//PWM通道3	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = 900;
	TIM_OC3Init(TIM8 , &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM8 , TIM_OCPreload_Enable);
	TIM_CtrlPWMOutputs(TIM8,ENABLE);	//MOE 主输出使能	
	
	
	//PWM通道4	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = 900;
	TIM_OC4Init(TIM8 , &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM8 , TIM_OCPreload_Enable);
	TIM_CtrlPWMOutputs(TIM8,ENABLE);	//MOE 主输出使能	
	TIM_Cmd(TIM8 , ENABLE);
}

void go(void)//前进函数配置
{
			TIM_SetCompare1(TIM8 , 480); 	// L+
	    TIM_SetCompare2(TIM8 , 000);	// L-
      TIM_SetCompare3(TIM8 , 480);  // R+
	    TIM_SetCompare4(TIM8 , 000);	// R-
}

void stop(void)//停止函数配置
{
			TIM_SetCompare1(TIM8 , 000); 	// L+
	    TIM_SetCompare2(TIM8 , 000);	// L-
      TIM_SetCompare3(TIM8 , 000);  // R+
	    TIM_SetCompare4(TIM8 , 000);	// R-
}

void back(void)//后退函数配置
{
			TIM_SetCompare1(TIM8 , 000); 	// L+
	    TIM_SetCompare2(TIM8 , 400);	// L-
      TIM_SetCompare3(TIM8 , 000);  // R+
	    TIM_SetCompare4(TIM8 , 400);	// R-
}

void left(void)//左转函数配置
{			
			TIM_SetCompare1(TIM8 , 000);  // L+
	    TIM_SetCompare2(TIM8 , 700);	// L-
      TIM_SetCompare3(TIM8 , 700);  // R+
	    TIM_SetCompare4(TIM8 , 000);	// R-

}

void sleft(void)//小左转函数配置
{
  		TIM_SetCompare1(TIM8 , 000);  // L+
	    TIM_SetCompare2(TIM8 , 550);	// L-
      TIM_SetCompare3(TIM8 , 550);  // R+
	    TIM_SetCompare4(TIM8 , 000);	// R-
}

void right(void)//右转函数配置
{
			TIM_SetCompare1(TIM8 , 700);  // L+
	    TIM_SetCompare2(TIM8 , 000);	// L-
      TIM_SetCompare3(TIM8 , 000);  // R+
	    TIM_SetCompare4(TIM8 , 700);	// R-
	
}

void sright(void)//小右转函数配置
{
   		TIM_SetCompare1(TIM8 , 550);  // L+
	    TIM_SetCompare2(TIM8 , 000);	// L-
      TIM_SetCompare3(TIM8 , 000);  // R+
	    TIM_SetCompare4(TIM8 , 550);	// R-
	
}
void usleft(void)//避障左转函数
{
   		TIM_SetCompare1(TIM8 , 430);  // L+
	    TIM_SetCompare2(TIM8 , 000);	// L-
      TIM_SetCompare3(TIM8 , 900);  // R+
	    TIM_SetCompare4(TIM8 , 000);	// R-
	
}
void usright(void)//避障右转函数
{
   		TIM_SetCompare1(TIM8 , 850);  // L+
	    TIM_SetCompare2(TIM8 , 000);	// L-
      TIM_SetCompare3(TIM8 , 400);  // R+
	    TIM_SetCompare4(TIM8 , 000);	// R-
	
}
