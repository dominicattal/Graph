#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

class GraphSettings : public sf::Drawable
{
	sf::RectangleShape box;

	sf::RectangleShape arrow_right;
	sf::RectangleShape arrow_left;

	sf::Text present_light_text;
	sf::Text present_dark_text;
	sf::Text present_warm_text;
	sf::Text present_cool_text;
	sf::RectangleShape present_light;
	sf::RectangleShape present_dark;
	sf::RectangleShape present_warm;
	sf::RectangleShape present_cool;
	
	sf::RectangleShape r_slider;
	sf::RectangleShape r_slider_limit;
	sf::RectangleShape r_add;
	sf::RectangleShape r_sub;
	sf::RectangleShape g_slider;
	sf::RectangleShape g_slider_limit;
	sf::RectangleShape g_add;
	sf::RectangleShape g_sub;
	sf::RectangleShape b_slider;
	sf::RectangleShape b_slider_limit;
	sf::RectangleShape b_add;
	sf::RectangleShape b_sub;
	sf::Text R;
	sf::Text G;
	sf::Text B;
	
	sf::Text title;
	sf::Vector2f position;
	short page = 0;

public:
	sf::Color* background_color = NULL;
	sf::Color* node_color = NULL;
	sf::Color* node_select_color1 = NULL;
	sf::Color* node_select_color2 = NULL;
	sf::Color* node_connection_color = NULL;
	sf::Color* node_connection_select_color = NULL;
	sf::Color* chosen_color = NULL;

	bool r_slider_down = false;
	bool g_slider_down = false;
	bool b_slider_down = false;
	GraphSettings(sf::Font* font);
	bool visible = false;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool mouseInside(sf::Vector2f mouse_position);
	void setPosition(sf::Vector2f _position);
	void setPage();
	short getPage();
	void queryTools(sf::Vector2f mouse_position);
	void resetSliders();
	void testSliders(sf::Vector2f mouse_position);
};

