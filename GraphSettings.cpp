#include "GraphSettings.h"
#include <string>

GraphSettings::GraphSettings(sf::Font* font)
{
	int distance_between_sliders = 25;
	int distance_from_top = 45;

	sf::Texture* add_texture = new sf::Texture();
	sf::Texture* sub_texture = new sf::Texture();
	add_texture->loadFromFile("assets/add.png");
	sub_texture->loadFromFile("assets/subtract.png");

	sf::Texture* arrow_right_texture = new sf::Texture();
	sf::Texture* arrow_left_texture = new sf::Texture();
	arrow_right_texture->loadFromFile("assets/arrow_right.png");
	arrow_left_texture->loadFromFile("assets/arrow_left.png");

	box.setSize(sf::Vector2f(148, 170));
	box.setOutlineThickness(2);
	box.setOutlineColor(sf::Color::Black);

	arrow_left.setSize(sf::Vector2f(24, 19));
	arrow_left.setOrigin(-45, -(distance_from_top + 2 * distance_between_sliders + 50));
	arrow_left.setTexture(arrow_left_texture);

	arrow_right.setSize(sf::Vector2f(24, 19));
	arrow_right.setOrigin(-79, -(distance_from_top + 2 * distance_between_sliders + 50));
	arrow_right.setTexture(arrow_right_texture);

	title.setCharacterSize(16);
	title.setFont(*font);
	title.setFillColor(sf::Color::Black);
	title.setString("Background");

	present_light.setSize(sf::Vector2f(100, 22));
	present_light.setOutlineThickness(1);
	present_light.setOrigin(sf::Vector2f(-24, -30));
	present_light.setOutlineColor(sf::Color::Black);

	present_dark.setSize(sf::Vector2f(100, 22));
	present_dark.setOutlineThickness(1);
	present_dark.setOrigin(sf::Vector2f(-24, -58));
	present_dark.setOutlineColor(sf::Color::Black);

	present_warm.setSize(sf::Vector2f(100, 22));
	present_warm.setOutlineThickness(1);
	present_warm.setOrigin(sf::Vector2f(-24, -86));
	present_warm.setOutlineColor(sf::Color::Black);

	present_cool.setSize(sf::Vector2f(100, 22));
	present_cool.setOutlineThickness(1);
	present_cool.setOrigin(sf::Vector2f(-24, -114));
	present_cool.setOutlineColor(sf::Color::Black);

	present_light_text.setCharacterSize(16);
	present_light_text.setFont(*font);
	present_light_text.setFillColor(sf::Color::Black);
	present_light_text.setString("Light");
	present_light_text.setOrigin(sf::Vector2f(present_light.getOrigin().x - present_light.getLocalBounds().width / 2 + present_light_text.getLocalBounds().width / 2, present_light.getOrigin().y - present_light.getLocalBounds().height / 2 + present_light_text.getLocalBounds().height / 2 + 4));

	present_dark_text.setCharacterSize(16);
	present_dark_text.setFont(*font);
	present_dark_text.setFillColor(sf::Color::Black);
	present_dark_text.setString("Dark");
	present_dark_text.setOrigin(sf::Vector2f(present_dark.getOrigin().x - present_dark.getLocalBounds().width / 2 + present_dark_text.getLocalBounds().width / 2, present_dark.getOrigin().y - present_dark.getLocalBounds().height / 2 + present_dark_text.getLocalBounds().height / 2 + 4));

	present_warm_text.setCharacterSize(16);
	present_warm_text.setFont(*font);
	present_warm_text.setFillColor(sf::Color::Black);
	present_warm_text.setString("Warm");
	present_warm_text.setOrigin(sf::Vector2f(present_warm.getOrigin().x - present_warm.getLocalBounds().width / 2 + present_warm_text.getLocalBounds().width / 2, present_warm.getOrigin().y - present_warm.getLocalBounds().height / 2 + present_warm_text.getLocalBounds().height / 2 + 4));

	present_cool_text.setCharacterSize(16);
	present_cool_text.setFont(*font);
	present_cool_text.setFillColor(sf::Color::Black);
	present_cool_text.setString("Cool");
	present_cool_text.setOrigin(sf::Vector2f(present_cool.getOrigin().x - present_cool.getLocalBounds().width / 2 + present_cool_text.getLocalBounds().width / 2, present_cool.getOrigin().y - present_cool.getLocalBounds().height / 2 + present_cool_text.getLocalBounds().height / 2 + 4));

	R.setCharacterSize(16);
	R.setFont(*font);
	R.setFillColor(sf::Color::Black);
	R.setOrigin(-10, -(distance_from_top + 2 * distance_between_sliders + 17));

	r_add.setSize(sf::Vector2f(9, 9));
	r_add.setOrigin(-33, -(distance_from_top + 2 * distance_between_sliders + 38));
	r_add.setTexture(add_texture);

	r_sub.setSize(sf::Vector2f(9, 9));
	r_sub.setOrigin(-14, -(distance_from_top + 2 * distance_between_sliders + 38));
	r_sub.setTexture(sub_texture);

	G.setCharacterSize(16);
	G.setFont(*font);
	G.setFillColor(sf::Color::Black);
	G.setOrigin(-56, -(distance_from_top + 2 * distance_between_sliders + 17));

	g_add.setSize(sf::Vector2f(9, 9));
	g_add.setOrigin(-79, -(distance_from_top + 2 * distance_between_sliders + 38));
	g_add.setTexture(add_texture);

	g_sub.setSize(sf::Vector2f(9, 9));
	g_sub.setOrigin(-60, -(distance_from_top + 2 * distance_between_sliders + 38));
	g_sub.setTexture(sub_texture);

	B.setCharacterSize(16);
	B.setFont(*font);
	B.setFillColor(sf::Color::Black);
	B.setOrigin(-102, -(distance_from_top + 2 * distance_between_sliders + 17));

	b_add.setSize(sf::Vector2f(9, 9));
	b_add.setOrigin(-125, -(distance_from_top + 2 * distance_between_sliders + 38));
	b_add.setTexture(add_texture);

	b_sub.setSize(sf::Vector2f(9, 9));
	b_sub.setOrigin(-106, -(distance_from_top + 2 * distance_between_sliders + 38));
	b_sub.setTexture(sub_texture);

	r_slider.setSize(sf::Vector2f(8, 16));
	r_slider.setOrigin(sf::Vector2f(-6, -(distance_from_top - 7)));
	r_slider.setOutlineThickness(1);
	r_slider.setOutlineColor(sf::Color::Black);
	r_slider.setFillColor(sf::Color::Red);

	r_slider_limit.setSize(sf::Vector2f(128, 2));
	r_slider_limit.setOrigin(sf::Vector2f(-10, -(distance_from_top)));
	r_slider_limit.setFillColor(sf::Color::Black);

	g_slider.setSize(sf::Vector2f(8, 16));
	g_slider.setOrigin(sf::Vector2f(-6, -(distance_from_top + distance_between_sliders - 7)));
	g_slider.setOutlineThickness(1);
	g_slider.setOutlineColor(sf::Color::Black);
	g_slider.setFillColor(sf::Color::Green);

	g_slider_limit.setSize(sf::Vector2f(128, 2));
	g_slider_limit.setOrigin(sf::Vector2f(-10, -(distance_from_top + distance_between_sliders)));
	g_slider_limit.setFillColor(sf::Color::Black);

	b_slider.setSize(sf::Vector2f(8, 16));
	b_slider.setOrigin(sf::Vector2f(-6, -(distance_from_top + 2 * distance_between_sliders - 7)));
	b_slider.setOutlineThickness(1);
	b_slider.setOutlineColor(sf::Color::Black);
	b_slider.setFillColor(sf::Color::Blue);

	b_slider_limit.setSize(sf::Vector2f(128, 2));
	b_slider_limit.setOrigin(sf::Vector2f(-10, -(distance_from_top + 2 * distance_between_sliders)));
	b_slider_limit.setFillColor(sf::Color::Black);
}

