#include "EntityPlacer.h"

void ObjectRegistry::register_type(int id, SpawnFunc func) {
	factory_map[id] = std::move(func);
}

bool ObjectRegistry::spawn(int id,World& world,sf::Vector2i& epos) const {
	auto it = factory_map.find(id);
	if (it != factory_map.end()) {
		return it->second(world,epos);
	} else {
		warn_text(
			"Unknown entity id: " + std::to_string(id),
			"Ismeretlen entitás azonosító: " + std::to_string(id),
			3
		);
		return false;
	}
}

EntityPlacer::EntityPlacer(){
	placing=false;
	spacePreviouslyPressed=false;
	reset_mouse();
	setup_factory();
}

bool EntityPlacer::setup_factory() {
    factory.register_type(0, [&](World& world, sf::Vector2i epos) {
        return world.spawn_human(new creature::Human(epos.x, epos.y));
    });

    factory.register_type(1, [&](World& world, sf::Vector2i epos) {
        auto* temp = new creature::Bear(epos.x, epos.y);
        temp->set_save_name("Bear");
        return world.spawn_entity_at_pos(temp);
    });

    factory.register_type(2, [&](World& world, sf::Vector2i epos) {
        auto* temp = new creature::Goat(epos.x, epos.y);
        temp->set_save_name("Goat");
        return world.spawn_entity_at_pos(temp);
    });

    factory.register_type(3, [&](World& world, sf::Vector2i epos) {
        auto* temp = new creature::KillerRobot(epos.x, epos.y);
        temp->set_save_name("Robot");
        return world.spawn_entity_at_pos(temp);
    });

    factory.register_type(4, [&](World& world, sf::Vector2i epos) {
        auto* temp = new creature::Crocodile(epos.x, epos.y);
        temp->set_save_name("Crocodile");
        return world.spawn_entity_at_pos(temp);
    });

    factory.register_type(5, [&](World& world, sf::Vector2i epos) {
        world.spawn_structure_at<minerals::BerryBush>(epos.x, epos.y);
        return true;
    });

    factory.register_type(6, [&](World& world, sf::Vector2i epos) {
        world.spawn_structure_at<minerals::Iron>(epos.x, epos.y);
        return true;
    });

    factory.register_type(7, [&](World& world, sf::Vector2i epos) {
        world.spawn_structure_at<minerals::Tree>(epos.x, epos.y);
        return true;
    });

    factory.register_type(8, [&](World& world, sf::Vector2i epos) {
        world.spawn_structure_at<minerals::Stone>(epos.x, epos.y);
        return true;
    });

    factory.register_type(9, [&](World& world, sf::Vector2i epos) {
        return world.spawn_human(new creature::King(epos.x, epos.y,creature::ENTITY_GENDER::MALE));
    });
	
	return true;
}

bool EntityPlacer::try_place_entity(sf::Vector2i& epos,World& world){
	warn_text(
		"Trying to place entity at position: X: " + std::to_string(epos.x) + " Y: " + std::to_string(epos.y),
		"Entitás elhelyezési kísérlet itt: X: " + std::to_string(epos.x) + " Y: " + std::to_string(epos.y),
		2
	);
	
	if(placing==true&&current_entity_id!=-1&&mouse_lock==false){
		mouse_lock=true;
		bool success = factory.spawn(current_entity_id,world,epos);
		return success;
	}
	return false;
}

void EntityPlacer::toggle_placing(){
	placing=!placing;
}

void EntityPlacer::select_entity(int new_id){
	if(new_id<0){
		throw std::runtime_error("Nincs negatív entitás azonosító.");
	}
	current_entity_id=new_id;
}

void EntityPlacer::reset_mouse(){
	mouse_lock=false;
}