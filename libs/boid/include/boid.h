#ifndef BOID_H
#define BOID_H
#include<string>
#include<X11/Xlib.h>
#include<random>
#include<fstream>
#include<iostream>
#include<filesystem>
#include<cmath>

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
    static const std::string filename;


//member
    int pos_x_;
    int pos_y_;
    int vel_x_;
    int vel_y_;

// private member functions
    void initialize_at_random_positon();
    void initialize_at_random_velocity();
    void check_screen_margins();
    void write_last_position();
    


public:
    
    static const int top_margin_;
    static const int bottom_margin_;
    boid(int pos_x, int pos_y, int vel_x, int vel_y);
    boid();

    int get_pos_x_() const {return pos_x_;}
    int get_pos_y_() const {return pos_y_;}
    int get_vel_x_() const {return vel_x_;}
    int get_vel_y_() const {return vel_y_;}

    void update_positon();
    bool is_neighbor(const boid& other_boid);

    //static function, indipendent of any object of the class
    static int get_screen_height();
    static int get_screen_width();

};





#endif