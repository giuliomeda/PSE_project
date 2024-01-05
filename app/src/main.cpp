#include "boid.h"
#include "boids_manager.h"
#include <thread>
#include <iostream>
#include <vector>
#include <list>
#include <atomic>
#include <algorithm>
#include<stdlib.h>
using std::vector;
using std::thread;
using std::list;



boids_manager manager{"../visualizer/my_coordinates.txt"};

void handle_robot(int index_of_boid,int no_of_iteratation){
    int number_update{0};
    std::list<boid> neighbors{};

    while (number_update < no_of_iteratation){

        //apply the algorithm to the boid
        manager.reynolds_algorithm(neighbors,index_of_boid);

        number_update ++;
    }

    return;
}

void writer(int no_of_iteratation){
    int i{0};
    while(i < no_of_iteratation ){ 
        manager.write_positions();
        i++;
    }
    return;
}



int main(){
    //insert the number of iteration that you want to compute
    int no_of_iteratation;
    int no_of_boids;

    std::cout << "Insert the number of boids you want to instantiate: ";
    std::cin >> no_of_boids;
    if(no_of_boids <= 0 ){
        std::cerr << "Num of bois must be > 0\n";
        std::cerr << "exit...\n";
        exit(EXIT_FAILURE);
    }


    std::cout << "\nInsert the number of iterations that you want to compute: ";
    std::cin >> no_of_iteratation;
    if(no_of_iteratation <= 0){
        std::cerr << "Number of iterations must be > 0\n";
        std::cerr << "exit...\n";
        exit(EXIT_FAILURE);
    }
    if(no_of_iteratation < 200){
        std::cout << "\nFor a better graphic result number of iterations should be > 200 \n";
    }
    

    manager.initialize_storm(static_cast<size_t>(no_of_boids));

    vector<thread> threads;
    for (size_t i{0}; i < manager.get_storm_size(); i++){

        threads.push_back(thread{handle_robot,static_cast<int>(i), no_of_iteratation});

    }
    
    thread file_writer{writer,no_of_iteratation};

    for (auto el{threads.begin()}; el != threads.end(); el++){
        el->join();
    }

    file_writer.join();

    //launch Visualizer.py
    system("python3 ../visualizer/Visualizer.py");

    return 0;    

}