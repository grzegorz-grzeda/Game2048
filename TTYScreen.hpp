/*================================================================================================*/
/*
 * Screen.hpp
 *
 *  Created on: 28.10.2016
 *      Author: grzegorz
 */

/*================================================================================================*/
#ifndef TTYSCREEN_HPP_
#define TTYSCREEN_HPP_
/*================================================================================================*/
#include "AbstractScreen.hpp"
/*================================================================================================*/
class TTYScreen: public AbstractScreen {
public:
	TTYScreen(int fieldWidth = 5) :
			AbstractScreen(fieldWidth) {
	}
	~TTYScreen() {
	}
private:
	std::ostream& getWindowContext() {
		return std::cout;
	}

	void prepareWindowContext() {
			getWindowContext() << "\x1B[2J\x1B[H";
			getWindowContext().flush();
	}
	void releaseWindowContext() {
	}
};
/*================================================================================================*/
#endif /* TTYSCREEN_HPP_ */
/*================================================================================================*/
/*                                              EOF                                               */
/*================================================================================================*/
