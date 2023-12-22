#ifndef BOID_H
#define BOID_H
#include<string>
#include<X11/Xlib.h>
#include<random>
#include<fstream>
#include<iostream>
#include<filesystem>
#include<cmath>
#include<list>

class boid
{
public:
//static member, visible for all the class objects 
    static const int top_margin_;
    static const int bottom_margin_;
    static const int left_margin_;
    static const int right_margin_;
    static const float d_sep_;
    static const float d_ca_;
    static const float v_min_;
    static const float v_max_;
    static const float turn_factor_;
    static const float avoid_factor;
    static const float centering_factor;
    static const float align_factor;

    static size_t num_of_instantiated_boid;


    //static const std::string filename;

private:
//member
    float pos_x_;
    float pos_y_;
    float vel_x_;
    float vel_y_;
    size_t boid_id_;

// private member functions
    void initialize_at_random_positon();
    void initialize_at_random_velocity();
    void check_screen_margins();
    void separation(const std::list<boid>& neighbors);
    void alignement(const std::list<boid>& neighbors);
    void cohesion(const std::list<boid>& neighbors);
    void speed_limits();
    


public:
    
    boid(float pos_x, float pos_y, float vel_x, float vel_y);
    boid();

    int get_pos_x_() const {return pos_x_;}
    int get_pos_y_() const {return pos_y_;}
    int get_vel_x_() const {return vel_x_;}
    int get_vel_y_() const {return vel_y_;}
    size_t get_boid_id_() const {return boid_id_;}

    void update_positon(const std::list<boid>& neighbors);
    float distance_from_other_boid(const boid& other_boid);

    //static function, indipendent of any object of the class
    static int get_screen_height();
    static int get_screen_width();

};





#endif