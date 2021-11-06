#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(float x, float y, float gridSizeF)
{
	this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->shape.setFillColor(sf::Color::Cyan);
	this->shape.setPosition(x, y);
}

Tile::~Tile()
{

}

//Tile::Tile(sf::Texture& texture_sheet, sf::IntRect texture_rect, bool damaging)
//	: damaging(damaging)
//{
//	this->sprite.setTexture(texture_sheet);
//	this->sprite.setTextureRect(texture_rect);
//}

// Accessor
const sf::FloatRect Tile::getGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}

// update
void Tile::update()
{

}

// Render
void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}