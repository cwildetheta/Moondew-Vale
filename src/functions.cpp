#include "../include/functions.h"
#include <iostream>
#include <iomanip>

std::string months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

void options(int lines_printed, granary storehouse, brewery ale_house, workhouse dormitory, int month, int money, int upkeep, int current_price[], int base_price[], std::string seed_types[]) //This function should only be called by the UI function.
{
    std::string gap = "        ";
    if(lines_printed == 0){
        std::cout << gap << "Current month: " << months[month] << ".";
    }
    else if(lines_printed == 1){
        std::cout << gap << "Current money: \x9C" << money << ".";
    }
    else if(lines_printed == 2){
        std::cout << gap << "Current upkeep: \x9C" << upkeep << ".";
    }
    else if(lines_printed == 3){
        std::cout << gap;
    }
    else if(lines_printed == 4){
        std::cout << gap << "Press p to plant a crop.";
    }
    else if(lines_printed == 5){
        std::cout << gap << "Press h to harvest a crop.";
    }
    else if(lines_printed == 6){
        std::cout << gap << "Press c to clear a field.";
    }
    else if(lines_printed == 7){
        std::cout << gap << "Press f to fertilise a field.";
    }
    else if(lines_printed == 8){
        std::cout << gap;
    }
    else if(lines_printed == 9){
        std::cout << gap << "Press b to buy more seeds.";
    }
    else if(lines_printed == 10){
        if(storehouse.interact_is_working() == true){
            std::cout << gap << "Press s to view the storehouse.";
        }
        else{
            std::cout << gap << "Press s to build a storehouse.";
        }
    }
    else if(lines_printed == 11){
        if(ale_house.interact_is_working() == true){
            std::cout << gap << "Press a to view the brewery.";
        }
        else{
            std::cout << gap << "Press a to build a brewery.";
        }
    }
    else if(lines_printed == 12){
        if(dormitory.interact_is_working() == true){
            std::cout << gap << "Press d to view the dormitory.";
        }
        else{
            std::cout << gap << "Press d to build a dormitory.";
        }
    }
    else if(lines_printed == 13){
        std::cout << gap;
    }
    else if(lines_printed == 14){
        std::cout << gap << "Press q to exit.";
    }
    else if(lines_printed == 15){
        std::cout << gap << "Press any other key to move on to the next season.";
    }
    else if(lines_printed == 17){ //The string length manipulation here is cheaty, as it relies on the prices not going above £19, otherwise things will break.
        std::cout << gap << "Current price of " << seed_types[0] << ": \x9C" << current_price[0] << "." << std::setw(11-seed_types[0].length()-(current_price[0]/10)) << " " << "Average price: \x9C" << base_price[0] << "."; 
    }
    else if(lines_printed == 18){
        std::cout << gap << "Current price of " << seed_types[1] << ": \x9C" << current_price[1] << "." << std::setw(11-seed_types[1].length()-(current_price[1]/10)) << " " << "Average price: \x9C" << base_price[1] << "."; 
    }
    else if(lines_printed == 19){
        std::cout << gap << "Current price of " << seed_types[2] << ": \x9C" << current_price[2] << "." << std::setw(11-seed_types[2].length()-(current_price[2]/10)) << " " << "Average price: \x9C" << base_price[2] << "."; 
    }
    else if(lines_printed == 20){
        std::cout << gap << "Current price of " << seed_types[3] << ": \x9C" << current_price[3] << "." << std::setw(11-seed_types[3].length()-(current_price[3]/10)) << " " << "Average price: \x9C" << base_price[3] << "."; 
    }
    else if(lines_printed == 21){
        std::cout << gap << "Current price of " << seed_types[4] << ": \x9C" << current_price[4] << "." << std::setw(11-seed_types[4].length()-(current_price[4]/10)) << " " << "Average price: \x9C" << base_price[4] << "."; 
    }
    else if(lines_printed == 22){
        std::cout << gap << "Current price of " << seed_types[5] << ": \x9C" << current_price[5] << "." << std::setw(11-seed_types[5].length()-(current_price[5]/10)) << " " << "Average price: \x9C" << base_price[5] << "."; 
    }
}
void main_ui(std::vector<std::vector<crop>> crop_fields, std::vector<std::vector<orchard>> orchard_fields, std::vector<std::vector<multicrop>> multicrop_fields, int size, int month, int money, int upkeep, int harvestable, farmhouse home_house, granary storehouse, brewery ale_house, workhouse dormitory, int current_price[], int base_price[], std::string seed_types[])
{
    int lines_printed = 0;
    //std::cout << "-------------------------------------------------------------------------------------" << std::endl;
    std::cout << char(218);
    for(int l = 0; l < 7; l++){
        if(l != 6){
            for(int o = 0; o < 11; o++){
                std::cout << char(196);
            }
            std::cout << char(194);
        }
        else{
            for(int o = 0; o < 11; o++){
                std::cout << char(196);
            }
            std::cout << char(191);
        }
    }
    std::cout << std::endl;
    for(int i = 0; i < 3*size; i++){
        //std::cout << "|";
        std::cout << char(179);
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
                if(orchard_fields[i/3][k/3].interact_is_fertilised() == false){
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
                if(multicrop_fields[i/3][k/3].interact_is_fertilised() == false){
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
                //std::cout << "|";
                std::cout << char(179);
            }
            else{
                std::cout << " ";
            }
        }
        options(lines_printed, storehouse, ale_house, dormitory, month, money, upkeep, current_price, base_price, seed_types);
        std::cout << std::endl;
        lines_printed++;
        if((i+1)%3 == 0){
            //std::cout << "-------------------------------------------------------------------------------------";
            if(i != ((3*size) - 1)){
                std::cout << char(195);
                for(int l = 0; l < 7; l++){
                    if(l != 6){
                        for(int o = 0; o < 11; o++){
                            std::cout << char(196);
                        }
                        std::cout << char(197);
                    }
                    else{
                        for(int o = 0; o < 11; o++){
                            std::cout << char(196);
                        }
                        std::cout << char(180);
                    }
                }
            }
            else{
                std::cout << char(192);
                for(int l = 0; l < 7; l++){
                    if(l != 6){
                        for(int o = 0; o < 11; o++){
                            std::cout << char(196);
                        }
                        std::cout << char(193);
                    }
                    else{
                        for(int o = 0; o < 11; o++){
                            std::cout << char(196);
                        }
                        std::cout << char(217);
                    }
                }
            }
            //"-----------" << char(197) << "-----------" << char(197) << "-----------" << char(197) << "-----------" << char(197) << "-----------" << char(197) << "-----------" << char(197) << "-----------" << char(180);
            options(lines_printed, storehouse, ale_house, dormitory, month, money, upkeep, current_price, base_price, seed_types);
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

void set_up_granary(std::vector<std::vector<crop>> crop_fields, std::vector<std::vector<orchard>> orchard_fields, std::vector<std::vector<multicrop>> multicrop_fields, farmhouse home_house, granary *storehouse, brewery ale_house, workhouse dormitory, int size, int* money, int *upkeep)
{
    std::cout << "Would you like to build one? Y/N: ";
    char char_input;
    std::cin >> char_input;
    switch(char_input){
        case 'y':
        case 'Y':{
            int x_coord = int_inputter("Please enter x coordinate: ");
            int y_coord = int_inputter("Please enter y coordinate: ");
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
            int x_coord = int_inputter("Please enter x coordinate: ");
            int y_coord = int_inputter("Please enter y coordinate: ");
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
            int x_coord = int_inputter("Please enter x coordinate: ");
            int y_coord = int_inputter("Please enter y coordinate: ");
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

void plant(std::string seed_types[], std::vector<std::vector<crop *>> crop_fields, std::vector<std::vector<orchard *>> orchard_fields, std::vector<std::vector<multicrop *>> multicrop_fields, farmhouse* home_house, granary storehouse, brewery ale_house, workhouse dormitory, int size, char plant_chars[], char small_plant_chars[], int base_yields[])
{
    std::cout << "1. Wheat      Seeds: " << home_house->interact_seed_totals(seed_types[0]) << std::endl; //Generalise this later, ie. seed_types[i]
    std::cout << "2. Barley     Seeds: " << home_house->interact_seed_totals(seed_types[1]) << std::endl;
    std::cout << "3. Apple      Seeds: " << home_house->interact_seed_totals(seed_types[2]) << std::endl;
    std::cout << "4. Orange     Seeds: " << home_house->interact_seed_totals(seed_types[3]) << std::endl;
    std::cout << "5. Courgette  Seeds: " << home_house->interact_seed_totals(seed_types[4]) << std::endl;
    std::cout << "6. Tomato     Seeds: " << home_house->interact_seed_totals(seed_types[5]) << std::endl << std::endl;
    int seed_pick = int_inputter("Which seed would you like to plant: ");
    if(((seed_pick > 0) && (seed_pick < 7)) && (home_house->interact_seed_totals(seed_types[seed_pick-1]) > 0)){
        int x_coord = int_inputter("Please enter x coordinate: ");
        int y_coord = int_inputter("Please enter y coordinate: ");
        if((x_coord < 1) || (x_coord > size)){
            std::cout << "x coordinate out of bounds, please try again." << std::endl;
        }
        else if((y_coord < 1) || (y_coord > size)){
            std::cout << "y coordinate out of bounds, please try again." << std::endl;
        }
        else if((home_house->interact_x_location() == x_coord) && (home_house->interact_y_location() == y_coord)){
            std::cout << "This location is already occupied by the farmhouse, please try again." << std::endl;
        }
        else if((storehouse.interact_is_working() == true) && (storehouse.interact_x_location() == x_coord) && (storehouse.interact_y_location() == y_coord)){
            std::cout << "This location is already occupied by the storehouse, please try again." << std::endl;
        }
        else if((ale_house.interact_is_working() == true) && (ale_house.interact_x_location() == x_coord) && (ale_house.interact_y_location() == y_coord)){
            std::cout << "This location is already occupied by the brewery, please try again." << std::endl;
        }
        else if((dormitory.interact_is_working() == true) && (dormitory.interact_x_location() == x_coord) && (dormitory.interact_y_location() == y_coord)){
            std::cout << "This location is already occupied by the workhouse, please try again." << std::endl;
        }
        else if((crop_fields[y_coord-1][x_coord-1]->interact_is_active() == true) || (orchard_fields[y_coord-1][x_coord-1]->interact_is_active() == true) || (multicrop_fields[y_coord-1][x_coord-1]->interact_is_active() == true)){
            std::cout << "This field is already in use. Clear it before planting something else." << std::endl;
        }
        else{
            if((seed_pick == 1) || (seed_pick == 2)){ //Needs work on generalising which field subclass is used.
                crop_fields[y_coord-1][x_coord-1]->plant_field(seed_types[seed_pick-1], plant_chars[seed_pick-1], small_plant_chars[seed_pick-1], base_yields[seed_pick-1]);
                home_house->change_seed_totals(seed_types[seed_pick-1], -1);
                crop_fields[y_coord-1][x_coord-1]->begin(0, false, false);
            }
            if((seed_pick == 3) || (seed_pick == 4)){
                orchard_fields[y_coord-1][x_coord-1]->plant_field(seed_types[seed_pick-1], plant_chars[seed_pick-1], small_plant_chars[seed_pick-1], base_yields[seed_pick-1]);
                home_house->change_seed_totals(seed_types[seed_pick-1], -1);
                orchard_fields[y_coord-1][x_coord-1]->begin(0, false);
            }
            if((seed_pick == 5) || (seed_pick == 6)){
                multicrop_fields[y_coord-1][x_coord-1]->plant_field(seed_types[seed_pick-1], plant_chars[seed_pick-1], small_plant_chars[seed_pick-1], base_yields[seed_pick-1]);
                home_house->change_seed_totals(seed_types[seed_pick-1], -1);
                multicrop_fields[y_coord-1][x_coord-1]->begin(0, false);
            }
        }
    }
    else if((seed_pick < 1) || (seed_pick > 6)){
        std::cout << "Not a valid seed choice, please try again." << std::endl;
    }
    else{
        std::cout << "You don't have any " << seed_types[seed_pick-1] << " seeds left." << std::endl;
    }
}
void fertilise(std::vector<std::vector<crop *>> crop_fields, std::vector<std::vector<orchard *>> orchard_fields, std::vector<std::vector<multicrop *>> multicrop_fields, farmhouse* home_house, granary storehouse, brewery ale_house, workhouse dormitory, int size)
{
    std::cout << "You have " << home_house->interact_fertiliser() << " units of fertiliser." << std::endl;
    if(home_house->interact_fertiliser() > 0){
        std::cout << "Pick a field to fertilise." << std::endl;
        int x_coord = int_inputter("Please enter x coordinate: ");
        int y_coord = int_inputter("Please enter y coordinate: ");
        if((x_coord < 1) || (x_coord > size)){
            std::cout << "x coordinate out of bounds, please try again." << std::endl;
        }
        else if((y_coord < 1) || (y_coord > size)){
            std::cout << "y coordinate out of bounds, please try again." << std::endl;
        }
        if(crop_fields[y_coord-1][x_coord-1]->interact_is_active() == true){
            if(crop_fields[y_coord-1][x_coord-1]->interact_is_fertilised() == false){
                crop_fields[y_coord-1][x_coord-1]->interact_is_fertilised(true);
                home_house->interact_fertiliser(home_house->interact_fertiliser()-1);
                std::cout << "Field at " << x_coord << "," << y_coord << " fertilised." << std::endl;
            }
            else{
                std::cout << "This field is already fertilised." << std::endl;
            }
        }
        else if(orchard_fields[y_coord-1][x_coord-1]->interact_is_active() == true){
            if(orchard_fields[y_coord-1][x_coord-1]->interact_is_fertilised() == false){
                orchard_fields[y_coord-1][x_coord-1]->interact_is_fertilised(true);
                home_house->interact_fertiliser(home_house->interact_fertiliser()-1);
                std::cout << "Field at " << x_coord << "," << y_coord << " fertilised." << std::endl;
            }
            else{
                std::cout << "This field is already fertilised." << std::endl;
            }
        }
        else if(multicrop_fields[y_coord-1][x_coord-1]->interact_is_active() == true){
            if(multicrop_fields[y_coord-1][x_coord-1]->interact_is_fertilised() == false){
                multicrop_fields[y_coord-1][x_coord-1]->interact_is_fertilised(true);
                home_house->interact_fertiliser(home_house->interact_fertiliser()-1);
                std::cout << "Field at " << x_coord << "," << y_coord << " fertilised." << std::endl;
            }
            else{
                std::cout << "This field is already fertilised." << std::endl;
            }
        }
        else if((home_house->interact_x_location() == x_coord) && (home_house->interact_y_location() == y_coord)){
            std::cout << "This is your farmhouse. You can't fertilise it." << std::endl;
        }
        else if((storehouse.interact_is_working() == true) && (storehouse.interact_x_location() == x_coord) && (storehouse.interact_y_location() == y_coord)){
            std::cout << "This is your storehouse. You can't fertilise it." << std::endl;
        }
        else if((ale_house.interact_is_working() == true) && (ale_house.interact_x_location() == x_coord) && (ale_house.interact_y_location() == y_coord)){
            std::cout << "This is your brewery. You can't fertilise it." << std::endl;
        }
        else if((dormitory.interact_is_working() == true) && (dormitory.interact_x_location() == x_coord) && (dormitory.interact_y_location() == y_coord)){
            std::cout << "This is your workhouse. You can't fertilise it." << std::endl;
        }
        else{
            std::cout << "There is nothing in this field to fertilise." << std::endl;
        }
    }
}
void harvest_manual(std::vector<std::vector<crop *>> crop_fields, std::vector<std::vector<orchard *>> orchard_fields, std::vector<std::vector<multicrop *>> multicrop_fields, farmhouse home_house, granary storehouse, brewery ale_house, workhouse dormitory, int size, int *index, int *output, int number_of_plants, std::string seed_types[])
{
    int x_coord = int_inputter("Please enter x coordinate: ");
    int y_coord = int_inputter("Please enter y coordinate: ");
    if((x_coord < 1) || (x_coord > size)){
        std::cout << "x coordinate out of bounds, please try again." << std::endl;
    }
    else if((y_coord < 1) || (y_coord > size)){
        std::cout << "y coordinate out of bounds, please try again." << std::endl;
    }
    if(crop_fields[y_coord-1][x_coord-1]->interact_is_active() == true){
        *output = crop_fields[y_coord-1][x_coord-1]->harvest_field();
        if(*output != -1){
            for(int i = 0; i < number_of_plants; i++){ //Be careful with the limit here.
                if(seed_types[i] == crop_fields[y_coord-1][x_coord-1]->interact_name()){
                    *index = i;
                }
            }
            std::cout << "You have harvested " << *output << " units of " << crop_fields[y_coord-1][x_coord-1]->interact_name() << ". ";
            crop_fields[y_coord-1][x_coord-1]->clear_field();
        }
    }
    else if(orchard_fields[y_coord-1][x_coord-1]->interact_is_active() == true){
        *output = orchard_fields[y_coord-1][x_coord-1]->harvest_field();
        if(*output != -1){
            for(int i = 0; i < number_of_plants; i++){ //Be careful with the limit here.
                if(seed_types[i] == orchard_fields[y_coord-1][x_coord-1]->interact_name()){
                    *index = i;
                }
            }
            std::cout << "You have harvested " << *output << " units of " << orchard_fields[y_coord-1][x_coord-1]->interact_name() << ". ";
            orchard_fields[y_coord-1][x_coord-1]->interact_is_producing(false);
        }
    }
    else if(multicrop_fields[y_coord-1][x_coord-1]->interact_is_active() == true){
        *output = multicrop_fields[y_coord-1][x_coord-1]->harvest_field();
        if(*output != -1){
            for(int i = 0; i < number_of_plants; i++){ //Be careful with the limit here.
                if(seed_types[i] == multicrop_fields[y_coord-1][x_coord-1]->interact_name()){
                    *index = i;
                }
            }
            std::cout << "You have harvested " << *output << " units of " << multicrop_fields[y_coord-1][x_coord-1]->interact_name() << ". ";
            multicrop_fields[y_coord-1][x_coord-1]->interact_is_producing(false);
        }
    }
    else if((home_house.interact_x_location() == x_coord) && (home_house.interact_y_location() == y_coord)){
        std::cout << "This is your farmhouse. You can't harvest a building." << std::endl;
    }
    else if((storehouse.interact_is_working() == true) && (storehouse.interact_x_location() == x_coord) && (storehouse.interact_y_location() == y_coord)){
        std::cout << "This is your storehouse. You can't harvest a building." << std::endl;
    }
    else if((ale_house.interact_is_working() == true) && (ale_house.interact_x_location() == x_coord) && (ale_house.interact_y_location() == y_coord)){
        std::cout << "This is your brewery. You can't harvest a building." << std::endl;
    }
    else if((dormitory.interact_is_working() == true) && (dormitory.interact_x_location() == x_coord) && (dormitory.interact_y_location() == y_coord)){
        std::cout << "This is your workhouse. You can't harvest a building." << std::endl;
    }
    else{
        std::cout << "There is nothing in this field." << std::endl;
    }
}
void harvest_auto(std::string seed_types[], std::vector<std::vector<crop *>> crop_fields, std::vector<std::vector<orchard *>> orchard_fields, std::vector<std::vector<multicrop *>> multicrop_fields, int * auto_harvest[], int number_of_plants, int to_harvest, int *harvestable)
{
    int i = 0, k = 0;
    while((*harvestable > 0) && (to_harvest > 0) && (i < 7)){
        int index = 0;
        if((crop_fields[i][k]->interact_is_active() == true) && (crop_fields[i][k]->interact_is_alive() == true) && (crop_fields[i][k]->interact_is_ripe() == true)){
            for(int l = 0; l < number_of_plants; l++){
                if(seed_types[l] == crop_fields[i][k]->interact_name()){
                    index = l;
                }
            }
            *auto_harvest[index] += crop_fields[i][k]->harvest_field();
            crop_fields[i][k]->clear_field();
            to_harvest--;
            *harvestable -= 1;
        }
        else if((orchard_fields[i][k]->interact_is_active() == true) && (orchard_fields[i][k]->interact_is_alive() == true) && (orchard_fields[i][k]->interact_is_producing() == true)){
            for(int l = 0; l < number_of_plants; l++){
                if(seed_types[l] == orchard_fields[i][k]->interact_name()){
                    index = l;
                }
            }
            *auto_harvest[index] += orchard_fields[i][k]->harvest_field();
            orchard_fields[i][k]->interact_is_producing(false);
            to_harvest--;
            *harvestable -= 1;
        }
        else if((multicrop_fields[i][k]->interact_is_active() == true) && (multicrop_fields[i][k]->interact_is_alive() == true) && (multicrop_fields[i][k]->interact_is_producing() == true)){
            for(int l = 0; l < number_of_plants; l++){
                if(seed_types[l] == multicrop_fields[i][k]->interact_name()){
                    index = l;
                }
            }
            *auto_harvest[index] += multicrop_fields[i][k]->harvest_field();
            multicrop_fields[i][k]->interact_is_producing(false);
            to_harvest--;
            *harvestable -= 1;
        }
        k++;
        if(k > 6){
            k = 0, i++;
        }
    }
    std::cout << "Your workers have automatically harvested:";
    for(int l = 0; l < number_of_plants; l++){
        if(*auto_harvest[l] > 0){
            std::cout << "   " << *auto_harvest[l] << " units of " << seed_types[l];
        }
    }
    std::cout << "." << std::endl;
}
void harvest_manage(std::string seed_types, int current_price, granary *storehouse, brewery *ale_house, int output, int *money)
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
void clear(std::vector<std::vector<crop *>> crop_fields, std::vector<std::vector<orchard *>> orchard_fields, std::vector<std::vector<multicrop *>> multicrop_fields, farmhouse home_house, granary storehouse, brewery ale_house, workhouse dormitory, int size, int *harvestable)
{
    int x_coord = int_inputter("Please enter x coordinate: ");
    int y_coord = int_inputter("Please enter y coordinate: ");
    if((x_coord < 1) || (x_coord > size)){
        std::cout << "x coordinate out of bounds, please try again." << std::endl;
    }
    else if((y_coord < 1) || (y_coord > size)){
        std::cout << "y coordinate out of bounds, please try again." << std::endl;
    }
    if(crop_fields[y_coord-1][x_coord-1]->interact_is_active() == true){
        crop_fields[y_coord-1][x_coord-1]->clear_field();
        std::cout << "Field at " << x_coord << "," << y_coord << " cleared." << std::endl;
        if(crop_fields[y_coord-1][x_coord-1]->interact_is_ripe() == true){
            *harvestable -= 1;
            crop_fields[y_coord-1][x_coord-1]->interact_is_ripe(false);
        }
    }
    else if(orchard_fields[y_coord-1][x_coord-1]->interact_is_active() == true){
        orchard_fields[y_coord-1][x_coord-1]->clear_field();
        std::cout << "Field at " << x_coord << "," << y_coord << " cleared." << std::endl;
        if(orchard_fields[y_coord-1][x_coord-1]->interact_is_producing() == true){
            *harvestable -= 1;
            orchard_fields[y_coord-1][x_coord-1]->interact_is_producing(false);
        }
    }
    else if(multicrop_fields[y_coord-1][x_coord-1]->interact_is_active() == true){
        multicrop_fields[y_coord-1][x_coord-1]->clear_field();
        std::cout << "Field at " << x_coord << "," << y_coord << " cleared." << std::endl;
        if(multicrop_fields[y_coord-1][x_coord-1]->interact_is_producing() == true){
            *harvestable -= 1;
            multicrop_fields[y_coord-1][x_coord-1]->interact_is_producing();
        }
    }
    else if((home_house.interact_x_location() == x_coord) && (home_house.interact_y_location() == y_coord)){
        std::cout << "This is your farmhouse. You can't remove that: you live there." << std::endl;
    }
    else if((storehouse.interact_is_working() == true) && (storehouse.interact_x_location() == x_coord) && (storehouse.interact_y_location() == y_coord)){
        std::cout << "This is your storehouse, you can't remove that right now." << std::endl;
    }
    else if((ale_house.interact_is_working() == true) && (ale_house.interact_x_location() == x_coord) && (ale_house.interact_y_location() == y_coord)){
        std::cout << "This is your brewery, you can't remove that right now." << std::endl;
    }
    else if((dormitory.interact_is_working() == true) && (dormitory.interact_x_location() == x_coord) && (dormitory.interact_y_location() == y_coord)){
        std::cout << "This is your workhouse, you can't remove that right now." << std::endl;
    }
    else{
        std::cout << "There's nothing in this field to clear." << std::endl;
    }
}

void end_turn(std::vector<std::vector<crop *>> crop_fields, std::vector<std::vector<orchard *>> orchard_fields, std::vector<std::vector<multicrop *>> multicrop_fields, farmhouse *home_house, granary storehouse, brewery *ale_house, workhouse dormitory, int *harvestable, int *month, int *money, int upkeep, int size, int number_of_plants, bool *sim_loop, bool *simulation, bool *first_run, int *current_price[], int base_price[], int price_variation[])
{
    bool end_turn = true;
    if(*harvestable > 0){
        std::cout << "There are still fields that can be harvested, are you sure you want to move on? Press y to confirm: ";
        char end_turn_input;
        std::cin >> end_turn_input;
        if(end_turn_input == 'y' || end_turn_input == 'Y'){
            end_turn = true;
        }
        else{
            end_turn = false;
        }
    }
    if(end_turn == true){
        *month += 2;
        if(*month >= 12){
            *month -= 12;
        }
        for(int i = 0; i < size; i++){
            for(int k = 0; k < size; k++){
                if(crop_fields[i][k]->interact_is_active() == true){
                    if(crop_fields[i][k]->interact_is_alive() == false){
                        crop_fields[i][k]->clear_field();
                    }
                    if(*month == 8 || *month == 9){
                        if(crop_fields[i][k]->interact_lifestage() == 4){
                            crop_fields[i][k]->interact_is_ripe(true);
                        }
                        else if(crop_fields[i][k]->interact_lifestage() == 3){
                            crop_fields[i][k]->interact_is_ripe(true);
                            crop_fields[i][k]->interact_is_overripe(true);
                        }
                    }
                    if(crop_fields[i][k]->interact_lifestage() >= 5 || *month == 10 || *month == 11 || *month == 0){
                        crop_fields[i][k]->die();
                        crop_fields[i][k]->interact_is_ripe(false);
                    }
                    else{
                        crop_fields[i][k]->grow();
                    }
                }
                if(orchard_fields[i][k]->interact_is_active() == true){
                    if((*month == 6 || *month == 7 || *month == 8 || *month == 9) && (orchard_fields[i][k]->interact_age() > 18)){
                        orchard_fields[i][k]->interact_is_producing(true);
                    }
                    if(*month == 10 || *month == 11){
                        orchard_fields[i][k]->interact_is_producing(false);
                        orchard_fields[i][k]->interact_is_fertilised(false);
                    }
                    orchard_fields[i][k]->grow();
                }
                if(multicrop_fields[i][k]->interact_is_active() == true){
                    if(multicrop_fields[i][k]->interact_is_alive() == false){
                        multicrop_fields[i][k]->clear_field();
                    }
                    if((*month > 4 && *month < 10) && (multicrop_fields[i][k]->interact_lifestage() > 1)){
                        multicrop_fields[i][k]->interact_is_producing(true);
                    }
                    if(multicrop_fields[i][k]->interact_lifestage() >= 5 || *month == 10 || *month == 11 || *month == 0){
                        multicrop_fields[i][k]->die();
                        multicrop_fields[i][k]->interact_is_producing(false);
                    }
                    else{
                        multicrop_fields[i][k]->grow();
                    }
                }
            }
        }
        *harvestable = 0;
        for(int i = 0; i < size; i++){
            for(int k = 0; k < size; k++){
                if(crop_fields[i][k]->interact_is_ripe() == true || orchard_fields[i][k]->interact_is_producing() == true || multicrop_fields[i][k]->interact_is_producing() == true){
                    *harvestable += 1;
                }
            }
        }
        *money -= upkeep;
        if(*money < 0){
            std::cout << "You have run out of money, so your farm is now bankrupt." << std::endl;
            std::cout << "Simulation over." << std::endl;
            *sim_loop = false;
            *simulation = false;
        }
        if(ale_house->interact_is_working() == true){
            if(ale_house->interact_current_brewing() > 0){
                ale_house->make_beer(ale_house->interact_current_brewing());
            }
        }
        if(dormitory.interact_is_working() == true){
            int to_fertilise = dormitory.interact_fertilisers();
            int i = 0, k = 0;
            while((to_fertilise > 0) && (i < 7) && (home_house->interact_fertiliser() > 0)){
                if((crop_fields[i][k]->interact_is_active() == true) && (crop_fields[i][k]->interact_is_alive() == true) && (crop_fields[i][k]->interact_is_fertilised() == false)){
                    crop_fields[i][k]->interact_is_fertilised(true);
                    home_house->change_fertiliser(-1);
                    to_fertilise--;
                }
                else if((orchard_fields[i][k]->interact_is_active() == true) && (orchard_fields[i][k]->interact_is_alive() == true) && (orchard_fields[i][k]->interact_is_fertilised() == false)){
                    orchard_fields[i][k]->interact_is_fertilised(true);
                    home_house->change_fertiliser(-1);
                    to_fertilise--;
                }
                else if((multicrop_fields[i][k]->interact_is_active() == true) && (multicrop_fields[i][k]->interact_is_alive() == true) && (multicrop_fields[i][k]->interact_is_fertilised() == false)){
                    multicrop_fields[i][k]->interact_is_fertilised(true);
                    home_house->change_fertiliser(-1);
                    to_fertilise--;
                }
                k++;
                if(k > 6){
                    k = 0, i++;
                }
            }
            if((home_house->interact_fertiliser() == 0) && (dormitory.interact_fertilisers() > 0)){
                std::cout << "You are out of fertiliser, so yor workers cannot fertilise the fields." << std::endl;
                system("pause");
            }
        }
        if((*harvestable > 0) && (dormitory.interact_is_working() == true) && (dormitory.interact_harvesters() > 0)){
            *first_run = true;
        }
        for(int i = 0; i < number_of_plants; i++){
            *current_price[i] = change_prices(*current_price[i], base_price[i], price_variation[i]);
        }
    }
}

void test_function(farmhouse *home_house)
{
    home_house->change_seed_totals("Wheat", 5);
    std::cout << "Upadating seed totals." << std::endl;
}
void test(int *money)
{
    *money += 1000;
}