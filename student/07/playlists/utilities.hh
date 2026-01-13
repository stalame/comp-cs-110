#ifndef UTILITIES_HH
#define UTILITIES_HH

#include "song.hh"
#include <vector>
#include <string>
#include <memory>

namespace Utilities {

// Splits the given string into parts by a given delimiter and stores them
// into a vector. If keep_empty is false, the function doesn't store empty parts.
std::vector<std::string> split(const std::string& str, char delim, bool keep_empty = false);

// Checks if the given string is an integer, and consists only of digits.
// If allow_negative is true, the string can additionally have a '-' prefix.
bool is_int(std::string str, bool allow_negative = false);

// Function pointer for song printer
using song_printer = void(*)(const std::shared_ptr<Song>&);

// Prints input parameter song in correct output format
// using function pointer song_printer
void print_song(const std::shared_ptr<Song>& s);

// All durations for both playlists and songs are stored in program in seconds
// Function changes duration to correct output format mins:secs
std::string format_duration(int total_seconds);

// Helper function for class Music methods that require printing songs in alphabetical order
// first based on band name and then based on song title
bool compare_songs(const std::shared_ptr<Song>& a, const std::shared_ptr<Song> & b);

}

#endif // UTILITIES_HH
