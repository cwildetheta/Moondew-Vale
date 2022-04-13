#include "../include/brewery.h"

brewery::brewery(int int_input_1, int int_input_2)
{
    storage_space = int_input_1;
    brewing_cap = int_input_2;
    current_total = 0, stored_barley = 0, stored_beer = 0;
}
void brewery::calculate_total()
{
    current_total = stored_barley + stored_beer;
}
void brewery::make_beer(int int_input)
{
    stored_barley -= int_input;
    stored_beer += int_input;
}
void brewery::sell_beer(int int_input)
{
    stored_beer -= int_input;
}
void brewery::transfer_barley(int int_input)
{
    stored_barley += int_input;
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