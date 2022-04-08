#include "../include/crop.h"
#include "../include/orchard.h"
#include "../include/multicrop.h"
#include "../include/farmhouse.h"
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
        std::string seed_types[6] = {"Wheat", "Barley", "Apple", "Orange", "Courgette", "Tomato"};
        char plant_chars[6] = {'W', 'B', 'A', 'O', 'C', 'T'};
        int initial_seed_numbers[6] = {10, 10, 5, 5, 2, 2};
        farmhouse home_house(6, seed_types, initial_seed_numbers);
        home_house.interact_is_working(true);
        home_house.interact_upkeep(0);
        home_house.interact_fertiliser(5);
        home_house.interact_x_location(4);
        home_house.interact_y_location(4);
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
                    else if(orchard_fields[i][k].interact_is_active() == true){
                        std::cout << orchard_fields[i][k].interact_symbol();
                    }
                    else if(multicrop_fields[i][k].interact_is_active() == true){
                        std::cout << multicrop_fields[i][k].interact_symbol();
                    }
                    else if(((home_house.interact_x_location()-1) == k) && ((home_house.interact_y_location()-1) == i)){
                        std::cout << "F";
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
                    std::cout << "Which plant would you like to plant?" << std::endl; //Generalise this later, ie. seed_types[i]
                    std::cout << "1. Wheat      Seeds: " << home_house.interact_seed_totals(seed_types[0]) << std::endl;
                    std::cout << "2. Barley     Seeds: " << home_house.interact_seed_totals(seed_types[1]) << std::endl;
                    std::cout << "3. Apple      Seeds: " << home_house.interact_seed_totals(seed_types[2]) << std::endl;
                    std::cout << "4. Orange     Seeds: " << home_house.interact_seed_totals(seed_types[3]) << std::endl;
                    std::cout << "5. Courgette  Seeds: " << home_house.interact_seed_totals(seed_types[4]) << std::endl;
                    std::cout << "6. Tomato     Seeds: " << home_house.interact_seed_totals(seed_types[5]) << std::endl << std::endl;
                    int seed_pick;
                    std::cin >> seed_pick;
                    std::cout << "Please enter x coordinate: ";
                    int x_coord, y_coord;
                    std::cin >> x_coord;
                    std::cout << "Please enter y coordinate: ";
                    std::cin >> y_coord;
                    if((seed_pick < 1) || (seed_pick > 6)){
                        std::cout << "Not a valid seed choice, please try again." << std::endl;
                    }
                    else if((x_coord < 1) || (x_coord > size)){
                        std::cout << "x coordinate out of bounds, please try again." << std::endl;
                    }
                    else if((y_coord < 1) || (y_coord > size)){
                        std::cout << "y coordinate out of bounds, please try again." << std::endl;
                    }
                    else if((home_house.interact_x_location() == (x_coord-1)) && (home_house.interact_y_location() == (y_coord-1))){
                        std::cout << "This location is already occupied by the farmhouse, please try again." << std::endl;
                    }
                    else if((crop_fields[x_coord-1][y_coord-1].interact_is_active() == true) || (orchard_fields[x_coord-1][y_coord-1].interact_is_active() == true) || (multicrop_fields[x_coord-1][y_coord-1].interact_is_active() == true)){
                        std::cout << "This field is already in use. Clear it before planting something else." << std::endl;
                    }
                    else{
                        if(home_house.interact_seed_totals(seed_types[seed_pick-1]) > 0){
                            if((seed_pick == 1) || (seed_pick == 2)){ //Needs work on generalising which field subclass is used.
                                crop_fields[x_coord-1][y_coord-1].plant_field(seed_types[seed_pick-1], plant_chars[seed_pick-1]);
                                home_house.change_seed_totals(seed_types[seed_pick-1], -1);
                                crop_fields[x_coord-1][y_coord-1].interact_lifestage(0);
                            }
                            if((seed_pick == 3) || (seed_pick == 4)){
                                orchard_fields[x_coord-1][y_coord-1].plant_field(seed_types[seed_pick-1], plant_chars[seed_pick-1]);
                                home_house.change_seed_totals(seed_types[seed_pick-1], -1);
                                orchard_fields[x_coord-1][y_coord-1].interact_age(0);
                            }
                            if((seed_pick == 5) || (seed_pick == 6)){
                                multicrop_fields[x_coord-1][y_coord-1].plant_field(seed_types[seed_pick-1], plant_chars[seed_pick-1]);
                                home_house.change_seed_totals(seed_types[seed_pick-1], -1);
                                multicrop_fields[x_coord-1][y_coord-1].interact_lifestage(0);
                            }
                        }
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
                                if(crop_fields[i][k].interact_is_alive() == false){
                                    crop_fields[i][k].clear_field();
                                }
                                if(crop_fields[i][k].interact_lifestage() == 4 || month == 10 || month == 11 || month == 0 || month == 1){
                                    crop_fields[i][k].die();
                                }
                                else{
                                    crop_fields[i][k].grow();
                                }
                            }
                            if(orchard_fields[i][k].interact_is_active() == true){
                                orchard_fields[i][k].grow();
                            }
                            if(multicrop_fields[i][k].interact_is_active() == true){
                                if(multicrop_fields[i][k].interact_is_alive() == false){
                                    multicrop_fields[i][k].clear_field();
                                }
                                if(multicrop_fields[i][k].interact_lifestage() == 4 || month == 10 || month == 11 || month == 0 || month == 1){
                                    multicrop_fields[i][k].die();
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