#include "forwardDeclarations.h"
#include <windows.h> //for SetConsoleTextAttribute()
#include <cstdio> // for printf()
#include <iostream>
//it was necessary to move these functions here because of some
//name collisions between headers

//colors are bit-encoded with the first 4 bits referring to the background colour
//and the last 4 bits referring to the text colour (in the format intensity-red-green-blue).
const unsigned short lightGreyOnBlack = 0x7; //default
const unsigned short darkGreyOnBlack = 0x8;
const unsigned short whiteOnRed = 0xcf;
const unsigned short whiteOnBlue = 0x9f;

//change text and background colours of a tile based on its content
void setColours(const Board &board, int row, int col)
{
	if (board.doubleArray[row][col] == 'V')
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), whiteOnRed);
	else if (board.doubleArray[row][col] == 'H')
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), whiteOnBlue);
}

void toggleBooleans(const Board &board, int row, int column, bool &hBool, bool *vBool)
{
	if (board.doubleArray[row][column] == 'H')
		hBool = !hBool;
	else if (board.doubleArray[row][column] == 'V')
		vBool[column] = !vBool[column];
}

void printBoard(const Board &board)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), darkGreyOnBlack);
	//The following bool variables are toggled every time an H (or V) is found while drawing the board.
	//When they are true, it means that they have been toggled an even number of times,
	//which means that an even number of Hs (or Vs) have been found,
	//which means that a whole number of pieces has been found so far
	//(rememeber, one piece is made up of two Hs or two Vs).
	bool *interruptColourV = new bool[board.size]; //each bool variable keeps track of the Vs in one particular column.
	bool interruptColourH = true; //this bool variable keeps track of the Hs in each row.
	for (int count = 0; count < board.size; count++)
	{
		interruptColourV[count] = true;
	}
	//PRINT LETTERS ON TOP
	std::cout << std::endl;
	std::cout << "   ";
	char ascii = 65;	//ascii code for 'A'
	for (int colCount = 0; colCount < board.size; colCount++)
	{
		std::cout << "  " << ascii << " ";
		ascii++;
	}
	std::cout << std::endl;
	//PRINT TOP EDGE OF THE BOARD
	std::cout << "   " << static_cast<char>(218);
	for (int count = 0; count < board.size - 1; count++)
	{
		std::cout << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(194);
	}
	std::cout << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(191) << std::endl;
	//PRINT TOP ROW OF THE BOARD
	std::cout << " " << 1 << " " << static_cast<char>(179);
	for (int count = 0; count < board.size; count++)
	{
		toggleBooleans(board, 0, count, interruptColourH, interruptColourV);
		setColours(board, 0, count);
		std::cout << " " << board.doubleArray[0][count] << " ";
		if (interruptColourH) //the whole horizontal piece has been printed
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), darkGreyOnBlack);
			std::cout << static_cast<char>(179);
		}
		else //the remaining half of the horizontal piece has not been printed yet
			std::cout << " ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), darkGreyOnBlack);
	}
	std::cout << std::endl;
	//PRINT ALL THE REMAINING ROWS
	for (int rowCount = 1; rowCount < board.size; rowCount++)
	{
		//solid line
		std::cout << "   " << static_cast<char>(195);
		for (int colCount = 0; colCount < board.size - 1; colCount++)
		{
			if (!interruptColourV[colCount]) //the whole vertical piece has been printed
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), whiteOnRed);
				std::cout << "   ";
			}
			else //the remaining half of the vertical piece has not been printed yet
				std::cout << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), darkGreyOnBlack);
			std::cout << static_cast<char>(197);
		}
		if (!interruptColourV[board.size-1]) //the whole vertical piece has been printed
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), whiteOnRed);
			std::cout << "   ";
		}
		else //the remaining half of the vertical piece has not been printed yet
			std::cout << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), darkGreyOnBlack);
		std::cout << static_cast<char>(180) << std::endl;
		//row
		printf("%2d", rowCount + 1);
		std::cout << " " << static_cast<char>(179);
		for (int colCount = 0; colCount < board.size; colCount++)
		{
			toggleBooleans(board, rowCount, colCount, interruptColourH, interruptColourV);
			setColours(board, rowCount, colCount);
			std::cout << " " << board.doubleArray[rowCount][colCount] << " ";
			if (interruptColourH) //the whole horizontal piece has been printed
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), darkGreyOnBlack);
				std::cout << static_cast<char>(179);
			}
			else //the remaining half of the horizontal piece has not been printed yet
				std::cout << " ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), darkGreyOnBlack);
		}
		std::cout << std::endl;
	}
	//PRINT THE BOTTOM EDGE
	std::cout << "   " << static_cast<char>(192);
	for (int count = 0; count < board.size - 1; count++)
	{
		std::cout << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(193);
	}
	std::cout << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(217) << std::endl;
	delete[] interruptColourV;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), lightGreyOnBlack);
}
