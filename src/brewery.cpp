#include "../include/brewery.h"
#include <iostream>

brewery::brewery(int int_input_1, int int_input_2, int cost_input, int upkeep_input, bool is_working_input)
{
    storage_space = int_input_1;
    brewing_cap = int_input_2;
    current_total = 0, stored_barley = 0, stored_beer = 0, current_brewing = 0;
    interact_cost(cost_input);
    interact_upkeep(upkeep_input);
    interact_is_working(is_working_input);
}
void brewery::calculate_total()
{
    current_total = stored_barley + stored_beer;
}
void brewery::make_beer(int int_input)
{
    stored_barley -= int_input;
    stored_beer += int_input;
    current_brewing = 0;
}
void brewery::sell_beer(int int_input)
{
    stored_beer -= int_input;
}
void brewery::transfer_barley(int int_input)
{
    stored_barley += int_input;
}
void brewery::add_to_brewing(int int_input)
{
    current_brewing += int_input;
}
void brewery::barley_in(granary *storehouse)
{
    if(storehouse->interact_is_working() == true){
        if(storehouse->interact_store_totals("Barley") > 0){
            calculate_total();
            std::cout << "There are " << storehouse->interact_store_totals("Barley") << " units of Barley in the storehouse and " << (interact_storage_space() - interact_current_total()) << " units of space in the brewery. ";
            if(interact_current_total() == interact_storage_space()){
                std::cout << "The brewery is full. Remove something if you wish to add more Barley to it." << std::endl;
            }
            else{
                int move_input = int_inputter("How much Barley do you want to move into the brewery: ");
                if(move_input >= storehouse->interact_store_totals("Barley")){
                    move_input = storehouse->interact_store_totals("Barley");
                    std::cout << "Moving the entire Barley store into the brewery." << std::endl;
                    storehouse->add_to_store("Barley", -move_input);
                    transfer_barley(move_input);
                }
                else{
                    std::cout << "Moving " << move_input << " units of Barley into the brewery." << std::endl;
                    storehouse->add_to_store("Barley", -move_input);
                    transfer_barley(move_input);
                }
            }
        }
        else{
            std::cout << "There is currently no Barley stored in the storehouse." << std::endl;
        }
    }
    else{
        std::cout << "You currently don't have a storehouse, so there is nowhere to move Barley from." << std::endl;
    }
}
void brewery::barley_out(granary *storehouse)
{
    if(storehouse->interact_is_working() == true){
        if(interact_stored_barley() > 0){
            storehouse->calculate_total();
            std::cout << "There are " << interact_stored_barley() << " units of Barley in the brewery, and " << (storehouse->interact_storage_space() - storehouse->interact_current_total()) << " units of space free in the storehouse. ";
            if(storehouse->interact_current_total() == storehouse->interact_storage_space()){
                std::cout << "There storehouse is full, so no Barley can be move to there." << std::endl;
            }
            else{
                int move_input = int_inputter("How much Barley do you want to move into the storehouse: ");
                if(move_input >= interact_stored_barley()){
                    move_input = interact_stored_barley();
                    std::cout << "Moving the entire Barley store into the storehouse." << std::endl;
                    storehouse->add_to_store("Barley", move_input);
                    transfer_barley(-move_input);
                }
                else{
                    std::cout << "Moving " << move_input << " units of Barley into the storehouse." << std::endl;
                    storehouse->add_to_store("Barley", move_input);
                    transfer_barley(-move_input);
                }
            }
        }
        else{
            std::cout << "There is currently no Barley stored in the brewery." << std::endl;
        }
    }
    else{
        std::cout << "You currently don't have a storehouse, so there is nowhere to move Barley to." << std::endl;
    }
}
void brewery::brew()
{
    bool in_brew_adding = true;
    while(in_brew_adding == true){
        std::cout << "There are currently " << interact_current_brewing() << " units of Barley waiting to be brewed, out of a potential total of " << interact_brewing_cap() << " units." << std::endl;
        std::cout << "Would you like to add (a) or remove (r) Barley, or exit (e): ";
        char brew_input;
        int move_amount;
        std::cin >> brew_input;
        switch(brew_input){
            case 'a':
            case 'A':{
                if(interact_current_brewing() == interact_brewing_cap()){
                    std::cout << "The brewing process is already at capacity, you can't add any more Barley." << std::endl;
                }
                else if(interact_stored_barley() == 0){
                    std::cout << "There is no Barley currently stored in the brewery to add to the process." << std::endl;
                }
                else{
                    move_amount = int_inputter("How much Barley would you like to add: ");
                    if(move_amount > interact_stored_barley()){
                        move_amount = interact_stored_barley();
                    }
                    if(move_amount > (interact_brewing_cap() - interact_current_brewing())){
                        move_amount = (interact_brewing_cap() - interact_current_brewing());
                    }
                    std::cout << "Adding " << move_amount << " units of Barley to the brewing process." << std::endl;
                    add_to_brewing(move_amount);
                }
                break;
            }
            case 'r':
            case 'R':{
                if(interact_current_brewing() == 0){
                    std::cout << "There is no Barley in the brewing process to be removed." << std::endl;
                }
                else{
                    move_amount = int_inputter("How much Barley would you like to remove: ");
                    if(move_amount > interact_current_brewing()){
                        move_amount = interact_current_brewing();
                    }
                    std::cout << "Removing " << move_amount << " units of Barley from the brewing process." << std::endl;
                    add_to_brewing(-move_amount);
                }
                break;
            }
            case 'e':
            case 'E':{
                in_brew_adding = false;
                break;
            }
            default:{
                std::cout << "Invalid entry, please try again." << std::endl;
                break;
            }
        }
    }
}
void brewery::sale(int *money)
{                                
    if(interact_stored_beer() > 0){
        std::cout << "There are currently " << interact_stored_beer() << " units of beer in the brewery. It sells for \x9C" << "20 per unit. ";
        int sell_amount = int_inputter("How many would you like to sell: ");
        if(sell_amount >= interact_stored_beer()){
            sell_amount = interact_stored_beer();
            std::cout << "Selling the entire beer stock." << std::endl;
            sell_beer(sell_amount);
            *money += (sell_amount*20);
        }
        else{
            std::cout << "Selling " << sell_amount << " units of beer." << std::endl;
            sell_beer(sell_amount);
            *money += (sell_amount*20);
        }
    }
    else{
        std::cout << "There is currently no beer stored in the brewery to sell." << std::endl;
    }
}

//INPUTS AND OUTPUTS//
int brewery::interact_storage_space()
{
    return storage_space;
}
void brewery::interact_storage_space(int int_input)
{
    storage_space = int_input;
}
int brewery::interact_current_total()
{
    return current_total;
}
void brewery::interact_current_total(int int_input)
{
    current_total = int_input;
}
int brewery::interact_stored_barley()
{
    return stored_barley;
}
void brewery::interact_stored_barley(int int_input)
{
    stored_barley = int_input;
}
int brewery::interact_stored_beer()
{
    return stored_beer;
}
void brewery::interact_stored_beer(int int_input)
{
    stored_beer = int_input;
}
int brewery::interact_brewing_cap()
{
    return brewing_cap;
}
void brewery::interact_brewing_cap(int int_input)
{
    brewing_cap = int_input;
}
int brewery::interact_current_brewing()
{
    return current_brewing;
}
void brewery::interact_current_brewing(int int_input)
{
    current_brewing = int_input;
}