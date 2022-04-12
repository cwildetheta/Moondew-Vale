#include "../include/multicrop.h"
#include <iostream>

void multicrop::grow()
{
    lifestage++;
}
int multicrop::harvest_field()
{
    int output = -1;
    if(interact_is_active() == true){
        if(interact_is_alive() == true){
            if(is_producing == true){
                output = interact_yield();
                is_producing = false;
            }
            else{
                std::cout << "This plant isn't ripe yet, wait for it to grow some more." << std::endl;
            }
        }
        else{
            std::cout << "This plant is dead, there is nothing left to harvest." << std::endl;
        }
    }
    else{
        std::cout << "Error, trying to harvest a non-active field. This shouldn't be happening." << std::endl;
    }
    if(interact_is_fertilised() == true){
        output = output*1.5;
    }
    return output;
}

//INPUTS AND OUTPUTS
int multicrop::interact_lifestage()
{
    return lifestage;
}
void multicrop::interact_lifestage(int int_input)
{
    lifestage = int_input;
}
bool multicrop::interact_is_producing()
{
    return is_producing;
}
void multicrop::interact_is_producing(bool bool_input)
{
    is_producing = bool_input;
}