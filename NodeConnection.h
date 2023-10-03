#pragma once
#include <SFML/Graphics/VertexArray.hpp>
#include "Node.h"

class NodeConnection : public sf::Drawable
{
public:
	Node* node1;
	Node* node2;
	sf::VertexArray node_connection;
	sf::Color* node_connection_color = NULL;
	sf::Color* node_connection_select_color = NULL;
	bool selected = false;
	NodeConnection(sf::Color* _node_connection_color, sf::Color* _node_connection_select_color);
	~NodeConnection();
	void setNodes(Node* _node1, Node* _node2);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	static void connectNodes(Node* node1, Node* node2, NodeConnection* node_connection);
	void changeColor();
	bool hasNodes(Node* node1, Node* node2);
	bool hasNode(Node* node);
	void select();
	void deselect();
	void disconnectNodes();
};

