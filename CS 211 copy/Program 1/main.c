#include <stdio.h>
#include <stdlib.h> // Needed for malloc
#include <string.h> // Needed for strcmp
#include <time.h>

#define MAX_SOLUTION 3188
#define EASY_MODE_PUZZLES 10

const int easyModePuzzles[EASY_MODE_PUZZLES][4] = {{3, 9, 4, 1}, {8, 5, 8, 1}, {6, 1, 5, 1}, {2, 8, 7, 8}, {5, 2, 9, 2}, {2, 6, 8, 4}, {5, 5, 4, 3}, {6, 6, 2, 6}, {8, 4, 2, 6}, {6, 2, 8, 1}};

int debugMode = 0;
int easyMode = 1;

int calculate(int num1, int num2, char operator)
{
    if (operator == '+')
    {
        return num1 + num2;
    }

    if (operator == '-')
    {
        return num1 - num2;
    }

    if (operator == '*')
    {
        return num1 * num2;
    }

    if (operator == '/')
    {
        return num1 / num2;
    }

    return 0;
}

int isValidOperator(char operator)
{
    if (operator == '+' || operator == '-' || operator == '*' || operator == '/')
    {
        return 1;
    }

    return 0;
}

void solvePuzzle(int num1, int num2, int num3, int num4, char operator1, char operator2, char operator3)
{

    int result1 = calculate(num1, num2, operator1);
    int result2 = calculate(result1, num3, operator2);
    int result3 = calculate(result2, num4, operator3);

    int mainResult = result1 + result2 + result3;

    printf("%d %c %d = %d\n", num1, operator1, num2, result1);
    printf("%d %c %d = %d\n", result1, operator2, num3, result2);
    printf("%d %c %d = %d\n", result2, operator3, num4, result3);

    if (mainResult == 24)
    {
        printf("Well done! You are a math genius.\n");
    }
    else
    {
        printf("Sorry. Your solution did not evaluate to 24.\n");
    }
}

void playGame()
{
    int num1, num2, num3, num4;
    char operator1, operator2, operator3;

    if (easyMode)
    {
        int puzzleIndex = rand() % EASY_MODE_PUZZLES;
        num1 = easyModePuzzles[puzzleIndex][0];
        num2 = easyModePuzzles[puzzleIndex][1];
        num3 = easyModePuzzles[puzzleIndex][2];
        num4 = easyModePuzzles[puzzleIndex][3];
    }
    else
    {
        num1 = rand() % 9 + 1;
        num2 = rand() % 9 + 1;
        num3 = rand() % 9 + 1;
        num4 = rand() % 9 + 1;
    }

    printf("The numbers to use are: %d, %d, %d, %d", num1, num2, num3, num4);
    printf("\n");
    printf("Enter the three operators to be used, in order (+,-,*, or /): ");
    scanf("%c %c %c", &operator1, &operator2, &operator3);

    if (isValidOperator(operator1) && isValidOperator(operator2) && isValidOperator(operator3))
    {
        solvePuzzle(num1, num2, num3, num4, operator1, operator2, operator3);
    }
    else
    {
        printf("Error! Invlaid operator entered. Please try again.\n");
        printf("\n");
        playGame();
    }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));


    printf("Welcome to the game of TwentyFour.\n");
    printf("Use each of the four numbers shown below exactly once,\n");
    printf("combining them somehow with the basic mathematical operators (+,-,*,/)\n");
    printf("to yield the value twenty-four.\n\n");

    char playAgain;

    while(playAgain != 'N')
    {   
        playGame();
        printf("\n");
        printf("Would you like to play again? Enter N for no and any other character for yes. ");
        scanf(" %c", &playAgain);
        printf("\n");
    }

    printf("Thanks for playing!\n");

    return 0;
}