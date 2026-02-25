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
    if (elevator->elevator_state == INITIALIZING){return;} //cancel queue calculation if Initializing


    add_queue_orders(elevator);

    clear_finished_queue_orders(elevator);

    calculate_direction_and_next_floor_target(elevator);

    
    
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

void calculate_direction_and_next_floor_target(elevator *elevator) {
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

            int target_was_made = 0;
            for (int floor = elevator->last_floor_detected; floor <= N_FLOORS; floor++){
                
                if(elevator->queue_list_1st_priority[floor] == 1 ){
                    //set next floor target on the first next floor in the up direction
                    elevator->queue_next_floor_target = floor;
                    target_was_made = 1;
                    break;
                }
                
                
            }   
            //if no target is made: then change direction to down.
            if (!target_was_made){
                elevator->queue_is_headed_up = 0;
            }     
        } 
        //same, down direction
        if (!elevator->queue_is_headed_up) { 
            int target_was_made = 0;

            for (int floor = elevator->last_floor_detected; floor > 0; floor--){
                if(elevator->queue_list_1st_priority[floor] == 1){
                    elevator->queue_next_floor_target = floor;
                    target_was_made = 1;
                    break;
                }
                
            }

            //if no target is made: then change direction to up.
            if (!target_was_made){
                elevator->queue_is_headed_up = 1;
            } 
        }
        //check again in the up direction, in case the direction changed from down to up.
        if (elevator->queue_is_headed_up){
            int target_was_made = 0;

            for (int floor = elevator->last_floor_detected; floor <= N_FLOORS; floor++){
                
                if(elevator->queue_list_1st_priority[floor] == 1 ){
                    //set next floor target on the first next floor in the up direction
                    elevator->queue_next_floor_target = floor;
                    target_was_made = 1;
                    break;
                }
            }
            //if no target is made: then change direction to down. but something was wrong
            if (!target_was_made){
                elevator->queue_is_headed_up = 0;
                printf("A 1st priority target was not hit when it should have been");
            }     
        }  
    }


    //check if there are any 2nd priority orders in between last_floor_detected and queue_next_floor_target. Set the nearest one as target
    
    int has_2nd_priority_order = 0;
    for (int floor = 1; floor <= N_FLOORS; floor++){
        if (elevator->queue_list_2nd_priority[floor][0] == 1 || elevator->queue_list_2nd_priority[floor][1] == 1){
            has_2nd_priority_order = 1;
        }
    }
    printf("has 1st priority: %d, has 2nd priority: %d\n", has_1st_priority_order, has_2nd_priority_order);
    
    if (has_2nd_priority_order && has_1st_priority_order){
        printf("both");
        
        //check if orders are in between in the direction up
        if (elevator->queue_is_headed_up == 1){
            printf("is headed up");
            printf("next floor target: %d\n", elevator->queue_next_floor_target);
            printf("Last_floor_detected: %d\n", elevator->last_floor_detected);
                    
            for (int floor = elevator->last_floor_detected; floor < elevator->queue_next_floor_target; floor++){
                printf("elevator->queue_list_2nd_priority[floor][0]: %d\n ", elevator->queue_list_2nd_priority[floor][0]);
                if (elevator->queue_list_2nd_priority[floor][0] == 1){
                    elevator->queue_next_floor_target = floor;
                    printf("prøvde å legge til 2nd priority order i mellom 1st priority target \n");
                    break;
                }
            }
        }
        //check if orders are in between in the direction down
        if (elevator->queue_is_headed_up == 0){
            printf("is headed down");
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
        int did_detect_order = 0;
        // for loop if up direction
        if(elevator->queue_is_headed_up){
            for (int floor = elevator->last_floor_detected; floor <= N_FLOORS; floor++){
                if (elevator->queue_list_2nd_priority[floor][0] || elevator->queue_list_2nd_priority[floor][1]){
                    elevator->queue_next_floor_target = floor;
                    did_detect_order = 1;
                }
                
            }
        }
        // for loop if down direction
        if(! elevator->queue_is_headed_up){
            for (int floor = elevator->last_floor_detected; floor >= 1; floor--){
                if (elevator->queue_list_2nd_priority[floor][0] || elevator->queue_list_2nd_priority[floor][1]){
                    elevator->queue_next_floor_target = floor;
                    did_detect_order = 1;
                }
            }
        }
        
        //if there is no order detected in the queue_is_headed_up direction, then choose the nearest order in the other direction
        if (! did_detect_order){
            //switch direction.
            elevator->queue_is_headed_up = ! elevator->queue_is_headed_up;


            //--------------check again.---------
            if(elevator->queue_is_headed_up){
                for (int floor = elevator->last_floor_detected; floor <= N_FLOORS; floor++){
                    if (elevator->queue_list_2nd_priority[floor][0] || elevator->queue_list_2nd_priority[floor][1]){
                    elevator->queue_next_floor_target = floor;
                    did_detect_order = 1;
                }
                }
            }
            // for loop if down direction
            if(! elevator->queue_is_headed_up){
                for (int floor = elevator->last_floor_detected; floor >= 1; floor--){
                    if (elevator->queue_list_2nd_priority[floor][0] || elevator->queue_list_2nd_priority[floor][1]){
                    elevator->queue_next_floor_target = floor;
                    did_detect_order = 1;
                }
                }
            }
            //DEBUG if failed
            if (!did_detect_order){
                printf("Any 2nd priority order was not detected when it should have been");
            }

        }
    }

    if (!has_1st_priority_order && !has_2nd_priority_order){
        elevator->queue_next_floor_target = -1; // set an invalid target
    }

    
}

void clear_finished_queue_orders(elevator *elevator){
    
    //clear orders only in WAIT
    if(elevator->elevator_state == WAIT){
        elevator->queue_list_1st_priority[elevator->sensor_floor_detected] = 0;
        elevator->queue_list_2nd_priority[elevator->sensor_floor_detected][0] = 0;
        elevator->queue_list_2nd_priority[elevator->sensor_floor_detected][1] = 0;
    }

    if(elevator->elevator_state == STOP){
        elevator->queue_list_1st_priority[elevator->sensor_floor_detected] = 0;
        elevator->queue_list_2nd_priority[elevator->sensor_floor_detected][0] = 0;
        elevator->queue_list_2nd_priority[elevator->sensor_floor_detected][1] = 0;
    }

}

void init_queue(elevator *elevator){
    for (int element = 0; element <= N_FLOORS; element++){
        elevator->queue_list_1st_priority[element] = 0;
        elevator->queue_list_2nd_priority[element][0] = 0;
        elevator->queue_list_2nd_priority[element][1] = 0;
    }
}