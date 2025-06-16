#ifndef HUMANRESOURCES_HPP
#define HUMANRESOURCES_HPP

#include <string>
#include <unordered_map>

/**
 * @class HumanResources
 * @brief Az emberek által összegyűjtött erőforrások itt vannak nyilvántartva.
 *
 */
class HumanResources{
	private:
		std::unordered_map<std::string, int> resources; ///< Egy map, ami tárolja az erőforrásokat, amiket az emberek termeltek és azt, hogy mennyit. Fa, Kő, Étel és Vas.
	public:
		/**
		 * @brief Az emberek által gyűjtött erőforrásokhoz hozzáad egy típusból valamennyit.
		 * @param what Mit adjon hozzá.
		 * @param amount Mennyit adjon hozzá.
		 */
		void add_resources(const std::string& what, int amount);
		/**
		 * @brief Az emberek által gyűjtött erőforrásokból kiszed egy típusból valamennyit.
		 * @param what Mit vesz el.
		 * @return Mennyit vegyen el.
		 */
		void remove_resources(const std::string& what, int amount);
		/**
		 * @brief Megnézi, hogy az emberek már szedtek-e elég erőforrást valamiből.
		 * @param from_what Miből kell.
		 * @param needed_amount Mennyi kell, hogy legyen.
		 * @return Ha van elég, akkor igaz, ha nincs akkor hamis.
		 */
		bool is_there_enough_resource(const std::string& from_what, int needed_amount) const;
		
		/**
		 * @brief Beállítja egy erőforrás számát fix értékre.
		 * @param what Miből kell.
		 * @param amount Mennyi kell, hogy legyen.
		 */
		void set_resources(const std::string& what,int amount);
		
		int get_count_from(const std::string& what) const; ///< Visszaadja, hogy mennyi erőforrás van egy bízonyos típusból.
};

#endif