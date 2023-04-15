/*
    Program 3 - TwentyFour Part Two
    Course: CS-211, Spring 2023, UIC
    System: Windows 11
    Author: Moksh Shah
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define NOT_TWENTY_FOUR 0

/*
    Struct for a node in a linked list.

    value: The value of the node.
    next: The next node in the linked list.

    Note: The linked list is used to implement a stack.
*/

typedef struct Node
{
    int value;
    struct Node *next;
} Node;


/*
    Struct for a stack.

    top: The top node in the stack.

    Note: The stack is used to implement a queue.
*/
typedef struct Stack
{
    Node *top;
} Stack;


/*
    Creates a new stack.

    Returns: The new stack.

    Note: The stack is used to implement a queue.
*/
Stack *create_stack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}


/*
    Pushes a value to the top of the stack.

    stack: The stack to push the value to.
    value: The value to push to the stack.

    Note: The stack is used to implement a queue.
*/
void push(Stack *stack, int value)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = stack->top;
    stack->top = new_node;
}


/*
    Pops the top value from the stack.

    stack: The stack to pop the value from.

    Returns: The value popped from the stack.

    Note: The stack is used to implement a queue.
*/
int pop(Stack *stack)
{
    if (stack->top == NULL)
    {
        printf("Error! Stack is empty.\n");
        exit(1);
    }
    int value = stack->top->value;
    Node *temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    return value;
}


/*
    Returns 1 if the stack is empty, 0 otherwise.

    stack: The stack to check if it is empty.

    Note: The stack is used to implement a queue.
*/
int is_empty(Stack *stack)
{
    return stack->top == NULL;
}


/*
    Deletes the stack.

    stack: The stack to delete.

    Note: The stack is used to implement a queue.
*/
void delete_stack(Stack *stack)
{
    while (!is_empty(stack))
    {
        pop(stack);
    }
    free(stack);
}


/*
    Returns 1 if the character is a valid symbol, 0 otherwise.

    c: The character to check if it is a valid symbol.

    Note: Valid symbols are +, -, *, /, (, ), and spaces.
*/
int is_valid_symbol(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == ' ' || isdigit(c);
}


/*
    Returns 1 if the expression is valid, 0 otherwise.

    expression: The expression to check if it is valid.

    Note: Valid expressions are composed of valid symbols and have a valid number of parentheses.
*/
int is_valid_solution(const char *solution, const int *numbers)
{
    int count[4] = {0};
    for (int i = 0; solution[i]; ++i)
    {
        if (isdigit(solution[i]))
        {
            int num = solution[i] - '0';
            int index = -1;
            for (int j = 0; j < 4; ++j)
            {
                if (numbers[j] == num && count[j] == 0)
                {
                    index = j;
                    break;
                }
            }
            if (index == -1)
                return 0;
            count[index]++;
        }
    }
    return count[0] == 1 && count[1] == 1 && count[2] == 1 && count[3] == 1;
}


/*
    Returns the precedence of the operator.

    op: The operator to get the precedence of.

    Note: The precedence of + and - is 1, the precedence of * and / is 2, and the precedence of all other operators is 0.
*/
int get_precedence(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}


/*
    Evaluates the expression.

    expression: The expression to evaluate.

    Returns: The result of the expression.

    Note: The expression is assumed to be valid.

    Note: The expression is assumed to be in postfix notation.

    Note: The expression is assumed to be composed of integers and the operators +, -, *, and /.
*/
int evaluate_expression(const char *expression, const int *numbers)
{
    Stack *value_stack = create_stack();
    Stack *operator_stack = create_stack();

    for (int i = 0; expression[i]; ++i)
    {
        if (isdigit(expression[i]))
        {
            push(value_stack, expression[i] - '0');
        }
        else if (expression[i] == '(')
        {
            push(operator_stack, expression[i]);
        }
        else if (expression[i] == ')')
        {
            while (!is_empty(operator_stack) && operator_stack->top->value != '(')
            {
                char op = (char)pop(operator_stack);
                int b = pop(value_stack);
                int a = pop(value_stack);
                int result;
                switch (op)
                {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    if (b == 0)
                    {
                        printf("Error! Division by zero.\n");
                        delete_stack(value_stack);
                        delete_stack(operator_stack);
                        return -1;
                    }
                    result = a / b;
                    break;
                }
                printf("%d %c %d = %d.\n", a, op, b, result); // Print the steps
                push(value_stack, result);
            }
            if (is_empty(operator_stack))
            {
                printf("Error! Too many closing parentheses in the expression.\n");
                delete_stack(value_stack);
                delete_stack(operator_stack);
                return -1;
            }
            pop(operator_stack);
        }
        else if (strchr("+-*/", expression[i]))
        {
            while (!is_empty(operator_stack) && get_precedence(expression[i]) <= get_precedence(operator_stack->top->value))
            {
                char op = (char)pop(operator_stack);
                int b = pop(value_stack);
                int a = pop(value_stack);
                int result;
                switch (op)
                {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    if (b == 0)
                    {
                        printf("Error! Division by zero.\n");
                        delete_stack(value_stack);
                        delete_stack(operator_stack);
                        return -1;
                    }
                    result = a / b;
                    break;
                }
                printf("%d %c %d = %d.\n", a, op, b, result); // Print the steps
                push(value_stack, result);
            }
            push(operator_stack, expression[i]);
        }
    }

    while (!is_empty(operator_stack))
    {
        char op = (char)pop(operator_stack);
        int b = pop(value_stack);
        int a = pop(value_stack);
        int result;

        switch (op)
        {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            if (b == 0)
            {
                printf("Error! Division by zero.\n");
                delete_stack(value_stack);
                delete_stack(operator_stack);
                return -1;
            }
            result = a / b;
            break;
        }
        printf("%d %c %d = %d.\n", a, op, b, result); // Print the steps
        push(value_stack, result);
    }

    if (value_stack->top->next != NULL)
    {
        printf("Error! Too many values in the expression.\n");
        delete_stack(value_stack);
        delete_stack(operator_stack);
        return -1;
    }

    int final_result = pop(value_stack);
    delete_stack(value_stack);
    delete_stack(operator_stack);

    if (final_result == 24)
    {
        return final_result;
    }
    else
    {
        return NOT_TWENTY_FOUR;
    }
}


