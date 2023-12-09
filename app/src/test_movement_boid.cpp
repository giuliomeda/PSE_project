#include "boid.h"
#include <thread>
#include <iostream>
using std::thread;


boid my_robot{};


void handle_robot(){
    int number_update{0};

    while (number_update < 1000){
        my_robot.update_positon();
        std::cout << "Pos: " << my_robot.get_pos_x_() << ", " << my_robot.get_pos_y_() << "\n";
        std::cout << "Vel: " << my_robot.get_vel_x_() << ", " << my_robot.get_vel_y_() << "\n";
        number_update ++;
    }
    return;
}

int main(){ 
    std::cout << "Dimensioni dello schermo: " << boid::get_screen_width() << ", " << boid::get_screen_height() << "\n";
    std::cout << "Posiziione iniziale robot: " << my_robot.get_pos_x_() << ", " << my_robot.get_pos_y_() << "\n";
    std::cout << "Velocità iniziale robot: " << my_robot.get_vel_x_() << ", " << my_robot.get_vel_y_() << "\n";

    thread robot_manager{handle_robot};

    robot_manager.join();

    return 0;    

}