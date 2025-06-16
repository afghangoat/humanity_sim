/**
 * @file GameConfig.hpp
 * @brief A Szimuláció konfigurációja itt érhető el.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */
#ifndef GAMECONFIG_HPP
#define GAMECONFIG_HPP

#include "YAMLParser.h"

#include <mutex>
#include <iostream>
#include <string>

enum class Language { MAGYAR, ENGLISH, NONE };

/**
 * @class GameConfig
 * @brief A világ szimulációjának leírása.
 *
 * Tárolja azokat az értékeket, amiktől függ az, hogy mi mikor és hogyan történik a világba.
 */
class GameConfig {
	private:
        int debug_level=3; ///< Szabályozza, hogy milyen információk, figyelmeztetések íródnak ki. 1: Nem íródik ki semmi, 2: IO és kisebb figyelmeztetések, 3: Szimulációhoz kapcsolatos információk is kiíródnak
		
		int target_fps=60; ///< A kívánt FPS szám a program futása során.
		int screen_width=960; ///< Az ablak szélessége.
		int screen_height=640; ///< Az ablak magassága.
		
		int world_size=40; ///< A világ mérete n*n formában.
		Language what_language=Language::MAGYAR; ///< Milyen nyelven kell logolni?
		Language what_sfml_language=Language::NONE; ///< Milyen nyelven kell logolni az SFML utasításokat?
		
		int max_spawn_tries=99; ///< Meddig próbálkozzon az entitások, objektumok letételével a világ.
		int resource_scarcity=4; ///< Milyen bő legyen a világ az erőforrásokban.
		int hostiles_count=1; ///< Hány vadállat idéződjön szezononként.
		
		bool chromatic_aberration=false;
		bool noise=false;
		
		std::mutex mtx; ///< Segéd adattag a párhuzamosítás biztonságot működéséhez.

        GameConfig(); ///< Privát konstruktor a signleton pattern miatt.

    public:
		
        GameConfig(const GameConfig&) = delete; ///< Nem szükséges a signleton pattern miatt.
        GameConfig& operator=(const GameConfig&) = delete; ///< Nem szükséges a signleton pattern miatt.
		
		/**
		 * @brief Visszaad egy referenciát erre az osztály-ra.
		 * @return A singleton-hoz egy referencia.
		 * @static
		 */
        static GameConfig& get_instance();
		
		bool read_from_config_file(const std::string& filepath); ///< Beolvassa a filepath elérési útvonalról a konfigurációt.
		
        int get_config_level() const; ///< Visszaadja, hogy mennyire bőbeszédű legyen a hibakezelés / figyelmeztetések.
		int get_target_fps() const; ///< Visszaadja az elérni kívánt FPS értékét.
		
		int get_screen_width() const; ///< Visszaadja az ablak szélességét.
		int get_screen_height() const; ///< Visszaadja az ablak magasságát.
			
        void set_config_level(int n_flag); ///< Beállítható, hogy mennyire bőbeszédű legyen a hibakezelés / figyelmeztetések.
		
		int get_world_size() const; ///< Visszaadja a világ konfigurált méretét.
		void set_world_size(int newsize); ///< Beállítja a világ konfigurált méretét.
		int get_max_spawn_tries() const;
		int get_resource_scarcity() const;
		int get_hostiles_count() const;
		bool is_noise() const;
		bool is_chromatic_aberration() const;
		
		float day_length=400.0; ///< A napok hossza másodpercben.
		Language get_lang() const;
		Language get_sfml_lang() const;
		
};

#endif