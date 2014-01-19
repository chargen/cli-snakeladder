/*
 * GameSession.h
 *
 *  Created on: Jan 15, 2014
 *      Author: dmartana
 */

#ifndef GAMESESSION_H_
#define GAMESESSION_H_

#include<map>
#include<string>
#include "Player.h"

#ifdef _WIN32
#include "time.h"
#endif

class GameSession {
public:
	GameSession();
	virtual ~GameSession();

	int getBoardSize();
	void createBoard(int numOfSquares, int numOfSnakes, int numOfLadders);
	void createPlayer(const std::string& name);
	bool wonBy(const Player& p);
	bool gotSnakeTail(const Player& p);
	bool gotLadderBase(const Player& p);
	void createSnakes();
	void createLadders();
	void setNumOfSnakes(int snakes);
	void setNumOfLadder(int ladder);
	int getNumOfPlayers();
	Player* nextPlayer();
	int throwDie();
	std::pair<std::string, int> play();

private:
	std::map<int, int> snakeMap; // key: snake tail, value: snake head
	std::map<int, int> ladderMap; // key: ladder base, value: ladder top
	std::map<int, Player*> playerMap;
	unsigned int boardSize;
	unsigned int numOfSnakes;
	unsigned int numOfLadders;
	unsigned int currentPlayer;
};

#endif /* GAMESESSION_H_ */
