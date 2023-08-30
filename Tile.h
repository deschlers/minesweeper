#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using namespace std;

class Tile
{
	int _x;
	int _y;
	bool hidden;
	bool flagged;
	bool mined;
	int adjacent;
	int vectorNum;
	bool real;
	
public:
	//contructors
	Tile();
	Tile(int x, int y);
	
	//accessors
	int getX();
	int getY();
	int getAdjacent();

	bool Hidden();
	bool Flagged();
	bool Mined();
	int getVect();
	bool getReal();

	//mutators
	void Flag();
	void Unhide();
	void Mine();
	void Addjacent(); //adds 1 to the number of adjacent mines :P
	void setVect(int num);
	
};

