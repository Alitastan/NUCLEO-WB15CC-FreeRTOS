/*
 * led_effect.h
 *
 *  Created on: Jul 20, 2023
 *      Author: MSI-NB
 */

#ifndef INC_LED_EFFECT_H_
#define INC_LED_EFFECT_H_


#include "FreeRTOS.h"
#include "timers.h"
#include <stdint.h>
#include "stm32wbxx_hal.h"



#define BLUE_LED GPIO_PIN_5
#define GREEN_LED GPIO_PIN_0
#define RED_LED	GPIO_PIN_1

#define LED_EFFECT1	1
#define LED_EFFECT2	2
#define LED_EFFECT3	3


void LedEffectStop(void);
void LedStartTimer(uint8_t n);
void LedEffect1(void);
void LedEffect2(void);
void LedEffect3(void);
void LedControl(uint8_t value);
void TurnOnAllLeds(void);
void TurnOffAllLeds(void);
void TurnOnOddLeds(void);
void TurnOnEvenLeds(void);

void LedEffectCbx(TimerHandle_t xTimer);

extern TimerHandle_t hLedTimer[3];
extern UART_HandleTypeDef huart1;

#endif /* INC_LED_EFFECT_H_ */
