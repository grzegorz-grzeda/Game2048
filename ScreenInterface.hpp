/*================================================================================================*/
/*
 * ScreenInterface.hpp
 *
 *  Created on: 28.10.2016
 *      Author: grzegorz
 */

/*================================================================================================*/
#ifndef SCREENINTERFACE_HPP_
#define SCREENINTERFACE_HPP_
/*================================================================================================*/
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>
/*================================================================================================*/
class AbstractScreen {
public:
	AbstractScreen(int fieldWidth) :
			fieldWidth(fieldWidth) {

	}
	void draw(std::vector<std::vector<int> > values, int gameScore, bool isGameOver) {
		prepareWindowContext();
		getWindowContext() << makeStatusLine(gameScore, isGameOver) << std::endl << std::endl;

		for (std::vector<std::vector<int> >::iterator row = values.begin(); row < values.end();
		      ++row) {
			getWindowContext() << makeDivisionLine(row->size()) << std::endl;
			getWindowContext() << makeOneLine(*row) << std::endl;
		}
		getWindowContext() << makeDivisionLine(values.at(0).size()) << std::endl;
		releaseWindowContext();
	}
	virtual ~AbstractScreen() {

	}
private:
	virtual std::ostream& getWindowContext() = 0;
	virtual void prepareWindowContext() = 0;
	virtual void releaseWindowContext() = 0;
	std::string getNumberString(int number) {
		std::string fixTable[] = {
		      "",
		      "k",
		      "M",
		      "G",
		      "T," "P" };
		std::string postfix = fixTable[0];

		for (unsigned int i = 0, divisor = 1; i < (sizeof(fixTable) / sizeof(std::string)); i++) {
			if (number / divisor) {
				postfix = fixTable[i];
				number /= divisor;
				divisor *= 1024;
			} else {
				break;
			}
		}
		std::stringstream ss;
		ss << number << postfix;
		return ss.str();
	}
	std::string makeOneLine(std::vector<int> numbers) {
		std::stringstream ss;
		ss << "|";
		for (std::vector<int>::iterator it = numbers.begin(); it < numbers.end(); ++it) {
			if (*it == 0) {
				ss << std::setw(fieldWidth) << " ";
			} else {
				ss << std::setw(fieldWidth) << getNumberString(*it);
			}
			ss << "|";
		}
		return ss.str();
	}
	std::string makeDivisionLine(int numberOfFields) {
		std::stringstream line;
		line << "+";

		for (int i = 0; i < numberOfFields; i++) {
			line << std::setw(fieldWidth) << std::setfill('-') << "-";
			line << "+";
		}
		return line.str();
	}
	std::string makeStatusLine(int score, bool gameOver) {
		std::stringstream status;
		status << "Score:\t" << score;
		if (gameOver)
			status << "\tGAME OVER!";
		return status.str();
	}
	int fieldWidth;
};
/*================================================================================================*/
#endif /* SCREENINTERFACE_HPP_ */
/*================================================================================================*/
/*                                              EOF                                               */
/*================================================================================================*/
