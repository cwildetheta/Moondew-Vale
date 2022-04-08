#include "../include/crop.h"
#include <iostream>

void crop::grow()
{
    lifestage++;
}

//INPUTS AND OUTPUTS
int crop::interact_lifestage()
{
    return lifestage;
}
void crop::interact_lifestage(int int_input)
{
    lifestage = int_input;
}
bool crop::interact_is_ripe()
{
    return is_ripe;
}
void crop::interact_is_ripe(bool bool_input)
{
    is_ripe = bool_input;
}
bool crop::interact_is_overripe()
{
    return is_overripe;
}
void crop::interact_is_overripe(bool bool_input)
{
    is_overripe = bool_input;
}