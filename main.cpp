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

string adventurerNameList[4];
int gameTurn = 0; // Used for passing turns
int player1TotalHealth = 0; // Used in end calcation
int player2TotalHealth = 0; // Used in end calcation

int player1PotionCounter = 1; // This is used to keep track of the amount of potions player 1 has
int player2PotionCounter = 1; // This is used to keep track of the amount of potions player 2 has
int diagDash = 1;

int adventurerList[4][3]{ // First slot is the Health, second and third slot is the X and Y coordinates
	{6,4,1},
	{6,3,2},
	{6,1,0},
	{6,5,5},
};

//Movement Items
string movements[2] = { "Standard Walk","Diagonal Dash" };

//Attack Items
string attacks[] = { "Jab Attack", "Ranged Attack", "Swing Attack" };

//Consumable Items
string consumables[1] = { "Health Potion" };


void startUp() {

	for (int i = 0; i < 2; i++) { // Adventurers' names under Player 1's control
		cout << "Player 1, Please enter the name of Adventurer #" << i + 1 << ".\n";
		cin >> adventurerNameList[i]; // Use gameTurn to repersent the array numbers
	}

	for (int i = 2; i < 4; i++) { // Adventurers' names under Player 2's control
		cout << "Player 2, Please enter the name of Adventurer #" << i + 1 << ".\n";
		cin >> adventurerNameList[i]; // Use gameTurn to repersent the array numbers
	}

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
}

void jabAttack()
{
	int dirInput;
	cout << "\nWhich Direction?\n1. Up\n2. Down\n3. Left\n4. Right\n5. Cancel";
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
		moveCounter++;
	}

	int enemyPosX = adventurerList[gameTurn][1] + tempX;
	int enemyPosY = adventurerList[gameTurn][2] + tempY;
	cout << map[enemyPosX][enemyPosY] << endl; // Debugging

	for (int i = 0; i < 4; i++) {
		if ((adventurerList[i][1] == enemyPosX) && (adventurerList[i][2] == enemyPosY)) // This is used check if the position of the enemy player 
		{
			cout << "\nYou attacked the enemy for 2 DMG!\n";
			adventurerList[i][0] = adventurerList[i][0] - 3; // Inflict 3 damage
			if (adventurerList[i][0] < 0) {
				adventurerList[i][0] = 0; // Prevents the health from being in the negative, as it will affect the win
			}
			break;
		}
		else
		{
			cout << "\nYou swung at nothing...\n";
		}
	}
}

