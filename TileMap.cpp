#include "stdafx.h"
#include "TileMap.h"

// Private 
void TileMap::clear()
{
	for (int x = 0; x < this->maxSizeGrid.x; x++)
	{
		for (int y = 0; y < this->maxSizeGrid.y; y++)
		{
			for (int z = 0; z < this->layers; z++)
			{
				for (size_t k = 0; k < this->map[x][y][z].size(); k++)
				{
					delete this->map[x][y][z][k];
					this->map[x][y][z][k] = NULL;
				}
				this->map[x][y][z].clear();
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
TileMap::TileMap(float gridSize, int width, int height, std::string texture_file)
{
	this->gridSizeF = gridSize;
	this->gridSizeI = static_cast<int>(this->gridSizeF);

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

	this->map.resize(this->maxSizeGrid.x, std::vector< vector< vector<Tile*> > >());
	for (int x = 0; x < this->maxSizeGrid.x; x++)
	{
		for (int y = 0; y < this->maxSizeGrid.y; y++)
		{
			this->map[x].resize(this->maxSizeGrid.y, vector< vector <Tile*> >());

			for (int z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, vector<Tile*>()); 
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

const int TileMap::getLayerSize(const int x, const int y, const int layer) const
{
	if (x >= 0 && x < this->map.size())
	{
		if (y >= 0 && y < this->map[x].size())
		{
			if (layer >= 0 && layer < this->map[x][y].size())
			{	
				return this->map[x][y][layer].size(); // know if tile is inbetween
			}
		}
	}
	return -1; 
}

// Mutators
void TileMap::addTile(const int x, const int y, const int z, const sf::IntRect& tex_rect, const bool collision, const short type)
{	// three inputs from the mouse position in the grid. Adds a tile to a position of the array
	if (x < this->maxSizeGrid.x && x >= 0 &&
		y < this->maxSizeGrid.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
			// checks if its okay to add tile
			this->map[x][y][z].push_back(new Tile(x, y, this->gridSizeF, this->tileSheet, tex_rect, collision, type));
			cout << "DEBUG: ADDED TILE!" << endl;
	}
}

void TileMap::removeTile(const int x, const int y, const int z)
{	// three inputs from the mouse position in the grid. removes a tile to a position of the array
	if (x < this->maxSizeGrid.x && x >= 0 &&
		y < this->maxSizeGrid.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		if (!this->map[x][y][z].empty())
		{	// checks if its okay to remove tile
			delete this->map[x][y][z][this->map[x][y][z].size() -1];
			this->map[x][y][z].pop_back(); // place previous condition
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
		out_file << this->gridSizeI << endl;
		out_file << this->layers << endl;
		out_file << this->textureFile << endl;

		for (int x = 0; x < this->maxSizeGrid.x; x++)
		{

			for (int y = 0; y < this->maxSizeGrid.y; y++)
			{

				for (int z = 0; z < this->layers; z++)
				{
					//out_file << 1 << 1 << 2 << 3 << 5 << " ";
					if (!this->map[x][y][z].empty()) // null pointer check
					{
						for (size_t k = 0; k < this->map[x][y][z].size(); k++)
						{
							out_file << x << " " << y << " " << z << " " << this->map[x][y][z][k]->getAsString() << " ";
						}
					}
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
		int gridSize = 0;
		int layers = 0;
		std::string texture_file = ""; // nothing
		int x = 0;
		int y = 0;
		int z = 0;
		int trX = 0; // tecture rect x
		int trY = 0; // texture rect y
		bool collision = false;
		short type = 0;


		in_file >> size.x >> size.y >> gridSize >> layers >> texture_file; // parse normal values

		// Tiles
		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeI = gridSize;
		this->maxSizeGrid.x = size.x;
		this->maxSizeGrid.y = size.y;
		this->layers = layers;
		this->textureFile = texture_file;

		this->clear();

		this->map.resize(this->maxSizeGrid.x, std::vector< vector< vector <Tile*> > >());
		for (int x = 0; x < this->maxSizeGrid.x; x++)
		{
			for (int y = 0; y < this->maxSizeGrid.y; y++)
			{
				this->map[x].resize(this->maxSizeGrid.y, vector< vector<Tile*> >());

				for (int z = 0; z < this->layers; z++)
				{
					this->map[x][y].resize(this->layers, vector<Tile*>());
				}
			}
		}

		if (!this->tileSheet.loadFromFile(texture_file))// find texture
			cout << "ERROR::TILEMAP::FAILED TO LOAD TILESHEET::FILENAME:" << texture_file << endl;

		// load all tiles from text file
		while (in_file >> x >> y >> z >> trX >> trY >> collision >> type)
		{
			this->map[x][y][z].push_back(new Tile(x, y, gridSizeF,this->tileSheet, sf::IntRect(trX, trY, this->gridSizeI, this->gridSizeI), collision, type));
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

	this->fromX = entity->getGridPosition(this->gridSizeI).x - 20; // - 2 to the left
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeGrid.x)
		this->fromX = this->maxSizeGrid.x;

	this->toX = entity->getGridPosition(this->gridSizeI).x + 20;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeGrid.x)
		this->toX = this->maxSizeGrid.x;

	this->fromY = entity->getGridPosition(this->gridSizeI).y - 10; // - 2 to the left
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeGrid.y)
		this->fromY = this->maxSizeGrid.y;

	this->toY = entity->getGridPosition(this->gridSizeI).y + 10;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeGrid.y)
		this->toY = this->maxSizeGrid.y;



	for (int x = fromX; x < this->toX; x++)
	{
		for (int y = fromY; y < this->toY; y++)
		{
			for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++)
			{

				FloatRect playerBounds = entity->getGlobalBounds();
				FloatRect wallBounds = this->map[x][y][this->layer][k]->getGlobalBounds();
				FloatRect nextPos = entity->getNextPosBounds(dt);

				if (this->map[x][y][this->layer][k]->getCollision() && this->map[x][y][this->layer][k]->intersects(nextPos)) // check intersects w/ player
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

					//	// collision of right of COLLSION BLOCK
					//	if (playerBounds.left < wallBounds.left
					//		&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
					//		&& playerBounds.top < wallBounds.top + wallBounds.height
					//		&& playerBounds.top + playerBounds.height > wallBounds.top
					//		)
					//	{
					//		entity->resetVelocityX();
					//		entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
					//	}

					//	// collision of left of COLLSION BLOCK
					//	else if (playerBounds.left > wallBounds.left
					//		&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
					//		&& playerBounds.top < wallBounds.top + wallBounds.height
					//		&& playerBounds.top + playerBounds.height > wallBounds.top
					//		)
					//	{
					//		entity->resetVelocityX();
					//		entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
					//	}
				}
			}
		}
	}
} 

// Update / Render
void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget& target, const Vector2i& gridPos)
{

	this->layer = 0;

	this->fromX = gridPos.x - 20; // - 2 to the left
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeGrid.x)
		this->fromX = this->maxSizeGrid.x;

	this->toX = gridPos.x + 20;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeGrid.x)
		this->toX = this->maxSizeGrid.x;

	this->fromY = gridPos.y - 10; // - 2 to the left
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeGrid.y)
		this->fromY = this->maxSizeGrid.y;

	this->toY = gridPos.y + 10;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeGrid.y)
		this->toY = this->maxSizeGrid.y;

	for (int x = fromX; x < this->toX; x++)
	{
		for (int y = fromY; y < this->toY; y++)
		{
			for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++)
			{
				if (this->map[x][y][this->layer][k]->getType() == TileTypes::OVERTILE)
				{
					this->queueRenderStack.push(this->map[x][y][this->layer][k]);
				}

				else
				{
					this->map[x][y][this->layer][k]->render(target);
				}
		
				if (this->map[x][y][this->layer][k]->getCollision())
				{
					this->collisionBox.setPosition(this->map[x][y][this->layer][k]->getPosition());
					target.draw(this->collisionBox);
				}
			}
		}
	}

	//else
	//{
	//	for (auto& x : this->map)
	//	{
	//		for (auto& y : x)
	//		{
	//			for (auto& z : y)
	//			{
	//				for (auto* k : z)
	//				{ 
	//					k->render(target);

	//					if (k->getCollision())
	//					{
	//						this->collisionBox.setPosition(k->getPosition());
	//						target.draw(this->collisionBox);
	//					}
	//				}
	//			}
	//		}
	//	}
	//}
}

void TileMap::queueRender(RenderTarget& target)
{
	while (!this->queueRenderStack.empty())
	{
		queueRenderStack.top()->render(target);

		queueRenderStack.pop();
	}
}


