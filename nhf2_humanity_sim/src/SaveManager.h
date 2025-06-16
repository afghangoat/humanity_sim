/**
 * @file SaveManager.hpp
 * @brief A fájl menedzseléshez szolgáló osztály itt van deklarálva.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef SAVEe_MANAGER_HPP
#define SAVEe_MANAGER_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>

#include "Utils.h"

#include "World.hpp"
#include "SaveHelpers.h"
#include "GameConfig.h"

#include "./exceptions/FileExceptions.h"

class World;

/**
 * @class SaveManager
 * @brief A fájl menedzseléshez szolgáló osztály leírása.
 *
 * Képes betölteni mentést, eltárolni és törölni is.
 */
class SaveManager {
	private:
		std::string fileName; ///< A mentés fájl elérési útvonala és neve.

	public:
		/**
		 * @brief A konstruktor, ahol beállítható, hogy mi a neve és elérési útvonala a mentés fájlnak.
		 * @param file Az elérési útvonal.
		 */
		SaveManager(const std::string& file);

		/**
		 * @brief Elment egy világot a fájlba.
		 * @param world Referencia a világra.
		 */
		void saveFile(World& world);

		/**
		 * @brief Elment egy fájlt a világba.
		 * @param world Referencia a világra.
		 */
		void loadFile(World& world);

		void deleteFile(); ///< Kitörli a jelenlegi mentés fájl tartalmát.
};
#endif