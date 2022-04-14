#ifndef BUILDING_H_INCLUDED
#define BUILDING_H_INCLUDED

class building{
    private:
        bool is_working;
        int cost, upkeep, x_location, y_location;

    public:
        void build(int, int);

        //VARIABLE INTERACTIONS//
        bool interact_is_working();
        void interact_is_working(bool);
        int interact_cost();
        void interact_cost(int);
        int interact_upkeep();
        void interact_upkeep(int);
        int interact_x_location();
        void interact_x_location(int);
        int interact_y_location();
        void interact_y_location(int);
};

#endif //BUILDING_H_INCLUDED