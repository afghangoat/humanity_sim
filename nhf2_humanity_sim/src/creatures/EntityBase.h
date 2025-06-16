#ifndef ENTITYBASE_HPP
#define ENTITYBASE_HPP

#include "EntityUtils.h"
#include "../Utils.h"

namespace creature{
	
	/**
	 * @class EntityBase
	 * @brief Egy alap, nem rajzolható entitás osztálya.
	 *
	 * Ebbe az alap entitás leírása van, kivéve a kirajzoláshoz való dolgok.
	 */
	class EntityBase{
		protected:
			float max_age; ///< Az entitás maximum életkora. Ha ezt eléri meghal.
			ENTITY_GENDER gender; ///< Az entitás neme.
			LIVINGSTATE state; ///< Az entitás belső állapota.
			FACING facing; ///< Jobbra vagy balra néz az entitás.
			
			int health; ///< Még mennyi élete maradt az entitásnak. Ha ez <=0 akkor meghal az entitás.
			float hit_timer=0.0f; ///< Ha megütik az entitást, akkor egy piros szín effektet kap, ez a változó mutatja, hogy még meddig legyen rajta ez az effekt.
			float inner_timer; ///< Az entitás születése óta eltelt idő.
			float speed; ///< Milyen gyorsan sétál az entitás (1 delta idő alatt).
			float run_speed_modifier; ///< Milyen gyorsan fut az entitás (1 delta idő alatt).
			
			LivingTexture texture_data;
			
			float death_timer=0.1f; ///< A halál animáció hátralévő idejét méri. Ha ez 0 akkor az entitás felszabadul és megsemmisül.
			std::string save_name="?"; ///< Milyen szimbóluma legyen a mentés fájlba.
		public:
			const std::string& get_save_name() const; ///< Getter a mentés szimbólumra.
			void set_save_name(const std::string& s); ///< Setter a mentés szimbólumra.
			/**
			 * @brief Visszaadja az entitás nemét.
			 * @return Az entitás neme.
			 */
			ENTITY_GENDER get_gender() const;
			/**
			 * @brief Visszaadja az entitás belső állapotát.
			 * @return Az entitás belső állapota.
			 */
			LIVINGSTATE get_state() const;
			float get_death_timer() const; ///< Getter a death_timer-re
			double posx; ///< Az entitás X pozíciója.
			double posy; ///< Az entitás Y pozíciója.
			
			virtual void set_state(LIVINGSTATE newstate)=0;
			
			/**
			 * @brief Visszaadja az entitás belső szimbólumát. Ez abba segít, hogy a vadállatok példáúl csak embert támadjanak, Az emberek csak vadállatot.
			 * @return A belső szimbólum.
			 */
			virtual ENTITY_TYPE get_type() const=0;
			
			/**
			 * @brief Beállítja az entitás életét ez bizonyos értékre.
			 * @param amm Az új életpont szám.
			 */
			void set_health(int amm);
			void apply_age(); ///< Megnézi, hogy hány éves az entitás, ha már meg kell halnia akkor meghal.
			
			virtual void die()=0; ///< Mi történjen, ha meghal az entitás.
			virtual ~EntityBase(); ///< Virtuális destruktor.
			
			/**
			 * @brief Frissíti az entitás "semmit nem csináló" textúráját.
			 * @param new_str Az új textúra elérési útvonala.
			 */
			void set_idle_texture(std::string new_str);
			/**
			 * @brief Frissíti az entitás "támadó" textúráját.
			 * @param new_str Az új textúra elérési útvonala.
			 */
			void set_attack_texture(std::string new_str);
			/**
			 * @brief Frissíti az entitás "sétáló" textúráját.
			 * @param new_str Az új textúra elérési útvonala.
			 */
			void set_walk_texture(std::string new_str);
			/**
			 * @brief Frissíti az entitás "futó" textúráját.
			 * @param new_str Az új textúra elérési útvonala.
			 */
			void set_run_texture(std::string new_str);
			/**
			 * @brief Frissíti az entitás "elhalálozó" textúráját.
			 * @param new_str Az új textúra elérési útvonala.
			 */
			void set_death_texture(std::string new_str);
	};
}

#endif