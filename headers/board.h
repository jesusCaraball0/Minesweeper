#pragma once
#include<SFML/Graphics.hpp>
#include<fstream>
#include<vector>
#include<string>
#include<map>
#include"tile.h"

using namespace std;




class Board {
	int height = 0;
	int width = 0;
	int mineCount = 0;
	int tileCount = 0;
	int currentCount = 0;
	int interactedCount = 0;
	vector<vector<Tile>> boardTiles;
	sf::Sprite digitOne;
	sf::Sprite digitTwo;
	sf::Sprite digitThree;
	sf::Sprite faceHappy;
	sf::Sprite test1;
	sf::Sprite test2;
	sf::Sprite test3;
	sf::Sprite debug;


public:
	Board(string filename, map<string, sf::Texture>& textures);
	vector<vector<Tile>>& getBoardTiles();
	void clearMines();
	void clearInteracted(map<string, sf::Texture>& textures);
	void setNearbyMines();
	void recursiveReveal(unsigned int j, unsigned int i, map<string, sf::Texture>& textures);
	void updateCount(int _thisCount);
	void interactWithTile(map<string, sf::Texture>& textures, int j, int i);
	void setMineCount(int _mineCount);
	void setFaceTexture(map<string, sf::Texture>&textures, string face);
	void setCurrentCount(int _currentCount);
	int getHeight();
	int getWidth();
	int getMineCount();
	int getTileCount();
	int getCurrentCount();
	int getInteractedCount();
	sf::Sprite getFaceHappy();
	sf::Sprite getTest1();
	sf::Sprite getTest2();
	sf::Sprite getTest3();
	sf::Sprite getDebug();
	sf::Sprite getDigitOne();
	sf::Sprite getDigitTwo();
	sf::Sprite getDigitThree();

};