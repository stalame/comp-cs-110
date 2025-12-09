#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

// create struct that stores the word, how many times it appears and which rows it appears in
struct word_specs {
    string word;
    int appearances;
    vector<int> rows;
};

// manually splits string into vector of words in string
// returns vector of words from string
vector<string> row_to_vector(const string& row){
    vector<string> row_words; // this is where each row in input file will be stored
    string temp = row;
    size_t pos = 0;
    while ((pos = temp.find(' ')) != string::npos){
        string word = temp.substr(0, pos);

        if (!word.empty()){
            row_words.push_back(word); // this is just in case there are multiple spaces between words
        }

        temp.erase(0, pos+1); // erases processed part from the row
    }

    // while loop only loops until last space, so we still need to process the last word
    if (!temp.empty()){
        row_words.push_back(temp);
    }
    return row_words;
}


int main()
{
    string filename = "";
    cout << "Input file: ";
    getline(cin, filename);

    ifstream file(filename);
    if (not file){
        cout << "Error! The file " << filename << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    map<int, vector<string>> rows; // in is the line number, vector is the string for said line.
    string row = "";
    int line_num = 1;

    while (getline(file, row)){ // first we create a loop over the lines
        vector<string> row_words =  row_to_vector(row);

        rows[line_num] = row_words;
        row_words.clear();
        line_num++;
    }

    map<string, word_specs> word_info; // now we can look up a word easily and update its count and line numbers

    for (const auto& [line_num, row] : rows) {
        set<string> counted_in_row;  // track words already counted in this line

        for (const string& word : row) {
            if (word_info.find(word) == word_info.end()) {
                word_info[word] = word_specs{word, 0, {}};
            }

            // count the word only once per line
            if (counted_in_row.find(word) == counted_in_row.end()) {
                word_info[word].appearances += 1;
                counted_in_row.insert(word);
            }

            // add line number if not already present
            if (find(word_info[word].rows.begin(), word_info[word].rows.end(), line_num) == word_info[word].rows.end()) {
                word_info[word].rows.push_back(line_num);
            }
        }
    }

    for (const auto& [word, info] : word_info){
        cout << info.word << " " << info.appearances << ": ";
        for (size_t i = 0; i < info.rows.size(); ++i ){
            cout << info.rows[i];
            if (i != info.rows.size()-1){
                cout << ", ";
            }
        }
        cout << "\n";
    }


    return EXIT_SUCCESS;
}
