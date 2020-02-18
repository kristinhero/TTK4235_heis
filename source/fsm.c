#include "fsm.h"

int current_floor;
FSMState current_state;
FSMMotorDirection current_direction;

void fsm_set_state(FSMState new_state){
    current_state = new_state;
};
FSMState fsm_get_state(){
    return current_state;
};

FSMMotorDirection fsm_get_motor_direction(){
    return current_direction;
};

int fsm_get_current_floor(){
    return current_floor;
};