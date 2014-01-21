/*
 * GameSession.cpp
 *
 *  Created on: Jan 15, 2014
 *      Author: dmartana
 */

#include<iostream>
#include<cstdlib>
#include "GameSession.h"

GameSession::GameSession() : boardSize(100), numOfSnakes(5), numOfLadders(5), currentPlayer(0) {
	srand(time(NULL));
}

GameSession::~GameSession() {
	// TODO Auto-generated destructor stub
}

int GameSession::getBoardSize() {
	return boardSize;
}

void GameSession::createBoard(int squares, int snakes, int ladders) {
	boardSize = squares;
	numOfSnakes = snakes;
	numOfLadders = ladders;
}

void GameSession::createSnakes() {
	// Condition:
	// 1. key: tail, value: head
	// 2. tail > head
	for (unsigned int i = 0; i < numOfSnakes; i++) {
		int tail = rand() % (boardSize - 2) + 2; // from 2 to boardSize-1
		int head = rand() % (boardSize - 2) + 1; // from 1 to boardSize-2
		while (head >= tail) {
			head = rand() % (boardSize - 2) + 1; // if head >= tail, re-generate the value of head until it is smaller than tail
		}
		snakeMap[tail] = head;
	}
}

void GameSession::createLadders() {
	// Condition:
	// 1. key: base, value: top
	// 2. top > base
	for (unsigned int i =0; i < numOfLadders; i++) {
		int top = rand() % (boardSize - 2) + 2; // from 2 to boardSize-1
		int base = rand() % (boardSize - 2) + 1; // from 1 to boardSize-2
		while (base >= top) {
			base = rand() % (boardSize - 2) + 1; // if base >= top, re-generate the value of base until it is smaller than top
		}
		ladderMap[base] = top;
	}
}

void GameSession::setNumOfSnakes(int snakes) {
	numOfSnakes = snakes;
}

void GameSession::setNumOfLadder(int ladders) {
	numOfLadders = ladders;
}

void GameSession::createPlayer(const std::string& name) {
	playerMap[playerMap.size()] = new Player(name);
}

bool GameSession::wonBy(const Player& p) {
	return p.getCurrentPos() >= boardSize;
}

bool GameSession::gotSnakeTail(const Player& p) {
	return snakeMap.count(p.getCurrentPos()) != 0;
}

bool GameSession::gotLadderBase(const Player& p) {
	return ladderMap.count(p.getCurrentPos()) != 0;
}

int GameSession::getNumOfPlayers() {
	return playerMap.size();
}

Player* GameSession::nextPlayer() {
	if (currentPlayer == playerMap.size() - 1) {
		currentPlayer = 0;
		return playerMap[playerMap.size() - 1];
	}
	else
	{
		return playerMap[currentPlayer++];
	}
}

int GameSession::throwDie()
{
	int die = rand()%6 + 1;

	return die;
}

std::pair<std::string, int> GameSession::play() {
	std::pair<std::string, int> turnResult;

	Player* p = nextPlayer();
	int steps = throwDie();
	p->move(steps);
	std::cout << p->getName() << " moves " << steps << " steps to square no. " << p->getCurrentPos() << std::endl;

	if (wonBy(*p)) {
		turnResult = std::make_pair(p->getName(), 1);
		return turnResult;
	}

	if (gotSnakeTail(*p)) {
		p->setCurrentPos(snakeMap[p->getCurrentPos()]);
		std::cout << "Alas! SNAKE\'s tail. Move back to square no. " << p->getCurrentPos() << std::endl;
	}

	if (gotLadderBase(*p)) {
		p->setCurrentPos(ladderMap[p->getCurrentPos()]);
		std::cout << "Hooray! LADDER! Move up to square no. " << p->getCurrentPos() << std::endl;
	}

	turnResult = std::make_pair(p->getName(), 0);

	return turnResult;
}