void rangedAttack() {
	int finalCheck;
	cout << "\n!!ARE YOU SURE? FRIENDLY FIRE IS ON!!\n1. Yes\n2. No (refund action point)";
	cin >> finalCheck;
	if (finalCheck == 1) {
		int dirInput;
		cout << "\nWhich Direction?\n1. Up\n2. Down\n3. Left\n4. Right\n5. Cancel";
		cin >> dirInput;
		if (dirInput == 1) {
			bool hit = false; // Avoid a piercing arrow
			int tempX = adventurerList[gameTurn][1];
			int tempY = adventurerList[gameTurn][2];
			for (int i = tempX - 1; i > -6; i--) { // Goes through the Y axis, + 1 is used to prevent the player shooting himself
				if (map[tempX][i] == '#') { // Checks for obstacles
					cout << "\n!!The arrow hit an obstacle and was stopped!!\n";
					hit = true;
				}
				if (hit == false) { // Skips the check if the Arrow has already hit something
					for (int j = 0; j < 4; j++) { // Checks every Adventurer's position
						if ((adventurerList[j][1] == i) && (adventurerList[gameTurn][2] == adventurerList[j][2])) {
							//the second condition is used to check the x axis
							cout << "\nYou attacked the enemy for 4 DMG!\n";
							adventurerList[j][0] = adventurerList[j][0] - 4; // Inflict 3 damage
							if (adventurerList[j][0] < 0) {
								adventurerList[j][0] = 0; // Prevents the health from being in the negative, as it will affect the win
							}
							hit = true; // Stops the arrow
						}
					}
				}
			}
		}
		else if (dirInput == 2) {
			bool hit = false; // Avoid a piercing arrow
			int tempX = adventurerList[gameTurn][1];
			int tempY = adventurerList[gameTurn][2];
			for (int i = tempX + 1; i < 6; i++) { // Goes through the Y axis, + 1 is used to prevent the player shooting himself
				if (map[tempX][i] == '#') { // Checks for obstacles
					cout << "\n!!The arrow hit an obstacle and was stopped!!\n";
					hit = true;
				}
				if (hit == false) { // Skips the check if the Arrow has already hit something
					for (int j = 0; j < 4; j++) { // Checks every Adventurer's position
						if ((adventurerList[j][1] == i) && (adventurerList[gameTurn][2] == adventurerList[j][2])) {
							//the second condition is used to check the x axis
							cout << "\nYou attacked the enemy for 4 DMG!\n";
							adventurerList[j][0] = adventurerList[j][0] - 4; // Inflict 3 damage
							if (adventurerList[j][0] < 0) {
								adventurerList[j][0] = 0; // Prevents the health from being in the negative, as it will affect the win
							}
							hit = true; // Stops the arrow
						}
					}
				}
			}
		}
		else if (dirInput == 3) {
			bool hit = false; // Avoid a piercing arrow
			int tempX = adventurerList[gameTurn][1];
			int tempY = adventurerList[gameTurn][2];
			for (int i = tempY - 1; i > -6; i--) { // Goes through the Y axis, + 1 is used to prevent the player shooting himself
				if (map[tempX][i] == '#') { // Checks for obstacles
					cout << "\n!!The arrow hit an obstacle and was stopped!!\n";
					hit = true;
				}
				if (hit == false) { // Skips the check if the Arrow has already hit something
					for (int j = 0; j < 4; j++) { // Checks every Adventurer's position
						if ((adventurerList[j][2] == i) && (adventurerList[gameTurn][1] == adventurerList[j][1])) {
							//the second condition is used to check the x axis
							cout << "\nYou attacked the enemy for 4 DMG!\n";
							adventurerList[j][0] = adventurerList[j][0] - 4; // Inflict 3 damage
							if (adventurerList[j][0] < 0) {
								adventurerList[j][0] = 0; // Prevents the health from being in the negative, as it will affect the win
							}
							hit = true; // Stops the arrow
						}
					}
				}
			}
		}
		else if (dirInput == 4) {
			bool hit = false; // Avoid a piercing arrow
			int tempX = adventurerList[gameTurn][1];
			int tempY = adventurerList[gameTurn][2];
			for (int i = tempY + 1; i < 6; i++) { // Goes through the Y axis, + 1 is used to prevent the player shooting himself
				if (map[tempX][i] == '#') { // Checks for obstacles
					cout << "\n!!The arrow hit an obstacle and was stopped!!\n";
					hit = true;
				}
				if (hit == false) { // Skips the check if the Arrow has already hit something
					for (int j = 0; j < 4; j++) { // Checks every Adventurer's position
						if ((adventurerList[j][2] == i) && (adventurerList[gameTurn][1] == adventurerList[j][1])) {
							//the second condition is used to check the x axis
							cout << "\nYou attacked the enemy for 4 DMG!\n";
							adventurerList[j][0] = adventurerList[j][0] - 4; // Inflict 3 damage
							if (adventurerList[j][0] < 0) {
								adventurerList[j][0] = 0; // Prevents the health from being in the negative, as it will affect the win
							}
							hit = true; // Stops the arrow
						}
					}
				}
			}
		}
		else {
			moveCounter++; // Cancel option
		}
	}
	else {
		moveCounter++; // Cancel option
	}
}

void swingAttack() {
	int finalCheck;
	cout << "\n!!ARE YOU SURE? FRIENDLY FIRE IS ON!!\n1. Yes\n2. No (refund action point)";
	cin >> finalCheck;
	if (finalCheck == 1) {
		
		for (int x = -1; x <= 1; x++)
		{
			for (int y = -1; y <= 1; y++)
			{
				if (x != 0 && y != 0)
				{
					for (int i = 0; i < 4; i++)
					{

						if ((adventurerList[i][1] == adventurerList[gameTurn][1] + x) && (adventurerList[i][2] == adventurerList[gameTurn][2] + y)) // This is used check if the position of the enemy player 
						{
							cout << "\nYou attacked the enemy for 2 DMG!\n";
							adventurerList[i][0] = adventurerList[i][0] - 2; // Inflict 2 damage
							if (adventurerList[i][0] < 0) {
								adventurerList[i][0] = 0; // Prevents the health from being in the negative, as it will affect the win
							}

						}





					}
				}


			}



		}


	}

	else {
		moveCounter++;
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
		rangedAttack();
	}

	else if (input - 1 == 2)
	{
		swingAttack();
	}

	else
	{
		moveCounter++;
	}
}

void AdventurerItems() { // Need to input the adventurer number here!
	if ((gameTurn == 0) || (gameTurn == 1)) {
		if (player1PotionCounter > 0) {
			adventurerList[gameTurn][0] += 2; // Adds 2 health
			player1PotionCounter--;
			cout << "\n!!You drank the potion and recovered 2 HP!!\n";
		}
		else {
			cout << "\n!!There are no Potions left in your inventory (action point has been refunded)!!\n";
			moveCounter++;
		}
	}
	if ((gameTurn == 2) || (gameTurn == 3)) {
		if (player2PotionCounter > 0) {
			adventurerList[gameTurn][0] += 2; // Adds 2 health
			player2PotionCounter--;
			cout << "\n!!You drank the potion and recovered 2 HP!!\n";
		}
		else {
			cout << "\n!!There are no Potions left in your inventory (action point has been refunded)!!\n";
			moveCounter++;
		}
	}
}

