#ifndef __SERVO_H
#define __SERVO_H
#include "sys.h"

#define angle0 TIM_SetCompare1(TIM3 , 195);		//0業
#define angle45 TIM_SetCompare1(TIM3 , 190);	//45業
#define angle90 TIM_SetCompare1(TIM3 , 185);	//90業
#define angle135 TIM_SetCompare1(TIM3 , 180);	//135業
#define angle180 TIM_SetCompare1(TIM3 , 175);	//180業

void pwm_init();


#endif



