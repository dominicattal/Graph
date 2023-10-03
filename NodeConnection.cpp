#include "NodeConnection.h"

NodeConnection::NodeConnection(sf::Color* _node_connection_color, sf::Color* _node_connection_select_color)
{
	node_connection_color = _node_connection_color;
	node_connection_select_color = _node_connection_select_color;
	node_connection.resize(2);
	node_connection.setPrimitiveType(sf::Lines);
	node_connection[0].color = *node_connection_color;
	node_connection[1].color = *node_connection_color;
}

NodeConnection::~NodeConnection()
{
	disconnectNodes();
}

void NodeConnection::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(node_connection);
}

void NodeConnection::setNodes(Node* _node1, Node* _node2)
{
	node1 = _node1;
	node2 = _node2;
	node_connection[0].position = node1->position;
	node_connection[1].position = node2->position;
}

void NodeConnection::connectNodes(Node* node1, Node* node2, NodeConnection* node_connection)
{
	node1->connected_nodes.push_back(node2);
	node2->connected_nodes.push_back(node1);
	node_connection->setNodes(node1, node2);
}

void NodeConnection::disconnectNodes()
{
	for (int i = 0; i < node1->connected_nodes.size(); i++)
	{
		if (node1->connected_nodes[i] == node2)
			node1->connected_nodes.erase(node1->connected_nodes.begin() + i);
	}
	for (int i = 0; i < node2->connected_nodes.size(); i++)
	{
		if (node2->connected_nodes[i] == node1)
			node2->connected_nodes.erase(node2->connected_nodes.begin() + i);
	}
}

void NodeConnection::select()
{
	selected = true;
	node_connection[0].color = *node_connection_select_color;
	node_connection[1].color = *node_connection_select_color;
}

void NodeConnection::deselect()
{
	selected = false;
	node_connection[0].color = *node_connection_color;
	node_connection[1].color = *node_connection_color;
}

bool NodeConnection::hasNodes(Node* _node1, Node* _node2)
{
	return ((node1 == _node1 && node2 == _node2) || (node1 == _node2 && node2 == _node1));
}

bool NodeConnection::hasNode(Node* node)
{
	return node == node1 || node == node2;
}

void NodeConnection::changeColor()
{
	if (selected)
	{
		node_connection[0].color = *node_connection_select_color;
		node_connection[1].color = *node_connection_select_color;
	}
	else
	{
		node_connection[0].color = *node_connection_color;
		node_connection[1].color = *node_connection_color;
	}
}