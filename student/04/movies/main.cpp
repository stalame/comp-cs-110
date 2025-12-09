/* COMP.CS.110 Project 1: Movies
 * 
 * Description: This program reads a file containing movies and their respective director and actors.
 * All rows in the file must be of the following form: movie name; year;director;main actor 1|main actor 2.
 * The program checks that each row is structured correctly.
 * 
 * The commands the user can input are the following:
 * Commands:
 * help: Print this command guide.
 * quit: Quit the application.
 * read <file_name>: Read in movie data from a file.
 * movies: List all movies.
 * -> from <year>: List all movies released in the given year.
 * -> by <first_name> <last_name>: List all movies directed by the given director.
 * actors: List all actors.
 * -> prolific <n>: List the top <n> actors that have acted in the most movies.
 * 
 * Created by Amelia Stalter
 * Student ID: 151193060
 * Username: gmamst
 * E-Mail: amelia.stalter@tuni.fi
 * 
 * Comments and/or notes about the program and its implementation:
 * ChatGPT(3.5) has been used in the implementation of this program to aid in best structures to pick,
 * ensure good code, and help with sorting in print functions.
 * */
#include <iostream>
#include <cctype>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

struct Movie{
    string name;
    int year;
    string director;
    vector<string> actors;
};

void help(){
    cout << "Commands: \n"
         << "  help: Print this command guide.\n"
         << "  quit: Quit the application.\n"
         << "  read <file_name>: Read in movie data from a file.\n"
         << "  movies: List all movies.\n"
         << "  * from <year>: List all movies released in the given year.\n"
         << "  * by <first_name> <last_name>: List all movies directed by the given director.\n"
         << "  actors: List all actors.\n"
         << "  * prolific <n>: List the top <n> actors that have acted in the most movies." << endl;
    cout << "\n";
}

// splits string into vector
// params:
// string s is string that is split, 
// char separator is according to which string is separated.
// bool ignore_spaces determines whether we include empty spaces or not
// returns: vector<int> of row
vector<string> split(const string& s, const char& separator, bool ignore_spaces = false){
    string temp = "";
    vector<string> parts;

    if (ignore_spaces){ // this is here because if there are empty spaces, then isRowValid() returns false
        for (size_t i=0; i < s.length(); ++i){
            if (s[i] == separator){

                if (!temp.empty()){
                    parts.push_back(temp);
                    temp.clear(); // clear temporary string storage before next loop
                }
            }
            else{
                temp += s[i];
            }
        }
        parts.push_back(temp); // include last string after last separator
        return parts;
    }

    else{ // in most cases we assume there are no empty spaces so we don't need to check for them

    for (size_t i = 0; i < s.length(); ++i){
        if (s[i] == separator){
            parts.push_back(temp);
            temp.clear();
        }

        else{
            temp += s[i];
        }
    }
    parts.push_back(temp);
    return parts;
    }
}

// creates a struct Movie for data from row of input file
// params:
// string title of the movie
// int year movie was published
// string director name ("Lastname,Firstname")
// vector of names of actors (also "Lastname,Firstname")
// returns Movie with input params
Movie createMovie(const string& title, const int& year, const string& director,
                 const vector<string>& actors){

    Movie m;
    m.name = title;
    m.year = year;
    m.director = director;
    m.actors = actors;
    return m;
}

bool isNumber(const string& s);

void addOrUpdateMovies(map<pair<string, int>, Movie>& movies, const Movie& m){
    auto key = make_pair(m.name, m.year);
    movies[key] = m; // inserts or updates movie
}

// Checks if row in file if of form movie name; year;director;main actor 1|main actor 2.
// params: line_vector is the row in question (see function readFile()) split into a vector using
// split function
// returns: bool value true if row is ok, false if not.
bool isRowValid(const vector<string>& line_vector){
    for (size_t i = 0; i < line_vector.size(); ++i ){
        if (line_vector.at(i).empty()){
            return false;
        }

        if (i == 1 and !isNumber(line_vector.at(i))){ // second term in vector (year) must be an integer
            return false;
        }
    }
    return true;
}

