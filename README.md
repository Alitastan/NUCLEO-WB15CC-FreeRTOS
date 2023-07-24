# NUCLEO-WB15CC FreeRTOS 

- The projects here are examples of NON CMSIS manual FreeRTOS implementation.
- FreeRTOS Kernel **V10.4.3** is used.
- The application code is being written on **STM32CubeIDE version 1.12.0**

## Notes
	
- This project is based on FastBit Embedded Brain Academy course: Mastering RTOS: Hands on FreeRTOS and STM32Fx with Debugging

**001Tasks** *is an example of creating two simple tasks. It also includes Segger Sysview implementation.*

**002LedTasks** *is an example of 3 LED tasks blinking with different periods.*

**003LedTasks_Notification** *is an example of 3 LEDs and 1 button task. Button2 of NUCLEO-WB15CC board is used to trigger the LED blinking. Press the button 4 times and see for yourself!*

**004LedBtnFromISR** *is similar to 003LedTasks_Notification, it demonstrates how to notify a task from interrupt service routine triggered by the button-2 press.*

**QueuesnTimers** *project example demonstrates the use of 5 tasks, 2 queues, several timers and RTC functionality over USART connection. The application offers 3 LED effect configurations, Time and Date configuration over RTC and tracking over ITM data console. Flash the code and set the baud rate to 115200 over any serial terminal application and try it! ``Do not forget to set the SWV (Serial Wire Viewer) frequency to 4.0 MHz and Limit SWO clock frequency to 2000kHz.``*

https://www.udemy.com/course/mastering-rtos-hands-on-with-freertos-arduino-and-stm32fx/



