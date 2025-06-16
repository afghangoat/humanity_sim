/**
 * @file GameManager.hpp
 * @brief A játékmenedzser osztály itt van deklarálva.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "Utils.h"
#ifndef WITH_SFML_RENDER
	#include "./fake_sfml/fake_sfml.h"
#else
	#include <SFML/Graphics.hpp>
#endif
#include <iostream>
#include <vector>
#include "Utils.h"
#include "GameConfig.h"
#include "ui/button.h"

#include "World.hpp"
#include "EntityPlacer.h"
#include "PostProcesser.h"

#include "MusicPlayer.h"
#include "SaveManager.h"
#include "SoundPlayer.h"


class World;
class SaveManager;
class EntityPlacer;

/**
 * @class GameManager
 * @brief A világ szimulálásáért és a kirazolás irányításáért felelős osztály.
 *
 * Tárolja a világot, a render ablakot, a kamera adatait, a gombokat és a zene lejátszót.
 * Végül mindent ez az osztály szabadít fel.
 */
class GameManager{
	private:
		sf::RenderWindow* window=nullptr; ///< A render ablak.
		
		int view_offset_x; ///< A kamera X eltolása.
		int view_offset_y; ///< A kamera Y eltolása.
		
		sf::Vector2i mouse_pos; ///< Az egér pozíciója.
		bool mouse_clicked; ///< Le van-e nyomva az egér bal gombja.
		const int camera_speed=5; ///< A kamera gyorsasága, amit egy frame-be megtesz.
		sf::Clock Clock; ///< Az óra, ami segít kiszámolni az időt 2 frame között.
		float delta_time; ///< A program indítása óta eltelt idő.
		
		World* world=nullptr; ///< A világ, amiben történik a szimuláció.
		PostProcesser* processer=nullptr; ///< A grafikus szépító osztályra pointer.
		std::vector<ui::Button*> buttons; ///< Gombok tömbje.
		
		void handle_inputs(); ///< Lekezeli a kamera mozgását, az egér kattintását.
		void update_world(); ///< Kiad egy parancsot, hogy frissüljön 1 iterációt a világ.
		void draw_world(); ///< Kirajzolja a világot.
		
		MusicPlayer music_player; ///< A hanglejtászásért felelős osztály.
		SaveManager* save_manager=nullptr; ///< A mentéshez szükséges osztály pointer.
		bool paused; ///< Kell-e szimulálni a világot.
		
		SoundPlayer sound_player; ///< Egy hanglejtászó, ami a gombok kattintását játsza le, ha kell.
		bool valid=false;
		
		EntityPlacer* entity_placer=nullptr; ///< Ez arra kell, hogy le tudjon a felhasználó rakni entitásokat.
	public:
	
		GameManager(); ///< A konstruktorba létrejön az ablak és az alap változók beállításra kerülnek.
		
		void run(); ///< Elindítja a szimulációt és innentől kirajolja a világot, gombokat.
		
		void game_loop(); ///< A szimuláció loopolását indítja el.
		
		void setup_buttons(); ///< A gombokat létrehozza, textúrájukat, viselkedésüket betölti.
		void update_buttons(); ///< Frissíti a gombokat, ha 1-re rákattintottak.
		void draw_buttons(); ///< Kirajzolja a gombokat.
		
		bool is_valid() const; ///< Megadja, hogy sikeres lett-e a szimulációs elemek inicializálása.
		float get_elapsed_time() const; ///< Megadja az eltelt időt, ami eltelt a szimulációba.
		void simulate_tick(float e_time); ///< Szimulál T idő egységnyi időt.
		bool handle_unit_placement(); ///< Igazat ad vissza, ha idéztek le entitást, ha nem akkor hamis.
		
		~GameManager(); ///< Felszabadítja a világot, gombokat, hangot, textúrákat, render ablakot. Mindent, ami a program tartalmaz.
};

#endif