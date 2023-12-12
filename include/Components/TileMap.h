#ifndef TILEMAP_H
#define TILEMAP_H

#include <array>
#include <vector>
#include <span>
#include <concepts>
#include <algorithm>
#include <ranges>
#include <iterator>
#include <fstream>

constexpr std::size_t max_tile_nums = 256;

template <std::integral TileType = uint8_t>
class TileMap
{	
private:
	using TileMapType = std::vector<TileType>;

	TileMapType tile_map{};

	std::uint64_t max_size = 0;
	std::uint64_t w = 0;

public:
	using value_type = TileType;
	using size_type = std::uint64_t;
	using iterator = TileMapType::iterator;
	using const_iterator = TileMapType::const_iterator;

	constexpr TileMap() = default;

	constexpr TileMap(size_type width, size_type height) : w(width), max_size(width * height)
	{
		resize(width, height);
	};

	constexpr TileMap(std::initializer_list<TileType> tile_map, size_type width) : TileMap(width, tile_map.size() / width)
	{
		std::ranges::copy(tile_map, this->tile_map.begin());
	};

	template <std::ranges::input_range R>
	constexpr TileMap(R&& tile_map, size_type width) : TileMap(width, std::ranges::size(tile_map) / width)
	{
		std::ranges::copy(tile_map, this->tile_map.begin());
	};

	//write a function to resize the tilemap
	constexpr void resize(size_type width, size_type height)
	{
		w = width;
		max_size = width * height;
		tile_map.resize(max_size, TileType{0});
		tile_map.shrink_to_fit();
	};

	
	value_type* data() { return tile_map.data(); };
    const value_type* data() const { return tile_map.data(); };

	constexpr value_type&operator[](size_type index) { return tile_map[index]; };
	constexpr value_type& at(size_type x, size_type y){	return tile_map.at(x + y * width()); };
	constexpr value_type get(size_type x, size_type y) const { return tile_map[x + y * width()]; };
	constexpr void set(size_type x, size_type y, uint8_t val) { tile_map[x + y * width()] = val; };

	constexpr size_type width() const { return w; };
	constexpr size_type height() const { return tile_map.size() / w; };
	constexpr size_type size() const { return tile_map.size(); };

	
	constexpr iterator begin() { return tile_map.begin(); };
	constexpr iterator end() { return tile_map.end(); };
	constexpr const_iterator begin() const { return tile_map.begin(); };
	constexpr const_iterator end() const { return tile_map.end(); };
	constexpr const_iterator cbegin() const { return tile_map.cbegin(); };
	constexpr const_iterator cend() const { return tile_map.cend(); };

	constexpr std::counted_iterator<iterator> begin(std::size_t count) { return std::counted_iterator<iterator>(tile_map.begin(), count); };
	constexpr std::counted_iterator<iterator> end(std::size_t count) { return std::counted_iterator<iterator>(tile_map.end(), count); };
	constexpr std::counted_iterator<const_iterator> begin(std::size_t count) const { return std::counted_iterator<const_iterator>(tile_map.begin(), count); };
	constexpr std::counted_iterator<const_iterator> end(std::size_t count) const { return std::counted_iterator<const_iterator>(tile_map.end(), count); };
	constexpr std::counted_iterator<const_iterator> cbegin(std::size_t count) const { return std::counted_iterator<const_iterator>(tile_map.cbegin(), count); };
	constexpr std::counted_iterator<const_iterator> cend(std::size_t count) const { return std::counted_iterator<const_iterator>(tile_map.cend(), count); };

	constexpr std::reverse_iterator<iterator> rbegin() { return std::reverse_iterator<iterator>(tile_map.end()); };
	constexpr std::reverse_iterator<iterator> rend() { return std::reverse_iterator<iterator>(tile_map.begin()); };
	constexpr std::reverse_iterator<const_iterator> rbegin() const { return std::reverse_iterator<const_iterator>(tile_map.end()); };
	constexpr std::reverse_iterator<const_iterator> rend() const { return std::reverse_iterator<const_iterator>(tile_map.begin()); };
	constexpr std::reverse_iterator<const_iterator> crbegin() const { return std::reverse_iterator<const_iterator>(tile_map.cend()); };
	constexpr std::reverse_iterator<const_iterator> crend() const { return std::reverse_iterator<const_iterator>(tile_map.cbegin()); };

	constexpr std::counted_iterator<std::reverse_iterator<iterator>> rbegin(std::size_t count) { return std::counted_iterator<std::reverse_iterator<iterator>>(std::reverse_iterator<iterator>(tile_map.end()), count); };
	constexpr std::counted_iterator<std::reverse_iterator<iterator>> rend(std::size_t count) { return std::counted_iterator<std::reverse_iterator<iterator>>(std::reverse_iterator<iterator>(tile_map.begin()), count); };
	constexpr std::counted_iterator<std::reverse_iterator<const_iterator>> rbegin(std::size_t count) const { return std::counted_iterator<std::reverse_iterator<const_iterator>>(std::reverse_iterator<const_iterator>(tile_map.end()), count); };
	constexpr std::counted_iterator<std::reverse_iterator<const_iterator>> rend(std::size_t count) const { return std::counted_iterator<std::reverse_iterator<const_iterator>>(std::reverse_iterator<const_iterator>(tile_map.begin()), count); };
	constexpr std::counted_iterator<std::reverse_iterator<const_iterator>> crbegin(std::size_t count) const { return std::counted_iterator<std::reverse_iterator<const_iterator>>(std::reverse_iterator<const_iterator>(tile_map.cend()), count); };
	constexpr std::counted_iterator<std::reverse_iterator<const_iterator>> crend(std::size_t count) const { return std::counted_iterator<std::reverse_iterator<const_iterator>>(std::reverse_iterator<const_iterator>(tile_map.cbegin()), count); };

	constexpr void fill(const TileType& value) { std::ranges::fill(tile_map, value); };


	void write_file(std::filesystem::path file_path)
	{
		std::fstream file{ file_path, std::ios::binary | std::ios::out };

		auto size = this->size();
		file.write(reinterpret_cast<const char*>(&size), sizeof(size_type));

		auto width = this->width();
		file.write(reinterpret_cast<const char*>(&width), sizeof(size_type));

		file.write(reinterpret_cast<const char*>(this->data()), this->size() * sizeof(value_type));

		file.close();
	}
	
	inline static TileMap<TileType> load_file(std::filesystem::path file_path)
	{
		using size_type = TileMap<TileType>::size_type;
		using value_type = TileMap<TileType>::value_type;

		std::fstream file(file_path, std::ios::binary | std::ios::in);

		size_type size = 0;
		size_type width = 0;

		file.read(reinterpret_cast<char*>(&size), sizeof(size_type));
		file.read(reinterpret_cast<char*>(&width), sizeof(size_type));
		
		TileMap<TileType> tile_map{width, size/width};

		file.read(reinterpret_cast<char*>(tile_map.data()), size * sizeof(value_type));

		file.close();

		return tile_map;
	}
};

template <std::integral TileType>
std::ostream& operator<<(std::ostream& os, const TileMap<TileType>& tile_map)
{
	std::ranges::for_each(tile_map, [&os](const auto& tile) { os << std::to_string(tile); });
	return os;
};

#endif
