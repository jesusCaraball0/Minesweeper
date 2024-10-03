#include<SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<map>
#include"tile.h"
#include"board.h"
#include"random.h"

using namespace std;

Board::Board(string filename, map<string, sf::Texture>& textures) {

	ifstream inFile(filename);
	if (inFile.is_open()) {

		string tempHeight;
		getline(inFile, tempHeight);
		height = stoi(tempHeight);

		string tempWidth;
		getline(inFile, tempWidth);
		width = stoi(tempWidth);

		string tempMines;
		getline(inFile, tempMines);
		mineCount = stoi(tempMines);

		tileCount = height * width;
		
		
		faceHappy.setTexture(textures["face_happy"]);
		faceHappy.setPosition(float(((height / 2.0) * 32) - 32), float(width * 32));

		test1.setTexture(textures["test_1"]);
		test1.setPosition(float((height - 6) * 32), float(width * 32));

		test2.setTexture(textures["test_2"]);
		test2.setPosition(float((height - 4) * 32), float(width * 32));

		test3.setTexture(textures["test_3"]);
		test3.setPosition(float((height - 2) * 32), float(width * 32));

		debug.setTexture(textures["debug"]);
		debug.setPosition(float((height - 8) * 32), float(width * 32));


		currentCount = mineCount;
		digitOne.setTexture(textures["digits"]);
		digitOne.setPosition(float(0), float(width * 32));
		digitOne.setTextureRect(sf::IntRect((21 * (currentCount / 100)), 0, 21, 32));

		digitTwo.setTexture(textures["digits"]);
		digitTwo.setPosition(float(32), float(width * 32));
		digitTwo.setTextureRect(sf::IntRect((21 * (currentCount / 10)), 0, 21, 32));

		digitThree.setTexture(textures["digits"]);
		digitThree.setPosition(float(64), float(width * 32));
		digitThree.setTextureRect(sf::IntRect((21 * (currentCount % 10)), 0, 21, 32));

		vector<Tile> rowTiles;
		for (int j = 0; j < height; j++) {
			rowTiles.clear();
			for (int i = 0; i < width; i++) {
				sf::Sprite newTile;

				newTile.setTexture(textures["tile_hidden"]);
				newTile.setPosition(32.f * j, 32.f * i);
				Tile thisTile(newTile);
				rowTiles.push_back(thisTile);
			}
			boardTiles.push_back(rowTiles);
		}

		for (int i = 0; i < mineCount; i++) {
			int newMineColumn = Random::Int(0, (boardTiles.size() - 1));
			int newMineRow = Random::Int(0, (boardTiles[0].size() - 1));
			while (boardTiles[newMineColumn][newMineRow].getHasMine()) {
				newMineColumn = Random::Int(0, (boardTiles.size() - 1));
				newMineRow = Random::Int(0, (boardTiles[0].size() - 1));
			}
			boardTiles[newMineColumn][newMineRow].setMine(textures);
		}

		setNearbyMines();
		interactedCount = 0;

	}
}

void Board::interactWithTile(map<string, sf::Texture>& textures, int j, int i) {
	if (!boardTiles[j][i].getIsInteracted() || boardTiles[j][i].getIsFlagged()) {
		boardTiles[j][i].interactTile(textures);
		if (!boardTiles[j][i].getIsFlagged() && boardTiles[j][i].getIsInteracted() && !boardTiles[j][i].getHasMine()) {
			recursiveReveal(j, i, textures);
			interactedCount++;
		}
	}
}

void Board::setCurrentCount(int _currentCount) {
	currentCount = _currentCount;
}

void Board::updateCount(int _thisCount) {
	if (_thisCount >= 0) {
		digitOne.setTextureRect(sf::IntRect((21 * (_thisCount / 100)), 0, 21, 32));
		digitTwo.setTextureRect(sf::IntRect((21 * (_thisCount / 10)), 0, 21, 32));
		digitThree.setTextureRect(sf::IntRect((21 * (_thisCount % 10)), 0, 21, 32));
	}
	else {
		digitOne.setTextureRect(sf::IntRect((21 * 10), 0, 21, 32));
		digitTwo.setTextureRect(sf::IntRect((21 * ((-_thisCount) / 10)), 0, 21, 32));
		digitThree.setTextureRect(sf::IntRect((21 * ((-_thisCount) % 10)), 0, 21, 32));

	}
	
}

