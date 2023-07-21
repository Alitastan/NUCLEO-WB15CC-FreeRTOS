/*
 * task_handler.c
 *
 *  Created on: Jul 13, 2023
 *      Author: MSI-NB
 */



#include "task_handler.h"

State_t currentProgramState = sMainMenu;

const char* invalid_message = "~~Invalid Message~~\n";

void menuTask(void* parameters)
{
	uint32_t command_adr;
	Command_t* command;

	int8_t option;

	const char* entry_message = "======================\n"
								"|	MENU		|\n"
								"======================\n"
									"LED EFFECT	--->	0\n"
									"DATE & TIME	--->	1\n"
									"EXIT	--->	2\n"
									"ENTER YOUR CHOICE HERE... : ";
	while(1)
	{
		xQueueSend(hPrintQueue,&entry_message,portMAX_DELAY);
		xTaskNotifyWait(0,0,&command_adr,portMAX_DELAY);

		// Wait for menu commands
		command = (Command_t*)command_adr;
		if(command -> len == 1)
		{
			// Converting ASCII to number by subtracting 48
			option = command->payload[0] - 48;

			switch(option)
			{
			case LED_EFFECT:
				currentProgramState = sLedEffect;
				xTaskNotify(hLed,0,eNoAction);
				break;
			case DATE_TIME:
				currentProgramState = sRtcMenu;
				xTaskNotify(hRTC,0,eNoAction);
				break;
			case EXIT_MENU:
				/* Todo: implement exit */
				break;
			default:
				xQueueSend(hPrintQueue,&entry_message,portMAX_DELAY);
				continue;
			}
		}
		else
		{
			// Invalid entry
			xQueueSend(hPrintQueue,&invalid_message,portMAX_DELAY);
			continue;
		}

		// Wait to run again when some other task notifies menu task.
		xTaskNotifyWait(0,0,NULL,portMAX_DELAY);

	} // End of while loop

}

void ledTask(void* parameters)
{
	uint32_t command_adr;
	Command_t* command;

	const char* led_message = 	"=====================\n"
								"|	LED EFFECT	|\n"
								"=====================\n"
								"OPTIONS: Please type none, e1, e2 or e3.\n"
								"ENTER YOUR CHOICE HERE... :\n ";
	while(1)
	{
		/* Wait for notification */
		xTaskNotifyWait(0,0,NULL,portMAX_DELAY);

		/* Print LED menu */
		xQueueSend(hPrintQueue,&led_message,portMAX_DELAY);

		/* Wait for LED commands */
		xTaskNotifyWait(0,0,&command_adr,portMAX_DELAY);

		command = (Command_t*)command_adr;

		if( (command->len) <= 4)
		{
			if(! strncmp((char*)command->payload, "none", strlen("none")) )
				LedEffectStop();
			else if(! strncmp((char*)command->payload, "e1", strlen("e1")) )
				LedStartTimer(1);
			else if(! strncmp((char*)command->payload, "e2", strlen("e2")) )
				LedStartTimer(2);
			else if(! strncmp((char*)command->payload, "e3", strlen("e3")) )
				LedStartTimer(3);
			else
				// Print invalid message
				xQueueSend(hPrintQueue,&invalid_message,portMAX_DELAY);
		}
		else
			// Print invalid message
			xQueueSend(hPrintQueue,&invalid_message,portMAX_DELAY);

		// Update the state variable
		currentProgramState = sMainMenu;

		// Notify menu task
		xTaskNotify(hMenu,0,eNoAction);



	}
}

void RTCTask(void* parameters)
{
	while(1)
	{

	}
}

void printTask(void* parameters)
{
	uint32_t* message;
	while(1)
	{
		xQueueReceive(hPrintQueue, &message, portMAX_DELAY);
		HAL_UART_Transmit(&huart1, (uint8_t*)message, strlen((char*)message), HAL_MAX_DELAY);
	}
}

 void commandTask(void* parameters)
{
	 BaseType_t status;
	 //const TickType_t xFrequency = pdMS_TO_TICKS(1000);
	 Command_t command;
		while(1)
		{
			/* Implement notify wait */
			status = xTaskNotifyWait(0,0,NULL,portMAX_DELAY);
			if(status == pdTRUE)
			{
				/* Process the user data(command) stored in input data queue */
				/* Notify the command to relevant task */
				processCommand(&command);
			}

		}
}

/* The notification value of the target task is
 * unconditionally set to ulValue when eSetValueWithOverwrite
 * is used.   */

 void processCommand(Command_t* command)
 {
	 /* Extract the data bytes from the input data queue and form a command */
	 extract_command(command);

	 switch(currentProgramState)
	 {
	 case sMainMenu:
		 /* Notify menu task with the command */
		 xTaskNotify(hMenu, (uint32_t)command, eSetValueWithOverwrite);
		 break;

	 case sLedEffect:
		 /* Notify LED task with the command */
		 xTaskNotify(hLed, (uint32_t)command, eSetValueWithOverwrite);
		 break;

	 case sRtcMenu:
	 case sRtcTimeConfig:
	 case sRtcDateConfig:
	 case sRtcReport:
		 /* Notify RTC task with the command */
		 xTaskNotify(hRTC, (uint32_t)command, eSetValueWithOverwrite);
		 break;

	 }
 }

 int extract_command(Command_t* command)
 {
	 uint8_t item;
	 BaseType_t status;

	 // Return the number of messages stored in a queue.
	 status = uxQueueMessagesWaiting(hInputDataQueue);
	 if(!status) return -1;

	 uint8_t i = 0;
	 do
	 {
		 // Received item into the hInputDataQueue will be copied to item buffer.
		 status = xQueueReceive(hInputDataQueue, (void*)&item, 0);
		 if(status == pdTRUE) command -> payload[i++] = item;
	 }while(item != '\n');

	 command -> payload[i-1] = '\0';
	 command -> len = i-1; /* Save length of the command excluding null char */

	 return 0;
 }
