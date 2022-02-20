#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"

void motor_init();
void go(void);
void stop(void);
void back(void);
void left(void);
void right(void);
void sleft(void);		//小左转
void sright(void);  //小右转 
void usright(void); //避障右转 
void usleft(void);  //避障左转 

#endif

