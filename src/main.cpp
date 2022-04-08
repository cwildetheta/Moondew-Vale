#include "../include/crop.h"
#include <iostream>

int main()
{
    system("cls");

    crop crop_fields[10][10];
    for(int i = 0; i < 10; i++){
        for(int k = 0; k < 10; k++){
            crop_fields[i][k].interact_is_active(false);
        }
    }
    crop_fields[0][0].interact_is_active(true);
    crop_fields[2][6].interact_is_active(true);
    crop_fields[7][3].interact_is_active(true);
    crop_fields[4][4].interact_is_active(true);
    crop_fields[9][5].interact_is_active(true);
    for(int i = 0; i < 10; i++){
        for(int k = 0; k < 10; k++){
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