/**
 * @file
 * @brief Functions to stop and start timer, and detect a timeout.
 */
#ifndef TIMER_H
#define TIMER_H
#include <sys/time.h>

/**
 * @brief Start timer with a given @p duration
 * 
 * @param[in] duration
 */
void timer_start(double duration);

/**
 * @brief Stop timer.
 * 
 * Make timer inactive.
 */
void timer_stop();

/**
 * @brief Check if timer has timed out. 
 * 
 * Check if the duration has passed and the timer is active.
 * 
 * @return 1 if the timer has timed out; 0 if not.
 */
int timer_timeout();

#endif