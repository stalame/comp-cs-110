/*
 * COMP.CS.110: Programming 2
 * Project: Playlists
 * File: song.hh
 * Description: header file for struct Song. No source file needed for struct.
 * Attributes:
 * - song ID (used in playlists)
 * - Artist
 * - Song title
 * - Duration in seconds
 *
 * All attributes are stored as type string.
 *
 * Notes:
 *
 */

#ifndef SONG_HH
#define SONG_HH

#include <string>

struct Song{
    std::string id; // id of song, stored in playlist according to this
    std::string artist;
    std::string title;
    int duration; //duration is stored in seconds
};

#endif // SONG_HH
