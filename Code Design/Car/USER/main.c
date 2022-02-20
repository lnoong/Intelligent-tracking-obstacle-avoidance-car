#include"delay.h"	
#include"motor.h"		//电机
#include"servo.h"		//舵机
#include"sensor.h"	//红外传感器
#include"cs.h"			//超声波传感器
#include"led.h"			//指示灯
int main(void)
 {	int a=1;
		char 	str[20];        //用来存放浮点数字符	
		float length_res[5];  //用来存放测距结果
	 
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断优先级
	 
		delay_init();	    		//延时函数初始化	  
	  motor_init();					//电机函数初始化
		Sensor_Init();			 	//初始化与红外传感器连接的硬件接口
		pwm_init();  					//舵机pwm	    		TIM3
		CH_SR04_Init();  			//超声波定时器    	TIM4
		Senor_Using(); 				//测距函数初始化
		NVIC_Config();				//中断函数初始化

	while(1)
	{	

{	//循迹模块
	//SENSOR0 0==白		SENSOR1 0==黑	 	SENSOR2 0==白


				while(1)		//未检测到障碍物，循迹
				{
					angle90;//舵机摆正
				if(SENSOR0 ==1 && SENSOR1==0 && SENSOR2 ==1 )//十字或停止，先认为是十字
				{
					go();
				}
				 if(SENSOR0 ==0 && SENSOR1==0 && SENSOR2 ==0)//直线
				{
					go();
				}
				 if(SENSOR0 ==1 && SENSOR1==0 && SENSOR2 ==0)//左直弯
				{
						go();
						delay_ms(150);
						left();
						delay_ms(200);
				}
				 if(SENSOR0 ==1 && SENSOR1==1 && SENSOR2 ==0)//左弧弯或左偏
				{
					sleft();
		
				}
				 if(SENSOR0 ==0 && SENSOR1==0 && SENSOR2 ==1)//右直弯
				{
					go();
					delay_ms(150);
					right();
					delay_ms(200);
				}
				 if(SENSOR0 ==0 && SENSOR1==1 && SENSOR2 ==1)//右弧弯或右偏
				{
					sright();
	
				}
				if(a==1&&distance<=25)
					break;
				
				}
}		
/******************************************************************************/
{	//避障模块		
			while(distance<=25)
			{a=0;
					if(SENSOR0!=1||SENSOR1!=0||SENSOR2!=1)		//检测到障碍物，避障
					{	

						stop(); 
					
						angle135;      //舵机左转45度测距
						delay_ms(200);		
		
						angle45;     	//舵机右转45度测距
						delay_ms(200);	
			
						angle90;
						left();
						delay_ms(400);
						
						stop();
						delay_ms(100);
						usright();
				
					}
							if(SENSOR0==1||SENSOR1==0||SENSOR2==1)
							{	stop();
								delay_ms(100);
								left();
								delay_ms(200);
								break;
							}
						
					
					
				}	
	
			}
			
	}			
}	



		
		  			
	 
