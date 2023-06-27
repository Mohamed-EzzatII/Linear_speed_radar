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
#ifndef APP_H_
#define APP_H_

#include"std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define DISTANCE_MUL_PRESCALER_OVER_CPU_FREQ 234387

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/* Function to set the configurations of modules*/
void configurations(void);


/* A function to set the call back ISR functions*/
void set_ISR_functions();

/* A Function to convert a given integer to a string
 * copied from : https://www.sanfoundry.com/
 */
void tostring(char str[], int num);

/* A function to detect the first motion at first sensor and start the timer*/
void TCRT1();

/* A function to calculate the speed of the car by measuring the time it takes with a distance
 * and display it on LCD and send it to PC using UART
 * it also check the speed if it less than 15cm/sec then we are in safe and it will light a green for 1 sec
 * LED else it will illuminate a red led and the buzzer will work for 1 sec also
 */
void TCRT2();


/* a function to send the measured speed to PC to be displayed on tera terminal*/
void send_to_terminal(uint16 speed);
#endif /* APP_H_ */
