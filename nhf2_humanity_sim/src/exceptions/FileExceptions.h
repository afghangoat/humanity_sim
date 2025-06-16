/**
 * @file FileExceptions.hpp
 * @brief Ebben a fájlban vannak deklarálva azok a hibák, amik az IO-hoz kapcsolódnak.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef FILE_EXCEPTIONS_HPP
#define FILE_EXCEPTIONS_HPP

#include "SimulationException.h"

/**
 * @class ImportInvalidEntityException
 * @brief Akkor kell dobni, ha egy entitás hibásan lett beolvasva.
 */
class ImportInvalidEntityException : public SimulationException {
	public:
		explicit ImportInvalidEntityException(const std::string& msg) : SimulationException("Unknown creature: "+msg) {}
};
/**
 * @class ImportInvalidHumanProfessionException
 * @brief Akkor kell dobni, ha egy szakma hibásan lett beolvasva.
 */
class ImportInvalidHumanProfessionException : public std::logic_error {
	public:
		explicit ImportInvalidHumanProfessionException(const std::string& msg) : std::logic_error("Unknown human profession: "+msg) {}
};
/**
 * @class ImportInvalidHousingLevelException
 * @brief Akkor kell dobni, ha egy ház hibásan lett beolvasva.
 */
class ImportInvalidHousingLevelException : public SimulationException {
	public:
		explicit ImportInvalidHousingLevelException(const std::string& msg) : SimulationException("Unknown house level specified: "+msg) {}
};
/**
 * @class ImportInvalidResourceException
 * @brief Akkor kell dobni, ha egy erőforrás hibásan lett beolvasva.
 */
class ImportInvalidResourceException : public SimulationException {
	public:
		explicit ImportInvalidResourceException(const std::string& msg) : SimulationException("Tried to import unknown resource type from save file: "+msg) {}
};
/**
 * @class ReadSaveFileFail
 * @brief Akkor kell dobni, ha egy IO mentés, importálás vagy törlés hibás.
 */
class ReadSaveFileFail : public SimulationException {
	public:
		explicit ReadSaveFileFail(const std::string& msg) : SimulationException("Malformatted save file: "+msg) {}
};

#endif