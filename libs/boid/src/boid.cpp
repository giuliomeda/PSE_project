#include "boid.h"

//initialize the static members
const int boid::left_margin_ {0};
const int boid::right_margin_{1920};
const int boid::top_margin_{1080};
const int boid::bottom_margin_{0};
const float boid::v_min_{10};
const float boid::v_max_{100};
const float boid::d_sep_{50};
const float boid::d_ca_{500};
const float boid::turn_factor_{10};
const float boid::avoid_factor{5};
const float boid::centering_factor{0.1};
const float boid::align_factor{1};
size_t boid::num_of_instantiated_boid{0};


boid::boid(float pos_x, float pos_y, float vel_x, float vel_y)
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

boid::boid()
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

void boid::initialize_at_random_positon()
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<> distribution_1(0, right_margin_);
    std::uniform_real_distribution<> distribution_2(0, top_margin_);

    pos_x_ = distribution_1(generator);
    pos_y_ = distribution_2(generator);

    return;
}

void boid::initialize_at_random_speed()
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution distribution(-(v_max_ / std::sqrt(2)), (v_max_ / std::sqrt(2)));

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

float boid::distance_from_other_boid(const boid& other_boid)
{
    double distance_in_x {std::pow((pos_x_ - other_boid.get_pos_x_()),2)};
    double distance_in_y {std::pow((pos_y_ - other_boid.get_pos_y_()),2)};
    double distance = std::sqrt(distance_in_x + distance_in_y);

    return static_cast<float> (distance);

}

void boid::separation(const std::list<boid>& neighbors)
{
    if(neighbors.empty()) //if there are no neighbors, return..
        return;

    float close_dx{0};
    float close_dy{0};

    for (const boid &el : neighbors)
    {
        if (distance_from_other_boid(el) < boid::d_sep_)
        {
            close_dx += pos_x_ - el.get_pos_x_();
            close_dy += pos_y_ - el.get_pos_y_();
        }
    }

    //update speed for separation
    vel_x_ += close_dx * boid::avoid_factor;
    vel_y_ += close_dy * boid::avoid_factor;

    return;
}

void boid::alignement(const std::list<boid>& neighbors)
{
    if(neighbors.empty()) //if there are not neighbors, return..
        return;
    
    float x_vel_avg{0};
    float y_vel_avg{0};
    int neighboring_boids{static_cast<int>(neighbors.size())};

    

    for(const boid& el:neighbors){
        x_vel_avg += el.get_vel_x_();
        y_vel_avg += el.get_vel_y_();
    }
    if(neighboring_boids > 0){
        x_vel_avg = x_vel_avg / neighboring_boids;
        y_vel_avg = y_vel_avg / neighboring_boids;
    }
    else return;

    //update speed
    vel_x_ += (x_vel_avg - vel_x_) * boid::align_factor;
    vel_y_ += (y_vel_avg - vel_y_) * boid::align_factor;

    return;
}

void boid::cohesion(const std::list<boid>& neighbors)
{
    if(neighbors.empty()) //if there are not neighbors, return..
        return;
    
    float x_pos_avg{0};
    float y_pos_avg{0};
    int neighboring_boids{static_cast<int>(neighbors.size())};

    
    
    for(const boid& el:neighbors){
        x_pos_avg += el.get_pos_x_();
        y_pos_avg += el.get_pos_y_();
    }
    if(neighboring_boids > 0){
        x_pos_avg = x_pos_avg / neighboring_boids;
        y_pos_avg = y_pos_avg / neighboring_boids;
    }
    else return;

    //update speed
    vel_x_ += (x_pos_avg - pos_x_) * boid::centering_factor;
    vel_y_ += (y_pos_avg - pos_y_) * boid::centering_factor;

}

void boid::speed_limits()
{
    double speed {std::sqrt(vel_x_ * vel_x_ + vel_y_ * vel_y_)};

    if (speed > boid::v_max_){
        vel_x_ = (vel_x_ / speed) * boid::v_max_;
        vel_y_ = (vel_y_ / speed) * boid::v_max_;
    }

    if (speed < boid::v_min_){
        vel_x_ = (vel_x_ / speed) * boid::v_min_;
        vel_y_ = (vel_y_ / speed) * boid::v_min_;
    }

    return;

}

void boid::update_speed(const std::list<boid>& neighbors)
{
    separation(neighbors);
    alignement(neighbors);
    cohesion(neighbors);
    speed_limits();
    check_screen_margins();

    return;
}

void boid::update_position()
{
    pos_x_ = pos_x_ + vel_x_;
    pos_y_ = pos_y_ + vel_y_;
    return;
}