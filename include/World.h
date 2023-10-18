#ifndef ODISWORLD_H
#define ODISWORLD_H

#include <iostream>
#include <vector>
#include <string>
#include <functional>

#include <entt.hpp>

namespace OdisEngine
{
	typedef uint32_t entity_storage_type;

	enum class entity : uint32_t {};

	inline std::ostream& operator<<(std::ostream& os, const entity& entity)
	{
		os << static_cast<entity_storage_type>(entity);
		return os;
	}

	typedef entt::basic_registry<entity> WorldEntities;
	typedef std::vector<entity> Garbage;

	class World
	{
	private:
		WorldEntities world_entities;
		Garbage garbage;

	public:
		World() {};

		template <typename Component, typename...Arg>
		inline Component& assign(entity entity, Arg&&...args)
		{
			return world_entities.emplace<Component>(entity, args...);
		}

		template <typename ...Components>
		inline void update_system(std::function<void(Components...)> system)
		{
			auto view = world_entities.view<Components...>();

			for (auto entity : view)
			{
				system(view.get<Components...>(entity));
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
}


#endif