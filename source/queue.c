#include "queue.h"

void calculate_queue_data(elevator *elevator){
    //register new button taps
    
    /*
    int queue_next_floor_target;
    int queue_list_1st_priority[N_FLOORS+1];
    int queue_list_2nd_priority_up[N_FLOORS+1]; //last element is invalid
    int queue_list_2nd_priority_down[N_FLOORS+1];
    int queue_is_headed_up;
    */
    
    add_queue_orders(elevator);

    //Set direction based on 1st priority order
    int has_1st_priority_order = 0;
    for (int floor = 1; floor <= N_FLOORS; floor++){
        if (elevator->queue_list_1st_priority[floor] == 1){
            has_1st_priority_order = 1;
        }
    }
    
    if (has_1st_priority_order){
        //check if 1st priority orders are in the queue_is_headed_up direction.
        if (elevator->queue_is_headed_up){
            for (int floor = elevator->last_floor_detected; floor <= N_FLOORS; floor++){
                
                if(elevator->queue_list_1st_priority[floor] == 1 ){
                    //set next floor target on the first next floor in the up direction
                    elevator->queue_next_floor_target = floor;
                    break;
                }
                //if no target is made: then change direction to down.
                elevator->queue_is_headed_up = 0;
            }        
        } 
        //same, down direction
        if (!elevator->queue_is_headed_up) { 
            for (int floor = elevator->last_floor_detected; floor > 0; floor--){
                if(elevator->queue_list_1st_priority[floor] == 1){
                    elevator->queue_next_floor_target = floor;
                    break;
                }
                //if no target is made: then change direction to up.
                elevator->queue_is_headed_up = 1;
            }
        }
        //check again in the up direction, in case the direction changed from down to up.
        if (elevator->queue_is_headed_up){
            for (int floor = elevator->last_floor_detected; floor <= N_FLOORS; floor++){
                
                if(elevator->queue_list_1st_priority[floor] == 1 ){
                    //set next floor target on the first next floor in the up direction
                    elevator->queue_next_floor_target = floor;
                    break;
                }
                //if no target is made: then change direction to down.

                elevator->queue_is_headed_up = 0;
            }        
        }  
    }
    //check if there are any 2nd priority orders in between last_floor_detected and queue_next_floor_target. Set the nearest one as target
    int has_2nd_priority_order = 0;
    for (int floor = 1; floor <= N_FLOORS; floor++){
        if (elevator->queue_list_2nd_priority[floor][0] == 1 || elevator->queue_list_2nd_priority[floor][1] == 1){
            has_2nd_priority_order = 1;
    }
    if (has_2nd_priority_order && has_1st_priority_order){

        //check if orders are in between in the direction up
        if (elevator->queue_is_headed_up == 1){
            for (int floor = elevator->last_floor_detected; floor < elevator->queue_next_floor_target; floor++){
                if (elevator->queue_list_2nd_priority[floor][0] == 1){
                    elevator->queue_next_floor_target = floor;
                    break;
                }
            }
        }
        //check if orders are in between in the direction down
        if (elevator->queue_is_headed_up == 0){
            for (int floor = elevator->last_floor_detected; floor > elevator->queue_next_floor_target; floor--){
                if (elevator->queue_list_2nd_priority[floor][1] == 1){
                    elevator->queue_next_floor_target = floor;
                    break;
                }
            }
        }
    }

    if (has_2nd_priority_order && !has_1st_priority_order){
        //choose the nearest order in the queue_is_headed_up direction.
        // for loop if up direction
        // for loop if down direction


        //if there is no order in the queue_is_headed_up direction, then choose the nearest order in the other direction
    }




    
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