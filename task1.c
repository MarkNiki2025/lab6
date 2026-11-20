#include <stdio.h>
#include <stdlib.h>
#define NUMOFDEFAULTPOINTS 5
#define checkMem(a) do { \
    if ((a) == NULL) { \
        printf("Problems with mem\n"); \
        return 1; \
    } \
} while (0)

typedef struct {
    int from;
    int to;
    int weight;
}Edge ;

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

int countEdges(int *wMatrix, int numOfPoints) {
    int count = 0;

    for (int i = 0; i < numOfPoints; i++) {
        for (int j = i + 1; j < numOfPoints; j++) {
            if (*(wMatrix + i * numOfPoints + j) != 0) {
                count++;
            }
        }
    }

    return count;
}

void matrixToEdges(int *wMatrix, Edge *edges, int numOfPoints) {
    int k = 0;

    for (int i = 0; i < numOfPoints; i++) {
        for (int j = i + 1; j < numOfPoints; j++) {
            int weight = *(wMatrix + i * numOfPoints + j);

            if (weight != 0) {
                edges[k].from = i;
                edges[k].to = j;
                edges[k].weight = weight;
                k++;
            }
        }
    }
}

void printEdges(Edge *edges, int count) {
    printf("\nEdges:\n");

    for (int i = 0; i < count; i++) {
        printf("%c -- %c : %d\n",
            'A' + edges[i].from,
            'A' + edges[i].to,
            edges[i].weight
        );
    }
}

void swap(Edge *a, Edge *b) {
    Edge temp = *a;
    *a = *b;
    *b = temp;
}

int partition(Edge *edges, int low, int high) {
    int pivot = edges[high].weight;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (edges[j].weight <= pivot) {
            i++;
            swap(&edges[i], &edges[j]);
        }
    }

    swap(&edges[i + 1], &edges[high]);

    return i + 1;
}

void quickSort(Edge *edges, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(edges, low, high);

        quickSort(edges, low, pivotIndex - 1);
        quickSort(edges, pivotIndex + 1, high);
    }
}

void algorithmKraskala(Edge *edges, int numOfPoints, int numOfEdges,int *result) {
    int parent[numOfPoints];
    int edgesByAl[numOfPoints - 1];
    int count = 0;

    for (int i = 0; i < numOfPoints; i++) {
        parent[i] = i;
    }

    for (int i = 0; i < numOfEdges && count < numOfPoints - 1; i++) {
        int a = edges[i].from;
        int b = edges[i].to;

        int rootA = a;
        while (parent[rootA] != rootA) {
            rootA = parent[rootA];
        }

        int rootB = b;
        while (parent[rootB] != rootB) {
            rootB = parent[rootB];
        }

        if (rootA == rootB) continue;

        parent[rootB] = rootA;

        edgesByAl[count] = i;
        count++;
    }
    if (count != numOfPoints - 1) {
        printf("Graph is not connected!\n");
        return;
    }
    for(int i = 0; i < numOfPoints - 1; i++){
        result[i] = edgesByAl[i];
    }
        
}

int main() {
    int *wMatrix = calloc(NUMOFDEFAULTPOINTS * NUMOFDEFAULTPOINTS, sizeof(int));
    int choice = 0;
    int edgesCount;
    int numOfPoints = 0;
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
        numOfPoints = NUMOFDEFAULTPOINTS;
    }else {
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
        
    }

    printMatrix(wMatrix,numOfPoints);
    edgesCount = countEdges(wMatrix, numOfPoints);
    Edge *edges = calloc(edgesCount,sizeof(Edge));
    checkMem(edges);
    matrixToEdges(wMatrix, edges, numOfPoints);
    quickSort(edges, 0, edgesCount - 1);
    int *indexesForTree = calloc(numOfPoints-1,sizeof(int));
    Edge *edgesForTree = calloc(numOfPoints-1,sizeof(Edge));
    
    algorithmKraskala(edges,numOfPoints,edgesCount,indexesForTree);
    for (int i = 0; i < numOfPoints-1; i++){
        edgesForTree[i] = edges[indexesForTree[i]];
        printf("%d) \n",i+1);
        printEdges(edgesForTree,i+1);
        printf("\n");
    }
    printEdges(edgesForTree,numOfPoints-1);
    free(edges);
    free(wMatrix);
    return 0;
}