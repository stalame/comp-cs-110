#include "utilities.hh"

#include <algorithm>
#include <cctype>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <memory>

using namespace std;

namespace Utilities {

vector<string> split(const string& str, char delim, bool keep_empty)
{
    vector<string> result = {""};
    bool insideQuotation = false;
    for ( char currentChar : str )
    {
        if ( currentChar == '"' )
        {
            insideQuotation = !insideQuotation;
        }
        else if ( currentChar == delim && !insideQuotation)
        {
            if (keep_empty || result.back() != "") {
                result.push_back("");
            }
        }
        else
        {
            result.back().push_back(currentChar);
        }
    }
    if (!keep_empty && result.back() == "") {
        result.pop_back();
    }
    return result;
}

bool is_int(string str, bool allow_negative)
{
    if (str.empty()) {
        return false;
    }

    // Negative number check
    if (str.at(0) == '-') {
        if (allow_negative) {
            str = str.substr(1);
        } else {
            return false;
        }
    }

    // All characters (except first, if negatives are allowed) need to be digits
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }

    return true;
}

void print_song(const shared_ptr<Song>& s){
    cout << s->artist << " - " << s->title << " (" << format_duration(s->duration) << ")" << endl;
}

string format_duration(int total_seconds){
    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;

    ostringstream oss;
    oss << minutes << ":" << setw(2) << setfill('0') << seconds;

    return oss.str();
}

bool compare_songs(const shared_ptr<Song>& a, const shared_ptr<Song>& b){
    if (a->artist != b->artist){
        return a->artist < b->artist;
    }
    return a->title < b->title;
}
}
