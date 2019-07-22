//COMP9024 Assignment 1 : Sliding-Tile Puzzle
//
//Practicing the use of C language, pointers and the ADT.
//
//student ID: z5181350
//
//student name: Xiaoyi Tao
//
//Time: 25/06/2019

#include "boardADT.h"

// main function --- read the start and goal lines from stdin
//and analyse the two lines to draw a conclusion.

int main(int argc, char **argv){
    char *start_text;
    char *goal_text;

    //request memory space to store data of start and goal lines.
    start_text = (char*)malloc(sizeof(char) * 1024);
    goal_text = (char*)malloc(sizeof(char) * 1024);
    if (start_text == NULL || goal_text ==NULL) {
        fprintf(stderr, "Run out of memory.\n");
        return EXIT_FAILURE;
    }

    //read the content of start and goal lines from stdin.
    fgets(start_text, 1024, stdin);
    fgets(goal_text, 1024, stdin);

    //print the start and goal lines.
    printf("start: %s", start_text);
    printf("goal: %s", goal_text);

    //analyse the two lines to check the parity of the two board.
    int start_parity = analyse_board(start_text);
    int goal_parity = analyse_board(goal_text);

    //check and print the result whether the board is solvable.
    if (start_parity == goal_parity){
        printf("solvable\n");
    }else{
        printf("unsolvable\n");
    }

    //free the memories.
    free(start_text);
    free(goal_text);

    return 0;
}
