/*================================================================================================*/
/*
 * KeyboardInput.hpp
 *
 *  Created on: 03.11.2016
 *      Author: grzegorz
 */

/*================================================================================================*/
#ifndef KEYBOARDINPUT_HPP_
#define KEYBOARDINPUT_HPP_
/*================================================================================================*/
#include "AbstractPlayer.hpp"
#include <termios.h>
#include <cstdio>
/*================================================================================================*/
class KeyboardInput: public AbstractPlayer {
public:
	KeyboardInput() {

	}

	PlayerInput getInput() {
		termios Old, New;
		tcgetattr(0, &Old);
		New = Old;
		New.c_lflag &= ~ICANON;
		New.c_lflag &= ~ECHO;
		tcsetattr(0, TCSANOW, &New);

		char c = getchar();

		tcsetattr(0, TCSANOW, &Old);

		switch (c) {
			case 'w':
				return UP;
			case 'a':
				return LEFT;
			case 's':
				return DOWN;
			case 'd':
				return RIGHT;
			case 'q':
				return EXIT;
			case 'b':
				return UNDO;
			default:
				return INVALID;
		}
	}
};
/*================================================================================================*/
#endif /* KEYBOARDINPUT_HPP_ */
/*================================================================================================*/
/*                                              EOF                                               */
/*================================================================================================*/
