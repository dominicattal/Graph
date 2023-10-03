#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <map>
#pragma once

class Node : public sf::Drawable
{
	sf::CircleShape node_shape;
	sf::Color* node_color;
	sf::Color* node_select_color1;
	sf::Color* node_select_color2;
	
public:
	sf::Vector2f position;
	std::map<Node*, float> distances;
	short selected = 0;
	bool tested;
	bool visible = true;
	float minimal_path;
	Node* prev_node = NULL;
	float radius;
	std::vector<Node*> connected_nodes;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void select(bool toggle);
	void deselect();
	bool mouseInside(sf::Vector2f mouse_position);
	bool connectedTo(Node* other_node);
	void setPosition(sf::Vector2f _position);
	static float distance(Node* node1, Node* node2, float scale);
	void updateColor();
	void reset();
	Node(sf::Vector2f position, float _radius, sf::Color* _node_color, sf::Color* _node_select_color1, sf::Color* _node_select_color2);
};