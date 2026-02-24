#pragma once
#include "states_and_variables.h"

typedef struct elevator elevator;

void calculate_motor_data(elevator *elevator);

void send_motor_data(elevator *elevator);



