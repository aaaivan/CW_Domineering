#include "forwardDeclarations.h"
#include <ctime> // for std::time()
#include <iostream>
#include <string>

int main()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr))); // set seed value for rand(). See usesHorizontalPieces() function.

	std::cout << "------------------------------ DOMINEERING ------------------------------\n" << std::endl;
	std::cout << "Rules: 2 players alternatively place pieces of size 2x1 on a board.\n" <<
		"One player has to place their pieces horizontally, the other player vertically.\n" <<
		"First who cannot add a new piece looses. Player with horizontal pieces goes first.\n" << std::endl;
	Player player1;
	Player player2;
	Board board;
	char optionSelected{};
	
	//MAIN LOOP
	while (true)
	{
		deallocateMemoryArray(board);
		optionSelected = mainMenu(); //return 'Q', 'N' or 'L'
		//Quit programme
		if (optionSelected == 'Q')
			break;
		//New game. Get the info about the players and the board size
		else if (optionSelected == 'N')
		{
			player1.name = askPlayerName("");
			player1.horizontalPiece = usesHorizontalPieces(player1.name);
			player1.hasToPlay = player1.horizontalPiece; //player with horizontal pieces plays first 
			player2.name = askPlayerName(player1.name);
			player2.horizontalPiece = !player1.horizontalPiece;
			player2.hasToPlay = !player1.hasToPlay;
			board.size = askBoardSize();
			board.doubleArray = createEmptyBoard(board.size); //dynamically allocate memory for a 2d array
		}
		//Load game.
		else if (optionSelected == 'L')
		{
			if (!loadGame(board, player1, player2))	//if file not loaded go back to beginning of main loop
				continue;
		}
		//GAME LOOP
		while (true)
		{
			const Player &currentPlayer{ player1.hasToPlay ? player1 : player2 }; //player who has to place a piece next
			if (canPlaceNewPiece(board, currentPlayer)) //check if player can play
			{
				printBoard(board);
				placeNewPiece(board, currentPlayer);
				optionSelected = inGameMenu(); //return 'Q', 'N', 'L' or 'S'
				if (optionSelected == 'N') //Next turn: inactive player becomes active and vice versa
				{
					player1.hasToPlay = !player1.hasToPlay;
					player2.hasToPlay = !player2.hasToPlay;
					continue;
				}
				else if (optionSelected == 'S') //Save the game
				{
					//SAVE GAME LOOP
					while (!saveGame(board, player1, player2)) //while file cannot be saved ask what to do
					{
						optionSelected = gameNotSavedOrLoadedMenu(); //return 'Q', 'R' or 'C'
						if (optionSelected == 'R') //Retry
							continue;
						else if (optionSelected == 'C' || optionSelected == 'Q') //Continue current game or Quit
						{
							player1.hasToPlay = !player1.hasToPlay;
							player2.hasToPlay = !player2.hasToPlay;
							break; //break the save game loop
						}
					}
					if (optionSelected != 'C') //if Continue current game was not chosen
						break; //break game loop and go back to beginning of main loop
				}
				else if (optionSelected == 'L') //Load game
				{
					//LOAD GAME LOOP
					while (!loadGame(board, player1, player2)) //while file cannot be loaded ask what to do
					{
						optionSelected = gameNotSavedOrLoadedMenu(); //return 'Q', 'R' or 'C'
						if (optionSelected == 'R') //Retry
							continue;
						else if (optionSelected == 'C' || optionSelected == 'Q') //Continue current game or Quit
						{ 
							player1.hasToPlay = !player1.hasToPlay;
							player2.hasToPlay = !player2.hasToPlay;
							break; //break load game loop
						}
					}
				}
				if (optionSelected == 'Q') //Quit
					break; //break game loop and go back to beginning of main loop
			}
			else //the current player cannot place a new piece
			{
				printBoard(board);
				std::cout << (player1.hasToPlay ? player1.name : player2.name) << " has no moves left. " << 
					(player1.hasToPlay ? player2.name : player1.name) << " is the winner!" << std::endl;
				std::cout << "***************************************************************\n" << std::endl;
				break; //break game loop and go back to beginning of main loop
			}
		}
	}
}
