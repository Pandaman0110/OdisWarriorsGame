#ifndef CAT_GENERATOR_H
#define CAT_GENERATOR_H

#include <algorithm>
#include <random>
#include <ranges>

#include <FileSystem.h>

#include "Game.h"
#include "ScriptManager.h"
#include "Components/Cat.h"

using namespace OdisEngine;

class CatGenerator
{
private:
	sol::state* lua_state;
	Script* script;

	std::vector<std::string> cat_prefixes;
	std::vector<std::string> cat_suffixes;

	Cat generate_lua_cat()
	{
		return script->execute<Cat>();
	}
	
	/*
	std::vector<std::string> load_prefixes()
	{
		auto document = toml::parse_file("assets/data/cat_names.toml");
		auto prefixes = document["names"]["prefixes"].as_array();
		//auto suffixes = document["names"]["suffixes"].as_array();

		prefixes->for_each(
			[] (auto&& name)
			{
				if constexpr (toml::is_string<decltype(name)>)
				{
					prefixes
				}
				else
				{

				}
			});
	}
	*/
public:
	CatGenerator() {};

	CatGenerator(sol::state* state) : lua_state(state)
	{
		//auto cat_type = lua_state->new_usertype<Cat>("Cat");

		//cat_type.set("prefix", &Cat::prefix);
		//cat_type.set("suffix", &Cat::suffix);
		//cat_type.set("role", &Cat::role);

		//script = script_manager->new_script("script/cat_generator.lua", lua_state, "cat_generator");
		//auto document = toml::parse_file("assets/data/cat_names.toml");
		//auto prefixes = document["names"]["prefixes"].as<toml::value<std::string>>();
		//auto suffixes = document["names"]["suffixes"].as<toml::value<std::string>>();

		//std::for_each(prefixes.begin(), prefixes

		//cat_prefixes.assign(, prefixes->end());
		//cat_suffixes.assign(suffixes, suffixes->end());
	};

	Cat operator()() 
	{
		Cat cat{};

		cat_prefixes.assign_range(FileSystem::load_toml_array<std::string>("assets/data/cat_names.toml", "prefixes"));
		cat_suffixes.assign_range(FileSystem::load_toml_array<std::string>("assets/data/cat_names.toml", "suffixes"));

		logger->get("Warriors")->log(LogLevel::debug, "Number of prefixes loaded", cat_prefixes.size());
		logger->get("Warriors")->log(LogLevel::debug, "Number of suffixes loaded", cat_suffixes.size());

		return cat;
	};
};

#endif