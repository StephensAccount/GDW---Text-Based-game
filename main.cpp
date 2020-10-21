#include <iostream> 
#include <time.h> 
#include <stdlib.h> 
using namespace std;

// Global variables 
int playerX = 4, playerY = 1;
int moveCounter = 3; // Player's moves 
char map[6][8] = { // Global variables 
	{'-','-','-','-','-','-','-','-'},
	{'-','-','-','-','-','-','-','-'},
	{'-','-','-','-','-','-','-','-'},
	{'-','-','-','-','-','-','-','-'},
	{'-','-','-','-','-','-','-','-'},
	{'-','-','-','-','-','-','-','-'},
};

string adventurerNameList[3];

int adventurerList[3][3]{ // First slot is the Health, second and third slot is the X and Y coordinates 
	{6},
	{6},
	{6},
};

int enemyList[6][4]; // Left to right. First slot if enemy type, second slot is the health of the enemy 
					// Third and forth slots are the X and Y cooridinates 

//Movement Items 
int diagDash = 1;

//Attack Items 
string attacks[] = { "Jab Attack", "Ranged Attack", "Swing Attack" };

//Consumable Items 
string consumables[1] = { "Health Potion" };


void startUp() {
	int obstacleNumber = rand() % 8 + 1;  // Determines the number of obstacles 
	 // system("Color C1"); // This used to change the color 
	cout << "Obstacles: " << obstacleNumber << endl;
	do {
		int x = rand() % 6; // Determines the vertical coordinate 
		int y = rand() % 8; // Determines the horizonal coordinate 
		cout << x << " " << y << endl;

		if ((x != playerX) && (y != playerY) && (map[x][y] != 'B')) {
			map[x][y] = '#';
			obstacleNumber--;
		}
	} while (obstacleNumber > 0);

	int enemyNumber = rand() % 6 + 1;  // Determines the number of enemies 
	cout << "Enemies: " << enemyNumber << endl;
	int arrayCounter = 0; // Used for assigning the jobs each enemy takes  
	do {
		int x = rand() % 6; // Determines the vertical coordinate 
		int y = rand() % 8; // Determines the horizontal coordinate 
		cout << x << " " << y << endl;

		if ((x != playerX) && (y != playerY) && (map[x][y] != 'B')) {
			int type = rand() % 4;
			if (type == 0) {
				enemyList[arrayCounter][0] = 0; // 0 is the type number for zombies 
				enemyList[arrayCounter][1] = 3; // Health 
				enemyList[arrayCounter][2] = x; // Coordinates 
				enemyList[arrayCounter][3] = y;
				map[x][y] = 'Z';
			}
			else if (type == 1) {
				enemyList[arrayCounter][0] = 1; // 1 is the type number for Thieves 
				enemyList[arrayCounter][1] = 4; // Health 
				enemyList[arrayCounter][2] = x; // Coordinates 
				enemyList[arrayCounter][3] = y;
				map[x][y] = 'T';
			}
			else if (type == 2) {
				enemyList[arrayCounter][0] = 2; // 2 is the type number for Slashers 
				enemyList[arrayCounter][1] = 5; // Health 
				enemyList[arrayCounter][2] = x; // Coordinates 
				enemyList[arrayCounter][3] = y;
				map[x][y] = 'S';
			}
			else if (type == 3) {
				enemyList[arrayCounter][0] = 3; // 3 is the type number for Rangers 
				enemyList[arrayCounter][1] = 2; // Health 
				enemyList[arrayCounter][2] = x; // Coordinates 
				enemyList[arrayCounter][3] = y;
				map[x][y] = 'E';
			}
			enemyNumber--;
		}
	} while (enemyNumber > 0);

	for (int i = 0; i < 3; i++) {
		cout << "Please enter the name of Adventurer #" << i + 1 << ".\n";
		cin >> adventurerNameList[i];
	}
}

void jabAttack()
{
	int dirInput;
	cout << "\nWhich Direction?\n1. Up\n2. Down\n3. Left\n4. Right\n";
	cin >> dirInput;
	int tempX = 0, tempY = 0;

	if (dirInput == 1)
	{
		tempX = -1, tempY = 0;
	}
	else if (dirInput == 2)
	{
		tempX = 1, tempY = 0;
	}
	else if (dirInput == 3)
	{
		tempX = 0, tempY = -1;
	}
	else if (dirInput == 4)
	{
		tempX = 0, tempY = 1;
	}
	else
	{
		tempX = 0, tempY = 0;
	}

	int enemyPosX = playerX + tempX;
	int enemyPosY = playerY + tempY;
	cout << map[enemyPosX][enemyPosY] << endl; // Debugging 

	if (map[playerX + tempX][playerY + tempY] == 'E')
	{
		//Take away enemy damage 
		cout << "\nYou attacked the enemy for 2 DMG!\n";
		// Put code that checks enemy health here 
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
		cout << "\n" << i + 1 << ": " << attacks[i] << endl;
	}
	cout << "\n";
	cout << "4. Return to menu.\n";
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

	else
	{
		moveCounter++;
	}
}

void push()
{



}

