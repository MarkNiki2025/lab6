#include <stdio.h>
#include <stdlib.h>
#define NUMOFDEFAULTPOINTS 5
void readDataFromFile(FILE *file, int *wMatrix) {
    for (int i = 0; i < NUMOFDEFAULTPOINTS; i++) {
        for (int j = 0; j < NUMOFDEFAULTPOINTS; j++) {
            fscanf(file, "%d", wMatrix + i * NUMOFDEFAULTPOINTS + j);
        }
    }
}
void printMatrix(int *wMatrix) {
    printf("\n     ");

    for (int j = 0; j < NUMOFDEFAULTPOINTS; j++) {
        printf("%5c", 'A' + j);
    }

    printf("\n    ");
    for (int j = 0; j < NUMOFDEFAULTPOINTS; j++) {
        printf("-----");
    }
    printf("\n");

    for (int i = 0; i < NUMOFDEFAULTPOINTS; i++) {
        printf("%3c |", 'A' + i);

        for (int j = 0; j < NUMOFDEFAULTPOINTS; j++) {
            int value = *(wMatrix + i * NUMOFDEFAULTPOINTS + j);

            printf("%5d", value);
        }

        printf("\n");
    }

    printf("\n");
}

int main() {
    int *wMatrix = calloc(NUMOFDEFAULTPOINTS * NUMOFDEFAULTPOINTS, sizeof(int));
    if (wMatrix == NULL) {
        printf("Problems with mem");
        free(wMatrix);
        return 1;
    }
    FILE *file = fopen("task1.txt","r");
    if (file == NULL) {
        printf("Problems with file\n");
        free(wMatrix); 
        return 1;
    }
    readDataFromFile(file,wMatrix);
    fclose(file);
    printMatrix(wMatrix);
    free(wMatrix);
    return 0;
}