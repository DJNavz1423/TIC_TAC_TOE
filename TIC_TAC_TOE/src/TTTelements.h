#pragma once
#include <iostream>
#include <windows.h>

struct Elements{ // game structure
	static const short SIZE = 3;
	char matrix[SIZE][SIZE]; //board matrix
	short player, status;
	char mark, botMark, inputNum;

	void board(char& choice)  //prints board  {
		system("cls");
		std::cout << "\tTIC - TAC - TOE\n"
			<< "\t---------------\n\n";
		if (choice == 'A' || choice == 'a')
			std::cout << "PLAYER (" << mark << ")  -- - AI (" << botMark << ")\n\n\n";
		else
			std::cout << "PLAYER 1 (X)  ---  PLAYER 2 (O)\n\n\n";

		std::cout << "     |     |     \n"
			<< "  " << matrix[0][0] << "  |  " << matrix[0][1] << "  |  " << matrix[0][2]
			<< "\n_____|_____|_____\n"
			<< "     |     |\n"
			<< "  " << matrix[1][0] << "  |  " << matrix[1][1] << "  |  " << matrix[1][2]
			<< "\n_____|_____|_____\n"
			<< "     |     |     \n"
			<< "  " << matrix[2][0] << "  |  " << matrix[2][1] << "  |  " << matrix[2][2]
			<< "\n     |     |     \n";
	}
};