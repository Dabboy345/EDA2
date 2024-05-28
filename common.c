#include "common.h"

int get_valid_input(int first, int size) { //We were having many problems with the scanf so we asked Chat Gpt to help it with us 
    int a;
    int valid = 0;
    while (!valid) { //if valid is 1 it is true and then the while will stop        
        if (scanf("%d", &a) != 1) {
            // Clear the invalid input
            while (getchar() != '\n'); // Discard invalid input until a newline is found
            printf("\n----> Invalid input. Please enter a number between %d and %d\n\n", first, size);
        } else if (a < first || a > size) {
            printf("\n----> Invalid input. Please enter a number between %d and %d\n\n", first, size);
        } else {
            valid = 1; // Valid input received
        }
    }
    return a;
}

void pause(){
    int a;
    printf("-Type anything to continue-\n");
    scanf("%d", &a);
    while (getchar() != '\n');
}
