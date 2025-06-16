#include "World.hpp"

HumanResources& WorldBase::get_resources() {
	return hr;
}

void WorldBase::remove_structure_at(int x, int y){
	warn_text("Trying to remove structure at: X: "+ std::to_string(x) + " Y: " +std::to_string(y),
		      "Struktúra lerombolására kísérlet itt: X: " +std::to_string(x) + " Y: " +std::to_string(y),2);
	
	for(auto it=structures.begin();it!=structures.end();++it){
		if((*it)->posx==x&&(*it)->posy==y){
			(*it)->play_destroy_sound(sound_player);
			
			minerals::ResourceStructure* c1= (*it);
			c1->harvest();
			
			if(c1->get_needs_remove()==true){
				structures.erase(it);
			}
			return;
		}
	}
}

minerals::Structure* WorldBase::get_structure_type(minerals::MINERAL_TYPE atype) {
	auto it = std::find_if(structures.begin(), structures.end(),
		[atype](minerals::Structure* s) {return s->get_type() == atype;});
	return (it != structures.end()) ? *it : nullptr;
}

sf::Vector2f WorldBase::get_position_nearby_town(){
	int max_tries=GameConfig::get_instance().get_max_spawn_tries();
	int random_x=-1;
	int random_y=-1;
	
	minerals::CityCenter* tcenter=current_city_center;
	if(tcenter!=nullptr){
		do{
			random_x=tcenter->posx-100+RandomGenerator::get_instance().get_random_int(200);
			random_y=tcenter->posy-100+RandomGenerator::get_instance().get_random_int(200);
			if(random_x>terrain.get_width()-MAX_OBJECT_SIZE){
				random_x=terrain.get_width()-MAX_OBJECT_SIZE;
			}
			if(random_y>terrain.get_height()-MAX_OBJECT_SIZE){
				random_y=terrain.get_height()-MAX_OBJECT_SIZE;
			}
			if(random_x<0){
				random_x=0;
			}
			if(random_y<0){
				random_y=0;
			}
			
			if(getTileAt(random_x,random_y).get_type()==tiles::TILETYPE::GRASS){
				max_tries=0;
			}
			--max_tries;
		} while(max_tries>0);
		
		sf::Vector2f pos_vector(random_x,random_y);
		return pos_vector;
		
	} else {
		sf::Vector2f invalid_vector(-1,-1);
		return invalid_vector;
	}
}

creature::Living* WorldBase::get_excluded_entities(creature::ENTITY_TYPE excluded_type){
	std::vector<creature::Living*> potential_targets;
	for(auto it=entities.begin();it!=entities.end();++it){
		if((*it)->get_type()!=excluded_type){
			potential_targets.push_back(*it);
		}
	}
	for(auto it=humans.begin();it!=humans.end();++it){
		if((*it)->get_type()!=excluded_type){
			potential_targets.push_back(*it);
		}
	}
	
	if(!potential_targets.empty()) {
		int randomIndex = RandomGenerator::get_instance().get_random_int(potential_targets.size());
		return potential_targets[randomIndex];
	}
	
	return nullptr;
}

sf::Vector2f WorldBase::get_random_suitable_position(tiles::TILETYPE suitable_tile){
	int max_tries=GameConfig::get_instance().get_max_spawn_tries();
	int random_x=0;
	int random_y=0;
	
	do{
		random_x=RandomGenerator::get_instance().get_random_int(terrain.get_width()-MAX_OBJECT_SIZE);
		random_y=RandomGenerator::get_instance().get_random_int(terrain.get_height()-MAX_OBJECT_SIZE);
		if(getTileAt(random_x,random_y).get_type()==suitable_tile){
			max_tries=0;
		}
		--max_tries;
	} while(max_tries>0);
	
	sf::Vector2f pos_vector(random_x,random_y);
	return pos_vector;
}

void WorldBase::build_city_center_at(int x, int y){
	if(current_city_center==nullptr){
		current_city_center=new minerals::CityCenter(x,y);
		warn_text("Built new city center at: X: " +std::to_string(x) +" Y: " +std::to_string(y),
				  "Új városközpont épült itt: X: " +std::to_string(x) +" Y: " +std::to_string(y),3);
	} else {
		throw CityCenterException("Egy új városközpont jött létre pedig már létezik egy!");
	}
	hr.add_resources("wood",10);
	hr.add_resources("food",10);
	hr.add_resources("stone",10);
	sound_player.play_sound("src/sfx/metal_hit1.wav");
	//Új emberek idézése a városhoz
	camp_needs_spawn=true;
	
}

sf::Vector2f WorldBase::get_random_house_pos(){
	if(!houses.empty()) {
		int randomIndex = RandomGenerator::get_instance().get_random_int(houses.size());
		sf::Vector2f pos_vector(houses[randomIndex]->posx,houses[randomIndex]->posy);
		return pos_vector;
	}

	sf::Vector2f invalid_vector(-1,-1);
	return invalid_vector;
	
}
minerals::CityCenter* WorldBase::get_current_city_center(){
	if(current_city_center==nullptr){
		return nullptr;
		warn_text(
			"No current city center found!",
			"Nem található jelenlegi városközpont!",
			3
		);
	} else {
		return current_city_center;
	}
}

void WorldBase::upgrade_house_at(int x,int y){
	for(auto it=houses.begin();it!=houses.end();++it){
		if((*it)->posx==x && (*it)->posy==y){
			if((*it)->try_upgrade(hr)==true){
				return;
			}
		}
	}
	
	houses.push_back(new minerals::House(x,y));
	warn_text(
		"Build new house at: X: " + std::to_string(x) + " Y: " + std::to_string(y),
		"Új ház építése itt: X: " + std::to_string(x) + " Y: " + std::to_string(y),
		3
	);
}

tiles::Tile& WorldBase::getTileAt(int x, int y) const{
	return *(terrain[y/terrain.TILE_SIZE][x/terrain.TILE_SIZE]);
}