void push()
{



}

void move()
{
	cout << gameTurn;
	int moveInput;
	int newX = 0, newY = 0;
	cout << "\nWhat Type of Movement?\n1. Standard Walk\n2. Diagonal Dash: " << diagDash << "\n";
	cin >> moveInput;
	if (moveInput == 1)
	{
		int dirInput;
		cout << "\nWhich Direction?\n1. Up\n2. Down\n3. Left\n4. Right\n5. Back to menu\n"; // This is no option for 5. as it is set as the default 
		cin >> dirInput;
		if (dirInput == 1) // Player moving up 
		{
			newX = -1;
		}

		else if (dirInput == 2) // Player moving down 
		{
			newX = 1;
		}

		else if (dirInput == 3) // Player moving left 
		{
			newY = -1;

		}

		else if (dirInput == 4) // Player moving right 
		{
			newY = 1;

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
			cout << "\nWhich Direction?\n1. Top-Left\n2. Top-Right\n3. Bottom-Left\n4. Bottom-Right\n5. Back to menu\n"; // This is no option for 5. as it is set as the default 
			cin >> dirInput;

			if (dirInput == 1) // Top Left
			{
				newX = -1;
				newY = -1;
				diagDash -= 1;
			}

			else if (dirInput == 2) // Top Right
			{
				newX = -1;
				newY = 1;
				diagDash -= 1;
			}

			else if (dirInput == 3) // Bottom Left
			{
				newX = 1;
				newY = -1;
				diagDash -= 1;

			}

			else if (dirInput == 4) // Bottom Right
			{
				newX = 1;
				newY = 1;
				diagDash -= 1;

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

		//Moves Player & Checks for enemies
		if (map[adventurerList[gameTurn][1] + newX][adventurerList[gameTurn][2] + newY] != 'A' && map[adventurerList[gameTurn][1] + newX][adventurerList[gameTurn][2] + newY] != '#')
		{
			map[adventurerList[gameTurn][1]][adventurerList[gameTurn][2]] = '-';
			adventurerList[gameTurn][1] += newX;
			adventurerList[gameTurn][2] += newY;
		}

		else
		{
			cout << endl;
			cout << "!!The Enemy is blocking your path!!\n";
			moveCounter++;
		}





	

}

void markMap()
{

	for (int x = 0; x < 6; x++)
	{
		cout << "\n";
		for (int y = 0; y < 8; y++)
		{
			for (int i = 0; i < 4; i++)
			{
				if (x == adventurerList[i][1] && y == adventurerList[i][2])
				{
					map[x][y] = 'A';
				}
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
		if ((gameTurn == 0) || (gameTurn == 1)) {
			cout << '\n' << adventurerNameList[gameTurn] << ", What would you like to do?\n1. Move\n2. Attack\n3. Push\n4. Drink a recovery Potion: " << player1PotionCounter << " left. \n";
		}
		if ((gameTurn == 2) || (gameTurn == 3)) {
			cout << '\n' << adventurerNameList[gameTurn] << ", What would you like to do?\n1. Move\n2. Attack\n3. Push\n4. Drink a recovery Potion: " << player2PotionCounter << " left. \n";
		}
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
			AdventurerItems();
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

void repeatTurn() {
	for (int i = 0; i < 2; i++) {
		player1TotalHealth = player1TotalHealth + adventurerList[i][0];
	}

	for (int i = 2; i < 4; i++) {
		player2TotalHealth = player2TotalHealth + adventurerList[i][0];
	}
}

void pickingWinners() {
	if (player1TotalHealth <= 0) {
		for (int i = 0; i < 20; i++) {
			cout << "\nPlayer 2 WINS\n!!";
		}
	}

	if (player2TotalHealth <= 0) {
		for (int i = 0; i < 20; i++) {
			cout << "\nPlayer 1 WINS\n!!";
		}
	}
}

int main()
{
	srand(time(NULL)); // This is used to make random numbers. Seed 2 is a good one to use for the presentation 
	startUp(); // Starts up the gameboard
	markMap();
	do {
		if (gameTurn > 3) { // Resets the counter so it doesn't break the program
			gameTurn = 0;
		}
		cout << gameTurn << '\n';
		if (adventurerList[gameTurn][0] > 0) {
			player1TotalHealth = 0; // Used to reset the counter
			player2TotalHealth = 0; // Used to reset the counter

			playerTurn();
			repeatTurn();
		}
		gameTurn++;
	} while ((player1TotalHealth > 0) && (player2TotalHealth > 0)); // Checks if the total health pool of the teams have not reached 0 yet

	pickingWinners();
}
