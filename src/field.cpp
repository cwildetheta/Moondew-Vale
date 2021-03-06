#include "../include/field.h"

void field::plant_field(std::string plant_name, char plant_symbol, char small_plant_symbol, int yield_input)
{
    name = plant_name;
    is_active = true;
    is_alive = true;
    is_fertilised = false;
    symbol = plant_symbol;
    immature_symbol = small_plant_symbol;
    yield = yield_input;
}
void field::grow()
{
    lifestage++;
}
void field::die()
{
    is_alive = false;
    is_fertilised = false;
    symbol = 'x';
    immature_symbol = 'x';
}
void field::clear_field()
{
    is_active = false;
}

//INPUTS AND OUTPUTS
bool field::interact_is_active()
{
    return is_active;
}
void field::interact_is_active(bool bool_input)
{
    is_active = bool_input;
}
std::string field::interact_name()
{
    return name;
}
void field::interact_name(std::string string_input)
{
    name = string_input;
}
bool field::interact_is_alive()
{
    return is_alive;
}
void field::interact_is_alive(bool bool_input)
{
    is_alive = bool_input;
}
bool field::interact_is_fertilised()
{
    return is_fertilised;
}
void field::interact_is_fertilised(bool bool_input)
{
    is_fertilised = bool_input;
}
char field::interact_symbol()
{
    return symbol;
}
void field::interact_symbol(char char_input)
{
    symbol = char_input;
}
char field::interact_immature_symbol()
{
    return immature_symbol;
}
void field::interact_immature_symbol(char char_input)
{
    immature_symbol = char_input;
}
int field::interact_yield()
{
    return yield;
}
void field::interact_yield(int int_input)
{
    yield = int_input;
}
int field::interact_lifestage()
{
    return lifestage;
}
void field::interact_lifestage(int int_input)
{
    lifestage = int_input;
}