#include "fake_sfml.h"

namespace sf {
	inline std::string to_string(const Color& c) {
		return "Color(" + std::to_string(c.r) + ", " + std::to_string(c.g) + ", " + std::to_string(c.b) + ", " + std::to_string(c.a) + ")";
	}

	inline bool file_exists_at_path(const std::string& name) {
		std::ifstream file(name);
		return file.good();
	}

	Vector2f::Vector2f() : x(0.0f), y(0.0f) {
		log_text("[Vector2f] Default constructed (0, 0)", "[Vector2f] Alapértelmezett konstruktor (0, 0)");
	}

	Vector2f::Vector2f(float x1, float y1) : x(x1), y(y1) {
		log_text("[Vector2f] Constructed (" + std::to_string(x) + ", " + std::to_string(y) + ")",
				 "[Vector2f] Létrehozva (" + std::to_string(x) + ", " + std::to_string(y) + ")");
	}

	Vector2i::Vector2i() : x(0), y(0) {
		log_text("[Vector2i] Default constructed (0, 0)",
				 "[Vector2i] Alapértelmezett konstruktor (0, 0)");
	}

	Vector2i::Vector2i(int x1, int y1) : x(x1), y(y1) {
		log_text("[Vector2i] Constructed (" + std::to_string(x) + ", " + std::to_string(y) + ")",
				 "[Vector2i] Létrehozva (" + std::to_string(x) + ", " + std::to_string(y) + ")");
	}

	Texture::Texture() {
		log_text("[Texture] Default constructor called.",
				 "[Texture] Alapértelmezett konstruktor meghívva.");
	}
	
	Texture::~Texture(){
		log_text("[Texture] Default destructor called.",
				 "[Texture] Alapértelmezett destructor meghívva.");
	}
	
	Vector2i Texture::getSize(){
		Vector2i mock_size(20,20);
		return mock_size;
	}

	IntRect::IntRect() : left(0), top(0), width(0), height(0) {}

	IntRect::IntRect(int l, int t, int w, int h): left(l), top(t), width(w), height(h) {}

	bool Texture::loadFromFile(const std::string& filepath) {
		if (file_exists_at_path(filepath) == false) {
			log_text("[Texture] File at specified location not found: " + filepath,
					 "[Textúra] A megadott helyen nem található a fájl: " + filepath);
			return false;
		}
		if (!path_name.empty()) {
			log_text("[Texture] Replacing old texture (" + path_name + ") with " + filepath,
					 "[Textúra] A régi textúra lecserélése (" + path_name + ") erre: " + filepath);
		} else {
			log_text("[Texture] Loading texture from file: " + filepath,
					 "[Textúra] Textúra betöltése a fájlból: " + filepath);
		}

		path_name = filepath;

		log_text("[Texture] File valid and loaded successfully.",
				 "[Textúra] A fájl érvényes és sikeresen betöltve.");
		return true;
	}
	Texture::Texture(const Texture& other) {
        path_name = other.path_name;
    }

    Texture& Texture::operator=(const Texture& other) {
        if (this != &other) {
            path_name = other.path_name;
        }
        return *this;
    }

	Sprite::Sprite() {
		log_text("[Sprite] Created empty sprite",
				 "[Sprite] Üres sprite létrehozva");
		
		position.x=0;
		position.y=0;
		scale.x=0;
		scale.y=0;
		origin.x=0;
		origin.y=0;
		rotation=0.0f;
	}
	
	Vector2f Sprite::getPosition(){
		return position;
	}
	
	FloatRect Sprite::getLocalBounds(){
		FloatRect b1(position.x,position.y,70*scale.x,70*scale.y);
		return b1;
	}
	
	FloatRect Sprite::getGlobalBounds(){
		FloatRect b1(position.x,position.y+rotation,90*scale.x,90*scale.y);
		return b1;
	}
	
	FloatRect Sprite::getGlobalBounds() const{
		return FloatRect(position.x,position.y,scale.x,scale.y);
	}
	
	void Sprite::setTexture( Texture& tex) {
		log_text("[Sprite] Texture set",
				 "[Sprite] Textúra beállítva");
		texture = tex;
	}

