#ifndef DYNAMIC2D_INL
#define DYNAMIC2D_INL

#include "TerrainContainer.hpp"

template <typename T>
int TerrainContainer<T>::get_width() const {
    return width * TILE_SIZE;
}

template <typename T>
int TerrainContainer<T>::get_height() const {
    return height * TILE_SIZE;
}

template <typename T>
TerrainContainer<T>::TerrainContainer() = default;

template <typename T>
TerrainContainer<T>::TerrainContainer(int awidth, int aheight, T def_value) {
    resize(awidth, aheight, def_value);
}

template <typename T>
void TerrainContainer<T>::swap_at(int x1, int y1, int x2, int y2) {
    std::swap(in_array[y1][x1], in_array[y2][x2]);
}

template <typename T>
bool TerrainContainer<T>::is_valid_coordinate(int x, int y) {
    return !(x < 0 || y < 0 || x >= width || y >= height);
}

template <typename T>
bool TerrainContainer<T>::is_on_screen(int x, int y) {
    int tw = GameConfig::get_instance().get_screen_width();
    int th = GameConfig::get_instance().get_screen_height();
    return (x > -TILE_SIZE && y > -TILE_SIZE && x < tw + TILE_SIZE && y < th + TILE_SIZE);
}

template <typename T>
T*& TerrainContainer<T>::operator[](std::size_t row) {
    return in_array[row];
}

template <typename T>
T* const& TerrainContainer<T>::operator[](std::size_t row) const {
    return in_array[row];
}

template <typename T>
void TerrainContainer<T>::draw(sf::RenderWindow& window, int offx, int offy) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int dest_x = x * TILE_SIZE + offx;
            int dest_y = y * TILE_SIZE + offy;
            if (is_on_screen(dest_x, dest_y)) {
                in_array[y][x]->setPosition(dest_x, dest_y);
                in_array[y][x]->draw(window);
            }
        }
    }
}

template <typename T>
void TerrainContainer<T>::set_seed(int new_value){
	seed = new_value;
}

template <typename T>
int TerrainContainer<T>::get_seed() const{
	return seed;
}


template <typename T>
void TerrainContainer<T>::generate_world() {
	if(seed==-1){
		seed = RandomGenerator::get_instance().get_random_int(32767);
	}
    const double mountain_threshold = 0.4;
    const double water_threshold = 0.0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double oct2 = (std::sin((seed + x * 0.1) * 3.14159)) * std::cos(((seed + y) * 0.1) * 3.14159);
            double oct1 = std::sin((seed + x * 0.01 + 100) * 3.14159) * std::cos((seed + y * 0.01 + 100) * 3.14159);
            double noise_value = oct2 * 0.3 + oct1 * 0.7;

            if (noise_value > mountain_threshold) {
                in_array[y][x]->init(tiles::TILETYPE::MOUNTAIN);
            } else if (noise_value < water_threshold) {
                in_array[y][x]->init(tiles::TILETYPE::WATER);
            } else {
                in_array[y][x]->init(tiles::TILETYPE::GRASS);
            }
        }
    }
}

template <typename T>
void TerrainContainer<T>::clear_at(int x, int y) {
    if (in_array[y][x] != nullptr) {
        delete in_array[y][x];
        in_array[y][x] = nullptr;
    }
}

template <typename T>
void TerrainContainer<T>::clear() {
    if (in_array != nullptr) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                delete in_array[i][j];
            }
            delete[] in_array[i];
        }
        delete[] in_array;
        in_array = nullptr;
        width = 0;
        height = 0;
    }
}

template <typename T>
template <typename Defvalue>
void TerrainContainer<T>::resize(int awidth, int aheight) {
    clear();

    width = awidth;
    height = aheight;

    in_array = new T*[height];
    for (int i = 0; i < height; i++) {
        in_array[i] = new T[width];
        for (int j = 0; j < width; j++) {
            in_array[i][j] = new Defvalue;
        }
    }
}

template <typename T>
TerrainContainer<T>::~TerrainContainer() {
	clear();
}

#endif
