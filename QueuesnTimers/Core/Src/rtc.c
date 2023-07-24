/*
 * rtc.c
 *
 *  Created on: Jul 13, 2023
 *      Author: MSI-NB
 */


#include "rtc.h"



void ShowTimeDate(void)
{
	static char showTime[100];
	static char showDate[100];

	RTC_DateTypeDef rtcDate;
	RTC_TimeTypeDef rtcTime;


	static char * time = showTime;
	static char * date = showDate;

	memset(&rtcDate,0,sizeof(rtcDate));
	memset(&rtcTime,0,sizeof(rtcTime));

	/* Get the RTC current Time */
	HAL_RTC_GetTime(&hrtc, &rtcTime, RTC_FORMAT_BIN);

	/* Get the RTC Current Date */
	HAL_RTC_GetDate(&hrtc, &rtcDate, RTC_FORMAT_BIN);

	char * format;
	format = (rtcTime.TimeFormat == RTC_HOURFORMAT_24) ? "24 Hours Format" : "12 Hours Format";


	/* Display time format : hh:mm:ss */
	sprintf((char *)showTime,
			"%s:\t%02d:%02d:%02d [%s]",
			"\nCurrent Time&Date",
			rtcTime.Hours,
			rtcTime.Minutes,
			rtcTime.Seconds,
			format);

	xQueueSend(	hPrintQueue, &time, portMAX_DELAY );

	/* Display date format: date-month-year */
	sprintf((char *)showDate,
			"\t%02d-%02d-%2d\n",
			rtcDate.Month,
			rtcDate.Date,
			2000 + rtcDate.Year);

	xQueueSend( hPrintQueue, &date, portMAX_DELAY);

}

void RtcConfigureTime(RTC_TimeTypeDef * time)
{
	time->TimeFormat = RTC_HOURFORMAT_24;
	time->DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	time->StoreOperation = RTC_STOREOPERATION_RESET;
	HAL_RTC_SetTime(&hrtc, time, RTC_FORMAT_BIN);

}

void RtcConfigureDate(RTC_DateTypeDef * date)
{
	HAL_RTC_SetDate(&hrtc, date, RTC_FORMAT_BIN);
}

int ValidateRtcInfo(RTC_TimeTypeDef *time , RTC_DateTypeDef *date)
{
	if(time){
		if( (time->Hours > 24) || (time->Minutes > 59) || (time->Seconds > 59) )
			return 1;
	}

	if(date){
		if( (date->Date > 31) || (date->WeekDay > 7) || (date->Year > 99) || (date->Month > 12) )
			return 1;
	}

	return 0;
}
