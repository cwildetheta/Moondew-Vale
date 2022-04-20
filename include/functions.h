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

void options(int, granary, brewery, workhouse, int, int, int, int[], int[], std::string[]);
void main_ui(std::vector<std::vector<crop>>, std::vector<std::vector<orchard>>, std::vector<std::vector<multicrop>>, int, int, int, int, int, farmhouse, granary, brewery, workhouse, int[], int[], std::string[]);
int change_prices(int, int, int);
void set_up_granary(std::vector<std::vector<crop>>, std::vector<std::vector<orchard>>, std::vector<std::vector<multicrop>>, farmhouse, granary *, brewery, workhouse, int, int*, int*);
void set_up_brewery(std::vector<std::vector<crop>>, std::vector<std::vector<orchard>>, std::vector<std::vector<multicrop>>, farmhouse, granary, brewery *, workhouse, int, int*, int *);
void set_up_workhouse(std::vector<std::vector<crop>>, std::vector<std::vector<orchard>>, std::vector<std::vector<multicrop>>, farmhouse, granary, brewery, workhouse *, int, int*, int *);

void plant(std::string[], std::vector<std::vector<crop *>>, std::vector<std::vector<orchard *>>, std::vector<std::vector<multicrop *>>, farmhouse *, granary, brewery, workhouse, int, char[], char[], int[]);
void fertilise(std::vector<std::vector<crop *>>, std::vector<std::vector<orchard *>>, std::vector<std::vector<multicrop *>>, farmhouse *, granary, brewery, workhouse, int);
void harvest_manual(std::vector<std::vector<crop *>>, std::vector<std::vector<orchard *>>, std::vector<std::vector<multicrop *>>, farmhouse, granary, brewery, workhouse, int, int *, int *, int, std::string[]);
void harvest_auto(std::string[], std::vector<std::vector<crop *>>, std::vector<std::vector<orchard *>>, std::vector<std::vector<multicrop *>>, int *[], int, int, int *);
void harvest_manage(std::string, int, granary *, brewery *, int, int *);
void clear(std::vector<std::vector<crop *>>, std::vector<std::vector<orchard *>>, std::vector<std::vector<multicrop *>>, farmhouse, granary, brewery, workhouse, int, int *);

void end_turn(std::vector<std::vector<crop *>>, std::vector<std::vector<orchard *>>, std::vector<std::vector<multicrop *>>, farmhouse *, granary, brewery *, workhouse, int *, int *, int *, int, int, int, bool *, bool *, bool *, int *[], int[], int[]);

void test_function(farmhouse *);
void test(int *);

#endif //FUNCTIONS_H_INCLUDED