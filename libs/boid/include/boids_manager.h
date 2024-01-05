#ifndef boids_manager_H
#define boids_manager_H

#include<condition_variable>
#include<mutex>
#include<string>
#include "boid.h"



class boids_manager
{
private:
    std::vector<boid> my_storm_;
    std::vector<bool> no_of_new_positions_to_write_;
    std::string filename_;
    std::mutex mutex_;
    std::condition_variable OkToWrite;
    std::condition_variable new_update;

public:
    boids_manager(const std::string& filename);
    boids_manager(const std::string& filename, size_t storm_size);
    void write_positions();
    void reynolds_algorithm(std::list<boid>& neighbors, int index_of_boid);
    void initialize_storm(size_t storm_size);
    int get_storm_size() const {return my_storm_.size();}
private:
    void initialize_output_file(const std::string& filename);
    void update_list_of_neighbors(std::list<boid>& neighbors, int index_of_boid);
    void check_for_new_neighbors(std::list<boid>& neighbors, int index_of_boid);
    
};


#endif