/**
 * @file World.hpp
 * @brief A Világ osztály, ami a fő szimulációs elemek tárolásáért felelős.
 * 
 * Ez az osztály felelős a szimulácós elemekért, felszabadítja őket, ha kell.
 * 
 * @author Funk Gábor
 * @date 2025-04-21
 */

#ifndef WORLD_HPP
#define WORLD_HPP

#include "terrain_tiles/Tile.h"

#include <fstream>
#include <string>
#include <sstream>

#include "Utils.h"

#include "TerrainContainer.hpp"

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

#include <unordered_map>
#include <queue>

#include "world_object/Structure.h"
#include "world_object/ResourceStructure.h"
#include "world_object/BerryBush.h"
#include "world_object/Stone.h"
#include "world_object/Tree.h"
#include "world_object/Iron.h"
#include "world_object/CityCenter.h"
#include "world_object/House.h"
#include <vector>

#include "SoundPlayer.h"

#include "SaveHelpers.h"

#include "./exceptions/FileExceptions.h"
#include "./exceptions/WorldExceptions.h"

#include "HumanResources.h"

/**
 * @class WorldBase
 * @brief A világ elemeinek nyilvántartása és a kiszolgáló függvények is itt vannak. Csak az alap függvényeket tartalmazza.
 *
 */
class WorldBase{
	private:
		HumanResources hr; ///< Kezeli az emberek erőforrásait.
		
	protected:
		TerrainContainer<tiles::Tile*> terrain; ///< A terep tároló, 2 dimenziós dinamikus tömb.
		
		std::vector<creature::Living*> entities; ///< Az entitások pointerének tárolása. Nem tárol embert.
		std::vector<creature::Human*> humans; ///< Az ember pointerek tárolása.
		minerals::CityCenter* current_city_center; ///< A városközpont pointerének tárolása. Csak 1 városközpont lehet, ha 2-t próbálnak építeni, az hibás működést jelent.
		
		std::vector<minerals::ResourceStructure*> structures; ///< Az erőforrást tartalmazó struktúrák pointerének (fa, bokor, kő, vasérc) tárolásáért felelős heterogén kollekció.
		std::vector<minerals::House*> houses; ///< Az emberek által épített lakóházak pointerének tárolásáért felelős tároló.
		
		static constexpr int MAX_OBJECT_SIZE=64; ///< Amikor kikerül valami ennyire messziről a látótérből akkor az már nem rajzolódik ki.
		
		bool camp_needs_spawn; ///< Kell-e idéznünk új városlakókat?
		SoundPlayer sound_player; ///< Hanglejátszó modul. Mindennek hangja van a világban, ezért kell ez az osztály.
	public:
		HumanResources& get_resources(); ///< Külső referenciát ad a tárolt erőforrások elérésére.
		/**
		 * @brief Egy függvény, amivel kívülről el lehet érni a jelenlegi városközpontot.
		 * @return A városközpont.
		 */
		minerals::CityCenter* get_current_city_center();
		
		/**
		 * @brief Visszaadja a világban az [y][x]-edik terepkockát.
		 * @param x Oszlop index.
		 * @param y Sor index.
		 * @return Az x.Oszlop y.Sor-i terepkocka.
		 */
		tiles::Tile& getTileAt(int x, int y) const;
		
		/**
		 * @brief Idéz egy struktúrát. Opcionálisan bekapcsolható, hogy csak a hegyekben idéződjön.
		 * 
		 * @tparam T A struktúra.
		 * @param mountain_exclusive Ha igaz, akkor csak a hegyekben idéződik a struktúra.
		 */
		template<typename T>
		void spawn_structure(bool mountain_exclusive);
		
		/**
		 * @brief Keres egy olyan erőforrás struktúrát, ami bizonyos erőforrást tartalmaz.
		 * @param atype Az erőforrás típusa, ami keresett.
		 * @return Egy struktúra pointer.
		 */
		minerals::Structure* get_structure_type(minerals::MINERAL_TYPE atype);
		
