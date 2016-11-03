/*================================================================================================*/
/*
 * DefaultGameField.hpp
 *
 *  Created on: 03.11.2016
 *      Author: grzegorz
 */

/*================================================================================================*/
#ifndef DEFAULTGAMEFIELD_HPP_
#define DEFAULTGAMEFIELD_HPP_
/*================================================================================================*/
#include "AbstractGameField.hpp"
#include <vector>
/*================================================================================================*/
class DefaultGameField: public AbstractGameField {
public:
	DefaultGameField(int size) :
			AbstractGameField(size), values(size, std::vector<int>(size, 0)) {

	}
	int getSize() {
		return (int) values.size();
	}
	int get(int x, int y) {
		if ((x < 0) || (x >= size) || (y < 0) || (y >= size))
			return -1;
		return values.at(y).at(x);
	}
	void set(int x, int y, int value) {
		if ((x < 0) || (x >= size) || (y < 0) || (y >= size))
			return;
		values.at(y).at(x) = value;
	}
private:
	std::vector<std::vector<int> > values;
};
/*================================================================================================*/
#endif /* DEFAULTGAMEFIELD_HPP_ */
/*================================================================================================*/
/*                                              EOF                                               */
/*================================================================================================*/
