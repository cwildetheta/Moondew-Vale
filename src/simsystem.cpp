#include "../include/simsystem.h"
#include "../include/crop.h"
#include "../include/orchard.h"
#include "../include/multicrop.h"
#include <iostream>

simsystem::simsystem(int int_input)
{
    crop crop_field[int_input][int_input];
    orchard orchard_fields[int_input][int_input];
    multicrop multicrop_fields[int_input][int_input];
    for(int i = 0; i < size; i++){
        for(int k = 0; k < size; k++){
            crop_fields[i][k].interact_is_active(false);
            orchard_fields[i][k].interact_is_active(false);
            multicrop_fields[i][k].interact_is_active(false);
        }
    }
}

void simsystem::display_fields(int size){
    for(int i = 0; i < size; i++){
        for(int k = 0; k < size; k++){
            std::cout << " ";
            if(crop_fields[i][k].interact_is_active() == true){
                std::cout << crop_fields[i][k].interact_symbol();
            }
            else{
                std::cout << ":";
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}

//INPUTS AND OUTPUTS
int simsystem::interact_size()
{
    return size;
}
void simsystem::interact_size(int int_input)
{
    size = int_input;
}