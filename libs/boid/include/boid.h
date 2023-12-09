#ifndef BOID_H
#define BOID_H
#include<iostream>


class boid
{
private:
//static member, visible for all the class objects 
    static const int left_margin_;
    static const int right_margin_;
    static const int d_sep_;
    static const int d_ca_;
    static const int v_min_;
    static const int v_max_;
    static const int turn_factor_;


//member
    int pos_y_;
    int vel_x_;
    int pos_x_;
    int vel_y_;

// private member functions
    void initialize_at_random_positon();
    void initialize_at_random_velocity();
    void check_screen_margins();
    


public:
    
    static const int top_margin_;
    static const int bottom_margin_;
    boid(int pos_x, int pos_y, int vel_x, int vel_y);
    boid();

    int get_pos_x_(){return pos_x_;}
    int get_pos_y_(){return pos_y_;}
    int get_vel_x_(){return vel_x_;}
    int get_vel_y_(){return vel_y_;}

    void update_positon();

    //static function, indipendent of any object of the class
    static int get_screen_height();
    static int get_screen_width();

};





#endif