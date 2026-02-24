#pragma once
#include "states_and_variables.h"

typedef struct elevator elevator;

void recieve_button_data(elevator *elevator);

void recieve_sensor_data(elevator *elevator);

