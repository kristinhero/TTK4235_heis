#include "timer.h"

static double timer_get_current_time(){
    struct timeval time;
    gettimeofday(&time, 0);
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}


static  double timer_end_time;
static  int timer_active;

void timer_start(double duration){
    timer_end_time    = timer_get_current_time() + duration;
    timer_active     = 1;
}

void timer_stop(){
    timer_active = 0;
}

int timer_timeout(){
    return (timer_active  &&  timer_get_current_time() > timer_end_time);
}