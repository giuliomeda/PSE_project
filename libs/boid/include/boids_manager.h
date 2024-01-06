#ifndef boids_manager_H
#define boids_manager_H

#include<condition_variable>
#include<mutex>
#include<string>
#include<atomic>
#include "boid.h"



class boids_manager
{
private:
    std::vector<boid> my_storm_;
    std::vector<int> no_of_new_positions_to_write;
    bool activeWriter{false};
    std::string filename_;
    static const int max_num_of_loss_positions{3};
    std::mutex mutex_;
    std::condition_variable OkToWrite;
    std::condition_variable noActiveWriter;

public:
    boids_manager(const std::string& filename);
    boids_manager(const std::string& filename, size_t storm_size);
    void write_positions();
    void reynolds_algorithm(std::vector<boid>& neighbors, int index_of_boid);
    int get_storm_size() const {return my_storm_.size();}
    void initialize_storm(size_t storm_size);
private:
    void initialize_output_file(const std::string& filename);
    void update_list_of_neighbors(std::vector<boid>& neighbors, int index_of_boid);
    void check_for_new_neighbors(std::vector<boid>& neighbors, int index_of_boid);
    
};


#endif