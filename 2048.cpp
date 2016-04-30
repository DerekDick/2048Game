#pragma warning(disable:4996)

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

int numbers[4][4] = {}; //The two dimentional array to store the numbers
int tempUnit[4] = {}; //For function move()
unsigned score = 0;
int validity = 0; //The validity of the user's move(0 represent invalidity and 1 represent validity)
char option = 0; //The option of the user
std::string username;
std::ofstream logfile("2048Game.log"); //The log file
std::ofstream record("2048record.txt", std::ios::app); //The record file
//ofstream userInfo("userInfo.xxx", ios::app); //The users' information
char* currentLocalTime();

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
	std::cout << "By DerekDick" << std::endl 
		<< "Welcome to 2048 Game version2.0!" << std::endl
		<< "Press w/a/s/d and enter key to move the blocks." << std::endl
		<< "For example, if you want to move left, just press \"a\" and the enter key." << std::endl;
	
	//Get the user's name
	std::cout << "Please type in your name(no longer than 16 characters):" << std::endl;
	while (std::cin >> username) {
		if (username.length() <= 16)
			break;
		else
			std::cout << "The name is too longer! Please try another shorter name:\a" << std::endl;
	}

	//Initalization
	addRandom();
	addRandom();
	printNums();

	//Turns in loops
	while (std::cin >> option) {
		//Check if the player is dead
		if (!isAlive()) {
			system("color fc");
			std::cout << "You lose!!!\a" << std::endl;
			break;
		}

		morge();
		if (validity)
			addRandom();
		validity = 0;
		system("cls");
		printNums();
	}

	//Write the result into the record file
	record << std::setw(16) << std::left << username << ' ' << std::setw(6) << std::right << score << std::endl;

	logfile.close();
	record.close();

	//Rename the log file according to the current time
	std::string newlogname = username + currentLocalTime() + ".log";
	rename("2048Game.log", newlogname.c_str());
	logfile.close();

	system("pause");

	return 0;
}

void morge(void) {
	/*This function is used to morge(move and merge) the number blocks*/
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
		std::cout << "Illegal input!!!\a" << std::endl;
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
				std::cout << std::setw(6) << numbers[i][j] << ' ';
				logfile << std::setw(6) << numbers[i][j] << ' ';
			}
			else {
				printf("       ");
				logfile << "       ";
			}
		}
		std::cout << std::endl;
		logfile << std::endl;
	}
	std::cout << "Score: " << score << std::endl;
	logfile << option << " Score = " << score << std::endl;
	logfile << "------------------------------" << std::endl;

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

char* currentLocalTime() {
	/*This function is used to get the current local time*/
	const time_t t = time(0);
	struct tm* now = localtime(&t);
	static char currentTime[14] = "";
	sprintf(currentTime, "%04d%02d%02d%02d%02d%02d", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec);

	return currentTime;
}
