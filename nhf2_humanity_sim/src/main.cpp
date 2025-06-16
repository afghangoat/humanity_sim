#include "GameManager.h"

#include "GameConfig.h"
#include "World.hpp"
#include "TextureManager.h"
#include "Random_Gen.h"
#include <filesystem>

#include "external/modified_gtest_lite.h"

//#define JPORTA_INPUT_SIM  // Jporta std in szimuláció

int main(){
	/*
	Az alap tesztek készen vannak és a dinamikus tesztek is, van olyan teszt, ami az egész világot szimulálja egy kicsit. Ez magába nem determinisztikus, de olyan dolgokat tesztelek benne, amik azok.
	*/
	#ifndef FAKE_SFML
		//A szimulációs program teljes működéséhez való hívások:
		GameConfig::get_instance().read_from_config_file("mod_config.yml");
		GameManager game;
		game.run();
		
	#else
		
		#ifdef MEMTRACE
			#define MEMTRACE_FIX //Ha memtrace-vel kell tesztelni
		#endif
		
		//Tesztek
		GTINIT(std::cin);
		
		/*TEST(Szivargas, lol){
			int* a = new int[3];
			std::cout << a <<"|\n";
		} ENDM*/
		
		//Lefutott-e a menedzser konstruktor rendesen?
		TEST(GameManager, konstruktor) {
			GameManager game;
			EXPECT_TRUE(game.is_valid());
			
		} ENDM
		
		//Megnézi, hogy nem-e keletkezett-e hiba és nem-e volt hibás a szimulálás
		TEST(GameManager, szimulalas) {
			GameManager game2;
			for(int i=0;i<10;i++){
				EXPECT_NO_THROW(game2.simulate_tick(0.5f)); //Fél másodperces frame szimulálása.
			}
			EXPECT_TRUE(game2.is_valid());
			EXPECT_EQ(5.0f, game2.get_elapsed_time());
			
		} ENDM
		
		//Világ tesztelése, hogy az adatok stimmelnek-e.
		TEST(World, adatok) {
			World w1;
			void* nptr=nullptr;
			
			//Az elején nem kéne, hogy legyen semmilyen erőforrása az embereknek.
			EXPECT_FALSE(w1.get_resources().is_there_enough_resource("Stone",1));
			EXPECT_FALSE(w1.get_resources().is_there_enough_resource("Iron",1));
			EXPECT_FALSE(w1.get_resources().is_there_enough_resource("Wood",1));
			EXPECT_FALSE(w1.get_resources().is_there_enough_resource("Food",1));
			
			//Az elején nincs városközpont, ezt kell is ellenőrizni.
			EXPECT_EQ(nptr, w1.get_current_city_center());
			
			//Csak akkor működik az új határ beállítás, ha nem negatív az új érték.
			w1.set_border_width(23);
			w1.set_border_height(23);
			
			//Itt működnie kéne:
			EXPECT_EQ(23, w1.get_border_width());
			EXPECT_EQ(23, w1.get_border_height());
			
			EXPECT_THROW(w1.set_border_width(-1),InvalidBorderSizeException);
			EXPECT_THROW(w1.set_border_height(-1),InvalidBorderSizeException);
			
		} ENDM
		
		//Megnézi, hogy épülhet-e több városközpont (NEM)
		TEST(World, varoskozpont) {
			World w1;
			
			EXPECT_NO_THROW(w1.build_city_center_at(20,20));
			
			EXPECT_THROW(w1.build_city_center_at(20,20),CityCenterException) << "Már van központ";
			
			sf::Vector2f i=w1.get_position_nearby_town();
			sf::Vector2f invalid;
			invalid.x=-1.0f;
			invalid.y=-1.0f;
			EXPECT_TRUE(i.x != invalid.x && i.y != invalid.y) << "Már van központ";
			
		} ENDM
		
		//Szabad a semmit lerombolni, nem kéne hiba
		TEST(World, varoskozpont rombolas) {
			World w1;
			
			EXPECT_NO_THROW(w1.get_resources().add_resources("stone",100));
			EXPECT_NO_THROW(w1.get_resources().add_resources("iron",100));
			EXPECT_NO_THROW(w1.get_resources().add_resources("wood",100));
			EXPECT_NO_THROW(w1.get_resources().add_resources("food",100));
			
			EXPECT_NO_THROW(w1.upgrade_house_at(20,20));
			
			EXPECT_NO_THROW(w1.remove_structure_at(20,20)) << "Nem kéne hibát dobnia.";
			
		} ENDM
		
		//Entitások:
		TEST(Human, adatok es konstruktor) {
			//Az emberek alapbeállításainak ellenőrzése.
			creature::Human* h1 = new creature::Human(10,10);
			creature::Human* h2 = new creature::Human(13,10);
			
			//Nem szabad egyenlőnek lenniük.
			EXPECT_NE(h1,h2);
			
			//Amíg a világ nem frissíti őket, nem szabadna se királlyá akarniuk lenni sem más szakmát választani.
			EXPECT_FALSE(h2->needs_to_be_royal) << "Még nem kéne királlyá koronázódnia a 2. embernek";
			EXPECT_FALSE(h1->needs_to_be_royal) << "Még nem kéne királlyá koronázódnia a 1. embernek";
			EXPECT_FALSE(h2->needs_promotion) << "Még nem kéne új szakmát kérnie az embernek";
			EXPECT_FALSE(h1->needs_promotion) << "Még nem kéne új szakmát kérnie az embernek";
			
			//Az ember szakmájának a szimbóluma eleinte üresnek kell lennie, mert nincs szakmája.
			EXPECT_STREQ("empty", h1->get_profession_string().c_str()) << "Most idéződött le az ember, nem kéne még szakmát kérnie.";
			EXPECT_STREQ("empty", h2->get_profession_string().c_str()) << "Most idéződött le az ember, nem kéne még szakmát kérnie.";
			
			TextureManager::getInstance().clear();
			delete h1;
			delete h2;
			
		} ENDM
		
		TEST(Human, allapot) {
			creature::Human* h1 = new creature::Human(10,10);
			//Semmit nem szabadna csinálnia még. Hiszen most született meg.
			bool state_eq=h1->get_state()==creature::LIVINGSTATE::IDLE;
			EXPECT_TRUE(state_eq) << "Most idéződött le az ember, nem kéne még semmit se csinálnia.";
			
			//Megváltozik-e a működés az embernek, ha meghal?
			h1->die();
			bool state2_eq=h1->get_state()==creature::LIVINGSTATE::DEATH;
			EXPECT_TRUE(state2_eq) << "Az embernek halottnak kell lennie.";
			
			TextureManager::getInstance().clear();
			delete h1;
			
		} ENDM
		
		TEST(Human, allapot2) {
			creature::Human* h1 = new creature::Human(10,10,creature::ENTITY_GENDER::FEMALE);
			creature::Human* h2 = new creature::Human(10,5,creature::ENTITY_GENDER::MALE);
			
			//Helyesen be lett-e állítva az emberek neme a konstruktorba?
			bool h1_gender_eq=h1->get_gender()==creature::ENTITY_GENDER::FEMALE;
			bool h2_gender_eq=h2->get_gender()==creature::ENTITY_GENDER::MALE;
			EXPECT_TRUE(h1_gender_eq);
			EXPECT_TRUE(h2_gender_eq);
			
			TextureManager::getInstance().clear();
			delete h1;
			delete h2;
			
		} ENDM
		
		TEST(Entitas, szimbolum) {
			creature::Human* h1 = new creature::Human(10,10,creature::ENTITY_GENDER::FEMALE);
			
			EXPECT_STREQ(h1->get_save_name().c_str(),"Human") << "Az ember mentés szimbóluma helytelen";
			EXPECT_NO_THROW(h1->set_save_name("UJ"));
			
			EXPECT_STREQ(h1->get_save_name().c_str(),"UJ") << "Meg kellett volna változnia.";
			
			EXPECT_THROW(h1->set_save_name(""),ImportInvalidHumanProfessionException);
			
			TextureManager::getInstance().clear();
			delete h1;
			
		} ENDM
		
		//Emberek tesztelése egy világba:
		TEST(AnglerMiner, viselkedes) {
			creature::Human* h1 = new creature::AnglerMiner(10,10,creature::ENTITY_GENDER::FEMALE);
			
			World w1;
			for(size_t i=0;i<4;i++){
				EXPECT_NO_THROW(h1->update_logic(w1,0.1f)) << "Hibás viselkedéses szimulációs működés.";
			}
			
			TextureManager::getInstance().clear();
			delete h1;
			
		} ENDM
		
		TEST(Farmer, viselkedes) {
			creature::Human* h1 = new creature::Farmer(10,10,creature::ENTITY_GENDER::FEMALE);
			
			World w1;
			for(size_t i=0;i<4;i++){
				EXPECT_NO_THROW(h1->update_logic(w1,0.1f)) << "Hibás viselkedéses szimulációs működés.";
			}
			
			TextureManager::getInstance().clear();
			delete h1;
			
		} ENDM
		
		TEST(Builder, viselkedes) {
			creature::Human* h1 = new creature::Builder(10,10,creature::ENTITY_GENDER::FEMALE);
			
			World w1;
			for(size_t i=0;i<4;i++){
				EXPECT_NO_THROW(h1->update_logic(w1,0.1f)) << "Hibás viselkedéses szimulációs működés.";
			}
			
			TextureManager::getInstance().clear();
			delete h1;
			
		} ENDM
		
		TEST(Fisherman, viselkedes) {
			creature::Human* h1 = new creature::Fisherman(10,10,creature::ENTITY_GENDER::FEMALE);
			
			World w1;
			for(size_t i=0;i<4;i++){
				EXPECT_NO_THROW(h1->update_logic(w1,0.1f)) << "Hibás viselkedéses szimulációs működés.";
			}
			
			TextureManager::getInstance().clear();
			delete h1;
			
		} ENDM
		
		TEST(King, viselkedes) {
			creature::Human* h1 = new creature::King(10,10,creature::ENTITY_GENDER::FEMALE);
			
			World w1;
			for(size_t i=0;i<4;i++){
				EXPECT_NO_THROW(h1->update_logic(w1,0.1f)) << "Hibás viselkedéses szimulációs működés.";
			}
			
			TextureManager::getInstance().clear();
			delete h1;
			
		} ENDM
		
		TEST(Soldier, viselkedes) {
			creature::Human* h1 = new creature::Soldier(10,10,creature::ENTITY_GENDER::FEMALE);
			
			World w1;
			for(size_t i=0;i<4;i++){
				EXPECT_NO_THROW(h1->update_logic(w1,0.1f)) << "Hibás viselkedéses szimulációs működés.";
			}
			
			TextureManager::getInstance().clear();
			delete h1;
			
		} ENDM
		
		TEST(Woodcutter, viselkedes) {
			creature::Human* h1 = new creature::Woodcutter(10,10,creature::ENTITY_GENDER::FEMALE);
			
			World w1;
			for(size_t i=0;i<4;i++){
				EXPECT_NO_THROW(h1->update_logic(w1,0.1f)) << "Hibás viselkedéses szimulációs működés.";
			}
			
			TextureManager::getInstance().clear();
			delete h1;
			
		} ENDM
		
		TEST(Stonemason, viselkedes) {
			creature::Human* h1 = new creature::Stonemason(10,10,creature::ENTITY_GENDER::FEMALE);
			
			World w1;
			for(size_t i=0;i<4;i++){
				EXPECT_NO_THROW(h1->update_logic(w1,0.1f)) << "Hibás viselkedéses szimulációs működés.";
			}
			
			TextureManager::getInstance().clear();
			delete h1;
			
		} ENDM
		
		//A gyilkos robot tesztje, meg kell nézni, hogy ellenséges-e az emberekkel szemben?
		TEST(KillerRobot, adatok es mukodes) {
			World w1;
			creature::Human* h1= new creature::Human(20,20);
			creature::KillerRobot* r1 = new creature::KillerRobot(13,10);

			//Ez egy mechanikus egység, annak is kell lennie. (Fájl mentés szimbólum check)
			bool is_type_eq=r1->get_type()==creature::ENTITY_TYPE::ROBOTIC;
			EXPECT_TRUE(is_type_eq) << "A robotnak mechanikus entitásnak kéne lennie.";
			
			EXPECT_NO_THROW(r1->set_hostile_config(5.0,4.0f));
			
			for(size_t i=0;i<4;i++){
				EXPECT_NO_THROW(r1->update_logic(w1,0.1f)) << "Hibás viselkedéses szimulációs működés.";
			}
			
			r1->retarget(h1);
			EXPECT_TRUE(r1->check_aggroed()!=nullptr) << "Az előbb támadott meg egy embert";
			
			r1->select_target(w1);
			//Meg akarja-e ölni az egyik embert?
			bool is_null=r1->check_aggroed()==nullptr;
			EXPECT_FALSE(is_null);
			
			TextureManager::getInstance().clear();
			delete h1;
			delete r1;
			
		} ENDM
		
		TEST(KillerRobot, halal) {
			creature::KillerRobot* r1 = new creature::KillerRobot(13,10);
			
			//Megváltozik-e rendesen a belső állapot halálnál?
			r1->die();
			bool is_state_death=r1->get_state()==creature::LIVINGSTATE::DEATH;
			EXPECT_TRUE(is_state_death);
			
			TextureManager::getInstance().clear();
			delete r1;
			
		} ENDM
		
		//A medve tesztje, meg kell nézni, hogy ellenséges-e a többi élőlénnyel szemben. szemben?
		TEST(Bear, adatok es mukodes) {
			World w1;
			creature::Bear* b1 = new creature::Bear(199,10);
			
			for(size_t i=0;i<4;i++){
				EXPECT_NO_THROW(b1->update_logic(w1,0.1f)) << "Hibás viselkedéses szimulációs működés.";
			}
			
			//Ez biológikus egység, annak is kell lennie. (Fájl mentés szimbólum check)
			bool is_type_good=b1->get_type()==creature::ENTITY_TYPE::ANIMAL;
			EXPECT_TRUE(is_type_good) << "A medvének állat szimbólumú entitásnak kéne lennie.";
			
			EXPECT_NO_THROW(b1->set_hostile_config(5.0,4.0f));
			
			b1->select_target(w1);
			//Meg akarja-e ölni az egyik állatot/embert
			bool is_null=b1->check_aggroed()==nullptr;
			EXPECT_FALSE(is_null);
			
			TextureManager::getInstance().clear();
			delete b1;
			
		} ENDM
		
		TEST(Bear, halal) {
			creature::Bear* b1 = new creature::Bear(199,10);
			
			//Megváltozik-e rendesen a belső állapot halálnál?
			b1->die();
			bool is_state_death=b1->get_state()==creature::LIVINGSTATE::DEATH;
			EXPECT_TRUE(is_state_death);
			
			TextureManager::getInstance().clear();
			delete b1;
			
		} ENDM
		
		//A krokodil tesztje, meg kell nézni, hogy ellenséges-e a többi élőlénnyel szemben. szemben?
		TEST(Crocodile, adatok es mukodes) {
			World w1;
			creature::Crocodile* b1 = new creature::Crocodile(199,180);
			
			for(size_t i=0;i<4;i++){
				EXPECT_NO_THROW(b1->update_logic(w1,0.1f)) << "Hibás viselkedéses szimulációs működés.";
			}
			
			//Ez biológikus egység, annak is kell lennie. (Fájl mentés szimbólum check)
			bool is_type_good=b1->get_type()==creature::ENTITY_TYPE::ANIMAL;
			EXPECT_TRUE(is_type_good) << "A medvének állat szimbólumú entitásnak kéne lennie.";
			
			EXPECT_NO_THROW(b1->set_hostile_config(5.0,4.0f));
			
			b1->select_target(w1);
			//Meg akarja-e ölni az egyik állatot/embert
			bool is_null=b1->check_aggroed()==nullptr;
			EXPECT_FALSE(is_null);
			
			TextureManager::getInstance().clear();
			delete b1;
			
		} ENDM
		
		TEST(Crocodile, halal) {
			creature::Crocodile* b1 = new creature::Crocodile(199,108);
			
			//Megváltozik-e rendesen a belső állapot halálnál?
			b1->die();
			bool is_state_death=b1->get_state()==creature::LIVINGSTATE::DEATH;
			EXPECT_TRUE(is_state_death);
			
			TextureManager::getInstance().clear();
			delete b1;
			
		} ENDM
		
		TEST(Goat, adatok es mukodes) {
			creature::Goat* b1 = new creature::Goat(199,108);
			
			bool is_type_good=b1->get_type()==creature::ENTITY_TYPE::ANIMAL;
			EXPECT_TRUE(is_type_good) << "A medvének állat szimbólumú entitásnak kéne lennie.";
			
			//Megváltozik-e rendesen a belső állapot halálnál?
			b1->die();
			bool is_state_death=b1->get_state()==creature::LIVINGSTATE::DEATH;
			EXPECT_TRUE(is_state_death);
			
			TextureManager::getInstance().clear();
			delete b1;
			
		} ENDM
		
		//Terepkocka tesztje, rendesen állítja be-e a dolgokat a konstruktor?
		TEST(Tile, konstruktor es texturak1) {
			
			tiles::Tile* t1=new tiles::Tile();
			EXPECT_NO_THROW(t1->init(tiles::TILETYPE::GRASS)) << "Rendesen történt-e a terepkocka textúra beolvasása? Hiányzik a képfájl?";
			bool is_t1_good=t1->get_type()==tiles::TILETYPE::GRASS;
			EXPECT_TRUE(is_t1_good) << "A konstruktor rendesen elmentette az adatokat";
			
			
			TextureManager::getInstance().clear();
			delete t1;
			
		} ENDM
		
		TEST(Tile, konstruktor es texturak2) {
			
			tiles::Tile* t2=new tiles::Tile();
			EXPECT_NO_THROW(t2->init(tiles::TILETYPE::MOUNTAIN)) << "Rendesen történt-e a terepkocka textúra beolvasása? Hiányzik a képfájl?";
			bool is_t2_good=t2->get_type()==tiles::TILETYPE::MOUNTAIN;
			EXPECT_TRUE(is_t2_good) << "A konstruktor rendesen elmentette az adatokat";
			
			TextureManager::getInstance().clear();
			delete t2;
			
		} ENDM
		
		TEST(Tile, konstruktor es texturak3) {
			
			tiles::Tile* t3=new tiles::Tile();
			EXPECT_NO_THROW(t3->init(tiles::TILETYPE::WATER)) << "Rendesen történt-e a terepkocka textúra beolvasása? Hiányzik a képfájl?";
			bool is_t3_good=t3->get_type()==tiles::TILETYPE::WATER;
			EXPECT_TRUE(is_t3_good) << "A konstruktor rendesen elmentette az adatokat";
			
			
			TextureManager::getInstance().clear();
			delete t3;
			
		} ENDM
		
		//A textúra kezelő tesztje:
		TEST(TextureManager, mukodik a textura kezelo) {
			sf::Texture* test_texture=TextureManager::getInstance().loadTexture("src/textures/vignette2.png"); //Egy létező fájlból textúra betöltése.
			sf::Texture* nulltext=nullptr;
			//Ha sikeres, akkor nem nullptr az érték. Ennek sikeresnek kell lennie.
			EXPECT_NE(nulltext,test_texture);
			
			TextureManager::getInstance().clear();
			test_texture=nullptr;
			
		} ENDM
		
		//A YAML feldolgozó tesztje
		TEST(YAMLParser, betoltes es feldolgozas) {
			YAMLParser parser;
			
			bool success1=parser.parse_file("nemletezohuihihuih.yml");
			EXPECT_FALSE(success1) << "Ennek nem kéne lefutni, mert nem létezik a file";
			
			bool success2=parser.parse_file("mod_config.yml");
			EXPECT_TRUE(success2) << "Ennek kéne lefutni, mert létezik a file";
			
			std::string entry1= parser.get_value_of_key("target_fps");
			bool ok1=entry1=="INVALID";
			EXPECT_FALSE(ok1) << "Ez egy valid token, el kéne fogadnia.";
			
			std::string entry2= parser.get_value_of_key("blablabla");
			bool ok2=entry2=="INVALID";
			EXPECT_TRUE(ok2) << "Ez egy nemvalid token, nem kéne elfogadnia.";

			std::filesystem::path file_path("example.yml");
			if (std::filesystem::exists("example.yml")) {
				std::filesystem::remove("example.yml");
			}

			EXPECT_TRUE(parser.try_generate_config_file("example.yml"));
			EXPECT_FALSE(parser.try_generate_config_file("example.yml")) << "Már van";
			
		} ENDM
		
		//A zene lejátszó tesztje.
		TEST(MusicPlayer, hang betoltese) {
			MusicPlayer m1;
			
			//Egy rendes fájl beolvasás
			EXPECT_NO_THROW(m1.load_music("src/sfx/click.wav"));
			//Egy nem létező fájl beolvasás
			EXPECT_THROW(m1.load_music("blabla/blabla.mm"), MusicLoadException);
		} ENDM
		
		//A hang lejátszó tesztje.
		TEST(SoundPlayer, hang betoltese es lejatszas) {
			SoundPlayer player;
    
			EXPECT_NO_THROW(player.play_sound("src/sfx/click.wav")) << "Ha létezik a hang akkor nem kéne hibát adni.";
		} ENDM
		
		TEST(SoundPlayer, megallitas) {
			SoundPlayer player;
			player.play_sound("src/sfx/click.wav");
			EXPECT_NO_THROW(player.stop_sound()) << "Nem kéne hibát adnia.";
		} ENDM
		
		//A TerrainContainer tesztje.
		TEST(TerrainContainer, alap meret) {
			TerrainContainer<tiles::Tile*> terulet;
			terulet.clear();
			terulet.resize<tiles::Tile>(3,3);

			// Méretek ellenőrzése
			EXPECT_EQ(terulet.get_width(), 3*32);
			EXPECT_EQ(terulet.get_height(), 3*32);
			
			bool wasnullptr=false;
			if(terulet[0][0]==nullptr||terulet[2][2]==nullptr){
				wasnullptr=true;
				break;
			}
			
			EXPECT_FALSE(wasnullptr) << "Nem jól let a terrain container adata incializálva.";

			// Érték??
			EXPECT_NE(terulet[0][0], terulet[1][0]) << "Nem kéne 2 azonos pointernek lennie.";
		} ENDM
		
		//A PostProcesser tesztjei.
		TEST(PostProcesser, vizualisok metodusok) {
			PostProcesser p;
			
			EXPECT_NO_THROW(p.toggle_vignette(false)) << "Nem szabadna hibát dobnia, valami roszul lett inicialiálva.";
			EXPECT_NO_THROW(p.toggle_vignette(true)) << "Nem szabadna hibát dobnia, valami roszul lett inicialiálva.";
			
			EXPECT_NO_THROW(p.toggle_noise(false)) << "Nem szabadna hibát dobnia, valami roszul lett inicialiálva.";
			EXPECT_NO_THROW(p.toggle_noise(true)) << "Nem szabadna hibát dobnia, valami roszul lett inicialiálva.";
			
			EXPECT_NO_THROW(p.toggle_chromatic_aberration(false)) << "Nem szabadna hibát dobnia, valami roszul lett inicialiálva.";
			EXPECT_NO_THROW(p.toggle_chromatic_aberration(true)) << "Nem szabadna hibát dobnia, valami roszul lett inicialiálva.";
			
		} ENDM
		
		TEST(PostProcesser, renderek) {
			PostProcesser pp;
			
			EXPECT_NO_THROW(pp.setRenderSize(800.0, 600.0)) << "Nem szabadna hibát dobnia, nincs ablak??";
			EXPECT_NO_THROW(pp.setRenderSize(1.0, 1.0)) << "Nem szabadna hibát dobnia, nincs ablak??";
			EXPECT_THROW(pp.setRenderSize(0.0, 0.0),std::runtime_error) << "Ilyen mérettel nem lehet ablak";
			EXPECT_THROW(pp.setRenderSize(-800.0, -600.0),std::runtime_error) << "Ilyen mérettel nem lehet ablak";
			
		} ENDM
		
		TEST(PostProcesser, szinek) {
			PostProcesser pp;
			
			EXPECT_NO_THROW(pp.setColorOverlay(0,0,0,0)) << "Ez jó szín.";
			EXPECT_NO_THROW(pp.setColorOverlay(255,255,255,1)) << "Ez jó szín.";
			
		} ENDM
		
		//A szakma tesztjei
		TEST(Profession, Ctor) {
			Profession p("farmer");
			EXPECT_EQ(p.to_string(), "farmer");
		} ENDM

		TEST(Profession, textura) {
			Profession p("farmer");
			// Provide a valid path to an image
			EXPECT_TRUE(p.setTexture("src/textures/vignette2.png"));
		} ENDM

		TEST(Profession, textura rossz) {
			Profession p("farmer");
			EXPECT_FALSE(p.setTexture("nonexistent.pngp"));
		} ENDM

		TEST(Profession, nem fagy ki) {
			Profession p("farmer");
			EXPECT_NO_THROW(p.setPosition(100.0, 200.0));
		} ENDM

		TEST(Profession, szimbolum) {
			Profession p("farmer");
			p.load_profession("builder");
			EXPECT_EQ(p.to_string(), "builder");
		} ENDM
		
		//A mentés menedzser tesztje:
		TEST(SaveManager, helyesseg) {
			World w1;
			
			SaveManager manager("testfile.txt");
			EXPECT_NO_THROW(manager.saveFile(w1));
			
		} ENDM
		
		TEST(SaveManager, nem kene mukodni) {
			World w1;
			
			SaveManager manager("testfilebla.txt"); //Nem létező mentés (még nem létezik)
			
			EXPECT_THROW(manager.loadFile(w1),ReadSaveFileFail);
			
			EXPECT_THROW(manager.deleteFile(),ReadSaveFileFail);
			
		} ENDM
		
		TEST(World, serializable) {
			World w1;
			
			w1.build_city_center_at(20,20);
			w1.get_resources().add_resources("stone",100);
			w1.get_resources().add_resources("iron",100);
			w1.get_resources().add_resources("wood",100);
			w1.get_resources().add_resources("food",100);
			
			w1.upgrade_house_at(24,20);
			
			SaveManager manager("testfile.txt"); //Nem létező mentés (még nem létezik)
			EXPECT_NO_THROW(manager.loadFile(w1));
			EXPECT_NO_THROW(manager.saveFile(w1));
			
		} ENDM
		
		//Gomb tesztje:
		TEST(Button, konstruktor) {
			ui::Button btn(100, 200, 50, 30, "src/textures/vignette2.png");

			EXPECT_NO_THROW(btn.setPosition(150, 250));
		} ENDM
		
		TEST(Button, callback) {
			ui::Button btn(0, 0, 100, 100, "src/textures/vignette2.png");

			bool called = false;
			btn.setCallback([&called]() { called = true; });

			btn.try_hover_animation(50, 50);
			btn.onClick(true);

			EXPECT_TRUE(called);
		} ENDM
		
		TEST(Button, textura) {
			ui::Button btn(0, 0, 50, 50, "src/textures/vignette2.png");

			EXPECT_NO_THROW(btn.setTexture("src/textures/png_all_vignette.png"));
		} ENDM
		
		//Az erőforrások tesztje is itt van.
		
		//Bokor tesztjei:
		TEST(BerryBush, konstruktor es tipus) {
			minerals::BerryBush bush(5, 10);
			bool is_t_eq=bush.get_type()==minerals::MINERAL_TYPE::FOOD;
			EXPECT_TRUE(is_t_eq);
		} ENDM

		TEST(BerryBush, kitermeles) {
			minerals::BerryBush bush(0, 0);
			bool first = bush.harvest();
			EXPECT_TRUE(first);

			bool second = bush.harvest();
			EXPECT_FALSE(second) << "Már nincs mit kitermelni!";
		} ENDM

		TEST(BerryBush, visszanoves) {
			minerals::BerryBush bush(0, 0);
			bush.harvest();

			bush.update_logic(3600.0f);
			bool canHarvestAgain = bush.harvest();

			EXPECT_TRUE(canHarvestAgain)<<"Idő elteltével vissza kéne nőnie a bokor termésének.";
		} ENDM

		TEST(BerryBush, nem tellt el ido) {
			minerals::BerryBush bush(0, 0);
			bush.harvest();

			bush.update_logic(0.1f);
			bool canHarvestAgain = bush.harvest();

			EXPECT_FALSE(canHarvestAgain) << "Nem tellt el még elég idő";
		} ENDM
		
		//Fa tesztjei
		TEST(Tree, konstruktor es tipus) {
			minerals::Tree tree(5, 10);
			bool is_t_eq=tree.get_type()==minerals::MINERAL_TYPE::WOOD;
			EXPECT_TRUE(is_t_eq);
		} ENDM

		TEST(Tree, kitermeles) {
			minerals::Tree tree(0, 0);
			bool first = tree.harvest();
			EXPECT_TRUE(first);

			bool second = tree.harvest();
			EXPECT_FALSE(second) << "Már nincs mit kitermelni!";
		} ENDM
		
		//Kő tesztjei
		TEST(Stone, konstruktor es tipus) {
			minerals::Stone stone(5, 10);
			bool is_t_eq=stone.get_type()==minerals::MINERAL_TYPE::STONE;
			EXPECT_TRUE(is_t_eq);
		} ENDM

		TEST(Stone, kitermeles) {
			minerals::Stone stone(0, 0);
			bool first = stone.harvest();
			EXPECT_TRUE(first);

			bool second = stone.harvest();
			EXPECT_FALSE(second) << "Már nincs mit kitermelni!";
		} ENDM
		
		//Vas tesztjei.
		TEST(Iron, konstruktor es tipus) {
			minerals::Iron iron(5, 10);
			bool is_t_eq=iron.get_type()==minerals::MINERAL_TYPE::IRON;
			EXPECT_TRUE(is_t_eq);
			
		} ENDM

		TEST(Iron, kitermeles) {
			minerals::Iron iron(0, 0);
			bool first = iron.harvest();
			EXPECT_TRUE(first);

			bool second = iron.harvest();
			EXPECT_FALSE(second) << "Már nincs mit kitermelni!";
		} ENDM
		
		//Ház tesztje:
		TEST(House, konstruktor es mukodes) {
			minerals::House h(0, 0);
			bool is_t_eq=h.get_type()==minerals::MINERAL_TYPE::HOUSING;
			EXPECT_TRUE(is_t_eq);
			
			EXPECT_NO_THROW(h.update_logic(0.1f));
		} ENDM
		
		//CITY_CENTER tesztje
		TEST(CityCenter, konstruktor es mukodes) {
			minerals::CityCenter h(0, 0);
			bool is_t_eq=h.get_type()==minerals::MINERAL_TYPE::CITY_CENTER;
			EXPECT_TRUE(is_t_eq);
			
			EXPECT_NO_THROW(h.update_logic(0.1f));
			EXPECT_NO_THROW(h.register_new_house());
			for(size_t i=0;i<14;i++){
				h.register_new_house();
			}
			EXPECT_TRUE(h.is_there_room_for_housing());
			EXPECT_THROW(h.register_new_house(),StructureException) << "Nem kéne beférnie.";
			
			EXPECT_FALSE(h.is_there_room_for_housing());
		} ENDM
		
		//Living inteface teszje:
		TEST(Living, konstruktor es mukodes) {
			creature::Human l(2,2);
			EXPECT_TRUE(l.needs_drawn()) << "Olyan helyen van, ahol meg kell jeleníteni.";
			
			EXPECT_NO_THROW(l.set_death_texture("src/textures/png_all_vignette.png"));
			EXPECT_NO_THROW(l.set_run_texture("src/textures/png_all_vignette.png"));
			EXPECT_NO_THROW(l.set_walk_texture("src/textures/png_all_vignette.png"));
			EXPECT_NO_THROW(l.set_attack_texture("src/textures/png_all_vignette.png"));
			EXPECT_NO_THROW(l.set_idle_texture("src/textures/png_all_vignette.png"));
			
			EXPECT_NO_THROW(l.update_spritesheet(0.1f));
			EXPECT_NO_THROW(l.setPosition(0.0,0.0));
			EXPECT_NO_THROW(l.look_right());
			EXPECT_NO_THROW(l.look_left());
			EXPECT_NO_THROW(l.init_spritesheet_data(6,6.0));
			
			EXPECT_NO_THROW(l.setTheShadow("src/textures/png_all_vignette.png"));
			EXPECT_NO_THROW(l.setTexture("src/textures/png_all_vignette.png"));
			
		} ENDM
		
		TEST(Living, sebzodes) {
			creature::Human l(2,2);
			
			EXPECT_NO_THROW(l.set_health(100.0f));
			EXPECT_NO_THROW(l.damage(nullptr,6.0f));
			bool is_t_eq=l.get_state()==creature::LIVINGSTATE::DEATH;
			EXPECT_FALSE(is_t_eq) << "Ilyen kicsi sebzéstől nem kellene meghalnia.";
		} ENDM
		
		TEST(Shadowable, ertekek) {
			creature::Human l(2,2);
			
			EXPECT_NO_THROW(l.set_height_offset(0.0));
			EXPECT_NO_THROW(l.set_shadow_strength(0));
			EXPECT_NO_THROW(l.set_skew_offset(0));
			
			EXPECT_EQ(l.get_height_offset(),0.0);
			EXPECT_EQ(l.get_shadow_strength(),0);
			EXPECT_EQ(l.get_skew_offset(),0);
		} ENDM
		
		TEST(Living, belso mukodes) {
			creature::Human l(2,2);
			
			EXPECT_NO_THROW(l.set_state(creature::LIVINGSTATE::DEATH));
			bool is_t_eq=l.get_state()==creature::LIVINGSTATE::DEATH;
			EXPECT_TRUE(is_t_eq) << "Igaznak kell lennie mert beállítottuk.";
			
		} ENDM
		
		//Entitás lerakó tesztje
		TEST(EntityPlacer, mukodes es konstruktor){
			EntityPlacer p1;
			
			//Ki-be kapcsolás
			EXPECT_NO_THROW(p1.toggle_placing());
			EXPECT_NO_THROW(p1.toggle_placing());
			
			EXPECT_FALSE(p1.spacePreviouslyPressed) << "Még nem nyomtunk meg semmit.";
			
			EXPECT_NO_THROW(p1.select_entity(4));
			
			EXPECT_NO_THROW(p1.select_entity(0));
			
			EXPECT_THROW(p1.select_entity(-2),std::runtime_error);
			
		} ENDM
		
		//SFML helyettesítő könyvtár elvárt, hogy helyesen működjön.
		
		
		GTEND(std::cerr);
	#endif
	
	return 0;
}