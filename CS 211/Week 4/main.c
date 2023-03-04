/* Dynamic array allocation program in C

Running program looks like:
    Give input of -1 to exit the program.
    Enter value: 1
    Array: 1 
    Enter value: 2
    Array: 1 2 
    Enter value: 3
    Array: 1 2 3 
    Enter value: 4
    
    Growing array from size 3 to 6
    Array: 1 2 3 4 
    Enter value: 5
    Array: 1 2 3 4 5 
    Enter value: 6
    Array: 1 2 3 4 5 6 
    Enter value: 7
    
    Growing array from size 6 to 9
    Array: 1 2 3 4 5 6 7 
    Enter value: -1
    Done.
 */
#include <stdio.h>
#include <stdlib.h>   // Needed for malloc

#define true 1         // Make true a synonym for 1
const int Delta = 3;   // Array growth increment


//-------------------------------------------------
void displayArray( int theArray[], int size)
{
   printf("Array: ");
   for( int i=0; i<size; i++) {
      printf("%d ",theArray[ i]);
   }
   printf("\n");
} // end of displayArray(...)


//----------------------------------------------------
// Add newNumber into array pArray, currently containing
// "size" elements. Grow the array as needed, updating
// currentSize and maxSize.
// 
// Be sure to implement this fully in place within main()
// before attempting to do it here in the function!
//
// To do this, if array is full then:
//   1. Allocate space for new array (pNew) that is the
//      size of the old one (pArray), plus 3 more.
//   2. Copy over the old array (pArray) into the new
//      one (pNew)
//   3. Free up the old array (pArray)
//   4. Make the array (pArray) now be the new array (pNew)
//   5. Update the new array max size
// Add the new element and update the new current size
//
void add(int newNumber, int *pArray, int *currSize, int *maxSize){
    // See if array is full
    if(*currSize == *maxSize){
        // Allocate space for new array
        int *pNew = malloc((*maxSize + Delta) * sizeof(int));
        // Copy over the old array
        for(int i = 0; i < *currSize; i++){
            pNew[i] = pArray[i];
        }
        // Free up the old array
        free(pArray);
        // Make the array now be the new array
        pArray = pNew;
        // Update the new array max size
        *maxSize += Delta;
    }
    // Add the new element and update the new current size
    pArray[*currSize] = newNumber;

} // end of add(...)


//-----------------------------------------------
int main()
{
    int currentSize = 0;
    int maxSize = 0;
    int *pArray = NULL;
    int newNumber = 0;
    
    // Dynamically allocate space for the initial array
    pArray = malloc(Delta * sizeof(int));
    maxSize = Delta;     // Set the initial max size
    
    // Prompt for, get and store new number
	printf("Give input of -1 to exit the program.\n");
    do {
        printf("Enter value: ");
        scanf("%d", &newNumber);
        if( newNumber == -1) {
            break;   // Exit when -1 is entered
        }
        
        // Add the new value, growing array if needed
        // add(......);
        // First implement the code here, before trying to put it in the add(...) function
        // ...
      
      add(newNumber, pArray, &currentSize, &maxSize);

        
        // Display the array with this new element
        displayArray( pArray, currentSize);
     } while( true);

    printf("Done.\n");
    return 0;
}
