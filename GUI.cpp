#include "GUI.h"

GUI::GUI(sf::Color* _select_color1, sf::Color* _select_color2)
{
	select_color1 = _select_color1;
	select_color2 = _select_color2;

	box.setSize(sf::Vector2f(110, 75));
	box.setOutlineThickness(2);
	box.setOutlineColor(sf::Color::Black);

	place_tool.setSize(sf::Vector2f(30, 30));
	place_tool.setOrigin(-5, -5);
	place_tool.setOutlineThickness(1);
	place_tool.setOutlineColor(sf::Color::Black);
	place_tool.setFillColor(sf::Color::Cyan);
	place_tool_texture = new sf::Texture();
	place_tool_texture->loadFromFile("assets/place_tool.png");
	place_tool.setTexture(place_tool_texture);

	delete_tool.setSize(sf::Vector2f(30, 30));
	delete_tool.setOrigin(-5, -40);
	delete_tool.setOutlineThickness(1);
	delete_tool.setOutlineColor(sf::Color::Black);
	delete_tool_texture = new sf::Texture();
	delete_tool_texture->loadFromFile("assets/delete_tool.png");
	delete_tool.setTexture(delete_tool_texture);

	move_tool.setSize(sf::Vector2f(30, 30));
	move_tool.setOrigin(-40, -5);
	move_tool.setOutlineThickness(1);
	move_tool.setOutlineColor(sf::Color::Black);
	move_tool_texture = new sf::Texture();
	move_tool_texture->loadFromFile("assets/move_tool.png");
	move_tool.setTexture(move_tool_texture);

	select_tool.setSize(sf::Vector2f(30, 30));
	select_tool.setOrigin(-40, -40);
	select_tool.setOutlineThickness(1);
	select_tool.setOutlineColor(sf::Color::Black);
	select_tool_texture = new sf::Texture();
	select_tool_texture->loadFromFile("assets/select_tool.png");
	select_tool.setTexture(select_tool_texture);

	selection.setOutlineThickness(1);
	selection.setOutlineColor(sf::Color(255, 0, 0, 100));
	selection.setFillColor(*select_color1);

	connect_tool.setSize(sf::Vector2f(30, 30));
	connect_tool.setOrigin(-75, -5);
	connect_tool.setOutlineThickness(1);
	connect_tool.setOutlineColor(sf::Color::Black);
	connect_tool_texture = new sf::Texture();
	connect_tool_texture->loadFromFile("assets/connect_tool.png");
	connect_tool.setTexture(connect_tool_texture);

	disconnect_tool.setSize(sf::Vector2f(30, 30));
	disconnect_tool.setOrigin(-75, -40);
	disconnect_tool.setOutlineThickness(1);
	disconnect_tool.setOutlineColor(sf::Color::Black);
	disconnect_tool_texture = new sf::Texture();
	disconnect_tool_texture->loadFromFile("assets/disconnect_tool.png");
	disconnect_tool.setTexture(disconnect_tool_texture);
}

void GUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (visible)
	{
		target.draw(box);
		target.draw(place_tool);
		target.draw(delete_tool);
		target.draw(move_tool);
		target.draw(select_tool);
		target.draw(connect_tool);
		target.draw(disconnect_tool);
	}
	if (selection_visible)
		target.draw(selection);
}

void GUI::setPosition(sf::Vector2f position)
{
	box.setPosition(position);
	place_tool.setPosition(position);
	delete_tool.setPosition(position);
	move_tool.setPosition(position);
	select_tool.setPosition(position);
	connect_tool.setPosition(position);
	disconnect_tool.setPosition(position);
}

void GUI::setSelectionPosition(sf::Vector2f position)
{
	selection.setPosition(position);
	selection_position = position;
}

void GUI::setSelectionState(bool state)
{
	if (state)
	{
		selection.setFillColor(sf::Color(select_color2->r, select_color2->g, select_color2->b, 50));
		selection.setOutlineColor(sf::Color(select_color2->r, select_color2->g, select_color2->b, 100));
	}
	else
	{
		selection.setFillColor(sf::Color(select_color1->r, select_color1->g, select_color1->b, 50));
		selection.setOutlineColor(sf::Color(select_color1->r, select_color1->g, select_color1->b, 100));
	}
}

sf::Vector2f GUI::getSelectionPosition()
{
	return selection.getPosition();
}

sf::Vector2f GUI::getSelectionSize()
{
	return selection.getSize();
}

