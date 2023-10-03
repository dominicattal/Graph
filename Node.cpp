#include "Node.h"
#include <cmath>

Node::Node(sf::Vector2f _position, float _radius, sf::Color* _node_color, sf::Color* _node_select_color1, sf::Color* _node_select_color2)
{
	node_color = _node_color;
	node_select_color1 = _node_select_color1;
	node_select_color2 = _node_select_color2;
	position = _position;
	radius = _radius;

	node_shape.setOrigin(radius, radius);
	node_shape.setPosition(position);
	node_shape.setFillColor(*node_color);
	node_shape.setRadius(radius);
}

void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(node_shape);
}

void Node::select(bool toggle)
{
	if (!toggle)
	{
		node_shape.setFillColor(*node_select_color1);
		selected = 1;
	}
	else
	{
		node_shape.setFillColor(*node_select_color2);
		selected = 2;
	}
}

void Node::deselect()
{
	selected = 0;
	node_shape.setFillColor(*node_color);
}


void Node::setPosition(sf::Vector2f _position)
{
	position = _position;
	node_shape.setPosition(position);
}

bool Node::mouseInside(sf::Vector2f mouse_position)
{
	return mouse_position.x >= position.x - radius && mouse_position.x <= position.x + radius && mouse_position.y >= position.y - radius && mouse_position.y <= position.y + radius;
}

bool Node::connectedTo(Node* other_node)
{
	for (Node* node : connected_nodes)
	{
		if (node == other_node)
			return true;
	}
	return false;
}

float Node::distance(Node* node1, Node* node2, float scale)
{
	if (node1->distances.find(node2) == node1->distances.end())
	{
		float x_dis = node1->position.x - node2->position.x;
		float y_dis = node1->position.y - node2->position.y;
		return sqrt(x_dis * x_dis + y_dis * y_dis) * scale;
	}
	else
	{
		return node1->distances.find(node2)->second;
	}
}

void Node::updateColor()
{
	if (selected == 0)
	{
		node_shape.setFillColor(*node_color);
	}
	else if (selected == 1)
	{
		node_shape.setFillColor(*node_select_color1);
	}
	else
	{
		node_shape.setFillColor(*node_select_color2);
	}
}

void Node::reset()
{
	tested = false;
	minimal_path = -1;
	prev_node = NULL;
}