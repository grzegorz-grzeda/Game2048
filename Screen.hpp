/*================================================================================================*/
/*
 * Screen.hpp
 *
 *  Created on: 28.10.2016
 *      Author: grzegorz
 */

/*================================================================================================*/
#ifndef SCREEN_HPP_
#define SCREEN_HPP_
/*================================================================================================*/

#include "AbstractScreen.hpp"
/*================================================================================================*/
class Screen: public AbstractScreen {
public:
	Screen(int fieldWidth = 5, std::string outputDeviceName = "") :
			AbstractScreen(fieldWidth), outputDeviceName(outputDeviceName) {
	}
	~Screen() {
	}
private:
	std::ostream& getWindowContext() {
		if (outputDevice.is_open()) {
			return outputDevice;
		}
		return std::cout;
	}

	void prepareWindowContext() {
		if (!outputDeviceName.empty()) {
			outputDevice.open(outputDeviceName.c_str(), std::ofstream::out);
		}
		if (getWindowContext() == std::cout) {
			getWindowContext() << "\x1B[2J\x1B[H";
			getWindowContext().flush();
		}
	}
	void releaseWindowContext() {
		if (outputDevice.is_open())
			outputDevice.close();
	}
	std::string outputDeviceName;
	std::ofstream outputDevice;
};
/*================================================================================================*/
#endif /* SCREEN_HPP_ */
/*================================================================================================*/
/*                                              EOF                                               */
/*================================================================================================*/
