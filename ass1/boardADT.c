//COMP9024 Assignment 1 : Sliding-Tile Puzzle
//
//Practicing the use of C language, pointers and the ADT.
//
//student ID: z5181350
//
//student name: Xiaoyi Tao
//
//Time: 25/06/2019


//describe the detailed operations on the board.

#include "boardADT.h"

//structure the board.
struct board{
    int *tiles;
    int board_length;
};

//analyse the properties of the board.
int analyse_board(char *text){
    //request memory space to store data of the structure.
    struct board *p_board = malloc(sizeof(struct board));
    if (p_board == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }else{
        //initialize the board.
        //the length of the board(the number of the tiles).
        p_board->board_length = 0;
        //the content of the tiles on the board.
        p_board->tiles = NULL;

        if (text ==NULL) {
            printf("Input error\n");
            exit(1);
        }else{
            //request memory space to store data of tiles.
            p_board->tiles = (int*)malloc(1024 * sizeof(int));
            char *token;
            char *separator = " ";
            //separate the line with " " one by one.
            token = strtok(text, separator);

            //transfer the char string into int pointer.
            while( token != NULL) {
                if (strcmp(token, "b") == 0){
                    //mark the blank tile with integer 0.
                    *(p_board->tiles +p_board->board_length) = 0;
                } else {
                    //transfer the string into integer values.
                    *(p_board->tiles +p_board->board_length) = atoi(token);
                }
                //move to the rest of the string.
                token = strtok(NULL, separator);
                //record the length of the board.
                p_board->board_length++;
            }
        }
    }

    //calculate the size of the board(2*2, 3*3......)
    int size = (int)sqrt((double)p_board->board_length);
    //check if the board is null or the number of tiles is wrong
    //which can not make an board.
    if (p_board->tiles == NULL||p_board->board_length == 0||size * size != p_board->board_length){
        printf("Input error\n");
        exit(1);
    }

    //check if the numbers on the board only appear once
    //and strictly include the numbers from 0 to length -1.
    for (int i = 0; i < p_board->board_length; i++){
        int repeat_check = 0;
        for (int j = 0; j < p_board->board_length; j++){
            if (*(p_board->tiles + j) == i){
                repeat_check += 1;
            }
        }
        if (repeat_check > 1 || repeat_check == 0){
            printf("Input error\n");
            exit(1);
        }
    }

    //calculate the disorder numbers on the board.
    int disorder = 0;
    for (int i = 0; i < (p_board->board_length - 1); i++){
        if (*(p_board->tiles + i) == 0){
            continue;
        }
        for (int j = i + 1;j < p_board->board_length; j++){
            if (*(p_board->tiles +j) == 0){
                continue;
            }
            else if (*(p_board->tiles + j) < *(p_board->tiles + i)){
                disorder += 1;
            }
        }
    }

    //check the board is odd-sized or even-sized
    //add the row of number of the blank to the sum of disorders
    //if the board is even-sized.
    if (size % 2 == 0){
        for (int i = 0; i < p_board->board_length; i++){
            if (*(p_board->tiles + i) == 0){
                disorder += i/size + 1;
            }
        }
    }else{
        disorder = disorder;
    }

    //calculate the parity of the board.
    int parity = disorder % 2;

    //free the memory of the board and tiles.
    if (p_board != NULL){
        if (p_board->tiles != NULL){
            free(p_board->tiles);
        }
        free(p_board);
    }

    //return the parity of the board to
    //check if the board is solvable.
    return parity;
}