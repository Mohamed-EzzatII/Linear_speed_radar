

 /******************************************************************************
 *
 * Module: GRN_LED
 *
 * File Name: grn_red.c
 *
 * Description: Source file for the GRN_LED driver
 *
 * Author: Mohamed Ezzat
 *
 * Created on: April 24, 2023
 *
 * Version : v1.0.1
 *
 *******************************************************************************/

/************************Libraries and inclusions*******************************/

#include"common_macros.h"
#include<avr/io.h>
#include"grn_led.h"
#include"../MCAL/gpio.h"

/*******************************************************************************/

/*******************************************************************************/

/**********************************Functions************************************/

/*
 * Description :
 * A function to initialize the GRN_LED
 */
void GRN_LED_init(void)
{
	/*Make the GRN_LED pin output pin*/
	GPIO_setupPinDirection(GRN_LED_PORT,GRN_LED_PIN,PIN_OUTPUT);

	/*Turn off the GRN_LED*/
	GPIO_writePin(GRN_LED_PORT,GRN_LED_PIN,PIN_INPUT);
}

/*
 * Description :
 * A function to turn on the GRN_LED
 */
void GRN_LED_on(void)
{
	/*Turn on the GRN_LED*/
	GPIO_writePin(GRN_LED_PORT,GRN_LED_PIN,PIN_OUTPUT);
}

/*
 * Description :
 * A function to turn off the GRN_LED
 */
void GRN_LED_off(void)
{
	/*Turn off the GRN*/
	GPIO_writePin(GRN_LED_PORT,GRN_LED_PIN,PIN_INPUT);
}
