typedef enum {
    FSM_MOTOR_DIRECTION_UP,
    FSM_MOTOR_DIRECTION_DOWN
} FSMMotorDirection;

typedef enum {
    FSM_INITIALIZE,
    FSM_IDLE,
    FSM_MOVING,
    FSM_OPEN,
    FSM_STOP
} FSMState;

int current_floor;
FSMState current_state;

void fsm_set_state(FSMState new_state){current_state = new_state;};
FSMState fsm_get_state(){return current_state;};