/*
 * Player.h
 *
 *  Created on: Jan 15, 2014
 *      Author: dmartana
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include<string>

class Player {
public:
	Player(const std::string& name);
	virtual ~Player();

	int move(int steps);
	unsigned int getCurrentPos() const;
	void setCurrentPos(int newPos);
	std::string getName();

private:
	unsigned int currentPos;
	std::string name;
};

#endif /* PLAYER_H_ */
