#include "../include/orchard.h"
#include <iostream>

void orchard::grow()
{
    age++;
}
int orchard::harvest_field()
{
    int output = -1;
    if(interact_is_active() == true){
        if(interact_is_alive() == true){
            if(is_producing == true){
                output = interact_yield();
                is_producing = false;
            }
        }
        else{
            std::cout << "This plant is dead, there is nothing left to harvest." << std::endl;
        }
    }
    else{
        std::cout << "Error, trying to harvest a non-active field. This shouldn't be happening." << std::endl;
    }
    return output;
}

//INPUTS AND OUTPUTS
int orchard::interact_age()
{
    return age;
}
void orchard::interact_age(int int_input)
{
    age = int_input;
}
bool orchard::interact_is_producing()
{
    return is_producing;
}
void orchard::interact_is_producing(bool bool_input)
{
    is_producing = bool_input;
}