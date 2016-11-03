/*================================================================================================*/
/*
 * AbstractGameField.hpp
 *
 *  Created on: 03.11.2016
 *      Author: grzegorz
 */

/*================================================================================================*/
#ifndef ABSTRACTGAMEFIELD_HPP_
#define ABSTRACTGAMEFIELD_HPP_
/*================================================================================================*/
class GameFieldVector {
public:
	GameFieldVector(int size) :
			rd(0), wr(0), size(size) {
		numbers = new int[size];
	}
	GameFieldVector(const GameFieldVector &src) :
			rd(src.rd), wr(src.wr), size(src.size) {
		if (this != &src) {
			numbers = new int[src.size];
			for (int i = 0; i < size; i++)
				numbers[i] = src.numbers[i];
		}
	}
	~GameFieldVector() {
		delete[] numbers;
	}
	int getNext() {
		return numbers[rd++];
	}
	int getSize() {
		return size;
	}
	void putNext(int val) {
		numbers[wr++] = val;
	}
private:
	int *numbers, rd, wr, size;
};
/*================================================================================================*/
class AbstractGameField {
public:
	AbstractGameField(int size) :
			size(size) {
	}
	virtual ~AbstractGameField() {
	}
	virtual int getSize() = 0;
	virtual int get(int x, int y) = 0;
	virtual void set(int x, int y, int value) = 0;
	bool isEmpty(int x, int y) {
		return get(x, y) == 0;
	}
	GameFieldVector getRow(int y) {
		GameFieldVector row(size);
		for (int i = 0; i < size; i++)
			row.putNext(get(i, y));
		return row;
	}
	GameFieldVector getColumn(int x) {
		GameFieldVector row(size);
		for (int i = 0; i < size; i++)
			row.putNext(get(x, i));
		return row;
	}
	void update(AbstractGameField*src) {
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				set(i, j, src->get(i, j));
	}
	bool isDifferentThan(AbstractGameField*src) {
		return !isTheSameThan(src);
	}
	bool isTheSameThan(AbstractGameField*src) {
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				if (get(i, j) != src->get(i, j))
					return false;
		return true;
	}
	void trim() {
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				if (get(i, j) < 0)
					set(i, j, 0);
	}
protected:
	int size;
};
/*================================================================================================*/
/*================================================================================================*/
#endif /* ABSTRACTGAMEFIELD_HPP_ */
/*================================================================================================*/
/*                                              EOF                                               */
/*================================================================================================*/
