#include "../include/crop.h"
#include "../include/orchard.h"
#include "../include/multicrop.h"
#include <iostream>

int main()
{
    system("cls");

    int size = 10;
    crop crop_fields[size][size];
    for(int i = 0; i < size; i++){
        for(int k = 0; k < size; k++){
            crop_fields[i][k].interact_is_active(false);
        }
    }
    crop_fields[0][0].plant_field("Wheat", 'W');
    crop_fields[2][6].plant_field("Wheat", 'W');
    crop_fields[7][3].plant_field("Wheat", 'W');
    crop_fields[4][4].plant_field("Barley", 'B');
    crop_fields[9][5].plant_field("Barley", 'B');
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
    std::cout << std::endl << std::endl;
    crop_fields[0][0].clear_field();
    for(int i = 0; i < size; i++){
        for(int k = 0; k < size; k++){
            std::cout << " ";
            if(crop_fields[i][k].interact_is_active() == true){
                std::cout << "1";
            }
            else{
                std::cout << "0";
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}