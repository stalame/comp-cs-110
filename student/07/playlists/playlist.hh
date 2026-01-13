/*
 * COMP.CS.110: Programming 2
 * Project: Playlists
 * File: playlists.hh
 * Description: header file for class Playlist. Corresponding sourcefile is playlist.cpp.
 * Methods:
 * - add songs to playlist
 * - calculate the duration of the playlist
 * - get the name, user and songs of the playlist
 * - print the playlist's contents
 * - set the name and user for the playlist
 * Notes:
 * This class is here to help access the songs more easily from class Music and make this program more realistic
 * and correspond to a realistic music-managing structure. The class is a middle-man between struct Song and class Music.
 */
#ifndef PLAYLIST_HH
#define PLAYLIST_HH

#include "song.hh"
#include "utilities.hh"
#include <string>
#include <vector>
#include <memory>

class Playlist
{
public:
    // initialize class Playlist
    Playlist();

    // Calculates the total duration of the playlist according
    // to the length of the songs in the playlist.
    // returns an int of the playlist duration in seconds
    int playlist_duration()const;

    // adds songs into std::vector<Song> songs
    void add_song(const std::shared_ptr<Song>& s);

    // GETTERS
    // Retrieves the name of the playlist
    std::string get_name() const;

    // Retrieves the name of the user who created the playlist
    std::string get_user() const;

    // Returns a vector std::vector<Song> of the songs in playlist
    const std::vector<std::shared_ptr<Song>>& get_songs()const;

    //

    // Prints the playlist in the correct format
    // loops through the songs in playlist vector
    void print_playlist()const;

    // SETTERS
    // For initializing a new playlist,
    // Sets the attribute user_ to function input parameter name
    void set_user(const std::string& name);

    // For initializing a new playlist,
    // Sets the attribute playlist_title_ to function input string param title
    void set_title(const std::string& title);

    //

private:
    std::string playlist_title_;
    std::string user_;
    std::vector<std::shared_ptr<Song>> songs_;
};

#endif // PLAYLIST_HH
