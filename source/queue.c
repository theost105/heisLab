#include "queue.h"

void calculate_queue_data(elevator *elevator){
    //register new button taps
    
    int queue_next_floor_target;
    int queue_list_1st_priority[N_FLOORS+1];
    int queue_list_2nd_priority_up[N_FLOORS+1]; //last element is invalid
    int queue_list_2nd_priority_down[N_FLOORS+1];
    int queue_is_headed_up;

    add_queue_orders(elevator);

    //check if 1st priority orders are in the queue_is_headed_up direction.
    for (int floor = 1; floor <= N_FLOORS; floor++){

    }

    //check if 1st priority orders are in the not queue_is_headed_up direction.

    
}

void add_queue_orders(elevator *elevator) {
    //Add first priority orders
    for (int floor = 1; floor <= N_FLOORS; floor++){
        if (elevator->sensor_indoor_order_floor_button[floor] == 1){
            elevator->queue_list_1st_priority[floor] = 1;
        }    
    }

    //add second priority orders up
    for (int floor = 1; floor < N_FLOORS; floor++){
        if (elevator->sensor_outdoor_button[floor][0] == 1){
            elevator->queue_list_2nd_priority[floor][0] = 1;
        }    
    }
    //add second priority orders down
    for (int floor = 2; floor <= N_FLOORS; floor++){
        if (elevator->sensor_outdoor_button[floor][1] == 1){
            elevator->queue_list_2nd_priority[floor][1] = 1;
        }    
    }
}

void init_queue(elevator *elevator){
    for (int element = 0; element <= N_FLOORS; element++){
        elevator->queue_list_1st_priority[element] = 0;
        elevator->queue_list_2nd_priority[element][0] = 0;
        elevator->queue_list_2nd_priority[element][1] = 0;
    }
    
}