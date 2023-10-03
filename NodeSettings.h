#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Node.h"
#pragma once
class NodeSettings : public sf::Drawable
{
	sf::RectangleShape box;
	sf::RectangleShape scale_box;
	sf::RectangleShape distance_slider;
	sf::RectangleShape distance_line;

	Node* node1;
	Node* node2;

	sf::Vector2f position;

	sf::Text none_selected_text;
	sf::Text scale_box_text;
	sf::Text distance_text;
	sf::Text distance_value_text;
	sf::Text minimal_path_text;
	sf::Text minimal_path_value_text;
	bool none_selected = true;
	bool to_scale = true;
	
public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	NodeSettings(sf::Font* font);
	bool visible = false;
	bool slider_down = false;
	bool mouseInside(sf::Vector2f mouse_position);
	void queryTools(sf::Vector2f mouse_position, float scale);
	void testSlider(sf::Vector2f mouse_position, float scale);
	void resetSlider();
	void setPosition(sf::Vector2f mouse_position, float scale);
	void reset();
	void setNodes(Node* _node1, Node* _node2, float scale);
	void setMinimalPath(float minimal_path);
};