void GraphSettings::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (visible)
	{
		target.draw(box);
		target.draw(title);
		if (page != 6)
		{
			target.draw(r_slider_limit);
			target.draw(r_slider);
			target.draw(r_add);
			target.draw(r_sub);
			target.draw(g_slider_limit);
			target.draw(g_slider);
			target.draw(g_add);
			target.draw(g_sub);
			target.draw(b_slider_limit);
			target.draw(b_slider);
			target.draw(b_add);
			target.draw(b_sub);
			target.draw(R);
			target.draw(G);
			target.draw(B);
		}
		if (page == 6)
		{
			target.draw(present_light);
			target.draw(present_dark);
			target.draw(present_warm);
			target.draw(present_cool);
			target.draw(present_light_text);
			target.draw(present_dark_text);
			target.draw(present_warm_text);
			target.draw(present_cool_text);
		}
		if (page != 6)
			target.draw(arrow_right);
		if (page != 0)
			target.draw(arrow_left);
	}
}

bool GraphSettings::mouseInside(sf::Vector2f mouse_position)
{
	sf::Vector2f gui_position = box.getPosition();
	return mouse_position.x >= gui_position.x && mouse_position.x <= gui_position.x + box.getSize().x && mouse_position.y >= gui_position.y && mouse_position.y <= gui_position.y + box.getSize().y  && visible;
}

