#include "BinHeap.h"

typedef struct Element
{
    int Index;
    int Key;
}ElementType;

struct HeapStruct
{
    int Capacity;
    int Size;
    ElementType *Elements;
};


PriorityQueue Initialize( int MaxElemnets )
{
    PriorityQueue H;
    if( MaxElemnets < MinPQSize ){
        printf( "Priority queue size is too small" );
        exit( 1 );
    }

    H = malloc( sizeof( struct HeapStruct ) );
    if( H == NULL ){
        printf( "Out of Space!!!" );
        exit( 1 );
    }

    H->Elements = malloc( (MaxElemnets + 1) * sizeof(ElementType));

    if( H->Elements == NULL ){
        printf( "Out of Space!!!" );
        exit( 1 );
    }

    H->Capacity = MaxElemnets;
    H->Size = 0;
    H->Elements[ 0 ].Key = MinData;
    H->Elements[ 0 ].Index = -1;

    return H;
}

int DeleteMin( PriorityQueue H ){
    int i, Child;

    ElementType MinElement, LastElement;

    if( IsEmpty( H ) ){
        printf( "Priority queue is empty" );
        return H->Elements[ 0 ].Index;
    }

    MinElement = H->Elements[ 1 ];
    LastElement = H->Elements[ H->Size-- ];

    for( i = 1; i * 2 <= H->Size; i = Child ){
        /* Find Smaller child */
        Child = i * 2;
        if( Child != H->Size && H->Elements[ Child +1 ].Key < H->Elements[ Child ].Key )
            Child++;

        /* Percolate one level */
        if( LastElement.Key > H->Elements[ Child ].Key )
            H->Elements[ i ] = H->Elements[ Child ];
        else
            break;
    }
    H->Elements[i] = LastElement;
    return MinElement.Index;

}

void Insert( int X, int Index, PriorityQueue H )
{
    int i;
    if( IsFull( H ) ){
        printf( "Priority queue is full" );
        return;
    }

    for( i = ++H->Size; H->Elements[ i / 2 ].Key > X; i /= 2 )
        H->Elements[ i ] = H->Elements[ i / 2 ];

    H->Elements[i].Key = X;
    H->Elements[i].Index = Index;
}


int IsEmpty( PriorityQueue H )
{
    return H->Size == 0;
}

int IsFull( PriorityQueue H )
{
    return H->Size == H->Capacity;
}

void MakeEmpty( PriorityQueue H ){
    H->Size = 0;
}

int FindMin( PriorityQueue H ){
    return H->Elements[ 1 ].Index;
}

void Destroy( PriorityQueue H ){
    free( H->Elements );
    free( H );
}