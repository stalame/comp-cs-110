/*
 * COMP.CS.110: Programming 2
 * Project: Playlists
 * Creator: Amelia Stalter
 * Student ID: 151193060
 *
 * File: main.cpp
 *
 * Program description:
 * This program manages music through class Music, class Playlists and struct Song. When the program starts it
 * asks for a file to read, after which it reads it and stores the data from the file in the data structures
 * mentioned above. See other files to understand the characteristics and methods used for each data structure.
 * The program has a utilities data structure that includes all helper functions and other useful functions
 * that are used throughout the program.
 * The user can input commands:
 *  - playlist <name>
 *    Prints specific playlist called <name>, its creator, songs and total duration
 *  - playlists
 *    prints all playlists in program by name
 * - songs
 *    prints all songs in the program
 * - favorites <username>
 *    prints the favorite artists of some user's based on how many times that artist
 *    is found in user's playlists
 * - shuffle <playlist name> <seed>
 *   Shuffles a specific playlist according to random_number_generator and input seed value
 * - quit
 *   Quits the program
 *
 * Program files:
 *  Headers:
 *  cli.hh
 *  music.hh
 *  playlist.hh
 *  song.hh
 *  utilities.hh
 *
 *  Source files:
 *  cli.cpp
 *  music.cpp
 *  main.cpp
 *  playlist.cpp
 *  utilities.cpp
 *
 * Notes:
 *
 */
#include "cli.hh"
#include "music.hh"
#include <memory>
#include <iostream>

using namespace std;

int main() {

    shared_ptr<Music> music_db = make_shared<Music>();

    cout << "Input file: ";
    string input_file;
    getline(cin, input_file);
    if (!music_db->read_from_file(input_file)) {
        return EXIT_FAILURE;
    }
    cout << endl;

    shared_ptr<Cli> cli = make_shared<Cli>(music_db);

    bool exit_program = false;
    while (!exit_program) {
        exit_program = cli->exec_prompt();

        if (!exit_program) {
            cout << endl;
        }
    }

    return EXIT_SUCCESS;
}
