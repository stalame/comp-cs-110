#include "player.hh"
#include <string>
#include <iostream>


Player::Player(const string& name):
 name_(name){
}

bool Player::has_won(){
    if (points_ == 50){
        return true;
    }
    return false;
}

void Player::add_points(int points){
    points_ += points;

    if (points_ > 50){
        cout << name_ << " gets penalty points!" << endl;
        points_ = 25;
        return;
    }
}

string Player::get_name(){
    return name_;
}

int Player::get_points(){
    return points_;
}
