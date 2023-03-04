/*

Create the sentinel node at the beginning of main() and then implement functions
appendNumber( )  and deleteNumber( ).

The sentinel node should always be there at the beginning of the list,
with a data value of -1.  This sentinel Node should not be displayed whenever
you print the list.

 */
#include <stdio.h>  // For printf and scanf
#include <stdlib.h> // For malloc

typedef struct Node
    *NodePtr; // Make:  NodePtr to be a synonym for: struct Node *
struct Node
{
    int data;      // The data stored at the node
    NodePtr pNext; // Pointer to the next node
};

//------------------------------------------------------------
// Display the list.  We've supplied this version so your output
// will match the expected test cases.
void displayList(NodePtr pHead)
{
    printf("List is: ");
    while (pHead != NULL)
    {
        // Don't print the sentinel Node value
        if (pHead->data != -1)
        {
            printf("%d ", pHead->data);
        }
        pHead = pHead->pNext;
    }
    printf("\n");
} // end displayList()

///--------------------------------------------------------------
// Append number at the end of the list.  Add the parameters
// and the code needed to implement this function.
void appendNumber(NodePtr *ppHead, int number)
{
    NodePtr pNewNode = malloc(sizeof(struct Node));
    pNewNode->data = number;
    pNewNode->pNext = NULL;

    if (*ppHead == NULL)
    {
        *ppHead = pNewNode;
        return;
    }

    NodePtr pCurrent = *ppHead;

    while (pCurrent->pNext != NULL)
    {
        pCurrent = pCurrent->pNext;
    }

    pCurrent->pNext = pNewNode;

} // end appendNumber()

//--------------------------------------------------------------
// Delete the first (non-sentinel) Node on the list and return the
// number that was in it. Add the parameters and the code needed to
// implement this function.
int deleteNumber(NodePtr *ppHead, int dNumber)
{
    if (*ppHead == NULL)
    {
        return -1;
    }

    NodePtr pCurrent = *ppHead;
    NodePtr pPrevious = NULL;

    while (pCurrent->pNext != NULL)
    {
        pPrevious = pCurrent;
        pCurrent = pCurrent->pNext;
    }

    if (pPrevious == NULL)
    {
        *ppHead = pCurrent->pNext;
    }
    else
    {
        pPrevious->pNext = pCurrent->pNext;
    }

    dNumber = pCurrent->data;
    free(pCurrent);
    return dNumber;

} // end deleteNumber()

//--------------------------------------------------------------
// Consider: For input of 1 3 5 -1, what is the output?
int main()
{
    // Create a sentinal Node at list beginning, initialize it, and make
    //   both head and tail point to it.
    // ...
    NodePtr pSentinel = (NodePtr)malloc(sizeof(struct Node));
    pSentinel->data = -1;
    pSentinel->pNext = NULL;
    NodePtr pHead = pSentinel;
    NodePtr pTail = pSentinel;
    // ---------------------------------------------------
    // The code below this point should remain unchanged.
    int number = 0;        // Used to store numbers read in
    char menuOption = ' '; // Store user input menu option

    // Loop to allow adding and deleting list values.
    while (menuOption != 'x')
    {
        printf("Menu: \n");
        printf("  a n  to add value n to the list \n");
        printf("  d    to delete value from the list \n");
        printf("  x    to exit program \n");
        printf("Your choice: ");
        scanf(" %c", &menuOption);

        // Handle menu options
        switch (menuOption)
        {
        case 'x':
            return 0; // Exit program
            break;
        case 'a':
            scanf("%d", &number);         // Read in the number to be added
            appendNumber(&pHead, number); // Add to end of list
            break;
        case 'd':
            number = deleteNumber(&pHead, number);
            if (number != -1)
            {
                printf("Deleted %d\n", number);
            }
            break;
        default:
            printf("Invalid menu option.  Retry. \n");
            continue;
        }

        printf("\n");
        displayList(pHead); // Display the list
    }

    return 0; // return value to keep C++ happy
} // end main()

// what did you learn from this program?
/*
I learned how to use sentinel nodes and how to use them to create a linked list.
We also learned how to use pointers to pointers to create a linked list. 
*/