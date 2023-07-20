/*
 * led_effect.h
 *
 *  Created on: Jul 20, 2023
 *      Author: MSI-NB
 */

#ifndef INC_LED_EFFECT_H_
#define INC_LED_EFFECT_H_

#include <stdio.h>

#define BLUE_LED LD1_Pin
#define GREEN_LED LD2_Pin
#define RED_LED	LD3_Pin


void led_effect_stop(void);
void led_effect(uint8_t parameter);

#endif /* INC_LED_EFFECT_H_ */