	void Sprite::setTextureRect(const IntRect& tex) {
		log_text("[Sprite] Texture set to intrect at left: " + std::to_string(tex.left) + 
				 " top: " + std::to_string(tex.top),
				 "[Sprite] Textúra beállítva intrect-re: bal = " + std::to_string(tex.left) +
				 " felső = " + std::to_string(tex.top));
	}

	void Sprite::setPosition(float x, float y) {
		position = Vector2f(x, y);
		log_text("[Sprite] Position set to (" + std::to_string(x) + ", " + std::to_string(y) + ")",
				 "[Sprite] Pozíció beállítva erre: (" + std::to_string(x) + ", " + std::to_string(y) + ")");
	}

	void Sprite::setScale(float sx, float sy) {
		scale = Vector2f(sx, sy);
		log_text("[Sprite] Scale set to (" + std::to_string(sx) + ", " + std::to_string(sy) + ")",
				 "[Sprite] Skála beállítva erre: (" + std::to_string(sx) + ", " + std::to_string(sy) + ")");
	}

	void Sprite::draw() const {
		log_text("[Sprite] Drawing sprite at (" + std::to_string(position.x) + ", " + std::to_string(position.y) +
				 ") with scale (" + std::to_string(scale.x) + ", " + std::to_string(scale.y) + ")",
				 "[Sprite] Sprite kirajzolása itt: (" + std::to_string(position.x) + ", " + std::to_string(position.y) +
				 ") ezzel a skálával: (" + std::to_string(scale.x) + ", " + std::to_string(scale.y) + ")");
	}
	
	Sprite::~Sprite(){
		log_text("[Sprite] Destructor called",
				 "[Sprite] Destruktor meghívva");
	}
	void Sprite::setOrigin(float _x, float _y){
		origin.x=_x;
		origin.y=_y;
	}
	void Sprite::setRotation(float deg){
		rotation=deg;
	}
	Texture* Sprite::getTexture(){
		return &texture;
	}

	Event::Event() : type(NoEvent) {
		
	}
	
	ClockTime::ClockTime(std::size_t atime): time_ticks(atime){
		
	}
	ClockTime::ClockTime(): time_ticks(0){
		
	}
	float ClockTime::asSeconds(){
		return time_ticks/60.0;
	}
	void ClockTime::reset(){
		time_ticks=0;
	}
	void ClockTime::increment(){
		time_ticks++;
	}
	
	void Clock::restart(){
		held_time.reset();
	}
	
	ClockTime& Clock::getElapsedTime(){
		for(int i=0;i<10;i++){ //Idő tellésének szimulálása
			held_time.increment();
		}
		return held_time;
	}
	
	bool SoundBuffer::loadFromFile(const std::string& filepath) {
		if (!file_exists_at_path(filepath)) {
			log_text("[SoundBuffer] File at specified location not found: " + filepath,
					 "[SoundBuffer] A megadott helyen nem található a fájl: " + filepath);
			return false;
		}
		data = filepath;
		log_text("[SoundBuffer] Loaded sound file: " + filepath,
				 "[SoundBuffer] Hangfájl betöltve: " + filepath);
		return true;
	}

	void Sound::setBuffer(SoundBuffer& buf) {
		log_text("[Sound] Buffer set",
				 "[Sound] Puffer beállítva");
		buffer = &buf;
	}

	void Sound::play() {
		log_text("[Sound] Playing sound...",
				 "[Sound] Hang lejátszása...");
	}

	void Sound::stop() {
		log_text("[Sound] Stopping sound...",
				 "[Sound] Hang leállítása...");
	}
	
	Sound::~Sound(){
		buffer=nullptr;
		
	}
	
	Music::Music(){
		playing_file="";
		db=1.0;
		playing=false;
	}
	void Music::setLoop(bool newval){
		looping=newval;
	}
	void Music::setVolume(double new_db){
		db=new_db;
	}
	SoundSource::SoundSourceType Music::getStatus(){
		if(playing==true){
			return SoundSource::Playing;
		} else {
			return SoundSource::Stopped;
		}
	}
	void Music::play() {
		log_text("[Music] Playing music...",
				 "[Music] Zene lejátszása...");
	}

	void Music::stop() {
		log_text("[Music] Stopping music...",
				 "[Music] Zene leállítása...");
	}

