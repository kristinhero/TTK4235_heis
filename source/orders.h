#ifndef ORDERS_H
#define ORDERS_H
#include "hardware.h"
#include "fsm_types.h"

void orders_clear_orders();
void orders_delete_order(int floor, HardwareOrder order_type);
void orders_add_order(int floor, HardwareOrder order_type);
int orders_to_handle(int floor, FSMDirection * p_current_direction);
void orders_handled(int floor);
void orders_get_direction(int floor, FSMDirection * p_current_direction);
int orders_empty();

#endif