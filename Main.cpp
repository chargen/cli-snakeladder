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

	game.start();

	return 0;
}