		/**
		 * @brief Lerombol egy struktúrát egy bizonyos x és y koordinátán. Ezt az emberek hívják meg bányászatkor, favágáskor. Ha házra vagy városközpontra hívódik meg akkor hiba keletkezik.
		 * @param x Az x koordináta.
		 * @param y Az y koordináta.
		 */
		void remove_structure_at(int x, int y);
		
		/**
		 * @brief Keres egy nem foglalt lakóterületnek való helyet a városközponthoz közel.
		 * @return Egy (x,y) koordináta, ahova lehet házat építeni. Ha nincs ilyen akkor (-1,-1).
		 */
		sf::Vector2f get_position_nearby_town();
		
		/**
		 * @brief Keres egy olyan (x,y) koordinátát, amin van ház.
		 * @return Egy (x,y) koordinátapár ahol van ház. (-1,-1) ha nincs ilyen.
		 */
		sf::Vector2f get_random_house_pos();
		
		/**
		 * @brief Megpróbál megfrissíteni egy házat az (x,y) koordinátán. Ezt az építész ember hívja meg.
		 * @param x Az x koordináta.
		 * @param y Az y koordináta.
		 */
		void upgrade_house_at(int x,int y);
		
		/**
		 * @brief Visszaad egy olyan entitás típust, ami nem a specifikált típus. Ezt a ragadozó állatok hívják meg, hogy ne egymást vadásszák. Az ember vadász sem öl embereket.
		 * @param excluded_type A típus amit nem akar megkapni.
		 * @return Egy entitás pointer.
		 */
		creature::Living* get_excluded_entities(creature::ENTITY_TYPE excluded_type);
		
		/**
		 * @brief Idéz egy struktúrát egy pontos x és y coordinátára.
		 * 
		 * @tparam T A struktúra.
		 * @param x Az x koordináta.
		 * @param y Az y koordináta.
		 */
		template<typename T>
		void spawn_structure_at(int x, int y){
			structures.push_back(new T(x,y));
		}
		
		/**
		 * @brief Idéz egy entitást, egy bizonyos típusú biomba.
		 * 
		 * @tparam T Az entitás típusa.
		 * @param goal_habitat A terepkocka, ami a cél.
		 * @param savefile_identifier Ez egy azonosító, így fog a mentés fájlba megjelenni.
		 */
		template<typename T>
		void spawn_entity(tiles::TILETYPE goal_habitat,const std::string& savefile_identifier);
		
		/**
		 * @brief Keres egy optimális helyet terepkocka típus szerint.
		 * @param suitable_tile Az optimális terepkocka típusa.
		 * @return A szabad koordináta vektora. Ha nincs jó hely akkor a (-1,-1) vektor.
		 */
		sf::Vector2f get_random_suitable_position(tiles::TILETYPE suitable_tile);
		
		/**
		 * @brief Épít egy városközpontot egy x és y koordinátára. Ha már létezik városközpont, hiba keletkezik.
		 * @param x Az x koordináta.
		 * @param y Az y koordináta.
		 */
		void build_city_center_at(int x, int y);
		
		virtual ~WorldBase() = default; ///< Virtuális destruktor.
};

/**
 * @class WorldBaseSerialiazble
 * @brief A világ osztály bővítése, rendelkezik insertorral és extractorral.
 *
 * Be lehet olvasni adatot és ki lehet belőle olvasni adatot.
 */
class WorldBaseSerialiazble:public WorldBase{
	private:
		bool process_creature_chunk(const std::string& chunk); ///< Segédfüggvény a világ entitásainak betöltésére.
		bool process_structure_chunk(const std::string& chunk); ///< Segédfüggvény a világ struktúráinak betöltésére.
	protected:
		float elapsed_time; ///< A világba eltelt idő másodpercben.
		int saved_size=-1; ///< A világ elmentett mérete.
		
