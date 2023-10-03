#include "NodeSettings.h"

NodeSettings::NodeSettings(sf::Font* font)
{
	box.setSize(sf::Vector2f(160, 100));
	box.setOutlineColor(sf::Color::Black);
	box.setOutlineThickness(2);

	none_selected_text.setFont(*font);
	none_selected_text.setString("Select two Nodes");
	none_selected_text.setFillColor(sf::Color::Black);
	none_selected_text.setCharacterSize(16);
	none_selected_text.setOrigin((none_selected_text.getLocalBounds().width - box.getSize().x) / 2, -5);

	scale_box.setSize(sf::Vector2f(16, 16));
	scale_box.setOutlineColor(sf::Color::Black);
	scale_box.setFillColor(sf::Color::Green);
	scale_box.setOutlineThickness(1);
	scale_box.setOrigin(-5, -6);

	scale_box_text.setFont(*font);
	scale_box_text.setString("Scale");
	scale_box_text.setFillColor(sf::Color::Black);
	scale_box_text.setCharacterSize(16);
	scale_box_text.setOrigin(-26, -5);

	distance_text.setFont(*font);
	distance_text.setString("Distance:");
	distance_text.setFillColor(sf::Color::Black);
	distance_text.setCharacterSize(16);
	distance_text.setOrigin(-5, -28);

	distance_value_text.setFont(*font);
	distance_value_text.setString("12.34");
	distance_value_text.setFillColor(sf::Color::Black);
	distance_value_text.setCharacterSize(16);
	distance_value_text.setOrigin(-distance_text.getLocalBounds().width - 6, -28);

	distance_line.setSize(sf::Vector2f(box.getSize().x - 16, 2));
	distance_line.setOrigin(-8, -60);
	distance_line.setFillColor(sf::Color::Black);

	distance_slider.setSize(sf::Vector2f(8, 16));
	distance_slider.setOutlineColor(sf::Color::Black);
	distance_slider.setOutlineThickness(1);
	distance_slider.setOrigin(-4, -53);

	minimal_path_text.setFont(*font);
	minimal_path_text.setString("Min Path:");
	minimal_path_text.setFillColor(sf::Color::Black);
	minimal_path_text.setCharacterSize(16);
	minimal_path_text.setOrigin(-5, -75);

	minimal_path_value_text.setFont(*font);
	minimal_path_value_text.setString("Press D");
	minimal_path_value_text.setFillColor(sf::Color::Black);
	minimal_path_value_text.setCharacterSize(16);
	minimal_path_value_text.setOrigin(-minimal_path_text.getLocalBounds().width - 6, -75);
}

void NodeSettings::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (visible)
	{
		target.draw(box);
		if (node1 == NULL)
		{
			target.draw(none_selected_text);
		}
		else
		{
			target.draw(scale_box);
			target.draw(scale_box_text);
			target.draw(distance_text);
			target.draw(distance_value_text);
			target.draw(distance_line);
			target.draw(distance_slider);
			target.draw(minimal_path_text);
			target.draw(minimal_path_value_text);
		}
	}
}

void NodeSettings::setPosition(sf::Vector2f mouse_position, float scale)
{
	position = mouse_position;
	box.setPosition(mouse_position);
	none_selected_text.setPosition(mouse_position);
	scale_box.setPosition(mouse_position);
	scale_box_text.setPosition(mouse_position);
	distance_text.setPosition(mouse_position);
	distance_value_text.setPosition(mouse_position);
	distance_line.setPosition(mouse_position);
	if (to_scale)
	{
		distance_slider.setPosition(position.x + distance_line.getSize().x / 2, position.y);
	}
	else
	{
		float x_dis = node1->position.x - node2->position.x;
		float y_dis = node1->position.y - node2->position.y;
		float dis = sqrt(x_dis * x_dis + y_dis * y_dis) * scale;
		if (dis != 0)
		{
			float val = std::log10(node1->distances.find(node2)->second / dis);
			distance_slider.setPosition(position.x + (val + 1) * distance_line.getSize().x / 2, position.y);
		}
	}
	minimal_path_text.setPosition(mouse_position);
	minimal_path_value_text.setPosition(mouse_position);
}

void NodeSettings::reset()
{
	node1 = NULL;
	node2 = NULL;
}

