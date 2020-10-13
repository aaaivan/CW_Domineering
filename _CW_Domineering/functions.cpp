#include "forwardDeclarations.h"
#include <limits> // for numeric_limits
#include <cctype> // for toupper()
#include <cstdlib> // for std::rand() and std::srand()
#include <fstream>
#include <string>
#include <iostream>

//take a char (n=new game, l=load game, q=quit) from player and return it.
char mainMenu()
{
	while (true)
	{
		std::cout << "\nSelect one: new game (n), load game (l), quit(q): ";
		std::string tempStr{};
		char input{};
		std::cin >> tempStr;
		input = toupper(tempStr[0]);
		//input vaidation
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //remove any residual input in the buffer
		if (tempStr.length() != 1)
			std::cout << "Invalid input. Try again." << std::endl;
		else if (input == 'N' || input == 'L' || input == 'Q')
			return input;
		else
			std::cout << "Invalid input. Try again." << std::endl;
	}
}

//take a char (n=next turn, s=save, l=load game, q=quit) from player and return it.
char inGameMenu()
{
	while (true)
	{
		std::cout << "\nSelect one: next turn (n), save and quit current game (s), load game (l), quit current game(q): ";
		std::string tempStr{};
		char input{};
		std::cin >> tempStr;
		input = toupper(tempStr[0]);
		//input validation
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //remove any residual input in the buffer
		if (tempStr.length() != 1)
		{
			std::cout << "Invalid input. Try again." << std::endl;
		}
		else if (input == 'N' || input == 'S' || input == 'L' || input == 'Q')
			return input;
		else
			std::cout << "Invalid input. Try again." << std::endl;
	}
}

//take a char (r=retry, s=continue game, q=quit) from player and return it.
char gameNotSavedOrLoadedMenu()
{
	while (true)
	{
		std::cout << "\nSelect one: retry (r), continue current game (c), quit current game(q): ";
		std::string tempStr{};
		char input{};
		std::cin >> tempStr;
		input = toupper(tempStr[0]);
		//input validation
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //remove any residual input in the buffer
		if (tempStr.length() != 1)
		{
			std::cout << "Invalid input. Try again." << std::endl;
		}
		else if (input == 'R' || input == 'C' || input == 'Q')
			return input;
		else
			std::cout << "Invalid input. Try again." << std::endl;
	}
}

//get name from player and return it as soon as it is different from the argument.
std::string askPlayerName(std::string opponentName)
{
	static int id = 1;
	std::string name;
	std::cout << "\nPlayer " << id << ", enter your name: ";
	do
	{
		std::cin>> name;
		if (name == opponentName) //the players must have different names
			std::cout << "Please select a different name: " ;
	} while (name == opponentName);
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //remove any residual input in the buffer
	std::cout << std::endl;
	id = id % 2 + 1;
	return name;
}

//ask the user what type of pieces they want to use. Return true if the choise is the horizontal ones.
bool usesHorizontalPieces(std::string name)
{
	std::cout << name << ", what type of piece do you want to use?"<< std::endl;
	while (true)
	{
		std::cout << "Pick horizontal (h), vertical(v), or random(r): " ;
		char input{};
		std::string tempStr{};
		std::cin >> tempStr;
		input = toupper(tempStr[0]);
		//input validation
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (tempStr.length() != 1)
			std::cout << "Invalid input. Try again." << std::endl;
		else if (input == 'H') 
			return true;
		else if (input == 'V') 
			return false;
		else if (input == 'R') 
			return std::rand() % 2; //return 0 or 1 randomly
		else 
			std::cout << "Invalid input. Try again." << std::endl;
	}
}

//ask the board size and return it as soon as it is >=2 and <=15.
int askBoardSize()
{
	int size{};
	while (true)
	{
		std::cout << "How many tiles long should the board be? Enter an integer between 2 and 15: ";
		std::cin >> size;
		//input validation
		if (std::cin.fail())	//if the extraction fails, clear th ebuffer and print error message
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Try again."<<std::endl;
		}
		else if (size < 2 || size > 15)	//if size is not between 2 and 15, print erroe message
		{
			std::cout << "Your input is out of range. Try again." << std::endl;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //remove any residual input in the buffer
		}
		else
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //remove any residual input in the buffer
			return size;
		}
	}
}

//create a 2d array of chars all equal to whitespaces.
char** createEmptyBoard(int size)
{
	//dynamically allocate a 2d array with dimentions [size x sixe]
	char **boardArray = new char*[size];	//array of pointers to char.
	for (int count = 0; count < size; count++)
	{
		boardArray[count] = new char[size];	//array of chars.
	}
	//fill the 2d array with whitespace characaters
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			boardArray[row][col] = ' ';
		}
	}
	return boardArray;
}

