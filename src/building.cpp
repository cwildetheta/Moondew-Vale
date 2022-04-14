#include "../include/building.h"

void building::build(int x_input, int y_input)
{
    x_location = x_input, y_location = y_input;
    is_working = true;
}

//INPUTS AND OUTPUTS
bool building::interact_is_working()
{
    return is_working;
}
void building::interact_is_working(bool bool_input)
{
    is_working = bool_input;
}
int building::interact_cost()
{
    return cost;
}
void building::interact_cost(int int_input)
{
    cost = int_input;
}
int building::interact_upkeep()
{
    return upkeep;
}
void building::interact_upkeep(int int_input)
{
    upkeep = int_input;
}
int building::interact_x_location()
{
    return x_location;
}
void building::interact_x_location(int int_input)
{
    x_location = int_input;
}
int building::interact_y_location()
{
    return y_location;
}
void building::interact_y_location(int int_input)
{
    y_location = int_input;
}