#include "fsm.h"

int current_floor;
FSMState current_state = FSM_MOVING;
FSMDirection current_direction;

FSMDirection fsm_get_direction(){return current_direction;};
void fsm_set_direction(FSMDirection new_direction){ current_direction = new_direction;};

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
                orders_handled(floor, current_direction); // funksjonen skal endres
                hardware_command_door_open(1);
                // set timer
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
            hardware_command_door_open(0);
            if(orders_empty()){
                current_state = FSM_IDLE;
            } else {
                // velg retning
                current_direction = orders_get_direction(current_floor, current_direction);
                if(current_direction == FSM_DIRECTION_UP){
                    hardware_command_movement(HARDWARE_MOVEMENT_UP);
                } else {
                    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
                }
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
            break;
        case FSM_MOVING:
            orders_add_order(floor,order_type);
            break;
        case FSM_OPEN:
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