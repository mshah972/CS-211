# C Notes


## Pass by Value:

In pass by value, a copy of the variable is created and passed to the function. Any changes made to the variable inside the function will not affect the original variable.

```c
#include <stdio.h>

void increment(int num) {
    num++;
    printf("Inside function: num = %d\n", num);
}

int main() {
    int num = 5;
    printf("Before function call: num = %d\n", num);
    increment(num);
    printf("After function call: num = %d\n", num);
    return 0;
}

Output:

Before function call: num = 5
Inside function: num = 6
After function call: num = 5
```

In the above example, the value of the variable **`num`** is passed to the function**`increment()`** by value. Inside the function, a copy of **`num`** is created and incremented. However, this does not affect the original value of **`num`** in the **`main()`** function, which remains unchanged.

---

## Pass by Reference:

In pass by reference, the address of the variable is passed to the function, and any changes made to the variable inside the function will affect the original variable.

```c
#include <stdio.h>

void increment(int *num_ptr) {
    (*num_ptr)++;
    printf("Inside function: num = %d\n", *num_ptr);
}

int main() {
    int num = 5;
    printf("Before function call: num = %d\n", num);
    increment(&num);
    printf("After function call: num = %d\n", num);
    return 0;
}

Output:

Before function call: num = 5
Inside function: num = 6
After function call: num = 6
```

In the above example, the address of the variable **`num`** is passed to the function **`increment()`** by reference using a pointer. Inside the function, the value of **`num`** is incremented using the dereferenced pointer. This change affects the original value of **`num`** in the **`main()`** function.

Note: It is important to ensure that the pointer passed as an argument points to a valid memory location. Otherwise, the program may crash or behave unexpectedly.

---

## Type of Pointers:

Pointers are variables that store the memory address of other variables.

```c
int num = 5;
int *num_ptr = &num;
```

In the above example, **`num_ptr`** is a pointer variable that stores the memory address of the variable **`num`** using the address-of operator **`&`** .

Pointers can be dereferenced using the indirection operator **`*`** to access the value stored in the memory location pointed to by the pointer.

```c
int num = 5;
int *num_ptr = &num;
printf("Value of num = %d\n", *num_ptr);
```

In the above example, the value of **`num`** is accessed using the dereferenced pointer **`*num_ptr`** .

Pointers can be used to pass arguments to functions by reference, allowing the function to modify the original value of the argument.

```c
void increment(int *num_ptr) {
    (*num_ptr)++;
}

int main() {
    int num = 5;
    increment(&num);
    printf("Value of num = %d\n", num);
    return 0;
}
```

In the above example, the address of **`num`** is passed to the function **`increment()`** using a pointer. Inside the function, the value of **`num`** is incremented using the dereferenced pointer. This change affects the original value of **`num`** in the **`main()`** function.

 

Pointers can be used to dynamically allocate memory using the **`malloc()`** function.

```c
int *num_ptr = (int*)malloc(sizeof(int));
*num_ptr = 5;
printf("Value of num = %d\n", *num_ptr);
free(num_ptr);
```

In the above example, **`malloc()`** is used to allocate memory dynamically for an integer using the **`sizeof()`** operator. The pointer **`num_ptr`** is then used to access and set the value of the allocated memory using the dereferenced pointer. Finally, **`free()`** is used to deallocate the dynamically allocated memory.

Pointers can be used to create and manipulate arrays.

```c
int arr[5] = {1, 2, 3, 4, 5};
int *arr_ptr = arr;
printf("Third element of array: %d\n", *(arr_ptr + 2));
```

In the above example, the pointer **`arr_ptr`** is used to point to the first element of the array **`arr`** . The third element of the array is accessed using pointer arithmetic by adding 2 to **`arr_ptr`** and dereferencing the resulting pointer.

Pointers can be used to create and manipulate structures.

```c
struct student {
    char name[20];
    int age;
};

struct student stu1 = {"John", 20};
struct student *stu_ptr = &stu1;
printf("Name: %s, Age: %d\n", stu_ptr->name, stu_ptr->age);
```

In the above example, a structure **`student`** is defined with two members **`name`** and **`age`** . An instance of the structure **`stu1`** is created and initialized. A pointer **`stu_ptr`** is then used to point to the structure **`stu1`** . The members of the structure are accessed using the arrow operator **`->`** .

---

### Pointer incrementation

Incrementing a pointer means moving the pointer to the next memory location of the same data type. Here are some notes on incrementing pointers in C with an example:

1. Pointer arithmetic is used to increment a pointer.
2. When a pointer is incremented, it is moved to the next memory location based on the size of the data type it points to.
3. The increment operator **`++`** can be used to increment a pointer.
4. It is important to be careful when incrementing pointers to avoid accessing memory locations outside the allocated memory range.

```c
int arr[] = {1, 2, 3, 4, 5};
int *ptr = arr;  // initialize pointer to first element of array

// print array using pointer incrementation
for (int i = 0; i < 5; i++) {
    printf("%d ", *ptr);  // dereference pointer to print value
    ptr++;  // increment pointer to next element
}
```

