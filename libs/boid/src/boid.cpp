#include "boid.h"

//initialize the static members
const int boid::left_margin_ = (0);
const int boid::right_margin_{boid::get_screen_width()};
const int boid::top_margin_{boid::get_screen_height()};
const int boid::bottom_margin_{0};
const int boid::v_min_{1};
const int boid::v_max_{10};
const int boid::d_sep_{10};
const int boid::d_ca_{50};
const int boid::turn_factor_{5};
const std::string boid::filename{"../visualizer/my_coordinates.txt"};


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
    :pos_x_{0}, pos_y_{0},vel_x_{0},vel_y_{0}
{
    //il boid viene istanziato in un punto casuale e a vel casuale
    initialize_at_random_positon();
    initialize_at_random_velocity();
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
    write_last_position();
    return;

}

void boid::initialize_at_random_positon()
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution_1(0, get_screen_width());
    std::uniform_int_distribution<> distribution_2(0, get_screen_height());

    pos_x_ = distribution_1(generator);
    pos_y_ = distribution_2(generator);

    //write position into the file
    return;
}

void boid::initialize_at_random_velocity()
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(-(v_max_ / std::sqrt(2)), (v_max_ / std::sqrt(2)));

    vel_x_ = distribution(generator);
    vel_y_ = distribution(generator);


    return;
}
void boid::check_screen_margins()
{
    if (pos_x_ < left_margin_)
        vel_x_ += turn_factor_;
    if (pos_x_ > right_margin_)
        vel_x_ -= turn_factor_;
    if (pos_y_ < bottom_margin_)
        vel_y_ += turn_factor_;
    if (pos_y_ > top_margin_)
        vel_y_ -= turn_factor_;
    
    return;

}

void boid::write_last_position()
{
    std::fstream myfile;
    if (std::filesystem::exists(filename))
        myfile.open(filename,std::ios::app); //open the file in appending mode
        if(myfile.is_open()){
            myfile << pos_x_ << " " << pos_y_ << "\n";
            myfile.close();
        }

    else{ 
        myfile.open(filename,std::ios::app);
        if(myfile.is_open()){
            myfile << left_margin_ << " " << right_margin_ << " " << bottom_margin_ << " " << top_margin_ << "\n";
            myfile << pos_x_ << " " << pos_y_ << "\n";
            myfile.close();
        }
        else{
            std::cerr << "Unable to open the file, launch the program from the directory build and type './app/eseguibile' \n";
            exit(EXIT_FAILURE);
        }

    }
    return;
}
