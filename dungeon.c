/*
 * main.c
 *
 *  Created on: 12.11.2014
 *      Author: dk
 */
#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#define move(y,x) printf("\033[%d;%dH", x, y)
#define clear printf("")



/* This time, we use no "typedef" modifier. No, NEVER!!!! */
struct GameObject{
    int posX;
    int posY;
    const char* symbol;
    const char* name;
    int Health;
    struct GameObject* next;
}GameObject;

// --- global variables ---
// the cols and rows shall not be changed by any function, so mark them as "const"
const unsigned int cols = 20;
const unsigned int rows = 10;
struct GameObject* pPlayer = NULL;
struct GameObject* pListOfMonsters = NULL;   // The head of the list.


void moveGameObject( struct GameObject* obj, unsigned int x, unsigned int y )
{
    if(!obj)
    {
        return;
    }
    if(x > cols - 2 || y > rows - 2 || x < 2 || y < 2)
    {
        // no one leaves the dungeon!
        return;
    }
	move(obj->posX+1, obj->posY+1+3);
	clear;
    obj->posX = x;
    obj->posY = y;
	move(obj->posX+1, obj->posY+1+3);
	printf("%c", *(obj->symbol));
}
void addMonster(struct GameObject* newMonster)
{
    struct GameObject* pCurrentMonster = NULL;

    if(pListOfMonsters == NULL)
    {
        // If there are no monsters yet, add the first as the head of the list.
        pListOfMonsters = newMonster;
        //printf("...added %s as the leader of the monsters gang.\n",newMonster->name);
    }
    else
    {
        /* If we can access the head of the list, we can easily access all other list elements
         * by using the "next" pointer within each GameObject.
         */
        pCurrentMonster = pListOfMonsters;
        while( pCurrentMonster != NULL )
        {
            if(pCurrentMonster->next == NULL)
            {
                // We reached the last element of the list, append the new one,
                // then break the loop.
                pCurrentMonster->next = newMonster;
                //printf("...added %s to the monsters gang.\n",newMonster->name);
                break;
            }
            else
            {
                // we haven't reached the last element yet, so go on...
                pCurrentMonster = pCurrentMonster->next;
            }
        }
    }
}
void drawBoard(void){
	unsigned int i,j;
	for(i = 0; i < cols+2; i++)
		printf("-");
	printf("\n");

	for(j = 0; j < rows; j++){
		printf("|");
		for(i = 0; i < cols; i++)
			printf(" ");
		printf("|");
		printf("\n");
	}

	for(i = 0; i < cols+2; i++)
		printf("-");
	printf("\n");
}
void setUpGame()
{
    struct GameObject* newMonster = NULL;

    /* Let's add our hero to the game by allocating the required amount of memory on the HEAP.
     * By doing so, we can access the new "object" through a pointer from where ever we want
     * until we decide to wipe it out again.
     * Remember: If you use malloc(sizeof("whatever")), you must never redirect the pointer
     *           you received from malloc() until you cleared the reserved memory with free().
     *           Otherwise, the reserved memory becomes unreachable, what is pretty bad indeed.
     *           Practice safe coding!!!
     */
    pPlayer = (struct GameObject*)malloc(sizeof(*pPlayer));
    // After malloc(), always check if the allocation process succeeded.
    if(pPlayer)
    {
        pPlayer->Health = 100;
        pPlayer->name = "Jack Black";
        pPlayer->symbol = "J";
        pPlayer->next = NULL;
        moveGameObject(pPlayer, 3, 5);

    }
    else
    {
        /* If the memory allocation process failed for some reason, display an error message.
         * An error message should provide information about where the error occured.
         */
        printf("ERROR: setUpGame(): could not allocate memory for player object.");
    }
    // ----------------- MONSTER'S SECTION BELOW  -----------------
    // now, add the first monster to the list of all monsters. He's the evil boss!
    newMonster = (struct GameObject*)malloc(sizeof(GameObject));
    if(newMonster)
    {
        newMonster->Health = 100;
        newMonster->name = "Aaargghh!!!";
        newMonster->symbol = "§";
        newMonster->next = NULL;
        moveGameObject(newMonster,cols-4,rows-4);

        addMonster(newMonster);
    }
    else
    {
        printf("ERROR: setUpGame(): could not allocate memory for monster object.");
    }
    // add another monster to the list.
    newMonster = (struct GameObject*)malloc(sizeof(GameObject));
    if(newMonster)
    {
        newMonster->Health = 100;
        newMonster->name = "Kevin";
        newMonster->symbol = "$";
        newMonster->next = NULL;
        moveGameObject(newMonster,2,rows-3);

        addMonster(newMonster);
    }
    else
    {
        printf("ERROR: setUpGame(): could not allocate memory for monster object(s).");
    }


}
void handleInput(int *cinput, int *out_bRunning)
{
    if(*cinput == 'x' || *cinput == 'X')
    {
        *out_bRunning = 0;
        return;
    }
    if(*cinput == 'w' || *cinput == 'W')
        moveGameObject(pPlayer, pPlayer->posX, pPlayer->posY - 1);
    if(*cinput == 's' || *cinput == 'S')
        moveGameObject(pPlayer, pPlayer->posX, pPlayer->posY + 1);
    if(*cinput == 'a' || *cinput == 'A')
        moveGameObject(pPlayer, pPlayer->posX - 1, pPlayer->posY);
    if(*cinput == 'd' || *cinput == 'D')
        moveGameObject(pPlayer, pPlayer->posX + 1, pPlayer->posY);
}
/*void runGame(int *out_bRunning)
{
    int x,y;
    const char *line[cols];
    struct GameObject* pCurrentMonster = NULL;

    for(y=1;y<rows;++y)
    {
        for(x=1;x<cols;++x)
        {
            // draw the "dungeon"...
            line[x-1] = " ";
            if( x == 1 || x == cols-1)
            {
                line[x-1] = "|";
            }
            else if( y == 1 || y == rows-1 )
            {
                line[x-1] = "-";
            }
            // draw GameObjects...
            if(pPlayer)
            {
                if(x == pPlayer->posX && y == pPlayer->posY)
                {
                    line[x-1] = pPlayer->symbol;
                }
            }
            if(pListOfMonsters)
            {
                pCurrentMonster = pListOfMonsters;
                while( pCurrentMonster != NULL )
                {
                    if(x == pCurrentMonster->posX && y == pCurrentMonster->posY)
                    {
                        line[x-1] = pCurrentMonster->symbol;
                        // Player encounters a monster...
                        if(pPlayer && x == pPlayer->posX && y == pPlayer->posY)
                        {
                            //...Player takes damage!
                            pPlayer->Health -= 1000;
                        }
                    }
                    pCurrentMonster = pCurrentMonster->next;
                }
            }
            // print out the symbol...
            printf("%s",line[x-1]);
        }
        // go to next line...
        printf("\n");
    }
    // ------------- Game Mechanics -------------
    if(pPlayer && pPlayer->Health < 1)
    {
        printf("You died. GAME OVER\n");
        *out_bRunning = 0;
    }
}*/
void shutDownGame()
{
    struct GameObject* pDeletedMonster = NULL;

    if(pPlayer)
    {
        printf("shutDown(): free Player %s's reserved memory...\n",pPlayer->name);
        free(pPlayer);
        pPlayer = NULL;
    }
    while( pListOfMonsters != NULL )
    {
        if(pListOfMonsters->next == NULL)
        {
            printf("shutDown(): free %s's reserved memory...\n",pListOfMonsters->name);
            free(pListOfMonsters);
            pListOfMonsters = NULL;
        }
        else
        {
            // we haven't reached the last remaining element yet, so go on...
            pDeletedMonster = pListOfMonsters;
            // redirect the list entry...
            pListOfMonsters = pListOfMonsters->next;
            // free memory...
            printf("shutDown(): free %s's reserved memory...\n",pDeletedMonster->name);
            free(pDeletedMonster);
        }
    }

}
int main()
{
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


    while( bRunning )
    {
		if(!kbhit) continue;
        cinput = getch();
        handleInput(&cinput,&bRunning);

        if( bRunning && cinput != '\n' && cinput != '\t' )
        {
            //runGame(&bRunning);
        }
    }

    shutDownGame();
    return 0;
}
