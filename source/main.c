#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "orders.h"


/*static void sigint_handler(int sig){
    (void)(sig);
    printf("Terminating elevator\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}
*/

int main(){
    orders_add_order(2,HARDWARE_ORDER_UP);
    /*
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
    signal(SIGINT, sigint_handler);

    hardware_command_movement(HARDWARE_MOVEMENT_UP);

    while(1){
        if(hardware_read_floor_sensor(2)){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        }
        if(hardware_read_obstruction_signal()){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        }
        if(hardware_read_stop_signal()){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            break;
        }
    }
    */
    return 0;
}
