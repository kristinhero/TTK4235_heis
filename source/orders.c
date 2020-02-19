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

// Forsøk på å prioritere ordre
int orders_choose_next_order(){
    int current_floor = fsm_get_current_floor;
    switch(fsm_get_motor_direction())
    {
        case(FSM_MOTOR_DIRECTION_UP):
            //Sjekker etasjer over for ordre opp eller cab orders
            for(int r = current_floor + 1; r < 4; r++){
                for(int c = 0; c < 2; c++){
                    if(orders_order_matrix[r][c]){
                        current_order.floor = r;
                        current_order.order_type = c;
                        return 0;
                    }
                }
            }
            //Sjekker etasjer over for ordre ned
            for(int r = current_floor + 1; r < 4; r++){
                if(orders_order_matrix[r][HARDWARE_ORDER_DOWN]){
                    current_order.floor = r;
                    current_order.order_type = HARDWARE_ORDER_DOWN;
                    return 0;
                }
            }
            //Sjekker nåværende etasje for ordre ned
            if(orders_order_matrix[current_floor][HARDWARE_ORDER_DOWN]){
                current_order.floor = current_floor;
                current_order.order_type = HARDWARE_ORDER_DOWN;
                return 0;
            }
            //Sjekker etasjer under for ordre ned
            for(int r = current_floor - 1; r >= 0; r--){
                if(orders_order_matrix[r][HARDWARE_ORDER_DOWN]){
                    current_order.floor = r;
                    current_order.order_type = HARDWARE_ORDER_DOWN;
                    return 0;
                }

            }
            //Sjekker etasjer under for ordre opp eller cab orders
            for(int r = current_floor - 1; r >= 0; r--){
                return 0;
            }

            //Ingenting funnet, returner feilmelding
        return 1;
        case(FSM_MOTOR_DIRECTION_DOWN):
        return 1;    
    }
};