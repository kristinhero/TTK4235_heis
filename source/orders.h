#ifndef ORDERS_H
#define ORDERS_H
#include "hardware.h"
#include "utilities.h"

int orders_above(int floor);
int orders_below(int floor);
void orders_clear_orders();
void orders_delete_order(int floor, HardwareOrder order_type);
void orders_add_order(int floor, HardwareOrder order_type);
int orders_to_handle(int floor, FSMDirection current_direction);
void orders_handled(int floor, FSMDirection current_direction);
FSMDirection orders_get_direction(int floor, FSMDirection current_direction);
int orders_empty();

#endif