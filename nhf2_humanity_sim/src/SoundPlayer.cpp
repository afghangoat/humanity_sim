#include "SoundPlayer.h"

void SoundPlayer::load_sound(const std::string& filename){
	if (sounds.find(filename) == sounds.end()) {
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile(filename)) {
            warn_text(
				"Failed to load sound: " + filename,
				"Nem sikerült betölteni a hangot: " + filename,
				0
			);
            return;
        }
        sounds[filename] = std::move(buffer);
    }
}

void SoundPlayer::play_sound(const std::string& filename){
	auto it = sounds.find(filename);
    if (it == sounds.end()) {
		load_sound(filename);
    }
	auto it2 = sounds.find(filename);
	
	cur_sound.setBuffer(it2->second);
    cur_sound.play();
}

void SoundPlayer::stop_sound(){
	cur_sound.stop();
}