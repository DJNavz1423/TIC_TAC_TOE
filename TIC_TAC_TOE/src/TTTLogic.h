#pragma once
#include <iostream>
#include <windows.h>

class TicTacToe {
private:
	char matrix[3][3];
	short player, status;
	char mark, inputNum;

	 short checkwin() const {
		for (short i = 0; i < 3; i++)  /*Checks row and column*/ {
			if (matrix[i][0] == matrix[i][1] && matrix[i][1] == matrix[i][2]) //row
				return 1; //return 1 means win
			if (matrix[0][i] == matrix[1][i] && matrix[1][i] == matrix[2][i]) //column
				return 1;
		}
		if (matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2] || matrix[0][2] == matrix[1][1] && matrix[1][1] == matrix[2][0]) //checks diagonals
			return 1;

		for (short i = 0; i < 3; i++) { //checks if board is full
			for (short j = 0; j < 3; j++) {
				if (matrix[i][j] != 'X' && matrix[i][j] != 'O')
					return -1; // Return -1 indicating game is still ongoing
			}
		}
		return 0;
	}
	 void resetMatrix() { //reset matrix and prints 1 - 9 chars
		 system("cls");
		 char count = '1';
		 for (short i = 0; i < 3; i++) {
			 for (short j = 0; j < 3; j++) {
				 matrix[i][j] = count++;
			 }
		 }
	 }
void botMove(char matrix[3][3], char& botSide, char& playerSide) {
	// Check if the bot can win on the next move
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (matrix[i][j] != 'X' && matrix[i][j] != 'O') {
				char original = matrix[i][j];
				matrix[i][j] = botSide;
				if (checkwin() == 1) {
					return; // Bot has found a winning move
				}
				matrix[i][j] = original; // Reset the cell
			}
		}
	}
	for (int i = 0; i < 3; ++i) { // Check if the player can win on the next move and block them
		for (int j = 0; j < 3; ++j) {
			if (matrix[i][j] != 'X' && matrix[i][j] != 'O') {
				char original = matrix[i][j];
				matrix[i][j] = playerSide;
				if (checkwin() == 1) {
					matrix[i][j] = botSide; // Block the winning move
					return;
				}
				matrix[i][j] = original; // Reset the cell
			}
		}
	}
		// If no winning or blocking moves are available, make a random move
	int move;
	bool validMove = false;

	while (!validMove) {
		move = rand() % 9 + 1;

		int row = (move - 1) / 3;
		int col = (move - 1) % 3;

		if (matrix[row][col] != 'X' && matrix[row][col] != 'O') {
			matrix[row][col] = botSide;
			validMove = true;
		}
	}
}
void boardA(char& side, char& side1)  /*prints board for single player */ {
	system("cls");
	std::cout << "\tTIC - TAC - TOE\n"
		<< "\t---------------\n\n"
		<< "PLAYER (" << side << ")  -- - AI (" << side1 << ")\n\n\n";

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
void boardB() /*prints board for 2 player */ {
	system("cls");
	std::cout << "\tTIC - TAC - TOE\n"
		<< "\t---------------\n\n"
		<< "PLAYER 1 (X)  ---  PLAYER 2 (O)\n\n\n";

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
public:
	void startAndReset() {
		resetMatrix();
		player = 1;
		status = -1;
	}
	void singePlayer(char& run, bool& running) {
		char side, side1;
		do {
			system("cls");
			std::cout << "SINGLE PLAYER\n"
				<< "-------------\n\n"
				<< "CHOOSE SIDE (X or O): ";
			std::cin >> side;
			if (side == 'X')
				side1 = 'O';

			else if (side == 'O')
				side1 = 'X';

			else {
				std::cout << "\a\nINVALID INPUT! PRESS ANY KEY TO CONTINUE!\n";
				std::cin.ignore();
				std::cin.get();
			}
		} while (side != 'X' && side != 'O');

		if (side == 'X') {
			do {
				boardA(side, side1);
				player = (player % 2) ? 1 : 2;
				if (player == 1) {
					std::cout << "\n\nPLAYER! --- ENTER A NUMBER: ";
					std::cin >> inputNum;
					mark = side;

					if (inputNum >= '1' && inputNum <= '9') {
						short row = (inputNum - '1') / 3;
						short col = (inputNum - '1') % 3;

						if (matrix[row][col] == inputNum)
							matrix[row][col] = mark;

						else {
							std::cout << "\a\nINVALID MOVE! PRESS ANY KEY TO CONTINUE!";
							player--;
							std::cin.ignore();
							std::cin.get();
						}
					}
				}
				else {
					std::cout << "\n\nBOT (O) is thinking..." << std::endl;
					Sleep(1500); // Added sleep for better visualization
					botMove(matrix, side1, side);
				}
				status = checkwin();
				player++;
			} while (status == -1);
			boardA(side, side1);
			if (player == 2) {
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
			player = 2;
			do {
				boardA(side, side1);
				player = (player % 2) ? 1 : 2;
				if (player == 1) {
					std::cout << "\n\nPLAYER! --- ENTER A NUMBER: ";
					std::cin >> inputNum;
					mark = side;

					if (inputNum >= '1' && inputNum <= '9') {
						short row = (inputNum - '1') / 3;
						short col = (inputNum - '1') % 3;

						if (matrix[row][col] == inputNum)
							matrix[row][col] = mark;

						else {
							std::cout << "\a\nINVALID MOVE! PRESS ANY KEY TO CONTINUE!";
							player--;
							std::cin.ignore();
							std::cin.get();
						}
					}
				}
				else {
					std::cout << "\n\nBOT (O) is thinking..." << std::endl;
					Sleep(1500); // Added sleep for better visualization
					botMove(matrix, side1, side);
				}
				status = checkwin();
				player++;
			} while (status == -1);
			boardA(side, side1);
			if (player == 2) {
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
	void twoPlayers(char& run, bool& running) {
		do {
				boardB();
				player = (player % 2) ? 1 : 2;

				std::cout << "\n\nPLAYER " << player << " --- ENTER A NUMBER: ";
				std::cin >> inputNum;

				mark = (player == 1) ? 'X' : 'O';

				if (inputNum >= '1' && inputNum <= '9') {
					short row = (inputNum - '1') / 3;
					short col = (inputNum - '1') % 3;

					if (matrix[row][col] == inputNum)
						matrix[row][col] = mark;

					else {
						std::cout << "\a\nINVALID MOVE! PRESS ANY KEY TO CONTINUE!";
						player--;
						std::cin.ignore();
						std::cin.get();
					}
				}
				status = checkwin();
				player++;
			} while (status == -1);
			boardB();
			if (status == 1) {
				std::cout << "\a\nCONGRATULATIONS! PLAYER " << --player << " WINS!\n"
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