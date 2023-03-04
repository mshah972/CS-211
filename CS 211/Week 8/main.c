// Lab 8: Dynamic array implemented using a linked list.
// UIC CS 211, Spring 2023

#include <stdio.h>
#include <stdlib.h>

#define true 1       // Make true a synonym for 1
const int Delta = 3; // Array growth increment

typedef struct Node *NodePtr; // NodePtr is a synonym for: struct Node *
struct Node
{
    int data;      // The data stored at the node
    int index;     // Index position of this node, when viewed as array
    NodePtr pNext; // Pointer to the next node
};

//-------------------------------------------------
void displayArray(NodePtr pCurrent) // Pointer to the first list Node
{
    // Display the index values stored on the array nodes.
    printf("Array indices: ");
    NodePtr pTemp = pCurrent; // make a copy, so original can still be used below.
    while (pTemp != NULL)
    {
        // Don't print the sentinel Node value
        if (pTemp->data != -1)
        {
            printf("%3d", pTemp->index);
        }
        pTemp = pTemp->pNext;
    }
    printf("\n");

    // Display the numbers stored on the array nodes.
    printf("       values: ");
    while (pCurrent != NULL)
    {
        // Don't print the sentinel Node value
        if (pCurrent->data != -1)
        {
            printf("%3d", pCurrent->data);
        }
        pCurrent = pCurrent->pNext;
    }
    printf("\n");
} // end displayArray(..)

//----------------------------------------------------
// Find and return the pointer to the nth Node on the list.
// Return NULL if the index value we are searching for is
// not found.
NodePtr findNthNode(
    NodePtr pCurrent, // Starts at head of list
    int indexToFind)  // Index value we are looking for
{
    // Advance past the sentinel Node to the first Node, if there is one.
    if (pCurrent != NULL && pCurrent->index == -1)
    {
        pCurrent = pCurrent->pNext;
    }

    // Iterate down the list looking for the indexToFind.
    // Make sure we stop at the end of the list, in case indexToFind
    // is larger than the index at the end of the list.
    while (pCurrent != NULL && pCurrent->index < indexToFind)
    {
        // Advance pCurrent to point to next node
        pCurrent = pCurrent->pNext;
    }

    // Return pointer to the Node where index was found, or NULL if not found.
    if (pCurrent != NULL && indexToFind == pCurrent->index)
    {
        return pCurrent;
    }
    else
    {
        return NULL;
    }
} // end findNthNode(..)

//----------------------------------------------------
// Add newNumber into array. If index is larger than
// the current array size, then grow the array in groups
// of 3 nodes at a time until index is now in range.
//
// Once this is done, add the new element and update
// the new current size.
//
void addValueAt(NodePtr pHead, int newNumber, int newNumberIndex)
{
    // Find the Node where the newNumber should be inserted.
    // If the index is larger than the current array size, then
    // grow the array in groups of 3 nodes at a time until index
    // is now in range.
    // ...

    // Add the new element and update the new current size.

    NodePtr current = pHead;
    int currentIndex = 0;

    // Find the Node where the newNumber should be inserted.
    // If the index is larger than the current array size, then
    // grow the array in groups of 3 nodes at a time until index
    // is now in range.
    while (current != NULL && current->index < newNumberIndex)
    {
        current = current->pNext;
        currentIndex++;
    }

    // If the index is larger than the current array size, then
    // grow the array in groups of 3 nodes at a time until index
    // is now in range.

    if (current == NULL)
    {
        // Allocate space for the new Node and initialize its values.
        NodePtr pNewNode = (NodePtr)malloc(sizeof(struct Node));
        pNewNode->index = currentIndex;
        pNewNode->data = newNumber;
        pNewNode->pNext = NULL;

        // Add the new Node to the end of the list.
        current = pHead;
        while (current->pNext != NULL)
        {
            current = current->pNext;
        }
        current->pNext = pNewNode;
    }
    else
    {
        // Add the new element and update the new current size.
        NodePtr pNewNode = (NodePtr)malloc(sizeof(struct Node));
        pNewNode->index = currentIndex;
        pNewNode->data = newNumber;
        pNewNode->pNext = current;

        current = pHead;
        while (current->pNext != pNewNode->pNext)
        {
            current = current->pNext;
        }
        current->pNext = pNewNode;
    }

    // Update the index values of all the Nodes in the list.
    currentIndex = 0;

    current = pHead;
    while (current != NULL)
    {
        current->index = currentIndex;
        current = current->pNext;
        currentIndex++;
    }
}

//-----------------------------------------------
int main()
{
    int moveNumber = 1;     // Numbers user inputs.
    int maxSize = 0;        // Number of Nodes in storage, not counting the sentinel Node.
    int newNumber = 0;      // User input of new number to be added.
    int newNumberIndex = 0; // User input of index position where new number should go.

    // Allocate space for the initial sentinel Node and initialize its values.
    NodePtr pHead = (NodePtr)malloc(sizeof(struct Node));
    pHead->index = -1;
    pHead->data = -1;
    pHead->pNext = NULL;
    NodePtr pTail = pHead; // Tail initially points to sentinel node

    // Allocate the first set of 3 nodes
    // ...
    addValueAt(pHead, 10, 1);
    addValueAt(pHead, 20, 2);
    addValueAt(pHead, 30, 3);
    addValueAt(pHead, 40, 4);
    addValueAt(pHead, 50, 5);

    displayArray(pHead->pNext);

    // Prompt for, get and store new number
    // printf("Give input of -1 to exit the program.\n");
    // do
    // {
    //     printf("%2d. Enter value and index: ", moveNumber);
    //     scanf("%d", &newNumber);
    //     if (newNumber == -1)
    //     {
    //         break; // Exit when -1 is entered
    //     }
    //     else
    //     {
    //         // Also scan the index
    //         scanf("%d", &newNumberIndex);
    //     }

    //     // Add the new value, growing storage if needed.
    //     // addValueAt(...);
    //     addValueAt(pHead, newNumber, newNumberIndex);

    //     // Display the array with this new element
    //     displayArray(pHead);

    //     // Increment the moveNumber
    //     moveNumber++;
    // } while (true);

    printf("\n");


    printf("Testing some test cases...\n");
    printf("\n");

    // Test case 1: Add a value at the end of the list.
    printf("Test case 1: Add a value at the end of the list.\n");
    addValueAt(pHead, 60, 6);
    displayArray(pHead);

    printf("\n");

    // Test case 2: Add a value at the beginning of the list.
    printf("Test case 2: Add a value at the beginning of the list.\n");
    addValueAt(pHead, 5, 1);
    displayArray(pHead);

    printf("\n");

    // Test case 3: Add a value in the middle of the list.
    printf("Test case 3: Add a value in the middle of the list.\n");
    addValueAt(pHead, 25, 3);
    displayArray(pHead);

    printf("\n");


    printf("Done.\n");
    return 0;
}