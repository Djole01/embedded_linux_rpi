/*
 * main.c
 *
 *  Created on: 2.10.2019
 *      Author: emb linux
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "ioconfig.h"
#include "timers_init.h"


int main(void)
{

	io_init();
	io_interrupt_init();

	 while(1)
	 {

	 }



	return 0;
}