void GraphSettings::setPosition(sf::Vector2f _position)
{
	position = _position;
	box.setPosition(position);

	arrow_right.setPosition(position);
	arrow_left.setPosition(position);

	if (page == 6)
	{
		present_light.setPosition(position);
		present_dark.setPosition(position);
		present_warm.setPosition(position);
		present_cool.setPosition(position);
		present_light_text.setPosition(position);
		present_dark_text.setPosition(position);
		present_warm_text.setPosition(position);
		present_cool_text.setPosition(position);
	}
	if (chosen_color != NULL)
	{
		R.setString("R " + std::to_string(chosen_color->r));
		R.setPosition(position);
		r_add.setPosition(position);
		r_sub.setPosition(position);
		r_slider_limit.setPosition(position);
		r_slider.setPosition(sf::Vector2f(position.x + 128 * chosen_color->r / 255, position.y));

		G.setString("G " + std::to_string(chosen_color->g));
		G.setPosition(position);
		g_add.setPosition(position);
		g_sub.setPosition(position);
		g_slider_limit.setPosition(position);
		g_slider.setPosition(sf::Vector2f(position.x + 128 * chosen_color->g / 255, position.y));

		B.setString("B " + std::to_string(chosen_color->b));
		B.setPosition(position);
		b_add.setPosition(position);
		b_sub.setPosition(position);
		b_slider_limit.setPosition(position);
		b_slider.setPosition(sf::Vector2f(position.x + 128 * chosen_color->b / 255, position.y));
	}
	
	title.setPosition(sf::Vector2f(position.x + (box.getSize().x - title.getLocalBounds().width) / 2, position.y + 5));
}

