#include "boid.h"
#include "boids_manager.h"
#include <thread>
#include <iostream>
#include <vector>
#include <list>
using std::vector;
using std::thread;
using std::list;


boids_manager manager{"../visualizer/my_coordinates.txt",10};

void handle_robot(int index_of_boid){
    int number_update{0};
    std::list<boid> neighbors{};

    while (number_update < 1000){

        //update list of neighbors, only if there're neighbors
        /*if(!neighbors.empty())
            manager.update_list_of_neighbors(neighbors,index_of_boid);*/
        
        //check for new neighbors 
        manager.check_for_new_neighbors(neighbors,index_of_boid);        

        //apply the algorithm to the boid
        manager.reynolds_algorithm(neighbors,index_of_boid);

        //manager.print_position(index_of_boid);

        number_update ++;
    }

    return;
}

void writer(){
    int i{0};
    while(i < 1000){ 
        manager.write_positions();
        i++;
    }
    return;
}


int main(){

    
    vector<thread> threads;
    for (size_t i{0}; i < manager.get_storm_size(); i++){

        threads.push_back(thread{handle_robot,static_cast<int>(i)});

    }
    
    thread file_writer{writer};

    for (auto el{threads.begin()}; el != threads.end(); el++){
        el->join();
    }

    file_writer.join();

    return 0;    

}