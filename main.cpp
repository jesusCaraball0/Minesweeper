#include<SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<map>
#include"board.h"
#include"tile.h"
#include"random.h"

using namespace std;

void setTextures(map < string, sf::Texture>& textures);
void readTestBoard(string filename, Board& gameBoard, map<string, sf::Texture>& textures, int& tempMines);
void updateBoard(Board& gameBoard);
void winGameCheck(Board& gameBoard, map<string, sf::Texture>& textures, bool& isInteractable);
void loseGameCheck(Board& gameBoard, map<string, sf::Texture>& textures, bool& isInteractable, int j, int i);

int main() {

	map<string, sf::Texture> textures;
	setTextures(textures);
	Board gameBoard("boards/config.cfg", textures);
	bool isInteractable = true;
	int tempMines = gameBoard.getMineCount();

	sf::RenderWindow window(sf::VideoMode(gameBoard.getHeight(), gameBoard.getWidth()), "GameBoard");

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				if (isInteractable) {
					for (unsigned int j = 0; j < gameBoard.getBoardTiles().size(); j++) {
						for (unsigned int i = 0; i < gameBoard.getBoardTiles()[j].size(); i++) {
							if (gameBoard.getBoardTiles()[j][i].getTile().getGlobalBounds().contains(float(mousePosition.x), float(mousePosition.y))) {
								gameBoard.interactWithTile(textures, j, i);
								winGameCheck(gameBoard, textures, isInteractable);
								loseGameCheck(gameBoard, textures, isInteractable, j, i);
							}
						}
					}
				}
				if (gameBoard.getTest1().getGlobalBounds().contains(float(mousePosition.x), float(mousePosition.y))) {
							gameBoard.clearInteracted(textures);
							readTestBoard("boards/testboard1.brd", gameBoard, textures, tempMines);
							isInteractable = true;
				}
				else if (gameBoard.getTest2().getGlobalBounds().contains(float(mousePosition.x), float(mousePosition.y))) {
							gameBoard.clearInteracted(textures);
							readTestBoard("boards/testboard2.brd", gameBoard, textures, tempMines);
							isInteractable = true;
						}
				else if (gameBoard.getTest3().getGlobalBounds().contains(float(mousePosition.x), float(mousePosition.y))) {
							gameBoard.clearInteracted(textures);
							readTestBoard("boards/testboard3.brd", gameBoard, textures, tempMines);
							isInteractable = true;
						}
				else if (gameBoard.getDebug().getGlobalBounds().contains(float(mousePosition.x), float(mousePosition.y))) {
					if (isInteractable) {
						for (unsigned int j = 0; j < gameBoard.getBoardTiles().size(); j++) {
							for (unsigned int i = 0; i < gameBoard.getBoardTiles()[j].size(); i++) {
								gameBoard.getBoardTiles()[j][i].setShowMine(gameBoard.getBoardTiles()[j][i].getShowMine());
							}
						}
					}
					}
				else if (gameBoard.getFaceHappy().getGlobalBounds().contains(float(mousePosition.x), float(mousePosition.y))) {
					Board newGameBoard("boards/config.cfg", textures);
					gameBoard = newGameBoard;
					isInteractable = true;

				}
				if (isInteractable) {
					gameBoard.setFaceTexture(textures, "face_happy");
				}
				updateBoard(gameBoard);
			}
					window.clear();
					for (unsigned int j = 0; j < gameBoard.getBoardTiles().size(); j++) {
						for (unsigned int i = 0; i < gameBoard.getBoardTiles()[j].size(); i++) {
							window.draw(gameBoard.getBoardTiles()[j][i].getTile());
							window.draw(gameBoard.getBoardTiles()[j][i].getFlag());
							window.draw(gameBoard.getBoardTiles()[j][i].getNumber());
							if (gameBoard.getBoardTiles()[j][i].getShowMine()) {
								window.draw(gameBoard.getBoardTiles()[j][i].getMine());
							}
						}
					}
					window.draw(gameBoard.getTest1());
					window.draw(gameBoard.getTest2());
					window.draw(gameBoard.getTest3());
					window.draw(gameBoard.getFaceHappy());
					window.draw(gameBoard.getDebug());
					window.draw(gameBoard.getDigitOne());
					window.draw(gameBoard.getDigitTwo());
					window.draw(gameBoard.getDigitThree());
					window.display();
				}
			}
	return 0;
}