	bool Music::openFromFile(const std::string& filepath) {
		log_text("[Music] Trying to open file... " + filepath,
				 "[Music] Fájl megnyitása: " + filepath);

		if (!file_exists_at_path(filepath)) {
			log_text("[Music] File at specified location not found: " + filepath,
					 "[Music] A megadott helyen nem található a fájl: " + filepath);
			return false;
		}

		playing_file = filepath;
		return true;
	}
	
	SoundSource::SoundSource() : type(Stopped) {}
	
	Color::Color(){
		r=0;
		g=0;
		b=0;
		a=255;
	}
	Color::Color(int _r, int _g, int _b){
		r=_r;
		g=_g;
		b=_b;
		a=255;
	}
	Color::Color(int _r, int _g, int _b, int _a){
		r=_r;
		g=_g;
		b=_b;
		a=_a;
	}
	
	const Color Color::Black       = Color(0, 0, 0);
	const Color Color::White       = Color(255, 255, 255);
	const Color Color::Red         = Color(255, 0, 0);
	const Color Color::Green       = Color(0, 255, 0);
	const Color Color::Blue        = Color(0, 0, 255);
	const Color Color::Transparent = Color(0, 0, 0, 0);
	
	void Sprite::setColor(Color _clr) {
		clr = _clr;
		log_text("[Sprite] Set color to " + to_string(_clr),
				 "[Sprite] Szín beállítva: " + to_string(_clr));
	}

	void RectangleShape::setFillColor(Color new_color) {
		selfcolor.r = new_color.r;
		selfcolor.g = new_color.g;
		selfcolor.b = new_color.b;
		selfcolor.a = new_color.a;

		log_text("[RectangleShape] Set color to: " + to_string(selfcolor),
				 "[RectangleShape] Szín beállítva: " + to_string(selfcolor));
	}

	void RectangleShape::setSize(Vector2f newsize) {
		size = newsize;
		log_text("[RectangleShape] Resized to: " + std::to_string(size.x) + " " + std::to_string(size.y),
				 "[RectangleShape] Átméretezve: " + std::to_string(size.x) + " " + std::to_string(size.y));
	}

	void RectangleShape::setPosition(Vector2f newpos) {
		position = newpos;
		log_text("[RectangleShape] Repositioned to: " + std::to_string(position.x) + " " + std::to_string(position.y),
				 "[RectangleShape] Áthelyezve: " + std::to_string(position.x) + " " + std::to_string(position.y));
	}
	
	bool Keyboard::isKeyPressed(Key key) {
		switch (key) {
			case Key::Right:
				return right_key_state;
			case Key::Left:
				return left_key_state;
			case Key::Down:
				return down_key_state;
			case Key::Up:
				return up_key_state;
			case Key::Space:case Key::Num0:case Key::Num1:case Key::Num2:case Key::Num3:case Key::Num4:case Key::Num5:case Key::Num6:case Key::Num7:case Key::Num8:case Key::Num9:
				return up_key_state;
				break;
		}
		return false;
	}

	void Keyboard::simulate_key_press(Key key) {
		switch (key) {
			case Key::Right:
				right_key_state = true;
				break;
			case Key::Left:
				left_key_state  = true;
				break;
			case Key::Down:
				down_key_state  = true;
				break;
			case Key::Up:
				up_key_state    = true;
				break;
			case Key::Space:case Key::Num0:case Key::Num1:case Key::Num2:case Key::Num3:case Key::Num4:case Key::Num5:case Key::Num6:case Key::Num7:case Key::Num8:case Key::Num9:
				log_text("[Keyboard] Number key pressed",
						 "[Keyboard] Szám lenyomva");
				break;
		}
	}

	void Keyboard::simulate_key_release(Key key) {
		switch (key) {
			case Key::Right:
				right_key_state = false;
				break;
			case Key::Left:
				left_key_state  = false;
				break;
			case Key::Down:
				down_key_state  = false;
				break;
			case Key::Up:
				up_key_state    = false;
				break;
			case Key::Space:case Key::Num0:case Key::Num1:case Key::Num2:case Key::Num3:case Key::Num4:case Key::Num5:case Key::Num6:case Key::Num7:case Key::Num8:case Key::Num9:
				log_text("[Keyboard] Number key released",
						 "[Keyboard] Szám felemelve");
				break;
		}
	}

