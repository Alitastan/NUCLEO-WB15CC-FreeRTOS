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
	static uint16_t flag = 1;
	(flag ^= 1) ? TurnOffAllLeds() : TurnOnAllLeds();
}

void LedEffect2(void)
{
	static uint16_t flag = 1;
	(flag ^= 1) ? TurnOnOddLeds() : TurnOnEvenLeds();
}


/* TODO: Try to fix the order of blinking. It starts blinking
 * with BLUE LED and goes in reverse direction. */

void LedEffect3(void)
{
	static uint16_t i = 0;
	// 1 << 0 : 1	(0x1)
	// 1 << 1 : 2	(0x2)
	// 1 << 2 : 4	(0x4)
	// 1 << 3 : 8	(0x8)
	// 1 << 4 : 16	(0x10)
	// 1 << 5 : 32	(0x20)
	// 1 << 6 : 64	(0x40)
	LedControl( 0x1 << (i++ % 6) );

	if (i % 6 == 0)
	{
		// Reset i
		i = 0;
	}
	else
	{
		// Do nothing.
	}
}

void LedControl(uint8_t value)
{
	for( uint8_t i = 0; i < 6; i++ )
		HAL_GPIO_WritePin( GPIOB, ( BLUE_LED >> i), ((value >> i))& 0x1 );
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

/* Timer callback function. It is called whenever a timer ends */
void LedEffectCbx(TimerHandle_t xTimer)
{
	uint32_t id;
	id = (uint32_t) pvTimerGetTimerID(xTimer);

	switch(id)
	{
	case LED_EFFECT1:
		LedEffect1();
		break;
	case LED_EFFECT2:
		LedEffect2();
		break;
	case LED_EFFECT3:
		LedEffect3();
		break;
	}

}

