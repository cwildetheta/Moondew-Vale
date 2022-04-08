#include "../include/crop.h"
#include "../include/orchard.h"
#include "../include/multicrop.h"
#include <iostream>

int main()
{
    system("cls");
    system("pause");
    std::string months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    bool simulation = true;
    while(simulation == true){
        int size = 7;
        crop crop_fields[size][size];
        orchard orchard_fields[size][size];
        multicrop multicrop_fields[size][size];
        for(int i = 0; i < size; i++){
            for(int k = 0; k < size; k++){
                crop_fields[i][k].interact_is_active(false);
                orchard_fields[i][k].interact_is_active(false);
                multicrop_fields[i][k].interact_is_active(false);
            }
        }
        bool sim_loop = true;
        int month = 1;
        while(sim_loop == true){
            system("cls");
            std::cout << "The current month is " << months[month] << "." << std::endl;
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
            char entry;
            std::cout << "Enter choice: ";
            std::cin >> entry;
            switch(entry){
                case 'q':
                case 'Q':{
                    sim_loop = false;
                    simulation = false;
                    break;
                }
                case 'p':
                case 'P':{
                    std::cout << "Please enter x coordinate: ";
                    int x_coord, y_coord;
                    std::cin >> x_coord;
                    std::cout << "Please enter y coordinate: ";
                    std::cin >> y_coord;
                    if((x_coord < 1) || (x_coord > size)){
                        std::cout << "x coordinate out of bounds, please try again.";
                    }
                    else if((y_coord < 1) || (y_coord > size)){
                        std::cout << "y coordinate out of bounds, please try again.";
                    }
                    else{
                        crop_fields[x_coord-1][y_coord-1].plant_field("Wheat", 'W');
                        crop_fields[x_coord-1][y_coord-1].interact_lifestage(0);
                    }
                    break;
                }
                default:{
                    month += 2;
                    if(month >= 12){
                        month = month - 12;
                    }
                    for(int i = 0; i < size; i++){
                        for(int k = 0; k < size; k++){
                            if(crop_fields[i][k].interact_is_active() == true){
                                if(crop_fields[i][k].interact_lifestage() > 4){
                                    crop_fields[i][k].clear_field();
                                }
                                else{
                                    crop_fields[i][k].grow();
                                }
                            }
                            if(orchard_fields[i][k].interact_is_active() == true){
                                orchard_fields[i][k].grow();
                            }
                            if(multicrop_fields[i][k].interact_is_active() == true){
                                if(multicrop_fields[i][k].interact_lifestage() > 4){
                                    multicrop_fields[i][k].clear_field();
                                }
                                else{
                                    multicrop_fields[i][k].grow();
                                }
                            }
                        }
                    }
                    break;
                }
            }
        }
    }
    system("pause");
    system("cls");
    return 0;
}