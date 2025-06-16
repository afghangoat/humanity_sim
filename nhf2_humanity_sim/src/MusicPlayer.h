/**
 * @file MusicPlayer.hpp
 * @brief A zene lejátszó osztály itt van deklarálva.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef MUSICPLAYER_HPP
#define MUSICPLAYER_HPP

#include "Utils.h"
#ifndef WITH_SFML_RENDER
	#include "./fake_sfml/fake_sfml.h"
#else
	#include <SFML/Audio.hpp>
#endif
#include <unordered_map>
#include <string>
#include <memory>
#include "./exceptions/MusicLoadException.h"

/**
 * @class MusicPlayer
 * @brief A zene játszó osztály leírása.
 *
 * Képes zenét betölteni, ki-be kapcsolni és lejátszani megadott hangerőn.
 */
class MusicPlayer{
	private:
		bool toggled; ///< Be van-e kapcsolva a zene.
		bool loaded_music; ///< Be van-e töltve a zene.
		sf::Music music; ///< A jelenlegi betöltött zene.
	public:
		MusicPlayer(); ///< Alap konstruktor, beállítja a toggled és load_music értéket hamisra.
		
		/**
		 * @brief Betölti az elérési útvonal végén lévő fájlból a zenét.
		 * @param filename A fájl elérési útvonala.
		 */
		void load_music(const std::string& filename);
		void toggle_music(); ///< Ki-be kapcsolja a zenét.
		/**
		 * @brief Beállítja a hangerőt X decibelre.
		 * @param vol Mekkora decibel.
		 */
		void set_volume(float vol);
		~MusicPlayer(); ///< Destruktor, ami megállítja a zenét. Ez kiküszöböli a sound blasting-et, ami e-nélkül lenne.
};
#endif