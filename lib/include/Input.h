#ifndef INPUT_H
#define INPUT_H

#include <vector>
#include <string>
#include <map>

#include "Window.h"
#include "Keys.h"
#include "InputEvent.h"

namespace OdisEngine
{

	class InputMap
	{
	public:
		InputMap();

		void add_event(std::string action, int event);
		void erase_event(std::string action, int event);
		void remove_events(std::string action);

		void add_action(std::string action);
		void erase_action(std::string action);

		void load_actions_from_config ();

		std::vector<std::string> get_actions() const;

	private:
		//std::multimap<std::string, >

	};


	class Input
	{
	public:
		Input(Window& window);

		bool is_action_pressed(std::string action) const;
		bool is_action_released(std::string action) const;
		bool is_action_down(std::string action) const;

		bool is_key_pressed(Key key) const;
		bool is_key_released(Key key) const;
		bool is_key_down(Key key) const;

		bool is_mouse_button_pressed(MouseButton button) const;
		bool is_mouse_button_released(MouseButton button) const;
		bool is_mouse_button_down(MouseButton button) const;

		void poll_inputs(float dt);
	private:
		InputMap input_map;
		std::vector<KeyboardInputEvent> keyboard_input_queue;
		std::vector<MouseButtonInputEvent> mouse_button_input_queue;

		void keyboard_input_callback(KeyboardInputEvent&& input_event);
		void mouse_button_input_callback(MouseButtonInputEvent&& input_event);
	};

}

#endif