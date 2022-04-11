#include "../include/crop.h"
#include "../include/orchard.h"
#include "../include/multicrop.h"
#include "../include/farmhouse.h"
#include <iostream>
#include <iomanip>

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
                crop_fields[i][k].interact_is_ripe(false);
                orchard_fields[i][k].interact_is_active(false);
                orchard_fields[i][k].interact_is_producing(false);
                multicrop_fields[i][k].interact_is_active(false);
                multicrop_fields[i][k].interact_is_producing(false);
            }
        }
        std::string seed_types[6] = {"Wheat", "Barley", "Apple", "Orange", "Courgette", "Tomato"};
        char plant_chars[6] = {'W', 'B', 'A', 'O', 'C', 'T'};
        char small_plant_chars[6] = {'w', 'b', 'a', 'o', 'c', 't'};
        int initial_seed_numbers[6] = {10, 10, 5, 5, 2, 2};
        int seed_prices[6] = {30, 45, 35, 35, 25, 20};
        int base_yields[6] = {15, 15, 5, 5, 5, 5};
        int base_price[6] = {5, 10, 6, 8, 3, 2}, current_price[6] = {5, 10, 6, 8, 3, 2};
        farmhouse home_house(6, seed_types, initial_seed_numbers);
        home_house.interact_is_working(true);
        home_house.interact_upkeep(0);
        home_house.interact_fertiliser(5);
        home_house.interact_x_location(4);
        home_house.interact_y_location(4);
        bool sim_loop = true;
        int money = 100;
        int month = 1;
        int harvestable = 0;
        while(sim_loop == true){
            system("cls");
            std::cout << "Current money: " << money << " pounds." << std::endl;
            std::cout << "The current month is " << months[month] << "." << std::endl;
            for(int i = 0; i < size; i++){
                for(int k = 0; k < size; k++){
                    std::cout << " ";
                    if(crop_fields[i][k].interact_is_active() == true){
                        if(crop_fields[i][k].interact_is_ripe() == true){
                            std::cout << crop_fields[i][k].interact_symbol();
                        }
                        else{
                            std::cout << crop_fields[i][k].interact_immature_symbol();
                        }
                    }
                    else if(orchard_fields[i][k].interact_is_active() == true){
                        if(orchard_fields[i][k].interact_age() > 18){
                            std::cout << orchard_fields[i][k].interact_symbol();
                        }
                        else{
                            std::cout << orchard_fields[i][k].interact_immature_symbol();
                        }
                    }
                    else if(multicrop_fields[i][k].interact_is_active() == true){
                        if(multicrop_fields[i][k].interact_is_producing() == true){
                            std::cout << multicrop_fields[i][k].interact_symbol();
                        }
                        else{
                            std::cout << multicrop_fields[i][k].interact_immature_symbol();
                        }
                    }
                    else if(((home_house.interact_x_location()-1) == k) && ((home_house.interact_y_location()-1) == i)){
                        std::cout << "F";
                    }
                    else{
                        std::cout << ":";
                    }
                    std::cout << " ";
                }
                if(i == 0){
                    std::cout << "          " << "Press p to plant a crop.";
                }
                if(i == 1){
                    std::cout << "          " << "Press h to harvest a crop.";
                }
                if(i == 2){
                    std::cout << "          " << "Press b to buy more seeds.";
                }
                if(i == 3){
                    std::cout << "          " << "Press c to clear a field.";
                }
                if(i == 4){
                    std::cout << "          " << "Press q to exit.";
                }
                if(i == 5){
                    std::cout << "          " << "Press any other key to move on to the next season.";
                }
                std::cout << std::endl;
            }
            if(harvestable > 0){
                std::cout << "There are " << harvestable << " fields ready to be harvested." << std::endl;
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
                                crop_fields[x_coord-1][y_coord-1].plant_field(seed_types[seed_pick-1], plant_chars[seed_pick-1], small_plant_chars[seed_pick-1]);
                                home_house.change_seed_totals(seed_types[seed_pick-1], -1);
                                crop_fields[x_coord-1][y_coord-1].interact_lifestage(0);
                                crop_fields[x_coord-1][y_coord-1].interact_is_ripe(false);
                                crop_fields[x_coord-1][y_coord-1].interact_is_overripe(false);
                                crop_fields[x_coord-1][y_coord-1].interact_yield(base_yields[seed_pick-1]);
                            }
                            if((seed_pick == 3) || (seed_pick == 4)){
                                orchard_fields[x_coord-1][y_coord-1].plant_field(seed_types[seed_pick-1], plant_chars[seed_pick-1], small_plant_chars[seed_pick-1]);
                                home_house.change_seed_totals(seed_types[seed_pick-1], -1);
                                orchard_fields[x_coord-1][y_coord-1].interact_age(0);
                                orchard_fields[x_coord-1][y_coord-1].interact_is_producing(false);
                                orchard_fields[x_coord-1][y_coord-1].interact_yield(base_yields[seed_pick-1]);
                            }
                            if((seed_pick == 5) || (seed_pick == 6)){
                                multicrop_fields[x_coord-1][y_coord-1].plant_field(seed_types[seed_pick-1], plant_chars[seed_pick-1], small_plant_chars[seed_pick-1]);
                                home_house.change_seed_totals(seed_types[seed_pick-1], -1);
                                multicrop_fields[x_coord-1][y_coord-1].interact_lifestage(0);
                                multicrop_fields[x_coord-1][y_coord-1].interact_is_producing(false);
                                multicrop_fields[x_coord-1][y_coord-1].interact_yield(base_yields[seed_pick-1]);
                            }
                        }
                    }
                    system("pause");
                    break;
                }
                case 'h':
                case 'H':{
                    std::cout << "Please enter x coordinate: ";
                    int x_coord, y_coord;
                    std::cin >> x_coord;
                    std::cout << "Please enter y coordinate: ";
                    std::cin >> y_coord;
                    if((x_coord < 1) || (x_coord > size)){
                        std::cout << "x coordinate out of bounds, please try again." << std::endl;
                    }
                    else if((y_coord < 1) || (y_coord > size)){
                        std::cout << "y coordinate out of bounds, please try again." << std::endl;
                    }
                    if(crop_fields[x_coord-1][y_coord-1].interact_is_active() == true){
                        int output = crop_fields[x_coord-1][y_coord-1].harvest_field();
                        if(output != -1){
                            int index;
                            for(int i = 0; i < 6; i++){ //Be careful with the limit here, make sure to change it if it needs it.
                                if(seed_types[i] == crop_fields[x_coord-1][y_coord-1].interact_name()){
                                    index = i;
                                }
                            }
                            std::cout << "You have harvested " << output << " units of " << crop_fields[x_coord-1][y_coord-1].interact_name() << ". ";
                            std::cout << "The current price of " << crop_fields[x_coord-1][y_coord-1].interact_name() << " is " << current_price[index] << " pounds." << std::endl;
                            std::cout << "You have made " << output*current_price[index] << " pounds." << std::endl;
                            money = money + (output*current_price[index]);
                            crop_fields[x_coord-1][y_coord-1].clear_field();
                        }
                    }
                    else if(orchard_fields[x_coord-1][y_coord-1].interact_is_active() == true){
                        int output = orchard_fields[x_coord-1][y_coord-1].harvest_field();
                        if(output != -1){
                            int index;
                            for(int i = 0; i < 6; i++){ //Be careful with the limit here, make sure to change it if it needs it.
                                if(seed_types[i] == orchard_fields[x_coord-1][y_coord-1].interact_name()){
                                    index = i;
                                }
                            }
                            std::cout << "You have harvested " << output << " units of " << orchard_fields[x_coord-1][y_coord-1].interact_name() << ". ";
                            std::cout << "The current price of " << orchard_fields[x_coord-1][y_coord-1].interact_name() << " is " << current_price[index] << " pounds." << std::endl;
                            std::cout << "You have made " << output*current_price[index] << " pounds." << std::endl;
                            money = money + (output*current_price[index]);
                            orchard_fields[x_coord-1][y_coord-1].interact_is_producing(false);
                        }
                    }
                    else if(multicrop_fields[x_coord-1][y_coord-1].interact_is_active() == true){
                        int output = multicrop_fields[x_coord-1][y_coord-1].harvest_field();
                        if(output != -1){
                            int index;
                            for(int i = 0; i < 6; i++){ //Be careful with the limit here, make sure to change it if it needs it.
                                if(seed_types[i] == multicrop_fields[x_coord-1][y_coord-1].interact_name()){
                                    index = i;
                                }
                            }
                            std::cout << "You have harvested " << output << " units of " << multicrop_fields[x_coord-1][y_coord-1].interact_name() << ". ";
                            std::cout << "The current price of " << multicrop_fields[x_coord-1][y_coord-1].interact_name() << " is " << current_price[index] << " pounds." << std::endl;
                            std::cout << "You have made " << output*current_price[index] << " pounds." << std::endl;
                            money = money + (output*current_price[index]);
                            multicrop_fields[x_coord-1][y_coord-1].interact_is_producing(false);
                        }
                    }
                    else if((home_house.interact_x_location() == (x_coord-1)) && (home_house.interact_y_location() == (y_coord-1))){
                        std::cout << "This is your farmhouse. you can't harvest a building." << std::endl;
                    }
                    else{
                        std::cout << "There is nothing in this field." << std::endl;
                    }
                    system("pause");
                    break;
                }
                case 'b':
                case 'B':{
                    std::cout << "Which type of seeds would you like to buy? Seeds are bought in packs of 5.    Current money: "<< money << " pounds." << std::endl; //Generalise this later, ie. seed_types[i]
                    std::cout << "1. Wheat      Current seeds: " << std::setw(4) << home_house.interact_seed_totals(seed_types[0]) << "  Cost: " << seed_prices[0] << " pounds." << std::endl;
                    std::cout << "2. Barley     Current seeds: " << std::setw(4) << home_house.interact_seed_totals(seed_types[1]) << "  Cost: " << seed_prices[1] << " pounds." << std::endl;
                    std::cout << "3. Apple      Current seeds: " << std::setw(4) << home_house.interact_seed_totals(seed_types[2]) << "  Cost: " << seed_prices[2] << " pounds." << std::endl;
                    std::cout << "4. Orange     Current seeds: " << std::setw(4) << home_house.interact_seed_totals(seed_types[3]) << "  Cost: " << seed_prices[3] << " pounds." << std::endl;
                    std::cout << "5. Courgette  Current seeds: " << std::setw(4) << home_house.interact_seed_totals(seed_types[4]) << "  Cost: " << seed_prices[4] << " pounds." << std::endl;
                    std::cout << "6. Tomato     Current seeds: " << std::setw(4) << home_house.interact_seed_totals(seed_types[5]) << "  Cost: " << seed_prices[5] << " pounds." << std::endl << std::endl;
                    int seed_pick;
                    std::cin >> seed_pick;
                    if(seed_prices[seed_pick-1] > money){
                        std::cout << "You do not have enough money for that." << std::endl;
                    }
                    else{
                        money = money - seed_prices[seed_pick-1];
                        home_house.interact_seed_totals(seed_types[seed_pick-1], (home_house.interact_seed_totals(seed_types[seed_pick-1])+5));
                        std::cout << "You have bought 5 " << seed_types[seed_pick-1] << " seeds." << std::endl;
                    }
                    system("pause");
                    break;
                }
                case 'c':
                case 'C':{
                    std::cout << "Please enter x coordinate: ";
                    int x_coord, y_coord;
                    std::cin >> x_coord;
                    std::cout << "Please enter y coordinate: ";
                    std::cin >> y_coord;
                    if((x_coord < 1) || (x_coord > size)){
                        std::cout << "x coordinate out of bounds, please try again." << std::endl;
                    }
                    else if((y_coord < 1) || (y_coord > size)){
                        std::cout << "y coordinate out of bounds, please try again." << std::endl;
                    }
                    if(crop_fields[x_coord-1][y_coord-1].interact_is_active() == true){
                        crop_fields[x_coord-1][y_coord-1].clear_field();
                        std::cout << "Field at " << x_coord << "," << y_coord << " cleared." << std::endl;
                    }
                    else if(orchard_fields[x_coord-1][y_coord-1].interact_is_active() == true){
                        orchard_fields[x_coord-1][y_coord-1].clear_field();
                        std::cout << "Field at " << x_coord << "," << y_coord << " cleared." << std::endl;
                    }
                    else if(multicrop_fields[x_coord-1][y_coord-1].interact_is_active() == true){
                        multicrop_fields[x_coord-1][y_coord-1].clear_field();
                        std::cout << "Field at " << x_coord << "," << y_coord << " cleared." << std::endl;
                    }
                    else if((home_house.interact_x_location() == (x_coord-1)) && (home_house.interact_y_location() == (y_coord-1))){
                        std::cout << "This is your farmhouse. You can't remove that: you live there." << std::endl;
                    }
                    else{
                        std::cout << "There's nothing in this field to clear." << std::endl;
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
                                if(month == 8 || month == 9){
                                    if(crop_fields[i][k].interact_lifestage() == 4){
                                        crop_fields[i][k].interact_is_ripe(true);
                                    }
                                    else if(crop_fields[i][k].interact_lifestage() == 3){
                                        crop_fields[i][k].interact_is_ripe(true);
                                        crop_fields[i][k].interact_is_overripe(true);
                                    }
                                }
                                if(crop_fields[i][k].interact_lifestage() >= 5 || month == 10 || month == 11 || month == 0){
                                    crop_fields[i][k].die();
                                }
                                else{
                                    crop_fields[i][k].grow();
                                }
                            }
                            if(orchard_fields[i][k].interact_is_active() == true){
                                if((month == 6 || month == 7 || month == 8 || month == 9) && (orchard_fields[i][k].interact_age() > 18)){
                                    orchard_fields[i][k].interact_is_producing(true);
                                }
                                if(month == 10 || month == 11){
                                    orchard_fields[i][k].interact_is_producing(false);
                                }
                                orchard_fields[i][k].grow();
                            }
                            if(multicrop_fields[i][k].interact_is_active() == true){
                                if(multicrop_fields[i][k].interact_is_alive() == false){
                                    multicrop_fields[i][k].clear_field();
                                }
                                if((month > 4 && month < 10) && (multicrop_fields[i][k].interact_lifestage() > 1)){
                                    multicrop_fields[i][k].interact_is_producing(true);
                                }
                                if(multicrop_fields[i][k].interact_lifestage() >= 5 || month == 10 || month == 11 || month == 0){
                                    multicrop_fields[i][k].die();
                                }
                                else{
                                    multicrop_fields[i][k].grow();
                                }
                            }
                        }
                    }
                    harvestable = 0;
                    for(int i = 0; i < size; i++){
                        for(int k = 0; k < size; k++){
                            if(crop_fields[i][k].interact_is_ripe() == true || orchard_fields[i][k].interact_is_producing() == true || multicrop_fields[i][k].interact_is_producing() == true){
                                harvestable++;
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