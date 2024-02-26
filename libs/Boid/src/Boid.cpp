#include "Boid.h"

//initialize the static members
const int Boid::left_margin_ {0};
const int Boid::right_margin_{1920};
const int Boid::top_margin_{1080};
const int Boid::bottom_margin_{0};
const float Boid::v_min_{25};
const float Boid::v_max_{100};
const float Boid::d_sep_{20};
const float Boid::d_ca_{500};
const float Boid::turn_factor_{10};
const float Boid::avoid_factor{10};
const float Boid::centering_factor{0.1};
const float Boid::align_factor{0.85};
size_t Boid::num_of_instantiated_boid{0};


Boid::Boid(float pos_x, float pos_y, float vel_x, float vel_y)
    : pos_x_{pos_x}, pos_y_{pos_y}, vel_x_{vel_x}, vel_y_{vel_y}
{
    //check initial position given by the user
    if(pos_x > right_margin_)
        pos_x_ = right_margin_;
    if(pos_x < left_margin_)
        pos_x_ = left_margin_;
    if(pos_y < bottom_margin_)
        pos_y_ = bottom_margin_;
    if(pos_y > top_margin_)
        pos_y_ = top_margin_;

    //assign the boid id
    boid_id_ = num_of_instantiated_boid;
    num_of_instantiated_boid++;
 
    return;
    
}

Boid::Boid()
    :pos_x_{0}, pos_y_{0},vel_x_{0},vel_y_{0}
{
    //il boid viene istanziato in un punto casuale e a vel casuale
    initialize_at_random_positon();
    initialize_at_random_speed();
    //assign the boid id
    boid_id_ = num_of_instantiated_boid;
    num_of_instantiated_boid++;
    return;
}

void Boid::initialize_at_random_positon()
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<> distribution_1(0, right_margin_);
    std::uniform_real_distribution<> distribution_2(0, top_margin_);

    pos_x_ = distribution_1(generator);
    pos_y_ = distribution_2(generator);

    return;
}

void Boid::initialize_at_random_speed()
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution distribution(-(v_max_ / std::sqrt(2)), (v_max_ / std::sqrt(2)));

    vel_x_ = distribution(generator);
    vel_y_ = distribution(generator);


    return;
}

void Boid::check_screen_margins()
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

float Boid::distance_from_other_boid(const Boid& other_boid)
{
    double distance_in_x {std::pow((pos_x_ - other_boid.get_pos_x_()),2)};
    double distance_in_y {std::pow((pos_y_ - other_boid.get_pos_y_()),2)};
    double distance = std::sqrt(distance_in_x + distance_in_y);

    return static_cast<float> (distance);

}

void Boid::separation(const std::vector<Boid>& neighbors)
{
    if(neighbors.empty()) //if there are no neighbors, return..
        return;

    float close_dx{0};
    float close_dy{0};

    for (const Boid &el : neighbors)
    {
        if (distance_from_other_boid(el) < Boid::d_sep_)
        {
            close_dx += pos_x_ - el.get_pos_x_();
            close_dy += pos_y_ - el.get_pos_y_();
        }
    }

    //update speed for separation
    vel_x_ += close_dx * Boid::avoid_factor;
    vel_y_ += close_dy * Boid::avoid_factor;

    return;
}

void Boid::alignement(const std::vector<Boid>& neighbors)
{
    if(neighbors.empty()) //if there are not neighbors, return..
        return;
    
    float x_vel_avg{0};
    float y_vel_avg{0};
    int neighboring_boids{static_cast<int>(neighbors.size())};

    

    for(const Boid& el:neighbors){
        x_vel_avg += el.get_vel_x_();
        y_vel_avg += el.get_vel_y_();
    }
    if(neighboring_boids > 0){
        x_vel_avg = x_vel_avg / neighboring_boids;
        y_vel_avg = y_vel_avg / neighboring_boids;
    }
    else return;

    //update speed
    vel_x_ += (x_vel_avg - vel_x_) * Boid::align_factor;
    vel_y_ += (y_vel_avg - vel_y_) * Boid::align_factor;

    return;
}

void Boid::cohesion(const std::vector<Boid>& neighbors)
{
    if(neighbors.empty()) //if there are not neighbors, return..
        return;
    
    float x_pos_avg{0};
    float y_pos_avg{0};
    int neighboring_boids{static_cast<int>(neighbors.size())};

    
    
    for(const Boid& el:neighbors){
        x_pos_avg += el.get_pos_x_();
        y_pos_avg += el.get_pos_y_();
    }
    if(neighboring_boids > 0){
        x_pos_avg = x_pos_avg / neighboring_boids;
        y_pos_avg = y_pos_avg / neighboring_boids;
    }
    else return;

    //update speed
    vel_x_ += (x_pos_avg - pos_x_) * Boid::centering_factor;
    vel_y_ += (y_pos_avg - pos_y_) * Boid::centering_factor;

}

void Boid::speed_limits()
{
    double speed {std::sqrt(vel_x_ * vel_x_ + vel_y_ * vel_y_)};

    if (speed > Boid::v_max_){
        vel_x_ = (vel_x_ / speed) * Boid::v_max_;
        vel_y_ = (vel_y_ / speed) * Boid::v_max_;
    }

    if (speed < Boid::v_min_){
        vel_x_ = (vel_x_ / speed) * Boid::v_min_;
        vel_y_ = (vel_y_ / speed) * Boid::v_min_;
    }

    return;

}

void Boid::update_speed(const std::vector<Boid>& neighbors)
{
    separation(neighbors);
    alignement(neighbors);
    cohesion(neighbors);
    speed_limits();
    check_screen_margins();

    return;
}

void Boid::update_position()
{
    pos_x_ = pos_x_ + vel_x_;
    pos_y_ = pos_y_ + vel_y_;
    return;
}