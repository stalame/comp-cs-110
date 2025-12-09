#include "music.hh"
#include "playlist.hh"
#include "utilities.hh"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <random>

Music::Music(){

}

bool Music::read_from_file(std::string file_name){

    std::ifstream file_object(file_name);
    if (not file_object){
        std::cout << "Error: could not open file." << std::endl;
        return false;
    }
    std::string line = "";

    std::vector<Song> all_songs;

    while (getline(file_object, line)){

        if (line.empty() || line == "PLAYLISTS"){ // ignore empty lines and line that indicates playlists are in next line
            continue;
        }

        std::vector<std::string> parts = Utilities::split(line, ';', true);

        // check if any of the strings in parts are empty
        for (const auto& part : parts){
            if (part.empty()){
                std::cout << "Error: incorrect row in file." << std::endl;
                return false;
            }
        }

        if (parts.size() == 4){ //when parts.size() is 4, then it's a song
            if(!Utilities::is_int(parts.at(3))){
                std::cout << "Error: incorrect row in file." << std::endl;
                return false;
            }
            std::string id = parts.at(0);
            std::string artist = parts.at(1);
            std::string title = parts.at(2);
            int duration = stoi(parts.at(3)); // convert song duration from string to int
            Song new_song{id, artist, title, duration};

            all_songs.push_back(new_song); // add song to vector of songs
        }

        else if(parts.size() == 3){ // when parts.size() is 3, then it's a playlist
            Playlist playlist;
            std::string playlist_name = parts.at(0);
            std::string user = parts.at(1);
            std::vector<std::string> song_ids = Utilities::split(parts.at(2), '|', true);

            playlist.set_title(playlist_name);
            playlist.set_user(user);

            // check if any of the strings in song_ids are empty
            for (const auto& id : song_ids){
                if (id.empty()){
                    std::cout << "Error: incorrect row in file." << std::endl;
                    return false;
                }
                // check that all songs listed in file line are found in the program
                auto it = std::find_if(all_songs.begin(), all_songs.end(),[&](const Song& s){return s.id == id; });
                if (it != all_songs.end()){
                    playlist.add_song(*it); // make function for this
                }
                else{
                    std::cout << "Error: song not found." << std::endl;
                    return false;
                }

            }
            playlists_.push_back(playlist);
        }

        else{ // invalid line
            std::cout << "Error: incorrect row in file." << std::endl;
            return false;
        }
    }
    return true;
}

void Music::playlists_command(){
    std::vector<Playlist> sorted_playlists = playlists_;
    std::sort(sorted_playlists.begin(), sorted_playlists.end(),
              [](const Playlist& p1, const Playlist& p2){return p1.get_name() < p2.get_name();});

    for (const auto& playlist : sorted_playlists){
        playlist.print_playlist();
    }

}

void Music::playlist_command(std::string name){
    Playlist* p1 = nullptr;

    auto it = std::find_if(playlists_.begin(), playlists_.end(),
                           [&] (const Playlist& p){return p.get_name() == name;});
    if(it!=playlists_.end()){
        p1 = &(*it); //store pointer
    }
    else{
        std::cout << "Error: playlist not found." << std::endl;
        return;
    }
    std::vector<Song> sorted_songs = p1->get_songs();

    std::cout << p1->get_name() << ", created by " << p1->get_user() << std::endl;
    int running_number = 1;
    for(const auto& song : sorted_songs){
        std::cout << "  " << running_number << ". ";
        Utilities::print_song(song);
        running_number++;
    }

    std::cout << "Total duration " << Utilities::format_duration(p1->playlist_duration()) << std::endl;
}

void Music::songs_command(){
    // keep track of songs that have seen to avoid printing multiples
    std::set<std::string> seen_ids;
    std::vector<Song> all_songs;

    // collect all songs from all playlists
    for (const auto& playlist : playlists_){
        for(const auto& song : playlist.get_songs()){
            if(seen_ids.insert(song.id).second){
                all_songs.push_back(song); // collect each song only once
            }
        }
    }

    // sort songs according with compare_songs
    std::sort(all_songs.begin(), all_songs.end(),
              [](const Song& song1, const Song& song2){return Utilities::compare_songs(song1, song2);});

    for(const auto& song : all_songs){
        Utilities::print_song(song);
    }
}

void Music::favorites_command(std::string& user) {
    std::map<std::string, int> artist_count;

    // Count all songs by this user, grouped by artist
    for (const auto& playlist : playlists_) {
        if (playlist.get_user() == user) {
            for (const auto& song : playlist.get_songs()) {
                artist_count[song.artist]++;
            }
        }
    }

    if (artist_count.empty()) {
        std::cout << "Error: no playlists found for user." << std::endl;
        return;
    }

    // Find the maximum occurrence
    int max_count = 0;
    for (const auto& [artist, count] : artist_count) {
        if (count > max_count) max_count = count;
    }

    // Print the favorite artist(s)
    std::cout << "Favorite artist(s) of " << user
              << " (appeared " << max_count << " times):" << std::endl;

    for (const auto& [artist, count] : artist_count) {
        if (count == max_count) {
            std::cout << artist << std::endl;
        }
    }
}

void Music::shuffle_command(std::string name, std::string seed){
    // check

    auto it = std::find_if(playlists_.begin(), playlists_.end(),
                           [&](const Playlist& p){return p.get_name() == name ;});

    if(it==playlists_.end()){
        std::cout << "Error: playlist not found." << std::endl;
        return;
    }

    if(!Utilities::is_int(seed)){
        std::cout << "Error: incorrect seed parameter." << std::endl;
        return;
    }
    int seed_int = stoi(seed);
    const Playlist& playlist = *it;

    std::vector<Song> shuffled = playlist.get_songs();

    std::default_random_engine generator(seed_int);
    std::shuffle(shuffled.begin(), shuffled.end(), generator);

    std::cout << playlist.get_name() << ", created by " << playlist.get_user() << std::endl;
    int running_number = 1;
    for(const auto& song : shuffled){
        std::cout << "  " << running_number << ". ";
        Utilities::print_song(song);
        running_number++;
    }

    std::cout << "Total duration " << Utilities::format_duration(playlist.playlist_duration()) << std::endl;
}