In the above example, an integer array **`arr`** is declared and initialized. A pointer **`ptr`** is initialized to point to the first element of the array using the array name. A **`for`** loop is then used to print the values of the array using the pointer **`ptr`**. Inside the loop, the pointer is dereferenced to print the value of the current element, and then incremented using the increment operator **`++`** to move to the next element in the array.

The output of the above code will be:

```c
1 2 3 4 5
```

Note that the pointer **`ptr`** is incremented by the size of the data type it points to, which in this case is an integer (4 bytes). Therefore, after the first iteration of the loop, **`ptr`** points to the second element of the array, after the second iteration it points to the third element, and so on, until it points to the last element of the array after the final iteration.

---

### Pointer value incrementation

To increment the value that is being pointed to by a pointer in C, we can use the dereference operator **`*`** to access the value and the increment operator **`++`** to increase it. Here are some notes on incrementing the value that is being pointed to by a pointer with an example:

1. To increment the value that is being pointed to by a pointer, we need to dereference the pointer to access the value.
2. The dereference operator **``** is used to access the value pointed to by a pointer.
3. The increment operator **`++`** can be used to increase the value.
4. We need to be careful when incrementing the value that is being pointed to by a pointer to avoid accessing memory locations outside the allocated memory range.

```c
int num = 5;
int *ptr = &num;  // initialize pointer to variable

printf("Value of num before increment: %d\n", *ptr);  // dereference pointer to print value
(*ptr)++;  // increment value pointed to by pointer using dereference operator

printf("Value of num after increment: %d\n", *ptr);  // dereference pointer to print updated value
```

In the above example, an integer variable **`num`** is declared and initialized. A pointer **`ptr`** is initialized to point to the variable **`num`** using the address-of operator **`&`**. The value of **`num`** is then printed before and after incrementing it using the pointer **`ptr`**. Inside the **`printf()`** statements, the pointer is dereferenced using the dereference operator **`*`** to access the value of the variable. Inside the increment statement, the pointer is also dereferenced using parentheses to access the value of the variable, which is then incremented using the increment operator **`++`**.

The output of the above code will be:

```c
Value of num before increment: 5
Value of num after increment: 6
```

Note that in the above example, the value of **`num`** is incremented using the pointer **`ptr`** . This change affects the original value of **`num`** in the memory location pointed to by the pointer.

---

## Static, Stack, and Heap Memory

In C, memory is divided into three main parts: static memory, stack memory, and heap memory. Each of these parts of memory serves a different purpose and has its own characteristics. Here are some notes on static, stack, and heap memory in C with examples:

- Static memory is used to store global variables, static variables, and string literals.

```c
#include <stdio.h>

// global variable stored in static memory
int global_var;

// static variable stored in static memory
static int static_var;

int main() {
    // string literal stored in static memory
    char *str = "Hello, world!";
    printf("%s\n", str);
    return 0;
}
```

In the above example, a global variable **`global_var`** and a static variable **`static_var`** are declared outside of the **`main()`** function. These variables are stored in static memory and have a lifetime that lasts for the entire program execution. Inside the **`main()`** function, a string literal **`"Hello, world!"`** is assigned to a character pointer **`str`**. This string literal is also stored in static memory and has a lifetime that lasts for the entire program execution.

- Stack memory is used to store local variables and function parameters.

```c
#include <stdio.h>

void my_function(int param) {
    // local variable stored in stack memory
    int local_var = param + 1;
    printf("Local variable value: %d\n", local_var);
}

int main() {
    int num = 5;
    my_function(num);
    return 0;
}
```

In the above example, a function **`my_function()`** is declared with a parameter **`param`**. Inside the function, a local variable **`local_var`** is declared and initialized to **`param + 1`**. This variable is stored in stack memory and has a lifetime that lasts for the duration of the function call. Inside the **`main()`** function, an integer variable **`num`** is declared and initialized to **`5`**. This variable is also stored in stack memory and has a lifetime that lasts for the duration of the **`main()`** function.

- Heap memory is used to allocate memory dynamically during program execution.

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr;
    ptr = (int*)malloc(sizeof(int));  // allocate memory on heap
    *ptr = 5;  // store value in allocated memory
    printf("Value: %d\n", *ptr);
    free(ptr);  // release allocated memory
    return 0;
}
```

In the above example, a pointer **`ptr`** is declared to store a memory address on the heap. The **`malloc()`** function is then called to allocate memory on the heap for an integer value. The size of the allocated memory is determined by the **`sizeof()`** operator. The integer value **`5`** is then stored in the allocated memory using the dereference operator **`*`**. This memory has a lifetime that lasts until it is explicitly released using the **`free()`** function. Finally, the allocated memory is released using the **`free()`** function to prevent memory leaks.

Note that the heap memory is not automatically managed by the C runtime system, and it is the responsibility of the programmer to ensure that all allocated memory is properly released to prevent memory leaks.

---