//check if a player can place a new piece.
bool canPlaceNewPiece(const Board &board,  const Player &p)
{
	if (p.horizontalPiece) //player plays with horizontal pieces
	{
		for (int row = 0; row < board.size; row++)
		{
			for (int col = 0; col < board.size-1; col++)
			{
				if (board.doubleArray[row][col]== ' ' && board.doubleArray[row][col + 1]==' ')	//check if there are two adjacent
					return true;																//empty tiles on the same row
			}
		}
	}
	else //player plays with vertical pieces
	{
		for (int col = 0; col < board.size; col++)
		{
			for (int row = 0; row < board.size - 1; row++)
			{
				if (board.doubleArray[row][col] == ' ' && board.doubleArray[row+1][col] == ' ') //check if there are two adjacent
					return true;																//empty tiles on the same column
			}
		}
	}
	return false;
}

//ask for the number of the row where to place the new piece.
int getPlayerInputRow(int size)
{
	while (true)
	{
		int rowNum{};
		std::cout << "Enter the number for the row: ";
		std::cin >> rowNum;
		//input validation
		if (std::cin.fail())	//if the extraction fails, clear the buffer and print error message
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Try again." << std::endl;
		}
		else if (rowNum >= 1 && rowNum <= size)	//if rowNum is in range
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //remove any residual input in the buffer
			return rowNum - 1;
		}
		else
		{
			std::cout << "Your input is out of range. Try again." << std::endl;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //remove any residual input in the buffer
		}
	}

}

//ask for the letter of the column where to place the new piece.
int getPlayerInputCol(int size)
{
	while (true)
	{
		std::cout << "Enter the letter for the column: ";
		std::string input{};
		char columnLetter{};
		std::cin >> input;
		columnLetter = toupper(input[0]);
		//input validation
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //remove any residual input in the buffer
		if (input.length() != 1)
		{
			std::cout << "Invalid input. Try again." << std::endl;
		}
		else if (columnLetter >= 65 && columnLetter < 65 + size)
		{
			return columnLetter - 65;
		}
		else if (columnLetter >= 65 + size && columnLetter < 91)
		{
			std::cout << "Your input is out of range. Try again." << std::endl;
		}
		else
		{
			std::cout << "Invalid input. Try again." << std::endl;
		}
	}
}

//add a piece to the board at the coordinates specified by the player
//if there is enough room. If not keep asking for new coordinates.
void placeNewPiece(Board &board, const Player &p)
{
	std::cout << p.name << ", place a " << (p.horizontalPiece ? "HORIZONTAL" : "VERTICAL") << " piece on the board." << std::endl;
	std::cout << "Specify the coordinates of the tile where the " <<
		(p.horizontalPiece ? "left" : "top") << " half of your piece will sit." << std::endl;
	while (true)
	{
		int columnIndex{ getPlayerInputCol(board.size) }; //get column coordinate
		int rowIndex{ getPlayerInputRow(board.size) }; //get row coordinate

		if (p.horizontalPiece) //player uses horizontal pieces
		{
			if (columnIndex >= board.size - 1) //horizontal piece cannot go on the last column
			{
				std::cout << "Your piece will not fit there. Pick another tile."<<std::endl;
			}
			else if (board.doubleArray[rowIndex][columnIndex]==' ' && board.doubleArray[rowIndex][columnIndex+1] == ' ')
			{ //if the tile specified by the user and the one on its right are empty, put the piece there
				board.doubleArray[rowIndex][columnIndex] = 'H';
				board.doubleArray[rowIndex][columnIndex + 1] = 'H';
				return;
			}
			else
			{
				std::cout << "Your piece will not fit there. Pick another tile." << std::endl;
			}
		}
		else //player uses vertical pieces
		{
			if (rowIndex >= board.size - 1) //vertical piece cannot go on the last row
			{
				std::cout << "Your piece will not fit there. Pick another tile." << std::endl;
			}
			else if (board.doubleArray[rowIndex][columnIndex] == ' ' and board.doubleArray[rowIndex + 1][columnIndex] == ' ')
			{ //if the tile specified by the user and the one below are empty, put the piece there
				board.doubleArray[rowIndex][columnIndex] = 'V';
				board.doubleArray[rowIndex + 1][columnIndex] = 'V';
				return;
			}
			else
			{
				std::cout << "Your piece will not fit there. Pick another tile." << std::endl;
			}
		}
	}
}

