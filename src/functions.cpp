#include "../include/functions.h"
#include <iostream>

std::string months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

void options(int lines_printed, granary storehouse, brewery ale_house, workhouse dormitory, int month, int money, int upkeep) //This function should only be called by the UI function.
{
    if(lines_printed == 0){
        std::cout << "          " << "Current month: " << months[month] << ".";
    }
    else if(lines_printed == 1){
        std::cout << "          " << "Current money: \x9C" << money << ".";
    }
    else if(lines_printed == 2){
        std::cout << "          " << "Current upkeep: \x9C" << upkeep << ".";
    }
    else if(lines_printed == 3){
        std::cout << "          ";
    }
    else if(lines_printed == 4){
        std::cout << "          " << "Press p to plant a crop.";
    }
    else if(lines_printed == 5){
        std::cout << "          " << "Press h to harvest a crop.";
    }
    else if(lines_printed == 6){
        std::cout << "          " << "Press c to clear a field.";
    }
    else if(lines_printed == 7){
        std::cout << "          " << "Press f to fertilise a field.";
    }
    else if(lines_printed == 8){
        std::cout << "          ";
    }
    else if(lines_printed == 9){
        std::cout << "          " << "Press b to buy more seeds.";
    }
    else if(lines_printed == 10){
        if(storehouse.interact_is_working() == true){
            std::cout << "          " << "Press s to view the storehouse.";
        }
        else{
            std::cout << "          " << "Press s to build a storehouse.";
        }
    }
    else if(lines_printed == 11){
        if(ale_house.interact_is_working() == true){
            std::cout << "          " << "Press a to view the brewery.";
        }
        else{
            std::cout << "          " << "Press a to build a brewery.";
        }
    }
    else if(lines_printed == 12){
        if(dormitory.interact_is_working() == true){
            std::cout << "          " << "Press d to view the dormitory.";
        }
        else{
            std::cout << "          " << "Press d to build a dormitory.";
        }
    }
    else if(lines_printed == 13){
        std::cout << "          ";
    }
    else if(lines_printed == 14){
        std::cout << "          " << "Press q to exit.";
    }
    else if(lines_printed == 15){
        std::cout << "          " << "Press any other key to move on to the next season.";
    }
}

