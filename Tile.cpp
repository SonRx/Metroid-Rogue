#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
	this->collision = false;
	this->type = 0;
}

Tile::Tile(short type, int grid_x, int grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& tex_rect, const bool collision = false)
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

//const std::string Tile::getAsString() const
//{
//	std::stringstream ss;
//
//	ss << this->type << " " << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " << this->collision;
//
//	return ss.str();
//}

const sf::Vector2f& Tile::getPosition() const
{
	return this->shape.getPosition();
}

const bool Tile::intersects(const sf::FloatRect bounds) const
{
	return this->shape.getGlobalBounds().intersects(bounds);
}

const bool& Tile::getCollision() const
{
	return this->collision;
}

const short& Tile::getType() const
{
	return this->type;
}

// update
//void Tile::update()
//{
//	//this->shape.setFillColor(sf::Color::Red);
//}
//
//// Render
//void Tile::render(sf::RenderTarget& target, const sf::Vector2f player_position)
//{
//	//target.draw(this->shape);
//}