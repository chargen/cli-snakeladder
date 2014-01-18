/*
 * Player.cpp
 *
 *  Created on: Jan 15, 2014
 *      Author: dmartana
 */

#include<iostream>
#include<cstdlib>
#include "time.h"
#include "Player.h"

Player::Player(const std::string& name) : currentPos(0)
{
	this->name = name;
//	srand(time(NULL));
}

Player::~Player()
{
	// TODO Auto-generated destructor stub
}

unsigned int Player::getCurrentPos() const
{
	return currentPos;
}

void Player::setCurrentPos(int newPos)
{
	currentPos = newPos;
}

int Player::move(int steps)
{
	currentPos += steps;
	return currentPos;
}

std::string Player::getName()
{
	return name;
}
