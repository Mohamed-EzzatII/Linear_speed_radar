/******************************************************************************
 *
 * Module: the application code
 *
 * File Name: app.h
 *
 * Description: header file for the application layer
 *
 * Author: Mohamed Ezzat
 *
 * Created on: April 25, 2022
 *
 * Version : v1.0.1
 *
 *******************************************************************************/

/************************Libraries and inclusions*******************************/

#include<util/delay.h>
#include"../MCAL/interrupt.h"
#include"../HAL/lcd.h"
#include"../MCAL/timer1.h"
#include"../MCAL/uart.h"
#include"../HAL/buzzer.h"
#include"../HAL/grn_led.h"
#include"../HAL/red_led.h"
#include"app.h"

/**********************************Functions************************************/


/* Function to set the configurations of modules*/
void configurations(void)
{
	/* initialize the HAL layer modules */

	Buzzer_init(); /* Buzzer */
	GRN_LED_init();/* green led */
	RED_LED_init();/* red led */
	LCD_init();	   /* LCD */

	/* The static display on LCD */
	LCD_displayString("SPEED :     cm/sec");

	/* Initialize the MCAL layer modules */

	/* Timer 1 : normal mode and prescaler 1024*/
	Timer1_ConfigType conf={0,0,N_1024,NORMAL};
	TIMER1_init(&conf);

	/* interrupt : INT1 & INT0 configurations and both works on falling edge */
	INT_CONF conf1={INT0_ID,FALLING_EDGE};
	INT_CONF conf2={INT1_ID,FALLING_EDGE};
	INT_init(&conf1);
	INT_init(&conf2);

	/*set the interrupts ISR functions using call back technique*/
	set_ISR_functions();

	/* UART : works with 1 stop bit - no parity check - eight bits data length - 9600 baud rate*/
	config conf_uart={ONE,DISABLE,EIGHT_BITS,9600};
	UART_init(&conf_uart);
}

/* A function to set the call back ISR functions*/
void set_ISR_functions()
{
	/* interrupt zero to detect first motion */
	INT_setISR(TCRT1, 0);

	/* interrupt one to detect last motion */
	INT_setISR(TCRT2, 1);
}

/* A Function to convert a given integer to a string
 * copied from : https://www.sanfoundry.com/
 */
void tostring(char str[], int num)
{
    int i, rem, len = 0, n;

    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}

/* A function to detect the first motion at first sensor and start the timer*/
void TCRT1()
{
	/* Start timer counting */
	Timer1_ConfigType conf={0,0,N_1024,NORMAL};
	TIMER1_init(&conf);
}
/* A function to calculate the speed of the car by measuring the time it takes with a distance
 * and display it on LCD and send it to PC using UART
 * it also check the speed if it less than 15cm/sec then we are in safe and it will light a green for 1 sec
 * LED else it will illuminate a red led and the buzzer will work for 1 sec also
 */
void TCRT2()
{
	/* Get the timer value */
	uint16 tick = TIMER1_getTCRT();

	/* calculate the speed */
	uint16 speed = (uint16) (  ( (uint32) (DISTANCE_MUL_PRESCALER_OVER_CPU_FREQ) ) / tick);

	/* display the speed on LCD */
	LCD_moveCursor(0, 8);
	LCD_intgerToString(speed);

	/* Illuminate the RED LED and buzzer because the car speed exceeds the limit*/
	if(speed > 15){

		/* Turn the buzzer and led on*/
		Buzzer_on();
		RED_LED_on();

		/* wait 1 sec*/
		_delay_ms(1000);

		/* turn them off*/
		Buzzer_off();
		RED_LED_off();
	}

	/* Illuminate the GREEN LED and buzzer because the car speed doesn't exceed the limit*/
	else
	{
		/* The speed may be 1 digit which will lead an error on LCD , so we will display space after the speed*/
		LCD_displayString("  ");

		/* Turn on the green led*/
		GRN_LED_on();

		/*wait 1 sec*/
		_delay_ms(1000);

		/* Turn off the green led*/
		GRN_LED_off();
	}

	/* display the speed on tera terminal */
	send_to_terminal(speed);
}

/* a function to send the measured speed to PC to be displayed on tera terminal*/
void send_to_terminal(uint16 speed)
{
	uint8 *str;
	tostring(str,speed);

	UART_sendString("car speed = ");
	UART_sendString(str);
	UART_sendString(" cm/sec \n");
}
