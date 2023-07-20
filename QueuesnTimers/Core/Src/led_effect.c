/*
 * led_effect.c
 *
 *  Created on: Jul 13, 2023
 *      Author: MSI-NB
 */


#include "led_effect.h"


void LedStartTimer(uint8_t n)
{
	LedEffectStop();
	xTimerStart(hLedTimer[n-1], portMAX_DELAY);


}

void LedEffectStop(void)
{
	for(uint8_t i = 0; i < 3 ; i++)
		xTimerStop(hLedTimer[i],portMAX_DELAY);
}

void LedEffect1(void)
{
	static int flag = 1;
	(flag ^= 1) ? TurnOffAllLeds() : TurnOnAllLeds();
}

void LedEffect2(void)
{
	static int flag = 1;
	(flag ^= 1) ? TurnOnOddLeds() : TurnOnEvenLeds();
}


/* TODO: Implement LedEffect3 and LedControl */

void LedEffect3(void)
{

}

void LedControl(void)
{

}


void TurnOnAllLeds(void)
{
	HAL_GPIO_WritePin(GPIOB, BLUE_LED, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, RED_LED, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GREEN_LED, GPIO_PIN_SET);
}

void TurnOffAllLeds(void)
{
	HAL_GPIO_WritePin(GPIOB, BLUE_LED, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, RED_LED, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GREEN_LED, GPIO_PIN_RESET);
}

void TurnOnOddLeds(void)
{
	HAL_GPIO_WritePin(GPIOB, BLUE_LED, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GREEN_LED, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, RED_LED, GPIO_PIN_SET);
}

void TurnOnEvenLeds(void)
{
	HAL_GPIO_WritePin(GPIOB, BLUE_LED, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GREEN_LED, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, RED_LED, GPIO_PIN_RESET);
}

void LedEffectCbx(TimerHandle_t xTimer)
{
	uint32_t id;
	id = (uint32_t) pvTimerGetTimerID(xTimer);

	switch(id)
	{
	case LED_EFFECT1:
		LedEffect1();
	case LED_EFFECT2:
		LedEffect2();
	case LED_EFFECT3:
		LedEffect3();
	}

}
