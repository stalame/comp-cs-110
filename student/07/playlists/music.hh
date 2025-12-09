/*
 * COMP.CS.110: Programming 2
 * Project: Playlists
 * File: music.hh
 * Description: header file for class Music. Corresponding sourcefile is music.cpp.
 * Methods:
 * - read <file>
 * - print specific output based on command (playlists, playlist <name>, songs, favorites <user>)
 * - shuffle <playlist>, <seed>
 * Notes:
 * The CLI accesses program through this class.
 */

#ifndef MUSIC_HH
#define MUSIC_HH

#include "song.hh"
#include "utilities.hh"
#include "playlist.hh"
#include <string> 


class Music
{
public:
    Music();

    /**
     * @brief read_from_file Reads song and playlist information into the
     *   from an input file.
     * @param file_name The name of the file to read.
     * @return true if the read was completely successful, false if an
     *   error occurred during reading of the file.
     */
    bool read_from_file(std::string file_name);

    /**
     * @brief playlists_command Prints all playlists saved in this program
     *   in alphabetical order of the playlist names.
     */
    void playlists_command();

    /**
     * @brief playlist_command Prints the details of a single playlist if a
     *   playlist with the given name exists in the program.
     * @param name Name of the playlist to print
     */
    void playlist_command(std::string name);

    /**
     * @brief songs_command Prints all songs in the program in alphabetical order
     * first by artist name and then by song name.
     */
    void songs_command();

    /**
     * @brief favorites_command Prints the given user's favorite artist(s), AKA.
     *   the artist(s) whose songs appear the most times in the user's playlists.
     *   Also print the amount of times their songs are featured.
     * @param user The name of the user.
     */
    void favorites_command(std::string& user);

    /**
     * @brief shuffle_command Shuffles the given playlist's song order and
     *   prints the new order. Does not actually modify the original
     *   playlist however.
     * @param name The name of the playlist.
     * @param seed The seed to use in the rng.
     */
    void shuffle_command(std::string name, std::string seed);

private:
    std::vector<Playlist> playlists_;

};

#endif // MUSIC_HH
