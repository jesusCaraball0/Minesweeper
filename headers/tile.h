#pragma once
#include<SFML/Graphics.hpp>
#include<fstream>
#include<vector>
#include<string>
#include<map>

using namespace std;

class Tile {
	sf::Texture hiddenTile;
	sf::Texture revealedTile;
	sf::Sprite tile;
	sf::Sprite flag;
	sf::Sprite mine;
	sf::Sprite number;
	bool isInteracted;
	bool hasMine;
	bool showMine;
	bool isFlagged;
	int nearbyMines;

public:
	Tile(sf::Sprite thisSprite);

	sf::Sprite getTile();
	sf::Texture getTexture();
	sf::Sprite getFlag();
	sf::Sprite getMine();
	sf::Sprite getNumber();
	bool getIsInteracted();
	bool getHasMine();
	bool getShowMine();
	int getNearbyMines();
	bool getIsFlagged();
	void placeFlag(map<string, sf::Texture>& textures);
	void setIsInteracted(bool _isInteracted);
	void revealTile(map<string, sf::Texture>& textures);
	void setShowMine(bool prevMine);
	void setHasMine(bool value);
	void setMine(sf::Sprite nonMine);
	void interactTile(map<string, sf::Texture>& textures);
	void setPosition(float x, float y);
	void setTexture(string filename);
	void setMine(map<string, sf::Texture>& textures);
	void setNotInteracted(sf::Sprite newTile, map<string, sf::Texture>& textures);
	void setNearbyMines(int _nearbyMines);

};