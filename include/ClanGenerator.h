#ifndef CLAN_GENERATOR_H
#define CLAN_GENERATOR_H

#include "Game.h"
#include "ScriptManager.h"
#include "Components/Clan.h"

class ClanGenerator
{
private:
	sol::state* lua_state;
	Script* script;

	Clan generate_lua_clan()
	{
		return script->execute<Clan>();
	}
public:
	ClanGenerator() {};

	ClanGenerator(sol::state* lua_state) : lua_state(lua_state)
	{
		auto clan_type = lua_state->new_usertype<Clan>("Clan");
		clan_type.set("name", &Clan::name);

		script = script_manager->new_script("script/clan_generator.lua", lua_state, "clan_generator");
	};

	Clan operator()()
	{
		return generate_lua_clan();
	};
};


#endif