//save the game on a file. Return false.
bool saveGame(const Board &board, const Player &p1, const Player &p2)
{
	std::cout << "Specify the name of the file on which your game will be saved: ";
	std::string filename{};
	std::getline(std::cin, filename);
	std::ofstream outFile(filename);
	if (!outFile.is_open())
	{
		std::cout << "\""<< filename << "\" could not be opened for writing. Try again." << std::endl;
		return false;
	}
	//players info
	outFile << "H:" << (p1.horizontalPiece ? p1.name : p2.name) << std::endl;
	outFile << "V:" << (p1.horizontalPiece ? p2.name : p1.name) << std::endl;
	//game info
	for (int row = 0; row < board.size; row++)
	{
		for (int col = 0; col < board.size; col++)
		{
			outFile << (board.doubleArray[row][col] == ' ' ? '-' : board.doubleArray[row][col]);
		}
		outFile << std::endl;
	}
	return true;
}

//get the name of a player and the type of pieces they are using from next line of the file stream.
//check the player's name is preceded by H: or V: to identify the orientation of the pieces.
//check that the player's name is not an empty string.
//return true if can read these info from the file, false otherwise.
bool getPlayerInfoFromFile(std::ifstream &file, std::string &name, bool &horizontal)
{
	std::string tempStr{};
	char tempChar{};
	char separator{};
	file>> tempChar;
	tempChar = toupper(tempChar);
	if (tempChar == 'H' || tempChar == 'V') //first char must be V or H
	{
		file >> separator;
		if (separator != ':')
			return false;
		std::getline(file, tempStr);
		name = tempStr;
		if (name.length() == 0)	//name cannot be an empty string
		{
			return false;
		}
		horizontal = (tempChar == 'H' ? true : false);
		return true;
	}
	else
		return false;
}

//get board size from the file.
//check that all the rows of the board have the same length.
//return true if can read these info from the file, false otherwise.
bool getBoardSizeFromFile(std::ifstream &file, int &size, int &emptyLines)
{
	std::string tempStr{};
	emptyLines = -1;
	do //this loop discard the empty lines between the players'info and the board
	{
		std::getline(file, tempStr);
		if (file.eof()) //there is no board at all on the file
			return false;
		emptyLines++;
	} while (tempStr.length() == 0);

	size = tempStr.length(); //size of the board set to length of the first non-empty line after players'info
	
	for (int lineCount = 1; lineCount < size; lineCount++) //loop through the following [size-1] lines
	{
		std::getline(file, tempStr);
		if (tempStr.length() != size) //each line in the board must have a length of [size]
			return false;
	}
	if (file.fail()) //getline() failed because end of file was reached before the loop above was exited
	{
		file.clear();
		return false;
	}
	return true;
}

//read info about the players and the board size from the file.
//return true if can read all these info. False otherwise.
//the function also discard from the file strem everything before the board.
bool readFile(std::ifstream &inFile, std::string &name1, std::string &name2, bool &horizontal1, bool &horizontal2, int &size)
{
	int emptyLines{};	//count the empty lines between the players'info and the board
	//CHECK FORMAT OF THE FIRST TWO LINES OF THE FILE
	if (!getPlayerInfoFromFile(inFile, name1, horizontal1) || !getPlayerInfoFromFile(inFile, name2, horizontal2))
	{
		std::cout << "Invalid players data." << std::endl;
		return false;
	}
	if (horizontal1 == horizontal2 || name1 == name2)	//player names or orientations cannot be the same
	{
		std::cout << "Invalid players data." << std::endl;
		return false;
	}
	//CHECK FORMAT OF THE ARRAY REPRESENTING THE BOARD
	if (!getBoardSizeFromFile(inFile, size, emptyLines))
	{
		std::cout << "Invalid board format." << std::endl;
		return false;
	}
	//GO BACK TO THE BEGINNING OF THE FILE AND DISCARD THE LINES BEFORE THE BOARD
	std::string tempStr{};
	inFile.clear();
	inFile.seekg(0, inFile.beg); //move to begininng of the file
	for (int count=0; count<2+emptyLines; count++) //flush [2+emptyLines] lines
		std::getline(inFile, tempStr);
	return true;
}

//delete dinamically allocated array.
void deallocateMemoryArray(Board &board)
{
	if (board.doubleArray == nullptr)
		return;
	for (int count = 0; count < board.size; count++)
	{
		delete[] board.doubleArray[count];
	}
	delete[] board.doubleArray;
	board.doubleArray = nullptr;
}

