#ifndef CAT_GENERATOR_H
#define CAT_GENERATOR_H

#include "Game.h"
#include "ScriptManager.h"
#include "Components/Cat.h"

class CatGenerator
{
private:
	sol::state* lua_state;
	Script* script;

	Cat generate_lua_cat()
	{
		return script->execute<Cat>();
	}
public:
	CatGenerator() {};

	CatGenerator(sol::state* state) : lua_state(state)
	{
		auto cat_type = lua_state->new_usertype<Cat>("Cat");

		cat_type.set("prefix", &Cat::prefix);
		cat_type.set("suffix", &Cat::suffix);
		cat_type.set("role", &Cat::role);

		script = script_manager->new_script("script/cat_generator.lua", lua_state, "cat_generator");
	};

	Cat operator()() 
	{
		return generate_lua_cat();
	};
};

#endif