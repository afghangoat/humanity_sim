/**
 * @file EntityPlacer.hpp
 * @brief Az entitások lerakásáért felelős osztály itt van deklarálva.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef ENTITYPLACER_HPP
#define ENTITYPLACER_HPP

#include <string>
#include <unordered_map>
#include <algorithm>

#include "World.hpp"
#include "GameConfig.h"
#include "creatures/Living.h"

#include "creatures/humans/Human.h"
#include "creatures/humans/King.h"

#include "creatures/Goat.h"
#include "creatures/hostiles/Crocodile.h"
#include "creatures/hostiles/Bear.h"
#include "creatures/hostiles/KillerRobot.h"

#include "world_object/BerryBush.h"
#include "world_object/Stone.h"
#include "world_object/Tree.h"
#include "world_object/Iron.h"

#include "Utils.h"

/**
 * @class ObjectRegistry
 * @brief Az entitások és más világ objektumok lerakásának intézéséért felelős osztály.
 *
 */
class ObjectRegistry {
	private:
		using SpawnFunc = std::function<bool(World&,const sf::Vector2i&)>;
		std::unordered_map<int, SpawnFunc> factory_map; ///< Milyen idézés fusson le bizonyos gombok lenyomásakor.
		
	public:
		
		void register_type(int id, SpawnFunc func);///< Felvesz egy új idézés parancsot egy bizonyos gomb lenyomásra.

		bool spawn(int id,World& world,sf::Vector2i& epos) const; ///< Szimulál egy idézést a megadott gomb lenyomásra.
};

/**
 * @class EntityPlacer
 * @brief Az entitások a kattintással való lerakása.
 *
 */
class EntityPlacer{
	private:
		int current_entity_id=-1; ///< Gomb alapján melyik entitást kell lerakni
		bool placing=false; ///< Éppen le kell-e rakni entitásokat kattintásra.
		ObjectRegistry factory; ///< Így tudja tisztán leidézni az új objektumokat.
		bool mouse_lock=false;
		
		std::unordered_map<int, std::function<bool()>> entity_factory;
	public:
	
		EntityPlacer(); ///< Alap konstruktor, ami beállítja, hogy eleinte nem szabad lerakni semmit.
		bool try_place_entity(sf::Vector2i& epos,World& world); ///< Megpróbál lerakni egy entitást a kurzor helyére, ha megtehetei.
		void toggle_placing(); ///< Ki-be kapcsolja a működést.
		void select_entity(int new_id); ///< Beállítja, hogy milyen entitást rakjon le index alapján.
		
		bool setup_factory(); ///< Beállítja az alap idézési parancsokat.
		
		bool spacePreviouslyPressed;
		void reset_mouse();
		
};
#endif