/*
    Returns 1 if the expression is valid, 0 otherwise.

    expression: The expression to check.

    Returns: 1 if the expression is valid, 0 otherwise.

    Note: The expression is assumed to be composed of integers and the operators +, -, *, and /. Parentheses are also allowed.
*/
void load_puzzles(const char *filename, int puzzles[][4], int *num_puzzles)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Error! Could not open file %s.\n", filename);
        exit(1);
    }
    *num_puzzles = 0;
    while (fscanf(file, "%d %d %d %d", &puzzles[*num_puzzles][0], &puzzles[*num_puzzles][1],
                  &puzzles[*num_puzzles][2], &puzzles[*num_puzzles][3]) == 4)
    {
        (*num_puzzles)++;
    }
    fclose(file);
}

int main()
{
    srand(1);
    int easy_puzzles[100][4], medium_puzzles[100][4], hard_puzzles[100][4];
    int num_easy_puzzles, num_medium_puzzles, num_hard_puzzles;
    load_puzzles("easy.txt", easy_puzzles, &num_easy_puzzles);
    load_puzzles("medium.txt", medium_puzzles, &num_medium_puzzles);
    load_puzzles("hard.txt", hard_puzzles, &num_hard_puzzles);

    printf("Welcome to the game of TwentyFour Part Two!\n");
    printf("Use each of the four numbers shown exactly once, \n");
    printf("combining them somehow with the basic mathematical operators (+,-,*,/) \n");
    printf("to yield the value twenty-four.\n");

    int exit_game = 0;
    while (!exit_game)
    {
        printf("Choose your difficulty level: E for easy, M for medium, and H for hard (default is easy).\n");
        printf("Your choice --> ");
        char difficulty;
        fflush(stdout);
        scanf(" %c", &difficulty);

        int puzzle_index;
        int numbers[4];

        while (1)
        {

            switch (difficulty)
            {
            case 'E':
                puzzle_index = rand() % num_easy_puzzles;
                memcpy(numbers, easy_puzzles[puzzle_index], sizeof(numbers));
                break;
            case 'M':
                puzzle_index = rand() % num_medium_puzzles;
                memcpy(numbers, medium_puzzles[puzzle_index], sizeof(numbers));
                break;
            case 'H':
                puzzle_index = rand() % num_hard_puzzles;
                memcpy(numbers, hard_puzzles[puzzle_index], sizeof(numbers));
                break;
            default:
                difficulty = 'E';
                puzzle_index = rand() % num_easy_puzzles;
                memcpy(numbers, easy_puzzles[puzzle_index], sizeof(numbers));
                break;
            }

            printf("The numbers to use are: %d, %d, %d, %d.\n", numbers[0], numbers[1], numbers[2], numbers[3]);

            printf("Enter your solution: ");
            char solution[1000];
            fflush(stdout);
            scanf(" %[^\n]s", solution);

            int valid_symbols = 1;
            for (int i = 0; solution[i]; ++i)
            {
                if (!is_valid_symbol(solution[i]))
                {
                    valid_symbols = 0;
                    break;
                }
            }

            if (!valid_symbols)
            {
                printf("Error! Invalid symbol entered. Please try again.\n\n");
                continue;
            }

            if (!is_valid_solution(solution, numbers))
            {
                printf("Error! You must use all four numbers, and use each one only once. Please try again.\n\n");
                continue;
            }

            int result = evaluate_expression(solution, numbers);

            if (result == 24)
            {
                printf("Well done! You are a math genius.\n");
            }
            else if (result == NOT_TWENTY_FOUR)
            {
                printf("Sorry. Your solution did not evaluate to 24.\n");
            }

            printf("\nEnter: \t1 to play again,\n");
            printf("\t2 to change the difficulty level and then play again, or\n");
            printf("\t3 to exit the program.\n");
            printf("Your choice --> ");
            int choice;
            fflush(stdout);
            scanf("%d", &choice);

            if (choice == 3)
            {
                exit_game = 1;
                break;
            }
            else if (choice == 2)
            {
                break;
            }
            else
            {
                continue;
            }
        }
    }

    printf("\nThanks for playing!\n");
    printf("Exiting...\n");

    return 0;
}