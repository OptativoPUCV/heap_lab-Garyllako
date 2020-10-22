#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;


void* heap_top(Heap* pq){
    if(pq->size == 0){
      return NULL;
    }
    else{
      return pq->heapArray[0].data;
    }
}


void heap_push(Heap* pq, void* data, int priority){
  if((pq->size + 1) > pq->capac){
    pq->capac = (pq->capac) * 2 + 1;
    pq->heapArray = realloc(pq->heapArray,(pq->capac)*sizeof(heapElem));
  }
  int actual = pq->size;
  while(actual > 0 && pq->heapArray[(actual - 1) / 2].priority < priority){
    pq->heapArray[actual] = pq->heapArray[(actual - 1) / 2];
    actual = (actual - 1) / 2;
  }
  pq->heapArray[actual].priority = priority;
  pq->heapArray[actual].data = data;
  pq->size++;
}


void heap_pop(Heap* pq){
  void* auxData = pq->heapArray[0].data;
  int auxPriority = pq->heapArray[0].priority;
  int i;
  for(i=0; i < pq->size ;i++){
    if(i == pq->size-1){
      printf("%d",i);
      pq->heapArray[0].data = pq->heapArray[i].data;
      pq->heapArray[i].data = auxData;
      pq->heapArray[0].priority = pq->heapArray[i].priority;
      pq->heapArray[i].priority = auxPriority;
    }
  }
  pq->size--;


}

Heap* createHeap(){
    Heap* arreglo = (Heap*) malloc(sizeof(Heap));
    arreglo->heapArray = (heapElem*) calloc(3,sizeof(heapElem));
    arreglo->size = 0;
    arreglo->capac = 3;
    return arreglo;
}
