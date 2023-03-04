#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// char *removeAllSpaces(char inputLine[])
// {
//     char *outputLine = malloc(strlen(inputLine));
//     int i = 0;
//     int j = 0;
//     while (inputLine[i] != '\0')
//     {
//         if (inputLine[i] != ' ')
//         {
//             outputLine[j] = inputLine[i];
//             j++;
//         }
//         i++;
//     }
//     outputLine[j] = '\0';
//     return outputLine;
// }

// // wihout using the string library
// char *insertString(char inputLine[],      // The line of text being operated on
//                    char *pStringToInsert, // The string to be inserted
//                    char *pInsertionPointText)
// { // The insertion point text
//     char *newString = malloc(strlen(inputLine));
//     // Find the insertion point, and return NULL if it is not found without using the string library
//     char *pInsertionPoint = NULL;
//     int i = 0;
//     while (inputLine[i] != '\0')
//     {
//         if (inputLine[i] == *pInsertionPointText)
//         {
//             pInsertionPoint = &inputLine[i];
//             break;
//         }
//         i++;
//     }

//     if (pInsertionPoint == NULL)
//     {
//         return NULL;
//     }

//     // Extract a copy of the string starting from the insertion point
//     // until the end of the text.
//     char *pCopy = malloc(strlen(pInsertionPoint));
//     int j = 0;
//     while (pInsertionPoint[j] != '\0')
//     {
//         pCopy[j] = pInsertionPoint[j];
//         j++;
//     }

//     // Append the string to insert to the end of the input line
//     int k = 0;
//     while (pStringToInsert[k] != '\0')
//     {
//         inputLine[i] = pStringToInsert[k];
//         i++;
//         k++;
//     }

//     // Append the copy of the string to the end of the input line
//     k = 0;
//     while (pCopy[k] != '\0')
//     {
//         inputLine[i] = pCopy[k];
//         i++;
//         k++;
//     }

//     // Terminate the string
//     inputLine[i] = '\0';

//     return inputLine;
// }

char *removeString(char *pText,   // Text being operated on
                   char *pRemove) // Text to be removed
{
    // Find the start of the string to remove
    char *pStart = NULL;
    int i = 0;
    while (pText[i] != '\0')
    {
        if (pText[i] == *pRemove)
        {
            pStart = &pText[i];
            break;
        }
        i++;
    }

    if (pStart == NULL)
    {
        return NULL;
    }

    // Find the end of the string to remove
    char *pEnd = NULL;
    int j = 0;
    while (pRemove[j] != '\0')
    {
        j++;
    }
    pEnd = &pRemove[j];

    // Copy the text after the string to remove to the start of the string to remove
    int k = 0;
    while (pEnd[k] != '\0')
    {
        pStart[k] = pEnd[k];
        k++;
    }

    // Terminate the string
    pStart[k] = '\0';

    return pText;
} 

int main()
{
    // char inputLine[100];
    // printf("Enter a line of text: ");
    // fgets(inputLine, 100, stdin);
    // printf("You entered: %s", inputLine);
    // printf("Without spaces: %s", removeAllSpaces(inputLine));

    char inputLine[100];
    printf("Enter a line of text: ");
    fgets(inputLine, 100, stdin);
    printf("You entered: %s", inputLine);

    

    return 0;
}