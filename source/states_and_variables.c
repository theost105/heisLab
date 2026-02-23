#include "states_and_variables.h"


void recieve_elevator_data(elevator *elevator) {
    recieve_button_data(elevator);
    recieve_sensor_data(elevator);
}

void calculate_elevator_data(elevator *elevator){
    calculate_queue_data(elevator);
    calculate_primary_state(elevator);
    //maybe we need to add a calculate primary_state data. 
    //Or maybe that variable is directly calculated in calculate_motor_data(..)
    calculate_motor_data(elevator);
    calculate_lights_data(elevator);
}

void send_elevator_data(elevator *elevator){
    send_motor_data(elevator);
    send_lights_data(elevator);
}

void init_elevator(elevator *elevator){
    recieve_elevator_data(elevator);
    elevator->motor_direction = 0;
    elevator->timer = 0;
    elevator->queue_next_floor_target = -1; //set an invalid target
    elevator->elevator_state = INITIALIZING; //unsure about this.
}


void calculate_primary_elevator_state(elevator *elevator){
    switch (elevator->elevator_state)
    {
    case WAIT:
        if (elevator->timer * timer_sleep_timestep == timer_wait_time && 
            elevator->sensor_obstruction == 0){
            
            elevator->elevator_state = IDLE;
        } 
        break;

    case TRANSIT:
        if (elevator->sensor_floor_detected == elevator->queue_next_floor_target){
            elevator->elevator_state = WAIT;
        }
        break;

    case IDLE:
        if (elevator->queue_next_floor_target != -1){
            elevator->elevator_state = TRANSIT;
        }
        break;
    
    case INITIALIZING:
        if (elevator->sensor_floor_detected != -1){
            elevator->elevator_state = IDLE;
        }
        break;    
    }
}