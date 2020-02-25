#include "orders.h"

int orders_order_matrix[HARDWARE_NUMBER_OF_FLOORS][3] = {{0}};

static int orders_above(int floor){
    int above = 0;
        for(int f = floor + 1; f < HARDWARE_NUMBER_OF_FLOORS; f++){
            for(int t = HARDWARE_ORDER_UP; t <= HARDWARE_ORDER_DOWN; t++){
                if(orders_order_matrix[f][t]){
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
                if(orders_order_matrix[f][t]){
                    below = 1;
                }
            }
        }
    return below;
};

void orders_clear_orders(){
     for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int t = HARDWARE_ORDER_UP; t <= HARDWARE_ORDER_DOWN; t++){
            orders_order_matrix[f][t] = 0;
            hardware_command_order_light(f,t,0);
        } 
    }
};
void orders_delete_order(int floor, HardwareOrder order_type){
    orders_order_matrix[floor][order_type] = 0;
    hardware_command_order_light(floor,order_type,0);
};
void orders_add_order(int floor, HardwareOrder order_type){
    orders_order_matrix[floor][order_type] = 1;
    hardware_command_order_light(floor,order_type,1);
};

int orders_to_handle(int floor, FSMDirection current_direction){
    switch(current_direction){
        case FSM_DIRECTION_UP:
            for(int t = HARDWARE_ORDER_UP; t <= HARDWARE_ORDER_INSIDE; t ++){
                if(orders_order_matrix[floor][t]){
                    return 1;
                }
            }
            if(!orders_above(floor) && orders_order_matrix[floor][HARDWARE_ORDER_DOWN]){
                return 1;
            } 
            return 0;
        case FSM_DIRECTION_DOWN:
            for(int t = HARDWARE_ORDER_INSIDE; t <= HARDWARE_ORDER_DOWN; t ++){
                    if(orders_order_matrix[floor][t]){
                        return 1;
                    }
                }
            if(!orders_below(floor) && orders_order_matrix[floor][HARDWARE_ORDER_UP]){
                return 1;
            }
            return 0;
    }
    return 0;
};

void orders_handled(int floor){
    for(int t = HARDWARE_ORDER_UP; t<= HARDWARE_ORDER_DOWN; t++){
            orders_delete_order(floor,t);
    }
};

FSMDirection orders_get_direction(int floor, FSMDirection current_direction){ //endre til peker?
        switch(current_direction){
            case FSM_DIRECTION_UP:
                // Hvis ordre over, sett retning opp
                if(orders_above(floor)){
                    return FSM_DIRECTION_UP;
                }
                // Hvis ikke, sett retning ned
                return FSM_DIRECTION_DOWN;
            case FSM_DIRECTION_DOWN: ;
                // Hvis ordre under, sett retning ned
                if(orders_below(floor)){
                    return FSM_DIRECTION_DOWN;
                }
                //Hvis ikke, sett retning opp
                return FSM_DIRECTION_UP;
            }
        return current_direction;
};

int orders_empty(){
    int empty = 1;
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int t = HARDWARE_ORDER_UP; t <= HARDWARE_ORDER_DOWN; t++){
            if(orders_order_matrix[f][t]){
                empty = 0;
            }
        } 
    }
    return empty;
};