#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
// set the terminal cursor to position x, y
#define move(y,x) printf("\033[%d;%dH", x, y)
#define clear printf(" ")

// basic datastructure to store all kinds of game objects
struct GameObject {
    int posX;
    int posY;
    const char* symbol;
    const char* name;
    int health;
    struct GameObject* next;
};

/* global variables
 * yOff == # of "\n"" printed in the beginning in function main()
 *  - important for move macro
 */
const unsigned int cols = 20;
const unsigned int rows = 10;
const unsigned int yOff = 4;
struct GameObject* player = NULL;
struct GameObject* monsters = NULL;

// move a game object to a new position and display it on the screen
void moveGameObject(struct GameObject* obj, unsigned int x, unsigned int y) {
    if(!obj)
        return;
    // object must stay inside the dungeon
    if (x >= cols || y >= rows || x < 0 || y < 0)
        return;
    // clear the old position
	move(obj->posX + 2, obj->posY + 2 + yOff);
	clear;
    obj->posX = x;
    obj->posY = y;
    // print the object at the new position
	move(obj->posX + 2, obj->posY + 2 + yOff);
	printf("%c", *(obj->symbol));
    // get the cursor out of the dungeon
    move(0,rows+yOff+3);
}

// append a new monster to the existing list of monsters
void addMonster(int health, char* name, char* symbol, int posX, int posY) {
    static struct GameObject* latestMonster = NULL;
    // allocate memory for and initialize the monster
    struct GameObject* newMonster =
       (struct GameObject*) malloc(sizeof(struct GameObject));
    if (newMonster == NULL)
        exit(EXIT_FAILURE);
    newMonster->health = health;
    newMonster->name = name;
    newMonster->symbol = symbol;
    newMonster->posX = posX;
    newMonster->posY = posY;
    newMonster->next = NULL;
    // move it to its position in order to display it
    moveGameObject(newMonster, posX, posY);
    // if no monster has been added yet, begin with the head of the list
    if (latestMonster == NULL) {
        latestMonster = newMonster;
        monsters = latestMonster;
    }
    // we have a new latest monster
    else {
        latestMonster->next = newMonster;
        latestMonster = latestMonster->next;
    }
}

// display a visual representation of the dungeon in the terminal
void drawBoard(void) {
	unsigned int i, j;
    // draw the top border
	for (i = 0; i < cols+2; i++)
		printf("-");
	printf("\n");
    // draw all the rows where objects can move to
	for (j = 0; j < rows; j++) {
		printf("|");
		for(i = 0; i < cols; i++)
			printf(" ");
		printf("|\n");
	}
    // draw the bottom border
	for (i = 0; i < cols+2; i++)
		printf("-");
	printf("\n");
}

// create the player and monster objects
void setUpGame() {
    struct GameObject* newMonster = NULL;
    // init the player
    player = (struct GameObject*) malloc(sizeof(*player));
    if (player) {
        player->health = 100;
        player->name = "Jack Black";
        player->symbol = "J";
        player->next = NULL;
        player->posX = 3;
        player->posY = 5;
        moveGameObject(player, player->posX, player->posY);

    }
    else
        exit(EXIT_FAILURE);
    // add some Monsters
    addMonster(100, "Aaargghh!!!", "x", 8, 8);
    addMonster(100, "Kevin", "$", 0, 0);
}

// check user input
void handleInput(char input, int *running) {
    switch (input | 0x20) { // 0x20 is 32 in dec => allow for great letters as well
        case 'x':
            // x key means "exit game"
            *running = 0;
            break;
        // if one of WASD was pressed, move the player into the appropriate direction
        case 'w':
            moveGameObject(player, player->posX, player->posY - 1);
            break;
        case 's':
            moveGameObject(player, player->posX, player->posY + 1);
            break;
        case 'a':
            moveGameObject(player, player->posX - 1, player->posY);
            break;
        case 'd':
            moveGameObject(player, player->posX + 1, player->posY);
            break;
    }
}

// free all memory we have allocated
void shutDownGame() {
    struct GameObject* deletedMonster = NULL;
    // free the memory of struct GameObject player
    if (player)
        free(player);
    // free the list of monsters
    for (deletedMonster = monsters;
         deletedMonster != NULL;
         deletedMonster = monsters->next, monsters = monsters->next)
        free(deletedMonster);
}

int main() {
	system("clear");
    printf("\n============================================\n");
    printf("2D Retro Dungeon\n");
    printf("============================================\n");

    int running = 1;
    char input;

	drawBoard();
    setUpGame();

    /* main loop
     * while the game is running, check for input
     */
    while (running) {
        // if there was hit no key, check again
		if (!kbhit)
           continue;
        // there was hit a key, read it as a single letter from the standard
        // input
        input = getch();
        // now handle that input ;-)
        handleInput(input, &running);
    }

    shutDownGame();
    return 0;
}
