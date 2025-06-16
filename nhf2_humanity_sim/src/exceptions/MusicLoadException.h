/**
 * @file MusicLoadException.hpp
 * @brief Ebben a fájlban vannak deklarálva azok a hibák, amik az Zenéhez kapcsolódnak.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef MUSIC_LOAD_EXCEPTION_HPP
#define MUSIC_LOAD_EXCEPTION_HPP

#include "SimulationException.h"

/**
 * @class MusicLoadException
 * @brief Akkor kell dobni, ha egy zene hibásan lett lejátszva vagy hibás a beolvasott zene.
 */
class MusicLoadException : public SimulationException {
	public:
		explicit MusicLoadException(const std::string& msg) : SimulationException(msg) {}
};

#endif