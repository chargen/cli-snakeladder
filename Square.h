/*
 * Square.h
 *
 *  Created on: Jan 15, 2014
 *      Author: dmartana
 */

#ifndef SQUARE_H_
#define SQUARE_H_

class Square {
public:
	Square(int num);
	virtual ~Square();

	int getNum();

private:
	int num;
};

#endif /* SQUARE_H_ */
