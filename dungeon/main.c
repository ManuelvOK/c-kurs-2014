#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#define move(y,x) printf("\033[%d;%dH", x, y)
#define clear printf(" ")

struct GameObject {
    int posX;
    int posY;
    const char* symbol;
    const char* name;
    int Health;
    struct GameObject* next;
};

/* global variables
 * yOff == # of \n printed in the beginning in function main()
 */
const unsigned int cols = 20;
const unsigned int rows = 10;
const unsigned int yOff = 4;
struct GameObject* pPlayer = NULL;
struct GameObject* pListOfMonsters = NULL;

void moveGameObject(struct GameObject* obj, unsigned int x, unsigned int y) {
    if( !obj)
        return;
    if (x >= cols || y >= rows || x < 0 || y < 0)
        // no one leaves the dungeon!
        return;
	move(obj->posX + 2, obj->posY + 2 + yOff);
	clear;
    obj->posX = x;
    obj->posY = y;
	move(obj->posX + 2, obj->posY + 2 + yOff);
	printf("%c", *(obj->symbol));
    move(0,rows+yOff+3);
}

void addMonster(struct GameObject* newMonster) {
    struct GameObject* pCurrentMonster = NULL;

    if (pListOfMonsters == NULL) {
        // If there are no monsters yet, add the first as the head of the list.
        pListOfMonsters = newMonster;
    }
    else {
        /* If we can access the head of the list, we can easily access all other list elements
         * by using the "next" pointer within each GameObject.
         */
        pCurrentMonster = pListOfMonsters;
        while (pCurrentMonster != NULL ) {
            if (pCurrentMonster->next == NULL) {
                // We reached the last element of the list, append the new one,
                // then break the loop.
                pCurrentMonster->next = newMonster;
                break;
            }
            else {
                // we haven't reached the last element yet, so go on...
                pCurrentMonster = pCurrentMonster->next;
            }
        }
    }
}

void drawBoard(void) {
	unsigned int i, j;
	for (i = 0; i < cols+2; i++)
		printf("-");
	printf("\n");

	for (j = 0; j < rows; j++) {
		printf("|");
		for(i = 0; i < cols; i++)
			printf(" ");
		printf("|\n");
	}

	for (i = 0; i < cols+2; i++)
		printf("-");
	printf("\n");
}

void setUpGame() {
    struct GameObject* newMonster = NULL;

    /* Let's add our hero to the game by allocating the required amount of memory on the HEAP.
     * By doing so, we can access the new "object" through a pointer from where ever we want
     * until we decide to wipe it out again.
     * Remember: If you use malloc(sizeof("whatever")), you must never redirect the pointer
     *           you received from malloc() until you cleared the reserved memory with free().
     *           Otherwise, the reserved memory becomes unreachable, what is pretty bad indeed.
     *           Practice safe coding!!!
     */
    pPlayer = (struct GameObject*) malloc(sizeof(*pPlayer));
    // After malloc(), always check if the allocation process succeeded.
    if (pPlayer) {
        pPlayer->Health = 100;
        pPlayer->name = "Jack Black";
        pPlayer->symbol = "J";
        pPlayer->next = NULL;
        pPlayer->posX = 3;
        pPlayer->posY = 5;
        moveGameObject(pPlayer, pPlayer->posX, pPlayer->posY);

    }
    else {
        /* If the memory allocation process failed for some reason, display an error message.
         * An error message should provide information about where the error occured.
         */
        printf("ERROR: setUpGame(): could not allocate memory for player object.");
    }
    // ----------------- MONSTER'S SECTION BELOW  -----------------
    // now, add the first monster to the list of all monsters. He's the evil boss!
    newMonster = (struct GameObject*) malloc(sizeof(struct GameObject));
    if (newMonster) {
        newMonster->Health = 100;
        newMonster->name = "Aaargghh!!!";
        newMonster->symbol = "x";
        newMonster->next = NULL;
        newMonster->posX = 8;
        newMonster->posY = 8;
        moveGameObject(newMonster, newMonster->posX, newMonster->posY);

        addMonster(newMonster);
    }
    else
        printf("ERROR: setUpGame(): could not allocate memory for monster object.");
    // add another monster to the list.
    newMonster = (struct GameObject*) malloc(sizeof(struct GameObject));
    if (newMonster) {
        newMonster->Health = 100;
        newMonster->name = "Kevin";
        newMonster->symbol = "$";
        newMonster->next = NULL;
        newMonster->posX = 0;
        newMonster->posY = 0;
        moveGameObject(newMonster, newMonster->posX, newMonster->posY);

        addMonster(newMonster);
    }
    else
        printf("ERROR: setUpGame(): could not allocate memory for monster object(s).");
}

void handleInput(int *cinput, int *out_bRunning) {
    if (*cinput == 'x' || *cinput == 'X') {
        *out_bRunning = 0;
        return;
    }
    if (*cinput == 'w' || *cinput == 'W')
        moveGameObject(pPlayer, pPlayer->posX, pPlayer->posY - 1);
    if (*cinput == 's' || *cinput == 'S')
        moveGameObject(pPlayer, pPlayer->posX, pPlayer->posY + 1);
    if (*cinput == 'a' || *cinput == 'A')
        moveGameObject(pPlayer, pPlayer->posX - 1, pPlayer->posY);
    if (*cinput == 'd' || *cinput == 'D')
        moveGameObject(pPlayer, pPlayer->posX + 1, pPlayer->posY);
}

void shutDownGame() {
    struct GameObject* pDeletedMonster = NULL;

    if (pPlayer) {
        free(pPlayer);
        pPlayer = NULL;
    }
    while (pListOfMonsters != NULL ) {
        if( pListOfMonsters->next == NULL) {
            free(pListOfMonsters);
            pListOfMonsters = NULL;
        }
        else {
            // we haven't reached the last remaining element yet, so go on...
            pDeletedMonster = pListOfMonsters;
            // redirect the list entry...
            pListOfMonsters = pListOfMonsters->next;
            // free memory...
            free(pDeletedMonster);
        }
    }

}

int main() {
	system("clear");
    printf("\n============================================\n");
    printf("Tutorium 3, ASCII Dungeon v0.1\n");
    printf("============================================\n");

    int bRunning = 1;
    int cinput;


	drawBoard();
    setUpGame();

    //printf("\nYou are J. Walk the ASCII Dungeon and watch out for the monsters!\n\n");
    //printf("-- Press any key to start --\n");
    //printf("-- Press x to quit --\n");

    while (bRunning) {
		if (!kbhit)
           continue;
        cinput = getch();
        handleInput(&cinput,&bRunning);
    }

    shutDownGame();
    return 0;
}
