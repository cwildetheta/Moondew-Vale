#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED
#include <string>

class field{
    private:
        bool is_active, is_alive, is_fertilised;
        std::string name, health;
        char symbol;

    public:
        void clear_field();
        void die();
        void plant_field(std::string, char);
        void harvest_field();
        void develop_illness();

        //VARIABLE INTERACTIONS//
        bool interact_is_active();
        void interact_is_active(bool);
        std::string interact_name();
        void interact_name(std::string);
        bool interact_is_alive();
        void interact_is_alive(bool);
        bool interact_is_fertilised();
        void interact_is_fertilised(bool);
        std::string interact_health();
        void interact_health(std::string);
        char interact_symbol();
        void interact_symbol(char);
};

#endif //FIELD_H_INCLUDED