// Function attemps to open file, if successful the contents of file are saved into map structure
// if unsuccessful, prints error message and returns to main
// returns map of file contents which is map movies in main
map<pair<string, int>, Movie> readFile(const string& filename){
    ifstream file(filename);
    if (!file){
        cout << "Error: file cannot be opened." << endl;
        return {};
    }

    map<pair<string, int>, Movie> movies;
    string line;
    int line_num = 1;

    while(getline(file, line)){
        vector<string> current_line = split(line, ';');
        // term 0 = movie title
        // term 1 = year
        // term 2 = director
        // term 3 = actors

        if (!isRowValid(current_line)){
            cout << "Error: row " << line_num << " is erroneous." << endl;
            line_num++;
            continue;
        }

        string movie_title = current_line.at(0);
        int year = stoi(current_line.at(1)); // convert to int for storage

        // remove commas and separate first&last names to make printing names easier
        string director = current_line.at(2);

        vector<string> actors = split(current_line.at(3), '|', true); // let's separate actors into a vector as well

        Movie m = createMovie(movie_title, year, director, actors);
        addOrUpdateMovies(movies, m);
        line_num++;
    }
    file.close();
    return movies;
}

// function handles the printing of movies depending on the command line
// params:
// movies is the map containing all valid lines read in input file
// year is an int parameter for command "movies from <year>"
// director_name is a vector from split command "movies by <director>"
void printMovies(map<pair<string, int>, Movie>& movies,const int& year = 0, const vector<string>& director_name = {} ){

    if (movies.empty()){
        cout << "No movies." << endl;
        cout << endl;
        return;
    }

    if (year != 0 and director_name.empty()){ // we want to list movies by year
        vector<string> movies_in_year;
        for (const auto& [key, movie] : movies){
            if (key.second == year){
                vector<string> director_split = split(movie.director, ',');
                movies_in_year.push_back(movie.name);
                cout << "  " << key.first << " (dir. " << director_split[1] << " " << director_split[0] << ")" << endl;
            }

        }

        if (movies_in_year.empty()){
            cout << "No movies released in " << year << "." << endl;
        }
        cout << "\n";
        return;
    }

    vector<Movie> sorted_movies; // used to sort through movies by year

    if (year == 0 and !director_name.empty()){ // we want to list movies by director
        for (const auto& [key, movie] : movies){
            // director in struct Movie is string "Lastname,Firstname".
            // while director_name is vector where:
            // director_name[0] = firstname
            // director_name[1] = lastname

            vector<string> director_movie = split(movie.director, ',', true); // director in movies[key]
            // director_movie[0] = lastname
            // director_movie[1] = firstname
            if(director_name [1] == director_movie[0] and director_name[0] == director_movie[1]){
                sorted_movies.push_back(movie);
            }
        }

        if (sorted_movies.empty()){
            cout << "No movies directed by " << director_name[0] << " " << director_name[1] << "." << endl;
            cout << "\n";
            return;
        }

        sort(sorted_movies.begin(), sorted_movies.end(),
             [](const Movie& a, const Movie& b){
            if (a.year != b.year){
                return a.year < b.year; // which is older
            }
            return a.name < b.name; // in alphabetical order in case the year is the same
        });

        for (const auto& m : sorted_movies){ // print in desired format
            cout << "  " << m.name << " (" << m.year << ")" << endl;
        }
        cout << "\n";
        return;
    }

    else{ // we want to list all movies

        for (const auto& [key, movie] : movies){
            sorted_movies.push_back(movie);
        }

        sort(sorted_movies.begin(), sorted_movies.end(),
             [](const Movie& a, const Movie& b){
            if (a.year != b.year){
                return a.year < b.year; // which is older
            }
            return a.name < b.name; // in alphabetical order if year is same
        });

        for (const auto& m : sorted_movies){
            vector<string> director = split(m.director, ',', true);
            cout << "  " << m.name << " (" << m.year << ", dir. " << director[1] << " " << director[0] << ")" << endl;
        }
        cout << endl;
        return;
    }
}

