
#include "driver/elevio.h"
#include "lights.h"
#include "buttons_and_sensors.h"



const unsigned sleep_timestep = 20 ; //20ms ----NEED TO MULTIPLY BY 10^6 in nano sleep----
const unsigned int wait_time = 3 * 1000 ; //3s 
//This is to avoid integer overflow

typedef enum  { // We need idle to differentiate Transit wait and idle 
    WAIT = 0, //Wait with opendoors 3 sec
    TRANSIT = 1,
    IDLE = 2, //Stay idle when no commands are present
    INITIALIZING = 3,
    STOP = 4
} Primary_state;

typedef enum { //To determin where the elevator is incase of emergency stop
    NOT_DETECTED = 0,
    UNDER = 1,
    OVER = 2
} Stop_between_floors;

//struct that has all the state variables. 
//These variables should always be synced to the elevator
//elevator struct
typedef struct { 
    //------------main state-----------
    Primary_state elevator_state; 

    //------------lights----------------- 
    int lights_indoor_floor[N_FLOORS + 1]; // 1 = true, 0 = false
    int lights_indoor_door_open;
    int lights_stop;

    int lights_outdoor_floor[N_FLOORS + 1]; // only one of these should be active
    
    //outdoor light buttons
    int lights_outdoor_button[N_FLOORS + 1][2]; // floor, (up, down). 
        //lights_outdoor[1][0] = 1 says floor 1, up button light is active
        //lights_outdoor[4][1] = 1 says floor 4, down button light is active
        //invalid buttons should have the value -1
    
    //-------------Sensors--------------
    int sensor_floor_detected; // eg 1 , 2, 3, 4, -1 (between floors)
    int last_floor_detected; // only valid targets: 1, 2, 3, 4...

    int sensor_obstruction;

    //buttons
    int sensor_stop_button;

    int sensor_indoor_order_floor_button[N_FLOORS + 1]; //sensor_indoor_order_floor_button[1] is floor 1

    int sensor_outdoor_button[N_FLOORS + 1][2]; // floor, (up, down). 
        //sensor_outdoor[1][0] = 1 says floor 1, up button is active
        //sensor_outdoor[4][1] = 1 says floor 4, down button is active
        //invalid buttons should have the value -1
    

    //---------motor------------
    //primary states motor
    MotorDirection motor_direction; // -1, 0, 1


    //-----------queue states----------
    int queue_next_floor_target;
    int queue_list_1st_priority[N_FLOORS+1];
    int queue_list_2nd_priority[N_FLOORS+1][2]; // floor, (up, down)
    int queue_is_headed_up;

    //------------other-------------------
    int timer;
    
    //activated when stop is pushed between floors. 
    Stop_between_floors stop_between_floors 
    

} elevator ;





void recieve_elevator_data(elevator *elevator);
//Collects all new data sent from the elavator

void calculate_elevator_data(elevator *elevator);
//use the data to do necessary calulations.

void send_elevator_data(elevator *elevator);
//sends back instructions to the physical elevator

void init_elevator(elevator *elevator);

void detect_stop(elevator *elevator);

void calculate_primary_elevator_state(elevator *elevator);
