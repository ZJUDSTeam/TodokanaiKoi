#ifndef RECONSTRUCT_H
#define RECONSTRUCT_H
/*
 * here are the declarations of functions and data structures we used
 */

#include "BinHeap.h"

#define EmptyCell (-1)

typedef int Vertex;
typedef struct AdjVNode *PtrToAdjVNode;
typedef struct VNode *AdjList;
typedef struct AdjGph *AdjGraph;	
typedef struct HashTbl *HashTable;

void TopSort( AdjGraph G );
int Hash( int Key, int TableSize );
AdjGraph BuildAdjGraph( HashTable H );
HashTable InitHashTable( int TableSize );

#endif
