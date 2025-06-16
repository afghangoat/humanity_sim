/**
 * @file YAMLParser.hpp
 * @brief A config beolvasó osztály itt található.
 * 
 * @author Funk Gábor
 * @date 2025-05-09
 */
#ifndef YAML_HPP
#define YAML_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <fstream>

/**
 * @class YAMLParser
 * @brief Egy YAML (Yet Another Markup Language) fájl beolvasó osztály
 *
 * A YML specifikációnak megfelelően be tud olvasni YML fájlokat (.yml).
 */
class YAMLParser{
	private:
		static const std::string delimiter; ///< A YML fájlokban a : karakter az elválasztás (általába).
		static const std::string invalid_symbol; ///< Milyen tokent adjon a parser, ha nem olvasta be a keresett tokent.
		
		std::unordered_map<std::string, std::string> current_file_content; ///< A YML fájl tokeneinek tárolása.
		bool read_in; ///< Van-e már beolvasva fájl.
		
	public:
	
		YAMLParser(); ///< Az alap konstruktor, semmit nem csinál csak jelzi
		bool parse_file(const std::string& filepath); ///< Beolvassa a YML fájlt. Vigyáz a kommentekre.
		std::string get_value_of_key(const std::string& key) const; ///< Arra szolgál, hogy a beolvasott fájl tokenjeit kívűlről is el lehet érni.
		bool try_generate_config_file(const std::string& filename);
		
};

#endif