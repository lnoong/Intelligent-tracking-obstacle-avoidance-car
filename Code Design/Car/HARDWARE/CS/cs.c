#include "cs.h"
#include "stm32f10x.h"
#include "delay.h"

/*
参考来源：
CSDN 宗师之路 2016-06-05 21:12:56
基于stm32的超声波测距
CSDN Lostin_sakura 2019-02-17 20:30:23
基于STM32的超声波传感器测距
*/

//记录定时器溢出次数
uint overcount=0;
//设置中断优先级
void NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructer;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructer.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructer.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructer.NVIC_IRQChannel=TIM4_IRQn;
	NVIC_InitStructer.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructer);
}

//初始化模块的GPIO以及初始化定时器TIM4
void CH_SR04_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructer;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructer;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	/*TRIG触发信号*/
	GPIO_InitStructer.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructer.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructer.GPIO_Pin=GPIO_Pin_8;
	GPIO_Init(GPIOB, &GPIO_InitStructer);

	/*ECOH回响信号*/
	GPIO_InitStructer.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructer.GPIO_Pin=GPIO_Pin_9;
	GPIO_Init(GPIOB, & GPIO_InitStructer);

	/*定时器TIM4初始化*/
	TIM_DeInit(TIM4);
	TIM_TimeBaseInitStructer.TIM_Period=999;//定时周期为999
	TIM_TimeBaseInitStructer.TIM_Prescaler=71; //分频系数71
	TIM_TimeBaseInitStructer.TIM_ClockDivision=TIM_CKD_DIV1;//不分频
	TIM_TimeBaseInitStructer.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructer);

	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);//开启更新中断
	NVIC_Config();
	TIM_Cmd(TIM4,DISABLE);//关闭定时器使能
}

//测距函数
float Senor_Using(void)
{
	float length=0,sum=0;
	u16 tim;
	uint i=0;
	/*测5次数据计算一次平均值*/
	while(1){
	while(i!=5)
	{
		PBout(8)=1; //拉高信号，作为触发信号
		delay_us(20); //高电平信号超过10us
		PBout(8)=0;
		/*等待回响信号*/
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==RESET);
		TIM_Cmd(TIM4,ENABLE);//回响信号到来，开启定时器计数

		i+=1; //每收到一次回响信号+1，收到5次就计算均值
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==SET);//回响信号消失
		TIM_Cmd(TIM4,DISABLE);//关闭定时器

		tim=TIM_GetCounter(TIM4);//获取计TIM4数寄存器中的计数值，一边计算回响信号时间

		length=(tim+overcount*1000)/58.0;//通过回响信号计算距离，单位cm

		sum=length+sum;
		TIM4->CNT=0; //将TIM4计数寄存器的计数值清零
		overcount=0; //中断溢出次数清零
		delay_ms(10);
	}
	length=sum/5;
	return length;//距离作为函数返回值
}

}

void TIM4_IRQHandler(void) //中断，当回响信号很长是，计数值溢出后重复计数，用中断来保存溢出次数
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)!=RESET)
	 {
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);//清除中断标志
	overcount++;

	 }
}
