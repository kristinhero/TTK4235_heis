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

void fsm_set_state(FSMState new_state);
FSMState fsm_get_state();
void fsm_set_motor_direction();
FSMMotorDirection fsm_get_motor_direction();
void fsm_set_current_floor();
int fsm_get_current_floor();