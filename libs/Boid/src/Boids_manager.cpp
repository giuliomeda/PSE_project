#include "Boids_manager.h"
#include<algorithm>
#include<filesystem>
#include<fstream>

Boids_manager::Boids_manager(const std::string& filename)
    :filename_{filename}, my_storm_{}
{
    initialize_output_file(filename_);
    return;
}

Boids_manager::Boids_manager(const std::string& filename, size_t storm_size)
    :filename_{filename}, my_storm_{}
{
    //initialize the storm 
    initialize_storm(storm_size);
    //initialize output file
    initialize_output_file(filename);

    return;
}

void Boids_manager::initialize_output_file(const std::string & filename)
{
    std::ofstream myfile;
    if(!std::filesystem::exists(filename)){
        myfile.open(filename, std::ios::app);

        if(myfile.is_open()){
                myfile << Boid::left_margin_ << " " << Boid::right_margin_ << " " << Boid::bottom_margin_ << " " << Boid::top_margin_ << "\n";
                myfile.close();
            }
            else{
                std::cerr << "Unable to open the file, launch the program from the directory build and type './app/eseguibile' \n";
                exit(EXIT_FAILURE);
            }
    }

    //if the file already exist, clear it
    else{
        myfile.open(filename, std::ios::trunc);

        if(myfile.is_open()){
                myfile << Boid::left_margin_ << " " << Boid::right_margin_ << " " << Boid::bottom_margin_ << " " << Boid::top_margin_ << "\n";
                myfile.close();
            }
            else{
                std::cerr << "Unable to open the file, launch the program from the directory build and type './app/eseguibile' \n";
                exit(EXIT_FAILURE);
            }
    }

    return;

}

void Boids_manager::initialize_storm(size_t storm_size)
{
    if (storm_size == 0 ){
        std::cerr << "Invalid storm size...\n\n";
        exit(EXIT_FAILURE);
    }

    for(size_t i{0}; i < storm_size; i++){
        //populate the storm with random boid
        Boid new_boid{};
        my_storm_.push_back(new_boid);
        no_of_new_positions_to_write_.push_back(false);
    }

    return;
}

void Boids_manager::write_positions()
{
    std::unique_lock<std::mutex> mlock(mutex_);
    std::ofstream my_file;

    while (!std::all_of(no_of_new_positions_to_write_.begin(), no_of_new_positions_to_write_.end(), [](int a)
                        { return a; }))
        OkToWrite.wait(mlock);

    //update positions using updated speeds
    for (auto& el:my_storm_){
        el.update_position();
    }

    my_file.open(filename_, std::ios::app); // open the file in appending mode
    if (my_file.is_open())
    {
        for (const auto &el : my_storm_)
        {
            my_file << el.get_pos_x_() << " " << el.get_pos_y_() << " ";
        }
        my_file << "\n";
        my_file.close();

        for (auto el {no_of_new_positions_to_write_.begin()}; el != no_of_new_positions_to_write_.end(); el ++){
            (*el) = false;
        }
    }
    else{
        std::cerr << "Error occurred while opening the output file\n";
        exit(EXIT_FAILURE);
    }

    mlock.unlock();
    new_update.notify_all();
  

    return;
}

void Boids_manager::update_list_of_neighbors(std::vector<Boid>& neighbors, int index_of_boid)
{
    for (auto it{neighbors.begin()}; it != neighbors.end(); it++)
    {
        if (my_storm_.at(index_of_boid).distance_from_other_boid(*it) > Boid::d_ca_)
            it = neighbors.erase(it);
    }
    return;
}

void Boids_manager::check_for_new_neighbors(std::vector<Boid>& neighbors, int index_of_boid)
{
    neighbors.clear();
    for (const auto &el : my_storm_)
    {
        if ((my_storm_.at(index_of_boid).distance_from_other_boid(el) <= Boid::d_ca_) && (my_storm_.at(index_of_boid).get_boid_id_() != el.get_boid_id_()) )
            neighbors.push_back(el);
    }
    return;
}

void Boids_manager::reynolds_algorithm(std::vector<Boid>& neighbors, int index_of_boid)
{

    std::unique_lock<std::mutex> mlock(mutex_);
    while (no_of_new_positions_to_write_.at(index_of_boid))
        new_update.wait(mlock);
        
    //check for new neighbors       
    check_for_new_neighbors(neighbors,index_of_boid);
    my_storm_.at(index_of_boid).update_speed(neighbors);

    no_of_new_positions_to_write_.at(index_of_boid) = true;

    if (std::all_of(no_of_new_positions_to_write_.begin(), no_of_new_positions_to_write_.end(), [](int a){return a>0;})){
        OkToWrite.notify_all();
    }
    mlock.unlock();
        

    return;
}