#ifndef ODISGUI_COMPONENTS_H
#define ODISGUI_COMPONENTS_H

#include <vector>

#include <utility/OdisMath.h>

namespace OdisGui
{
	enum class Layout
	{
		manual
	};

	enum class Anchor
	{
		top_left,
		top_right,
		bottom_left,
		bottom_right
	};


	class GuiElement
	{
	private:
		Layout layout;

		int x, y, w, h;
	
	public:
		GuiElement() {};
		virtual ~GuiElement() {};


	};

	class View : public GuiElement
	{
	private:


	public:
		View() {};
		~View() {};

	};

	class Button : public GuiElement
	{
	private:



	public:
		Button() {};
		~Button() {};


	};

	class Label : public GuiElement
	{
	private:
		std::string text;


	public:
		Label(std::string text) : text(text) {};

		~Label() {};



	};


};



#endif
