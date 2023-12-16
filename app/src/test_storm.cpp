#include "boid.h"
#include <thread>
#include <iostream>
#include <vector>
#include <list>
using std::vector;
using std::thread;
using std::list;



vector<boid> my_storm;


void handle_robot(int index_of_boid){
    int number_update{0};
    std::list<boid> neighbors;

    while (number_update < 1000){

        for ( auto it {neighbors.begin()}; it != neighbors.end(); it++){
            if (!my_storm.at(index_of_boid).distance_from_other_boid(*it) > boid::d_ca_)
                it = neighbors.erase(it);
        }

        for (const auto& el:my_storm){
            if (my_storm.at(index_of_boid).distance_from_other_boid(el) <= boid::d_ca_)
                neighbors.push_back(el);
        }

        my_storm.at(index_of_boid).update_positon(neighbors);
       
        number_update ++;
    }
    return;
}


int main(){

    const int storm_size {50};

    for(int i{0}; i < storm_size; i++){
        //populate the storm with random boid
        boid new_boid{};
        my_storm.push_back(new_boid);
    }

    vector<thread> robots_manager;
    for (int i{0}; i < storm_size; i++){

        robots_manager.push_back(thread{handle_robot,i});

    }

    for (auto el{robots_manager.begin()}; el != robots_manager.end(); el++){
        el->join();
    }


    return 0;    

}