	bool Mouse::isButtonPressed(Mousedowntype key){
		switch (key) {
			case Mousedowntype::Right:
				return right_key_state;
			case Mousedowntype::Left:
				return left_key_state;
		}
		return false;
	}
	
	Vector2i Mouse::getPosition(RenderWindow& window){
		(void)window;
		Vector2i example_mouse_pos;
		example_mouse_pos.x=30;
		example_mouse_pos.y=30;
		return example_mouse_pos;
	}
	
	void Mouse::simulate_key_press(Mousedowntype key) {
		switch (key) {
			case Mousedowntype::Right:
				right_key_state = true;
				break;
			case Mousedowntype::Left:
				left_key_state  = true;
				break;
		}
	}

	void Mouse::simulate_key_release(Mousedowntype key) {
		switch (key) {
			case Mousedowntype::Right:
				right_key_state = false;
				break;
			case Mousedowntype::Left:
				left_key_state  = false;
				break;
		}
	}
	
	RenderWindow::RenderWindow() : width(800), height(600), framerateLimit(60) {
		open = true;
		log_text("[RenderWindow] Default constructor called (800x600, 60 FPS)",
				 "[RenderWindow] Alapértelmezett konstruktor meghívva (800x600, 60 FPS)");
	}

	RenderWindow::RenderWindow(const std::string& title_, std::size_t w, std::size_t h): title(title_), width(w), height(h), framerateLimit(60) {
		open = true;
		log_text("[RenderWindow] Created window: \"" + title + "\" (" + std::to_string(width) + "x" + std::to_string(height) + "), default 60 FPS",
				 "[RenderWindow] Ablak létrehozva: \"" + title + "\" (" + std::to_string(width) + "x" + std::to_string(height) + "), alapértelmezett 60 FPS");
	}

	RenderWindow::RenderWindow(VideoMode vmode, const std::string& title_): framerateLimit(60) {
		width = vmode.width;
		height = vmode.height;
		title = title_;
		log_text("[RenderWindow] Created window: \"" + title + "\" (" + std::to_string(width) + "x" + std::to_string(height) + "), default 60 FPS",
				 "[RenderWindow] Ablak létrehozva: \"" + title + "\" (" + std::to_string(width) + "x" + std::to_string(height) + "), alapértelmezett 60 FPS");
	}

	void RenderWindow::create(const std::string& title_, std::size_t w, std::size_t h) {
		title = title_;
		width = w;
		height = h;
		open = true;
		log_text("[RenderWindow] Window created with title: \"" + title + "\" and size: " + std::to_string(width) + "x" + std::to_string(height),
				 "[RenderWindow] Ablak létrehozva a következő névvel: \"" + title + "\" és mérettel: " + std::to_string(width) + "x" + std::to_string(height));
	}

	bool RenderWindow::isOpen() const {
		return open;
	}

	bool RenderWindow::pollEvent(Event& event) {
		if (event.type == Event::Closed) {
			log_text("[RenderWindow] Simulating event: Closed",
					 "[RenderWindow] Esemény szimulálása: Bezárás");
			pollCount++;
			return true;
		}
		event.type = Event::NoEvent;
		return false;
	}

	void RenderWindow::close() {
		open = false;
		log_text("[RenderWindow] Closing window...",
				 "[RenderWindow] Ablak bezárása...");
	}

	void RenderWindow::setFramerateLimit(std::size_t limit) {
		framerateLimit = limit;
		log_text("[RenderWindow] Framerate limit set to " + std::to_string(framerateLimit) + " FPS",
				 "[RenderWindow] Képkockaszám korlát beállítva: " + std::to_string(framerateLimit) + " FPS");
	}

	void RenderWindow::clear() {
		log_text("[RenderWindow] Clearing screen...",
				 "[RenderWindow] Képernyő törlése...");
	}

	void RenderWindow::clear(Color clr) {
		log_text("[RenderWindow] Cleared screen with color: " + to_string(clr),
				 "[RenderWindow] Képernyő törölve a következő színnel: " + to_string(clr));
	}

