/*================================================================================================*/
/*
 * Game.hpp
 *
 *  Created on: 03.11.2016
 *      Author: grzegorz
 */

/*================================================================================================*/
#ifndef GAME_HPP_
#define GAME_HPP_
/*================================================================================================*/
#include "Screen.hpp"
#include <cstdlib>
#include <cstdio>
#include <termios.h>
/*================================================================================================*/
class Game {
public:
	Game(int size = 4) :
			values(size, std::vector<int>(size, 0)), isOver(false), score(0), size(size) {
		sc = new Screen();
		srand(time(NULL));
		putNewNumber();
		putNewNumber();
		updateScreen();
	}
	bool isGameNotOver() {
		return !isOver;
	}
	void update() {
		if (move()) {
			if (!areAnyMovesLeft())
				isOver = true;
			else
				putNewNumber();
			updateScreen();
		}
	}
private:
	AbstractScreen *sc;
	std::vector<std::vector<int> > values;
	bool isOver;
	int score;
	int size;

	bool move() {
		char c = getKey();
		switch (c) {
			case 'w':
				moveUp();
				break;
			case 'a':
				moveLeft();
				break;
			case 's':
				moveDown();
				break;
			case 'd':
				moveRight();
				break;
			case 'q':
				exit(0);
				break;
			default:
				return false;
		}
		return true;
	}
	void moveUp() {
		slideToUp();
		coalesceToUp();
		slideToUp();
	}
	void moveDown() {
		slideToDown();
		coalesceToDown();
		slideToDown();
	}
	void moveRight() {
		slideToRight();
		coalesceToRight();
		slideToRight();
	}
	void moveLeft() {
		slideToLeft();
		coalesceToLeft();
		slideToLeft();
	}
	void updateScreen() {
		sc->draw(values, score, isOver);
	}
	void putNewNumber() {
		int cnt = 0;
		while (cnt < size * size) {
			int x = rand() % size;
			int y = rand() % size;
			if (isFieldEmpty(x, y)) {
				values[y][x] = generateNewNumber();
				break;
			}
			cnt++;
		}
	}
	int generateNewNumber() {
		int number = rand() % 100;

		if (number > 95)
			return 4;

		return 2;
	}
	bool areAnyMovesLeft() {
		if (isGameAreaFull()) {
			return areAnyPairs();
		} else
			return true;
	}
	bool isGameAreaFull() {
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				if (isFieldEmpty(i, j))
					return false;
		return true;
	}
	bool areAnyPairs() {
		for (int y = 0; y < size; y++) {
			for (int x = 0; x < size; x++) {
				int current = values.at(y).at(x);
				if (x > 0)
					if (current == values.at(y).at(x - 1))
						return true;
				if (x < size - 1)
					if (current == values.at(y).at(x + 1))
						return true;
				if (y > 0)
					if (current == values.at(y - 1).at(x))
						return true;
				if (y < size - 1)
					if (current == values.at(y + 1).at(x))
						return true;
			}
		}
		return false;
	}
	bool isFieldEmpty(int x, int y) {
		return values.at(y).at(x) == 0;
	}
	char getKey() {
		termios Old, New;
		tcgetattr(0, &Old);
		New = Old;
		New.c_lflag &= ~ICANON;
		New.c_lflag &= ~ECHO;
		tcsetattr(0, TCSANOW, &New);

		char c = getchar();

		tcsetattr(0, TCSANOW, &Old);

		return c;
	}

	void slideToUp() {
		for (int x = 0; x < size; x++) {
			for (int y = 0; y < size - 1; y++) {
				if (isFieldEmpty(x, y)) {
					int cnt = 0;
					while (1) {
						for (int i = y; i < size - 1; i++) {
							values.at(i).at(x) = values.at(i + 1).at(x);
							values.at(i + 1).at(x) = 0;
						}
						values.at(size - 1).at(x) = 0;
						if (!isFieldEmpty(x, y))
							break;

						cnt++;
						if (cnt > size * size)
							break;
					}
				}
			}
		}
	}

	void coalesceToUp() {
		for (int x = 0; x < size; x++) {
			for (int y = 0; y < size - 1; y++) {
				if (isFieldEmpty(x, y))
					continue;

				if (values.at(y).at(x) == values.at(y + 1).at(x)) {
					values.at(y).at(x) *= 2;
					values.at(y + 1).at(x) = 0;
					score += values.at(y).at(x);
				}
			}
		}
	}

	void slideToDown() {
		for (int x = 0; x < size; x++) {
			for (int y = size - 1; y > 0; y--) {
				if (isFieldEmpty(x, y)) {
					int cnt = 0;
					while (1) {
						for (int i = y; i > 0; i--) {
							values.at(i).at(x) = values.at(i - 1).at(x);
							values.at(i - 1).at(x) = 0;
						}
						values.at(0).at(x) = 0;
						if (!isFieldEmpty(x, y))
							break;

						cnt++;
						if (cnt > size * size)
							break;
					}
				}
			}
		}
	}

	void coalesceToDown() {
		for (int x = 0; x < size; x++) {
			for (int y = size - 1; y > 0; y--) {
				if (isFieldEmpty(x, y))
					continue;

				if (values.at(y).at(x) == values.at(y - 1).at(x)) {
					values.at(y).at(x) *= 2;
					values.at(y - 1).at(x) = 0;
					score += values.at(y).at(x);
				}
			}
		}
	}

	void slideToRight() {
		for (int x = size - 1; x > 0; x--) {
			for (int y = 0; y < size; y++) {
				if (isFieldEmpty(x, y)) {
					int cnt = 0;
					while (1) {
						for (int i = x; i > 0; i--) {
							values.at(y).at(i) = values.at(y).at(i - 1);
							values.at(y).at(i - 1) = 0;
						}
						values.at(y).at(0) = 0;
						if (!isFieldEmpty(x, y))
							break;

						cnt++;
						if (cnt > size * size)
							break;
					}
				}
			}
		}
	}

	void coalesceToRight() {
		for (int x = size - 1; x > 0; x--) {
			for (int y = 0; y < size; y++) {
				if (isFieldEmpty(x, y))
					continue;

				if (values.at(y).at(x) == values.at(y).at(x - 1)) {
					values.at(y).at(x) *= 2;
					values.at(y).at(x - 1) = 0;
					score += values.at(y).at(x);
				}
			}
		}
	}

	void slideToLeft() {
		for (int x = 0; x < size - 1; x++) {
			for (int y = 0; y < size; y++) {
				if (isFieldEmpty(x, y)) {
					int cnt = 0;
					while (1) {
						for (int i = x; i < size - 1; i++) {
							values.at(y).at(i) = values.at(y).at(i + 1);
							values.at(y).at(i + 1) = 0;
						}
						values.at(y).at(size - 1) = 0;
						if (!isFieldEmpty(x, y))
							break;

						cnt++;
						if (cnt > size * size)
							break;
					}
				}
			}
		}
	}

	void coalesceToLeft() {
		for (int x = 0; x < size - 1; x++) {
			for (int y = 0; y < size; y++) {
				if (isFieldEmpty(x, y))
					continue;

				if (values.at(y).at(x) == values.at(y).at(x + 1)) {
					values.at(y).at(x) *= 2;
					values.at(y).at(x + 1) = 0;
					score += values.at(y).at(x);
				}
			}
		}
	}
};
/*================================================================================================*/
#endif /* GAME_HPP_ */
/*================================================================================================*/
/*                                              EOF                                               */
/*================================================================================================*/
