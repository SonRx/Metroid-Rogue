#include "stdafx.h"
#include "TileMap.h"

// Private 
void TileMap::clear()
{
	for (size_t x = 0; x < this->maxSizeGrid.x; x++)
	{
		for (size_t y = 0; y < this->maxSizeGrid.y; y++)
		{
			for (size_t z = 0; z < this->layers; z++)
			{
				delete this->map[x][y][z];
				this->map[x][y][z] = NULL;
			}
			this->map[x][y].clear();
		}
		this->map[x].clear();
	}
	this->map.clear();

	//std::cout << "\n" << this->map.size() << "\n";
}

// Public 

// Constructor
TileMap::TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);

	this->maxSizeGrid.x = width;
	this->maxSizeGrid.y = height;

	this->maxSizeWorld.x = static_cast<float>(width) * gridSize;
	this->maxSizeWorld.y = static_cast<float>(height) * gridSize;

	this->layers = 1;
	this->textureFile = texture_file;

	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;

	this->map.resize(this->maxSizeGrid.x, std::vector< vector<Tile*> >());
	for (size_t x = 0; x < this->maxSizeGrid.x; x++)
	{
		for (size_t y = 0; y < this->maxSizeGrid.y; y++)
		{
			this->map[x].resize(this->maxSizeGrid.y, vector<Tile*>());

			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, NULL); 
			}
		}
	}

	if (!this->tileSheet.loadFromFile(texture_file))// find texture
		cout << "ERROR::TILEMAP::FAILED TO LOAD TILESHEET::FILENAME:" << texture_file << endl;

	this->collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	this->collisionBox.setOutlineColor(sf::Color::Red);
	this->collisionBox.setOutlineThickness(1.f);
}

TileMap::~TileMap()
{
	this->clear();
}

// Accessors
const sf::Texture* TileMap::getTileSheet() const
{
	return &this->tileSheet;
}

// Mutators
void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& tex_rect, const bool collision, const short type)
{	// three inputs from the mouse position in the grid. Adds a tile to a position of the array
	if (x < this->maxSizeGrid.x && x >= 0 &&
		y < this->maxSizeGrid.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] == NULL)
		{	// checks if its okay to add tile
			this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileSheet, tex_rect, collision, type);
			cout << "DEBUG: ADDED TILE!" << endl;
		}
	}
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{	// three inputs from the mouse position in the grid. removes a tile to a position of the array
	if (x < this->maxSizeGrid.x && x >= 0 &&
		y < this->maxSizeGrid.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] != NULL)
		{	// checks if its okay to remove tile
			delete this->map[x][y][z]; // deletes
			this->map[x][y][z] = NULL; // set to null
			cout << "DEBUG: REMOVED TILE!" << endl;
		}
	}
}

// Save and Load Tile maps
void TileMap::saveFile(const std::string file_name)
{
	/* Saves tilemap to text file
	normal:		Size x y
				grid Size
				layers
				texture file
	all tiles:
				gridPos x y layer
				Texture rect x y 
				collision
				type
	*/

	std::ofstream out_file; // output

	out_file.open(file_name);

	if (out_file.is_open())
	{
		out_file << this->maxSizeGrid.x << " " << this->maxSizeGrid.y << endl;
		out_file << this->gridSizeU << endl;
		out_file << this->layers << endl;
		out_file << this->textureFile << endl;

		for (size_t x = 0; x < this->maxSizeGrid.x; x++)
		{

			for (size_t y = 0; y < this->maxSizeGrid.y; y++)
			{

				for (size_t z = 0; z < this->layers; z++)
				{
					//out_file << 1 << 1 << 2 << 3 << 5 << " ";
					if (this->map[x][y][z]) // null pointer check
						out_file << x << " " << y << " " << z << " " << this->map[x][y][z]->getAsString() << " ";
				}
			}
		}
	}

	else
	{
		std::cout << "ERROR::TILEMAP::COULD NOT SAVE TO FILE::ARGV: " << file_name << endl;
	}

	out_file.close();
}

void TileMap::loadFile(const std::string file_name)
{
	std::ifstream in_file; // input

	in_file.open(file_name);

	if (in_file.is_open())
	{
		sf::Vector2u size;
		unsigned gridSize = 0;
		unsigned layers = 0;
		std::string texture_file = ""; // nothing
		unsigned x = 0;
		unsigned y = 0;
		unsigned z = 0;
		unsigned trX = 0; // tecture rect x
		unsigned trY = 0; // texture rect y
		bool collision = false;
		short type = 0;


		in_file >> size.x >> size.y >> gridSize >> layers >> texture_file; // parse normal values

		// Tiles
		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeU = gridSize;
		this->maxSizeGrid.x = size.x;
		this->maxSizeGrid.y = size.y;
		this->layers = layers;
		this->textureFile = texture_file;

		this->clear();

		this->map.resize(this->maxSizeGrid.x, std::vector< vector<Tile*> >());
		for (size_t x = 0; x < this->maxSizeGrid.x; x++)
		{
			for (size_t y = 0; y < this->maxSizeGrid.y; y++)
			{
				this->map[x].resize(this->maxSizeGrid.y, vector<Tile*>());

				for (size_t z = 0; z < this->layers; z++)
				{
					this->map[x][y].resize(this->layers, NULL);
				}
			}
		}

		if (!this->tileSheet.loadFromFile(texture_file))// find texture
			cout << "ERROR::TILEMAP::FAILED TO LOAD TILESHEET::FILENAME:" << texture_file << endl;

		// load all tiles
		while (in_file >> x >> y >> z >> trX >> trY >> collision >> type)
		{
			this->map[x][y][z] = new Tile(x, y, gridSizeF,this->tileSheet, sf::IntRect(trX, trY, this->gridSizeU, this->gridSizeU), collision, type);
		}
	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULD NOT LOAS FROM FILE::ARGV: " << file_name << endl;
	}

	in_file.close();
}

