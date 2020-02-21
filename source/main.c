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

void clear_all_button_lights(){
    for(int f = 0; f < 4; f++){
            for(int t = 0; t < 3; t++){
                    hardware_command_order_light(f,t,0);
            }
        }
    hardware_command_stop_light(0);
}

void clear_order_lights_at_floor(int floor){
    for(int t = 0; t < 3; t++){
        hardware_command_order_light(floor, t, 0);
    }
}

int main(){
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
    signal(SIGINT, sigint_handler);

    clear_all_button_lights();
    hardware_command_movement(HARDWARE_MOVEMENT_UP);

    while(1){
        for(int f = 0; f < 4; f++){
            if(hardware_read_floor_sensor(f)){
                fsm_floor_reached(f);
            }
            for(int t = 0; t < 3; t++){
                if(hardware_read_order(f,t)){
                    fsm_new_order(f,t);
                }
            }
        }
        /*
        for(int f = 0; f < 4; f++){
            if(hardware_read_floor_sensor(f)){
                hardware_command_floor_indicator_on(f);
                if(orders_check_orders_at_floor(f)){
                    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                    orders_delete_orders_at_floor(f);
                    clear_order_lights_at_floor(f);
                }
            }
            for(int t = 0; t < 3; t++){
                if(hardware_read_order(f,t)){
                    hardware_command_order_light(f,t,1);
                    orders_add_order(f,t);
                }
            }
        }
        if(hardware_read_floor_sensor(3)){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            hardware_command_door_open(1);
        }
        if(hardware_read_stop_signal()){
            hardware_command_stop_light(1);
        }
    */
    }
    return 0;
}
