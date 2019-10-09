/*
 * timers_init.c
 *
 *  Created on: 17 Sep 2019
 *      Author: Jarno Tuominen
 */


/* Timer initialization routines and handlers */

#include <signal.h>
#include <sys/time.h>
#include <time.h>
#include <string.h> //needed by memset
#include <stdio.h>

/* Let's create the global timer objects */
timer_t firstTimerID;
timer_t secondTimerID;
timer_t thirdTimerID;



/**@brief Common handler for all the timers
 *
 * @details
 */
static void timerHandler( int sig, siginfo_t *si, void *uc )
{
    timer_t *tidp;
    tidp = si->si_value.sival_ptr;
    //todo: change to switch/case
    if ( *tidp == firstTimerID ) {
    	printf ("Timer 1 says hello!\n");
    } else if ( *tidp == secondTimerID ) {
    	printf ("Timer 2 says hello!\n");
    } else if ( *tidp == thirdTimerID ) {
    	printf ("Timer 3 says hello!\n");
    }
}


/**@brief Function for creating a timer
 *
 * @details
 */
static int makeTimer(timer_t *timerID, int expire_msec, int interval_msec )
{
    struct sigevent         te;
    struct itimerspec       its;
    struct sigaction        sa;
    int sigNo = SIGRTMIN;

    /* Set up signal handler. */
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = timerHandler;
    sigemptyset(&sa.sa_mask);

    if (sigaction(sigNo, &sa, NULL) == -1) {
    	printf ("Failed to setup signal handling for timer\n");

        return(-1);
    }

    /* Set and enable alarm */
    te.sigev_notify = SIGEV_SIGNAL;
    te.sigev_signo = sigNo;
    te.sigev_value.sival_ptr = timerID;
    timer_create(CLOCK_REALTIME, &te, timerID);

    its.it_value.tv_sec = (int) expire_msec/1000;
    its.it_value.tv_nsec = (expire_msec % 1000) * 1000000;
    its.it_interval.tv_sec = (int) interval_msec/1000;
    its.it_interval.tv_nsec = (interval_msec % 1000) * 1000000;

    timer_settime(*timerID, 0, &its, NULL);
    return(0);
}



/**@brief Function for the Timer initialization.
 *
 * @details Initializes the timer module. Also creates application timers.
 * @todo 	Revise error handling
 */
int timers_init(void)
{
	int err_code;

	//Create some timers
	err_code = makeTimer(&firstTimerID, 5e3, 5e3); //5s
	if (err_code != 0) {
		return err_code;
	}
	err_code = makeTimer(&secondTimerID, 3e3, 3e3); //3s
	if (err_code != 0) {
			return err_code;
	}
	err_code = makeTimer(&thirdTimerID, 15e3, 15e3); //15s
	if (err_code != 0) {
			return err_code;
	}

	return 0;

}
