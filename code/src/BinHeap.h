#ifndef BINHEAP_H
#define BINHEAP_H

#include <stdio.h>
#include <stdlib.h>

#define MinData (-1)
#define MinPQSize (1)

struct HeapStruct;
typedef struct HeapStruct *PriorityQueue;

PriorityQueue Initialize( int MaxElements );
void Destroy( PriorityQueue H );
void MakeEmpty( PriorityQueue H );
void Insert( int X, int Index, PriorityQueue H );
int DeleteMin( PriorityQueue H );
int IsEmpty( PriorityQueue H );
int IsFull( PriorityQueue H );


#endif
