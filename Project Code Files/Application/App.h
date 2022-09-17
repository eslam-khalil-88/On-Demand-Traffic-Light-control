/*
 * App.h
 *
 * Created: 12/09/2022 18:03:04
 *  Author: COMPUMARTS
 */ 


#ifndef APP_H_
#define APP_H_

#include"../ECUAL/LED/LED.h"
#include "../ECUAL/Button/BUTTON.h"
#include "../MCAL/Timer0/Timer0.h"
#include "../MCAL/ExtINT/ExtINT.h"

#define NORMAL_MODE 0
#define PED_MODE 1

#define RED 0
#define YELLOW 1
#define GREEN 2

void App_Start(void);

#endif /* APP_H_ */