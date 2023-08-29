#include "player.hh"
#include<iostream>


Player::Player(std::string name):
        name_(name){

}

std::string Player::get_name() const {
    return name_;
}

int Player::get_points() const {
    return points_;
}

void Player::add_points(int points) {
    // get sum of points
    int sum = get_points() + points;
    // check if points are
    if (sum > 50) {
        // too many points, set them to 25
        std::cout << get_name() << " gets penalty points!" << std::endl;
        points_ = 25;
    } else {
        // add points normally
        points_ = sum;
    }
}

bool Player::has_won() {
    if (points_ == 50) {
        return true;
    }
    return false;
}


