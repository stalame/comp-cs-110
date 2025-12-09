#ifndef PLAYER_HH
#define PLAYER_HH

#include <string>

using namespace std;

class Player
{
public:
    Player(const string& name);
    string get_name();
    int get_points();
    void add_points(int points);
    bool has_won();

private:
    int points_ = 0;
    string name_;

};

#endif // PLAYER_HH
