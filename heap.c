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
  int i;
  for(i=0; i<pq->size ;i++){
    if(i == pq->size-1){
      pq->heapArray[0].data = pq->heapArray[i].data;
      pq->heapArray[0].priority = pq->heapArray[i].priority;
      pq->size--;
    }
  }
  int cont = 0;
  void* auxData;
  int auxPriority;
  while(cont < pq->capac){
    if((pq->heapArray[cont].priority < pq->heapArray[cont + 1].priority) && (pq->heapArray[cont].priority < pq->heapArray[cont + 2].priority)){
      if(pq->heapArray[cont + 1].priority > pq->heapArray[cont + 2].priority){
        auxData = pq->heapArray[cont + 1].data;
        pq->heapArray[cont + 1].data = pq->heapArray[cont].data;
        pq->heapArray[cont].data = auxData;
        auxPriority = pq->heapArray[cont + 1].priority;
        pq->heapArray[cont + 1].priority = pq->heapArray[cont].priority;
        pq->heapArray[cont].priority = auxPriority;
      }
      else{
        auxData = pq->heapArray[cont + 2].data;
        pq->heapArray[cont + 2].data = pq->heapArray[cont].data;
        pq->heapArray[cont].data = auxData;
        auxPriority = pq->heapArray[cont + 2].priority;
        pq->heapArray[cont + 2].priority = pq->heapArray[cont].priority;
        pq->heapArray[cont].priority = auxPriority;
      }
    }
    cont++;
  }
}

Heap* createHeap(){
    Heap* arreglo = (Heap*) malloc(sizeof(Heap));
    arreglo->heapArray = (heapElem*) calloc(3,sizeof(heapElem));
    arreglo->size = 0;
    arreglo->capac = 3;
    return arreglo;
}
