#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

int numbers[4][4] = {};//The two dimentional array to store the numbers
int tempUnit[4] = {};//For function move()
unsigned score = 0;
int validity = 0;//The validity of the user's move(0 represent invalidity and 1 represent validity)
char option = 0;//The option of the user
ofstream logfile("2048Game.log");//The log file

void morge(void);
void printNums(void);
bool isAlive(void);
bool canEliminate(void);
int zeroNum(void);
void addRandom(void);
void move(void);
void merge(void);

int main() {
	//Specify the rules of the game
	cout << "//By DerekDick v1.0" << endl 
		<< "Welcome to 2048 Game!" << endl
		<< "Press w/a/s/d and enter key to move the blocks." << endl
		<< "For example, if you want to move left, just press \"a\" and the enter key." << endl;
	
	//Initalization
	addRandom();
	addRandom();
	printNums();

	//Turns in loops
	while (cin >> option) {
		//Check if the player is dead
		if (!isAlive()) {
			system("color fc");
			cout << "You lose!!!\a" << endl;
			break;
		}

		morge();
		if (validity)
			addRandom();
		validity = 0;
		system("cls");
		printNums();
	}

	system("pause");

	return 0;
}

void morge(void) {
	//This function is used to morge(move and merge) the number blocks
	switch (option) {
	case 'w':
		for (int j = 0; j <= 3; j++) {
			for (int i = 0, k = 0; i <= 3; i++) {
				tempUnit[k++] = numbers[i][j];
			}

			move();
			merge();
			move();

			for (int i = 0, k = 0; i <= 3; i++) {
				numbers[i][j] = tempUnit[k++];
			}
		}
		break;
	case 'a':
		for (int i = 0; i <= 3; i++) {
			for (int j = 0, k = 0; j <= 3; j++) {
				tempUnit[k++] = numbers[i][j];
			}

			move();
			merge();
			move();

			for (int j = 0, k = 0; j <= 3; j++) {
				numbers[i][j] = tempUnit[k++];
			}
		}
		break;
	case 's':
		for (int j = 0; j <= 3; j++) {
			for (int i = 3, k = 0; i >= 0; i--) {
				tempUnit[k++] = numbers[i][j];
			}

			move();
			merge();
			move();

			for (int i = 3, k = 0; i >= 0; i--) {
				numbers[i][j] = tempUnit[k++];
			}
		}
		break;
	case 'd':
		for (int i = 0; i <= 3; i++) {
			for (int j = 3, k = 0; j >= 0; j--) {
				tempUnit[k++] = numbers[i][j];
			}

			move();
			merge();
			move();

			for (int j = 3, k = 0; j >= 0; j--) {
				numbers[i][j] = tempUnit[k++];
			}
		}
		break;
	default:
		system("color cf");
		cout << "Illegal input!!!\a" << endl;
	}
	system("color 0a");
	system("color");
	return;
}

void printNums(void) {
	//This function is used to print out the blocks of numbers
	int i, j;
	for (i = 0; i <= 3; i++) {
		for (j = 0; j <= 3; j++) {
			if (numbers[i][j] != 0) {
				cout << setw(6) << numbers[i][j] << ' ';
				logfile << setw(6) << numbers[i][j] << ' ';
			}
			else {
				printf("       ");
				logfile << "       ";
			}
		}
		cout << endl;
		logfile << endl;
	}
	cout << "Score: " << score << endl;
	logfile << option << " Score = " << score << endl;
	logfile << "------------------------------" << endl;

	return;
}

bool isAlive(void) {
	//This function is used to check if the player is still alive
	if (zeroNum()) {
		return true;
	}
	else if (canEliminate()) {
		return true;
	}
	else
		return false;
}

bool canEliminate(void) {
	//This function is used to check if the number blocks(BLOCLED!!!) can be eliminated
	//Rows
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 2; j++) {
			if (numbers[i][j] == numbers[i][j + 1])
				return true;
		}
	}

	//Columns
	for (int i = 0; i <= 2; i++) {
		for (int j = 0; j <= 3; j++) {
			if (numbers[i][j] == numbers[i + 1][j])
				return true;
		}
	}

	return false;
}

int zeroNum(void) {
	//This function is used to count the number of zeroes in the number block
	int count = 0;
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			if (numbers[i][j] == 0)
				count++;
		}
	}
	return count;
}

void addRandom(void) {
	//This function is used to add one 2 into a random empty place
	srand(int(time(0)));//Random seed
	int index = rand() % zeroNum();
	int position = 0;
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			if (numbers[i][j] == 0) {
				if (position == index) {
					numbers[i][j] = 2;
					return;
				}
				position++;
			}
		}
	}
	return;
}

void move(void) {
	int current = -1, count = 0;
	//Positioning the first zero in this unit
	for (int i = 0; i <= 2; i++) {
		if (tempUnit[i] == 0) {
			current = i;
			break;
		}
	}

	//No zeroes in this unit
	if (current == -1) {
		return;
	}

	//Move the zero(es) back
	for (; current <= 2; ) {
		if (tempUnit[current + 1] == 0) {
			count++;
			current++;
		}
		else {
			validity = 1;
			tempUnit[current - count] = tempUnit[current + 1];
			current++;
			for (int k = current - count; k <= current; k++)
				tempUnit[k] = 0;
		}
	}

	return;
}

void merge(void) {
	for (int i = 0; i <= 2; i++) {
		if (tempUnit[i] != 0) {
			if (tempUnit[i + 1] == tempUnit[i]) {
				validity = 1;
				tempUnit[i] = tempUnit[i + 1] + tempUnit[i];
				score += tempUnit[i];
				tempUnit[i + 1] = 0;
				i++;
			}
		}
		else
			break;
	}

	return;
}