void Board::recursiveReveal(unsigned int j, unsigned int i, map<string, sf::Texture>& textures) {

	if (j >= boardTiles.size()) {
		return;
	}
	else if (i >= boardTiles[j].size()) {
		return;
	}
	else {
		if (!boardTiles[j][i].getIsInteracted() && !boardTiles[j][i].getIsFlagged()) {
			interactedCount++;
			boardTiles[j][i].revealTile(textures);
			boardTiles[j][i].setIsInteracted(true);
		}
		
		if (boardTiles[j][i].getNearbyMines() == 0 && !boardTiles[j][i].getIsFlagged()) {
			recursiveReveal(j + 1, i, textures);
			recursiveReveal(j, i - 1, textures);
			//recursiveReveal(j - 1, i, textures);
			//recursiveReveal(j, i + 1, textures);
		}
		else {
			return;
		}
	}
}

void Board::clearMines() {
	for (unsigned int j = 0; j < boardTiles.size(); j++) {
		for (unsigned int i = 0; i < boardTiles[j].size(); i++) {
			if (boardTiles[j][i].getHasMine()) {
				sf::Sprite nonMine;
				boardTiles[j][i].setMine(nonMine);
				boardTiles[j][i].setHasMine(false);
				boardTiles[j][i].setShowMine(true);
			}
		}
	}
}

void Board::clearInteracted(map<string, sf::Texture>& textures) {
	for (unsigned int j = 0; j < boardTiles.size(); j++) {
		for (unsigned int i = 0; i < boardTiles[j].size(); i++) {
			if (boardTiles[j][i].getIsInteracted() || boardTiles[j][i].getIsFlagged()) {
				sf::Sprite newTile;
				newTile.setTexture(textures["tile_hidden"]);
				newTile.setPosition(boardTiles[j][i].getTile().getPosition());
				boardTiles[j][i].setNotInteracted(newTile, textures);
			}
		}
	}
	interactedCount = 0; 

}

void Board::setNearbyMines() {
	int nearbyMines = 0; 
	for (unsigned int j = 0; j < boardTiles.size(); j++) {
		for (unsigned int i = 0; i < boardTiles[j].size(); i++) {
			nearbyMines = 0;
			if ((i + 1) < (boardTiles[j].size() - 1)) {
				if (boardTiles[j][i + 1].getHasMine()) nearbyMines++;
			}
			if ((i - 1) < (boardTiles[j].size() - 1)) {
				if (boardTiles[j][i - 1].getHasMine()) nearbyMines++;
			}
			if ((j - 1) < (boardTiles.size() - 1)) {
				if (boardTiles[j - 1][i].getHasMine()) nearbyMines++;
				if ((i - 1) < (boardTiles[j].size() - 1)) {
					if (boardTiles[j - 1][i - 1].getHasMine()) nearbyMines++;
				}
				if ((i + 1) < (boardTiles[j].size() - 1)) {
					if (boardTiles[j - 1][i + 1].getHasMine()) nearbyMines++;
				}
			}
			if ((j + 1) < (boardTiles.size() - 1)) {
				if (boardTiles[j + 1][i].getHasMine()) nearbyMines++;
				if ((i - 1) < (boardTiles[j].size() - 1)) {
					if (boardTiles[j + 1][i - 1].getHasMine()) nearbyMines++;
				}
				if ((i + 1) < (boardTiles[j].size() - 1)) {
					if (boardTiles[j + 1][i + 1].getHasMine()) nearbyMines++;
				}
			}
			boardTiles[j][i].setNearbyMines(nearbyMines);
		}
	}
}

void Board::setMineCount(int _mineCount) {
	mineCount = _mineCount;
}

void Board::setFaceTexture(map<string, sf::Texture>& textures, string face) {
	faceHappy.setTexture(textures[face]);
}


int Board::getTileCount() {
	return tileCount;
}

vector<vector<Tile>>& Board::getBoardTiles() {
	return boardTiles;
}

int Board::getHeight() {
	return (height * 32);
}

int Board::getWidth() {
	return (width * 32) + 100;
}

int Board::getMineCount() {
	return mineCount;
}

sf::Sprite Board::getFaceHappy() {
	return faceHappy;
}

sf::Sprite Board::getTest1() {
	return test1;
}

sf::Sprite Board::getTest2() {
	return test2;
}

sf::Sprite Board::getTest3() {
	return test3;
}

sf::Sprite Board::getDebug() {
	return debug;
}

sf::Sprite Board::getDigitOne() {
	return digitOne;
}

sf::Sprite Board::getDigitTwo() {
	return digitTwo;
}

sf::Sprite Board::getDigitThree() {
	return digitThree;
}

int Board::getCurrentCount() {
	return currentCount;
}

int Board::getInteractedCount() {
	return interactedCount;
}