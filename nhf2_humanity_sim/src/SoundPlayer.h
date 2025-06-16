/**
 * @file SoundPlayer.hpp
 * @brief Ebben a fájlba vannak a hanglejátszó osztályhoz szükséges deklarációk.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef SOUNDPLAYER_HPP
#define SOUNDPLAYER_HPP

#include "Utils.h"
#ifndef WITH_SFML_RENDER
	#include "./fake_sfml/fake_sfml.h"
#else
	#include <SFML/Audio.hpp>
#endif
#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>

/**
 * @class SoundPlayer
 * @brief A hanglejátszó osztály leírása
 *
 * Képes hangokat betölteni, elindítani, lejátszani és megállítani.
 */
class SoundPlayer{
	private:
		std::unordered_map<std::string, sf::SoundBuffer> sounds; ///< A tárolt betöltött hangok hozzárendelve az elérési útvonalukhoz.
		sf::Sound cur_sound; ///< A jelenlegi lejátszott hang.
	public:
		/**
		 * @brief Betölt egy hangot az elérési útvonalról.
		 * @param filename Az elérési útvonal.
		 */
		void load_sound(const std::string& filename);
		/**
		 * @brief Lejátszik egy hangot az elérési útvonalról. Ha még nem volt ez betöltve akkor először betölti.
		 * @param filename Az elérési útvonal.
		 */
		void play_sound(const std::string& filename);
		
		void stop_sound(); ///< Megállítja az éppen lejátszott hangot.
};
#endif