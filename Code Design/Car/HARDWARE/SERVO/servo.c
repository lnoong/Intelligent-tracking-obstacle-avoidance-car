#include "servo.h"

/*
参考来源：
CSDN 蚂蚁的希望 2019-04-15 19:50:46
STM32控制SG90舵机
*/

void pwm_init()//舵机函数
{
	GPIO_InitTypeDef GPIO_InitStructure;   //声明一个结构体变量，用来初始化GPIO

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;//声明一个结构体变量，用来初始化定时器

	TIM_OCInitTypeDef TIM_OCInitStructure;//根据TIM_OCInitStruct中指定的参数初始化外设TIMx

	// 开启时钟 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能GPIOA
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//开启TIM3
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//端口复用，此处可省略//	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);//改变指定管脚的映射,重映射到PC6上

	//配置GPIO的模式和IO口 
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;// PA6
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_Init(GPIOA,&GPIO_InitStructure);//GPIOA
	
	//TIM3定时器初始化
	TIM_TimeBaseInitStructure.TIM_Period = 199; //PWM 频率=72000/(199+1)=36Khz//设置自动重装载寄存器周期的值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7199;//设置用来作为TIMx时钟频率预分频值
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//TIM向上计数模式
	TIM_TimeBaseInit(TIM3, & TIM_TimeBaseInitStructure);


	//PWM初始化	 根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//PWM输出使能
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_Low;

	TIM_OC1Init(TIM3,&TIM_OCInitStructure);			//此处初始化TIM3的CH1
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);		//使能或者失能TIMx在CCR1上的预装载寄存器
	TIM_Cmd(TIM3,ENABLE);	//使能或者失能TIMx外设
}

