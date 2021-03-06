#include "../include/crop.h"
#include <iostream>

/*void crop::grow()
{
    lifestage++;
}*/
int crop::harvest_field()
{
    int output = -1;
    if(interact_is_active() == true){
        if(interact_is_alive() == true){
            if(is_ripe == true){
                if(is_underripe == false){
                    output = interact_yield();
                    is_ripe = false;
                }
                else{
                    output = 0.5*interact_yield();
                    is_ripe = false;
                }
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
void crop::begin(int lifestage_input, bool is_ripe_input, bool is_overripe_input)
{
    interact_lifestage(lifestage_input);
    is_ripe = is_ripe_input;
    is_underripe = is_overripe_input;
}

//INPUTS AND OUTPUTS
/*int crop::interact_lifestage()
{
    return lifestage;
}
void crop::interact_lifestage(int int_input)
{
    lifestage = int_input;
}*/
bool crop::interact_is_ripe()
{
    return is_ripe;
}
void crop::interact_is_ripe(bool bool_input)
{
    is_ripe = bool_input;
}
bool crop::interact_is_underripe()
{
    return is_underripe;
}
void crop::interact_is_underripe(bool bool_input)
{
    is_underripe = bool_input;
}