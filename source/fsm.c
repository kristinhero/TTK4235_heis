#include "fsm.h"

static FSMPosition current_position;
static FSMState current_state;
static FSMDirection current_direction;
static double door_open_duration = 3;

static void fsm_between_floors(){
    current_position.above = 1;
    if(current_direction == FSM_DIRECTION_DOWN){
        current_position.floor --;
    }
}


static void fsm_move(){
    if(current_direction == FSM_DIRECTION_UP){
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
    } else {
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    }
    if(!current_position.above){
        fsm_between_floors();
    }
}
static void fsm_clear_all_button_lights(){
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int t = HARDWARE_ORDER_UP; t <= HARDWARE_ORDER_DOWN; t++){
            hardware_command_order_light(f,t,0);
        }
    }
    hardware_command_stop_light(0);
}
void fsm_initialize(){
    fsm_clear_all_button_lights();
    current_state = FSM_INITIALIZE;
    current_direction = FSM_DIRECTION_DOWN;
    fsm_move();
}

void fsm_floor_reached(int floor){
    current_position.floor = floor;
    current_position.above = 0;
    hardware_command_floor_indicator_on(floor);
    switch (current_state)
        {
        case FSM_INITIALIZE:
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            current_state = FSM_IDLE;
            break;
        case FSM_MOVING:
            if(orders_to_handle(floor, &current_direction)){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                hardware_command_door_open(1);
                timer_start(door_open_duration);
                orders_handled(current_position.floor);
                current_state = FSM_OPEN;
            } else {
                fsm_between_floors();
            }
            break;
        default:
            break;
        }
};
void fsm_new_order(int floor, HardwareOrder order_type){
    switch (current_state)
        {
        case FSM_IDLE:
            orders_add_order(floor,order_type);
            if(!current_position.above && floor == current_position.floor){
                hardware_command_door_open(1);
                timer_start(door_open_duration);
                orders_handled(current_position.floor);
                current_state = FSM_OPEN;
            } else {
                if(floor > current_position.floor){
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
            orders_add_order(floor, order_type);
            if(orders_to_handle(current_position.floor, &current_direction)){
                timer_start(door_open_duration);
                orders_handled(current_position.floor);
            }
            break;
        default:
            break;
        }
};
void fsm_timeout(){
    switch (current_state)
        {
        case FSM_OPEN:
            timer_stop();
            hardware_command_door_open(0);
            if(orders_empty()){
                current_state = FSM_IDLE;
            } else {
                orders_get_direction(current_position.floor, &current_direction);
                fsm_move();
                current_state = FSM_MOVING;
            }
            break;
        default:
            break;
        }
};
void fsm_obstruction_detected(){
    switch (current_state)
        {
        case FSM_OPEN:
            timer_start(door_open_duration);
            break;
        default:
            break;
        }
};
void fsm_stop_pressed(){
    hardware_command_stop_light(1);
    orders_clear_orders();
    switch (current_state)
        {
        case FSM_IDLE:
            if(!current_position.above){
                hardware_command_door_open(1);
                timer_start(door_open_duration);
            }
            current_state = FSM_STOP;
            break;
        case FSM_MOVING:
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            current_state = FSM_STOP;
            break;
        case FSM_OPEN:
            timer_start(door_open_duration);
            current_state = FSM_STOP;
            break;
        case FSM_STOP:
            timer_start(door_open_duration);
            break;
        default:
            break;
        }
};
void fsm_stop_released(){
    switch (current_state)
        {
        case FSM_STOP:
            hardware_command_stop_light(0);
            if(!current_position.above){
                current_state = FSM_OPEN;
            } else {
                current_state = FSM_IDLE;
            }
            break;
        default:
            break;
        }
};
