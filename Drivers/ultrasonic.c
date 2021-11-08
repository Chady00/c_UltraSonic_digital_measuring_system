/**************************
 *
 * Module: ULTRASONIC
 *
 * File Name: ultrasonic.c
 *
 * Description: Source file for the ULTRASONIC driver
 *
 * Author: Chady Achraf
 *
 ***************************/
#include"ultrasonic.h"
#include"icu.h"
#include"gpio.h"
#include"std_types.h"
#include"common_macros.h"
#include<util/delay.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
/*global variable to hold the value of callback function entry count.*/
uint8 count = 0;
/*global variable to hold the value of high time produced by the signal from rising to falling edge.
 */
uint16 first_high = 0;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description :
 * Initialize ICU configuration.
 * SetCall back function.
 * Set PINB5 as output pin, with initial value: LOGIC_LOW.
 */
void Ultrasonic_init(void) {

	/*Initializing the ICU configuration:
	 * Frequency: FCPU/8
	 * Triggered by: RISING edge
	 */
	Icu_ConfigType Icu_Config = { F_CPU_8, RISING };
	Icu_init(&Icu_Config);

	/* Setup the call back function pointer to ultrasonic driver:
	 * Ultrasonic_edgeProcessing
	 */
	Icu_setCallBack(Ultrasonic_edgeProcessing);

	/*Setup the direction for the trigger pin as output pin through the GPIO driver*/
	GPIO_setupPinDirection(PORTB_ID, PIN5_ID, PIN_OUTPUT);
	/*Initialize the pin value*/
	GPIO_writePin(PORTB_ID, PIN5_ID, LOGIC_LOW);

}

/*
 * Description :
 * This function is used to generate a 10us trigger.
 * Set PORTB5 as LOGIC_HIGH , then delay , then set PORTB5 as LOGIC_LOW.
 *
 */
void Ultrasonic_Trigger(void) {
	/*Writing logic high to pinD5*/
	GPIO_writePin(PORTB_ID, PIN5_ID, LOGIC_HIGH);

	_delay_us(10);

	/*Writing logic low to pinD5 to end the trigger pulse*/
	GPIO_writePin(PORTB_ID, PIN5_ID, LOGIC_LOW);
}

/*
 * Description :
 * Calls the trigger function to generate a 10us pulse.
 * Polling until the value of the first_high is updated.
 * distance = first_high /58.8.
 * return distance.
 */
uint16 Ultrasonic_readDistance(void) {
	/*Send the trigger pulse by using Ultrasonic_Trigger function*/
	uint16 distance;
	Ultrasonic_Trigger();

	while (first_high == 0)
		;

	//  while(1){LCD_intgerToString(first_high);_delay_ms(1241224);}
	distance = ((float) first_high / 58.823529);

	first_high = 0;

	return distance;
}

/*
 * Description :
 * Call back function handling ICU interrupts.
 * Updates the value of first_high from rising to falling edge.
 */
void Ultrasonic_edgeProcessing(void) {
	/*Start calculating the signal period */
	count++;
	if (count == 1) {
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		Icu_clearTimerValue();
		/* Detect falling edge */
		Icu_setEdgeDetectionType(FALLING);
	} else if (count == 2) {
		/* Store the High time value */
		first_high = Icu_getInputCaptureValue();
		/* Detect rising edge */
		Icu_setEdgeDetectionType(RISING);
		count = 0;
	}

}
