#include "Board.h"
#include "TextureManager.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>

using namespace std;

Board::Board(int width, int height, int mines) {
	_width = width;
	_height = height;
	_mines = mines;
	minecount = _mines;
	win = false;
	lost = false;
	debug = false;
	testState = 0;
	tileTotal = _height * _width;
	_allTiles = sf::FloatRect(0, 0, width * 32, height * 32);

	//set up the coordinates for the tiles
	for (int i = 0; i < _width; i++) {
		for (int j = 0; j < _height; j++) {
			string coords = to_string(i) + "," + to_string(j);
			tiles.emplace(coords, Tile(i*32, j*32));
		}
	}
	
	//randomize mines
	for (int i = 0; i < _mines; i++) {
		int x = rand() % (_width);
		int y = rand() % (_height);
		string coords = to_string(x) + "," + to_string(y);

		map<string, Tile>::iterator iter = tiles.find(coords);
		if (iter != tiles.end()) {
			if (iter->second.Mined()) {
				i--;
			}
			else {
				iter->second.Mine();
			}
		}
		else {
			cout << "oh no" << endl;
		}
	}

	//set up numbers
	for (int i = 0; i < _width; i++) {
		for (int j = 0; j < _height; j++) {
			string coords = to_string(i) + "," + to_string(j);
			string t = coords;
			
			
			//start checking
			coords = to_string(i) + "," + to_string(j - 1);
			if (tiles[coords].Mined()) {
				tiles[t].Addjacent();
			}
			coords = to_string(i+1) + "," + to_string(j - 1);
			if (tiles[coords].Mined()) {
				tiles[t].Addjacent();
			}
			coords = to_string(i-1) + "," + to_string(j + 1);
			if (tiles[coords].Mined()) {
				tiles[t].Addjacent();
			}
			coords = to_string(i+1) + "," + to_string(j + 1);
			if (tiles[coords].Mined()) {
				tiles[t].Addjacent();
			}
			coords = to_string(i-1) + "," + to_string(j - 1);
			if (tiles[coords].Mined()) {
				tiles[t].Addjacent();
			}
			coords = to_string(i) + "," + to_string(j + 1);
			if (tiles[coords].Mined()) {
				tiles[t].Addjacent();
			}
			coords = to_string(i-1) + "," + to_string(j);
			if (tiles[coords].Mined()) {
				tiles[t].Addjacent();
			}
			coords = to_string(i+1) + "," + to_string(j);
			if (tiles[coords].Mined()) {
				tiles[t].Addjacent();
			}
		}
	}
}


Board::Board(int width, int height, vector<bool> mines) {
	_width = width;
	_height = height;
	win = false;
	lost = false;
	debug = false;
	testState = 0;
	_mines = 0;
	tileTotal = _height * _width;
	_allTiles = sf::FloatRect(0, 0, width * 32, height * 32);

	int counter = 0;
	
	//set up the coordinates for the tiles
	for (int i = 0; i < _height; i++) {
		for (int j = 0; j < _width; j++) {
			string coords = to_string(j) + "," + to_string(i);
			tiles.emplace(coords, Tile(j * 32, i * 32));
			if (mines[counter]) {
				tiles[coords].Mine();
				_mines++;
			}
			counter++;
		}
	}
	minecount = _mines;

	//set up numbers
	for (int i = 0; i < _width; i++) {
		for (int j = 0; j < _height; j++) {
			string coords = to_string(i) + "," + to_string(j);
			string t = coords;
			//start checking
			coords = to_string(i) + "," + to_string(j - 1);
			if (tiles[coords].Mined()) {
				tiles[t].Addjacent();
			}
			coords = to_string(i + 1) + "," + to_string(j - 1);
			if (tiles[coords].Mined()) {
				tiles[t].Addjacent();
			}
			coords = to_string(i - 1) + "," + to_string(j + 1);
			if (tiles[coords].Mined()) {
				tiles[t].Addjacent();
			}
			coords = to_string(i + 1) + "," + to_string(j + 1);
			if (tiles[coords].Mined()) {
				tiles[t].Addjacent();
			}
			coords = to_string(i - 1) + "," + to_string(j - 1);
			if (tiles[coords].Mined()) {
				tiles[t].Addjacent();
			}
			coords = to_string(i) + "," + to_string(j + 1);
			if (tiles[coords].Mined()) {
				tiles[t].Addjacent();
			}
			coords = to_string(i - 1) + "," + to_string(j);
			if (tiles[coords].Mined()) {
				tiles[t].Addjacent();
			}
			coords = to_string(i + 1) + "," + to_string(j);
			if (tiles[coords].Mined()) {
				tiles[t].Addjacent();
			}
		}
	}
}


