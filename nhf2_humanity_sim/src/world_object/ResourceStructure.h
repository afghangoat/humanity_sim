/**
 * @file ResourceStructure.hpp
 * @brief A kibányászható osztály itt van deklarálva.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef RESOURCESTRUCTURE_HPP
#define RESOURCESTRUCTURE_HPP

#include "Structure.h"
#include "../SoundPlayer.h"
#include <string>

namespace minerals{
	/**
	 * @class ResourceStructure
	 * @brief Az erőforrás struktúra osztály leírása.
	 *
	 * Ez az interface rendelkezik azokról az adatokról, hogy kibányászható-e még ez az objektum és ahhoz szükséges metódusokkal.
	 */
	class ResourceStructure: public Structure{
		protected:
			float inner_timer; ///< Az idéződés óta eltelt idő.
			bool harvested; ///< Ki van-e termelve az erőforrás.
			bool needs_remove;
		public:
			bool get_harvested() const; ///< Megadja, hogy kitermelt-e az erőforrás.
			ResourceStructure(int x, int y); ///< Konstruktor ami lerakja az erőforrást egy (x,y) pontra.
			
			virtual bool harvest(); ///< virtuális metódus. Ez leírja mi történik, hogy ha kitermelik ezt az erőforrást.
			virtual ~ResourceStructure()=default; ///< Virtuális destruktor.
			
			virtual void play_destroy_sound(SoundPlayer& sound_player) const = 0; ///Rombolás hangjának lejátszása.
			
			bool get_needs_remove() const;
			
	};
}

#endif