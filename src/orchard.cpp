#include "../include/orchard.h"
#include <iostream>

void orchard::grow()
{
    age++;
}

//INPUTS AND OUTPUTS
int orchard::interact_age()
{
    return age;
}
void orchard::interact_age(int int_input)
{
    age = int_input;
}
int orchard::interact_yield()
{
    return yield;
}
void orchard::interact_yield(int int_input)
{
    yield = int_input;
}
bool orchard::interact_is_producing()
{
    return is_producing;
}
void orchard::interact_is_producing(bool bool_input)
{
    is_producing = bool_input;
}