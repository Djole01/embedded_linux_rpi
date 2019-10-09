/*
 * ioconfig.c
 *
 *  Created on: 17 Sep 2019
 *      Author: Jarno Tuominen
 */


#include <stddef.h> // NULL comes from here :D
#include <stdio.h> //Needed for printf

#include "wiringPi.h"
#include "ioconfig.h"

volatile int eventCounter = 0;

int io_init(void) {


	int err_code;

	err_code = wiringPiSetup();

	//Init one pin to be used as debug pin
	pinMode(DEBUG_PIN_1, OUTPUT); //Not needed!
	digitalWrite(DEBUG_PIN_1, HIGH);
	delay(50);
	digitalWrite(DEBUG_PIN_1, LOW);

	return(err_code);
}


void ext_int1_handler(void) {
	//struct timeval now;
	//gettimeofday(&now, NULL);
	eventCounter++;
	printf("ext_int_1 received\n");
	printf("Events so far: %d\n",eventCounter);
}

int io_interrupt_init(void) {
	wiringPiISR(EXT_INT_PIN_1, INT_EDGE_RISING, ext_int1_handler);
	return 0;
}
