#ifndef SCRIPT_MANAGER_H
#define SCRIPT_MANAGER_H

#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <filesystem>
#include <expected>

#include <Log.h>

#include <sol.hpp>
//https://sol2.readthedocs.io/en/latest/


using namespace OdisEngine;

class Script
{
private:
	sol::load_result script;

	bool is_file(const std::string& script_text) { return std::filesystem::exists(script_text); };
	void load_script(sol::state* lua_table, const std::string& script_text)
	{
		is_file(script_text) ? script = lua_table->load_file(script_text) : script = lua_table->load(script_text);
	};
public:
	Script(sol::state* lua_state, const std::string& script_text)
	{
		load_script(lua_state, script_text);
	}

	//if this is empty it loaded scucesfully
	std::expected<bool, std::string> valid() const
	{
#if !_DEBUG
		return true;
#endif
		if (!script.valid())
		{
			sol::error error = script;
			return std::unexpected(std::string(error.what()));
		}
		else
			return true;
	};

	void execute()
	{
		auto script_result = script();

		for (auto err : script_result)
		{
			sol::error error = err;
			logger->get("Script")->log(LogLevel::warning, error.what());
		}
	}

	template <typename Rt>
	decltype(auto) execute()
	{
		auto script_result = script();
		
		if (script_result.valid()) 
		{
			return static_cast<Rt>(script_result);
		}
		else
		{
			for (auto err : script_result)
			{
				sol::error error = err;
				logger->get("Script")->log(LogLevel::warning, error.what());
			}
			return static_cast<Rt>(script_result);
		}
	}
};



class ScriptManager
{
private:
	std::map<std::string, std::unique_ptr<Script>> scripts;
	std::map<std::string, std::unique_ptr<sol::state>> lua_states;

	std::optional<std::unique_ptr<Script>> try_load_script(const std::string& script_text, sol::state* lua_state)
	{
		auto script = std::make_unique<Script>(lua_state, script_text);
		auto result = script->valid();

		auto ch = logger->get("Script");
		
		if (result)
		{
			ch->log(LogLevel::info, "Script number", get_num_scripts(), "loaded succesfully");
			return script;
		}
		else
		{
			ch->log(LogLevel::warning, "Script number", get_num_scripts(), "error message", result.error());
			return std::nullopt;
		}
	}

public:
	ScriptManager()
	{
		logger->create("Script");
	}

	Script* new_script(const std::string& script_text, sol::state* lua_state, const std::string& script_name)
	{
		auto result = try_load_script(script_text, lua_state);

		if (result.has_value())
			scripts[script_name] = std::move(result.value());

		return get_script(script_name);
	};
	Script* get_script(const std::string& script_name) 
	{ 
		return scripts.at(script_name).get(); 
	};
	void delete_scripts()
	{
		scripts.clear();
	};
	void delete_script(const std::string& script_name)
	{
		scripts.erase(script_name);
	};
	size_t get_num_scripts() const 
	{ 
		return scripts.size(); 
	};

	sol::state* new_lua_state(const std::string& state_name)
	{
		lua_states.insert({ state_name, std::make_unique<sol::state>() });
		auto state = get_lua_state(state_name);

		state->open_libraries(sol::lib::base, sol::lib::math, sol::lib::package, sol::lib::table, sol::lib::string);

		//this code allows require to find scripts in script/
		const std::string package_path = state->traverse_get<std::string>("package", "path");
		state->traverse_set("package", "path", package_path + (!package_path.empty() ? ";" : "") + "script/" + "?.lua");

		return state;
	}

	sol::state* get_lua_state(const std::string& state_name)
	{
		return lua_states.at(state_name).get();
	}
	void delete_lua_states()
	{
		lua_states.clear();
	}
	void delete_lua_state(const std::string& state_name)
	{
		lua_states.erase(state_name);
	}

};


#endif