void setTextures(map <string, sf::Texture>& textures) {
	sf::Texture thisTexture;
	thisTexture.loadFromFile("images/digits.png");
	textures.emplace("digits", thisTexture);
	thisTexture.loadFromFile("images/debug.png");
	textures.emplace("debug", thisTexture);
	thisTexture.loadFromFile("images/face_lose.png");
	textures.emplace("face_lose", thisTexture);
	thisTexture.loadFromFile("images/face_happy.png");
	textures.emplace("face_happy", thisTexture);
	thisTexture.loadFromFile("images/face_win.png");
	textures.emplace("face_win", thisTexture);
	thisTexture.loadFromFile("images/mine.png");
	textures.emplace("mine", thisTexture);
	thisTexture.loadFromFile("images/flag.png");
	textures.emplace("flag", thisTexture);
	thisTexture.loadFromFile("images/face_win.png");
	textures.emplace("face_win", thisTexture);
	for (int i = 1; i < 9; i++) {
		string thisNumber = "number_";
		thisNumber += char(i + 48);
		string thisFile = "images/" + thisNumber + ".png";
		thisTexture.loadFromFile(thisFile);
		textures.emplace(thisNumber, thisTexture);
	}
	for (int i = 1; i < 4; i++) {
		string thisTest = "test_";
		thisTest += char(i + 48);
		string thisFile = "images/" + thisTest + ".png";
		thisTexture.loadFromFile(thisFile);
		textures.emplace(thisTest, thisTexture);
	}
	thisTexture.loadFromFile("images/tile_hidden.png");
	textures.emplace("tile_hidden", thisTexture);
	thisTexture.loadFromFile("images/tile_revealed.png");
	textures.emplace("tile_revealed", thisTexture);

}

void readTestBoard(string filename, Board& gameBoard, map<string, sf::Texture>& textures, int& tempMines) {
	ifstream inFile(filename);
	vector<vector<int>> readBoard;
	vector<int> readRow;
	if (inFile.is_open()) {
		string oneRow;
		while (getline(inFile, oneRow)) {
			readRow.clear();
			for (unsigned int i = 0; i < oneRow.size(); i++) {
				readRow.push_back(int(oneRow[i]) - 48);
			}
			readBoard.push_back(readRow);
		}
	}
	gameBoard.clearMines();
	int mineCount = 0; 
	for (unsigned int i = 0; i < readBoard.size(); i++) {
		for (unsigned int j = 0; j < readBoard[i].size(); j++) {
			if (readBoard[i][j] == 1) {
				mineCount++;
			}
		}
	}
	tempMines = gameBoard.getMineCount();
	gameBoard.setCurrentCount(mineCount);
	gameBoard.setMineCount(mineCount);
	for (unsigned int j = 0; j < gameBoard.getBoardTiles().size(); j++) {
		for (unsigned int i = 0; i < gameBoard.getBoardTiles()[j].size(); i++) {
			if (readBoard[i][j] == 1) {
				gameBoard.getBoardTiles()[j][i].setMine(textures);
			}
		}
	}
	gameBoard.setNearbyMines();

}

void updateBoard(Board& gameBoard) {
	int initialCount = gameBoard.getCurrentCount();
	int getSubtractAmount = 0;
	for (unsigned int j = 0; j < gameBoard.getBoardTiles().size(); j++) {
		for (unsigned int i = 0; i < gameBoard.getBoardTiles()[j].size(); i++) {
			if (gameBoard.getBoardTiles()[j][i].getIsFlagged()) {
				getSubtractAmount--;
			}	
		}
	}
	gameBoard.updateCount(initialCount + getSubtractAmount);
}

void winGameCheck(Board& gameBoard, map<string, sf::Texture>& textures, bool& isInteractable) {
	if ((gameBoard.getTileCount() - gameBoard.getMineCount()) == gameBoard.getInteractedCount()) {
		gameBoard.setFaceTexture(textures, "face_win");
		for (unsigned int j = 0; j < gameBoard.getBoardTiles().size(); j++) {
			for (unsigned int i = 0; i < gameBoard.getBoardTiles()[j].size(); i++) {
				if (gameBoard.getBoardTiles()[j][i].getHasMine()) {
					gameBoard.getBoardTiles()[j][i].placeFlag(textures);
				}
			}
		}
		isInteractable = false;
	}
}

void loseGameCheck(Board& gameBoard, map<string, sf::Texture>& textures, bool& isInteractable, int j, int i) {
	if (gameBoard.getBoardTiles()[j][i].getShowMine() && gameBoard.getBoardTiles()[j][i].getIsInteracted()) {
		gameBoard.setFaceTexture(textures, "face_lose");
		for (unsigned int j = 0; j < gameBoard.getBoardTiles().size(); j++) {
			for (unsigned int i = 0; i < gameBoard.getBoardTiles()[j].size(); i++) {
				if (gameBoard.getBoardTiles()[j][i].getHasMine()) {
					gameBoard.getBoardTiles()[j][i].setShowMine(false);
				}
			}
		}
		isInteractable = false;
	}
}
