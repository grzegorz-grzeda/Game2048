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
#include "DefaultGameField.hpp"
#include "KeyboardInput.hpp"
#include <cstdlib>
#include <cstdio>
/*================================================================================================*/
class Game {
public:
	Game(int size = 4) :
			isOver(false), score(0), historyScore(0), size(size) {
		values = new DefaultGameField(size);
		history = new DefaultGameField(size);
		input = new KeyboardInput();
		sc = new Screen();
		srand(time(NULL));
		putNewNumber();
		putNewNumber();
		history->update(values);
		updateScreen();
	}
	bool isGameNotOver() {
		return !isOver;
	}
	void update() {
		if (move()) {
			if (history->isDifferentThan(values)) {
				putNewNumber();
				history->update(values);
				historyScore = score;
			}
			if (!areAnyMovesLeft())
				isOver = true;
			updateScreen();
		}
	}
private:
	AbstractScreen *sc;
	AbstractGameField *values, *history;
	AbstractPlayer *input;
	bool isOver;
	int score, historyScore;
	int size;

	void putNewNumber() {
		if (!isGameAreaFull())
			while (1) {
				int x = generateNewPosition();
				int y = generateNewPosition();
				if (values->isEmpty(x, y)) {
					values->set(x, y, generateNewNumber());
					break;
				}
			}
	}
	void updateScreen() {
		sc->draw(values, score, isOver);
	}
	bool move() {
		bool result = true;
		switch (input->getInput()) {
			case UP:
				moveUp();
				break;
			case LEFT:
				moveLeft();
				break;
			case DOWN:
				moveDown();
				break;
			case RIGHT:
				moveRight();
				break;
			case UNDO:
				revert();
				break;
			case EXIT:
				exit(0);
				break;
			default:
				result = false;
		}

		values->trim();
		return result;
	}
	void moveUp() {
		slide(0, size, 1, 0, size - 1, 1, false);
		coalesce(0, size, 1, 0, size - 1, 1, false);
		slide(0, size, 1, 0, size - 1, 1, false);
	}
	void moveDown() {
		slide(0, size, 1, size - 1, 0, -1, false);
		coalesce(0, size, 1, size - 1, 0, -1, false);
		slide(0, size, 1, size - 1, 0, -1, false);
	}
	void moveRight() {
		slide(size - 1, 0, -1, 0, size, 1, true);
		coalesce(size - 1, 0, -1, 0, size, 1, true);
		slide(size - 1, 0, -1, 0, size, 1, true);
	}
	void moveLeft() {
		slide(0, size - 1, 1, 0, size, 1, true);
		coalesce(0, size - 1, 1, 0, size, 1, true);
		slide(0, size - 1, 1, 0, size, 1, true);
	}
	void slide(int xST, int xSP, int xSTEP, int yST, int ySP, int ySTEP, bool isX) {
		for (int x = xST; x != xSP; x += xSTEP) {
			for (int y = yST; y != ySP; y += ySTEP) {
				if (values->isEmpty(x, y)) {
					int cnt = 0;
					while (1) {
						if (isX) {
							for (int i = x; i != xSP; i += xSTEP) {
								values->set(i, y, values->get(i + xSTEP, y));
								values->set(i + xSTEP, y, 0);
							}
							values->set(xSP, y, 0);
						} else {
							for (int i = y; i != ySP; i += ySTEP) {
								values->set(x, i, values->get(x, i + ySTEP));
								values->set(x, i + ySTEP, 0);
							}
							values->set(x, ySP, 0);
						}
						if (!(values->isEmpty(x, y)))
							break;

						cnt++;
						if (cnt > size * size)
							break;
					}
				}
			}
		}
	}


	void coalesce(int xST, int xSP, int xD, int yST, int ySP, int yD, bool isX) {
		int xd = isX ? xD : 0;
		int yd = isX ? 0 : yD;

		for (int x = xST; x != xSP; x += xD) {
			for (int y = yST; y != ySP; y += yD) {
				if (values->isEmpty(x, y))
					continue;

				int c = values->get(x, y);
				int n = values->get(x + xd, y + yd);
				if (c == n) {
					values->set(x, y, c * 2);
					values->set(x + xd, y + yd, 0);
					score += c;
				}
			}
		}
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
				if (values->isEmpty(i, j))
					return false;
		return true;
	}
	bool areAnyPairs() {
		for (int y = 0; y < size; y++) {
			for (int x = 0; x < size; x++) {
				int c = values->get(x, y);
				int u = values->get(x, y + 1);
				int d = values->get(x, y - 1);
				int r = values->get(x + 1, y);
				int l = values->get(x - 1, y);

				if ((c == u) || (c == d) || (c == l) || (c == r))
					return true;
			}
		}
		return false;
	}
	void revert() {
		score = historyScore;
		values->update(history);
	}

	int generateNewNumber() {
		int number = rand() % 100;

		if (number > 95)
			return 4;

		return 2;
	}

	int generateNewPosition() {
		return rand() % size;
	}
};
/*================================================================================================*/
#endif /* GAME_HPP_ */
/*================================================================================================*/
/*                                              EOF                                               */
/*================================================================================================*/
