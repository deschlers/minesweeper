#include "Tile.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using namespace std;

Tile::Tile() {
	_x = 1000;
	_y = 1000;
	hidden = false;
	flagged = false;
	mined = false;
	adjacent = 0;
	vectorNum = 0;
	real = false;
}

Tile::Tile(int x, int y) {
	_x = x;
	_y = y;
	hidden = true;
	flagged = false;
	mined = false;
	adjacent = 0;
	vectorNum = 0;
	real = true;
}

int Tile::getX() {
	return _x;
}

int Tile::getY() {
	return _y;
}

bool Tile::Hidden() {
	return hidden;
}

bool Tile::Flagged() {
	return flagged;
}

bool Tile::Mined() {
	return mined;
}

void Tile::Flag() {
	if (flagged == true) {
		flagged = false;
	}
	else {
		flagged = true;
	}
}

void Tile::Unhide() {
	hidden = false;
}

void Tile::Mine() {
	mined = true;
}

void Tile::Addjacent() {
	adjacent++;
}

int Tile::getAdjacent() {
	return adjacent;
}

void Tile::setVect(int num) {
	vectorNum = num;
}

int Tile::getVect() {
	return vectorNum;
}

bool Tile::getReal() {
	return real;
}