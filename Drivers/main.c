/*
 ============================================================================
 Name        : MiniProject4.c
 Author      : Chady Achraf
 Copyright   : Your copyright notice
 Description : Mini_Project_4
 ============================================================================
 */

#include<avr/io.h>
#include<util/delay.h>
#include"gpio.h"
#include"lcd.h"
#include"common_macros.h"

uint32 distance = 0;

/*
 * Description :
 * Enable interrupts.
 * Initialize LCD_init , Ultrasonic_init.
 * Read Distance from ultrasonic_readDistance function.
 * Adjust Distance and display on LCD.
 */
int main() {
	/*Enable Interrupts in system*/
	SREG |= (1 << 7);

	/*Initialize the Ultrasonic function*/
	LCD_init();
	Ultrasonic_init();

	while (1) {
		/*Read the distance from the ultrasonic readDistance function*/
		distance = Ultrasonic_readDistance();

		/*Due to rounded float conversion , the distance is slightly adjusted*/
		if (distance < 57) {
			distance++;
		} else if (distance >= 57 && distance < 100) {
			distance += 2;
		} else if (distance >= 101 && distance <= 129) {
			distance += 2;
		} else if (distance >= 130 && distance < 200) {
			distance += 3;
		}

		/*Move the cursor and display the distance in cm*/
		LCD_moveCursor(0, 0);
		LCD_displayString("Distance= ");
		LCD_intgerToString(distance);
		LCD_displayString("cm ");

	}

}

