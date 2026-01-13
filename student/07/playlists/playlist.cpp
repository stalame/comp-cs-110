#include "playlist.hh"
#include <vector>
#include <iostream>


Playlist::Playlist():
    playlist_title_(), user_(), songs_()
{

}

// std::vector<Song> Playlist::shuffle(unsigned int seed) const;

int Playlist::playlist_duration()const{
    int total_seconds = 0;
    for (const auto& song : songs_){
        total_seconds += song->duration;
    }

    return total_seconds;
}

// void Playlist::list_songs(const std::vector<Song>& playlist, Utilities::song_printer printer) const{
// }

void Playlist::add_song(const std::shared_ptr<Song>& s){

    songs_.push_back(s);
}

std::string Playlist::get_name()const{
    return playlist_title_;
}

std::string Playlist::get_user()const{
    return user_;
}

const std::vector<std::shared_ptr<Song>>& Playlist::get_songs()const{
    return songs_;
}

void Playlist::print_playlist()const{
    std::cout << playlist_title_ << ", created by " << user_ << std::endl;
}

void Playlist::set_user(const std::string& name){
    user_ = name;
}

void Playlist::set_title(const std::string& title){
    playlist_title_ = title;
}
