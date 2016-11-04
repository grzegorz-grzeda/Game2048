/*================================================================================================*/
/*
 * DefaultRandomizer.hpp
 *
 *  Created on: 04.11.2016
 *      Author: grzegorz
 */

/*================================================================================================*/
#ifndef DEFAULTRANDOMIZER_HPP_
#define DEFAULTRANDOMIZER_HPP_
/*================================================================================================*/
#include "AbstractRandomizer.hpp"
#include <cstdlib>
#include <ctime>
/*================================================================================================*/
class DefaultRandomizer: public AbstractRandomizer {
public:
	DefaultRandomizer(int rowSize) :
			size(rowSize) {
		srand(time(NULL));
	}
	GameCell randomizeCell() {
		return GameCell(randomizeDirection(), randomizeDirection(), randomizeValue());
	}

private:
	int size;
	int randomizeDirection() {
		return rand() % size;
	}
	int randomizeValue() {
		int number = rand() % 100;

		if (number > 95)
			return 4;

		return 2;
	}
};
/*================================================================================================*/
#endif /* DEFAULTRANDOMIZER_HPP_ */
/*================================================================================================*/
/*                                              EOF                                               */
/*================================================================================================*/
