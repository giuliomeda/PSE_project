#include "boid.h"
#include "boids_manager.h"
#include <thread>
#include <iostream>
#include <vector>
#include <list>
using std::vector;
using std::thread;
using std::list;

#include<Python.h>


boids_manager manager{"../visualizer/my_coordinates.txt",100};

void handle_robot(int index_of_boid,int no_of_iteratation){
    int number_update{0};
    std::list<boid> neighbors{};

    while (number_update < no_of_iteratation){

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

void writer(int no_of_iteratation){
    int i{0};
    while(i < no_of_iteratation){ 
        manager.write_positions();
        i++;
    }
    return;
}

void launch_visualizer(){
    //launch the visualizer

	Py_Initialize();

	PyObject *obj = Py_BuildValue("s", "../visualizer/Visualizer.py");
    FILE *file = _Py_fopen_obj(obj, "r+");
    if(file != NULL) {
        PyRun_SimpleFile(file, "../visualizer/Visualizer.py");
    }

	Py_Finalize();

    return;
}


int main(){
    //insert the number of iteration that you want to compute
    const int no_of_iteratation{1000};

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
    launch_visualizer();
    
    return 0;    

}