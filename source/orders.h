#include "hardware.h"

typedef struct {
    int floor;
    HardwareOrder order_type;
} Order;

void orders_clear_orders();
void orders_remove_order(Order order);
void orders_add_order(Order order);
void orders_choose_next_order();