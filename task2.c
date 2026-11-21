#include <stdio.h>
#define  NUMOFDEFAULTPOINTS 10

void readDataFromFile(FILE *file, int *arr) {
    for (int i = 0; i < NUMOFDEFAULTPOINTS; i++) {
        fscanf(file, "%d", arr+i);
    }
}

int main () {
    FILE *file = fopen("task2.txt","r");
    return 0;
}