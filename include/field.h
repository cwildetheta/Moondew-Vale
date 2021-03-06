#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED
#include <string>

class field{
    private:
        bool is_active, is_alive, is_fertilised;
        std::string name;
        char symbol, immature_symbol;
        int yield, lifestage;

    public:
        void plant_field(std::string, char, char, int);
        void grow();
        void die();
        void clear_field();

        //VARIABLE INTERACTIONS//
        bool interact_is_active();
        void interact_is_active(bool);
        std::string interact_name();
        void interact_name(std::string);
        bool interact_is_alive();
        void interact_is_alive(bool);
        bool interact_is_fertilised();
        void interact_is_fertilised(bool);
        char interact_symbol();
        void interact_symbol(char);
        char interact_immature_symbol();
        void interact_immature_symbol(char);
        int interact_yield();
        void interact_yield(int);
        int interact_lifestage();
        void interact_lifestage(int);
};

#endif //FIELD_H_INCLUDED