void GraphSettings::testSliders(sf::Vector2f mouse_position)
{
	if (mouse_position.x < r_slider_limit.getPosition().x + r_slider_limit.getSize().x - r_slider_limit.getOrigin().x && mouse_position.x >= r_slider_limit.getPosition().x - r_slider_limit.getOrigin().x)
	{
		if (r_slider_down)
		{
			chosen_color->r = (255.0 / 128) * (mouse_position.x - (r_slider_limit.getPosition().x + r_slider_limit.getSize().x - r_slider_limit.getOrigin().x));
			r_slider.setPosition(sf::Vector2f(position.x + 128 * chosen_color->r / 255, position.y));
			R.setString("R " + std::to_string(chosen_color->r));
		}
		if (g_slider_down)
		{
			chosen_color->g = (255.0 / 128) * (mouse_position.x - (g_slider_limit.getPosition().x + g_slider_limit.getSize().x - g_slider_limit.getOrigin().x));
			g_slider.setPosition(sf::Vector2f(position.x + 128 * chosen_color->g / 255, position.y));
			G.setString("G " + std::to_string(chosen_color->g));
		}
		if (b_slider_down)
		{
			chosen_color->b = (255.0 / 128) * (mouse_position.x - (b_slider_limit.getPosition().x + b_slider_limit.getSize().x - b_slider_limit.getOrigin().x));
			b_slider.setPosition(sf::Vector2f(position.x + 128 * chosen_color->b / 255, position.y));
			B.setString("B " + std::to_string(chosen_color->b));
		}
	}
	else if (mouse_position.x < r_slider_limit.getPosition().x - r_slider_limit.getOrigin().x)
	{
		if (r_slider_down)
		{
			chosen_color->r = 0;
			r_slider.setPosition(sf::Vector2f(position.x + 128 * chosen_color->r / 255, position.y));
			R.setString("R " + std::to_string(chosen_color->r));
		}
		if (g_slider_down)
		{
			chosen_color->g = 0;
			g_slider.setPosition(sf::Vector2f(position.x + 128 * chosen_color->g / 255, position.y));
			G.setString("G " + std::to_string(chosen_color->g));
		}
		if (b_slider_down)
		{
			chosen_color->b = 0;
			b_slider.setPosition(sf::Vector2f(position.x + 128 * chosen_color->b / 255, position.y));
			B.setString("B " + std::to_string(chosen_color->b));
		}
	}
	else if (mouse_position.x >= r_slider_limit.getPosition().x + r_slider_limit.getSize().x - r_slider_limit.getOrigin().x)
	{ 
		if (r_slider_down)
		{
			chosen_color->r = 255;
			r_slider.setPosition(sf::Vector2f(position.x + 128 * chosen_color->r / 255, position.y));
			R.setString("R " + std::to_string(chosen_color->r));
		}
		if (g_slider_down)
		{
			chosen_color->g = 255;
			g_slider.setPosition(sf::Vector2f(position.x + 128 * chosen_color->g / 255, position.y));
			G.setString("G " + std::to_string(chosen_color->g));
		}
		if (b_slider_down)
		{
			chosen_color->b = 255;
			b_slider.setPosition(sf::Vector2f(position.x + 128 * chosen_color->b / 255, position.y));
			B.setString("B " + std::to_string(chosen_color->b));
		}
	}
}

void GraphSettings::resetSliders()
{
	r_slider_down = false;
	g_slider_down = false;
	b_slider_down = false;
}

