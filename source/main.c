#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"

#include "states_and_variables.h"


int main(){
    elevio_init();
    printf("=== Emil and Theo's elevator program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    elevator elevator;
    init_elevator(&elevator); //initialize


    while(1){
        recieve_elevator_data(&elevator);
        detect_stop(&elevator);
        calculate_elevator_data(&elevator);
        send_elevator_data(&elevator);
        nanosleep(&(struct timespec){0, sleep_timestep*1000*1000}, NULL);
    }
        

}
