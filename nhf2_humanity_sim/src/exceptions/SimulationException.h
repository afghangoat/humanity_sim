/**
 * @file SimulationException.hpp
 * @brief Ebben a fájlban vannak deklarálva azok a hibák, amik az alap Szimulációhoz kapcsolódnak.
 * Ezekből a hibákból öröklődik minden olyan hiba, amit a program kezel és dob.
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef SIMULATIONEXCEPTION_HPP
#define SIMULATIONEXCEPTION_HPP

#include <stdexcept>
#include <string>

/**
 * @class SimulationException
 * @brief Akkor kell dobni, ha egy szimulációs elem hibásan viselkedik.
 */
class SimulationException : public std::runtime_error {
	public:
		explicit SimulationException(const std::string& msg) : std::runtime_error("Simulation Program | "+msg) {}
};

#endif