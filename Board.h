#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <vector>
#include <string>
#include <map>
#include "TextureManager.h"

using namespace std;

class Board
{
	//numbers n stuff
	int _height;
	int _width;
	int _mines; //total number of mines
	int minecount; //total mines minus amount of flags
	int tileTotal; //total amount of tiles
	map<string, Tile> tiles;
	//board states
	bool win;
	bool lost;
	bool debug;
	int testState;
	//sprite rectangles (for clicking on)
	sf::FloatRect _allTiles;
	sf::FloatRect _smile;
	sf::FloatRect _test1;
	sf::FloatRect _test2;
	sf::FloatRect _test3;
	sf::FloatRect _debugbutton;
	vector<sf::FloatRect> _oneTile;

public:
	
	//constructors
	Board(int width, int height, int mines);
	Board(int width, int height, vector<bool> mines);

	//forget what you call these ones
	void LoadBoard(sf::RenderWindow& window);
	void Clear();

	void RightClick(sf::Vector2f mousePos);
	void LeftClick(sf::Vector2f mousePos);

	//accessors
	sf::FloatRect getsmile();
	Tile getTile(int x, int y);
	void LeftClickTile(sf::Vector2f mousePos);
	void showTile(Tile& t);
	int getTestState();

	//mutator
	void setTestState(int num);
};

