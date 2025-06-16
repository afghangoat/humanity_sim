#include "MusicPlayer.h"

MusicPlayer::MusicPlayer(){
	toggled=true;
	loaded_music=false;
}

void MusicPlayer::load_music(const std::string& filename){
	if (music.getStatus() == sf::SoundSource::Playing) {
        music.stop();
    }
	
	if (!music.openFromFile(filename)){
		throw MusicLoadException("Nem sikerült a zenét betölteni innen: " + filename);
		return;
	}

	music.setLoop(true);
	music.play();
	loaded_music=true;
}

void MusicPlayer::toggle_music(){
	if(loaded_music==false){
		return;
	}
	
	toggled=!toggled;
	if(toggled==true){
		music.play();
	} else {
		music.stop();
	}
}

void MusicPlayer::set_volume(float vol){
	if(vol>-100.0f){
		music.setVolume(vol);
	}
}
MusicPlayer::~MusicPlayer(){
	if(loaded_music==true){
		music.stop();
	}

}