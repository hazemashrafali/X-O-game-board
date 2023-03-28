#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include <ctype.h>
#define max_board 9

typedef unsigned char uint8_t;

/* function prototypes*/
void drawBoard(uint8_t *board);
void updateBoard(uint8_t *board, uint8_t position, uint8_t value);
uint8_t getPlayerSymbol(uint8_t playerNumber, uint8_t * symbol);
void setPlayerConfig(uint8_t *configArray);
void loadAndUpdate(uint8_t playerNumber);
void getGameState(uint8_t *board, uint8_t *gameState);
void gamereset();


/* global variables*/
uint8_t player_symbol[2]= {'a','b'};
uint8_t numbers[max_board]= {'1','2','3','4','5','6','7','8','9'};
uint8_t configArray[2]= {0};
uint8_t fill_count=0;
uint8_t gamestate=2;


int main()
{
    uint8_t option;
    while(1)
    {
        printf("1-start the game\n2-exit the game\n");
        switch(getche())
        {
        case '1':
        {
            drawBoard(numbers);
            printf("\n");
            setPlayerConfig(configArray);
            while(gamestate==2)
            {
                loadAndUpdate(1);
                drawBoard(numbers);
                getGameState(numbers,&gamestate);
                if(gamestate==0)
                {
                    printf("\nplayer-1 winning!\n");
                    gamereset();
                    break;
                }
                if(gamestate==1)
                {
                    printf("\nNo winner\n");
                    gamereset();
                    break;
                }
                loadAndUpdate(2);
                drawBoard(numbers);
                getGameState(numbers,&gamestate);
                if(gamestate==0)
                {
                    printf("\nplayer-2 winning!\n");
                    gamereset();
                    break;
                }
                if(gamestate==1)
                {
                    printf("\nNo winner\n");
                    gamereset();
                    break;
                }
            }
        }
        break;
        case '2':
        {
            printf("\nGOODBYE(^_^)");
            exit(0);
        }
        break;
        default:
            printf("\nwrong selection,please select\n");
            break;
        }

    }
}


//This function will take a board as an input and prints it on the console
void drawBoard(uint8_t *board)
{
    int i=0,j=0,col=0;
    printf("\n\n\t  ");
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            printf("%c",board[i+j+col]);
            if (j < 2)
            {
                printf("  |  ");
            }
        }
        if (i < 2)
            printf("\n\t----------------\n\t  ");
        col+=2;
    }
}

// This function will take the board, position to update and value to set in this position
void updateBoard(uint8_t *board, uint8_t position, uint8_t value)
{
    board[position]=value;
    fill_count++;
}

/*
This function will take the player's number and asks the player to choose between X and O (case insensitive)
- This function will return 0 when the input symbol is not wrong and/or was not chosen before
- This function will return 1 when the input symbol is wrong and/or was chosen before
*/
uint8_t getPlayerSymbol(uint8_t playerNumber, uint8_t * symbol)
{
    *symbol=toupper(*symbol);
    if(*symbol != 'X' && *symbol != 'O')
    {
        printf("wrong selection,choose between (X-O)\n");
        return 1;
    }
    if(playerNumber==1)
    {
        if(*symbol == player_symbol[1])
        {
            printf("the symbol is used\n");
            return 1;
        }
        else
        {
            player_symbol[0]=*symbol;
            printf("player-1 symbol:%c\n",*symbol);
            return 0;
        }
    }
    if(playerNumber==2)
    {
        if(*symbol == player_symbol[0])
        {
            printf("the symbol is used\n");
            return 1;
        }
        else
        {
            player_symbol[1]=*symbol;
            printf("player-2 symbol:%c\n",*symbol);
            return 0;
        }
    }
}

//This function will prompt and asks each user about their preferred symbols and saves it in the configureArray
void setPlayerConfig(uint8_t *configArray)
{
    uint8_t sym,return_flag=1;
    while(return_flag)
    {
        printf("select player-1 symbol (X-O):\n");
        sym=getche();
        printf("\n");
        return_flag=getPlayerSymbol(1,&sym);
    }
    configArray[0]=sym;
    return_flag=1;
    while(return_flag)
    {
        printf("select player-2 symbol (X-O):\n");
        sym=getche();
        printf("\n");
        return_flag=getPlayerSymbol(2,&sym);
    }
    configArray[1]=sym;
}


/*This function will take the player's number then load his configure,
ask him for the position then updates the board*/
void loadAndUpdate(uint8_t playerNumber)
{
    uint8_t position;
    uint8_t flag=0;
    while(flag==0)
    {
        printf("\n player-%d enter the position:\n",playerNumber);
        scanf("%d",&position);
        if(position < 1 || position > 9)
        {
            printf("position is not exist,select between (1:9)");
            flag=0;
            continue;
        }
        flag=1;
        switch (playerNumber)
        {
        case 1:
        {
            if(numbers[position-1] == 'X' || numbers[position-1] == 'O')
            {
                printf("position used already\n");
                flag=0;
            }
            else
            {
                updateBoard(numbers,position-1,configArray[0]);
                flag=1;
            }
            break;
        }
        case 2:
        {
            if(numbers[position-1] == 'X' || numbers[position-1] == 'O')
            {
                printf("position used already\n");
                flag=0;
            }
            else
            {
                updateBoard(numbers,position-1,configArray[1]);
                flag=1;
            }
            break;
        }
        default:
            printf("player number wrong");
            break;
        }

    }
}


/*
 function to check if there is a winning, draw, or continue playing.
 will check after each move if there is a win, draw or continue playing.
- Returns 0 for winning
- Returns 1 for a draw
- Returns 2 to continue
*/
void getGameState(uint8_t *board, uint8_t *gameState)
{
    if ((board[0]==board[1] && board[1]==board[2])||
            (board[3]==board[4] && board[4]==board[5])||
            (board[6]==board[7] && board[7]==board[8]))
        *gameState=0; //winning check rows
    else if((board[0]==board[3] && board[3]==board[6])||
            (board[1]==board[4] && board[4]==board[7])||
            (board[2]==board[5] && board[5]==board[8]))
        *gameState=0;  //winning check columns
    else if((board[0]==board[4] && board[4]==board[8])||
            (board[2]==board[4] && board[4]==board[6]))
        *gameState=0;  //winning check diagonal
    else if(fill_count<=8)
        *gameState=2;
    else
        *gameState=1;
}

/*reset all variables to its default*/
void gamereset()
{
    player_symbol[0]= 'a';
    player_symbol[1]= 'b';
    numbers[0]='1';
    numbers[1]='2';
    numbers[2]='3';
    numbers[3]='4';
    numbers[4]='5';
    numbers[5]='6';
    numbers[6]='7';
    numbers[7]='8';
    numbers[8]='9';
    configArray[0]=0;
    configArray[1]=0;
    fill_count=0;
    gamestate=2;
}
