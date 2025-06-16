/**
 * @file TextureManager.hpp
 * @brief Ebbe a fájlba van az az osztály, ami a textúrák betöltéséért, kiosztásáért és tárolásáért felelős.
 * 
 * A TextureManager osztály singleton pattern-t használ.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */

#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include "Utils.h"
#ifndef WITH_SFML_RENDER
	#include "./fake_sfml/fake_sfml.h"
#else
	#include <SFML/Graphics.hpp>
#endif


#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>

/**
 * @class TextureManager
 * @brief A Textúra kezelő osztály.
 *
 * A textúrák betöltéséért, tárolásáért és kiosztásáért felelős osztály.
 * Rendelkezik egy tisztítás metódussal is.
 */
class TextureManager {
	private:
		std::unordered_map<std::string, sf::Texture> textures; ///< Egy map, ami egy fájl elérési úthoz rendel egy textúrát.

		TextureManager() {} ///< A Singleton pattern miatt privát.
		~TextureManager() {} ///< A Singleton pattern miatt privát.

		TextureManager(const TextureManager&) = delete; ///< A Singleton pattern miatt ez nem kell. Priváttá is kell tenni.
		TextureManager& operator=(const TextureManager&) = delete; ///< A Singleton pattern miatt ez nem kell. Priváttá is kell tenni.
		
	public:
		/**
		 * @brief Odaadja a referenciát a singleton-ra.
		 * @return A referencia a textúrakezelőre.
		 * @static
		 */
		static TextureManager& getInstance();

		/**
		 * @brief Betölti a kért textúrát, ha kell. Ha nem, akkor csak visszaadja a már régen betöltött textúrát.
		 * @param filename A textúra elérési útja.
		 * @return Referencia a kért textúrára.
		 */
		sf::Texture* loadTexture(const std::string& filename);
		
		/**
		 * @brief Odaadja a kért textúrát. Azért kell, mert a Memtrace hibát dob, ha a másik metódust használom.
		 * @param filename A textúra elérési útja.
		 * @return Referencia a kért textúrára.
		 */
		sf::Texture getTexture(const std::string& filename);
		void clear(); ///< Kitörli az összes betöltött textúrát.
		
};

#endif