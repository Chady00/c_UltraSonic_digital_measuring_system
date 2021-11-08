 /******************************************************************************
 *
 * Module: ULTRASONIC
 *
 * File Name: ultrasonic.h
 *
 * Description: Header file for the ULTRASONIC driver
 *
 * Author: Chady Achraf
 *
 *******************************************************************************/
#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include"std_types.h"
#include"common_macros.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Initialize ICU configuration.
 * SetCall back function.
 * Set PINB5 as output pin, with initial value: LOGIC_LOW.
 */
void Ultrasonic_init(void);

/*
 * Description :
 * Call back function handling ICU interrupts.
 * Updates the value of first_high from rising to falling edge.
 */
void Ultrasonic_edgeProcessing(void);

/*
 * Description :
 * This function is used to generate a 10us trigger.
 * Set PORTB5 as LOGIC_HIGH , then delay , then set PORTB5 as LOGIC_LOW.
 *
 */
void Ultrasonic_Trigger(void);

/*
 * Description :
 * Calls the trigger function to generate a 10us pulse.
 * Polling until the value of the first_high is updated.
 * distance = first_high /58.8.
 * return distance.
 */
uint16 Ultrasonic_readDistance(void);

#endif /* ULTRASONIC_H_ */
