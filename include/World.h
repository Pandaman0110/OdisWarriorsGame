#ifndef ODISWORLD_H
#define ODISWORLD_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <functional>
#include <type_traits>
#include <concepts>

#include <entt.hpp>



typedef uint32_t entity_storage_type;

enum class Entity : uint32_t {};

inline std::ostream& operator<<(std::ostream& os, const Entity& entity)
{
	os << static_cast<entity_storage_type>(entity);
	return os;
}

template <typename T>
concept Component = requires (T component)
{
	{ std::is_aggregate_v<T> };
	{ component.write(std::declval<std::ostream&>()) };
};

template <Component T>
constexpr std::string get_component_name()
{
#ifdef __clang__
	std::abort();
		/*code specific to clang compiler*/
#elif __GNUC__
	std::abort();
		/*code for GNU C compiler */
#elif _MSC_VER
	/*usually has the version number in _MSC_VER*/
	/*code specific to MSVC compiler*/
	auto name = std::string(typeid(T).name());
	return name.erase(0, 7);
#endif
}

template <Component ...T>
void write_components(std::ostream& os, T...components)
{
	if constexpr (sizeof...(T) > 0)
		(..., components.write(os));
}

template <typename T>
void write_entity(std::ostream& os, T entity)
{
	os << "Entity: " << static_cast<int>(entity) << "\n";
}


typedef entt::basic_registry<Entity> WorldEntities;

class World
{
private:
	typedef std::vector<Entity> Garbage;

	WorldEntities world_entities;
	Garbage garbage;

public:
	World() {};

	template <Component T, typename...Arg> //requries Aggregate<Component>
	T& assign(Entity ent, Arg&&...args)
	{
		return world_entities.emplace<T>(ent, std::forward<Arg...>(args)...);
	}

	template <Component T>
	auto on_construct()
	{
		return world_entities.on_construct<T>();
	}
	
	template <Component...T>
	void update_system(std::function<void(float, T&...)> system, float dt)
	{
		auto view = world_entities.view<T...>();

		for (auto entity : view)
		{
			std::apply(system, std::tuple_cat(std::make_tuple(dt), view.get(entity)));
		}
	}

	template < std::size_t times, Component...T>
	void update_system(std::function<void(T&...)> system)
	{
		auto view = world_entities.view<T...>();

		for (std::size_t i = 0; i < times; ++i)
		{
			for (auto entity : view)
				std::apply(system, view.get(entity));
		}
	}

	inline void cleanup()
	{
		for (auto entity : garbage)
			world_entities.destroy(entity);

		garbage.clear();
	}

	inline Entity create_entity() { return world_entities.create(); };
	inline void destroy_entity(Entity entity) { garbage.push_back(entity); };
	inline void destroy_all_entities() { world_entities.clear(); };

	//TODO
	/*
	void write_entities(std::ostream& os)
	{
		auto view = world_entities.view<Entity>();

		for (auto entity : view)
		{
			write_entity(os, entity);
			write_components(os, view.get<T...>(entity));

			
			std::apply(
				[&](auto...args)
				{
					(..., args.write(os));
				}, view.get(entity));
				

			std::apply([&](auto ...args) { std::cout << sizeof...(args) << std::endl; write_components(os, args...); }, view.get(entity));
		}
	}
	*/
};


#endif

