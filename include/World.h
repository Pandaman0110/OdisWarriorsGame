#ifndef ODISWORLD_H
#define ODISWORLD_H

#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <type_traits>

#include <entt.hpp>


typedef uint32_t entity_storage_type;

enum class entity : uint32_t {};

inline std::ostream& operator<<(std::ostream& os, const entity& entity)
{
	os << static_cast<entity_storage_type>(entity);
	return os;
}

template <typename Component>
concept Aggregate = std::is_aggregate_v<Component>;

class World
{
private:

	typedef entt::basic_registry<entity> WorldEntities;
	typedef std::vector<entity> Garbage;

	WorldEntities world_entities;
	Garbage garbage;

public:
	World() {};

	template <Aggregate Component, typename...Arg> //requries Aggregate<Component>
	Component& assign(entity entity, Arg&&...args) 
	{
		return world_entities.emplace<Component>(entity, args...);
	}

	template <Aggregate...Component>
	inline void update_system(std::function<void(Component&...)> system)
	{
		auto view = world_entities.view<Component...>();

		for (auto entity : view)
		{
			system(view.get<Component...>(entity));
		}
	}

	inline void cleanup()
	{
		for (auto entity : garbage)
			world_entities.destroy(entity);

		garbage.clear();
	};

	inline entity create_entity() { return world_entities.create(); };
	inline void destroy_entity(entity entity) { garbage.push_back(entity); };
	inline void destroy_all_entities() { world_entities.clear(); };
};



#endif