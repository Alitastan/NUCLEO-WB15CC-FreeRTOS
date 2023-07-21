/*
 * rtc.h
 *
 *  Created on: Jul 21, 2023
 *      Author: MSI-NB
 */

#ifndef INC_RTC_H_
#define INC_RTC_H_

#include "FreeRTOS.h"
#include "queue.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "stm32wbxx_hal.h"



void ShowTimeDate(void);
void RtcConfigureTime(RTC_TimeTypeDef * time);
void RtcConfigureDate(RTC_DateTypeDef * date);
int ValidateRtcInfo(RTC_TimeTypeDef *time , RTC_DateTypeDef *date);

extern RTC_HandleTypeDef hrtc;
extern TaskHandle_t hMenu,hLed,hRTC,hPrint,hCommand;
extern QueueHandle_t hInputDataQueue, hPrintQueue;


#endif /* INC_RTC_H_ */
