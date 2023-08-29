#ifndef PLAYER_HH
#define PLAYER_HH

#include <iostream>

class Player
{
public:
    Player(std::string name);

    // constructor
    std::string get_name() const;
    int get_points() const;
    void add_points(int points);
    bool has_won();

private:

    // int values
    std::string name_;
    int points_ = 0;
    bool is_winner_ = false;

};

#endif // PLAYER_HH
