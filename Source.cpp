#include <SFML/Graphics.hpp>
#include "Node.h"
#include "GUI.h"
#include "NodeConnection.h"
#include "GraphSettings.h"
#include "NodeSettings.h"
#include <fstream>
#include <iostream>
#include <vector>

/*
drag and move screen
hide and show nodes
gui for node settings, controls
save feature
tools to make certain shapes, binary tree
"not to scale" functionality
*/

void minimalPath(Node* start_node, Node* end_node, float scale)
{
    start_node->tested = true;
    for (Node* node : start_node->connected_nodes)
    {
        if (!node->tested)
        {
            if (node->minimal_path == -1)
            {
                if (start_node->minimal_path == -1)
                {
                    node->minimal_path = Node::distance(start_node, node, scale);
                    node->prev_node = start_node;
                }
                else
                {
                    node->minimal_path = Node::distance(start_node, node, scale) + start_node->minimal_path;
                    node->prev_node = start_node;
                }
            }
            else
            {
                if (Node::distance(start_node, node, scale) + start_node->minimal_path < node->minimal_path)
                {
                    node->minimal_path = Node::distance(start_node, node, scale) + start_node->minimal_path;
                    node->prev_node = start_node;
                }
            }
        }
    }
    // sort all connected nodes first, then do in order
    Node* minimal_dis_node = start_node;
    int i = 0;
    while (minimal_dis_node != NULL)
    {
        minimal_dis_node = NULL;
        for (Node* node : start_node->connected_nodes)
        {
            if (!node->tested)
            {
                if (node != end_node)
                {
                    if (minimal_dis_node == NULL || minimal_dis_node == end_node || (minimal_dis_node->minimal_path > node->minimal_path && node->minimal_path != -1))
                    {
                        minimal_dis_node = node;
                    }
                }
                else
                {
                    if (minimal_dis_node == NULL)
                    {
                        minimal_dis_node = node;
                    }
                }
            }
        }
        if (minimal_dis_node != NULL)
        {
            if (minimal_dis_node != end_node)
            {
                minimalPath(minimal_dis_node, end_node, scale);
            }
            else
            {
                return;
            }
        }
    }
}

