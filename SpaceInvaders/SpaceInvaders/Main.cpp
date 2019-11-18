
#include <string>
#include <conio.h>
#include <algorithm>
#include <iostream>

const int width = 77;
const int height = 4;
int zombieBoard[height][width] = { 0 }; //0 is empty, 2 reps zombie shots, 4 reps zombies
std::string zombieShow[height][width] = { " " };
int zombMin = 0; //furthest left position of zombies
int zombMax = 0; //furthest right position of zombies
int zombCount = 1;
int zombieSpeed = 10000;
int current = 0;
bool moveForward = true; //true if zombies are moving to the right, false if left


int playerX = 0;
int playerPos[width] = { 0 }; //0 is empty, 1 reps bullets, 3 reps ship
std::string playerShow[width] = { " " };


std::string zombieMem = "(v)";
std::string playerMem = "[X]";

bool intro;
bool game = true;

int key = 0;

void initPlayer() {
	playerPos[playerX] = 3;
	playerShow[playerX] = playerMem; //center of ship
}

void initZombies() {
	zombieBoard[0][0] = 4;
}

void playerInput() {
	key = _getch();
	if (key == 0 ||key == 224) {
		switch (_getch()) {
		case 75: //Left
			if (playerX > 0) {
				playerX--;
			}
			break;

		case 77: //Right
			if (playerX < width -1) {
				playerX++;
			}
			break;
			
		}
	}
}

void updatePlayer() {
	for (int i = 0; i < width; i++) {
		playerPos[i] = 0;
	}
	playerPos[playerX] = 3; //center of ship

	for (int i = 0; i < width; i++) {
		switch (playerPos[i]) {
		case 0:
			playerShow[i] = " ";
			break;
		case 3:
			playerShow[i] = playerMem;
			break;
		}
	}
}

void zombieMove() {
	if (moveForward && (zombMax+1 == width) ) {
		moveForward = false;
		//move down
	}
	else if (!moveForward && (zombMin == 0) ){
		moveForward = true;
		//move down
	}else {
		if (moveForward) {

			for (int j = height - 1; j > 0; j--) {
				for (int i = width - 1; i > 0; i--) {
					if (i < width - 1) {
						zombieBoard[j][i + 1] = zombieBoard[j][i];
					}
					//set left column to empty
				}
			}

		}
		else if (!moveForward) {
			//move left
		}
	}
}

void updateEnemy() {
	if (current < zombieSpeed) {
		current++;
	}
	else if (current >= zombieSpeed){
		current = 0;
		zombieMove();
	}

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			switch (zombieBoard[j][i]) {
			case 0:
				zombieShow[j][i] = " ";
				break;
			case 1:
				//player bullets
				break;
			case 2:
				//zombie bullets
				break;
			case 4:
				zombieShow[j][i] = zombieMem;
			}
		}
	}
}

void gameLoop() {
	key = 0;
	playerInput();
	updatePlayer();
	updateEnemy();
	
}

void drawGame() {
	system("cls"); //clear output
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			std::cout << zombieShow[j][i];
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < width; i++) {
		std::cout << playerShow[i];
	}
	std::cout << std::endl;
	std::cout << playerX;
}

int main() {
	
	if (game) {
		initPlayer();
		updateEnemy();
		drawGame();
	}
	while (game) {
		playerInput();
		gameLoop();
		drawGame();
	}

	system("pause");
	return 0;
}