#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"

#include "states_and_variables.h"

/*
int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    elevio_motorDirection(DIRN_UP);

    while(1){
        int floor = elevio_floorSensor();

        if(floor == 0){
            elevio_motorDirection(DIRN_UP);
        }

        if(floor == N_FLOORS-1){
            elevio_motorDirection(DIRN_DOWN);
        }


        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
            }
        }

        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
*/

int main(){
    elevio_init();
    printf("=== Emil and Theo's elevator program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    elevator elevator;
    init_elevator(&elevator); //initialize


    while(1){
        recieve_elevator_data(&elevator);
        calculate_elevator_data(&elevator);
        send_elevator_data(&elevator);

        
        //Elevator stop safeguard
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
        //sleep function. needs to sleep by some timestep to calculate the timer correctly 
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
        nanosleep(&(struct timespec){0,0,}, NULL);
    }
        

}
