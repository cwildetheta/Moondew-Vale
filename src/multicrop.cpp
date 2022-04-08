#include "../include/multicrop.h"
#include <iostream>

void multicrop::grow()
{
    lifestage++;
}

//INPUTS AND OUTPUTS
int multicrop::interact_lifestage()
{
    return lifestage;
}
void multicrop::interact_lifestage(int int_input)
{
    lifestage = int_input;
}
int multicrop::interact_yield()
{
    return yield;
}
void multicrop::interact_yield(int int_input)
{
    yield = int_input;
}
bool multicrop::interact_is_producing()
{
    return is_producing;
}
void multicrop::interact_is_producing(bool bool_input)
{
    is_producing = bool_input;
}