void Board::LoadBoard(sf::RenderWindow& window) {

	sf::Sprite rtile(TextureManager::GetTexture("tile_revealed"));
	sf::Sprite htile(TextureManager::GetTexture("tile_hidden"));
	sf::Sprite mine(TextureManager::GetTexture("mine"));
	sf::Sprite test1(TextureManager::GetTexture("test_1"));
	sf::Sprite test2(TextureManager::GetTexture("test_2"));
	sf::Sprite test3(TextureManager::GetTexture("test_3"));
	sf::Sprite hsmile(TextureManager::GetTexture("face_happy"));
	sf::Sprite wsmile(TextureManager::GetTexture("face_win"));
	sf::Sprite lsmile(TextureManager::GetTexture("face_lose"));
	sf::Sprite flag(TextureManager::GetTexture("flag"));
	sf::Sprite debugbutton(TextureManager::GetTexture("debug"));
	sf::Sprite digits(TextureManager::GetTexture("digits"));

	//draw bottom layer of tiles
	map<string, Tile>::iterator iter = tiles.begin();

	int counter = 0;
	for (; iter != tiles.end(); ++iter) {
		Tile t = iter->second;
		rtile.setPosition(t.getX(), t.getY());
		window.draw(rtile);

		sf::FloatRect f = rtile.getGlobalBounds();
		_oneTile.push_back(f);
		iter->second.setVect(counter);
		counter++;
	}

	//draw mines
	iter = tiles.begin();

	for (; iter != tiles.end(); ++iter) {
		Tile t = iter->second;

		if (t.Mined()) {
			mine.setPosition(t.getX(), t.getY());
			window.draw(mine);
		}
	}

	//draw numbers
	iter = tiles.begin();

	for (; iter != tiles.end(); ++iter) {
		Tile t = iter->second;
		int num = t.getAdjacent();
		if (num > 0 && t.Mined() == false) {
			sf::Sprite number( TextureManager::GetTexture( "number_" + to_string(num) ) );
			number.setPosition(t.getX(), t.getY());
			window.draw(number);
		}
	}
	
	//draw top layer of tiles
	iter = tiles.begin();

	for (; iter != tiles.end(); ++iter) {
		Tile t = iter->second;

		if (t.Hidden()) {
			htile.setPosition(t.getX(), t.getY());
			window.draw(htile);
		}
	}

	//draw flags
	iter = tiles.begin();

	for (; iter != tiles.end(); ++iter) {
		Tile t = iter->second;

		if (t.Flagged()) {
			flag.setPosition(t.getX(), t.getY());
			window.draw(flag);
		}
	}

	//draw mines part 2
	if (debug == true) {
		iter = tiles.begin();
		for (; iter != tiles.end(); ++iter) {
			Tile t = iter->second;

			if (t.Mined()) {
				mine.setPosition(t.getX(), t.getY());
				window.draw(mine);
			}
		}
	}

	//draw test buttons
	test1.setPosition(_width * 16 + 160, _height * 32);
	window.draw(test1);
	_test1 = test1.getGlobalBounds();
	test2.setPosition(_width * 16 + 224, _height * 32);
	window.draw(test2);
	_test2 = test2.getGlobalBounds();
	test3.setPosition(_width * 16 + 288, _height * 32);
	window.draw(test3);
	_test3 = test3.getGlobalBounds();

	//draw debug button
	debugbutton.setPosition(_width * 16 + 96, _height * 32);
	window.draw(debugbutton);
	_debugbutton = debugbutton.getGlobalBounds();

	//draw smiley
	if (win == true) {
		wsmile.setPosition(_width * 16 - 32, _height * 32);
		window.draw(wsmile);
		_smile = wsmile.getGlobalBounds();
	}
	else if (lost == true) {
		lsmile.setPosition(_width * 16 - 32, _height * 32);
		window.draw(lsmile);
		_smile = lsmile.getGlobalBounds();
	}
	else {
		hsmile.setPosition(_width*16 - 32, _height*32);
		window.draw(hsmile);
		_smile = hsmile.getGlobalBounds();
	}

	//draw mine counter
	string drawCount;
	if (win) {
		drawCount = "0";
	}
	else {
		drawCount = to_string(minecount);
	}
	for (unsigned int i = 0; i < drawCount.size(); i++) {
		switch (drawCount[i]) {
			case '-':
				digits.setTextureRect(sf::IntRect(210, 0, 20, 32));
				break;
			case '0':
				digits.setTextureRect(sf::IntRect(0, 0, 20, 32));
				break;
			case '1':
				digits.setTextureRect(sf::IntRect(25, 0, 20, 32));
				break;
			case '2':
				digits.setTextureRect(sf::IntRect(45, 0, 20, 32));
				break;
			case '3':
				digits.setTextureRect(sf::IntRect(65, 0, 20, 32));
				break;
			case '4':
				digits.setTextureRect(sf::IntRect(85, 0, 20, 32));
				break;
			case '5':
				digits.setTextureRect(sf::IntRect(110, 0, 20, 32));
				break;
			case '6':
				digits.setTextureRect(sf::IntRect(130, 0, 20, 32));
				break;
			case '7':
				digits.setTextureRect(sf::IntRect(150, 0, 20, 32));
				break;
			case '8':
				digits.setTextureRect(sf::IntRect(170, 0, 20, 32));
				break;
			case '9':
				digits.setTextureRect(sf::IntRect(190, 0, 20, 32));
				break;
			default:
				cout << "something went wrong" << endl;
				break;
		}
		digits.setPosition((i+1)*20, _height * 32);
		window.draw(digits);
	}
	
}

