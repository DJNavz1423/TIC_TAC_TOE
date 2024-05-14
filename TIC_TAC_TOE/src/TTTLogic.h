#pragma once
#include "TTTelements.h"

class TicTacToe {
private:
	Elements elem;
	 short checkwin() const {
		for (short i = 0; i < elem.SIZE; i++)  /*Checks row and column*/ {
			if (elem.matrix[i][0] == elem.matrix[i][1] && elem.matrix[i][1] == elem.matrix[i][2]) //row
				return 1; //return 1 means win
			if (elem.matrix[0][i] == elem.matrix[1][i] && elem.matrix[1][i] == elem.matrix[2][i]) //column
				return 1;
		}
		if (elem.matrix[0][0] == elem.matrix[1][1] && elem.matrix[1][1] == elem.matrix[2][2] || elem.matrix[0][2] == elem.matrix[1][1] && elem.matrix[1][1] == elem.matrix[2][0]) //checks diagonals
			return 1;

		for (short i = 0; i < elem.SIZE; i++) { //checks if board is full
			for (short j = 0; j < elem.SIZE; j++) {
				if (elem.matrix[i][j] != 'X' && elem.matrix[i][j] != 'O')
					return -1; // Return -1 indicating game is still ongoing
			}
		}
		return 0;
	}
	 void resetMatrix() { //reset matrix and prints 1 - 9 chars
		 system("cls");
		 char count = '1';
		 for (short i = 0; i < elem.SIZE; i++) {
			 for (short j = 0; j < elem.SIZE ; j++) {
				 elem.matrix[i][j] = count++;
			 }
		 }
	 }
void botMove(char (&matrix)[3][3], char& botMark, char& playerSide) { //bot logic
	// Check if the bot can win on the next move
	for (int i = 0; i < elem.SIZE; ++i) {
		for (int j = 0; j < elem.SIZE; ++j) {
			if (matrix[i][j] != 'X' && matrix[i][j] != 'O') {
				char original = matrix[i][j];
				matrix[i][j] = botMark;
				if (checkwin() == 1) {
					return; // Bot has found a winning move
				}
				matrix[i][j] = original; // Reset the cell
			}
		}
	}
	for (int i = 0; i < elem.SIZE; ++i) { // Check if the player can win on the next move and block them
		for (int j = 0; j < 3; ++j) {
			if (matrix[i][j] != 'X' && matrix[i][j] != 'O') {
				char original = matrix[i][j];
				matrix[i][j] = playerSide;
				if (checkwin() == 1) {
					matrix[i][j] = botMark; // Block the winning move
					return;
				}
				matrix[i][j] = original; // Reset the cell
			}
		}
	}
	if (matrix[1][1] != 'X' && matrix[1][1] != 'O') {
		matrix[1][1] = botMark;
		return;
	}
	int move;
	bool validMove = false;
	while (!validMove) { // If no winning or blocking moves are available, make a random move
		move = rand() % 9 + 1;

		int row = (move - 1) / elem.SIZE;
		int col = (move - 1) % elem.SIZE;

		if (matrix[row][col] != 'X' && matrix[row][col] != 'O') {
			matrix[row][col] = botMark;
			validMove = true;
		}
	}
}
public:
	void startAndReset() { //set board and elements at the start and loop
		resetMatrix();
		elem.player = 1;
		elem.status = -1;
	}
	void singePlayer(char& run, bool& running, char& choice) { //single player method
		do {
			system("cls");
			std::cout << "SINGLE PLAYER\n"
				<< "-------------\n\n"
				<< "CHOOSE SIDE (X or O): ";
			std::cin >> elem.mark;
			elem.botMark = (elem.mark == 'X') ? 'O' : 'X';

			if(elem.mark != 'X' && elem.mark != 'O') {
				std::cout << "\a\nINVALID INPUT! PRESS ANY KEY TO CONTINUE!\n";
				std::cin.ignore();
				std::cin.get();
			}
		} while (elem.mark != 'X' && elem.mark != 'O');

		if (elem.mark == 'X') {
			do {
				elem.board(choice);
				elem.player = (elem.player % 2) ? 1 : 2;
				if (elem.player == 1) {
					std::cout << "\n\nPLAYER! --- ENTER A NUMBER: ";
					std::cin >> elem.inputNum;

					if (elem.inputNum >= '1' && elem.inputNum <= '9') {
						short row = (elem.inputNum - '1') / elem.SIZE;
						short col = (elem.inputNum - '1') % elem.SIZE;

						if (elem.matrix[row][col] == elem.inputNum)
							elem.matrix[row][col] = elem.mark;

						else {
							std::cout << "\a\nINVALID MOVE! PRESS ANY KEY TO CONTINUE!";
							elem.player--;
							std::cin.ignore();
							std::cin.get();
						}
					}
				}
				else {
					std::cout << "\n\nBOT (O) is thinking..." << std::endl;
					Sleep(1500); // Added sleep for better visualization
					botMove(elem.matrix, elem.botMark, elem.mark);
				}
				elem.status = checkwin();
				elem.player++;
			} while (elem.status == -1);
			elem.board(choice);
			if (checkwin() == 0) {
				std::cout << "\n\nGAME DRAW!\n"
					<< "\nDO YOU WANT TO PLAY AGAIN? (Y/N): ";
				std::cin >> run;
				running = (run == 'Y' || run == 'y') ? true : false;
			}
			else if (elem.player == 2) {
				std::cout << "\n\nCONGRATULATIONS! PLAYER WINS!\n"
					<< "\nDO YOU WANT TO PLAY AGAIN? (Y/N): ";
				std::cin >> run;
				running = (run == 'Y' || run == 'y') ? true : false;
			}
			else {
				std::cout << "\n\nTOO BAD! BOT WINS!\n"
					<< "\nDO YOU WANT TO PLAY AGAIN? (Y/N): ";
				std::cin >> run;
				running = (run == 'Y' || run == 'y') ? true : false;
			}
		}
		else {
			elem.player = 2;
			do {
				elem.board(choice);
				elem.player = (elem.player % 2) ? 1 : 2;
				if (elem.player == 1) {
					std::cout << "\n\nPLAYER! --- ENTER A NUMBER: ";
					std::cin >> elem.inputNum;

					if (elem.inputNum >= '1' && elem.inputNum <= '9') {
						short row = (elem.inputNum - '1') / elem.SIZE;
						short col = (elem.inputNum - '1') % elem.SIZE;

						if (elem.matrix[row][col] == elem.inputNum)
							elem.matrix[row][col] = elem.mark;

						else {
							std::cout << "\a\nINVALID MOVE! PRESS ANY KEY TO CONTINUE!";
							elem.player--;
							std::cin.ignore();
							std::cin.get();
						}
					}
				}
				else {
					std::cout << "\n\nBOT (O) is thinking..." << std::endl;
					Sleep(1500); // Added sleep for better visualization
					botMove(elem.matrix, elem.botMark, elem.mark);
				}
				elem.status = checkwin();
				elem.player++;
			} while (elem.status == -1);
			elem.board(choice);
			if (checkwin() == 0) {
				std::cout << "\n\nGAME DRAW!\n"
					<< "\nDO YOU WANT TO PLAY AGAIN? (Y/N): ";
				std::cin >> run;
				running = (run == 'Y' || run == 'y') ? true : false;
			}
			else if (elem.player == 2) {
				std::cout << "\n\nCONGRATULATIONS! PLAYER WINS!\n"
					<< "\nDO YOU WANT TO PLAY AGAIN? (Y/N): ";
				std::cin >> run;
				running = (run == 'Y' || run == 'y') ? true : false;
			}
			else {
				std::cout << "\n\nTOO BAD! BOT WINS!\n"
					<< "\nDO YOU WANT TO PLAY AGAIN? (Y/N): ";
				std::cin >> run;
				running = (run == 'Y' || run == 'y') ? true : false;
			}
		}
		std::cin.ignore();
	}
	void twoPlayers(char& run, bool& running, char& choice) {
		do {
				elem.board(choice);
				elem.player = (elem.player % 2) ? 1 : 2;

				std::cout << "\n\nPLAYER " << elem.player << " --- ENTER A NUMBER: ";
				std::cin >> elem.inputNum;

				elem.mark = (elem.player == 1) ? 'X' : 'O';

				if (elem.inputNum >= '1' && elem.inputNum <= '9') {
					short row = (elem.inputNum - '1') / elem.SIZE;
					short col = (elem.inputNum - '1') % elem.SIZE;

					if (elem.matrix[row][col] == elem.inputNum)
						elem.matrix[row][col] = elem.mark;

					else {
						std::cout << "\a\nINVALID MOVE! PRESS ANY KEY TO CONTINUE!";
						elem.player--;
						std::cin.ignore();
						std::cin.get();
					}
				}
				elem.status = checkwin();
				elem.player++;
			} while (elem.status == -1);
			elem.board(choice);
			if (elem.status == 1) {
				std::cout << "\a\nCONGRATULATIONS! PLAYER " << --elem.player << " WINS!\n"
					<< "\nDO YOU WANT TO PLAY AGAIN? (Y/N): ";
				std::cin >> run;
				running = (run == 'Y' || run == 'y') ? true : false;
			}
			else {
				std::cout << "\a\nGAME DRAW!\n"
					<< "\nDO YOU WANT TO PLAY AGAIN? (Y/N): ";
				std::cin >> run;
				running = (run == 'Y' || run == 'y') ? true : false;
			}
			std::cin.ignore();
			system("cls");
	}
};