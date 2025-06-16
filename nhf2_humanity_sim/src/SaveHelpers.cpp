#include "SaveHelpers.h"

namespace minerals{
	std::string mineral_to_string(MINERAL_TYPE type) {
		switch (type) {
			case MINERAL_TYPE::STONE:
				return "STONE";
			case MINERAL_TYPE::WOOD:
				return "WOOD";
			case MINERAL_TYPE::IRON:
				return "IRON";
			case MINERAL_TYPE::FOOD:
				return "FOOD";
			case MINERAL_TYPE::HOUSING:
				return "HOUSING";
			case MINERAL_TYPE::CITY_CENTER:
				return "CITY_CENTER";
			default:
				return "?";
		}
	}
}

namespace creatures{
	
}

const std::unordered_map<std::string, SaveHelper::CreatureFactory> SaveHelper::creature_factory = {
    {"Crocodile", [](int x, int y) {
        auto* temp = new creature::Crocodile(x, y);
        temp->set_save_name("Crocodile");
        return temp;
    }},
    {"Robot", [](int x, int y) {
        auto* temp = new creature::KillerRobot(x, y);
        temp->set_save_name("Robot");
        return temp;
    }},
    {"Goat", [](int x, int y) {
        auto* temp = new creature::Goat(x, y);
        temp->set_save_name("Goat");
        return temp;
    }},
    {"Bear", [](int x, int y) {
        auto* temp = new creature::Bear(x, y);
        temp->set_save_name("Bear");
        return temp;
    }}
};

const std::unordered_map<std::string, SaveHelper::HumanFactory> SaveHelper::human_factory = {
    {"empty",        [](int x, int y, creature::ENTITY_GENDER g) { return new creature::Human(x, y, g); }},
    {"?",            [](int x, int y, creature::ENTITY_GENDER g) { return new creature::Human(x, y, g); }},
    {"axe",          [](int x, int y, creature::ENTITY_GENDER g) { return new creature::Woodcutter(x, y, g); }},
    {"bricks",       [](int x, int y, creature::ENTITY_GENDER g) { return new creature::Builder(x, y, g); }},
    {"crown",        [](int x, int y, creature::ENTITY_GENDER g) { return new creature::King(x, y, g); }},
    {"fishing_rod",  [](int x, int y, creature::ENTITY_GENDER g) { return new creature::Fisherman(x, y, g); }},
    {"pickaxe",      [](int x, int y, creature::ENTITY_GENDER g) { return new creature::Stonemason(x, y, g); }},
    {"saw",          [](int x, int y, creature::ENTITY_GENDER g) { return new creature::AnglerMiner(x, y, g); }},
    {"scythe",       [](int x, int y, creature::ENTITY_GENDER g) { return new creature::Farmer(x, y, g); }},
    {"sword",        [](int x, int y, creature::ENTITY_GENDER g) { return new creature::Soldier(x, y, g); }}
};

const std::unordered_map<std::string, SaveHelper::ResourceFactory> SaveHelper::resource_factory = {
    {"FOOD",  [](int x, int y) { return new minerals::BerryBush(x, y); }},
    {"IRON",  [](int x, int y) { return new minerals::Iron(x, y); }},
    {"WOOD",  [](int x, int y) { return new minerals::Tree(x, y); }},
    {"STONE", [](int x, int y) { return new minerals::Stone(x, y); }}
};

const std::vector<RoleOption> SaveHelper::roles = {
	{ [](int x, int y, auto g) { return new creature::Woodcutter(x, y, g); }, {{"wood", 2}, {"stone", 1}} },
	{ [](int x, int y, auto g) { return new creature::Stonemason(x, y, g); }, {{"wood", 2}, {"stone", 2}} },
	{ [](int x, int y, auto g) { return new creature::Farmer(x, y, g); }, {{"wood", 3}, {"food", 1}} },
	{ [](int x, int y, auto g) { return new creature::Fisherman(x, y, g); }, {{"wood", 3}, {"iron", 2}} },
	{ [](int x, int y, auto g) { return new creature::Builder(x, y, g); }, {{"wood", 3}, {"stone", 1}} },
	{ [](int x, int y, auto g) { return new creature::Soldier(x, y, g); }, {{"iron", 2}, {"stone", 1}} },
	{ [](int x, int y, auto g) { return new creature::AnglerMiner(x, y, g); }, {{"iron", 2}, {"stone", 3}} }
};

const std::unordered_map<std::string, SaveHelper::CreatureFactory>& SaveHelper::getCreatureFactory() {
	return creature_factory;
}

const std::unordered_map<std::string, SaveHelper::HumanFactory>& SaveHelper::getHumanFactory() {
	return human_factory;
}

const std::unordered_map<std::string, SaveHelper::ResourceFactory>& SaveHelper::getResourceFactory() {
	return resource_factory;
}
const std::vector<RoleOption>& SaveHelper::get_roles(){
	return roles;
}

std::string SaveHelper::trim_brackets(const std::string& s) {
	return (s.size() >= 2 && s.front() == '<' && s.back() == '>') ? s.substr(1, s.size() - 2) : s;
}