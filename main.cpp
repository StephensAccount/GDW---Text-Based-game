
#include <iostream>
using namespace std;

int playerX = 4, playerY = 1,playerHP = 6;
char map[6][8] = { 
	{'O','O','O','O','O','O','O','O'}, 
	{'O','O','O','O','O','O','O','O'},
	{'O','O','O','O','O','O','O','O'},
	{'O','O','O','O','O','O','O','O'},
	{'O','O','E','O','O','O','O','O'},
	{'O','O','O','O','O','O','O','O'},
	 };

//Movement Items
string movements[2] = { "Standard Walk","Diagonal Dash" };

//Attack Items
string attacks[] = { "Jab Attack", "Ranged Attack", "Swing Attack"};

//Consumable Items
string consumables[1] = {"Health Potion"};


void enemyTurn()
{



}
void jabAttack()
{


	int dirInput;
	cout << "\nWhich Direction?\n1. Up\n2. Down\n3. Left\n4. Right";
	cin >> dirInput;
	int tempX, tempY;

	if (dirInput == 1)
	{
		tempX = -1;
		tempY = 0;

	}

	else if (dirInput == 2)
	{
		tempX = 1;
		tempY = 0;
	}

	else if (dirInput == 3)
	{
		tempX = 0;
		tempY = -1;
	}

	else if (dirInput == 4)
	{
		tempX = 0;
		tempY = 1;
	}

	else
	{
		tempX = 0;
		tempY = 0;

	}


	if (map[playerX + tempX][playerY + tempY] == 'E')
	{
		//Take away enemy damage

		cout << "\nYou attacked the enemy for 2 DMG!\n";

	}

	else
	{

		cout << "\nYou swung at nothing...\n";


	}



}

void attack()
{
	int input;
	cout << "\nWhat would you like to do?\n";
	for (int i = 0; i < sizeof(attacks) / sizeof(*attacks); i++)
	{
		cout <<"\n" << i + 1 << ": " << attacks[i];

	}
	cout << "\n";
	cin >> input;


	if (input - 1 == 0)
	{
		jabAttack();
	}

	else if (input - 1 == 1)
	{


	}

	else if (input - 1 == 2)
	{



	}




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
			attack();

		}

		else if (input == 3)
		{
			push();

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

