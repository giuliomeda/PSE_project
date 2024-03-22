#include "Boid.h"
#include "Boids_manager.h"
#include <thread>
#include <iostream>
#include <vector>
#include <atomic>
#include <algorithm>
#include<stdlib.h>
using std::vector;
using std::thread;



Boids_manager manager{"../visualizer/my_coordinates.txt"};

//class for the writer thread 
class writer_thread
{
public:
    void operator()(int no_of_iteration){
        while(!haveToStop){
            manager.write_positions(this->haveToStop, no_of_iteration);
        }
    }
private:
    bool haveToStop{false};
};


//class for the robot threads 
class robot_thread
{
private:
    std::vector<Boid> neighbors{};

public:    
    void operator()(int index_of_boid, int no_of_iteration){
        for (int number_update{0}; number_update < no_of_iteration; number_update++){
            //apply the algorithm to the boid
            manager.reynolds_algorithm(neighbors,index_of_boid);
        }
    }
};



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


    std::cout << "\nInsert the number of iterations you want to compute: ";
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

        threads.push_back(thread{robot_thread(),static_cast<int>(i), no_of_iteratation});

    }
    
    thread writer{writer_thread(),no_of_iteratation};

    for (auto el{threads.begin()}; el != threads.end(); el++){
        el->join();
    }

    writer.join();

    //launch Visualizer.py
    system("python3 ../visualizer/Visualizer.py");

    return 0;    

}