		friend std::ostream& operator<<(std::ostream& os, WorldBaseSerialiazble& w); ///< A világ adatait segíti kimenteni egy folyamba.
		friend std::ifstream& operator>>(std::ifstream& in, WorldBaseSerialiazble& w); ///< Egy folyamból tölti fel a világot új adatokkal.
		
		virtual void reinitialize_self(bool from_file)=0;
	public:
		virtual void clear()=0;
};

/**
 * @class World
 * @brief A világ osztály leírása.
 *
 * Tárolja az erőforrásokat, embereket, entitásokat, a terepet.
 * Rendelkezik a szimulációhoz tartozó methódusokkal. És kirajzolással is.
 */
class World:public WorldBaseSerialiazble{
	private:
		
		
		int border_width; ///< Ez a változó mondja meg, hogy a kamera mennyi pixelt mehet jobbra.
		int border_height; ///< Ez a változó mondja meg, hogy a kamera mennyi pixelt mehet le.
		
		void try_seasonal_cycle(float delta_time); ///< Új szezont szimulál: Új erőforrások, állatok idéződnek be a világba és az emberek ételt fogyasztanak. Ha nincs elég étel, meghalnak.
		float cycle_cooldown; ///< Ez eltárolja, hogy még mennyi idő van a következő szezonig.
		
		void reinitialize_self(bool from_file) override; ///< Újragenerálja a világot. Ha fájl olvasáskor hívják meg, akkor nem idéz embereket,állatokat,erőforrásokat, mert a fájlból úgy is beolvas valamit.
	public:
		/**
		 * @brief Egy getter a horizontális kamera határ nagysághoz.
		 * @return A határ mérete.
		 */
		int get_border_width() const;
		
		/**
		 * @brief Egy getter a vertikális kamera határ nagysághoz.
		 * @return A határ mérete.
		 */
		int get_border_height() const;
		
		/**
		 * @brief Egy setter a horizontális kamera határ nagysághoz.
		 * @param newwidth Az új határ méret.
		 */
		void set_border_width(int newwidth);
		
		/**
		 * @brief Egy setter a vertikális kamera határ nagysághoz.
		 * @param newheight Az új határ méret.
		 */
		void set_border_height(int newheight);
		
		/**
		 * @brief Segédfüggvény a világ törléséhez. Felszabadítja az entitásokat, erőforrásokat.
		 */
		void clear() override;
		
		World(); ///< A világ konstruktora. A konstruktor generál egy alap világot.
		~World(); ///< A világ destruktora. Itt felszabadul minden, ami a világban "van". Emberek, állatok, város, erőforrások.
		
		/**
		 * @brief Kirajzol mindent, ami a világba van.
		 * @param window A játékablak.
		 * @param delta_time Az előző frissítés óta eltelt idő.
		 * @param offx A kamera elmozdulása horizontálisan a felső bal csücsökhöz képest.
		 * @param offy A kamera elmozdulása vertikálisan a felső bal csücsökhöz képest.
		 */
		void draw(sf::RenderWindow& window,float delta_time,int offx, int offy);
		
		/**
		 * @brief Frissíti a világban lévő entitásokat, napszakot, árnyékolást.
		 * @param delta_time Az előző frissítés óta eltelt idő.
		 */
		void update_world(float delta_time);
		
		void regenerate(); ///< Újra épít egy világot az előző világ helyére. Az előző világ tartalmát üríti.
		
		void populate_world(); ///< Idéz entitásokat és fákat, bokrokat a világba. Ha pehhesek az emberek akkor egy gyilkos robot is megjeleneik :(
		
		/**
		 * @brief Kiválaszt egy új szakmát egy embernek. Ha ez az ember építette a várost, király lesz belőle.
		 * @param human_ptr Az ember pointer referenciája, akinek új szakmát kell adni.
		 */
		void try_develop_random_role(creature::Human*& human_ptr);
		
		bool spawn_entity_at_pos(creature::Living* entity); ///< Berak egy entitás pointert már megadott pozícióval a világba.
		bool spawn_human(creature::Human* human); ///< Berak egy ember pointert már megadott pozícióval a világba.
		
};
#endif