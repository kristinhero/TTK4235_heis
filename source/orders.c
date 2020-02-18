#include "orders.h"
#include "fsm.h"

int orders_order_matrix[4][3] = {{0}};

Order current_order = {0,0};

void orders_clear_orders(){
     for(int r = 0; r < 4; r++){
        for(int c = 0; c < 3; c++){
            orders_order_matrix[r][c] = 0;
        } 
    }
};
void orders_remove_order(Order order){
    orders_order_matrix[order.floor][order.order_type] = 0;
};
void orders_add_order(Order order){
    orders_order_matrix[order.floor][order.order_type] = 1;
};

void orders_choose_next_order(){
    int current_floor = fsm_get_current_floor;
    switch(fsm_get_motor_direction())
    {
        case(FSM_MOTOR_DIRECTION_UP):
            for(int r = current_floor; r < 4; r++){
                for(int c = 0; c < 2; c++){
                    if(orders_order_matrix[r][c]){
                        current_order.floor = r;
                        current_order.order_type = c;
                        break;
                    }
                }
            }
            for(int r = current_floor; r < 4; r++){}
            for(int r = current_floor; r >= 0; r--){

                }
        break;
        case(FSM_MOTOR_DIRECTION_DOWN):
        break;    
    }
};