void Board::Clear() {
	tiles.clear();
}

Tile Board::getTile(int x, int y) {
	
	string coords = to_string(x) + "," + to_string(y);
	
	map<string, Tile>::iterator iter = tiles.find(coords);

	if (iter != tiles.end()) {
		return iter->second;
	}
	
}

void Board::LeftClick(sf::Vector2f mousePos) {
	if (_debugbutton.contains(mousePos) && !win && !lost) {
		if (debug == true) {
			debug = false;
		}
		else {
			debug = true;
		}
	}
	else if (_smile.contains(mousePos))
	{
		testState = 4;
	}
	else if (_test1.contains(mousePos)) {
		testState = 1;
	}
	else if (_test2.contains(mousePos)) {
		testState = 2;
	}
	else if (_test3.contains(mousePos)) {
		testState = 3;
	}
	else if (_allTiles.contains(mousePos) && !win && !lost) {
		LeftClickTile(mousePos);
	}
}

void Board::RightClick(sf::Vector2f mousePos) {
	if (!win && !lost) {
		//iterate through the vector of floatrects for each tile
		for (unsigned int i = 0; i < _oneTile.size(); i++) {
			//found the correct floatrect
			if (_oneTile[i].contains(mousePos)) {
				//iterate through the map of tiles to find the corresponding tile to the floatrect
				map<string, Tile>::iterator iter = tiles.begin();
				for (; iter != tiles.end(); ++iter) {
					Tile t = iter->second;
					int index = t.getVect();
					//at this point i == the index of the vector 
					if (index == i) {
						//right now Tile t (iter->second) is the tile that has been clicked
						//determine what to do with the tile based on what it is
						if (iter->second.Hidden()) {
							iter->second.Flag();
							if (iter->second.Flagged()) {
								minecount--;
							}
							else {
								minecount++;
							}
						}
					}
				}
				break;
			}
		}
	}
}

sf::FloatRect Board::getsmile() {
	return _smile;
}

void Board::LeftClickTile(sf::Vector2f mousePos) {

	//I feel like this could have been less clunky but oh well
	// 
	//iterate through the vector of floatrects for each tile
	for (unsigned int i = 0; i < _oneTile.size(); i++) {
		//found the correct floatrect
		if (_oneTile[i].contains(mousePos)) {
			//iterate through the map of tiles to find the corresponding tile to the floatrect
			map<string, Tile>::iterator iter = tiles.begin();
			for (; iter != tiles.end(); ++iter) {
				Tile t = iter->second;
				int index = t.getVect();
				//at this point i == the index of the vector 
				if (index == i) {
					//right now Tile t (iter->second) is the tile that has been clicked
					//determine what to do with the tile based on what it is
					if (iter->second.Hidden()) {
						//if the tile is mined and not flagged, lose
						if (iter->second.Mined() && iter->second.Flagged() == false) {
							iter->second.Unhide();
							lost = true;
							
							//unhide all mines except if they're flagged
							map<string, Tile>::iterator newiter = tiles.begin();
							for (; newiter != tiles.end(); ++newiter) {
								if (newiter->second.Mined() && !newiter->second.Flagged()) {
									newiter->second.Unhide();
								}
							}
						}

						//if the tile is not mined and not flagged
						if (iter->second.Mined() == false && iter->second.Flagged() == false) {
							iter->second.Unhide();
							if (iter->second.getAdjacent() == 0) {
								showTile(iter->second);
							}

							//check to see if revealing this tile has won the game
							map<string, Tile>::iterator newiter = tiles.begin();
							int counter = 0;
							for (; newiter != tiles.end(); ++newiter) {
								if (newiter->second.getReal() && !newiter->second.Mined() && !newiter->second.Hidden()) {
									counter++;
								}
							}
							
							if (tileTotal - _mines - counter == 0) {
								win = true;
								debug = false;
								//flag any remaining mines
								map<string, Tile>::iterator iter3 = tiles.begin();
								for (; iter3 != tiles.end(); ++iter3) {
									if (iter3->second.Mined() && !iter3->second.Flagged()) {
										iter3->second.Flag();
									}
								}
							}
						}
					}
				}
			}
			break;
		}
	}
}

void Board::showTile(Tile& t) {
	int x = t.getX() / 32;
	int y = t.getY() / 32;
	string key = to_string(x) + "," + to_string(y);

	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			key = to_string(x+i) + "," + to_string(y + j);
			map<string, Tile>::iterator iter = tiles.find(key);
			if (iter != tiles.end()) {
				if (iter->second.Hidden()) {
					if (!iter->second.Mined() && !iter->second.Flagged()) {
						iter->second.Unhide();
						if (iter->second.getAdjacent() == 0) {
							showTile(iter->second); //recursion let's go
						}
					}
				}
			}
		}
	}
}

int Board::getTestState() {
	return testState;
}

void Board::setTestState(int num) {
	testState = num;
}