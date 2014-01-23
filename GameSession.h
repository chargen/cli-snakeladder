/*
 * GameSession.h
 *
 *  Created on: Jan 15, 2014
 *      Author: dmartana
 */

#ifndef GAMESESSION_H_
#define GAMESESSION_H_

#include<map>
#include<vector>
#include<string>
#include "Player.h"

#ifdef _WIN32
#include "time.h"
#include "windows.h"
#else
#include "unistd.h"
#define Sleep(x) usleep((x) * 1000)
#endif

class GameSession {
public:
	GameSession();
	virtual ~GameSession();

	void start();

private:
	int getBoardSize();
	void createBoard(int numOfSquares, int numOfSnakes, int numOfLadders);
	void createPlayer(const std::string& name);
	bool wonBy(const Player& p);
	bool gotSnakeTail(const Player& p);
	bool gotLadderBase(const Player& p);
	void createSnakes();
	void createLadders();
	int getNumOfPlayers();
	int throwDie();
	std::pair<std::string, int> play(Player& p);
	int getUserInput();

	std::map<int, int> snakeMap; // key: snake tail, value: snake head
	std::map<int, int> ladderMap; // key: ladder base, value: ladder top
	std::vector<Player> playerVector;
	unsigned int boardSize;
	unsigned int numOfSnakes;
	unsigned int numOfLadders;
	unsigned int currentPlayer;
};

#endif /* GAMESESSION_H_ */
