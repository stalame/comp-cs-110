#include <iostream>
#include <string>
#include <vector>

using namespace std;

// TODO: Implement split function here
// Do not change main function

// splits a string into a vector either with or without the empty spaces
// param line is the string
// param separator is the character by which the string is separated
// param ignore_spaces holds a bool value that tells us whether to include the separators in the vector or not
vector<string> split(string& line, char& separator, bool ignore_spaces = false){
    // create vector to save separated strings into
    vector<string> parts; // string separated as is, including separators
    vector<string> parts_no_empties; // string separated, not including separators
    string current_part = ""; // variable into which parts of the string can be added

    if (ignore_spaces){ // if separators need to be ignored
        for (size_t i=0; i < line.length(); ++i){
            if (line[i] == separator){ // if s == separator, then ignore it
                // as long as the current_part isn't empty,
                // it can be added into the vector
                if (!current_part.empty()){
                    parts_no_empties.push_back(current_part); // saves the string so far into vector
                    current_part.clear(); // clears string
                }

            }

            else { // if s == normal character, then just add the character into current_part
                current_part += line[i];
            }
        }
        // push latest current_part after last separator into vector
        parts_no_empties.push_back(current_part);
        return parts_no_empties;
    }

    else{
        // for loop to go through each character in string,
        // if char == separator, then the string before that is saved into vector
        for (size_t i=0; i < line.length(); ++i){
            if (line[i] == separator){ // if s == separator, then save it into vector as empty
                parts.push_back(current_part); // saves the string so far into vector
                current_part.clear(); // clears string
            }

            else { // if s == normal character, then just add the character into current_part
                current_part += line[i];
            }
        }
        // push latest current_part after last separator into vector
        parts.push_back(current_part);
        return parts;
    }
}


int main()
{
    string line = "";
    cout << "Enter a string: ";
    getline(cin, line);
    cout << "Enter the separator character: ";
    char separator = getchar();

    vector< string > parts  = split(line, separator);
    cout << "Splitted string including empty parts: " << endl;
    for( auto part : parts ) {
        cout << part << endl;
    }

    vector< string > parts_no_empty  = split(line, separator, true);
    cout << "Splitted string ignoring empty parts: " << endl;
    for( auto part : parts_no_empty ) {
        cout << part << endl;
    }

    return EXIT_SUCCESS;
}
