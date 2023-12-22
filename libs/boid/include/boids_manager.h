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
    boids_manager(std::string filename, size_t storm_size);
    void write_positions();
    void update_list_of_neighbors(std::list<boid>& neighbors, int index_of_boid);
    void check_for_new_neighbors(std::list<boid>& neighbors, int index_of_boid);
    void reynolds_algorithm(const std::list<boid>& neighbors, int index_of_boid);
    int get_storm_size() const {return my_storm_.size();}
};


#endif