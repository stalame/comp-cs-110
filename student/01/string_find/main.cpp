#include <iostream>
#include <string>
#include <list>

using namespace std;

int main()
{
    string long_str = " ";
    string short_str = " ";

    // Input long_str
    cout << "Enter a (longer) string: ";
    getline(cin, long_str);

    // Input short_str
    cout << "Enter a (shorter) string to be found: ";
    getline(cin, short_str);

    // define values into which index where short_str
    // is found in long_str
    string::size_type index_found = 0;

    // index of first occurrrence of short_str in long_str
    index_found = long_str.find(short_str);

    // flag variable for keeping track of when to print comma
    bool first_find = true;

    // output for when short_str is not in long_str
    if (index_found == string::npos){
        cout << "Not found" << endl;
    }

    else {
        cout << "Found at " ;
        while (index_found != string::npos){ // Now to find more occurrences of short_str
            if (!first_find) { // doesn't print comma before first index
                cout << ", ";
            }
                cout << index_found;
                first_find = false; // first find has been printed correctly
                        // rest of the indexes have to have a comma before them
                index_found = long_str.find(short_str, ++index_found); // continues search for short_str farther in long_str

        }
    }
    return EXIT_SUCCESS;
}