	void RenderWindow::draw(const Sprite& sprite) {
		(void)sprite;
		log_text("[RenderWindow] Drawing sprite...",
				 "[RenderWindow] Sprite kirajzolása...");
	}

	void RenderWindow::draw(const RectangleShape& shape) {
		(void)shape;
		log_text("[RenderWindow] Drawing rectangle shape...",
				 "[RenderWindow] Téglalap kirajzolása...");
	}

	void RenderWindow::draw(const Sprite& sprite, RenderStates states) {
		(void)sprite;
		(void)states;
		log_text("[RenderWindow] Drawing sprite with custom render states...",
				 "[RenderWindow] Sprite kirajzolása egyéni renderelési beállításokkal...");
	}

	void RenderWindow::display() {
		log_text("[RenderWindow] Displaying frame.",
				 "[RenderWindow] Képkocka megjelenítése.");
	}
	
	RenderStates::RenderStates(): blendMode(BlendMode::None){
		for (int i = 0; i < 3; ++i){
			for (int j = 0; j < 3; ++j){
				transform.matrix[i*3+j] = (i == j) ? 1.0f : 0.0f;
			}
		}
	}

	void RenderStates::setBlendMode(BlendMode mode) {
		blendMode = mode;
	}

	void RenderStates::setTransform(const float newTransform[4][4]) {
		for (int i = 0; i < 3; ++i){
			for (int j = 0; j < 3; ++j){
				transform.matrix[i*3+j] = newTransform[i][j];
			}
		}
	}
	
	VideoMode::VideoMode(std::size_t w, std::size_t h): width(w), height(h), bitsPerPixel(16) {}

	bool VideoMode::isValid() const {
		return width > 0 && height > 0 && bitsPerPixel > 0;
	}

	VideoMode VideoMode::getDesktopMode() {
		return VideoMode(1920, 1080); ///< (HD)
	}
	
	Transform::Transform() {
		matrix[0] = 1.f; matrix[1] = 0.f; matrix[2] = 0.f;
		matrix[3] = 0.f; matrix[4] = 1.f; matrix[5] = 0.f;
		matrix[6] = 0.f; matrix[7] = 0.f; matrix[8] = 1.f;
	}

	Transform::Transform(float a00, float a01, float a02, float a10, float a11, float a12, float a20, float a21, float a22) {
		matrix[0] = a00; matrix[1] = a10; matrix[2] = a20;
		matrix[3] = a01; matrix[4] = a11; matrix[5] = a21;
		matrix[6] = a02; matrix[7] = a12; matrix[8] = a22;
	}

	Transform Transform::combine(const Transform& other) {
		for(int i=0;i<9;i++){
			matrix[i]+=other.matrix[i];
		}
		
		return *this;
	}

	void Transform::transformPoint(float x, float y) const {
		(void)x;
		(void)y;
	}

	FloatRect::FloatRect(): left(0), top(0), width(0), height(0) {}

	FloatRect::FloatRect(float l, float t, float w, float h): left(l), top(t), width(w), height(h) {}

	bool FloatRect::contains(float x, float y) const {
		return x >= left && x <= (left + width) && y >= top && y <= (top + height);
	}
	
	void Transform::translate(float tx, float ty) {
		matrix[6] += tx * matrix[0] + ty * matrix[3];
		matrix[7] += tx * matrix[1] + ty * matrix[4];
		matrix[8] += tx * matrix[2] + ty * matrix[5];
		log_text("[Transform] Translated matrix with (" + std::to_string(tx) + ", " + std::to_string(ty) + ")",
				 "[Transform] Mátrix eltolása (" + std::to_string(tx) + ", " + std::to_string(ty) + ") értékekkel");
	}

	void Transform::translate(Vector2f Vy) {
		matrix[6] += Vy.x * matrix[0] + Vy.y * matrix[3];
		matrix[7] += Vy.x * matrix[1] + Vy.y * matrix[4];
		matrix[8] += Vy.x * matrix[2] + Vy.y * matrix[5];
		log_text("[Transform] Translated matrix with (" + std::to_string(Vy.x) + ", " + std::to_string(Vy.y) + ")",
				 "[Transform] Mátrix eltolása (" + std::to_string(Vy.x) + ", " + std::to_string(Vy.y) + ") értékekkel");
	}
}
