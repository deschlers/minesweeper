#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureManager.h"
#include "Board.h"
#include <fstream>
#include <string>

using namespace std;

Board createBoard(string filename) {
    ifstream inFile(filename);

    string data;
    getline(inFile, data);
    int width = stoi(data);
    getline(inFile, data);
    int height = stoi(data);
    getline(inFile, data);
    int mines = stoi(data);

    Board board1(width, height, mines);

    return board1;
}


Board createTest(string filename) {
    ifstream inFile(filename);

    string data;
    int height = 0;
    int width = 0;
    vector<bool> mines;

    while (getline(inFile, data)) {
        for (unsigned int i = 0; i < data.size(); i++) {
            bool foo;
            if (data[i] == '0') {
                foo = false;
            }
            else {
                foo = true;
            }
            mines.push_back(foo);
            width++;
        }
        height++;
    }
    width = width / height;
    Board board2(width, height, mines);
    return board2;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Minesweeper");
   
    //read the config board
    Board currentBoard = createBoard("boards/config.cfg");
    

    while (window.isOpen())
    {
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
            window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    // transform the mouse position from window coordinates to world coordinates
                    sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                    //tell the board that is has been right clicked
                    currentBoard.RightClick(mouse);
                    
                }
                else if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // transform the mouse position from window coordinates to world coordinates
                    sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                    //tell the board that it has been left clicked
                    currentBoard.LeftClick(mouse);
                }
            }
        }

        //clear anything already there
        window.clear();

        //check test state
        if (currentBoard.getTestState() == 1) {
            currentBoard = createTest("boards/testboard1.brd");
        }
        else if (currentBoard.getTestState() == 2) {
            currentBoard = createTest("boards/testboard2.brd");
        }
        else if (currentBoard.getTestState() == 3) {
            currentBoard = createTest("boards/testboard3.brd");
        }
        else if (currentBoard.getTestState() == 4) {
            currentBoard = createBoard("boards/config.cfg");
        }

        //draw the current board
        currentBoard.LoadBoard(window);

        //present the drawings
        window.display();
    }

    return 0;
}