void main_ui(std::vector<std::vector<crop>> crop_fields, std::vector<std::vector<orchard>> orchard_fields, std::vector<std::vector<multicrop>> multicrop_fields, int size, int month, int money, int upkeep, int harvestable, farmhouse home_house, granary storehouse, brewery ale_house, workhouse dormitory)
{
    int lines_printed = 0;
    std::cout << "-------------------------------------------------------------------------------------" << std::endl;
    for(int i = 0; i < 3*size; i++){
        std::cout << "|";
        for(int k = 0; k < 3*size; k++){
            //std::cout << " ";
            if(crop_fields[i/3][k/3].interact_is_active() == true){
                if(crop_fields[i/3][k/3].interact_is_fertilised() == false){
                    if(crop_fields[i/3][k/3].interact_is_ripe() == true){
                        std::cout << crop_fields[i/3][k/3].interact_symbol() << crop_fields[i/3][k/3].interact_symbol() << crop_fields[i/3][k/3].interact_symbol();
                    }
                    else if(crop_fields[i/3][k/3].interact_lifestage() == 0){
                        std::cout << "^^^";
                    }
                    else{
                        std::cout << crop_fields[i/3][k/3].interact_immature_symbol() << crop_fields[i/3][k/3].interact_immature_symbol() << crop_fields[i/3][k/3].interact_immature_symbol();
                    }
                }
                else{
                    if((i%3 == 1) && (k%3 == 1)){
                        std::cout << " f ";
                    }
                    else{
                        if(crop_fields[i/3][k/3].interact_is_ripe() == true){
                            std::cout << crop_fields[i/3][k/3].interact_symbol() << crop_fields[i/3][k/3].interact_symbol() << crop_fields[i/3][k/3].interact_symbol();
                        }
                        else if(crop_fields[i/3][k/3].interact_lifestage() == 0){
                            std::cout << "^^^";
                        }
                        else{
                            std::cout << crop_fields[i/3][k/3].interact_immature_symbol() << crop_fields[i/3][k/3].interact_immature_symbol() << crop_fields[i/3][k/3].interact_immature_symbol();
                        }
                    }
                }
            }
            else if(orchard_fields[i/3][k/3].interact_is_active() == true){
                if(crop_fields[i/3][k/3].interact_is_fertilised() == false){
                    if(orchard_fields[i/3][k/3].interact_age() <= 18){
                        std::cout << " " << char(193) << " ";
                    }
                    else if((orchard_fields[i/3][k/3].interact_age() > 18) && (orchard_fields[i/3][k/3].interact_is_producing() == true)){
                        std::cout << " " << orchard_fields[i/3][k/3].interact_symbol() << " ";
                    }
                    else{
                        std::cout << " " << orchard_fields[i/3][k/3].interact_immature_symbol() << " ";
                    }
                }
                else{
                    if((i%3 == 1) && (k%3 == 1)){
                        std::cout << " f ";
                    }
                    else{
                        if(orchard_fields[i/3][k/3].interact_age() <= 18){
                            std::cout << " " << char(193) << " ";
                        }
                        else if((orchard_fields[i/3][k/3].interact_age() > 18) && (orchard_fields[i/3][k/3].interact_is_producing() == true)){
                            std::cout << " " << orchard_fields[i/3][k/3].interact_symbol() << " ";
                        }
                        else{
                            std::cout << " " << orchard_fields[i/3][k/3].interact_immature_symbol() << " ";
                        }
                    }
                }
            }
            else if(multicrop_fields[i/3][k/3].interact_is_active() == true){
                if(crop_fields[i/3][k/3].interact_is_fertilised() == false){
                    if(multicrop_fields[i/3][k/3].interact_is_producing() == true){
                        std::cout << multicrop_fields[i/3][k/3].interact_symbol() << multicrop_fields[i/3][k/3].interact_symbol() << multicrop_fields[i/3][k/3].interact_symbol();
                    }
                    else if(multicrop_fields[i/3][k/3].interact_lifestage() == 0){
                        std::cout << "^^^";
                    }
                    else{
                        std::cout << multicrop_fields[i/3][k/3].interact_immature_symbol() << multicrop_fields[i/3][k/3].interact_immature_symbol() << multicrop_fields[i/3][k/3].interact_immature_symbol();
                    }
                }
                else{
                    if((i%3 == 1) && (k%3 == 1)){
                        std::cout << " f ";
                    }
                    else{
                        if(multicrop_fields[i/3][k/3].interact_is_producing() == true){
                            std::cout << multicrop_fields[i/3][k/3].interact_symbol() << multicrop_fields[i/3][k/3].interact_symbol() << multicrop_fields[i/3][k/3].interact_symbol();
                        }
                        else if(multicrop_fields[i/3][k/3].interact_lifestage() == 0){
                            std::cout << "^^^";
                        }
                        else{
                            std::cout << multicrop_fields[i/3][k/3].interact_immature_symbol() << multicrop_fields[i/3][k/3].interact_immature_symbol() << multicrop_fields[i/3][k/3].interact_immature_symbol();
                        }
                    }
                }
            }
            else if((home_house.interact_is_working() == true) && ((home_house.interact_x_location()-1) == k/3) && ((home_house.interact_y_location()-1) == i/3)){
                if((i%3 == 0) && (k%3 == 0)){
                    std::cout << char(219) << char(223) << char(223);
                }
                else if((i%3 == 0) && (k%3 == 1)){
                    std::cout << char(223) << char(223) << char(223);
                }
                else if((i%3 == 0) && (k%3 == 2)){
                    std::cout << char(223) << char(223) << char(219);
                }
                else if((i%3 == 1) && (k%3 == 0)){
                    std::cout << char(219) << " H";
                }
                else if((i%3 == 1) && (k%3 == 1)){
                    std::cout << " H ";
                }
                else if((i%3 == 1) && (k%3 == 2)){
                    std::cout << "H " << char(219);
                }
                else if((i%3 == 2) && (k%3 == 0)){
                    std::cout << char(219) << char(220) << char(220);
                }
                else if((i%3 == 2) && (k%3 == 1)){
                    std::cout << char(220) << char(220) << char(220);
                }
                else if((i%3 == 2) && (k%3 == 2)){
                    std::cout << char(220) << char(220) << char(219);
                }
                //std::cout << " H ";
            }
            else if((storehouse.interact_is_working() == true) && ((storehouse.interact_x_location()-1) == k/3) && ((storehouse.interact_y_location()-1) == i/3)){
                if((i%3 == 0) && (k%3 == 0)){
                    std::cout << char(219) << char(223) << char(223);
                }
                else if((i%3 == 0) && (k%3 == 1)){
                    std::cout << char(223) << char(223) << char(223);
                }
                else if((i%3 == 0) && (k%3 == 2)){
                    std::cout << char(223) << char(223) << char(219);
                }
                else if((i%3 == 1) && (k%3 == 0)){
                    std::cout << char(219) << " S";
                }
                else if((i%3 == 1) && (k%3 == 1)){
                    std::cout << " S ";
                }
                else if((i%3 == 1) && (k%3 == 2)){
                    std::cout << "S " << char(219);
                }
                else if((i%3 == 2) && (k%3 == 0)){
                    std::cout << char(219) << char(220) << char(220);
                }
                else if((i%3 == 2) && (k%3 == 1)){
                    std::cout << char(220) << char(220) << char(220);
                }
                else if((i%3 == 2) && (k%3 == 2)){
                    std::cout << char(220) << char(220) << char(219);
                }
                //std::cout << " S ";
            }
            else if((ale_house.interact_is_working() == true) && ((ale_house.interact_x_location()-1) == k/3) && ((ale_house.interact_y_location()-1) == i/3)){
                if((i%3 == 0) && (k%3 == 0)){
                    std::cout << char(219) << char(223) << char(223);
                }
                else if((i%3 == 0) && (k%3 == 1)){
                    std::cout << char(223) << char(223) << char(223);
                }
                else if((i%3 == 0) && (k%3 == 2)){
                    std::cout << char(223) << char(223) << char(219);
                }
                else if((i%3 == 1) && (k%3 == 0)){
                    std::cout << char(219) << "Br";
                }
                else if((i%3 == 1) && (k%3 == 1)){
                    std::cout << " Br";
                }
                else if((i%3 == 1) && (k%3 == 2)){
                    std::cout << "Br" << char(219);
                }
                else if((i%3 == 2) && (k%3 == 0)){
                    std::cout << char(219) << char(220) << char(220);
                }
                else if((i%3 == 2) && (k%3 == 1)){
                    std::cout << char(220) << char(220) << char(220);
                }
                else if((i%3 == 2) && (k%3 == 2)){
                    std::cout << char(220) << char(220) << char(219);
                }
                //std::cout << " S ";
            }
            else if((dormitory.interact_is_working() == true) && ((dormitory.interact_x_location()-1) == k/3) && ((dormitory.interact_y_location()-1) == i/3)){
                if((i%3 == 0) && (k%3 == 0)){
                    std::cout << char(219) << char(223) << char(223);
                }
                else if((i%3 == 0) && (k%3 == 1)){
                    std::cout << char(223) << char(223) << char(223);
                }
                else if((i%3 == 0) && (k%3 == 2)){
                    std::cout << char(223) << char(223) << char(219);
                }
                else if((i%3 == 1) && (k%3 == 0)){
                    std::cout << char(219) << " D";
                }
                else if((i%3 == 1) && (k%3 == 1)){
                    std::cout << " D ";
                }
                else if((i%3 == 1) && (k%3 == 2)){
                    std::cout << "D " << char(219);
                }
                else if((i%3 == 2) && (k%3 == 0)){
                    std::cout << char(219) << char(220) << char(220);
                }
                else if((i%3 == 2) && (k%3 == 1)){
                    std::cout << char(220) << char(220) << char(220);
                }
                else if((i%3 == 2) && (k%3 == 2)){
                    std::cout << char(220) << char(220) << char(219);
                }
                //std::cout << " S ";
            }
            else{
                std::cout << " ' ";
            }
            //std::cout << " ";
            if((k+1)%3 == 0){
                std::cout << "|";
            }
            else{
                std::cout << " ";
            }
        }
        options(lines_printed, storehouse, ale_house, dormitory, month, money, upkeep);
        std::cout << std::endl;
        lines_printed++;
        if((i+1)%3 == 0){
            std::cout << "-------------------------------------------------------------------------------------";
            options(lines_printed, storehouse, ale_house, dormitory, month, money, upkeep);
            std::cout << std::endl;
            lines_printed++;
        }
    }
    if(harvestable > 0){
        std::cout << "There are " << harvestable << " fields ready to be harvested." << std::endl;
    }
    std::cout << std::endl << std::endl;
}

