#include "GameManager.h"

GameManager::GameManager(){
	warn_text(
		"GameManager Constructor called!",
		"GameManager Konstruktor meghívva!",
		1
	);
	
	Clock.restart();
	delta_time=0.0f;
	mouse_clicked=false;
	paused=false;
	mouse_pos.x=-1;
	mouse_pos.y=-1;
	view_offset_x=0;
	view_offset_y=0;
	
	window=new sf::RenderWindow(sf::VideoMode(GameConfig::get_instance().get_screen_width(), GameConfig::get_instance().get_screen_height()), "Humanity Simulator");
	window->setFramerateLimit(GameConfig::get_instance().get_target_fps());
	
	world=new World();
	processer=new PostProcesser();
	processer->setRenderSize(GameConfig::get_instance().get_screen_width(), GameConfig::get_instance().get_screen_height());
	processer->setColorOverlay(255, 204, 102,30);
	processer->toggle_vignette(true);
	
	if(GameConfig::get_instance().is_chromatic_aberration()==true){
		processer->toggle_chromatic_aberration(true);
	}
	if(GameConfig::get_instance().is_noise()==true){
		processer->toggle_noise(true);
	}
	
	setup_buttons();
	music_player.load_music("src/sfx/ambient_music_1.wav");
	music_player.set_volume(10.0f);
	
	save_manager=new SaveManager("save_data.dat");
	valid=true;
	
	entity_placer=new EntityPlacer();
}

GameManager::~GameManager(){
	if(buttons.size()>0){
		for (ui::Button* btn : buttons) {
			delete btn;
		}
	}
	
	//buttons.clear();
	
	if (world != nullptr) {
		delete world;
		world=nullptr;
	}
	if (save_manager != nullptr) {
		delete save_manager;
		save_manager=nullptr;
	}
	if (processer != nullptr) {
		delete processer;
		processer=nullptr;
	}
	TextureManager::getInstance().clear();
	if (window != nullptr) {
		delete window;
		window=nullptr;
	}
	if(entity_placer!=nullptr){
		delete entity_placer;
		entity_placer=nullptr;
	}
}

void GameManager::run(){
	warn_text(
		"GameManager Run called!",
		"GameManager Futtatás meghívva!",
		1
	);
	view_offset_x=0;
	view_offset_y=0;
	
	game_loop();
}

void GameManager::game_loop(){
	while (window->isOpen()==true) {
        sf::Event event;
        while (window->pollEvent(event)==true) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
        }
		
		
		simulate_tick(0.0f);
		
    }
}
void GameManager::simulate_tick(float e_time){
	if(e_time==0.0f){
		delta_time = Clock.getElapsedTime().asSeconds();
		Clock.restart();
	} else {
		delta_time+=e_time;
	}
	handle_inputs();

	if(paused==false){
		world->update_world(delta_time);
	}
	update_buttons();
	
	draw_world();
}
bool GameManager::is_valid() const{
	return valid;
}
float GameManager::get_elapsed_time() const{
	return delta_time;
}

void GameManager::handle_inputs(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		view_offset_x-=camera_speed;
		int check_boundary_value=world->get_border_width();
		if(view_offset_x<-check_boundary_value){
			view_offset_x=-check_boundary_value;
		}
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		view_offset_x+=camera_speed;
		
		if(view_offset_x>0){
			view_offset_x=0;
		}
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		
		view_offset_y-=camera_speed;
		int check_boundary_value=world->get_border_height();
		if(view_offset_y<-check_boundary_value){
			view_offset_y=-check_boundary_value;
		}
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		view_offset_y+=camera_speed;
		if(view_offset_y>0){
			view_offset_y=0;
		}
	}
	mouse_pos = sf::Mouse::getPosition(*window);
	mouse_clicked = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	
	handle_unit_placement();
}

bool GameManager::handle_unit_placement(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (entity_placer->spacePreviouslyPressed==false) {
            entity_placer->toggle_placing();
            entity_placer->spacePreviouslyPressed = true;
        }
    } else {
        entity_placer->spacePreviouslyPressed = false;
    }
	
	static const sf::Keyboard::Key numKeys[10] = {
		sf::Keyboard::Num0, sf::Keyboard::Num1, sf::Keyboard::Num2,
		sf::Keyboard::Num3, sf::Keyboard::Num4, sf::Keyboard::Num5,
		sf::Keyboard::Num6, sf::Keyboard::Num7, sf::Keyboard::Num8,
		sf::Keyboard::Num9
	};

	for (int i = 0; i < 10; ++i) {
		if (sf::Keyboard::isKeyPressed(numKeys[i])) {
			entity_placer->select_entity(i);
			break;
		}
	}
	
	if(mouse_clicked==true){
		sf::Vector2i spawn_pos = sf::Vector2i(-view_offset_x,-view_offset_y);
		spawn_pos.x+=mouse_pos.x;
		spawn_pos.y+=mouse_pos.y;
		
		return entity_placer->try_place_entity(spawn_pos,*world);
	} else {
		entity_placer->reset_mouse();
	}
	return false;
}

void GameManager::draw_world(){
	window->clear(sf::Color::Black);
	
	world->draw(*window,delta_time,view_offset_x,view_offset_y);
	draw_buttons();
	
	processer->draw(*window);//Itt
	window->display();
}

void GameManager::setup_buttons(){
	const std::string ui_paths="src/textures/ui/";
	
	buttons.push_back(new ui::Button(4,4,32,32,ui_paths+"regenerate.png"));
	buttons[0]->setCallback([this](){
		world->regenerate();
		sound_player.play_sound("src/sfx/explosion.wav");
	});
	
	buttons.push_back(new ui::Button(4+32,4,32,32,ui_paths+"load_data.png"));
	buttons[1]->setCallback([this](){
		save_manager->loadFile(*world);
		view_offset_x=0;
		view_offset_y=0;
		sound_player.play_sound("src/sfx/squish.wav");
	});
	
	buttons.push_back(new ui::Button(4+32*2,4,32,32,ui_paths+"save.png"));
	buttons[2]->setCallback([this](){
		save_manager->saveFile(*world);
		sound_player.play_sound("src/sfx/squish.wav");
	});
	
	buttons.push_back(new ui::Button(4+32*3,4,32,32,ui_paths+"del_save.png"));
	buttons[3]->setCallback([this](){
		save_manager->deleteFile();
		sound_player.play_sound("src/sfx/explosion.wav");
	});
	
	buttons.push_back(new ui::Button(4+32*4,4,32,32,ui_paths+"sound.png"));
	buttons[4]->setCallback([this](){
		music_player.toggle_music();
		sound_player.play_sound("src/sfx/click.wav");
	});
	
	buttons.push_back(new ui::Button(4+32*5,4,32,32,ui_paths+"pause.png"));
	buttons[5]->setCallback([this](){
		paused=!paused;
		sound_player.play_sound("src/sfx/click.wav");
	});
}

void GameManager::update_buttons(){
	if(mouse_pos.x!=-1&&mouse_pos.y!=-1){
		for(auto it = buttons.begin();it!=buttons.end();++it){
			(*it)->try_hover_animation(mouse_pos.x,mouse_pos.y);
			(*it)->onClick(mouse_clicked);
		}
	}
	
}
void GameManager::draw_buttons(){
	for(auto it = buttons.begin();it!=buttons.end();++it){
		(*it)->draw(*window);
	}
}