//check that the configuration of the pieces is allowed by the rules.
bool isGameConfigurationValid(const Board &board, int hCounter, int vCounter)
{
	//horizontal pieces are placed first-> Hs on the board are either same number or 2 more than Vs.
	if (hCounter != vCounter && hCounter != vCounter + 2)
		return false;
	if (board.size < 2 || board.size>15)
		return false;
	bool evenConsecutiveTiles{ true }; 
	//check H tiles: the following loop scans the array row by row.
	//The variable evenConsecutiveTiles is toggled every time 'H' is found in the array.
	//Every time the element in the array is NOT 'H' or it is the end of the row,
	//evenConsecutiveTiles must be true (i.e. toggled an even number of times).
	for (int row = 0; row < board.size; row++)
	{
		for (int col = 0; col < board.size; col++)
		{
			if (board.doubleArray[row][col] == 'H')
			{
				evenConsecutiveTiles=!evenConsecutiveTiles;
			}
			else
			{
				if (!evenConsecutiveTiles)
					return false;
			}
		}
		if (!evenConsecutiveTiles)
			return false;
	}
	//Check V tiles: just like H tiles but loop scan the board column by column.
	for (int col = 0; col < board.size; col++)
	{
		for (int row = 0; row < board.size; row++)
		{
			if (board.doubleArray[row][col] == 'V')
			{
				evenConsecutiveTiles = !evenConsecutiveTiles;
			}
			else
			{
				if (!evenConsecutiveTiles)
					return false;
			}
		}
		if (!evenConsecutiveTiles)
			return false;
	}
	return true;
}

//load a game from a file.
//check that the format of the file is readable by the programme.
//extract info about players and board size.
//transfer the content of the board in the file to a new array.
//check the game configuration is allowed by the rules.
//move all these data from the local variables into the function arguments.
//delete the old array.
//the function returns true if the game is loaded correctly, false otherwise.
bool loadGame(Board &board, Player &p1, Player &p2)
{
	//local variables: will store info temporarely
	std::string name1{};
	std::string name2{};
	bool horizontalPiece1{};
	bool horizontalPiece2{};
	int size;
	//OPEN FILE
	std::cout << "Specify the name of the file on which your game is saved: ";
	std::string filename{};
	std::getline(std::cin, filename);
	std::ifstream inFile(filename);
	if (!inFile.is_open())
	{
		std::cout <<"\""<< filename << "\" could not be opened for reading." << std::endl;
		return false;
	}
	//CHECK THAT THE FILE IS IN A FORMAT THAT CAN BE READ. IF YES, EXTRACT THE INFO ABOUT THE GAME
	//IMPORTANT: readFile() also flush from the file strem everything before the board.
	if ( !readFile(inFile, name1, name2, horizontalPiece1, horizontalPiece2, size) )
		return false;
	//ALLOCATE MEMORY FOR A NEW BOARD AND READ DATA FROM THE BOARD IN THE FILE
	std::string tempStr{};
	char tempChar{};
	int hCounter{0};	//count tiles occupied by a horizontal piece
	int vCounter{0};	//count tiles occupied by a vertical piece
	Board newBoard{size ,  createEmptyBoard(size) };
	for (int lineCount = 0; lineCount < size; lineCount++) //read the chars in the file's board and fill the new 2d array.
	{
		std::getline(inFile, tempStr);
		for (int charCount = 0; charCount < size; charCount++)
		{
			tempChar = toupper(tempStr[charCount]);
			if (tempChar == 'H')
			{
				newBoard.doubleArray[lineCount][charCount] = tempChar;
				hCounter++;
			}
			else if (tempChar == 'V')
			{
				newBoard.doubleArray[lineCount][charCount] = tempChar;
				vCounter++;
			}
			else if (tempChar=='-')
				newBoard.doubleArray[lineCount][charCount] = ' ';
			else	//the current charcater is not recognised
			{
				deallocateMemoryArray(newBoard);	//deallocate memory allocated for newBoard
				std::cout << "Invalid charcter on the board." << std::endl;
				return false;
			}
		}
	}
	//CHECK THAT THE CONFIGURATION OF THE GAME IS VALID
	if (!isGameConfigurationValid(newBoard, hCounter, vCounter))
	{
		deallocateMemoryArray(newBoard);	//deallocate memory allocated for newBoard
		std::cout << "Invalid game configuration." << std::endl;
		return false;
	}
	//IF EVERYTHING WENT FINE SO FAR...
	//COPY THE DATA FROM THE LOCAL VARIABLES INTO THE FUNCTION ARGUMENTS
	//decide whose turn is it based on the number of H and V tiles
	//knowing that the Horizontal piece is placed first in the game.
	if (hCounter == vCounter)
		p1.hasToPlay = horizontalPiece1;
	else if (hCounter == vCounter + 2)
		p1.hasToPlay = !horizontalPiece1;
	p2.hasToPlay = !p1.hasToPlay;
	p1.name = name1;
	p2.name = name2;
	p1.horizontalPiece = horizontalPiece1;
	p2.horizontalPiece = !p1.horizontalPiece;
	deallocateMemoryArray(board); //deallocate memory for the old 2d array to prevent memory leaks
	board.size = size;
	board.doubleArray = newBoard.doubleArray;
	return true;
}