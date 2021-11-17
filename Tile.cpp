#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
	this->collision = false;
	this->type = 0;
}

Tile::Tile(unsigned grid_x, unsigned grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& tex_rect, bool collision, short type)
{
	this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->shape.setFillColor(sf::Color::White);
	//this->shape.setOutlineThickness(1.f);
	//this->shape.setOutlineColor(sf::Color::Green);
	this->shape.setPosition(static_cast<float>(grid_x)* gridSizeF, static_cast<float>(grid_y) * gridSizeF); // static_cast
	this->shape.setTexture(&texture);
	this->shape.setTextureRect(tex_rect);

	this->collision = collision;
	this->type = type;
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

// Accessors
const sf::FloatRect Tile::getGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}

const std::string Tile::getAsString() const
{
	std::stringstream ss;

	ss << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " << this->collision << " " << this->type;

	return ss.str();
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