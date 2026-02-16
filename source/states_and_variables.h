#include "driver/elvio.h"
#include "lights.h"

typedef enum floor{
    first, second, third, fourth} floor;



//struct that has all the state variables. 
//These variables should always be synced to the elevator
//elevator struct
typedef struct { 

    //------------lights----------------- 
    int lights_indoor_floor[4]; // 1 = true, 0 = false
    int lights_indoor_door_open;
    int lights_stop;

    int lights_outdoor_floor[4]; // only one of these should be active
    
    //outdoor light buttons
    int lights_outdoor_button_down_4;
    int lights_outdoor_button_down_3;
    int lights_outdoor_button_down_2;
    
    int lights_outdoor_button_up_3;
    int lights_outdoor_button_up_2;
    int lights_outdoor_button_up_1;
    
    //-------------Sensors--------------
    floor last_floor_detected; //enum 1 , 2, 3, 4, -1 (mellom ettasje)

    int sensor_indoor_order_floor_button[4]; 

    int sensor_obstruction;
    int sensor_stop_button;
    
    //outdoor buttons
    int sensor_outdoor_button_down_4; // 1 = true, 0 = false
    int sensor_outdoor_button_down_3;
    int sensor_outdoor_button_down_2;
    
    int sensor_outdoor_button_up_3;
    int sensor_outdoor_button_up_2;
    int sensor_outdoor_button_up_1;

    //---------motor------------
    //primary states motor
    MotorDirection motor_direction; // -1, 0, 1


    //-----------queue states----------
    int queue_next_floor_target;

    //------------other-------------------
    int timer;


} elevator ;

void recieve_elevator_variables(elevator *elevator)
