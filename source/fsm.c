#include "fsm.h"
#include "hardware.h"

int current_floor;
FSMState current_state;
FSMMotorDirection current_direction;

void fsm_set_state(FSMState new_state){current_state = new_state};

void fsm_transition(FSMState new_state){
    switch(new_state){
        case(FSM_INITIALIZE):
        break;
        case(FSM_IDLE):
            switch(current_state){
                case(FSM_INITIALIZE):
                break;
                case(FSM_OPEN):
                hardware_command_door_open(0);
                break;
                case(FSM_STOP):
                hardware_command_stop_light(0);
                break;
            }
        break;
        case(FSM_MOVING):
        break;
        case(FSM_OPEN):
            //Set timer
            //Open doors
            //Remove orders at floor
            switch(current_state){
                case(FSM_IDLE):
                break;
                case(FSM_MOVING):
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                hardware_command_floor_indicator_on(current_floor);
                break;
                case(FSM_STOP):
                break;
            }
        break;
        case(FSM_STOP): 
            hardware_command_stop_light(1);
            //delete all orders
            switch(current_state){
                case(FSM_IDLE):
                //if at floor, open doors
                break;
                case(FSM_MOVING):
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                //if at floor, open doors
                break;
                case(FSM_OPEN):
                //interrupt timer
                break;
            }     
        break;
}
        fsm_set_state(new_state);
};
FSMState fsm_get_state(){
    return current_state;
};

FSMMotorDirection fsm_get_motor_direction(){
    return current_direction;
};

int fsm_get_current_floor(){
    return current_floor;
};
