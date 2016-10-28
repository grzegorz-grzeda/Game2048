/*================================================================================================*/
/*
 * main.cpp
 *
 *  Created on: 28.10.2016
 *      Author: grzegorz
 */
/*================================================================================================*/
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
/*================================================================================================*/
using namespace std;
/*================================================================================================*/
string getNumberString(int number) {
	string fixTable[] = {
	      "",
	      "k",
	      "M",
	      "G",
	      "T," "P" };
	string postfix = fixTable[0];

	for (unsigned int i = 0, divisor = 1; i < (sizeof(fixTable) / sizeof(string)); i++) {
		if (number / divisor) {
			postfix = fixTable[i];
			number /= divisor;
			divisor *= 1024;
		} else {
			break;
		}
	}
	stringstream ss;
	ss << number << postfix;
	return ss.str();
}
/*================================================================================================*/
string makeOneLine(vector<int> numbers) {
	stringstream ss;
	ss << "|";
	for (vector<int>::iterator it = numbers.begin(); it < numbers.end(); ++it) {
		if (*it == 0) {
			ss << setw(5) << " ";
			ss << "|";
		} else {
			ss << setw(5) << getNumberString(*it);
			ss << "|";
		}
	}
	return ss.str();
}
/*================================================================================================*/
string makeDivisionLine(int numberOfFields) {
	stringstream line;
	line << "+";

	for (int i = 0; i < numberOfFields; i++) {
		line << setw(6) << setfill('-') << "+";
	}
	return line.str();
}
/*================================================================================================*/
string makeStatusLine(int score, bool gameOver) {
	stringstream status;
	status << "Score:\t" << score;
	if (gameOver)
		status << "\tGAME OVER!";
	return status.str();
}
/*================================================================================================*/
ostream& outputStream() {
	return cout;
}
/*================================================================================================*/
void drawScreen(vector<vector<int> > numbers, int score, bool gameOver) {
	if (outputStream() == cout) {
		outputStream() << "\x1B[2J\x1B[H";
		outputStream().flush();
	}
	outputStream() << makeStatusLine(score, gameOver) << endl << endl;

	for (vector<vector<int> >::iterator row = numbers.begin(); row < numbers.end(); ++row) {
		outputStream() << makeDivisionLine(row->size()) << endl;
		outputStream() << makeOneLine(*row) << endl;
	}
	outputStream() << makeDivisionLine(numbers.at(0).size()) << endl;
}
/*================================================================================================*/
int main() {
	vector<vector<int> > rows;
	vector<int> row;
	row.push_back(16);
	row.push_back(32);
	row.push_back(0);
	row.push_back(1024);
	row.push_back(512);

	rows.push_back(row);
	rows.push_back(row);
	rows.push_back(row);
	rows.push_back(row);
	rows.push_back(row);
	drawScreen(rows, 10, false);
	return 0;
}
/*================================================================================================*/
/*                                              EOF                                               */
/*================================================================================================*/
