#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <map>

using namespace std;

const string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


vector<string> split(const string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    vector<string> result;
    string tmp = s;

    while(tmp.find(delimiter) != string::npos)
    {
        string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

struct profile{
string name;
vector<string> network;
};

map<string, profile> people;

void store(const string& id1, const string& id2){
    if (people.find(id1) == people.end()){
        people[id1] = profile{id1, {id2}};
    } else {
        profile& p = people[id1];
        if (find(p.network.begin(), p.network.end(), id2) == p.network.end()) {
            p.network.push_back(id2);
        }
    }

    // ensure id2 exists
    if (people.find(id2) == people.end()){
        people[id2] = profile{id2, {}};
    }
}


// depth counts the deepest network for person id1
int depth(const string& id1){

    // check if profile exists
    if (people.find(id1) == people.end()) return 0;

    profile& p = people[id1];
    int max_depth = 1; // store current deepest network here, 1st layer is top layer

    for (const string& friend_id : p.network){
        int d = depth(friend_id) + 1;
        if (d > max_depth){
            max_depth = d;
        }
    }
    return max_depth;
}

void print_helper(const string& id, int layer){
    if (people.find(id) == people.end()){
        return;
    }

    // how many dots to print before name
    for (int i=0; i < layer; ++i){
        cout << "." ;
    }
    cout << id << endl;

    // for
    for (const string& friend_id : people[id].network){
        print_helper(friend_id, layer + 2);
}
}

void print(const string& id1){
    if (people.find(id1) == people.end()) {
            return;
        }
    print_helper(id1, 0); // first layer has no dots
}


// calculates the size of the network
int count(const string& id1){
    if (people.find(id1) == people.end()) return 0;

    int total = people[id1].network.size();

    for (const string& friend_id : people[id1].network){
        total += count(friend_id);
    }

    return total;
}

int main()
{
     set<string> valid_commands = {"S", "s", "P", "p", "C", "c",
                                             "D", "d", "Q", "q"};

    while(true)
    {
        string line;
        cout << "> ";
        getline(cin, line);
        vector<string> parts = split(line, ' ', true);

        // Allowing empty inputs
        if(parts.size() == 0)
        {
            continue;
        }

        string command = parts.at(0);

        if(command == "Q" or command == "q")
        {
           return EXIT_SUCCESS;
        }
        else if(command == "S" or command == "s")
        {
            if(parts.size() != 3)
            {
                cout << "Erroneous parameters!" << endl << HELP_TEXT;
                continue;
            }
            string id1 = parts.at(1);
            string id2 = parts.at(2);

            store(id1, id2);

        }
        // Other valid commands are not reasonable for an empty datastructure
        else if(valid_commands.find(command) != valid_commands.end()
                and people.empty())
        {
            continue;
        }
        else if(command == "P" or command == "p")
        {
            if(parts.size() != 2)
            {
                cout << "Erroneous parameters!" << endl << HELP_TEXT;
                continue;
            }
            string id = parts.at(1);

            print(id);

        }
        else if(command == "C" or command == "c")
        {
            if(parts.size() != 2)
            {
                cout << "Erroneous parameters!" << endl << HELP_TEXT;
                continue;
            }
            string id = parts.at(1);

            cout << count(id) << endl;

        }
        else if(command == "D" or command == "d")
        {
            if(parts.size() != 2)
            {
                cout << "Erroneous parameters!" << endl << HELP_TEXT;
                continue;
            }
            string id = parts.at(1);
            cout << depth(id) << endl;

        }
        else
        {
            cout << "Erroneous command!" << endl << HELP_TEXT;
        }
    }
}
