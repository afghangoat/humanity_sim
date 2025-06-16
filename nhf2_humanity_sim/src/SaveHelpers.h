/**
 * @file SaveHelpers.hpp
 * @brief A mentést segítő factory-k és segédfüggvények.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef SAVEHELPERS_HPP
#define SAVEHELPERS_HPP

#include <string>
#include <unordered_map>
#include <functional>

#include "creatures/Living.h"

#include "creatures/humans/Human.h"
#include "creatures/humans/Woodcutter.h"
#include "creatures/humans/Farmer.h"
#include "creatures/humans/Stonemason.h"
#include "creatures/humans/Fisherman.h"
#include "creatures/humans/Builder.h"
#include "creatures/humans/King.h"
#include "creatures/humans/AnglerMiner.h"
#include "creatures/humans/Soldier.h"

#include "creatures/Goat.h"

#include "creatures/hostiles/Crocodile.h"
#include "creatures/hostiles/Bear.h"
#include "creatures/hostiles/KillerRobot.h"

#include "world_object/Structure.h"
#include "world_object/ResourceStructure.h"
#include "world_object/BerryBush.h"
#include "world_object/Stone.h"
#include "world_object/Tree.h"
#include "world_object/Iron.h"
#include "world_object/CityCenter.h"
#include "world_object/House.h"

namespace minerals{
	/// @brief Mentést elősegítő függvények.
	std::string mineral_to_string(MINERAL_TYPE type);
}

/// Segít abba, hogy OOP-sebben lehessen az embernek véletlenszerűen új szakmát adni.
struct RoleOption {
	std::function<creature::Human*(int, int, creature::ENTITY_GENDER)> create;
	std::vector<std::pair<std::string, int>> requirements;
};

/// @brief Factory-k.
class SaveHelper {
	private:
		using CreatureFactory = std::function<creature::Living*(int, int)>;
		using HumanFactory = std::function<creature::Human*(int, int, creature::ENTITY_GENDER)>;
		using ResourceFactory = std::function<minerals::ResourceStructure*(int, int)>;
		
		static const std::unordered_map<std::string, ResourceFactory> resource_factory;
		static const std::unordered_map<std::string, HumanFactory> human_factory;
		static const std::unordered_map<std::string, CreatureFactory> creature_factory;
		static const std::vector<RoleOption> roles;
		
	public:

		static const std::unordered_map<std::string, CreatureFactory>& getCreatureFactory();
		static const std::unordered_map<std::string, HumanFactory>& getHumanFactory();
		static const std::unordered_map<std::string, ResourceFactory>& getResourceFactory();
		static const std::vector<RoleOption>& get_roles();
		
		static std::string trim_brackets(const std::string& s);
};

#endif