int change_prices(int current_price, int base_price, int price_variation)
{
    srand(time(NULL));
    current_price = rand()%(2*price_variation) + (base_price - price_variation);

    return current_price;
}

void test_function(farmhouse *home_house)
{
    home_house->change_seed_totals("Wheat", 5);
    std::cout << "Upadating seed totals." << std::endl;
}

void set_up_granary(std::vector<std::vector<crop>> crop_fields, std::vector<std::vector<orchard>> orchard_fields, std::vector<std::vector<multicrop>> multicrop_fields, farmhouse home_house, granary *storehouse, brewery ale_house, workhouse dormitory, int size, int* money, int *upkeep)
{
    std::cout << "Would you like to build one? Y/N: ";
    char char_input;
    std::cin >> char_input;
    switch(char_input){
        case 'y':
        case 'Y':{
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
            else if(crop_fields[y_coord-1][x_coord-1].interact_is_active() == true || orchard_fields[y_coord-1][x_coord-1].interact_is_active() == true || multicrop_fields[y_coord-1][x_coord-1].interact_is_active() == true){
                std::cout << "There is a field planted here. You need to clear it before a storehouse can be built here." << std::endl;
            }
            else if((home_house.interact_x_location() == x_coord) && (home_house.interact_y_location() == y_coord)){
                std::cout << "That's the farmhouse, you can't build a storehouse here." << std::endl;
            }
            else if((ale_house.interact_is_working() == true) && (ale_house.interact_x_location() == x_coord) && (ale_house.interact_y_location() == y_coord)){
                std::cout << "That's the brewery, you can't build a storehouse here." << std::endl;
            }
            else if((dormitory.interact_is_working() == true) && (dormitory.interact_x_location() == x_coord) && (dormitory.interact_y_location() == y_coord)){
                std::cout << "That's the dormitory, you can't build a storehouse here." << std::endl;
            }
            else{
                storehouse->build(x_coord, y_coord);
                *money -= storehouse->interact_cost();
                *upkeep += storehouse->interact_upkeep();
            }
            break;
        }
        case 'n':
        case 'N':{
            break;
        }
        default:{
            std::cout << "Invalid entry." << std::endl;
            break;
        }
    }
}
void set_up_brewery(std::vector<std::vector<crop>> crop_fields, std::vector<std::vector<orchard>> orchard_fields, std::vector<std::vector<multicrop>> multicrop_fields, farmhouse home_house, granary storehouse, brewery *ale_house, workhouse dormitory, int size, int* money, int *upkeep)
{
    std::cout << "Would you like to build one? Y/N: ";
    char char_input;
    std::cin >> char_input;
    switch(char_input){
        case 'y':
        case 'Y':{
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
            else if(crop_fields[y_coord-1][x_coord-1].interact_is_active() == true || orchard_fields[y_coord-1][x_coord-1].interact_is_active() == true || multicrop_fields[y_coord-1][x_coord-1].interact_is_active() == true){
                std::cout << "There is a field planted here. You need to clear it before a brewery can be built here." << std::endl;
            }
            else if((home_house.interact_x_location() == x_coord) && (home_house.interact_y_location() == y_coord)){
                std::cout << "That's the farmhouse, you can't build a brewery here." << std::endl;
            }
            else if((storehouse.interact_is_working() == true) && (storehouse.interact_x_location() == x_coord) && (storehouse.interact_y_location() == y_coord)){
                std::cout << "That's the storehouse, you can't build a brewery here." << std::endl;
            }
            else if((dormitory.interact_is_working() == true) && (dormitory.interact_x_location() == x_coord) && (dormitory.interact_y_location() == y_coord)){
                std::cout << "That's the dormitory, you can't build a brewery here." << std::endl;
            }
            else{
                ale_house->build(x_coord, y_coord);
                *money -= ale_house->interact_cost();
                *upkeep += ale_house->interact_upkeep();
            }
            break;
        }
        case 'n':
        case 'N':{
            break;
        }
        default:{
            std::cout << "Invalid entry." << std::endl;
            break;
        }
    }
}
void set_up_workhouse(std::vector<std::vector<crop>> crop_fields, std::vector<std::vector<orchard>> orchard_fields, std::vector<std::vector<multicrop>> multicrop_fields, farmhouse home_house, granary storehouse, brewery ale_house, workhouse *dormitory, int size, int* money, int *upkeep)
{
    std::cout << "Would you like to build one? Y/N: ";
    char char_input;
    std::cin >> char_input;
    switch(char_input){
        case 'y':
        case 'Y':{
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
            else if(crop_fields[y_coord-1][x_coord-1].interact_is_active() == true || orchard_fields[y_coord-1][x_coord-1].interact_is_active() == true || multicrop_fields[y_coord-1][x_coord-1].interact_is_active() == true){
                std::cout << "There is a field planted here. You need to clear it before a dormitory can be built here." << std::endl;
            }
            else if((home_house.interact_x_location() == x_coord) && (home_house.interact_y_location() == y_coord)){
                std::cout << "That's the farmhouse, you can't build a dormitory here." << std::endl;
            }
            else if((storehouse.interact_is_working() == true) && (storehouse.interact_x_location() == x_coord) && (storehouse.interact_y_location() == y_coord)){
                std::cout << "That's the storehouse, you can't build a dormitory here." << std::endl;
            }
            else if((ale_house.interact_is_working() == true) && (ale_house.interact_x_location() == x_coord) && (ale_house.interact_y_location() == y_coord)){
                std::cout << "That's the brewery, you can't build a dormitory here." << std::endl;
            }
            else{
                dormitory->build(x_coord, y_coord);
                *money -= dormitory->interact_cost();
                *upkeep += dormitory->interact_upkeep();
            }
            break;
        }
        case 'n':
        case 'N':{
            break;
        }
        default:{
            std::cout << "Invalid entry." << std::endl;
            break;
        }
    }
}