void GraphSettings::queryTools(sf::Vector2f mouse_position)
{
	if (visible)
	{
		if (page != 6)
		{
			if (mouse_position.x >= r_slider.getPosition().x - r_slider.getOrigin().x && mouse_position.x <= r_slider.getPosition().x - r_slider.getOrigin().x + r_slider.getSize().x
				&& mouse_position.y >= r_slider.getPosition().y - r_slider.getOrigin().y && mouse_position.y <= r_slider.getPosition().y - r_slider.getOrigin().y + r_slider.getSize().y)
			{
				r_slider_down = true;
			}
			else if (mouse_position.x >= g_slider.getPosition().x - g_slider.getOrigin().x && mouse_position.x <= g_slider.getPosition().x - g_slider.getOrigin().x + g_slider.getSize().x
				&& mouse_position.y >= g_slider.getPosition().y - g_slider.getOrigin().y && mouse_position.y <= g_slider.getPosition().y - g_slider.getOrigin().y + g_slider.getSize().y)
			{
				g_slider_down = true;
			}
			else if (mouse_position.x >= b_slider.getPosition().x - b_slider.getOrigin().x && mouse_position.x <= b_slider.getPosition().x - b_slider.getOrigin().x + b_slider.getSize().x
				&& mouse_position.y >= b_slider.getPosition().y - b_slider.getOrigin().y && mouse_position.y <= b_slider.getPosition().y - b_slider.getOrigin().y + b_slider.getSize().y)
			{
				b_slider_down = true;
			}
			else if (mouse_position.x >= position.x - r_add.getOrigin().x && mouse_position.x <= position.x - r_add.getOrigin().x + r_add.getSize().x
				&& mouse_position.y >= position.y - r_add.getOrigin().y && mouse_position.y <= position.y - r_add.getOrigin().y + r_add.getSize().y)
			{
				if (chosen_color->r < 255)
				{
					chosen_color->r++;
					r_slider.setPosition(sf::Vector2f(position.x + 128 * chosen_color->r / 255, position.y));
					R.setString("R " + std::to_string(chosen_color->r));
				}
			}
			else if (mouse_position.x >= position.x - g_add.getOrigin().x && mouse_position.x <= position.x - g_add.getOrigin().x + g_add.getSize().x
				&& mouse_position.y >= position.y - g_add.getOrigin().y && mouse_position.y <= position.y - g_add.getOrigin().y + g_add.getSize().y)
			{
				if (chosen_color->g < 255)
				{
					chosen_color->g++;
					g_slider.setPosition(sf::Vector2f(position.x + 128 * chosen_color->g / 255, position.y));
					G.setString("G " + std::to_string(chosen_color->g));
				}
			}
			else if (mouse_position.x >= position.x - b_add.getOrigin().x && mouse_position.x <= position.x - b_add.getOrigin().x + b_add.getSize().x
				&& mouse_position.y >= position.y - b_add.getOrigin().y && mouse_position.y <= position.y - b_add.getOrigin().y + b_add.getSize().y)
			{
				if (chosen_color->b < 255)
				{
					chosen_color->b++;
					b_slider.setPosition(sf::Vector2f(position.x + 128 * chosen_color->b / 255, position.y));
					B.setString("B " + std::to_string(chosen_color->b));
				}
			}
			else if (mouse_position.x >= position.x - r_sub.getOrigin().x && mouse_position.x <= position.x - r_sub.getOrigin().x + r_sub.getSize().x
				&& mouse_position.y >= position.y - r_sub.getOrigin().y && mouse_position.y <= position.y - r_sub.getOrigin().y + r_sub.getSize().y)
			{
				if (chosen_color->r > 0)
				{
					chosen_color->r--;
					r_slider.setPosition(sf::Vector2f(position.x + 128 * chosen_color->r / 255, position.y));
					R.setString("R " + std::to_string(chosen_color->r));
				}
			}
			else if (mouse_position.x >= position.x - g_sub.getOrigin().x && mouse_position.x <= position.x - g_sub.getOrigin().x + g_sub.getSize().x
				&& mouse_position.y >= position.y - g_sub.getOrigin().y && mouse_position.y <= position.y - g_sub.getOrigin().y + g_sub.getSize().y)
			{
				if (chosen_color->g > 0)
				{
					chosen_color->g--;
					g_slider.setPosition(sf::Vector2f(position.x + 128 * chosen_color->g / 255, position.y));
					G.setString("G " + std::to_string(chosen_color->g));
				}
			}
			else if (mouse_position.x >= position.x - b_sub.getOrigin().x && mouse_position.x <= position.x - b_sub.getOrigin().x + b_sub.getSize().x
				&& mouse_position.y >= position.y - b_sub.getOrigin().y && mouse_position.y <= position.y - b_sub.getOrigin().y + b_sub.getSize().y)
			{
				if (chosen_color->b > 0)
				{
					chosen_color->b--;
					b_slider.setPosition(sf::Vector2f(position.x + 128 * chosen_color->b / 255, position.y));
					B.setString("B " + std::to_string(chosen_color->b));
				}
			}
		}
		if (page == 6)
		{
			if (mouse_position.x >= position.x - present_light.getOrigin().x && mouse_position.x <= position.x - present_light.getOrigin().x + present_light.getSize().x
				&& mouse_position.y >= position.y - present_light.getOrigin().y && mouse_position.y <= position.y - present_light.getOrigin().y + present_light.getSize().y)
			{
				background_color->r             = 230; background_color->g             = 230; background_color->b             = 230;
				node_color->r                   = 0  ; node_color->g                   = 0  ; node_color->b                   = 255;
				node_select_color1->r           = 0  ; node_select_color1->g           = 255; node_select_color1->b           = 0  ;
				node_select_color2->r           = 255; node_select_color2->g           = 0  ; node_select_color2->b           = 255;
				node_connection_color->r        = 255; node_connection_color->g        = 255; node_connection_color->b        = 0  ;
				node_connection_select_color->r = 255; node_connection_select_color->g = 0  ; node_connection_select_color->b = 0  ;
			}
			else if (mouse_position.x >= position.x - present_dark.getOrigin().x && mouse_position.x <= position.x - present_dark.getOrigin().x + present_dark.getSize().x
				&& mouse_position.y >= position.y - present_dark.getOrigin().y && mouse_position.y <= position.y - present_dark.getOrigin().y + present_dark.getSize().y)
			{
				background_color->r             = 16 ; background_color->g             = 16 ; background_color->b             = 16 ;
				node_color->r                   = 255; node_color->g                   = 160; node_color->b                   = 0  ;
				node_select_color1->r           = 90 ; node_select_color1->g           = 140; node_select_color1->b           = 190;
				node_select_color2->r           = 90 ; node_select_color2->g           = 190; node_select_color2->b           = 140;
				node_connection_color->r        = 40 ; node_connection_color->g        = 40 ; node_connection_color->b        = 160;
				node_connection_select_color->r = 240; node_connection_select_color->g = 240; node_connection_select_color->b = 240;
			}
			else if (mouse_position.x >= position.x - present_warm.getOrigin().x && mouse_position.x <= position.x - present_warm.getOrigin().x + present_warm.getSize().x
				&& mouse_position.y >= position.y - present_warm.getOrigin().y && mouse_position.y <= position.y - present_warm.getOrigin().y + present_warm.getSize().y)
			{
				background_color->r             = 255; background_color->g             = 150; background_color->b             = 0  ;
				node_color->r                   = 255; node_color->g                   = 0  ; node_color->b                   = 0  ;
				node_select_color1->r           = 255; node_select_color1->g           = 0  ; node_select_color1->b           = 255;
				node_select_color2->r           = 255; node_select_color2->g           = 255; node_select_color2->b           = 0  ;
				node_connection_color->r        = 150; node_connection_color->g        = 50 ; node_connection_color->b        = 50 ;
				node_connection_select_color->r = 255; node_connection_select_color->g = 0  ; node_connection_select_color->b = 0  ;
			}
			else if (mouse_position.x >= position.x - present_cool.getOrigin().x && mouse_position.x <= position.x - present_cool.getOrigin().x + present_cool.getSize().x
				&& mouse_position.y >= position.y - present_cool.getOrigin().y && mouse_position.y <= position.y - present_cool.getOrigin().y + present_cool.getSize().y)
			{
				background_color->r             = 0  ; background_color->g             = 160; background_color->b             = 250;
				node_color->r                   = 0  ; node_color->g                   = 255; node_color->b                   = 100;
				node_select_color1->r           = 130; node_select_color1->g           = 0  ; node_select_color1->b           = 255;
				node_select_color2->r           = 255; node_select_color2->g           = 255; node_select_color2->b           = 255;
				node_connection_color->r        = 0  ; node_connection_color->g        = 40 ; node_connection_color->b        = 160;
				node_connection_select_color->r = 255; node_connection_select_color->g = 0  ; node_connection_select_color->b = 255;
			}
		}
		if (mouse_position.x >= position.x - arrow_left.getOrigin().x && mouse_position.x <= position.x - arrow_left.getOrigin().x + arrow_left.getSize().x
			&& mouse_position.y >= position.y - arrow_left.getOrigin().y && mouse_position.y <= position.y - arrow_left.getOrigin().y + arrow_left.getSize().y)
		{
			if (page > 0)
			{
				page--;
				setPage();
			}
		}
		else if (mouse_position.x >= position.x - arrow_right.getOrigin().x && mouse_position.x <= position.x - arrow_right.getOrigin().x + arrow_right.getSize().x
			&& mouse_position.y >= position.y - arrow_right.getOrigin().y && mouse_position.y <= position.y - arrow_right.getOrigin().y + arrow_right.getSize().y)
		{
			if (page < 6)
			{
				page++;
				setPage();
			}
		}
	}
}

void GraphSettings::setPage()
{
	switch (page)
	{
	case 0:
		chosen_color = background_color;
		title.setString("Background");
		setPosition(position);
		break;
	case 1:
		chosen_color = node_color;
		title.setString("Node");
		setPosition(position);
		break;
	case 2:
		chosen_color = node_select_color1;
		title.setString("Node Select 1");
		setPosition(position);
		break;
	case 3:
		chosen_color = node_select_color2;
		title.setString("Node Select 2");
		setPosition(position);
		break;
	case 4:
		chosen_color = node_connection_color;
		title.setString("Connection");
		setPosition(position);
		break;
	case 5:
		chosen_color = node_connection_select_color;
		title.setString("Connection Select");
		setPosition(position);
		break;
	case 6:
		chosen_color = NULL;
		title.setString("Presents");
		setPosition(position);
		break;
	}
}

short GraphSettings::getPage()
{
	return page;
}