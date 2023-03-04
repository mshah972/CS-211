#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N_PUZZLES 10
#define N_NUMS 4
#define TARGET 24

// Define the puzzles for easy mode
const int easy_puzzles[N_PUZZLES][N_NUMS] = {
  {3, 9, 4, 1},
  {8, 5, 8, 1},
  {6, 1, 5, 1},
  {2, 8, 7, 8},
  {5, 2, 9, 2},
  {2, 6, 8, 4},
  {5, 5, 4, 3},
  {6, 6, 2, 6},
  {8, 4, 2, 6},
  {6, 2, 8, 1}
};

// Check if the result is 24
int check_result(double result) {
  return fabs(result - TARGET) < 0.0001;
}

// Perform the calculation
double calculate(int nums[N_NUMS], char ops[N_NUMS - 1]) {
  double result = nums[0];
  for (int i = 0; i < N_NUMS - 1; i++) {
    switch (ops[i]) {
      case '+':
        result += nums[i + 1];
        break;
      case '-':
        result -= nums[i + 1];
        break;
      case '*':
        result *= nums[i + 1];
        break;
      case '/':
        result /= nums[i + 1];
        break;
      default:
        printf("Error! Invalid operator entered. Please try again.\n");
        return 0.0;
    }
  }
  return result;
}

// Print the puzzle and get the user's input
void get_input(int nums[N_NUMS], char ops[N_NUMS - 1]) {
  printf("Puzzle: ");
  for (int i = 0; i < N_NUMS; i++) {
    printf("%d ", nums[i]);
  }
  printf("\nEnter three operators: ");
  scanf("%s", ops);
  if (strlen(ops) != N_NUMS - 1) {
    printf("Error! The number of operators is incorrect. Please try again.\n");
  }
}

int main(int argc, char *argv[]) {
  srand(1);
  int debug = 0, easy = 1;
  int nums[N_NUMS];
  char ops[N_NUMS - 1];
  int puzzle_index;

  // Check for command-line arguments
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-d") == 0) {
      debug = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-e") == 0) {
      easy = atoi(argv[++i]);
    }
    }

    // Get the puzzle
    if (easy) {
      puzzle_index = rand() % N_PUZZLES;
      for (int i = 0; i < N_NUMS; i++) {
        nums[i] = easy_puzzles[puzzle_index][i];
      }
    } else {
      printf("Enter four numbers: ");
      for (int i = 0; i < N_NUMS; i++) {
        scanf("%d", &nums[i]);
      }
    }

    // Get the user's input
    get_input(nums, ops);

    // Perform the calculation
    double result = calculate(nums, ops);

    // Check the result
    if (check_result(result)) {
      printf("Correct!\n");
    } else {
      printf("Incorrect! The correct answer is 24.\n");
    }

    // Print the debug information
    if (debug) {
      printf("Debug: ");
      for (int i = 0; i < N_NUMS; i++) {
        printf("%d ", nums[i]);
      }
      printf("= %f  ", result);
        for (int i = 0; i < N_NUMS - 1; i++) {
            printf("%c ", ops[i]);
        }
        printf(" %d %d %d %d " , nums[0], nums[1], nums[2], nums[3]);
        printf(" %c %c %c " , ops[0], ops[1], ops[2]);
        printf(" %f " , result);
        printf(" %d " , check_result(result));
        printf(
