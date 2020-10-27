//Sokorogue by GDW Group 8
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

//Consumables
int player1PotionCounter = 1; // This is used to keep track of the amount of potions player 1 has
int player2PotionCounter = 1; // This is used to keep track of the amount of potions player 2 has

int diagDash1 = 3; // Counters for storing diagonal dash
int diagDash2 = 3;

int swingAtt1 = 1;
int swingAtt2 = 1;

int rangedAtt1 = 1;
int rangedAtt2 = 1;

int adventurerList[4][3]{ // First slot is the Health, second and third slot is the X and Y coordinates
	{6,2,1},
	{6,4,2},
	{6,1,6},
	{6,1,5},
};


//Attack Items
string attacks[] = { "Jab Attack", "Ranged Attack", "Swing Attack" };




void startUp() {

	for (int i = 0; i < 2; i++) { // Adventurers' names under Player 1's control
		cout << "\nPlayer 1, Please enter the name of Adventurer #" << i + 1 << ".\n";
		cin >> adventurerNameList[i]; // Use gameTurn to repersent the array numbers
	}
	cout << "\n";
	for (int i = 2; i < 4; i++) { // Adventurers' names under Player 2's control
		cout << "\nPlayer 2, Please enter the name of Adventurer #" << i + 1 << ".\n";
		cin >> adventurerNameList[i]; // Use gameTurn to repersent the array numbers
	}
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
	int obstacleNumber = rand() % 8 + 4;  // Determines the number of obstacles
	
	cout << "Obstacles: " << obstacleNumber << endl;
	do {
		int x = rand() % 5 ; // Determines the vertical coordinate
		int y = rand() % 7; // Determines the horizonal coordinate
		//cout << x << y<< " ";
		int check = 0; // used to check the x and y cooridinates of the adventurers
		for (int i = 0; i <= 3; i++) {
			if ((x != adventurerList[i][1]) && (y != adventurerList[i][2]) && (map[x][y] != '#')) {
				check++; // Checks if there is nothing overlapping
			}
		}
		if (check == 3) {
			map[x][y] = '#'; // Enters in the obstacale
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

	//Setting Direction of Attack
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
	//cout << map[enemyPosX][enemyPosY] << endl; // Debugging

	for (int i = 0; i < 4; i++) {
		if ((adventurerList[i][1] == enemyPosX) && (adventurerList[i][2] == enemyPosY)) // This is used check if the position of the enemy player 
		{
			cout << "\nYou attacked the enemy for 2 DMG!\n";
			adventurerList[i][0] = adventurerList[i][0] - 2; // Inflict 2 damage
			cout << adventurerNameList[i] << " has " << adventurerList[i][0] << " health left!\n";

			if (adventurerList[i][0] <= 0) 
			{
				map[enemyPosX][enemyPosY] = '-';
				cout << adventurerNameList[i] << " has " << "died!\n";
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
		if ((gameTurn == 0) || (gameTurn == 1)) 
		{
			if (rangedAtt1 > 0)
			{
				rangedAtt1--;
			}
		}

		if ((gameTurn == 2) || (gameTurn == 3))
		{
			if (rangedAtt2 > 0)
			{
				rangedAtt2--;
			}
		}

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
							adventurerList[j][0] = adventurerList[j][0] - 4; // Inflict 4 damage
							if (adventurerList[j][0] <= 0) {
								int tempX2 = adventurerList[j][1]; // used from erasing the char off the map
								int tempY2 = adventurerList[j][2]; // used from erasing the char off the map
								cout << adventurerNameList[j] << " has " << "died!\n";
								map[tempX2][tempY2] = '-';
								adventurerList[j][0] = 0; // Prevents the health from being in the negative, as it will affect the win
							}
							else
							{
								cout << adventurerNameList[j] << " has " << adventurerList[j][0] << " left!";
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
							cout << adventurerNameList[j] << " has " << adventurerList[j][0] << " left!";
							adventurerList[j][0] = adventurerList[j][0] - 4; // Inflict 3 damage
							if (adventurerList[j][0] <= 0) {
								int tempX2 = adventurerList[j][1]; // used from erasing the char off the map
								int tempY2 = adventurerList[j][2]; // used from erasing the char off the map
								cout << adventurerNameList[j] << " has " << "died!\n";
								map[tempX2][tempY2] = '-';
								adventurerList[j][0] = 0; // Prevents the health from being in the negative, as it will affect the win
							}
							else
							{
								cout << adventurerNameList[j] << " has " << adventurerList[j][0] << " left!";
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
							cout << adventurerNameList[j] << " has " << adventurerList[j][0] << " left!";
							adventurerList[j][0] = adventurerList[j][0] - 4; // Inflict 3 damage
							if (adventurerList[j][0] <= 0) {
								int tempX2 = adventurerList[j][1]; // used from erasing the char off the map
								int tempY2 = adventurerList[j][2]; // used from erasing the char off the map
								cout << adventurerNameList[j] << " has " << "died!\n";
								map[tempX2][tempY2] = '-';
								adventurerList[j][0] = 0; // Prevents the health from being in the negative, as it will affect the win
							}
							else
							{
								cout << adventurerNameList[j] << " has " << adventurerList[j][0] << " left!";
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
							cout << adventurerNameList[j] << " has " << adventurerList[j][0] << " left!";
							adventurerList[j][0] = adventurerList[j][0] - 4; // Inflict 3 damage
							if (adventurerList[j][0] <= 0) {
								int tempX2 = adventurerList[j][1]; // used from erasing the char off the map
								int tempY2 = adventurerList[j][2]; // used from erasing the char off the map
								cout << adventurerNameList[j] << " has " << "died!\n";
								map[tempX2][tempY2] = '-';
								adventurerList[j][0] = 0; // Prevents the health from being in the negative, as it will affect the win
							}
							else
							{
								cout << adventurerNameList[j] << " has " << adventurerList[j][0] << " left!";
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

	if ((gameTurn == 0) || (gameTurn == 1))
	{
		if (swingAtt1 > 0)
		{
			swingAtt1--;
		}
	}

	if ((gameTurn == 2) || (gameTurn == 3))
	{
		if (swingAtt2 > 0)
		{
			swingAtt2--;
		}
	}

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
							cout << "\nYou attacked the enemy for 4 DMG!\n";
							adventurerList[i][0] = adventurerList[i][0] - 4; // Inflict 4 damage
							cout << adventurerNameList[i] << " has " << adventurerList[i][0] << " left!";
							if (adventurerList[i][0] <= 0) {
								int tempX2 = adventurerList[i][1]; // used from erasing the char off the map
								int tempY2 = adventurerList[i][2]; // used from erasing the char off the map
								cout << adventurerNameList[i] << " has " << "died!\n";
								map[tempX2][tempY2] = '-';
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
		if ((gameTurn == 2) || (gameTurn == 3))
		{
			if (rangedAtt2 > 0)
			{
				rangedAttack();
			}

			else
			{

				cout << "You have run out of this item.";
				moveCounter++;
			}

		}

		else if ((gameTurn == 0) || (gameTurn == 1))
		{
			if (rangedAtt1 > 0)
			{
				rangedAttack();
			}


			else
			{

				cout << "You have run out of this item.";
				moveCounter++;
			}

		}
		
	}

	else if (input - 1 == 2)
	{
		if ((gameTurn == 2) || (gameTurn == 3))
		{
			if (swingAtt2 > 0)
			{
				swingAttack();
			}

			else
			{

				cout << "You have run out of this item.";
				moveCounter++;
			}

		}

		else if ((gameTurn == 0) || (gameTurn == 1))
		{
			if (swingAtt1 > 0)
			{
				swingAttack();
			}


			else
			{

				cout << "You have run out of this item.";
				moveCounter++;
			}
		}
	}

	else
	{
		moveCounter++;
	}
}

void AdventurerItems() { 
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
	int dirInput;
	int newX = 0, newY = 0;
	cout << "\nPush at what direction?\n1. Up\n2. Down\n3. Left\n4. Right\n5. Back to menu\n"; // This is no option for 5. as it is set as the default 
	cin >> dirInput;
	if (dirInput == 1) // Player moving up 
	{
		newX = -1;
		if (map[adventurerList[gameTurn][1] + newX][adventurerList[gameTurn][2] + newY] == '#')
		{
			char temp = 'I';
			int counter = 0;

			while (true) // counts how many objects will be pushed
			{
				temp = map[adventurerList[gameTurn][1] + (counter * newX)][adventurerList[gameTurn][2] + (counter * newY)]; //stores the current char being checked
				if (temp == '-')
				{
					break;

				}
				counter++;
			}

			int baseX = adventurerList[gameTurn][1] - counter + 1; //Stores the x value the next for loop with start checking from
			if (baseX == 0) //Check to makes sure objects won't go out of bounds
			{
				for (baseX; baseX <= adventurerList[gameTurn][1]; baseX++) //Moves the objects to their new position
				{
					temp = map[baseX][adventurerList[gameTurn][2]];
					if (temp == '#')
					{

						map[baseX - 1][adventurerList[gameTurn][2]] = temp;
					}

					for (int i = 0; i <= 3; i++)
					{
						if (temp == (char)adventurerNameList[i].front())
						{
							map[baseX][adventurerList[i][2]] = '-';
							adventurerList[i][1]--;

						}

					}

				}
			}
			else
			{
				cout << "\nYou stopped yourself from pushing the box off the edge\n";
				moveCounter++;
			}
		}
		else
		{
			cout << endl;
			cout << "!!Well Done, you pushed at thin air! (action point refunded)!!\n";
			moveCounter++;
		}
	}

	else if (dirInput == 2) // Player moving down 
	{
		newX = 1;
		if (map[adventurerList[gameTurn][1] + newX][adventurerList[gameTurn][2] + newY] == '#')
		{
			char temp = 'I';
			int counter = 0;

			while (true)
			{
				temp = map[adventurerList[gameTurn][1] + (counter * newX)][adventurerList[gameTurn][2] + (counter * newY)]; 
				if (temp == '-')
				{
					break;

				}
				counter++;
			}
			
			int baseX = counter + adventurerList[gameTurn][1] - 1;
			if (baseX < 5)
			{
				for (baseX; baseX >= adventurerList[gameTurn][1]; baseX--)
				{
					temp = map[baseX][adventurerList[gameTurn][2]];
					if (temp == '#')
					{

						map[baseX + 1][adventurerList[gameTurn][2]] = temp;
					}

					for (int i = 0; i <= 3; i++)
					{
						if (temp == (char)adventurerNameList[i].front())
						{
							map[baseX][adventurerList[i][2]] = '-';
							adventurerList[i][1]++;

						}

					}

				}
			}
			else
			{
				cout << "\nYou stopped yourself from pushing the box off the edge\n";
				moveCounter++;
			}
		}
		else
		{
			cout << endl;
			cout << "!!Well Done, you pushed at thin air! (action point refunded)!!\n";
			moveCounter++;
		}
	}
	else if (dirInput == 3) // Player moving left 
	{
		newY = -1;

		if (map[adventurerList[gameTurn][1] + newX][adventurerList[gameTurn][2] + newY] == '#')
		{
			char temp = 'I';
			int counter = 0;

			while (true)
			{
				temp = map[adventurerList[gameTurn][1] + (counter * newX)][adventurerList[gameTurn][2] + (counter * newY)]; 
				if (temp == '-')
				{
					break;

				}
				counter++;
			}

			int baseY = adventurerList[gameTurn][2] - counter + 1;
			if (baseY > 0)
			{
				for (baseY; baseY <= adventurerList[gameTurn][2]; baseY++)
				{
					temp = map[adventurerList[gameTurn][1]][baseY];
					if (temp == '#')
					{

						map[adventurerList[gameTurn][1]][baseY - 1] = temp;
					}

					for (int i = 0; i <= 3; i++)
					{
						if (temp == (char)adventurerNameList[i].front())
						{
							map[adventurerList[i][1]][baseY] = '-';
							adventurerList[i][2]--;

						}

					}

				}
			}
			else
			{
				cout << "\nYou stopped yourself from pushing the box off the edge\n";
				moveCounter++;
			}
		}

		else
		{
			cout << endl;
			cout << "!!Well Done, you pushed at thin air! (action point refunded)!!\n";
			moveCounter++;
		}

	}
	else if (dirInput == 4) // Player moving right 
	{
		newY = 1;
		
		if (map[adventurerList[gameTurn][1] + newX][adventurerList[gameTurn][2] + newY] == '#')
		{
			char temp = 'I';
			int counter = 0;

			while (true)
			{
				temp = map[adventurerList[gameTurn][1] + (counter * newX)][adventurerList[gameTurn][2] + (counter * newY)]; 
				if (temp == '-')
				{
					break;

				}
				counter++;
			}

			int baseY = counter + adventurerList[gameTurn][2] - 1;
			if (baseY < 7)
			{

				for (baseY; baseY >= adventurerList[gameTurn][2]; baseY--)
				{
					temp = map[adventurerList[gameTurn][1]][baseY];
					if (temp == '#')
					{

						map[adventurerList[gameTurn][1]][baseY + 1] = temp;
					}

					for (int i = 0; i <= 3; i++)
					{
						if (temp == (char)adventurerNameList[i].front())
						{
							map[adventurerList[i][1]][baseY] = '-';
							adventurerList[i][2]++;

						}

					}

				}
			}

			else
			{
				cout << "\nYou stopped yourself from pushing the box off the edge\n";
				moveCounter++;
			}
		}
		else
		{
			cout << endl;
			cout << "!!Well Done, you pushed at thin air! (action point refunded)!!\n";
			moveCounter++;
		}
	}
	else // Player chose to go back to the menu 
	{
		moveCounter++;
	}


}


void move()
{
	cout << gameTurn;
	int moveInput;
	int newX = 0, newY = 0;
	char firstLetter = adventurerNameList[gameTurn].front(); // This gets the first letter of a string

	if ((gameTurn == 0) || (gameTurn == 1)) {
		cout << "\nWhat Type of Movement?\n1. Standard Walk\n2. Diagonal Dash: " << diagDash1 << "\n";
	}
	else if ((gameTurn == 2) || (gameTurn == 3)) {
		cout << "\nWhat Type of Movement?\n1. Standard Walk\n2. Diagonal Dash: " << diagDash2 << "\n";
	}
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
	}

	else if (moveInput == 2)
	{
		if ((gameTurn == 0) || (gameTurn == 1)) {
			if (diagDash1 > 0)
			{
				int dirInput;
				cout << "\nWhich Direction?\n1. Top-Left\n2. Top-Right\n3. Bottom-Left\n4. Bottom-Right\n5. Back to menu\n"; // This is no option for 5. as it is set as the default 
				cin >> dirInput;
				if (dirInput == 1) // Top Left
				{
					newX = -1;
					newY = -1;
					diagDash1 -= 1;
				}
				else if (dirInput == 2) // Top Right
				{
					newX = -1;
					newY = 1;
					diagDash1 -= 1;
				}
				else if (dirInput == 3) // Bottom Left
				{
					newX = 1;
					newY = -1;
					diagDash1 -= 1;

				}
				else if (dirInput == 4) // Bottom Right
				{
					newX = 1;
					newY = 1;
					diagDash1 -= 1;

				}
			}
			else
			{
				cout << "You have run out of this item.";
			}
		}
		else if ((gameTurn == 2) || (gameTurn == 3)) {
			if (diagDash2 > 0)
			{
				int dirInput;
				cout << "\nWhich Direction?\n1. Top-Left\n2. Top-Right\n3. Bottom-Left\n4. Bottom-Right\n5. Back to menu\n"; // This is no option for 5. as it is set as the default 
				cin >> dirInput;
				if (dirInput == 1) // Top Left
				{
					newX = -1;
					newY = -1;
					diagDash2 -= 1;
				}
				else if (dirInput == 2) // Top Right
				{
					newX = -1;
					newY = 1;
					diagDash2 -= 1;
				}
				else if (dirInput == 3) // Bottom Left
				{
					newX = 1;
					newY = -1;
					diagDash2 -= 1;

				}
				else if (dirInput == 4) // Bottom Right
				{
					newX = 1;
					newY = 1;
					diagDash2 -= 1;

				}
			}
			else
			{
				cout << "You have run out of this item.";
				moveCounter++;
			}
		}
	}
	int check = 0; // A counter used to check player positions, and used to check if the player has wandered off the map
	//Moves Player & Checks for enemies
	for (int i = 0; i < 4; i++) {
		firstLetter = adventurerNameList[i].front(); // Checks for every adventurer's first letter
		if (map[adventurerList[gameTurn][1] + newX][adventurerList[gameTurn][2] + newY] != firstLetter) {
			check++;
		}
	}

	int tempX = adventurerList[gameTurn][1] + newX;
	int tempY = adventurerList[gameTurn][2] + newY;
	if ((tempX == -1) || (tempX == 6) || (tempY == -1) || (tempY == 8)) { // Checks of the player has wandered off the map 
		check = 0;
		cout << '\n' << adventurerNameList[gameTurn] << ", you've wandered too far from the battlefield!\n";
	}

	if ((check == 4) && (map[adventurerList[gameTurn][1] + newX][adventurerList[gameTurn][2] + newY] != '#')) // Only moves if there are no players or obstacles in the active player's way
	{
		map[adventurerList[gameTurn][1]][adventurerList[gameTurn][2]] = '-';
		adventurerList[gameTurn][1] += newX;
		adventurerList[gameTurn][2] += newY;
		firstLetter = adventurerNameList[gameTurn].front(); // Overrides the original variable, as it has been changed 
		map[adventurerList[gameTurn][1]][adventurerList[gameTurn][2]] = firstLetter;
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
					char firstLetter = adventurerNameList[i].front(); // This gets the first letter of a string
					map[x][y] = firstLetter;
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
		cout <<"\n" << moveCounter << " Moves Remaining.";
		cout << "\n" << adventurerList[gameTurn][0] << " HP Remaining.";
		if ((gameTurn == 0) || (gameTurn == 1)) {
			cout << '\n' << adventurerNameList[gameTurn] << ", What would you like to do?\n 1. Move\n 2. Attack\n 3. Push\n 4. Drink a recovery Potion: " << player1PotionCounter << " left. \n";
		}
		if ((gameTurn == 2) || (gameTurn == 3)) {
			cout << '\n' << adventurerNameList[gameTurn] << ", What would you like to do?\n 1. Move\n 2. Attack\n 3. Push\n 4. Drink a recovery Potion: " << player2PotionCounter << " left. \n";
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
			push();
			moveCounter--;
		}

		else if (input == 4)
		{
			AdventurerItems();
			moveCounter--;

		}

		else
		{
			
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
	srand(time(NULL)); // This is used to make random numbers
	startUp(); // Starts up the gameboard
	markMap();
	do {
		if (gameTurn > 3) { // Resets the counter so it doesn't break the program
			gameTurn = 0;
		}
		//cout << gameTurn << '\n';
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