void NodeSettings::setNodes(Node* _node1, Node* _node2, float scale)
{
	node1 = _node1;
	node2 = _node2;
	distance_value_text.setString(std::to_string(Node::distance(node1, node2, scale)));
	if (distance_text.getLocalBounds().width + distance_value_text.getLocalBounds().width + 16 > 160)
	{
		box.setSize(sf::Vector2f(distance_text.getLocalBounds().width + 16 + distance_value_text.getLocalBounds().width, box.getSize().y));
	}
	else
	{
		box.setSize(sf::Vector2f(160, 100));
	}
	if (_node1->distances.find(_node2) == _node1->distances.end())
	{
		to_scale = true;
	}
	else
	{
		to_scale = false;
	}
}

void NodeSettings::setMinimalPath(float minimal_path) 
{
	if (minimal_path != -1)
	{
		minimal_path_value_text.setString(std::to_string(minimal_path));
		if (minimal_path_text.getLocalBounds().width + minimal_path_value_text.getLocalBounds().width + 16 > 160)
		{
			box.setSize(sf::Vector2f(minimal_path_text.getLocalBounds().width + 16 + minimal_path_value_text.getLocalBounds().width, box.getSize().y));
		}
		else
		{
			box.setSize(sf::Vector2f(160, 100));
		}
	}
	else
	{
		minimal_path_value_text.setString("No Path");
	}
}

bool NodeSettings::mouseInside(sf::Vector2f mouse_position)
{
	sf::Vector2f gui_position = box.getPosition();
	return mouse_position.x >= gui_position.x && mouse_position.x <= gui_position.x + box.getSize().x && mouse_position.y >= gui_position.y && mouse_position.y <= gui_position.y + box.getSize().y && visible;
}

void NodeSettings::queryTools(sf::Vector2f mouse_position, float scale)
{
	if (mouse_position.x >= distance_slider.getPosition().x - distance_slider.getOrigin().x && mouse_position.x <= distance_slider.getPosition().x - distance_slider.getOrigin().x + distance_slider.getSize().x
		&& mouse_position.y >= distance_slider.getPosition().y - distance_slider.getOrigin().y && mouse_position.y <= distance_slider.getPosition().y - distance_slider.getOrigin().y + distance_slider.getSize().y)
	{
		slider_down = true;
		to_scale = false;
		scale_box.setFillColor(sf::Color::Transparent);
	}
	else if (mouse_position.x >= scale_box.getPosition().x - scale_box.getOrigin().x && mouse_position.x <= scale_box.getPosition().x - scale_box.getOrigin().x + scale_box.getSize().x
		&& mouse_position.y >= scale_box.getPosition().y - scale_box.getOrigin().y && mouse_position.y <= scale_box.getPosition().y - scale_box.getOrigin().y + scale_box.getSize().y)
	{
		if (!to_scale)
		{
			scale_box.setFillColor(sf::Color::Green);
			distance_slider.setPosition(position.x + distance_line.getSize().x / 2, position.y);
			node1->distances.erase(node1->distances.find(node2));
			node2->distances.erase(node2->distances.find(node1));
			to_scale = true;
		}
		else
		{
			scale_box.setFillColor(sf::Color::Transparent);
			to_scale = false;
		}
	}
}

void NodeSettings::resetSlider()
{
	slider_down = false;
}

void NodeSettings::testSlider(sf::Vector2f mouse_position, float scale)
{
	if (slider_down)
	{
		if (mouse_position.x > distance_line.getPosition().x - distance_line.getOrigin().x && mouse_position.x < distance_line.getPosition().x + distance_line.getSize().x - distance_line.getOrigin().x)
		{
			distance_slider.setPosition(mouse_position.x - 8, position.y);
			float x_dis = node1->position.x - node2->position.x;
			float y_dis = node1->position.y - node2->position.y;
			node1->distances[node2] = sqrt(x_dis * x_dis + y_dis * y_dis) * scale * std::pow(10, (mouse_position.x - position.x - 8) / (distance_line.getSize().x / 2) - 1);
			node2->distances[node1] = sqrt(x_dis * x_dis + y_dis * y_dis) * scale * std::pow(10, (mouse_position.x - position.x - 8) / (distance_line.getSize().x / 2) - 1);
		}
		else if (mouse_position.x <= distance_line.getPosition().x - distance_line.getOrigin().x)
		{
			distance_slider.setPosition(position);
			node1->distances[node2] = 0;
			node2->distances[node1] = 0;
		}
		else
		{
			distance_slider.setPosition(position.x + distance_line.getSize().x, position.y);
			float x_dis = node1->position.x - node2->position.x;
			float y_dis = node1->position.y - node2->position.y;
			node1->distances[node2] = sqrt(x_dis * x_dis + y_dis * y_dis) * scale * 10;
			node2->distances[node1] = sqrt(x_dis * x_dis + y_dis * y_dis) * scale * 10;
		}
	}
}