void move()
{
	int moveInput;
	cout << "\nWhat Type of Movement?\n1. Standard Walk\n2. Diagonal Dash: " << diagDash << "\n";
	cin >> moveInput;
	if (moveInput == 1)
	{
		int dirInput;
		cout << "\nWhich Direction?\n1. Up\n2. Down\n3. Left\n4. Right\n5. Back to menu\n"; // This is no option for 5. as it is set as the default 
		cin >> dirInput;
		if (dirInput == 1) // Player moving up 
		{
			if (map[playerX - 1][playerY] != 'E' && map[playerX - 1][playerY] != '#') {
				map[playerX][playerY] = '-';
				playerX -= 1;
			}
			else {
				cout << endl;
				cout << "!!The Enemy is blocking your path!!\n";
				moveCounter++;
			}
		}

		else if (dirInput == 2) // Player moving down 
		{
			if (map[playerX + 1][playerY] != 'E' && map[playerX + 1][playerY] != '#') {
				map[playerX][playerY] = '-';
				playerX += 1;
			}
			else {
				cout << endl;
				cout << "!!The Enemy is blocking your path!!\n";
				moveCounter++;
			}
		}

		else if (dirInput == 3) // Player moving left 
		{
			if (map[playerX][playerY - 1] != 'E' && map[playerX][playerY - 1] != '#') {
				map[playerX][playerY] = '-';
				playerY -= 1;
			}
			else {
				cout << endl;
				cout << "!!The Enemy is blocking your path!!\n";
				moveCounter++;
			}
		}

		else if (dirInput == 4) // Player moving right 
		{
			if (map[playerX][playerY + 1] != 'E' && map[playerX][playerY + 1] != '#') {
				map[playerX][playerY] = '-';
				playerY += 1;
			}
			else {
				cout << endl;
				cout << "!!The Enemy is blocking your path!!\n";
				moveCounter++;
			}
		}

		else // Player chose to go back to the menu 
		{
			moveCounter++;
		}

	}

	else if (moveInput == 2)
	{
		if (diagDash > 0)
		{
			int dirInput;
			cout << "\nWhich Direction?\n1. Top-Left\n2. Top-Right\n3. Bottom-Right\n4. Bottom-Left\n5. Back to menu\n"; // This is no option for 5. as it is set as the default 
			cin >> dirInput;
			if (dirInput == 1) // Top Left
			{
				if (map[playerX - 1][playerY - 1] != 'E' && map[playerX - 1][playerY - 1] != 'O') {
					map[playerX][playerY] = '-';
					playerX -= 1;
					playerY -= 1;
					diagDash -= 1;
				}
				else {
					cout << endl;
					cout << "!!The Enemy is blocking your path!!\n";
					moveCounter++;
				}
			}

			else if (dirInput == 2) // Top Right
			{
				if (map[playerX - 1][playerY + 1] != 'E' && map[playerX - 1][playerY + 1] != 'O') {
					map[playerX][playerY] = '-';
					playerX -= 1;
					playerY += 1;
					diagDash -= 1;
				}
				else {
					cout << endl;
					cout << "!!The Enemy is blocking your path!!\n";
					moveCounter++;
				}
			}

			else if (dirInput == 3) // Bottom Right
			{
				if (map[playerX + 1][playerY + 1] != 'E' && map[playerX + 1][playerY + 1] != 'O') {
					map[playerX][playerY] = '-';
					playerX += 1;
					playerY += 1;
					diagDash -= 1;
				}
				else {
					cout << endl;
					cout << "!!The Enemy is blocking your path!!\n";
					moveCounter++;
				}
			}

			else if (dirInput == 4) // Bottom Left 
			{
				if (map[playerX + 1][playerY - 1] != 'E' && map[playerX + 1][playerY - 1] != 'O') {
					map[playerX][playerY] = '-';
					playerX += 1;
					playerY -= 1;
					diagDash -= 1;
				}
				else {
					cout << endl;
					cout << "!!The Enemy is blocking your path!!\n";
					moveCounter++;
				}
			}

			else // Player chose to go back to the menu 
			{
				moveCounter++;
			}
		}

		else
		{
			cout << "You have run out of this item.";
			moveCounter++;
		}
		




	}
	
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
				map[x][y] = 'A';

			}
			cout << map[x][y] << " "; // used to separate the map a bit 
		}

	}
	cout << "\n";

}

void playerTurn()
{
	int input;
	do {
		cout << moveCounter << " Moves Remaining.";
		cout << "\nWhat would you like to do?\n1. Move\n2. Attack\n3. Push\n4. Use Item\n";
		cin >> input;

		if (input == 1)
		{
			move();
			moveCounter--;
		}

		else if (input == 2)
		{
			attack();
			moveCounter--;
		}

		else if (input == 3)
		{
			moveCounter--;

		}

		else if (input == 4)
		{
			moveCounter--;

		}

		else
		{
			moveCounter += 1;
			cout << "\nInvalid Input. Please Try Again.\n";

		}

		markMap();
	} while (moveCounter != 0);
	moveCounter = 3; // Used to reset the counter 
}

int main()
{
	srand(time(NULL)); // This is used to make random numbers 
	startUp();
	markMap();
	playerTurn();
}