void TileMap::updateCollision(Entity* entity, const float& dt) // VERY IMPORTANT 
{
	/* World Bounds for x */
	if (entity->getPosition().x < 0.f)
	{
		entity->setPosition(0.f, entity->getPosition().y);
		entity->resetVelocityX();
	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width > this->maxSizeWorld.x)
	{
		entity->setPosition(this->maxSizeWorld.x - entity->getGlobalBounds().width, entity->getPosition().y); //static_cast<float>(this->maxSizeGrid.x) * this->gridSizeWorld
		entity->resetVelocityX();
	}
	/* World Bounds for y */
	if (entity->getPosition().y < 0.f)
	{
		entity->setPosition(entity->getPosition().x, 0.f);
		entity->resetVelocityY();
	}																// first floor offset with - gridsizeF
	else if (entity->getPosition().y + entity->getGlobalBounds().height > this->maxSizeWorld.y - gridSizeF)
	{
		entity->setPosition(entity->getPosition().x, this->maxSizeWorld.y - gridSizeF - entity->getGlobalBounds().height);
		entity->resetVelocityY();
	}

	/* Tiles */
	this->layer = 0;

	this->fromX = entity->getGridPosition(this->gridSizeU).x - 20; // - 2 to the left
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeGrid.x)
		this->fromX = this->maxSizeGrid.x;

	this->toX = entity->getGridPosition(this->gridSizeU).x + 20;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeGrid.x)
		this->toX = this->maxSizeGrid.x;

	this->fromY = entity->getGridPosition(this->gridSizeU).y - 10; // - 2 to the left
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeGrid.y)
		this->fromY = this->maxSizeGrid.y;

	this->toY = entity->getGridPosition(this->gridSizeU).y + 10;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeGrid.y)
		this->toY = this->maxSizeGrid.y;



	for (size_t x = fromX; x < this->toX; x++)
	{
		for (size_t y = fromY; y < this->toY; y++)
		{
			FloatRect playerBounds = entity->getGlobalBounds();
			FloatRect wallBounds = this->map[x][y][this->layer]->getGlobalBounds();
			FloatRect nextPos = entity->getNextPosBounds(dt);

			if (this->map[x][y][this->layer]->getCollision() && this->map[x][y][this->layer]->intersects(nextPos)) // check intersects w/ player
			{
				//std::cout << "collsion" << endl; // when player touches red tiles then print collision

				// Collision of bottom of COLLSION BLOCK
				if (playerBounds.top < wallBounds.top
					&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
					&& playerBounds.left < wallBounds.left + wallBounds.width
					&& playerBounds.left + playerBounds.width > wallBounds.left
					)
				{
					entity->resetVelocityY();
					entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
				}
				// collision of top of COLLSION BLOCK
				else if (playerBounds.top > wallBounds.top
					&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
					&& playerBounds.left < wallBounds.left + wallBounds.width
					&& playerBounds.left + playerBounds.width > wallBounds.left
					)
				{
					entity->resetVelocityY();
					entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
				}

				//// collision of right of COLLSION BLOCK
				//if (playerBounds.left < wallBounds.left
				//	&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
				//	&& playerBounds.top < wallBounds.top + wallBounds.height
				//	&& playerBounds.top + playerBounds.height > wallBounds.top
				//	)
				//{
				//	entity->resetVelocityX();
				//	entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
				//}

				//// collision of left of COLLSION BLOCK
				//else if (playerBounds.left > wallBounds.left
				//	&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
				//	&& playerBounds.top < wallBounds.top + wallBounds.height
				//	&& playerBounds.top + playerBounds.height > wallBounds.top
				//	)
				//{
				//	entity->resetVelocityX();
				//	entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
				//}
			}
		}
	}
} 

// Update / Render
void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget& target, Entity* entity)
{

	if (entity)
	{
		this->layer = 0;

		this->fromX = entity->getGridPosition(this->gridSizeU).x - 20; // - 2 to the left
		if (this->fromX < 0)
			this->fromX = 0;
		else if (this->fromX > this->maxSizeGrid.x)
			this->fromX = this->maxSizeGrid.x;

		this->toX = entity->getGridPosition(this->gridSizeU).x + 20;
		if (this->toX < 0)
			this->toX = 0;
		else if (this->toX > this->maxSizeGrid.x)
			this->toX = this->maxSizeGrid.x;

		this->fromY = entity->getGridPosition(this->gridSizeU).y - 10; // - 2 to the left
		if (this->fromY < 0)
			this->fromY = 0;
		else if (this->fromY > this->maxSizeGrid.y)
			this->fromY = this->maxSizeGrid.y;

		this->toY = entity->getGridPosition(this->gridSizeU).y + 10;
		if (this->toY < 0)
			this->toY = 0;
		else if (this->toY > this->maxSizeGrid.y)
			this->toY = this->maxSizeGrid.y;

		for (size_t x = fromX; x < this->toX; x++)
		{
			for (size_t y = fromY; y < this->toY; y++)
			{
				this->map[x][y][this->layer]->render(target);

				if (this->map[x][y][this->layer]->getCollision())
				{
					this->collisionBox.setPosition(this->map[x][y][this->layer]->getPosition());
					target.draw(this->collisionBox);
				}
			}
		}
	}

	else
	{
		for (auto& x : this->map)
		{
			for (auto& y : x)
			{
				for (auto* z : y)
				{
					if (z != NULL)
					{
						z->render(target);

						if (z->getCollision())
						{
							this->collisionBox.setPosition(z->getPosition());
							target.draw(this->collisionBox);
						}
					}
				}
			}
		}
	}
	
}


