
#include <iostream>
using namespace std;

int playerX = 4, playerY = 1;
char map[6][8] = { 
	{'O','O','O','O','O','O','O','O'}, 
	{'O','O','O','O','O','O','O','O'},
	{'O','O','O','O','O','O','O','O'},
	{'O','O','O','O','O','O','O','O'},
	{'O','O','O','O','O','O','O','O'},
	{'O','O','O','O','O','O','O','O'},
	 };





void enemyTurn()
{



}


void attack()
{



}

void push()
{



}

void move()
{
	int dirInput;
	cout << "\nWhich Direction?\n1. Up\n2. Down\n3. Left\n4. Right";
	cin >> dirInput;
	if (dirInput == 1)
	{
		map[playerX][playerY] = 'O';
		playerX -= 1;
	}

	else if (dirInput == 2)
	{
		map[playerX][playerY] = 'O';
		playerX += 1;
	}

	else if (dirInput == 3)
	{
		map[playerX][playerY] = 'O';
		playerY -= 1;
	}

	else if (dirInput == 4)
	{
		map[playerX][playerY] = 'O';
		playerY += 1;
	}
	return;
}

void markMap()
{

	for (int x = 0; x < 6; x++)
	{
		cout << "\n";
		for (int y = 0; y < 8; y++)
		{
			
			if (x == playerX && y == playerY)
			{
				map[x][y] = 'P';
			
			}
			cout << map[x][y];
		}

	}
	cout << "\n";

}


void playerTurn()
{
	int input;
	
	for (int i = 3; i > 0; i--)
	{
		cout << i << " Moves Remaining.";
		cout << "\nWhat would you like to do?\n1. Move\n2. Attack\n3. Push\n4. Use Item\n";
		cin >> input;

		if (input == 1)
		{
			move();
		}

		else if (input == 2)
		{


		}

		else if (input == 3)
		{


		}

		else if (input == 4)
		{


		}

		else
		{
			i += 1;
			cout << "\nInvalid Input. Please Try Again.\n";

		}

		markMap();
	}
}

int main()
{
	markMap();
	playerTurn();





	


}

