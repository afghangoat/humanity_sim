#include "World.hpp"

std::ostream& operator<<(std::ostream& os, WorldBaseSerialiazble& w){
	auto serialize_obj = [](std::ostream& os, const std::string& name, int x, int y, const std::string& extra = "?") {
        os << '<' << name << ';' << x << ';' << y << ';' << extra << ";>|";
    };
	//1. Sor
	os << w.saved_size << '|' << w.elapsed_time << '|' <<w.terrain.get_seed() << '\n';
	
	//2. Sor
	auto& res = w.get_resources();
	os << res.get_count_from("iron") << '|' << res.get_count_from("stone") << '|' << res.get_count_from("food") << '|' << res.get_count_from("wood") << '\n';
	
	//3. Sor
	for (auto* e : w.entities)
        serialize_obj(os, e->get_save_name(), e->posx, e->posy);
    for (auto* h : w.humans)
        serialize_obj(os, h->get_save_name(), h->posx, h->posy, h->get_profession_string());
    os << '\n';
	
	//4. Sor
	for (auto* house : w.houses)
        serialize_obj(os, "House", house->posx, house->posy, std::to_string(house->get_level()));
    for (auto* s : w.structures)
        serialize_obj(os, minerals::mineral_to_string(s->get_type()), s->posx, s->posy);
	
    if (w.current_city_center){
        serialize_obj(os, "CITY_CENTER", w.current_city_center->posx, w.current_city_center->posy);
	}
	
	os << '\n';
	return os;
}

bool WorldBaseSerialiazble::process_creature_chunk(const std::string& chunk) {
    auto content = SaveHelper::trim_brackets(chunk);
    std::istringstream ss(content);
    std::string name, x_str, y_str, tag;
    if (std::getline(ss, name, ';') && std::getline(ss, x_str, ';') && std::getline(ss, y_str, ';') && std::getline(ss, tag, ';')) {
        int px = std::stoi(x_str), py = std::stoi(y_str);
        auto gender = RandomGenerator::get_instance().get_random_int(2) == 0 ? creature::ENTITY_GENDER::MALE : creature::ENTITY_GENDER::FEMALE;

        if (name == "Human") {
            auto it = SaveHelper::getHumanFactory().find(tag);
            if (it == SaveHelper::getHumanFactory().end()) throw ImportInvalidHumanProfessionException(tag.c_str());
            auto* h = it->second(px, py, gender);
            h->posx = px;
            h->posy = py;
            humans.push_back(h);
        } else {
            auto it = SaveHelper::getCreatureFactory().find(name);
            if (it == SaveHelper::getCreatureFactory().end()) throw ImportInvalidEntityException(name.c_str());
            auto* e = it->second(px, py);
            e->posx = px;
            e->posy = py;
            entities.push_back(e);
        }
    }
	return true;
}

bool WorldBaseSerialiazble::process_structure_chunk(const std::string& chunk) {
    auto content = SaveHelper::trim_brackets(chunk);
    std::istringstream ss(content);
    std::string name, x_str, y_str;
    if (std::getline(ss, name, ';') &&std::getline(ss, x_str, ';') &&std::getline(ss, y_str, ';')) {
        int px = std::stoi(x_str), py = std::stoi(y_str);

        if (name == "HOUSING") {
            std::string level_str;
            if (!std::getline(ss, level_str, ';')) throw ImportInvalidHousingLevelException("Nincs megadott érték");
            int level = std::stoi(level_str);
            auto* house = new minerals::House(px, py);
            house->set_level(level);
            if (level >= 2) {
                house->set_level(level-1);
                house->upgrade_house();
            }

            houses.push_back(house);
        } else if (name == "CITY_CENTER") {
            build_city_center_at(px, py);
            camp_needs_spawn = false;
        } else if (name != "?") {
            auto it = SaveHelper::getResourceFactory().find(name);
            if (it == SaveHelper::getResourceFactory().end()) throw ImportInvalidResourceException(name.c_str());
            auto* s = it->second(px, py);
            structures.push_back(s);
        }
    }
	return true;
}

std::ifstream& operator>>(std::ifstream& in, WorldBaseSerialiazble& w) {
    std::vector<std::string> lines(4);
    for (int i = 0; i < 4; ++i) {
        if (!std::getline(in, lines[i])) throw ReadSaveFileFail("Nem pontos mentés!");
    }
	w.clear();

    auto tokenize = [](const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        std::istringstream ss(str);
        std::string token;
        while (std::getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    };

    // 1. Világ adatai, seed.
    auto meta = tokenize(lines[0], '|');
    if (meta.size() != 3) throw ReadSaveFileFail("Sor formátum nem helyes!");
    w.saved_size = std::stoi(meta[0]);
    w.elapsed_time = std::stod(meta[1]);
    int new_seed = std::stoi(meta[2]);

    w.terrain.set_seed(new_seed);
    w.reinitialize_self(true);

    // 2. Erőforrások.
    auto res = tokenize(lines[1], '|');
    if (res.size() != 4) throw ReadSaveFileFail("Sor formátum nem helyes!");
    w.get_resources().set_resources("iron", std::stoi(res[0]));
    w.get_resources().set_resources("stone", std::stoi(res[1]));
    w.get_resources().set_resources("food", std::stoi(res[2]));
    w.get_resources().set_resources("wood", std::stoi(res[3]));

    // 3. Entitások és emberek.
    for (const auto& chunk : tokenize(lines[2], '|')) {
		w.process_creature_chunk(chunk);
	}

    // 4. Struktúrák és kitermelni valók.
    for (const auto& chunk : tokenize(lines[3], '|')) {
		w.process_structure_chunk(chunk);
	}

    return in;
}