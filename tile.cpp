#include<SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<map>
#include"tile.h"

using namespace std;


Tile::Tile(sf::Sprite thisSprite) {
	hiddenTile.loadFromFile("images/tile_hidden.png");
	revealedTile.loadFromFile("images/tile_revealed.png");
	tile = thisSprite;
	isInteracted = false;
	hasMine = false;
	showMine = false;
	isFlagged = false;
	nearbyMines = 0;
}

void Tile::interactTile(map<string, sf::Texture>& textures) {


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (isFlagged) {
			return;
		}
		else if (hasMine) {
			setMine(textures);
			showMine = true;
			tile.setTexture(revealedTile);
		}
		else if (nearbyMines > 0) {
			number.setPosition(tile.getPosition());
			string thisNumber = "number_";
			thisNumber += char(48 + nearbyMines);
			number.setTexture(textures[thisNumber]);
		}
		tile.setTexture(revealedTile);


	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		if (isFlagged) {
			sf::Sprite newFlag;
			flag.setPosition(tile.getPosition());
			flag = newFlag;
			isFlagged = false;
			isInteracted = false;
			return;

		}
		else if (!isInteracted) {
			flag.setPosition(tile.getPosition());
			flag.setTexture(textures["flag"]);
			isFlagged = true;
		}
		else {
			return;
		}

	}
	isInteracted = true;
}

void Tile::placeFlag(map<string, sf::Texture>& textures) {
	flag.setPosition(tile.getPosition());
	flag.setTexture(textures["flag"]);
	isFlagged = true;
}

void Tile::setPosition(float x, float y) {
	tile.setPosition(sf::Vector2f(x, y));
}

void Tile::setTexture(string filename) {
	sf::Texture thisTexture;
	thisTexture.loadFromFile(filename);
	tile.setTexture(thisTexture);
}

void Tile::setMine(map<string, sf::Texture>& textures) {
	mine.setTexture(textures["mine"]);
	mine.setPosition(tile.getPosition());
	hasMine = true;
}

void Tile::setHasMine(bool value) {
	hasMine = value;
}

void Tile::setMine(sf::Sprite nonMine) {
	mine = nonMine;
}

void Tile::setNotInteracted(sf::Sprite newTile, map<string, sf::Texture>& textures) {
	tile = newTile;
	sf::Sprite newFlag;
	newFlag.setPosition(flag.getPosition());
	flag = newFlag;
	isInteracted = false;
	isFlagged = false;
	sf::Sprite newNumber;
	newNumber.setPosition(number.getPosition());
	number = newNumber;
}

void Tile::setShowMine(bool prevMine) {
	showMine = !prevMine;
}

void Tile::setNearbyMines(int _nearbyMines) {
	nearbyMines = _nearbyMines;
}

void Tile::revealTile(map<string, sf::Texture>& textures) {
	tile.setTexture(revealedTile);
	if (nearbyMines > 0) {
		number.setPosition(tile.getPosition());
		string thisNumber = "number_";
		thisNumber += char(48 + nearbyMines);
		number.setTexture(textures[thisNumber]);
	}
}

void Tile::setIsInteracted(bool _isInteracted) {
	isInteracted = _isInteracted;
}


// ============== ACCESSSORS ===============
sf::Sprite Tile::getTile() {
	return tile;
}

sf::Texture Tile::getTexture() {
	return hiddenTile;
}

sf::Sprite Tile::getFlag() {
	return flag;
}

sf::Sprite Tile::getMine() {
	return mine;
}

sf::Sprite Tile::getNumber() {
	return number;
}

bool Tile::getIsInteracted() {
	return isInteracted;
}

bool Tile::getHasMine() {
	return hasMine;
}

bool Tile::getShowMine() {
	return showMine;
}

bool Tile::getIsFlagged() {
	return isFlagged;
}

int Tile::getNearbyMines() {
	return nearbyMines;
}