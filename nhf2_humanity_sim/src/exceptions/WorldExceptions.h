/**
 * @file WorldExceptions.hpp
 * @brief Ebben a fájlban vannak deklarálva azok a hibák, amik az Világhoz kapcsolódnak.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef WORLD_EXCEPTIONS_HPP
#define WORLD_EXCEPTIONS_HPP

#include "SimulationException.h"

/**
 * @class CityCenterException
 * @brief Akkor kell dobni, ha a városközpont hibásan működött.
 */
class CityCenterException : public SimulationException {
	public:
		explicit CityCenterException(const std::string& msg) : SimulationException(msg) {}
};
/**
 * @class StructureException
 * @brief Akkor kell dobni, ha egy struktúra hibásan működött.
 */
class StructureException : public SimulationException {
	public:
		explicit StructureException(const std::string& msg) : SimulationException(msg) {}
};

/**
 * @class InvalidBorderSizeException
 * @brief Akkor kell dobni, ha egy világhatárnak nem jó értéket akarnak beállítani.
 */
class InvalidBorderSizeException : public std::logic_error {
	public:
		explicit InvalidBorderSizeException(const std::string& msg) : std::logic_error(msg) {}
};

#endif