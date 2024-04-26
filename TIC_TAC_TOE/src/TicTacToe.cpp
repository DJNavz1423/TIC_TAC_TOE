#include "TTTLogic.h"

int main() { //main - entry point
	TicTacToe game{};
	bool running = true;
	char run;
	char choice;
	do {
		game.startAndReset();
		std::cout << "TIC - TAC - TOE\n" //print menu
			<< "---------------\n\n";
		
		std::cout << "A. SINGLE PLAYER\n"
			<< "B. TWO PLAYERS\n"
			<< "C. QUIT\n"
			<< "\nCHOOSE GAME MODE: ";
		std::cin >> choice;

		switch (choice) { // handle choices
		case 'A':
		case 'a':
			game.singePlayer(run, running, choice);
				break;
		case 'B':
		case 'b':
			game.twoPlayers(run, running, choice);
			break;
		case 'C':
		case 'c':
			running = false;
			break;
		default: // handle invalid input
			std::cout << "\a\nINVALID INPUT! PRESS ANY KEY TO CONTINUE! ";
			std::cin.ignore();
			std::cin.get();
			break;
		}
	} while (running);
	return 0;
}