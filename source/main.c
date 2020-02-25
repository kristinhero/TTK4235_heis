#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "fsm.h"


static void sigint_handler(int sig){
    (void)(sig);
    printf("Terminating elevator\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}

int main(){
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
    signal(SIGINT, sigint_handler);
    fsm_initialize();

    while(1){
        for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
            if(hardware_read_floor_sensor(f)){
                fsm_floor_reached(f);
            }
            for(int t = HARDWARE_ORDER_UP; t <= HARDWARE_ORDER_DOWN; t++){
                if(hardware_read_order(f,t)){
                    fsm_new_order(f,t);
                }
            }
        }
        if(timer_timeout()){
            fsm_timeout();
        }
        if(hardware_read_obstruction_signal()){
            fsm_obstruction_detected();
        } 
        if(hardware_read_stop_signal()){
            fsm_stop_pressed();
        } else {
            fsm_stop_released();
        }
    }
    return 0;
}
