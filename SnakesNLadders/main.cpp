#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "Tunnel.h"
#include <thread>

using namespace std;

int height, width;
int playerX, playerY;
int playerPos = 0;
char input;
bool gameOver;
vector <Tunnel> tunnels;

/*
This function sets up the board, player,
and snakes/ladders
*/
void SetUp()
{
	gameOver = false;

	// Board Setup
	height = 10, width = 10;

	// Player Setup
	playerX = 0, playerY = 9;

	//Ladders Setup
	tunnels.push_back(Tunnel("L ", 3, 9, 6, 8));
	tunnels.push_back(Tunnel("L ", 8, 9, 9, 6));
	tunnels.push_back(Tunnel("L ", 7, 7, 3, 1));
	tunnels.push_back(Tunnel("L ", 0, 6, 1, 4));
	tunnels.push_back(Tunnel("L ", 0, 8, 2, 6));
	tunnels.push_back(Tunnel("L ", 2, 3, 0, 1));
	tunnels.push_back(Tunnel("L ", 9, 2, 9, 0));
}

/*
This function redraws the board
*/
void Draw()
{
	system("cls");

	int counter = 100;
	bool isEvenRow = true;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			bool isSpecialTile = false;

			for (int i = 0; i < tunnels.size(); i++)
			{
				if (tunnels[i].isTrapLocation(x, y))
				{
					cout << " " << setw(3) << right << tunnels[i].getName() << " ";
					isSpecialTile = true;
				}
			}

			if (!isSpecialTile)
			{
				if (y == playerY && x == playerX)
					cout << " " << setw(3) << right << "#" << " ";

				else
					cout << " " << setw(3) << right << counter << " ";
			}


			if (x != width - 1)
			{
				if (isEvenRow)
					counter--;
				else
					counter++;
			}

		}
		counter -= 10;
		isEvenRow = !isEvenRow;
		cout << endl;
	}
} // END of Draw()

void Input()
{
	cout << "Roll the dice";
	cin.get();
}

/*
This function moves the player a single space
*/
void Logic()
{

	if (playerY % 2 == 0)
		playerX--;
	else
		playerX++;


	// Too far off board, move up a row
	if (playerX >= width)
	{
		playerY--;
		playerX--;
	}
	else if (playerX < 0)
	{
		playerY--;
		playerX++;
	}

	// If at final space, don't allow the player to
	// move and end the gameplay loop
	if (playerY <= 0 && playerX <= 0)
	{
		playerX = 0;
		playerY = 0;
		Draw();
		gameOver = true;
	}
} // END of Logic


/*
This function checks to see if player is
on a snake or ladder location and teleports
them accordingly
*/
void CheckForTunnel()
{
	// CHECK for snakes and / or ladders
	for (int i = 0; i < tunnels.size(); i++)
	{
		if (tunnels[i].isTrapLocation(playerX, playerY))
		{
			tunnels[i].teleportPlayer(playerX, playerY);
		}
	}
}

int main()
{
	std::srand(time(nullptr));


	int diceRoll = 0;

	SetUp();
	Draw();

	while (!gameOver)
	{

		if (diceRoll != 0)
			cout << "The last diceroll was " << diceRoll << endl;
		Input();

		diceRoll = (rand() % 6) + 1;
		diceRoll = 5;
		for (int i = 0; i < diceRoll; i++) {

			std::this_thread::sleep_for(std::chrono::seconds(1));
			Logic();
			Draw();
		}

		CheckForTunnel();
	}

	cout << "\nThe End" << endl;
	cout << endl;

	system("pause");
	return 0;
}