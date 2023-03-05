/*
    Moksh Shah
    CS 211
    Program 2 - Weaver
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *filename = "words.txt"; // The name of the file to open
/*

-----------------------------------------
-    A function that loads the file     -
-----------------------------------------

*/
void loadFile(char *filename, char **words[], int *numWords, int userChoice)
{
    FILE *filePtr = fopen(filename, "r"); // "r" means we open the file for reading

    // Check that the file was able to be opened
    if (filePtr == NULL)
    {
        printf("Error: could not open %s for reading\n", filename);
        exit(-1);
    }

    // Read each word from file, and print them one by one
    char inputString[81];
    while (fscanf(filePtr, "%s", inputString) != EOF)
    {
        if (strlen(inputString) == userChoice)
        {
            *words = realloc(*words, (*numWords + 1) * sizeof(char *));             // Allocate space for the next word
            (*words)[*numWords] = malloc((strlen(inputString) + 1) * sizeof(char)); // Allocate space for the characters in the word
            strcpy((*words)[*numWords], inputString);                               // Copy the word into the array
            (*numWords)++;                                                          // Increment the number of words
        }
    }

    // Close the file
    fclose(filePtr);
}

/*

------------------------------------------------------------------
-    A function that checks if the word is in the dictionary     -
------------------------------------------------------------------

*/
int checkWord(char *word, char **words, int numWords)
{
    for (int i = 0; i < numWords; i++)
    {
        if (strcmp(word, words[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

/*

---------------------------------------------------------------------------------------------------------------
-    A function that prints the statements if the word is not in the dictionary or not the correct length     -
---------------------------------------------------------------------------------------------------------------

*/
int checkWordPrintStatements(char *word, int userChoice, char **words, int numWords)
{
    if (strlen(word) != userChoice) // If the word is not the correct length
    {
        printf("Your word, '%s', is not a %d-letter word. Try again.\n", word, userChoice);
        return 0;
    }
    else if (checkWord(word, words, numWords) == 0) // If the word is not in the dictionary
    {
        printf("Your word, '%s', is not a valid dictionary word. Try again.\n", word);
        return 0;
    }
    return 1;
}

void playAgainPrintStaments()
{
    printf("\nEnter: \t1 to play again,\n");
    printf("\t2 to change the number of letters in the words and then play again, or\n");
    printf("\t3 to exit the program.\n");
    printf("Your choice --> ");
}

/*

---------------------------------------------------------------------
-    A function that checks if the word is one letter different     -
---------------------------------------------------------------------

*/
int checkOneLetter(char *word, char *nextWord)
{
    int numDifferences = 0;
    int wordLen = strlen(word);
    for (int i = 0; i < wordLen; i++)
    {
        if (word[i] != nextWord[i]) // If the characters are not the same
        {
            numDifferences++; // Increment the number of differences
        }
    }
    if (numDifferences == 1) // If the number of differences is 1
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*

--------------------------------------------
-    A function for the guessing game      -
--------------------------------------------

*/

int guessingGame(char *startWord, char *endWord, char **words, int numWords, int numMoves, int userchoice)
{
    char tempStartWord[100];          // Create a temporary start word
    strcpy(tempStartWord, startWord); // Copy the start word into the temporary start word for later use

    printf("\n\nOn each move enter a word of the same length that is at most 1 character different and is also in the dictionary.\n");
    printf("You may also type in 'q' to quit guessing.\n");

    numMoves = 1; // Set the number of moves to 1

    char *nextWord = malloc((strlen(startWord) + 1) * sizeof(char)); // Allocate space for the next word

    printf("\n%d. Previous word is '%s'. Goal word is '%s'. Next word: ", numMoves, startWord, endWord);
    scanf("%s", nextWord);

    if (strcmp(nextWord, "q") == 0) // If the user wants to quit
    {
        return 0;
    }

    while (strcmp(startWord, endWord) != 0) // While the next word is not the end word
    {
        if (strcmp(nextWord, "q") == 0) // If the user wants to quit
        {
            return 0;
        }
        else if (checkWordPrintStatements(nextWord, userchoice, words, numWords) == 0) // If the word is not in the dictionary or is not the correct length
        {
            printf("\n%d. Previous word is '%s'. Goal word is '%s'. Next word: ", numMoves, startWord, endWord);
            scanf("%s", nextWord);
        }
        else if (checkOneLetter(startWord, nextWord) == 0) // If the word is not one letter different
        {
            printf("Your word, '%s', is not exactly 1 character different. Try again.\n", nextWord); // Print the statement if the word is more than 1 character different
            printf("\n%d. Previous word is '%s'. Goal word is '%s'. Next word: ", numMoves, startWord, endWord);
            scanf("%s", nextWord);
        }
        else // If the word is in the dictionary, is the correct length, and is one letter different
        {
            strcpy(startWord, nextWord); // Copy the next word into the start word
            numMoves++;                  // Increment the number of moves
            printf("\n%d. Previous word is '%s'. Goal word is '%s'. Next word: ", numMoves, startWord, endWord);
            scanf("%s", nextWord);
        }

        if (strcmp(nextWord, endWord) == 0 && checkOneLetter(startWord, nextWord) == 1) // If the next word is the end word
        {
            break;
        }
    }

    printf("Congratulations! You changed '%s' into '%s' in %d moves.\n", tempStartWord, endWord, numMoves);

    free(nextWord); // Free the memory allocated for the next word

    return 1;
}

/*

---------------------------------------------------------------------
-    A function that asks the user for input and plays the game     -
---------------------------------------------------------------------

*/
int askUserforInput(char *startWord, char *endWord, int userChoice, char **words, int numWords, int numMoves)
{
    printf("Enter starting and ending words, or 'r' for either for a random word: ");
    scanf("%s", startWord);
    scanf("%s", endWord);

    if (strcmp(startWord, "r") == 0)
    {
        int randomNum = rand() % numWords;
        strcpy(startWord, words[randomNum]);
    }

    if (strcmp(endWord, "r") == 0)
    {
        int randomNum = rand() % numWords;
        strcpy(endWord, words[randomNum]);
    }

    // Check if the start word is in the dictionary and is the correct length
    if (checkWordPrintStatements(startWord, userChoice, words, numWords) == 0)
    {
        askUserforInput(startWord, endWord, userChoice, words, numWords, numMoves);
    }
    else if (checkWordPrintStatements(endWord, userChoice, words, numWords) == 0)
    {
        askUserforInput(startWord, endWord, userChoice, words, numWords, numMoves);
    }
    else
    {
        printf("Your starting word is: %s.\n", startWord);
        printf("Your ending word is: %s.\n", endWord);

        guessingGame(startWord, endWord, words, numWords, numMoves, userChoice);
    }

    // guessingGame(startWord, endWord, words, numWords, numMoves);

    // char tempStartWord[100];          // Create a temporary start word
    // strcpy(tempStartWord, startWord); // Copy the start word into the temporary start word for later use

    // printf("\n\nOn each move enter a word of the same length that is at most 1 character different and is also in the dictionary.\n");
    // printf("You may also type in 'q' to quit guessing.\n");

    // numMoves = 1; // Set the number of moves to 1

    // // printf("\n%d. Previous word is '%s'. Goal word is '%s'. Next word: ", numMoves, startWord, endWord);

    // char *nextWord = malloc((strlen(startWord) + 1) * sizeof(char)); // Allocate space for the next word
    // // scanf("%s", nextWord);

    // while (strcmp(nextWord, endWord) != 0) // While the next word is not the end word
    // {
    //     printf("\n%d. Previous word is '%s'. Goal word is '%s'. Next word: ", numMoves, startWord, endWord);

    //     scanf("%s", nextWord);

    //     if (strcmp(nextWord, "q") == 0) // If the user wants to quit
    //     {
    //         return 0;
    //     }
    //     else if (checkWordPrintStatements(nextWord, userChoice, words, numWords) == 0) // If the word is not in the dictionary or is not the correct length
    //     {
    //         printf("\n%d. Previous word is '%s'. Goal word is '%s'. Next word: ", numMoves, startWord, endWord);
    //         scanf("%s", nextWord);
    //     }
    //     else if (checkOneLetter(startWord, nextWord) == 0) // If the word is not one letter different
    //     {
    //         printf("\n%d. Previous word is '%s'. Goal word is '%s'. Next word: ", numMoves, startWord, endWord);
    //         scanf("%s", nextWord);
    //     }
    //     else // If the word is one letter different and in the dictionary
    //     {
    //         strcpy(startWord, nextWord); // Copy the next word into the start word
    //         numMoves++;                  // Increment the number of moves
    //         printf("\n%d. Previous word is '%s'. Goal word is '%s'. Next word: ", numMoves, startWord, endWord);
    //         scanf("%s", nextWord);
    //     }
    // }

    // while (strcmp(nextWord, endWord) != 0) // While the next word is not the end word
    // {
    //     if (strcmp(nextWord, "q") == 0) // If the user wants to quit
    //     {
    //         return 0;
    //     }
    //     else if (checkWordPrintStatements(nextWord, userChoice, words, numWords) == 0) // If the word is not in the dictionary or is not the correct length
    //     {
    //         printf("\n%d. Previous word is '%s'. Goal word is '%s'. Next word: ", numMoves, startWord, endWord);
    //         scanf("%s", nextWord);
    //     }
    //     else if (checkOneLetter(startWord, nextWord) == 0) // If the word is not one letter different
    //     {
    //         printf("\n%d. Previous word is '%s'. Goal word is '%s'. Next word: ", numMoves, startWord, endWord);
    //         scanf("%s", nextWord);
    //     }
    //     else // If the word is in the dictionary, is the correct length, and is one letter different
    //     {
    //         strcpy(startWord, nextWord); // Copy the next word into the start word
    //         numMoves++;                  // Increment the number of moves
    //         printf("\n%d. Previous word is '%s'. Goal word is '%s'. Next word: ", numMoves, startWord, endWord);
    //         scanf("%s", nextWord);
    //     }
    // }

    // printf("\nCongratulations! You changed %s into %s in %d moves.", tempStartWord, endWord, numMoves);

    return 0;
}

int main()
{
    // srand(time(1)); // Seed the random number generator
    srand(1);

    char **words = NULL; // The array of words
    int numWords = 0;    // The number of words in the array

    printf("Weaver is a game where you try to find a way to get from the starting word to the ending word.\n");
    printf("You can change only one letter at a time, and each word along the way must be a valid word.\n");
    printf("Enjoy!\n\n");

    printf("How many letters do you want to have in the words? ");
    int userChoice = 0;
    scanf("%d", &userChoice);

    loadFile(filename, &words, &numWords, userChoice); // Load the file into the array

    int wordsFound = 0;
    for (int i = 0; i < numWords; i++)
    {
        if (strlen(words[i]) == userChoice)
        {
            wordsFound++; // Count the number of words with the user's choice of letters
        }
    }

    printf("Number of %d-letter words found: %d.", userChoice, wordsFound);

    printf("\n\n");

    char *startWord = malloc((userChoice + 1) * sizeof(char)); // Allocate memory for the start word
    char *endWord = malloc((userChoice + 1) * sizeof(char));   // Allocate memory for the end word

    askUserforInput(startWord, endWord, userChoice, words, numWords, 0); // Ask the user for input and play the game

    int playAgainChoice = 0;
    playAgainPrintStaments();
    scanf("%d", &playAgainChoice);

    while (playAgainChoice != 3)
    {
        if (playAgainChoice == 1) // If the user wants to play again
        {
            askUserforInput(startWord, endWord, userChoice, words, numWords, 0);
        }
        else if (playAgainChoice == 2) // If the user wants to change the number of letters in the words and then play again
        {
            char **newWords = NULL; // The array of words
            int newNumWords = 0;    // The number of words in the array

            printf("How many letters do you want to have in the words? ");
            scanf("%d", &userChoice);
            loadFile(filename, &newWords, &newNumWords, userChoice); // Load the file into the array

            int wordsFound = 0;
            for (int i = 0; i < newNumWords; i++)
            {
                if (strlen(newWords[i]) == userChoice)
                {
                    wordsFound++; // Count the number of words with the user's choice of letters
                }
            }

            printf("Number of %d-letter words found: %d.", userChoice, wordsFound);

            printf("\n\n");
            askUserforInput(startWord, endWord, userChoice, newWords, newNumWords, 0);

            free(newWords);
        }

        playAgainPrintStaments();
        scanf("%d", &playAgainChoice);
    }

    printf("\nThanks for Playing!\n");
    printf("Exiting...\n");

    free(startWord); // Free the memory
    free(endWord);   // Free the memory

    // if (userChoice2 == 1)
    // {
    //     askUserforInput(startWord, endWord, userChoice, words, numWords, 1);

    //     free(words); // Free the memory

    //     printf("\nEnter: \t1 to play again,\n");
    //     printf("\t2 to change the number of letters in the words and then play again, or\n");
    //     printf("\t3 to exit the program.\n");
    //     printf("Your choice --> ");

    //     scanf("%d", &userChoice2);
    // }
    // else if (userChoice2 == 2)
    // {
    //     printf("How many letters do you want to have in the words? ");
    //     scanf("%d", &userChoice);
    //     loadFile(filename, &words, &numWords, userChoice);
    //     printf("\n");
    //     askUserforInput(startWord, endWord, userChoice, words, numWords, 0);

    //     free(words); // Free the memory

    //     printf("\nEnter: \t1 to play again,\n");
    //     printf("\t2 to change the number of letters in the words and then play again, or\n");
    //     printf("\t3 to exit the program.\n");
    //     printf("Your choice --> ");

    //     scanf("%d", &userChoice2);
    // }
    // else if (userChoice2 == 3)
    // {
    //     printf("\nThanks for Playing!\n");
    //     printf("Exiting...\n");
    // }

    return 0;
}
