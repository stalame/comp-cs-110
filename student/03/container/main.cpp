#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

// Prints the elements in the parameter vector ints.
void print_integers(const vector< int >& ints)
{
    for(auto elem : ints) {
        cout << elem << " ";
    }
    cout << endl;
}

// Reads as many integers as the parameter count indicates
// and stores them into the parameter vector ints.
void read_integers(vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i) {
        cin >> new_integer;

        // adds integer into vector ints
        ints.push_back(new_integer);
    }
}

// evaluates the integers in vector<int> and returns a bool value if they are all the same
bool same_values(const vector<int>& ints){
    // if it's a zero vector then this is true.
    if (ints.empty()) return true;

    // for-loop of indexes so that we can compare current and previous values
    // start loop at i=1 to avoid error with i-1
    for (size_t i=1; i < ints.size(); ++i){
        if (ints[i-1] != ints[i]){
            return false;
        }
    }
    return true;
}

// evaluates whether the vectors are ascending
bool is_ordered_non_strict_ascending(vector<int>& ints){

    for (size_t i=1; i < ints.size(); ++i){
        // only checks if it ever decreases
        if (ints[i] < ints[i-1]){
            return false;
        }
    }
    return true;
}

// evaluates a vector of type vector<int> and whether its values form an arithmetic series
// an arithmetic series is defined by its terms being of equal distance to one another
bool is_arithmetic_series(vector<int>& ints){
    int difference = abs(ints[1]-ints[0]);
    for (size_t i=1; i < ints.size(); ++i){
        int current_difference = abs(ints[i]-ints[i-1]);
        if (current_difference != difference){
            return false;
        }
    }
    return true;
}

// evaluates a vector of type vector<int> and whether its values form a geometric series
// a geometric series is defined by the constant ratio of two consecutive terms
bool is_geometric_series(vector<int>& ints){
    if (ints.empty()) return false;

    //check for zero vectors
    bool all_zeros = true;
    for (size_t i : ints){
        if (i != 0){
            all_zeros = false;
            break;
        }
    }

    if (all_zeros) return false; // a zero vector is not considered a geometric series

    int ratio = ints[1]/ints[0];
    for (size_t i=1; i < ints.size(); ++i){
        int current_ratio = ints[i]/ints[i-1];
        if (current_ratio != ratio){
            return false;
        }
    }
    return true;
}

// triples the integers in vector
void triple_integers(vector<int>& ints){
    for (int& i : ints){
        i = i * 3;
    }
}

int main()
{
    cout << "How many integers are there? ";
    int how_many = 0;
    cin >> how_many;

    if(how_many <= 0) {
        return EXIT_FAILURE;
    }

    cout << "Enter the integers: ";
    vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers)) {
        cout << "All the integers are the same" << endl;
    } else {
        cout << "All the integers are not the same" << endl;
    }

    if(is_ordered_non_strict_ascending(integers)) {
        cout << "The integers are in a non-strict ascending order" << endl;
    } else {
        cout << "The integers are not in a non-strict ascending order" << endl;
    }

    if(is_arithmetic_series(integers)) {
        cout << "The integers form an arithmetic series" << endl;
    } else {
        cout << "The integers do not form an arithmetic series" << endl;
    }

    if(is_geometric_series(integers)) {
        cout << "The integers form a geometric series" << endl;
    } else {
        cout << "The integers do not form a geometric series" << endl;
    }

    triple_integers(integers);
    cout << "Tripled values: ";
    print_integers(integers);

    return EXIT_SUCCESS;
}

