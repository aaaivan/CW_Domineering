#ifndef FORWARD_DECLARATIONS
#define FORWARD_DECLARATIONS

#include <string>
#include <fstream>

struct Player
{
	std::string name = "";
	bool horizontalPiece = true;
	bool hasToPlay = true;
};
struct Board
{
	int size = 0;
	char **doubleArray = nullptr;
};
char mainMenu();
char inGameMenu();
char gameNotSavedOrLoadedMenu();
std::string askPlayerName(std::string opponentName);
bool usesHorizontalPieces(std::string name);
int askBoardSize();
char** createEmptyBoard(int size);
void printBoard(const Board &board);
bool canPlaceNewPiece(const Board &board, const Player &p);
int getPlayerInputRow(int size);
int getPlayerInputCol(int size);
void placeNewPiece(Board &board, const Player &p);
bool saveGame(const Board &board, const Player &p1, const Player &p2);
bool loadGame(Board &board, Player &p1, Player &p2);
void deallocateMemoryArray(Board& board);
#endif // !FORWARD_DECLARATIONS
