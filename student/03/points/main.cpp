#include <iostream>
#include <string>
#include <map>
#include <fstream>

using namespace std;

int main() {
    string filename;
    cout << "Input file: ";
    getline(cin, filename);

    ifstream file(filename);
    if (!file) {
        cout << "Error! The file " << filename << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    map<string, double> totals;
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue; // skip empty lines

        size_t colonPos = line.find(':');
        if (colonPos == string::npos) continue; // skip lines without a colon

        string name = line.substr(0, colonPos);
        string scoreStr = line.substr(colonPos + 1);

        try {
            int score = stoi(scoreStr); // convert string to int
            totals[name] += score;
        } catch (const invalid_argument&) {
            continue; // skip lines with non-numeric scores
        }
    }

    cout << "Final scores:" << endl;
    for (const auto& [person, total] : totals) {
        cout << person << ": " << total << endl;
    }

    return EXIT_SUCCESS;
}

