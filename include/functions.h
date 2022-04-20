#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include "../include/base_functions.h"
#include "../include/crop.h"
#include "../include/orchard.h"
#include "../include/multicrop.h"
#include "../include/farmhouse.h"
#include "../include/granary.h"
#include "../include/brewery.h"
#include "../include/workhouse.h"
#include <vector>

void options(int, granary, brewery, workhouse, int, int, int);
void main_ui(std::vector<std::vector<crop>>, std::vector<std::vector<orchard>>, std::vector<std::vector<multicrop>>, int, int, int, int, int, farmhouse, granary, brewery, workhouse);
int change_prices(int, int, int);
//void test_function(farmhouse *);
void set_up_granary(std::vector<std::vector<crop>>, std::vector<std::vector<orchard>>, std::vector<std::vector<multicrop>>, farmhouse, granary *, brewery, workhouse, int, int*, int*);
void set_up_brewery(std::vector<std::vector<crop>>, std::vector<std::vector<orchard>>, std::vector<std::vector<multicrop>>, farmhouse, granary, brewery *, workhouse, int, int*, int *);
void set_up_workhouse(std::vector<std::vector<crop>>, std::vector<std::vector<orchard>>, std::vector<std::vector<multicrop>>, farmhouse, granary, brewery, workhouse *, int, int*, int *);
void harvest(std::string, int, granary *, brewery *, int, int *);
void clear(std::vector<std::vector<crop *>>, std::vector<std::vector<orchard *>>, std::vector<std::vector<multicrop *>>, farmhouse, granary, brewery, workhouse, int, int *);
void test(int *);

#endif //FUNCTIONS_H_INCLUDED