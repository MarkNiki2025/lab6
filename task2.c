#include <stdio.h>
#include <stdlib.h>
#define  NUMOFDEFAULTPOINTS 10
#define checkMem(a) do { \
    if ((a) == NULL) { \
        printf("Problems with mem\n"); \
        return 1; \
    } \
} while (0)

typedef struct {
    int from;
    int to;
}Edge ;

void printEdges(Edge *edges, int count) {
    printf("\nEdges:\n");

    for (int i = 0; i < count; i++) {
        printf("%d -- %d \n",
            edges[i].from,
            edges[i].to
        );
    }
}

void readDataFromFile(FILE *file, int *arr) {
    for (int i = 0; i < NUMOFDEFAULTPOINTS; i++) {
        fscanf(file, "%d,", arr+i);
    }
}
void algorithm(Edge *edges, int *arr, int lengthOfCode) {
    int verticesCount = lengthOfCode + 2;

    int *degree = calloc(verticesCount + 1, sizeof(int));

    for (int i = 1; i <= verticesCount; i++) {
        degree[i] = 1;
    }

    for (int i = 0; i < lengthOfCode; i++) {
        degree[arr[i]]++;
    }

    for (int i = 0; i < lengthOfCode; i++) {

        int leaf = 1;

        while (degree[leaf] != 1) {
            leaf++;
        }

        edges[i].from = leaf;
        edges[i].to = arr[i];

        degree[leaf]--;
        degree[arr[i]]--;
    }

    int first = 0;
    int second = 0;

    for (int i = 1; i <= verticesCount; i++) {
        if (degree[i] == 1) {
            if (first == 0) {
                first = i;
            } else {
                second = i;
                break;
            }
        }
    }

    edges[lengthOfCode].from = first;
    edges[lengthOfCode].to = second;

    free(degree);
}

int main () {
    int *code = calloc(NUMOFDEFAULTPOINTS,sizeof(int));
    checkMem(code);
    int choice = 0;
    int lengthOfCode = NUMOFDEFAULTPOINTS;
    printf("Hello! Where will I use info? \n");
    printf("Default value - 1\n");
    printf("Custom value - 2\n");
    printf("Your choice: ");

    if (!scanf("%d",&choice) || choice < 1 || choice > 2) {
        printf("Incorect num");
        return 1;
    }
    if (choice == 1){
        FILE *file = fopen("task2.txt","r");   
        readDataFromFile(file,code);
    }else{
        printf("Write length of your code\n");
        printf("Length: ");
        if (!scanf("%d",&lengthOfCode) || lengthOfCode < 1) {
            printf("Incorect num");
            return 1;
        }
        int *temp = realloc(code, lengthOfCode * sizeof(int));
        checkMem(temp);
        checkMem(code);
        code = temp;
        printf("Okey go to your code\n");
        for (int i = 0; i < lengthOfCode; i++){
            printf("Your num: ");
            if(!scanf("%d",code + i)||*(code+i) < 0){
                printf("Incorrect num");
                return 1;
            }
        }
    }
    Edge *edges = calloc(lengthOfCode+1,sizeof(Edge));
    for(int i = 0; i < lengthOfCode; i++){
        printf("%d ", *(code +i));
    }
    algorithm(edges,code,lengthOfCode);
    printEdges(edges,lengthOfCode+1);
    return 0;
}