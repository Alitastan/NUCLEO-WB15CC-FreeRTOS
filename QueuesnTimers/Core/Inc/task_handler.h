/*
 * task_handler.h
 *
 *  Created on: Jul 13, 2023
 *      Author: MSI-NB
 */

#ifndef INC_TASK_HANDLER_H_
#define INC_TASK_HANDLER_H_

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <stdio.h>

#define LED_EFFECT	0
#define DATE_TIME	1
#define	EXIT_MENU	2

/* Application states */
typedef enum
{
	sMainMenu = 0,
	sLedEffect,
	sRtcMenu,
	sRtcTimeConfig,
	sRtcDateConfig,
	sRtcReport,
}State_t;

void menuTask(void* parameters);
void ledTask(void* parameters);
void RTCTask(void* parameters);
void printTask(void* parameters);
void commandTask(void* parameters);

extern TaskHandle_t hMenu,hLed,hRTC,hPrint,hCommand;
extern QueueHandle_t hInputDataQueue, hPrintQueue;
extern State_t currentProgramState;



#endif /* INC_TASK_HANDLER_H_ */
