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
#include <string.h>

#define LED_EFFECT	0
#define DATE_TIME	1
#define	EXIT_MENU	2

typedef struct
{
	uint8_t payload[10]; // stores data bytes of the command
	uint8_t len;	// command length
}Command_t;

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

int extract_command(Command_t* command);
void processCommand(Command_t* command);

extern TaskHandle_t hMenu,hLed,hRTC,hPrint,hCommand;
extern QueueHandle_t hInputDataQueue, hPrintQueue;
extern State_t currentProgramState;



#endif /* INC_TASK_HANDLER_H_ */
