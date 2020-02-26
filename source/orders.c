#include "orders.h"

int orders_matrix[HARDWARE_NUMBER_OF_FLOORS][3] = {{0}};

static int orders_above(int floor){
    int above = 0;
    for(int f = floor + 1; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int t = HARDWARE_ORDER_UP; t <= HARDWARE_ORDER_DOWN; t++){
            if(orders_matrix[f][t]){
                above = 1;
            }
        }
    }
    return above;
};

static int orders_below(int floor){
    int below = 0;
    for(int f = 0; f < floor; f++){
        for(int t = HARDWARE_ORDER_UP; t <= HARDWARE_ORDER_DOWN; t++){
            if(orders_matrix[f][t]){
                below = 1;
            }
        }
    }
    return below;
};

static void orders_delete_order(int floor, HardwareOrder order_type){
    orders_matrix[floor][order_type] = 0;
    hardware_command_order_light(floor,order_type,0);
};

void orders_clear_orders(){
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int t = HARDWARE_ORDER_UP; t <= HARDWARE_ORDER_DOWN; t++){
            orders_matrix[f][t] = 0;
            hardware_command_order_light(f,t,0);
        } 
    }
};
int orders_empty(){
    int empty = 1;
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int t = HARDWARE_ORDER_UP; t <= HARDWARE_ORDER_DOWN; t++){
            if(orders_matrix[f][t]){
                empty = 0;
            }
        } 
    }
    return empty;
};
void orders_add_order(int floor, HardwareOrder order_type){
    orders_matrix[floor][order_type] = 1;
    hardware_command_order_light(floor,order_type,1);
};

int orders_to_handle(int floor, FSMDirection * p_current_direction){
    switch(*p_current_direction){
        case FSM_DIRECTION_UP:
            for(int t = HARDWARE_ORDER_UP; t <= HARDWARE_ORDER_INSIDE; t ++){
                if(orders_matrix[floor][t]){
                    return 1;
                }
            }
            if(!orders_above(floor) && orders_matrix[floor][HARDWARE_ORDER_DOWN]){
                return 1;
            } 
            return 0;
        case FSM_DIRECTION_DOWN:
            for(int t = HARDWARE_ORDER_INSIDE; t <= HARDWARE_ORDER_DOWN; t ++){
                if(orders_matrix[floor][t]){
                    return 1;
                }
            }
            if(!orders_below(floor) && orders_matrix[floor][HARDWARE_ORDER_UP]){
                return 1;
            }
            return 0;
        default:
            return 0;
    }
};

void orders_handled(int floor){
    for(int t = HARDWARE_ORDER_UP; t<= HARDWARE_ORDER_DOWN; t++){
        orders_delete_order(floor,t);
    }
};

void orders_get_direction(int floor, FSMDirection * p_current_direction){
    switch(*p_current_direction){
        case FSM_DIRECTION_UP:
            if(!orders_above(floor)){
                *p_current_direction = FSM_DIRECTION_DOWN;
            }
        case FSM_DIRECTION_DOWN: ;
            if(!orders_below(floor)){
                *p_current_direction = FSM_DIRECTION_UP;
            }
        }
};