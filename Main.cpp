/*
 * Main.cpp
 *
 *  Created on: Jan 15, 2014
 *      Author: dmartana
 */

#include<iostream>
#include<cstdlib>
#include "Square.h"
#include "Player.h"
#include "GameSession.h"


// TODO:
// 1. Select auto or manual mode:
//		a. auto: players move one after another automatically until someon wins
// 		b. manual: players move and each requires a user input to proceed
// 2. 'Bounce back' if the distance required is smaller than the value of thrown die.

// NOTE:
// The class Square is not used, at least it is not necessary for now.

int main()
{
	GameSession game;

	std::string response = "y";
	int seqNo = 1;
	do {
		std::string pname;
		std::cout << "Enter Player " << seqNo++ << "\'s name: ";
		std::cin >> pname;
		std::cout << std::endl;
		if (pname.empty()) {
			pname = "Player" + seqNo;
		}
		game.createPlayer(pname);

		std::cout << "Type \"Y/y\" and press ENTER to add another player, " << std::endl;
		std::cout << "or any other key to proceed to game: " << std::endl;
		std::cout << "Enter another player? " << std::endl;
		std::cin >> response;
		std::cout << std::endl;

	}
	while (response.compare("Y") == 0 || response.compare("y") == 0);

	std::cout << "No. of Snakes in the board: ";
	int snakes = 0;
	std::cin >> snakes;
	game.setNumOfSnakes(snakes);

	std::cout << "No. of Ladders in the board: ";
	int ladders = 0;
	std::cin >> ladders;
	game.setNumOfLadder(ladders);

	if (game.getNumOfPlayers() > 0) {
		game.createSnakes();
		game.createLadders();
	}
	else {
		std::cout << "Seems nobody is playing. Number of players must be greater than 0" << std::endl;
		return 0;
	}

	int turn = 0;
	while(true) {
		turn++;
		if (turn % game.getNumOfPlayers() == 1) {
			std::cout << std::endl;
			std::cout << "Turn no. " << turn << std::endl;
		}

		std::pair<std::string, int> turnResult = game.play();
		if (turnResult.second == 1)
		{
			std::cout << turnResult.first << " is THE WINNER!" << std::endl;
			return 0;
		}
	}

	return 0;
}


