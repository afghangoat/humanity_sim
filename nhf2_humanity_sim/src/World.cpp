#include "World.hpp"

void World::reinitialize_self(bool from_file){
	cycle_cooldown=300.0f;
	current_city_center=nullptr;
	if(saved_size==-1){
		saved_size=GameConfig::get_instance().get_world_size();
	}
	terrain.resize<tiles::Tile>(saved_size,saved_size);
	terrain.generate_world();
	
	border_width=std::max(0,terrain.get_width()-GameConfig::get_instance().get_screen_width());
	border_height=std::max(0,terrain.get_height()-GameConfig::get_instance().get_screen_height());
	
	if(from_file==false){
		humans.push_back(new creature::Human(100,100));
		
		populate_world();
	}
	
	elapsed_time=0.0f;
	camp_needs_spawn=false;
}

World::World(){
	reinitialize_self(false);
}

World::~World(){
	clear();
}

void World::regenerate(){
	clear();
	reinitialize_self(false);
}

void World::clear(){
	for (auto iter : entities) {
		delete iter;
	}
	entities.clear();
	for (auto iter : humans) {
		if(iter!=nullptr){
			delete iter;
		}
		
	}
	humans.clear();
	if(current_city_center!=nullptr){
		delete current_city_center;
		current_city_center=nullptr;
	}
	for (auto iter : houses) {
		delete iter;
	}
	houses.clear();
	for (auto iter : structures) {
		delete iter;
	}
	structures.clear();
	elapsed_time=0.0f;
	camp_needs_spawn=false;
	get_resources().set_resources("iron",0);
	get_resources().set_resources("stone",0);
	get_resources().set_resources("food",0);
	get_resources().set_resources("wood",0);
	
	terrain.set_seed(-1);
	terrain.clear();
}

void World::draw(sf::RenderWindow& window,float delta_time,int offx, int offy){
	terrain.draw(window,offx,offy);
	
	for(auto it=structures.begin();it!=structures.end();++it){
		(*it)->draw_logic(window,elapsed_time,offx,offy);
	}
	for(auto it=houses.begin();it!=houses.end();++it){
		(*it)->draw_logic(window,elapsed_time,offx,offy);
	}
	
	if(current_city_center!=nullptr){
		current_city_center->draw_logic(window,elapsed_time,offx,offy);
	}
	for(auto it=entities.begin();it!=entities.end();++it){
		(*it)->draw_logic(window,delta_time,offx,offy);
		(*it)->shadow_logic(window,elapsed_time,offx,offy);
	}
	for(auto it=humans.begin();it!=humans.end();++it){
		(*it)->draw_logic(window,delta_time,offx,offy);
		(*it)->shadow_logic(window,elapsed_time,offx,offy);
	}
	
}

void World::update_world(float delta_time){
	elapsed_time+=delta_time;
	
	for(auto it=structures.begin();it!=structures.end();++it){
		(*it)->update_logic(delta_time);
	}
	for(auto it=houses.begin();it!=houses.end();++it){
		(*it)->update_logic(delta_time);
	}
	if(current_city_center!=nullptr){
		current_city_center->update_logic(delta_time);
	}
	
	for(auto it=entities.begin();it!=entities.end();){
		(*it)->update_logic(*this,delta_time);
		(*it)->apply_age();
		if ((*it)->get_death_timer() < 0.0f) {
			delete *it;
			it = entities.erase(it);
		} else {
			++it;
		}
	}
	for(auto it=humans.begin();it!=humans.end();){
		(*it)->update_logic(*this,delta_time);
		(*it)->apply_age();
		if((*it)->needs_promotion==true){
			try_develop_random_role((*it));
		}
		if ((*it)->get_death_timer() < 0.0f) {
			delete *it;
			it = humans.erase(it);
		} else {
			++it;
		}
	}
	
	if(camp_needs_spawn==true){
		camp_needs_spawn=false;
		for(int i=0;i<5;i++){
			sf::Vector2f random_pos=get_position_nearby_town();
			humans.push_back(new creature::Human(random_pos.x,random_pos.y));
		}
	}
	
	
	try_seasonal_cycle(delta_time);
	
}
void World::try_seasonal_cycle(float delta_time){
	cycle_cooldown-=delta_time;
	if(cycle_cooldown>0.0f){
		return;
	}
	
	cycle_cooldown=300.0f;
	
	for(auto it=humans.begin();it!=humans.end();++it){
		if(get_resources().is_there_enough_resource("food",1)==true){
			get_resources().remove_resources("food",1);
		} else {
			(*it)->set_state(creature::LIVINGSTATE::DEATH);
		}
	}
	
	//Szaporodás szimulálása, ha van még elő ember.
	if(!humans.empty()) {
		double new_human_count=1.0;
		for(auto it=houses.begin();it!=houses.end();++it){
			new_human_count+=((*it)->get_level())*0.15;
		}
		for(int i=0;i<new_human_count;i++){
			sf::Vector2f random_pos=get_position_nearby_town();
			humans.push_back(new creature::Human(random_pos.x,random_pos.y));
		}
	}
	
	populate_world();
}

