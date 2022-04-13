#include "../include/workhouse.h"

workhouse::workhouse(int int_input)
{
    workers = int_input;
    harvesters = 0, fertilisers = 0;
}
void workhouse::increase_workers(int int_input)
{
    workers += int_input;
}
void workhouse::automate_harvest(int int_input){}
void workhouse::automate_fertilise(int int_input){}

//INPUTS AND OUTPUTS//
int workhouse::interact_workers()
{
    return workers;
}
void workhouse::interact_workers(int int_input)
{
    workers = int_input;
}
int workhouse::interact_harvesters()
{
    return harvesters;
}
void workhouse::interact_harvesters(int int_input)
{
    harvesters = int_input;
}
int workhouse::interact_fertilisers()
{
    return fertilisers;
}
void workhouse::interact_fertilisers(int int_input)
{
    fertilisers = int_input;
}