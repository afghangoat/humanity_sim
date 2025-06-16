#ifndef FAKE_SFML_HPP
#define FAKE_SFML_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

#include "../Utils.h"

namespace sf {
	inline bool file_exists_at_path(const std::string& name);
	
	class Vector2f {
		public:
			float x;
			float y;

			Vector2f();

			Vector2f(float x1, float y1);
	};
	
	class Transform {
		public:
			float matrix[9];

			Transform();

			Transform(float a00, float a01, float a02, float a10, float a11, float a12, float a20, float a21, float a22);

			Transform combine(const Transform& other);

			void transformPoint(float x, float y) const;
			
			void translate(float tx, float ty);
			void translate(Vector2f Vy);
    };
	
    class FloatRect {
		public:
			float left;
			float top;
			float width;
			float height;

			FloatRect();

			FloatRect(float l, float t, float w, float h);

			bool contains(float x, float y) const;
    };
	
	class Vector2i {
		public:
			int x;
			int y;

			Vector2i();

			Vector2i(int x1, int y1);
	};
	
	class Texture {
		private:
			std::string path_name;
		public:
			Texture();

			bool loadFromFile(const std::string& filepath);
			Vector2i getSize();
			~Texture();
			Texture(const Texture& other);

			Texture& operator=(const Texture& other);
	};
	class Bound{
		public:
			int width;
			int height;
	};
	class Color{
		public:
			int r;
			int g;
			int b;
			int a;
			
			Color();
			Color(int _r, int _g, int _b);
			Color(int _r, int _g, int _b, int _a);
			
			static const Color Black;
			static const Color White;
			static const Color Red;
			static const Color Green;
			static const Color Blue;
			static const Color Transparent;
	};
	
	class IntRect {
		public:
			int left;
			int top;
			int width;
			int height;

			IntRect();

			IntRect(int l, int t, int w, int h);
	};
	
	class Sprite {
		private:
			Texture texture;
			Vector2f position;
			Vector2f scale;
			Vector2f origin;
			float rotation=0.0f;
			Color clr;

		public:
			Sprite();

			void setTexture(Texture& tex);
			void setTextureRect(const IntRect& tex);
			Texture* getTexture();

			void setPosition(float x, float y);
			void setOrigin(float _x, float _y);
			void setRotation(float deg);
			Vector2f getPosition();

			void setScale(float sx, float sy);
			
			FloatRect getLocalBounds();
			FloatRect getGlobalBounds();
			FloatRect getGlobalBounds() const;

			void draw() const;
			
			void setColor(Color _clr);
			~Sprite();
	};
	
	class Event{
		public:
			enum EType : char {
				Closed,
				NoEvent,
				Invalid
			};
			EType type;
			Event();
	};
	
	class ClockTime{
		private:
			std::size_t time_ticks;
		public:
			ClockTime(std::size_t atime);
			
			ClockTime();
			
			float asSeconds();
			
			void reset();
			
			void increment();
	};
	
	class Clock{
		private:
			ClockTime held_time;
		public:
			void restart();
			ClockTime& getElapsedTime();
	};
	
	class SoundBuffer {
		private:
			std::string data;
		public:
			bool loadFromFile(const std::string& filepath);
	};
	
	class Sound {
		private:
			SoundBuffer* buffer = nullptr;
		public:
			void setBuffer(SoundBuffer& buf);
			void play();
			void stop();
			~Sound();
	};
	
	class SoundSource{
		public:
			enum SoundSourceType:char {
				Playing,Stopped,Paused
			};
			
			SoundSourceType type;
			
			SoundSource();
			
			virtual ~SoundSource ()=default;
	};
	class Music{
		private:
			bool playing=false;
			bool looping=false;
			double db;
			std::string playing_file;
		public:
			
			Music();
			
			void setLoop(bool newval);
			void setVolume(double new_db);
			SoundSource::SoundSourceType getStatus();
			void play();
			void stop();
			bool openFromFile(const std::string& filepath);
	};
	
	
	class RectangleShape{
		private:
			Color selfcolor;
			Vector2f size;
		public:
			Vector2f position;
			void setFillColor(Color new_color);
			void setSize(Vector2f newsize);
			void setPosition(Vector2f newsize);
	};
	
	class Keyboard {
		private:
			static inline bool right_key_state = false;
			static inline bool left_key_state = false;
			static inline bool down_key_state = false;
			static inline bool up_key_state = false;

		public:
			enum Key : char {Right,Left,Down,Up,Space,Num1,Num2,Num3,Num4,Num5,Num6,Num7,Num8,Num9,Num0};

			static bool isKeyPressed(Key key);

			static void simulate_key_press(Key key);

			static void simulate_key_release(Key key);
	};
	
	enum class BlendMode {
        None,
        Alpha,
        Additive,
        Multiply,
		BlendAdd
    };
	
	inline constexpr BlendMode BlendAdd = BlendMode::BlendAdd;

    class RenderStates {
		public:
			Transform transform;

			BlendMode blendMode;

			RenderStates();

			void setBlendMode(BlendMode mode);

			void setTransform(const float newTransform[4][4]);
    };
	
	class VideoMode {
		public:
			std::size_t width;
			std::size_t height;
			std::size_t bitsPerPixel;

			VideoMode(std::size_t w = 800, std::size_t h = 600);

			bool isValid() const;

			static VideoMode getDesktopMode();
    };
	
	class RenderWindow {
		private:
			std::string title;
			std::size_t width, height;
			std::size_t framerateLimit;
			bool open;
			int pollCount;

		public:
			RenderWindow();

			RenderWindow(const std::string& title_, std::size_t w, std::size_t h);
			
			RenderWindow(VideoMode vmode, const std::string& title_);

			void create(const std::string& title_, std::size_t w, std::size_t h);
			bool isOpen() const;
			
			bool pollEvent(Event& event);

			void close();

			void setFramerateLimit(std::size_t limit);

			void clear();

			void draw(const Sprite& sprite);
			void draw(const Sprite& sprite, RenderStates states);
			void draw(const RectangleShape& shape);

			void display();
			void clear(Color clr);
	};
	
	class Mouse{
		private:
			static inline bool right_key_state = false;
			static inline bool left_key_state = false;
		public:
			enum Mousedowntype:char {
				Right,Left
			};
			static bool isButtonPressed(Mousedowntype key);
			static Vector2i getPosition(RenderWindow& window);
			
			static void simulate_key_press(Mousedowntype key);

			static void simulate_key_release(Mousedowntype key);
	};
}
#endif