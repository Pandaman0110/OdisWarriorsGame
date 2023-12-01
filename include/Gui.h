#ifndef ODISGUI_H
#define ODISGUI_H


#include <iostream>
#include <vector>

#include <tree/st_tree.h>

#include "ScriptManager.h"
#include "Game.h"
#include "GuiComponents.h"


namespace OdisGui
{
	typedef st_tree::tree<GuiElement> Tree;

	class Gui
	{
	private:
		Tree gui_elements;

		void load_gui()
		{

		}

	public:
		Gui()
		{
			//add a blank view element to the root of the tree
			gui_elements.insert(View{});
		}


		size_t size() const { return gui_elements.size(); };
	};

};




#endif
