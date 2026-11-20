#include <stdio.h>
#include <stdlib.h>
#define NUMOFDEFAULTPOINTS 5
#define checkMem(a) do { \
    if ((a) == NULL) { \
        printf("Problems with mem\n"); \
        return 1; \
    } \
} while (0)

void readDataFromFile(FILE *file, int *wMatrix) {
    for (int i = 0; i < NUMOFDEFAULTPOINTS; i++) {
        for (int j = 0; j < NUMOFDEFAULTPOINTS; j++) {
            fscanf(file, "%d", wMatrix + i * NUMOFDEFAULTPOINTS + j);
        }
    }
}
void printMatrix(int *wMatrix,int numofpoints) {
    printf("\n     ");

    for (int j = 0; j < numofpoints; j++) {
        printf("%5c", 'A' + j);
    }

    printf("\n    ");
    for (int j = 0; j < numofpoints; j++) {
        printf("-----");
    }
    printf("\n");

    for (int i = 0; i < numofpoints; i++) {
        printf("%3c |", 'A' + i);

        for (int j = 0; j < numofpoints; j++) {
            int value = *(wMatrix + i * numofpoints + j);

            printf("%5d", value);
        }

        printf("\n");
    }

    printf("\n");
}

int main() {
    int *wMatrix = calloc(NUMOFDEFAULTPOINTS * NUMOFDEFAULTPOINTS, sizeof(int));
    int choice = 0;
    checkMem(wMatrix);

    printf("Hello! Where will I use info? \n");
    printf("Default value - 1\n");
    printf("Custom value - 2\n");
    printf("Your choice: ");
    if (!scanf("%d",&choice) || choice < 1 || choice > 2) {
        printf("Incorect num");
        return 1;
    }
    if(choice == 1){
        FILE *file = fopen("task1.txt","r");
        if (file == NULL) {
            printf("Problems with file\n");
            free(wMatrix); 
            return 1;
        }
        readDataFromFile(file,wMatrix);
        fclose(file);
        printMatrix(wMatrix,NUMOFDEFAULTPOINTS);

    }else {
        int numOfPoints = 0;
        printf("Write nums of point: ");
        if (!scanf("%d",&numOfPoints)) {
            printf("Incorrect num");
            return 1;
        }
        int *temp = realloc(wMatrix, numOfPoints * numOfPoints * sizeof(int));
        checkMem(temp);
        wMatrix = temp;
        printf ("Now You will write weights\n");
        printf("0 - is absent shape \n");
        for(int i = 0; i < numOfPoints; i++) {
            for (int j = 0; j < numOfPoints; j++) {
                printf("Your weight %d.%d: ",i+1,j+1);
                if (!scanf("%d",wMatrix + i*numOfPoints + j) ||
                *(wMatrix + i*numOfPoints + j) < 0){
                    printf("Incorrect num \n");
                    return 1;
                }
            }
        }
        printMatrix(wMatrix,numOfPoints);

    }
    
    free(wMatrix);
    return 0;
}