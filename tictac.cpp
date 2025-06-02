#include <iostream>
#include <string>
using namespace std;

char square[9] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};
string player1, player2 = "BOT";
bool playWithBot = false;

// Function to display the board
void displayBoard()
{
	cout << "\n";
	for (int i = 0; i < 9; i++)
	{
		cout << " " << square[i] << " ";
		if (i % 3 != 2)
			cout << "|";
		if (i % 3 == 2 && i != 8)
			cout << "\n-----------\n";
	}
	cout << "\n"
		 << endl;
}

// Function to check win status
int checkWin()
{
	int winCombos[8][3] = {
		{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
	for (int i = 0; i < 8; i++)
	{
		int a = winCombos[i][0], b = winCombos[i][1], c = winCombos[i][2];
		if (square[a] == square[b] && square[b] == square[c])
		{
			return (square[a] == 'X') ? 1 : 2;
		}
	}
	return 0;
}

// Function to mark box
bool markBox(int player, int box)
{
	if (box < 0 || box > 8 || square[box] == 'X' || square[box] == 'O')
	{
		cout << "Invalid move! Try again.\n";
		return false;
	}
	square[box] = (player == 1) ? 'X' : 'O';
	return true;
}

// Function to check if the game is draw
bool isDraw()
{
	for (int i = 0; i < 9; i++)
	{
		if (square[i] != 'X' && square[i] != 'O')
			return false;
	}
	return true;
}

// Function for BOT move - easy mode
int getBotMove()
{
	for (int i = 0; i < 9; i++)
	{
		if (square[i] != 'X' && square[i] != 'O')
			return i;
	}
	return -1;
}

int main()
{
	int mode;
	cout << "===== TIC TAC TOE =====\n";
	cout << "1. Play with Friend\n";
	cout << "2. Play with BOT\n";
	cout << "Choose mode (1 or 2): ";
	cin >> mode;
	cin.ignore(); // to consume newline

	if (mode == 1)
	{
		playWithBot = false;
		cout << "Enter Player 1 Name (X): ";
		getline(cin, player1);
		cout << "Enter Player 2 Name (O): ";
		getline(cin, player2);
	}
	else
	{
		playWithBot = true;
		cout << "Enter Your Name (X): ";
		getline(cin, player1);
		cout << "You will play against the BOT (O)\n";
	}

	int currentPlayer = 1, box, result = 0;

	while (true)
	{
		displayBoard();

		if (currentPlayer == 1 || !playWithBot)
		{
			string currentName = (currentPlayer == 1) ? player1 : player2;
			cout << currentName << ", enter your move (0-8): ";
			cin >> box;
			if (!markBox(currentPlayer, box))
				continue;
		}
		else
		{
			// Bot's move
			cout << "BOT is thinking...\n";
			box = getBotMove();
			markBox(currentPlayer, box);
			cout << "BOT chose box " << box << endl;
		}

		result = checkWin();
		if (result == 1 || result == 2)
		{
			displayBoard();
			string winner = (result == 1) ? player1 : player2;
			cout << "🎉 Congratulations " << winner << "! You have won the game! 🎉\n";
			break;
		}

		if (isDraw())
		{
			displayBoard();
			cout << "It's a draw! Well played " << player1 << " and " << player2 << ".\n";
			break;
		}

		currentPlayer = (currentPlayer == 1) ? 2 : 1;
	}

	return 0;
}
