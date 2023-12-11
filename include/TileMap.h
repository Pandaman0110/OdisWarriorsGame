#ifndef TILEMAP_H
#define TILEMAP_H

#include <array>
#include <vector>
#include <span>
#include <concepts>
#include <algorithm>
#include <ranges>
#include <iterator>


template <std::integral TileType>
class TileMap
{	
private:
	typedef std::vector<TileType> TileMapType;
	typedef TileMapType::iterator iterator;
	typedef TileMapType::const_iterator const_iterator;

	TileMapType tile_map{};

	std::size_t max_size;
	std::size_t w;

	constexpr void reserve(std::size_t size)
	{
		tile_map.shrink_to_fit();
		tile_map.resize(size, TileType{ 0 });
	};
public:
	constexpr TileMap() = default;

	constexpr TileMap(std::size_t width, std::size_t height) : w(width), max_size(width * height)
	{
		reserve(max_size);
	};

	constexpr TileMap(std::initializer_list<TileType> tile_map, std::size_t width) : TileMap(width, tile_map.size() / width)
	{
		std::ranges::copy(tile_map, this->tile_map.begin());
	};

	template <std::ranges::input_range R>
	constexpr TileMap(R&& tile_map, std::size_t width) : TileMap(width, std::ranges::size(tile_map) / width)
	{
		std::ranges::copy(tile_map, this->tile_map.begin());
	};

	constexpr TileType &operator[](std::size_t index) { return tile_map[index]; };
	constexpr TileType& at(std::size_t x, std::size_t y){	return tile_map.at(x + y * width()); };
	constexpr TileType get(std::size_t x, std::size_t y) const { return tile_map[x + y * width()]; };

	constexpr std::size_t width() const { return w; };
	constexpr std::size_t height() const { return tile_map.size() / w; };

	
	//write iterator functions for tilemap
	constexpr iterator begin() { return tile_map.begin(); };
	constexpr iterator end() { return tile_map.end(); };
	constexpr const_iterator begin() const { return tile_map.begin(); };
	constexpr const_iterator end() const { return tile_map.end(); };
	constexpr const_iterator cbegin() const { return tile_map.cbegin(); };
	constexpr const_iterator cend() const { return tile_map.cend(); };

	//write counted iterator function for tilemap
	constexpr std::counted_iterator<iterator> begin(std::size_t count) { return std::counted_iterator<iterator>(tile_map.begin(), count); };
	constexpr std::counted_iterator<iterator> end(std::size_t count) { return std::counted_iterator<iterator>(tile_map.end(), count); };
	constexpr std::counted_iterator<const_iterator> begin(std::size_t count) const { return std::counted_iterator<const_iterator>(tile_map.begin(), count); };
	constexpr std::counted_iterator<const_iterator> end(std::size_t count) const { return std::counted_iterator<const_iterator>(tile_map.end(), count); };
	constexpr std::counted_iterator<const_iterator> cbegin(std::size_t count) const { return std::counted_iterator<const_iterator>(tile_map.cbegin(), count); };
	constexpr std::counted_iterator<const_iterator> cend(std::size_t count) const { return std::counted_iterator<const_iterator>(tile_map.cend(), count); };

	//write reverse iterator functions for tilemap
	constexpr std::reverse_iterator<iterator> rbegin() { return std::reverse_iterator<iterator>(tile_map.end()); };
	constexpr std::reverse_iterator<iterator> rend() { return std::reverse_iterator<iterator>(tile_map.begin()); };
	constexpr std::reverse_iterator<const_iterator> rbegin() const { return std::reverse_iterator<const_iterator>(tile_map.end()); };
	constexpr std::reverse_iterator<const_iterator> rend() const { return std::reverse_iterator<const_iterator>(tile_map.begin()); };
	constexpr std::reverse_iterator<const_iterator> crbegin() const { return std::reverse_iterator<const_iterator>(tile_map.cend()); };
	constexpr std::reverse_iterator<const_iterator> crend() const { return std::reverse_iterator<const_iterator>(tile_map.cbegin()); };

	//write counted reverse iterator functions for tilemap
	constexpr std::counted_iterator<std::reverse_iterator<iterator>> rbegin(std::size_t count) { return std::counted_iterator<std::reverse_iterator<iterator>>(std::reverse_iterator<iterator>(tile_map.end()), count); };
	constexpr std::counted_iterator<std::reverse_iterator<iterator>> rend(std::size_t count) { return std::counted_iterator<std::reverse_iterator<iterator>>(std::reverse_iterator<iterator>(tile_map.begin()), count); };
	constexpr std::counted_iterator<std::reverse_iterator<const_iterator>> rbegin(std::size_t count) const { return std::counted_iterator<std::reverse_iterator<const_iterator>>(std::reverse_iterator<const_iterator>(tile_map.end()), count); };
	constexpr std::counted_iterator<std::reverse_iterator<const_iterator>> rend(std::size_t count) const { return std::counted_iterator<std::reverse_iterator<const_iterator>>(std::reverse_iterator<const_iterator>(tile_map.begin()), count); };
	constexpr std::counted_iterator<std::reverse_iterator<const_iterator>> crbegin(std::size_t count) const { return std::counted_iterator<std::reverse_iterator<const_iterator>>(std::reverse_iterator<const_iterator>(tile_map.cend()), count); };
	constexpr std::counted_iterator<std::reverse_iterator<const_iterator>> crend(std::size_t count) const { return std::counted_iterator<std::reverse_iterator<const_iterator>>(std::reverse_iterator<const_iterator>(tile_map.cbegin()), count); };

	//write
};

#endif
