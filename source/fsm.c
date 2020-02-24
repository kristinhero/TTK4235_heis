#include "fsm.h"

int current_floor;
FSMState current_state = FSM_MOVING;
FSMDirection current_direction;

void fsm_move(){
    if(current_direction == FSM_DIRECTION_UP){
            hardware_command_movement(HARDWARE_MOVEMENT_UP);
    } else {
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    }
}

void fsm_initialize(){
    current_state = FSM_INITIALIZE;
    current_direction = FSM_DIRECTION_DOWN;
    fsm_move();
}

void fsm_floor_reached(int floor){
        current_floor = floor;
        switch (current_state)
        {
        case FSM_INITIALIZE:
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            current_state = FSM_IDLE;
            break;
        case FSM_IDLE:
            break;
        case FSM_MOVING:
            hardware_command_floor_indicator_on(floor);
            if(orders_to_handle(floor, current_direction)){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                hardware_command_door_open(1);
                timer_start(3);
                current_state = FSM_OPEN;
            }
            break;
        case FSM_OPEN:
            break;
        case FSM_STOP:
            break;
        default:
            break;
        }
};
void fsm_timeout(){
            switch (current_state)
        {
        case FSM_INITIALIZE:
            break;
        case FSM_IDLE:
            break;
        case FSM_MOVING:
            break;
        case FSM_OPEN:
            timer_stop;
            hardware_command_door_open(0);
            orders_handled(current_floor, current_direction); // skal denne være her?
            if(orders_empty()){
                current_state = FSM_IDLE;
            } else {
                current_direction = orders_get_direction(current_floor, current_direction);
                fsm_move();
                current_state = FSM_MOVING;
            }
            break;
        case FSM_STOP:
            break;
        default:
            break;
        }
};
void fsm_new_order(int floor, HardwareOrder order_type){
    switch (current_state)
        {
        case FSM_INITIALIZE:
            break;
        case FSM_IDLE:
            orders_add_order(floor,order_type);
            if(floor == current_floor){
                hardware_command_door_open(1);
                timer_start(3);
                current_state = FSM_OPEN;
            } else {
                if(floor > current_floor){
                current_direction = FSM_DIRECTION_UP;
            } else {
                current_direction = FSM_DIRECTION_DOWN;
                }
                fsm_move();
                current_state = FSM_MOVING;
            }
            break;
        case FSM_MOVING:
            orders_add_order(floor,order_type);
            break;
        case FSM_OPEN:
            orders_handled(floor, current_direction);
            if(orders_to_handle(current_floor, current_direction)){
                timer_start(3);
            }
            break;
        case FSM_STOP:
            break;
        default:
            break;
        }
};
void fsm_stop_pressed();
void fsm_stop_released();
void fsm_obstruction_detected();
void fsm_obstruction_removed();


/*
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
*/