// prints actors according to command line. Two options: either print all actors found in input file,
// or print the prolific of n actors (the actors starring in the most movies)
// params:
// map movies containing all movies
// n == 0 in default case where we're only looking to print all actors,
// if n > 0, then we are talking about prolific actors n.
void printActors(map<pair<string, int>, Movie>& movies, const int& n = 0){
    if (movies.empty()){
        cout << "No actors." << endl;
        cout << endl;
        return;
    }
    vector<string> actors;
    map<string, int> occurrences;
    for (const auto& [key, movie] : movies){
        for(const auto& actor : movie.actors){
            actors.push_back(actor);
        }
    }
    // now we have a vector of the actors in every movie in movies
    // we can use this to also count how many times a certain name comes up
    for (const auto& name : actors){
        occurrences[name]++;
    }

    if (n > 0){
        // let's copy map into vector or pairs to make sorting easier
        vector<pair<string, int>> actor_counts(occurrences.begin(), occurrences.end());

        // sort by count descending, then by name ascending
        sort(actor_counts.begin(), actor_counts.end(),
             [](const pair<string,int>& a, const pair<string,int>& b){
                 if (a.second != b.second) return a.second > b.second; // more movies first
                 return a.first < b.first;                             // alphabetical if same count
             });

        // determine how many to print
        size_t limit = min(actor_counts.size(), (size_t)n);

        for(size_t i=0; i<limit; ++i){
            string whole_name = actor_counts[i].first;
            vector<string> name_split = split(whole_name, ',', true);
            cout << "  " << name_split[1] << " " << name_split[0] << ": "
                 << actor_counts[i].second << " movies" << endl;
        }
        cout << "\n";
    }

    else{
        for (const auto& [name, occurrence] : occurrences){
        vector<string> name_split = split(name, ',', true);
        cout << "  " << name_split[1] << " " << name_split[0] << endl;
        }
        cout << "\n";
        return;
    }
}

// function evaluates a string and checks if it is a number or a string
// params: string s
// returns: bool true if all chars in string are digits and false otherwise
bool isNumber(const string& s){
    for (unsigned char c : s){
        if (!isdigit(c)){
            return false;
        }
    }
    return true;
}

int main()
{
    map<pair<string, int>, Movie> movies;
    while(true){
        string line;
        cout << "> ";
        getline(cin, line);
        
        vector<string> commands = split(line, ' ', true); // no need to include spaces in this context

        if (commands.size() == 0){ // allow empty inputs
            continue;
        }

        string command = commands.at(0);

        if (command == "help" or command == "Help"){
            help();
            continue;
        }

        else if (command == "read" or command == "Read"){
            string filename = commands.at(1); // assume file name is next string
            map<pair<string,int>, Movie> new_movies = readFile(filename);

                // Merge new_movies into existing movies map
                for (const auto& [key, movie] : new_movies){
                    movies[key] = movie; // insert or overwrite if already exists
                }

            cout << "\n";
            continue;
        }

        else if (command == "movies" or command == "Movies"){
            if (commands.size() > 1){ // user input has additional commands (movies by... or movies from...)

                if (commands.at(1) != "by" and commands.at(1) != "from"){
                    cout << "Error: unknown command." << endl;
                    cout << endl;
                    continue;
                }

                if (commands.at(1) == "from"){

                    if (commands.size() != 3){ // acceptable form is "movies from <year>"
                        cout << "Error: wrong amount of parameters." << endl;
                        cout << "\n";
                        continue;
                    }

                    string parameter = commands.at(2);

                    if (!isNumber(parameter)){
                        cout << "Error: invalid parameter." << endl;
                        cout << endl;
                        continue;
                    }

                    int n = stoi(parameter);
                    printMovies(movies, n);
                    // movies from <year> here
                    continue;
                }

                else if (commands.at(1) == "by"){ // acceptable form is "movies by <firstname> <lastname>"
                    if (commands.size() != 4){
                        cout << "Error: wrong amount of parameters." << endl;
                        cout << "\n";
                        continue;
                    }
                    else{
                        vector<string> parameter(commands.begin()+2, commands.end());
                        printMovies(movies,0, parameter);
                        // movies by <director> here
                        continue;
                    }

                }

            }

            else{ // user requests list of movies, no further requests
                printMovies(movies);
                continue;
            }
        }

        else if (command == "actors" or command == "Actors"){
            // actor operations here
            if (commands.size() == 3){

                string option = commands.at(1);
                string parameter = commands.at(2);

                if (!isNumber(parameter)){
                    cout << "Error: invalid parameter." << endl;
                    cout << endl;
                    continue;
                }
                int n = stoi(parameter);
                printActors(movies, n);
                // print actors that occur the most here
                continue;
            }

            if(commands.size() == 1){
                printActors(movies);
                // list actors here
            }

            else{
                cout << "Error: wrong amount of parameters." << endl;
                cout <<"\n";
            }
        }

        else if (command == "quit" or command == "Quit"){
            return EXIT_SUCCESS;
        }

        else{
            cout << "Error: unknown command." << endl;
            cout << "\n";
            continue;
        }
    }
}
