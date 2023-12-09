#include "boid.h"
#include<X11/Xlib.h>
#include<random>
#include<ctime>

//initialize the static members
const int boid::left_margin_ = (0);
const int boid::right_margin_{boid::get_screen_width()};
const int boid::top_margin_{0};
const int boid::bottom_margin_{boid::get_screen_height()};
const int boid::v_min_{1};
const int boid::v_max_{10};
const int boid::d_sep_{10};
const int boid::d_ca_{50};
const int boid::turn_factor_{5};


boid::boid(int pos_x, int pos_y, int vel_x, int vel_y)
    : pos_x_{pos_x}, pos_y_{pos_y}, vel_x_{vel_x}, vel_y_{vel_y}
{
    //check initial position given by the user
    if(pos_x > right_margin_)
        pos_x_ = right_margin_;
    if(pos_x < left_margin_)
        pos_x_ = left_margin_;
    if(pos_y > bottom_margin_)
        pos_y_ = bottom_margin_;
    if(pos_y < top_margin_)
        pos_y_ = top_margin_;
 
    return;
    
}

boid::boid()
{
    //il boid viene istanziato in un punto casuale e a vel casuale
    pos_x_ = get_screen_width() / 2;
    pos_y_ = get_screen_height() / 2;
    vel_x_ = v_max_/2;
    vel_y_ = v_max_/2;
    return;

}

int boid::get_screen_height()
{
    Display* display = XOpenDisplay(nullptr);
    if (!display) {
        std::cerr << "Unable to open display.\n";
        return 1;
    }

    Screen* screen = DefaultScreenOfDisplay(display);
    if (!screen) {
        std::cerr << "Unable to obtain screen information.\n";
        XCloseDisplay(display);
        return 1;
    }

    // Extract screen dimensions
    int screenWidth = WidthOfScreen(screen);
    int screenHeight = HeightOfScreen(screen);

    XCloseDisplay(display);
    return screenHeight;

}

int boid::get_screen_width()
{
    Display* display = XOpenDisplay(nullptr);
    if (!display) {
        std::cerr << "Unable to open display.\n";
        return 1;
    }

    Screen* screen = DefaultScreenOfDisplay(display);
    if (!screen) {
        std::cerr << "Unable to obtain screen information.\n";
        XCloseDisplay(display);
        return 1;
    }

    // Extract screen dimensions
    int screenWidth = WidthOfScreen(screen);

    XCloseDisplay(display);

    return screenWidth;

}

void boid::update_positon()
{
    pos_x_ = pos_x_ + vel_x_;
    pos_y_ = pos_y_ + vel_y_;

    check_screen_margins();
    return;

}

void boid::initialize_at_random_positon()
{
    return;
}

void boid::check_screen_margins()
{
    if (pos_x_ < left_margin_)
        vel_x_ += turn_factor_;
    if (pos_x_ > right_margin_)
        vel_x_ -= turn_factor_;
    if (pos_y_ > bottom_margin_)
        vel_y_ -= turn_factor_;
    if (pos_y_ < top_margin_)
        vel_y_ += turn_factor_;
    
    return;

}

