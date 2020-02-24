#include "orders.h"

int orders_order_matrix[4][3] = {{0}};

int orders_above(int floor){
    int above = 0;
        for(int f = floor + 1; f < 4; f++){
            for(int t = 0; t < 3; t++){
                if(orders_order_matrix[f][t]){
                        above = 1;
                }
            }
        }
    return above;
};

int orders_below(int floor){
    int below = 0;
        for(int f = 0; f < floor; f++){
            for(int t = 0; t < 3; t++){
                if(orders_order_matrix[f][t]){
                    below = 1;
                }
            }
        }
    return below;
};

void orders_clear_orders(){
     for(int r = 0; r < 4; r++){
        for(int c = 0; c < 3; c++){
            orders_order_matrix[r][c] = 0;
            hardware_command_order_light(r,c,0);
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
            for(int t = 0; t < 2; t ++){
                if(orders_order_matrix[floor][t]){
                    return 1;
                }
            }
            if(!orders_above(floor) && orders_order_matrix[floor][HARDWARE_ORDER_DOWN]){
                return 1;
            } 
            return 0;
        case FSM_DIRECTION_DOWN:
            for(int t = 1; t < 3; t ++){
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

void orders_handled(int floor, FSMDirection current_direction){
    switch(current_direction){
        case FSM_DIRECTION_UP:
            for(int t = 0; t < 2; t ++){
                orders_delete_order(floor, t);
            }
            if(!orders_above(floor) && orders_order_matrix[floor][HARDWARE_ORDER_DOWN]){
                orders_delete_order(floor, HARDWARE_ORDER_DOWN);
            } 
            break;
        case FSM_DIRECTION_DOWN:
            for(int t = 1; t < 3; t ++){
                orders_delete_order(floor, t);
            }
            if(!orders_below(floor) && orders_order_matrix[floor][HARDWARE_ORDER_UP]){
                orders_delete_order(floor, HARDWARE_ORDER_UP);
            } 
            break;
    }
};

FSMDirection orders_get_direction(int floor, FSMDirection current_direction){ //endre til peker??
        switch(current_direction){
            case FSM_DIRECTION_UP:
                // Hvis ordre over, sett retning opp
                if(orders_above(floor)){
                    return FSM_DIRECTION_UP;
                }
                // Hvis ikke, slett ordre ned i current floor og sett retning ned
                orders_order_matrix[floor][HARDWARE_ORDER_DOWN] = 0;
                return FSM_DIRECTION_DOWN;

            case FSM_DIRECTION_DOWN: ;
                // Hvis ordre under, sett retning ned
                if(orders_below(floor)){
                    return FSM_DIRECTION_DOWN;
                }
                //Hvis ikke, slett ordre opp i current floor og sett retning opp
                orders_order_matrix[floor][HARDWARE_ORDER_UP] = 0;
                return FSM_DIRECTION_UP;
            }
        return current_direction;
};

int orders_empty(){
    int empty = 1;
    for(int r = 0; r < 4; r++){
        for(int c = 0; c < 3; c++){
            if(orders_order_matrix[r][c]){
                empty = 0;
            }
        } 
    }
    return empty;
};