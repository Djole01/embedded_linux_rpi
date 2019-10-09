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
#include <sys/time.h>

volatile int eventCounter = 0;

unsigned long last_interrupt_time = 0;



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
	unsigned long interrupt_time = millis();
	//struct timeval now;
	//gettimeofday(&now, NULL);
	//printf("time taken %f\n",secs);

	if (interrupt_time - last_interrupt_time > 500)
	{
		eventCounter++;
		printf("ext_int_1 received\n");
		printf("Events so far: %d\n",eventCounter);
	}
	last_interrupt_time = interrupt_time;

}

int io_interrupt_init(void) {
	wiringPiISR(EXT_INT_PIN_1, INT_EDGE_RISING, ext_int1_handler);
	return 0;
}