int main()
{
    int resX = 640;
    int resY = 480;
    sf::ContextSettings contex_settings;
    contex_settings.antialiasingLevel = 16.0;
    sf::RenderWindow window(sf::VideoMode(resX, resY), "Nodes", sf::Style::Default, contex_settings);
    sf::View view;
    view.setSize(resX, resY);
    view.setCenter(view.getSize().x / 2, view.getSize().y / 2);

    sf::Color* background_color = new sf::Color(230, 230, 230, 255);
    sf::Color* node_color = new sf::Color(0, 0, 255, 255);
    sf::Color* node_select_color1 = new sf::Color(0, 255, 0, 255);
    sf::Color* node_select_color2 = new sf::Color(255, 0, 255, 255);
    sf::Color* node_connection_color = new sf::Color(255, 255, 0, 255);
    sf::Color* node_connection_select_color = new sf::Color(255, 0, 0, 255);

    sf::Text text;
    sf::Font font;
    font.loadFromFile("assets/BELL.ttf");
    text.setFont(font);
    text.setString("Yum");
    text.setPosition(0, 0);

    GUI gui(node_select_color1, node_select_color2);
    std::vector<Node*> nodes;
    std::vector<NodeConnection*> node_connections;

    GraphSettings graph_settings(&font);
    graph_settings.background_color = background_color;
    graph_settings.node_color = node_color;
    graph_settings.node_select_color1 = node_select_color1;
    graph_settings.node_select_color2 = node_select_color2;
    graph_settings.node_connection_color = node_connection_color;
    graph_settings.node_connection_select_color = node_connection_select_color;
    graph_settings.chosen_color = background_color;

    NodeSettings node_settings(&font);

    float scale = 0.2;
    bool view_states[4] = { false };
    float camera_speed = 100;
    sf::Clock clock;
    float dt = 0;
    bool placing = false;
    bool deleting = false;
    bool moving = false;
    bool selecting = false;
    bool connecting = false;
    bool disconnecting = false;
    Node* selected_node1 = NULL;
    Node* selected_node2 = NULL;
    std::vector<Node*> selected_nodes1;
    std::vector<Node*> selected_nodes2;
    // false = 1, true = 2
    bool selection_toggle = false; 
    sf::Vector2f selection_top_left;
    sf::Vector2f selection_bot_right;
    bool mouse_down = false;
    bool p = true;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized)
            {
                view.setSize(event.size.width, event.size.height);
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Right)
                {
                    view_states[0] = true;
                }
                if (event.key.code == sf::Keyboard::Up)
                {
                    view_states[1] = true;
                }
                if (event.key.code == sf::Keyboard::Left)
                {
                    view_states[2] = true;
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    view_states[3] = true;
                }
                if (event.key.code == sf::Keyboard::Num1)
                {
                    selection_toggle = false;
                }
                if (event.key.code == sf::Keyboard::Num2)
                {
                    selection_toggle = true;
                }
                if (event.key.code == sf::Keyboard::K)
                {
                    // save
                    std::ofstream save("save.txt");
                    save << "C\n";
                    save << std::to_string(node_color->r) + " " + std::to_string(node_color->g) + " " + std::to_string(node_color->b) + "\n";
                    save << std::to_string(background_color->r) + " " + std::to_string(background_color->g) + " " + std::to_string(background_color->b) + "\n";
                    save << std::to_string(node_select_color1->r) + " " + std::to_string(node_select_color1->g) + " " + std::to_string(node_select_color1->b) + "\n";
                    save << std::to_string(node_select_color2->r) + " " + std::to_string(node_select_color2->g) + " " + std::to_string(node_select_color2->b) + "\n";
                    save << std::to_string(node_connection_color->r) + " " + std::to_string(node_connection_color->g) + " " + std::to_string(node_connection_color->b) + "\n";
                    save << std::to_string(node_connection_select_color->r) + " " + std::to_string(node_connection_select_color->g) + " " + std::to_string(node_connection_select_color->b) + "\n";
                    save << "N" + std::to_string(nodes.size()) + "\n";
                    for (int i = 0; i < nodes.size(); i++)
                    {
                        save << std::to_string(nodes[i]->position.x) + " " + std::to_string(nodes[i]->position.y) + "\n";
                    }
                    save << "M" + std::to_string(node_connections.size()) + "\n";
                    for (int i = 0; i < node_connections.size(); i++)
                    {
                        save << std::to_string(node_connections[i]->node1->position.x) + " " + std::to_string(node_connections[i]->node1->position.y)
                            + " " + std::to_string(node_connections[i]->node2->position.x) + " " + std::to_string(node_connections[i]->node2->position.y) + "\n";
                    }
                    save.close();
                }
                if (event.key.code == sf::Keyboard::L)
                {
                    // load
                    std::ifstream load("save.txt");
                    std::string out_text;
                    short state = 0;
                    short color_state = 0;
                    short num_nodes = 0;
                    short num_connections = 0;
                    short connect_state = 0;
                    sf::Vector2f node1_pos;
                    sf::Vector2f node2_pos;
                    short node_x = 0, node_y = 0;
                    bool red_tested = false;
                    while (getline(load, out_text))
                    {
                        std::string value = "";
                        for (int i = 0; i < out_text.length(); i++)
                        {
                            if (out_text[i] == *" ")
                            {
                                if (num_nodes > 0)
                                {
                                    node_x = stoi(value);
                                }
                                if (num_connections > 0)
                                {
                                    switch (connect_state)
                                    {
                                    case 0:
                                        node1_pos.x = stoi(value);
                                        connect_state++;
                                        break;
                                    case 1:
                                        node1_pos.y = stoi(value);
                                        connect_state++;
                                        break;
                                    case 2:
                                        node2_pos.x = stoi(value);
                                        connect_state++;
                                        break;
                                    }
                                }
                                if (state == 2)
                                {
                                    switch (color_state)
                                    {
                                    case 0:
                                        if (red_tested)
                                        {
                                            node_color->g = stoi(value);
                                            red_tested = false;
                                        }
                                        else
                                        {
                                            node_color->r = stoi(value);
                                            red_tested = true;
                                        }
                                        break;
                                    case 1:
                                        if (red_tested)
                                        {
                                            background_color->g = stoi(value);
                                            red_tested = false;
                                        }
                                        else
                                        {
                                            background_color->r = stoi(value);
                                            red_tested = true;
                                        }
                                        break;
                                    case 2:
                                        if (red_tested)
                                        {
                                            node_select_color1->g = stoi(value);
                                            red_tested = false;
                                        }
                                        else
                                        {
                                            node_select_color1->r = stoi(value);
                                            red_tested = true;
                                        }
                                        break;
                                    case 3:
                                        if (red_tested)
                                        {
                                            node_select_color2->g = stoi(value);
                                            red_tested = false;
                                        }
                                        else
                                        {
                                            node_select_color2->r = stoi(value);
                                            red_tested = false;
                                        }
                                        break;
                                    case 4:
                                        if (red_tested)
                                        {
                                            node_connection_color->g = stoi(value);
                                            red_tested = false;
                                        }
                                        else
                                        {
                                            node_connection_color->r = stoi(value);
                                            red_tested = true;
                                        }
                                        break;
                                    case 5:
                                        if (red_tested)
                                        {
                                            node_connection_select_color->g = stoi(value);
                                            red_tested = false;
                                        }
                                        else
                                        {
                                            node_connection_select_color->r = stoi(value);
                                            red_tested = true;
                                        }
                                        break;
                                    }
                                }
                                value = "";
                            }
                            else if (out_text[i] == *"N")
                            {
                                state = 1;
                                value = "";
                            }
                            else if (out_text[i] == *"C")
                            {
                                state = 2;
                                value = "";
                            }
                            else if (out_text[i] == *"M")
                            {
                                state = 3;
                                value = "";
                            }
                            else if (i == out_text.length() - 1)
                            {
                                value += out_text[i];
                                if (num_nodes > 0)
                                {
                                    node_y = stoi(value);
                                    Node* node = new Node(sf::Vector2f(node_x, node_y), 4, node_color, node_select_color1, node_select_color2);
                                    nodes.push_back(node);
                                    num_nodes--;
                                }
                                if (num_connections > 0)
                                {
                                    node2_pos.y = stoi(value);
                                    NodeConnection* node_connection = new NodeConnection(node_connection_color, node_connection_select_color);
                                    node_connections.push_back(node_connection);
                                    bool found = false;
                                    for (int i = 0; i < nodes.size() - 1; i++)
                                    {
                                        Node* node1 = nodes[i];
                                        for (int j = i + 1; j < nodes.size(); j++)
                                        {
                                            Node* node2 = nodes[j];
                                            if ((node1->position == node1_pos && node2->position == node2_pos)
                                                || (node1->position == node2_pos && node2->position == node1_pos))
                                            {
                                                NodeConnection::connectNodes(node1,node2, node_connection);
                                                found = true;
                                                break;
                                            }
                                        }
                                        if (found) break;
                                    }
                                    connect_state = 0;
                                    num_connections--;
                                }
                                if (state == 1)
                                {
                                    num_nodes = stoi(value);
                                    state = 0;
                                }
                                else if (state == 2)
                                {
                                    switch (color_state)
                                    {
                                    case 0:
                                        node_color->b = stoi(value);
                                        break;
                                    case 1:
                                        background_color->b = stoi(value);
                                        break;
                                    case 2:
                                        node_select_color1->b = stoi(value);
                                        break;
                                    case 3:
                                        node_select_color2->b = stoi(value);
                                        break;
                                    case 4:
                                        node_connection_color->b = stoi(value);
                                        break;
                                    case 5:
                                        node_connection_select_color->b = stoi(value);
                                        break;
                                    }
                                    color_state++;
                                }
                                else if (state == 3)
                                {
                                    num_connections = stoi(value);
                                    state = 0;
                                }
                            }
                            else
                            {
                                value += out_text[i];
                            }
                        } 
                    }

                }
                if (event.key.code == sf::Keyboard::A)
                {
                    if (selecting && selected_nodes1.size() == 2)
                    {
                        for (NodeConnection* node_connection : node_connections)
                        {
                            if (node_connection->hasNodes(selected_nodes1[0], selected_nodes1[1]))
                            {
                                node_connection->select();
                                break;
                            }
                        }
                    }
                    else if (selecting && selected_nodes2.size() == 2)
                    {
                        for (NodeConnection* node_connection : node_connections)
                        {
                            if (node_connection->hasNodes(selected_nodes2[0], selected_nodes2[1]))
                            {
                                node_connection->select();
                                break;
                            }
                        }
                    }
                }
                if (event.key.code == sf::Keyboard::S)
                {
                    if (selecting && selected_nodes1.size() == 2)
                    {
                        for (NodeConnection* node_connection : node_connections)
                        {
                            if (node_connection->hasNodes(selected_nodes1[0], selected_nodes1[1]))
                            {
                                node_connection->deselect();
                                break;
                            }
                        }
                    }
                    else if (selecting && selected_nodes2.size() == 2)
                    {
                        for (NodeConnection* node_connection : node_connections)
                        {
                            if (node_connection->hasNodes(selected_nodes2[0], selected_nodes2[1]))
                            {
                                node_connection->deselect();
                                break;
                            }
                        }
                    }
                }
                if (event.key.code == sf::Keyboard::D)
                {
                    if (selecting && selected_nodes1.size() == 2)
                    {
                        for (Node* node : nodes)
                            node->reset();
                        minimalPath(selected_nodes1[0], selected_nodes1[1], scale);
                        node_settings.setMinimalPath(selected_nodes1[1]->minimal_path);
                        Node* cur_node = selected_nodes1[1];
                        while (cur_node != NULL)
                        {
                            if (cur_node != NULL)
                            {
                                for (NodeConnection* node_connection : node_connections)
                                {
                                    if (node_connection->hasNodes(cur_node, cur_node->prev_node))
                                    {
                                        node_connection->select();
                                    }
                                }
                            }
                            cur_node = cur_node->prev_node;
                        }
                    }
                    if (selecting && selected_nodes2.size() == 2)
                    {
                        for (Node* node : nodes)
                            node->reset();
                        minimalPath(selected_nodes2[0], selected_nodes2[1], scale);
                        node_settings.setMinimalPath(selected_nodes2[1]->minimal_path);
                        Node* cur_node = selected_nodes2[1];
                        while (cur_node != NULL)
                        {
                            if (cur_node != NULL)
                            {
                                for (NodeConnection* node_connection : node_connections)
                                {
                                    if (node_connection->hasNodes(cur_node, cur_node->prev_node))
                                    {
                                        node_connection->select();
                                    }
                                }
                            }
                            cur_node = cur_node->prev_node;
                        }
                    }
                }
                if (event.key.code == sf::Keyboard::T)
                {
                    for (Node* node : nodes)
                    {
                        node->visible = !node->visible;
                    }
                }
                if (event.key.code == sf::Keyboard::W)
                {
                    sf::Vector2f position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (gui.visible)
                        gui.visible = false;
                    if (node_settings.visible)
                        node_settings.visible = false;
                    graph_settings.visible = !graph_settings.visible;
                    graph_settings.setPosition(position);
                }
                if (event.key.code == sf::Keyboard::G)
                {
                    if (selecting)
                    {
                        if (selected_nodes2.size() == 0)
                        {
                            for (int i = 0; i < selected_nodes1.size() - 1; i++)
                            {
                                Node* node1 = selected_nodes1[i];
                                for (int j = i + 1; j < selected_nodes1.size(); j++)
                                {
                                    Node* node2 = selected_nodes1[j];
                                    if (!node1->connectedTo(node2))
                                    {
                                        NodeConnection* node_connection = new NodeConnection(node_connection_color, node_connection_select_color);
                                        node_connections.push_back(node_connection);
                                        NodeConnection::connectNodes(node1, node2, node_connection);
                                    }
                                }
                            }
                        }
                        else if (selected_nodes1.size() == 0)
                        {
                            for (int i = 0; i < selected_nodes2.size() - 1; i++)
                            {
                                Node* node1 = selected_nodes2[i];
                                for (int j = i + 1; j < selected_nodes2.size(); j++)
                                {
                                    Node* node2 = selected_nodes2[j];
                                    if (!node1->connectedTo(node2))
                                    {
                                        NodeConnection* node_connection = new NodeConnection(node_connection_color, node_connection_select_color);
                                        node_connections.push_back(node_connection);
                                        NodeConnection::connectNodes(node1, node2, node_connection);
                                    }
                                }
                            }
                        }
                        else
                        {
                            for (Node* node1 : selected_nodes1)
                            {
                                for (Node* node2 : selected_nodes2)
                                {
                                    if (!node1->connectedTo(node2))
                                    {
                                        NodeConnection* node_connection = new NodeConnection(node_connection_color, node_connection_select_color);
                                        node_connections.push_back(node_connection);
                                        NodeConnection::connectNodes(node1, node2, node_connection);
                                    }
                                }
                            }
                        }
                    }
                }
                if (event.key.code == sf::Keyboard::H)
                {
                    if (selecting)
                    {
                        if (selected_nodes2.size() == 0)
                        {
                            for (int i = 0; i < selected_nodes1.size() - 1; i++)
                            {
                                Node* node1 = selected_nodes1[i];
                                for (int j = i + 1; j < selected_nodes1.size(); j++)
                                {
                                    Node* node2 = selected_nodes1[j];
                                    if (node1->connectedTo(node2))
                                    {
                                        for (int k = 0; k < node_connections.size(); k++)
                                        {
                                            NodeConnection* node_connection = node_connections[k];
                                            if (node_connection->hasNodes(node1, node2))
                                            {
                                                node_connections.erase(node_connections.begin() + k);
                                                k--;
                                                delete node_connection;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else if (selected_nodes1.size() == 0)
                        {
                            for (int i = 0; i < selected_nodes2.size() - 1; i++)
                            {
                                Node* node1 = selected_nodes2[i];
                                for (int j = i + 1; j < selected_nodes2.size(); j++)
                                {
                                    Node* node2 = selected_nodes2[j];
                                    if (node1->connectedTo(node2))
                                    {
                                        for (int k = 0; k < node_connections.size(); k++)
                                        {
                                            NodeConnection* node_connection = node_connections[k];
                                            if (node_connection->hasNodes(node1, node2))
                                            {
                                                node_connections.erase(node_connections.begin() + k);
                                                k--;
                                                delete node_connection;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            for (Node* node1 : selected_nodes1)
                            {
                                for (Node* node2 : selected_nodes2)
                                {
                                    if (node1->connectedTo(node2))
                                    {
                                        for (int k = 0; k < node_connections.size(); k++)
                                        {
                                            NodeConnection* node_connection = node_connections[k];
                                            if (node_connection->hasNodes(node1, node2))
                                            {
                                                node_connections.erase(node_connections.begin() + k);
                                                k--;
                                                delete node_connection;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                if (event.key.code == sf::Keyboard::Q)
                {

                    if (selected_node1 != NULL)
                    {
                        selected_node1->deselect();
                        selected_node1 = NULL;
                    }
                    while (selected_nodes1.size() > 0)
                    {
                        selected_nodes1[0]->deselect();
                        selected_nodes1.erase(selected_nodes1.begin());
                    }
                    while (selected_nodes2.size() > 0)
                    {
                        selected_nodes2[0]->deselect();
                        selected_nodes2.erase(selected_nodes2.begin());
                    }
                    for (NodeConnection* node_connection : node_connections)
                        node_connection->deselect();
                }
                
                if (event.key.code == sf::Keyboard::E)
                {
                    sf::Vector2f position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (gui.visible)
                        gui.visible = false;
                    if (graph_settings.visible)
                        graph_settings.visible = false;
                    node_settings.visible = !node_settings.visible;
                    node_settings.setPosition(position, scale);
                    
                }
                if (event.key.code == sf::Keyboard::BackSpace)
                {
                    if (selecting)
                    {
                        while (selected_nodes1.size() > 0)
                        {
                            Node* node = selected_nodes1[0];
                            for (int i = 0; i < nodes.size(); i++)
                            {
                                if (node == nodes[i])
                                {
                                    for (int j = 0; j < node_connections.size(); j++)
                                    {
                                        NodeConnection* node_connection = node_connections[j];
                                        if (node_connection->hasNode(node))
                                        {
                                            node_connections.erase(node_connections.begin() + j);
                                            j--;
                                            delete node_connection;
                                        }
                                    }
                                    nodes.erase(nodes.begin() + i);
                                    i--;
                                    delete node;
                                }
                            }
                            selected_nodes1.erase(selected_nodes1.begin());
                        }
                    }
                    while (selected_nodes2.size() > 0)
                    {
                        Node* node = selected_nodes2[0];
                        for (int i = 0; i < nodes.size(); i++)
                        {
                            if (node == nodes[i])
                            {
                                for (int j = 0; j < node_connections.size(); j++)
                                {
                                    NodeConnection* node_connection = node_connections[j];
                                    if (node_connection->hasNode(node))
                                    {
                                        node_connections.erase(node_connections.begin() + j);
                                        j--;
                                        delete node_connection;
                                    }
                                }
                                nodes.erase(nodes.begin() + i);
                                i--;
                                delete node;
                            }
                        }
                        selected_nodes2.erase(selected_nodes2.begin());
                    }
                }
            }
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Right)
                {
                    view_states[0] = false;
                }
                if (event.key.code == sf::Keyboard::Up)
                {
                    view_states[1] = false;
                }
                if (event.key.code == sf::Keyboard::Left)
                {
                    view_states[2] = false;
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    view_states[3] = false;
                }
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.key.code == sf::Mouse::Left)
                {
                    sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (!gui.mouseInside(mouse_position) && !graph_settings.mouseInside(mouse_position) && !node_settings.mouseInside(mouse_position))
                    {
                        if (gui.tool_state == 0)
                        {
                            Node* node = new Node(mouse_position, 4, node_color, node_select_color1, node_select_color2);
                            nodes.push_back(node);
                        }
                        else if (gui.tool_state == 1)
                        {
                            for (int i = 0; i < nodes.size(); i++)
                            {
                                Node* node = nodes[i];
                                if (node->mouseInside(mouse_position))
                                {
                                    for (int j = 0; j < node_connections.size(); j++)
                                    {
                                        NodeConnection* node_connection = node_connections[j];
                                        if (node_connection->node1 == node || node_connection->node2 == node)
                                        {
                                            node_connections.erase(node_connections.begin() + j);
                                            j--;
                                            delete node_connection;
                                        }
                                    }
                                    nodes.erase(nodes.begin() + i);
                                    delete node;
                                    break;
                                }
                            }
                        }
                        else if (gui.tool_state == 2)
                        {
                            for (Node* node : nodes)
                            {
                                if (node->mouseInside(mouse_position))
                                {
                                    selected_node1 = node;
                                    break;
                                }
                            }
                        }
                        else if (gui.tool_state == 3)
                        {
                            if (!mouse_down)
                            {
                                selection_top_left = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                                gui.setSelectionPosition(selection_top_left);
                                mouse_down = true;
                                gui.selection_visible = true;
                            }
                            for (Node* node : nodes)
                            {
                                if (node->mouseInside(mouse_position))
                                {
                                    
                                    if (node->selected == 1)
                                    {
                                        for (int i = 0; i < selected_nodes1.size(); i++)
                                        {
                                            if (selected_nodes1[i] == node)
                                            {
                                                selected_nodes1.erase(selected_nodes1.begin() + i);
                                                break;
                                            }
                                        }
                                        if (selection_toggle)
                                        {
                                            selected_nodes2.push_back(node);
                                            node->select(selection_toggle);
                                        }
                                        else
                                        {
                                            node->deselect();
                                        }
                                    }
                                    else if (node->selected == 2)
                                    {
                                        for (int i = 0; i < selected_nodes2.size(); i++)
                                        {
                                            if (selected_nodes2[i] == node)
                                            {
                                                selected_nodes2.erase(selected_nodes2.begin() + i);
                                                break;
                                            }
                                        }
                                        if (!selection_toggle)
                                        {
                                            selected_nodes1.push_back(node);
                                            node->select(selection_toggle);
                                        }
                                        else
                                        {
                                            node->deselect();
                                        }
                                    }
                                    else
                                    {
                                        if (selection_toggle)
                                        {
                                            selected_nodes2.push_back(node);
                                        }
                                        else
                                        {
                                            selected_nodes1.push_back(node);
                                        }
                                        node->select(selection_toggle);
                                    }
                                    break;
                                }
                            }
                        }
                        else if (gui.tool_state == 4)
                        {
                            for (Node* node : nodes)
                            {
                                if (node->mouseInside(mouse_position))
                                {
                                    if (selected_node1 == NULL)
                                    {
                                        node->select(false);
                                        selected_node1 = node;
                                    }
                                    else
                                    {
                                        if (!selected_node1->connectedTo(node))
                                            selected_node2 = node;
                                        else
                                        {
                                            selected_node1->deselect();
                                            selected_node1 = NULL;
                                        }
                                    }
                                    break;
                                }
                            }
                            if (selected_node2 != NULL)
                            {
                                selected_node1->deselect();
                                NodeConnection* node_connection = new NodeConnection(node_connection_color, node_connection_select_color);
                                node_connections.push_back(node_connection);
                                NodeConnection::connectNodes(selected_node1, selected_node2, node_connection);
                                selected_node1 = NULL;
                                selected_node2 = NULL;
                            }
                        }
                        else if (gui.tool_state == 5)
                        {
                            for (Node* node : nodes)
                            {
                                if (node->mouseInside(mouse_position))
                                {
                                    if (selected_node1 == NULL)
                                    {
                                        node->select(false);
                                        selected_node1 = node;
                                    }
                                    else
                                    {
                                        if (selected_node1->connectedTo(node))
                                            selected_node2 = node;
                                        else
                                        {
                                            selected_node1->deselect();
                                            selected_node1 = NULL;
                                        }
                                    }
                                    break;
                                }
                            }
                            if (selected_node2 != NULL)
                            {
                                selected_node1->deselect();
                                for (int i = 0; i < node_connections.size(); i++)
                                {
                                    NodeConnection* node_connection = node_connections[i];
                                    if (node_connection->hasNodes(selected_node1, selected_node2))
                                    {
                                        node_connections.erase(node_connections.begin() + i);
                                        delete node_connection;
                                        break;
                                    }
                                }
                                selected_node1 = NULL;
                                selected_node2 = NULL;
                            }
                        }
                    }
                    else
                    {
                        if (gui.mouseInside(mouse_position))
                        {
                            gui.queryTools(mouse_position);

                            if (!placing && gui.tool_state == 0)
                            {
                                if (selected_node1 != NULL)
                                {
                                    selected_node1->deselect();
                                    selected_node1 = NULL;
                                }
                                connecting = false;
                                disconnecting = false;
                                deleting = false;
                                moving = false;
                                selecting = false;
                                placing = true;
                            }

                            if (!deleting && gui.tool_state == 1)
                            {
                                if (selected_node1 != NULL)
                                {
                                    selected_node1->deselect();
                                    selected_node1 = NULL;
                                }
                                connecting = false;
                                disconnecting = false;
                                deleting = true;
                                moving = false;
                                placing = false;
                                selecting = false;
                            }

                            if (!moving && gui.tool_state == 2)
                            {
                                if (selected_node1 != NULL)
                                {
                                    selected_node1->deselect();
                                    selected_node1 = NULL;
                                }
                                connecting = false;
                                disconnecting = false;
                                deleting = false;
                                placing = false;
                                moving = true;
                                selecting = false;
                            }

                            if (!selecting && gui.tool_state == 3)
                            {
                                if (selected_node1 != NULL)
                                {
                                    selected_node1->deselect();
                                    selected_node1 = NULL;
                                }
                                connecting = false;
                                disconnecting = false;
                                deleting = false;
                                placing = false;
                                moving = false;
                                selecting = true;
                            }

                            if (!connecting && gui.tool_state == 4)
                            {
                                if (selected_node1 != NULL)
                                {
                                    selected_node1->deselect();
                                    selected_node1 = NULL;
                                }
                                disconnecting = false;
                                placing = false;
                                deleting = false;
                                connecting = true;
                                moving = false;
                                selecting = false;
                            }

                            if (!disconnecting && gui.tool_state == 5)
                            {
                                if (selected_node1 != NULL)
                                {
                                    selected_node1->deselect();
                                    selected_node1 = NULL;
                                }
                                connecting = false;
                                deleting = false;
                                placing = false;
                                disconnecting = true;
                                moving = false;
                                selecting = false;
                            }

                            if (!selecting && gui.tool_state != 3)
                            {
                                while (selected_nodes1.size() > 0)
                                {
                                    selected_nodes1[0]->deselect();
                                    selected_nodes1.erase(selected_nodes1.begin());
                                }
                                while (selected_nodes2.size() > 0)
                                {
                                    selected_nodes2[0]->deselect();
                                    selected_nodes2.erase(selected_nodes2.begin());
                                }
                                for (NodeConnection* node_connection : node_connections)
                                {
                                    node_connection->deselect();
                                }
                                gui.resetSelection();
                            }
                        }
                        else if (graph_settings.mouseInside(mouse_position))
                        {
                            graph_settings.queryTools(mouse_position);
                        }
                        else if (node_settings.mouseInside(mouse_position))
                        {
                            node_settings.queryTools(mouse_position, scale);
                        }
                    }
                }
                if (event.key.code == sf::Mouse::Right)
                {
                    sf::Vector2f position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (graph_settings.visible)
                        graph_settings.visible = false;
                    if (node_settings.visible)
                        node_settings.visible = false;
                    gui.visible = !gui.visible;
                    gui.setPosition(position);
                }
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.key.code == sf::Mouse::Left)
                {
                    if (graph_settings.visible)
                    {
                        graph_settings.resetSliders();
                    }
                    if (node_settings.visible)
                    {
                        node_settings.resetSlider();
                    }
                    if (gui.tool_state == 2)
                    {
                        selected_node1 = NULL;
                    }
                    if (gui.tool_state == 3)
                    {
                        mouse_down = false;
                        gui.selection_visible = false;
                        for (Node* node : nodes)
                        {
                            if (node->position.x >= gui.getSelectionPosition().x && node->position.x <= gui.getSelectionPosition().x + gui.getSelectionSize().x
                                && node->position.y >= gui.getSelectionPosition().y && node->position.y <= gui.getSelectionPosition().y + gui.getSelectionSize().y)
                            {
                                if (node->selected == 1)
                                {
                                    if (selection_toggle)
                                    {
                                        for (int i = 0; i < selected_nodes1.size(); i++)
                                        {
                                            if (selected_nodes1[i] == node)
                                            {
                                                selected_nodes1.erase(selected_nodes1.begin() + i);
                                                break;
                                            }
                                        }
                                        selected_nodes2.push_back(node);
                                        node->select(selection_toggle);
                                    }
                                }
                                else if (node->selected == 2)
                                {
                                    if (!selection_toggle)
                                    {
                                        for (int i = 0; i < selected_nodes2.size(); i++)
                                        {
                                            if (selected_nodes2[i] == node)
                                            {
                                                selected_nodes2.erase(selected_nodes2.begin() + i);
                                                break;
                                            }
                                        }
                                        selected_nodes1.push_back(node);
                                        node->select(selection_toggle);
                                    }
                                }
                                else
                                {
                                    if (selection_toggle)
                                    {
                                        selected_nodes2.push_back(node);
                                    }
                                    else
                                    {
                                        selected_nodes1.push_back(node);
                                    }
                                    node->select(selection_toggle);
                                }
                            }
                        }
                    }
                }
            }
        }

        if (view_states[0])
            view.setCenter(sf::Vector2f(view.getCenter().x + camera_speed * dt, view.getCenter().y));
        if (view_states[1])
            view.setCenter(sf::Vector2f(view.getCenter().x, view.getCenter().y - camera_speed * dt));
        if (view_states[2])
            view.setCenter(sf::Vector2f(view.getCenter().x - camera_speed * dt, view.getCenter().y));
        if (view_states[3])
            view.setCenter(sf::Vector2f(view.getCenter().x, view.getCenter().y + camera_speed * dt));

        sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        graph_settings.testSliders(mouse_position);
        node_settings.testSlider(mouse_position, scale);

        if (selected_nodes1.size() == 2)
        {
            node_settings.setNodes(selected_nodes1[0], selected_nodes1[1], scale);
        }
        else if (selected_nodes2.size() == 2)
        {
            node_settings.setNodes(selected_nodes2[0], selected_nodes2[1], scale);
        }
        else
        {
            node_settings.reset();
        }

        if (graph_settings.getPage() >= 4)
        {
            for (NodeConnection* node_connection : node_connections)
            {
                node_connection->changeColor();
            }
        }

        if (selecting && mouse_down)
        {
            selection_bot_right = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            gui.setSelectionSize(selection_bot_right);
            gui.setSelectionState(selection_toggle);
        }

        if (moving)
        {
            
            if (selected_node1 != NULL)
            {
                selected_node1->setPosition(mouse_position);
                for (NodeConnection* node_connection : node_connections)
                {
                    if (node_connection->node1 == selected_node1)
                        node_connection->node_connection[0].position = mouse_position;
                    else if (node_connection->node2 == selected_node1)
                        node_connection->node_connection[1].position = mouse_position;
                }
            }
        }

        std::vector<NodeConnection*> selected_node_connections;

        window.clear(*background_color);
        window.setView(view);
        for (NodeConnection* node_connection : node_connections)
        {
            if (!node_connection->selected)
                window.draw(*node_connection);
            else
                selected_node_connections.push_back(node_connection);
        }
        for (NodeConnection* node_connection : selected_node_connections)
            window.draw(*node_connection);
        for (Node* node : nodes)
        {
            node->updateColor();
            if (node->visible)
            {
                if (node->selected == 0)
                    window.draw(*node);
            }
        }
        if (selected_node1 != NULL)
            window.draw(*selected_node1);
        for (Node* node : selected_nodes1)
        {
            if (node->visible)
                window.draw(*node);
        }
        for (Node* node : selected_nodes2)
        {
            if (node->visible)
                window.draw(*node);
        }
        window.draw(gui);
        window.draw(graph_settings);
        window.draw(node_settings);
        window.display();

        dt = clock.restart().asSeconds();
    }

    return 0;
}