void harvest(std::string seed_types, int current_price, granary *storehouse, brewery *ale_house, int output, int *money)
{
    std::cout << "The current price of " << seed_types << " is \x9C" << current_price;
    storehouse->calculate_total();
    ale_house->calculate_total();
    if(((seed_types == "Barley") && (ale_house->interact_is_working() == true) && ((ale_house->interact_storage_space() - ale_house->interact_current_total()) >= output)) && ((storehouse->interact_is_working() == true) && ((storehouse->interact_storage_space()-storehouse->interact_current_total()) >= output))){
        std::cout << ", or there is " << (storehouse->interact_storage_space()-storehouse->interact_current_total()) << " units of space available in the storehouse, or " << (ale_house->interact_storage_space()-ale_house->interact_current_total()) << " units of space available in the brewery." << std::endl;
        std::cout << "If you would like to store the harvest in the storehouse, press s, or in the brewery, press b, otherwise it will be sold: ";
        char store_input;
        std::cin >> store_input;
        if(store_input == 's' || store_input == 'S'){
            storehouse->add_to_store(seed_types, output);
            std::cout << "The harvest has been stored in the storehouse." << std::endl;
        }
        else if(store_input == 'b' || store_input == 'B'){
            ale_house->transfer_barley(output);
            std::cout << "The harvest has been stored in the brewery." << std::endl;
        }
        else{
            std::cout << "You have made \x9C" << output*current_price << "." << std::endl;
            *money += (output*current_price);
        }
    }
    else if((seed_types == "Barley") && (ale_house->interact_is_working() == true) && ((ale_house->interact_storage_space()-ale_house->interact_current_total()) >= output)){
        std::cout << ", or there is " << (ale_house->interact_storage_space()-ale_house->interact_current_total()) << " units of space available in the brewery." << std::endl;
        std::cout << "If you would like to store the harvest, press s, otherwise it will be sold: ";
        char store_input;
        std::cin >> store_input;
        if(store_input == 's' || store_input == 'S'){
            ale_house->transfer_barley(output);
            std::cout << "The harvest has been stored in the brewery." << std::endl;
        }
        else{
            std::cout << "You have made \x9C" << output*current_price << "." << std::endl;
            *money += (output*current_price);
        }
    }
    else if((storehouse->interact_is_working() == true) && ((storehouse->interact_storage_space()-storehouse->interact_current_total()) >= output)){
        std::cout << ", or there is " << (storehouse->interact_storage_space()-storehouse->interact_current_total()) << " units of space available in the storehouse." << std::endl;
        std::cout << "If you would like to store the harvest, press s, otherwise it will be sold: ";
        char store_input;
        std::cin >> store_input;
        if(store_input == 's' || store_input == 'S'){
            storehouse->add_to_store(seed_types, output);
            std::cout << "The harvest has been stored in the storehouse." << std::endl;
        }
        else{
            std::cout << "You have made \x9C" << output*current_price << "." << std::endl;
            *money += (output*current_price);
        }
    }
    else{
        std::cout << "." << std::endl;
        std::cout << "You have made \x9C" << output*current_price << "." << std::endl;
        *money += (output*current_price);
    }
}

void test(int *money)
{
    *money += 1000;
}