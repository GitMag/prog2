#include "queue.hh"
#include <iostream>

// Implement the member functions of Queue here

Queue::Queue(unsigned int cycle): cycle_(cycle){

}

Queue::~Queue() {

}

string Queue::get_light_color() const{

    if (is_green_) {
        return "GREEN";
    } else {
        return "RED";
    }
}

// prints all the vehicles and queue and also traffic light color
void Queue::print() const {

    Vehicle* vehicle_to_print = first_;

    // traffic light status
    if (first_ == nullptr) {
        cout << get_light_color() << ": No vehicles waiting in traffic lights" << endl;
        return;
    }
    // some vehciles waiting
    cout << get_light_color() << ": Vehicle(s) ";

    string passed_cars_string = "";
    while (vehicle_to_print != nullptr) {
        passed_cars_string += vehicle_to_print->reg_num + " ";
        vehicle_to_print = vehicle_to_print->next;
    }
    cout << passed_cars_string + "waiting in traffic lights" << endl;
}
// sets new cycle
void Queue::reset_cycle(unsigned int new_cycle) {
    cycle_ = new_cycle;
}

void Queue::change_light() {
    if (is_green_) {
        is_green_ = false;
    } else {
        is_green_ = true;
    }
}

// switches light and lets vehicles pass
void Queue::switch_light() {
    // also needs to let cycle amount of vehicles pass from queue
    if (first_ == nullptr) {

        change_light();
        cout << get_light_color() << ": No vehicles waiting in traffic lights" << endl;
        return;
    }

    // some cars in traffic lights
    if (is_green_) {
        // set to red
        is_green_ = false;
    } else {
        is_green_ = true;
        // set to green
        //pass certain amount of vehicles trough traffic lights


        Vehicle* vehicle_to_pass = first_;

        unsigned int passed_cars = 0;
        string passed_cars_string = "";
        while (vehicle_to_pass != nullptr and passed_cars != cycle_) {

            // remove first vehicle from queue

            passed_cars_string += vehicle_to_pass->reg_num + " ";
            vehicle_to_pass = vehicle_to_pass->next;
            is_green_ = false;
            passed_cars++;
            dequeue();

        }

        // print passed cars:
        cout << "GREEN: Vehicle(s) " << passed_cars_string << "can go on" << endl;



    }
}

// lets first car go and updates passed_cars var
void Queue::dequeue() {
    // remove first car from queue
    Vehicle* vehicle_to_be_removed = first_;


    if ( first_ == last_ ) {
       first_ = nullptr;
       last_ = nullptr;
    } else {
       first_ = first_->next;
    }

    delete vehicle_to_be_removed;
}

// If the color of traffic light is red, inserts a vehicle, the register
// number of which is reg, to the queue.
void Queue::enqueue(string const& reg) {

    if (not is_green_) {
        // insert vehicle to queue (first vehicle is in back of queue
        Vehicle* new_vehicle = new Vehicle{reg, nullptr};

        if (first_ == nullptr ) {
            first_ = new_vehicle;
            last_ = new_vehicle;
        } else {
            last_->next = new_vehicle;
            last_ = new_vehicle;
        }

    } else {
        // is green, vehicle does not need to wait
        cout << "GREEN: The vehicle " << reg << " need not stop to wait" << endl;
    }
}
