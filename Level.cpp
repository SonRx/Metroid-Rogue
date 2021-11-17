#include "stdafx.h"
#include "Level.h"

// Struct Object

// Accessors
int Object::GetPropertyInt(std::string name)
{
	return atoi(properties[name].c_str());
}

float Object::GetPropertyFloat(std::string name)
{
	return strtod(properties[name].c_str(), NULL);
}

std::string Object::GetPropertyString(std::string name)
{
	return properties[name];
}

// Class Level

bool Level::LoadFromFile(std::string filename)
{
	return false;
}

Object Level::GetObject(std::string name)
{
	// Only the first object with given name
	for (int i = 0; i < objects.size(); i++)
		if (objects[i].name == name)
			return objects[i];
}

std::vector<Object> Level::GetObjects(std::string name)
{
	// All objects with given name
	std::vector<Object> vec;
	for (int i = 0; i < objects.size(); i++)
		if (objects[i].name == name)
			vec.push_back(objects[i]);

	return vec;
}

void Level::Draw(sf::RenderWindow& window)
{
	// Draw all the tiles (DON'T draw the objects!)
	for (int layer = 0; layer < layers.size(); layer++)
		for (int tile = 0; tile < layers[layer].tiles.size(); tile++)
			window.draw(layers[layer].tiles[tile]);
}

sf::Vector2i Level::GetTileSize()
{
	return sf::Vector2i(tileWidth, tileHeight);
}