void World::populate_world(){
	for(int i=0;i<GameConfig::get_instance().get_resource_scarcity();i++){
		spawn_structure<minerals::BerryBush>(false);
		spawn_structure<minerals::BerryBush>(false);
		spawn_structure<minerals::Tree>(false);
		spawn_structure<minerals::Iron>(true);
		spawn_structure<minerals::Stone>(true);
		
		spawn_entity<creature::Goat>(tiles::TILETYPE::MOUNTAIN,"Goat");
	}
	for(int i=0;i<GameConfig::get_instance().get_hostiles_count();i++){
		switch(RandomGenerator::get_instance().get_random_int(3)){
			case 0:
				spawn_entity<creature::Crocodile>(tiles::TILETYPE::WATER,"Crocodile");
				break;
			case 1:
				spawn_entity<creature::Bear>(tiles::TILETYPE::MOUNTAIN,"Bear");
				break;
			case 2:
				if(RandomGenerator::get_instance().get_random_int(10)==0){
					spawn_entity<creature::KillerRobot>(tiles::TILETYPE::GRASS,"Robot");
				}
				break;
		}
		
	}
}

bool World::spawn_entity_at_pos(creature::Living* entity){
	if(entity->posx<0||entity->posy<0){
		return false;
	}
	entities.push_back(entity);
	return true;
}
bool World::spawn_human(creature::Human* human){
	if(human->posx<0||human->posy<0){
		return false;
	}
	humans.push_back(human);
	return true;
}

void World::try_develop_random_role(creature::Human*& human_ptr){
	int tempx=human_ptr->posx;
	int tempy=human_ptr->posy;
	creature::ENTITY_GENDER temp_gender=human_ptr->get_gender();
	bool needsroyal=human_ptr->needs_to_be_royal;
	bool needs_retargeting=false;
	creature::Living* old_ptr=human_ptr;
	
	if(needsroyal==true){
		human_ptr=new creature::King(tempx,tempy,temp_gender);
		needs_retargeting=true;
		warn_text("A human became the king at: X: " + std::to_string(tempx) + " Y: " + std::to_string(tempy),"Egy ember lett a király itt: X: " + std::to_string(tempx) + " Y: " + std::to_string(tempy),3);
	} else {
		int profession_selector=RandomGenerator::get_instance().get_random_int(SaveHelper::get_roles().size());
		const auto& role = SaveHelper::get_roles()[profession_selector];

		bool has_resources = true;
		for (const auto& [res, amount] : role.requirements) {
			if (get_resources().is_there_enough_resource(res, amount)==false) {
				has_resources = false;
				break;
			}
		}
		if (has_resources==true) {
			for (const auto& [res, amount] : role.requirements) {
				get_resources().remove_resources(res, amount);
			}
			human_ptr = role.create(tempx,tempy,temp_gender);
			needs_retargeting=true;
			warn_text( "A human got a new profession at: X: " + std::to_string(tempx) + " Y: " + std::to_string(tempy), "Egy ember új foglalkozást kapott itt: X: " + std::to_string(tempx) + " Y: " + std::to_string(tempy), 3);
		}
	}
	if(needs_retargeting==true){
		warn_text("Retargeting hostile entity targets.", "Ellenséges entitások célpontjainak újracélzása.", 3);
		for(auto it=entities.begin();it!=entities.end();++it)
			if ((*it)->check_aggroed() == old_ptr) (*it)->retarget(human_ptr);
		
	}
	if (old_ptr != nullptr && old_ptr != human_ptr) {
        delete old_ptr;
        old_ptr = nullptr;
    }
}

int World::get_border_width() const{
	return border_width;
}
int World::get_border_height() const{
	return border_height;
}
void World::set_border_width(int newwidth){
	if(newwidth<=1){
		throw InvalidBorderSizeException("Nem lehet negatív a határ szélesség!");
	} else {
		border_width=newwidth;
	}
	
}
void World::set_border_height(int newheight){
	if(newheight<=1){
		throw InvalidBorderSizeException("Nem lehet negatív a határ magasság!");
	} else {
		border_height=newheight;
	}
}

//FOR WorldBase

template<typename T>
void WorldBase::spawn_structure(bool mountain_exclusive){
	int max_tries=GameConfig::get_instance().get_max_spawn_tries();
	int random_x=-1;
	int random_y=-1;
	
	do{
		random_x=RandomGenerator::get_instance().get_random_int(terrain.get_width()-MAX_OBJECT_SIZE);
		random_y=RandomGenerator::get_instance().get_random_int(terrain.get_height()-MAX_OBJECT_SIZE);
		
		tiles::TILETYPE current_type=getTileAt(random_x,random_y).get_type();
		if(mountain_exclusive==true){ //Ores
			if(current_type==tiles::TILETYPE::MOUNTAIN){
				max_tries=0;
			}
		} else if(current_type==tiles::TILETYPE::GRASS){
			max_tries=0;
		}
		
		--max_tries;
	} while(max_tries>0);
	
	if(random_x!=-1||random_y!=-1){
		spawn_structure_at<T>(random_x,random_y-MAX_OBJECT_SIZE);
	}
}

template<typename T>
void WorldBase::spawn_entity(tiles::TILETYPE goal_habitat, const std::string& savefile_identifier){
	int max_tries=GameConfig::get_instance().get_max_spawn_tries();
	int random_x=-1;
	int random_y=-1;
	
	do{
		random_x=RandomGenerator::get_instance().get_random_int(terrain.get_width()-MAX_OBJECT_SIZE);
		random_y=RandomGenerator::get_instance().get_random_int(terrain.get_height()-MAX_OBJECT_SIZE);
		
		tiles::TILETYPE current_type=getTileAt(random_x,random_y).get_type();
		if(current_type==goal_habitat){
			max_tries=0;
		}
		
		--max_tries;
	} while(max_tries>0);
	
	if(random_x!=-1||random_y!=-1){
		entities.push_back(new T(random_x,random_y-MAX_OBJECT_SIZE));
		entities[entities.size()-1]->set_save_name(savefile_identifier);
	}
}