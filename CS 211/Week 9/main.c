#include <stdio.h>
#include <stdlib.h>


struct course {
    int marks;
    char subject[30];
};

int main() {
    struct course *ptr;
    int no_of_records;

    char *temp = "Science";
    int per_temp = 98;

    printf("Enter the number fo records: ");
    scanf("%d", no_of_records);
    printf("\n");

    // Memory allocation for no_of_records struct
    ptr = (struct course *) malloc(no_of_records * sizeof(struct course));

    for (int i = 0; i < no_of_records; i++) {
        printf("Enter subject and grades(in percentage): ");
        scanf("%s %d", (ptr + i)->subject, &(ptr + i)->marks);
    }


    printf("\n");

    printf("Displaying Information Stored in the Data:\n");

    for (int i = 0; i < no_of_records; i++) {
        printf("%s\t- %d%c\n", (ptr + i)->subject, (ptr + i)->marks, '%');
    }

    free(ptr);

    printf("\n");

    return 0;
}