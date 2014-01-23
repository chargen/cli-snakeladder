/*
 * GameSession.cpp
 *
 *  Created on: Jan 15, 2014
 *      Author: dmartana
 */

#include<iostream>
#include<cstdlib>
#include "GameSession.h"

GameSession::GameSession() : boardSize(100), numOfSnakes(5), numOfLadders(5), currentPlayer(0)
{
	srand(time(NULL));
}

GameSession::~GameSession()
{
}

int GameSession::getBoardSize()
{
	return boardSize;
}

void GameSession::createBoard(int squares, int snakes, int ladders)
{
	boardSize = squares;
	numOfSnakes = snakes;
	numOfLadders = ladders;
}

void GameSession::createSnakes()
{
	// Condition:
	// 1. key: tail, value: head
	// 2. tail > head
	for (unsigned int i = 0; i < numOfSnakes; i++)
	{
		int tail = rand() % (boardSize - 2) + 2; // from 2 to boardSize-1
		int head = rand() % (boardSize - 2) + 1; // from 1 to boardSize-2
		while (head >= tail || ladderMap.count(head) > 0) {
			head = rand() % (boardSize - 2) + 1; // if head >= tail, re-generate the value of head until it is smaller than tail
		}
		snakeMap[tail] = head;
	}
}

void GameSession::createLadders()
{
	// Condition:
	// 1. key: base, value: top
	// 2. top > base
	for (unsigned int i =0; i < numOfLadders; i++)
	{
		int top = rand() % (boardSize - 2) + 2; // from 2 to boardSize-1
		int base = rand() % (boardSize - 2) + 1; // from 1 to boardSize-2
		while (base >= top || snakeMap.count(base) > 0) {
			base = rand() % (boardSize - 2) + 1; // if base >= top, re-generate the value of base until it is smaller than top
		}
		ladderMap[base] = top;
	}
}

void GameSession::createPlayer(const std::string& name)
{
	playerVector.push_back(Player(name));
}

bool GameSession::wonBy(const Player& p)
{
	return p.getCurrentPos() >= boardSize;
}

bool GameSession::gotSnakeTail(const Player& p)
{
	return snakeMap.count(p.getCurrentPos()) != 0;
}

bool GameSession::gotLadderBase(const Player& p)
{
	return ladderMap.count(p.getCurrentPos()) != 0;
}

int GameSession::getNumOfPlayers()
{
	return playerVector.size();
}

int GameSession::throwDie()
{
	int die = rand()%6 + 1;

	return die;
}

std::pair<std::string, int> GameSession::play(Player& p)
{
	int steps = throwDie();
	p.move(steps);
	std::cout << p.getName() << " moves " << steps << " steps to square no. " << p.getCurrentPos() << std::endl;

	if (wonBy(p)) {
		return std::make_pair(p.getName(), 1);
	}

	if (gotSnakeTail(p)) {
		p.setCurrentPos(snakeMap[p.getCurrentPos()]);
		std::cout << "Alas! SNAKE\'s tail. Move back to square no. " << p.getCurrentPos() << std::endl;
	}
	else if (gotLadderBase(p)) {
		p.setCurrentPos(ladderMap[p.getCurrentPos()]);
		std::cout << "Hooray! LADDER! Move up to square no. " << p.getCurrentPos() << std::endl;
	}

	return std::make_pair(p.getName(), 0);
}

int GameSession::getUserInput() {
	int snakes = 0;
	while ((std::cin >> snakes).fail()) {
		std::cin.clear();
		std::string dump;
		std::cin >> dump;
		std::cout << "Invalid input. Please enter an integer: ";
	}
	return snakes;
}

void GameSession::start()
{
	std::string response = "y";
	int seqNo = 1;
	do
	{
		std::string pname;
		std::cout << "Enter Player " << seqNo++ << "\'s name: ";
		std::cin >> pname;
		if (pname.empty()) {
			pname = "Player" + seqNo;
		}
		createPlayer(pname);

		std::cout << "Enter another player? [y/n]: ";
		std::cin >> response;

	}
	while (response.compare("Y") == 0 || response.compare("y") == 0);

	std::cout << "No. of Snakes in the board: ";
	numOfSnakes = getUserInput();

	std::cout << "No. of Ladders in the board: ";
	numOfLadders = getUserInput();

	if (getNumOfPlayers() > 0)
	{
		createSnakes();
		createLadders();
		std::cout << std::endl << "GAME STARTS..." << std::endl;
		sleep(1);
	}
	else
	{
		std::cout << "Seems nobody is playing. Number of players must be greater than 0" << std::endl;
		return;
	}

	int turn = 0;
	while(true)
	{
		if (turn % getNumOfPlayers() == 0)
		{
			std::cout << std::endl;
			std::cout << "Turn no. " << (turn / getNumOfPlayers()) + 1 << std::endl;
		}

		std::pair<std::string, int> turnResult = play(playerVector[turn % getNumOfPlayers()]);
		if (turnResult.second == 1)
		{
			std::cout << turnResult.first << " is THE WINNER!" << std::endl;
			break;
		}

		turn++;
	}
}