void GUI::setSelectionSize(sf::Vector2f bottom_right)
{
	if (bottom_right.x >= selection_position.x && bottom_right.y >= selection_position.y)
	{
		selection.setSize(sf::Vector2f(bottom_right.x - selection_position.x, bottom_right.y - selection_position.y));
	}
	else if (bottom_right.x < selection_position.x && bottom_right.y >= selection_position.y)
	{
		selection.setSize(sf::Vector2f(selection_position.x - bottom_right.x, bottom_right.y - selection_position.y));
		selection.setPosition(sf::Vector2f(bottom_right.x, selection_position.y));
	}
	else if (bottom_right.x >= selection_position.x && bottom_right.y < selection_position.y)
	{
		selection.setSize(sf::Vector2f(bottom_right.x - selection_position.x, selection_position.y - bottom_right.y));
		selection.setPosition(sf::Vector2f(selection_position.x, bottom_right.y));
	}
	else
	{
		selection.setSize(sf::Vector2f(selection_position.x - bottom_right.x, selection_position.y - bottom_right.y));
		selection.setPosition(sf::Vector2f(bottom_right.x, bottom_right.y));
	}
}

void GUI::resetSelection()
{
	selection.setPosition(sf::Vector2f(0, 0));
	selection.setSize(sf::Vector2f(0, 0));
	selection_position = sf::Vector2f(0, 0);
}

bool GUI::mouseInside(sf::Vector2f mouse_position)
{
	sf::Vector2f gui_position = box.getPosition();
	return mouse_position.x >= gui_position.x && mouse_position.x <= gui_position.x + box.getSize().x && mouse_position.y >= gui_position.y && mouse_position.y <= gui_position.y + box.getSize().y && visible;
}

void GUI::queryTools(sf::Vector2f mouse_position)
{
	if (visible)
	{
		sf::Vector2f position = box.getPosition();
		if (mouse_position.x >= position.x + 5 && mouse_position.x <= position.x + 35 && mouse_position.y >= position.y + 5 && mouse_position.y <= position.y + 35)
		{
			place_tool.setFillColor(sf::Color::Cyan);
			delete_tool.setFillColor(sf::Color::White);
			move_tool.setFillColor(sf::Color::White);
			select_tool.setFillColor(sf::Color::White);
			connect_tool.setFillColor(sf::Color::White);
			disconnect_tool.setFillColor(sf::Color::White);
			tool_state = 0;
		}
		else if (mouse_position.x >= position.x + 5 && mouse_position.x <= position.x + 35 && mouse_position.y >= position.y + 40 && mouse_position.y <= position.y + 70)
		{
			place_tool.setFillColor(sf::Color::White);
			delete_tool.setFillColor(sf::Color::Cyan);
			move_tool.setFillColor(sf::Color::White);
			select_tool.setFillColor(sf::Color::White);
			connect_tool.setFillColor(sf::Color::White);
			disconnect_tool.setFillColor(sf::Color::White);
			tool_state = 1;
		}
		else if (mouse_position.x >= position.x + 40 && mouse_position.x <= position.x + 70 && mouse_position.y >= position.y + 5 && mouse_position.y <= position.y + 35)
		{
			place_tool.setFillColor(sf::Color::White);
			delete_tool.setFillColor(sf::Color::White);
			move_tool.setFillColor(sf::Color::Cyan);
			select_tool.setFillColor(sf::Color::White);
			connect_tool.setFillColor(sf::Color::White);
			disconnect_tool.setFillColor(sf::Color::White);
			tool_state = 2;
		}
		else if (mouse_position.x >= position.x + 40 && mouse_position.x <= position.x + 70 && mouse_position.y >= position.y + 40 && mouse_position.y <= position.y + 70)
		{
			place_tool.setFillColor(sf::Color::White);
			delete_tool.setFillColor(sf::Color::White);
			move_tool.setFillColor(sf::Color::White);
			select_tool.setFillColor(sf::Color::Cyan);
			connect_tool.setFillColor(sf::Color::White);
			disconnect_tool.setFillColor(sf::Color::White);
			tool_state = 3;
		}
		else if (mouse_position.x >= position.x + 75 && mouse_position.x <= position.x + 105 && mouse_position.y >= position.y + 5 && mouse_position.y <= position.y + 35)
		{
			place_tool.setFillColor(sf::Color::White);
			delete_tool.setFillColor(sf::Color::White);
			move_tool.setFillColor(sf::Color::White);
			select_tool.setFillColor(sf::Color::White);
			connect_tool.setFillColor(sf::Color::Cyan);
			disconnect_tool.setFillColor(sf::Color::White);
			tool_state = 4;
		}
		else if (mouse_position.x >= position.x + 75 && mouse_position.x <= position.x + 105 && mouse_position.y >= position.y + 40 && mouse_position.y <= position.y + 70)
		{
			place_tool.setFillColor(sf::Color::White);
			delete_tool.setFillColor(sf::Color::White);
			move_tool.setFillColor(sf::Color::White);
			select_tool.setFillColor(sf::Color::White);
			connect_tool.setFillColor(sf::Color::White);
			disconnect_tool.setFillColor(sf::Color::Cyan);
			tool_state = 5;
		}
	}
}