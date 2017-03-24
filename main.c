#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define leftChild(i) (2*i)
#define rightChild(i) ((2*i)+1)
#define parent(i) (i/2)

int bu_assignments = 0;
int bu_comparisons = 0;

int td_assignments = 0;
int td_comparisons = 0;

int heap[10001];

void swap(int *a, int i, int j){
    int temp;
    temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void maxHeapifyBU(int *a, int i, int n){

    int largest;

    bu_comparisons++;
    if(i < n/2 && a[i] < a[leftChild(i)]){
        largest = leftChild(i);
    }
    else{
        largest = i;
    }

    bu_comparisons++;
    if(i < n/2 && a[largest] < a[rightChild(i)]){
        largest = rightChild(i);

    }

    if(i != largest){
        swap(a, i, largest);
        bu_assignments += 3;
        maxHeapifyBU(a, largest, n);
    }
}


void buildHeapBU(int *a, int n){  //construieste heap prin metoda bottom up
    int i;
    for(i = (n/2); i > 0; i--){
        maxHeapifyBU(a, i, n);
    }
}

void HeapSortBU(int *a, int n){ //bottom up
    int i, k = n;
    buildHeapBU(a, n);
    for(i = n-1; i > 1; i--){
        swap(a, 1, i);
        k = k - 1;
        maxHeapifyBU(a, 1, k);
    }

}

void insert(int x, int i){
    heap[i] = x;
    td_assignments++;
    td_comparisons++;
    while(parent(i) >= 1 && heap[parent(i)] < heap[i]){
        td_comparisons++;
        swap(heap, parent(i), i);
        td_assignments+=3;
        i = parent(i);
    }


}

void buildHeapTD(int *a, int n){ //construieste heap folosind metoda top down
    int i;
    for(i = 1; i < n; i++){
        insert(a[i], i);
    }

}

void HeapSortTD(int *a, int n){ //sortare top down
    int i;
    buildHeapTD(a, n);
    for(i = n - 1; i > 0; i--){
        swap(heap, 1, i);
        buildHeapTD(heap, i);
    }
}


int *getArray(int n){ //genereaza un sir random de numere
    int i;
    int *a = (int*)malloc(n*sizeof(int));
    srand(time(NULL));
    for(i = 1; i < n; i++){
        a[i] = rand()%20;
    }
    return a;
}


void printArray(int *a, int n){ //afiseaza in consola sirul
    int i;
    for(i = 1; i < n; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
}


int main()
{
    int i, j;
    int *array;
   FILE *f = fopen("assignments.csv", "a");
    FILE *g = fopen("comparisons.csv", "a");
    FILE *h = fopen("sum.csv", "a");

    if(f == NULL || g == NULL || h == NULL){
        puts("File not found!");
        return -1;
    }

    for(i = 100; i <= 10000; i=i+100){
        for(j = 0; j < 5; j++){
            array = getArray(i);
            buildHeapTD(array, i);
            buildHeapBU(array, i);
        }
        bu_assignments = bu_assignments / 5;
        bu_comparisons = bu_comparisons / 5;
        td_assignments = td_assignments / 5;
        td_comparisons = td_comparisons / 5;

        fprintf(f, "%d;%d;%d", i, bu_assignments, td_assignments);
        fprintf(f,"\n");
        fprintf(g, "%d;%d;%d", i, bu_assignments, td_comparisons);
        fprintf(g,"\n");
        fprintf(h, "%d;%d;%d", i, bu_assignments+bu_assignments, td_assignments+td_comparisons);
        fprintf(h,"\n");
        bu_assignments = 0;
        bu_comparisons = 0;
        td_assignments = 0;
        td_comparisons = 0;
    }

    fclose(f);
    fclose(g);
    fclose(h);



    free(array);


    return 0;

}

