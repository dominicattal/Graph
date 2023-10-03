#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#pragma once

class GUI : public sf::Drawable
{
	sf::RectangleShape box;

	sf::Texture* place_tool_texture;
	sf::RectangleShape place_tool;

	sf::Texture* delete_tool_texture;
	sf::RectangleShape delete_tool;

	sf::Texture* connect_tool_texture;
	sf::RectangleShape connect_tool;

	sf::Texture* disconnect_tool_texture;
	sf::RectangleShape disconnect_tool;

	sf::Texture* move_tool_texture;
	sf::RectangleShape move_tool;

	sf::Texture* select_tool_texture;
	sf::RectangleShape select_tool;
	sf::RectangleShape selection;

	sf::Color* select_color1;
	sf::Color* select_color2;
	
public:
	bool visible = false;
	bool selection_visible = false;
	bool selection_state = false;
	short tool_state = 0;
	sf::Vector2f selection_position;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setSelectionPosition(sf::Vector2f position);
	void setSelectionSize(sf::Vector2f bottom_right);
	void setSelectionState(bool state);
	sf::Vector2f getSelectionPosition();
	sf::Vector2f getSelectionSize();
	void resetSelection();
	void setPosition(sf::Vector2f position);
	bool mouseInside(sf::Vector2f mouse_position);
	void queryTools(sf::Vector2f mouse_position);
	GUI(sf::Color* _select_color1, sf::Color* _select_color2);
};

