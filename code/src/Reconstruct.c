#include "Reconstruct.h"

/* Node of the adjacency list */
struct AdjVNode{
    Vertex AdjV;    /* Index of the adjacent Vertex */
    PtrToAdjVNode Next;
};

/* Header of the adjacency list */
struct VNode{
    int Element;    /* Value of the vertex */
    int Indegree;   /* Indegree of the vertex */
    PtrToAdjVNode FirstEdge;
};

/* Definition of the adjacency list*/
struct AdjGph{
    AdjList List;
    int Nv;     /* Number of vertex */
};

/* Definition of the hash table */
struct HashTbl{
    int *Elements;
    int TableSize;
};



/**
 * Construct the hash table from the input
 * @param TableSize: the size of the hash table
 * @return the hash table generated from input
 */
HashTable InitHashTable( int TableSize ){

    int i;

    /* Allocate the memory*/
    HashTable H = malloc( sizeof( struct HashTbl ) );
    H->TableSize = TableSize;
    H->Elements = malloc( sizeof(int) * H->TableSize );


    /* Assign the element from the input */
    for( i = 0; i < H->TableSize; i++ )
        scanf( "%d", &H->Elements[i] );

    return H;

}



/**
 * Convert hash table into adjacency list
 * @param H: hash table to be reconstructed
 * @return converted adjacency list
 */
AdjGraph BuildAdjGraph( HashTable H ){

    int i, j;
    int N;

    /* Allocate the memory the adjacency list */
    AdjGraph G = malloc( sizeof( struct AdjGph ) );
    N = G->Nv = H->TableSize;
    G->List =  malloc( sizeof( struct VNode ) * N );

    /* Initialize the adjacency list */
    for( i = 0; i < N; i++ ){
        G->List[ i ].Element = H->Elements[ i ];

        if( G->List[ i ].Element < 0 )
            G->List[ i ].Indegree = EmptyCell;    /* Assign the Indegree the empty cell with -1 */
        else
            G->List[ i ].Indegree = 0;       /* Initialize the Indegree as 0 */

        G->List[ i ].FirstEdge = NULL;    /* Store the adjacent vertex using linked list with header */
    }

    for( i = 0; i < N; i++ ){

        if( G->List[ i ].Element < 0 )    /* Skip the empty cell */
            continue;

        int HashPos = Hash( G->List[ i ].Element, H->TableSize );   /* Calculate the position without collision */

        G->List[ i ].Indegree = (i - HashPos + N) % N;      /* Calculate the conflict time and set the indegree of the vertex */

        for( j = 0; j < G->List[ i ].Indegree; j++ ){       /* set the i-th vertex adjacent to the conflict vertex */

            int InsertPos = (HashPos + j + N) % N; /* Calculate the position of conflict vertex */

            PtrToAdjVNode P, InsertNode;

            /* Initialize the node to be inserted */
            InsertNode = malloc( sizeof( struct AdjVNode ) );
            InsertNode->AdjV = i;
            InsertNode->Next = NULL;

            /* Insert the node into the adjacency list */
            P = G->List[ InsertPos ].FirstEdge;
            if( P == NULL )
                G->List[ InsertPos ].FirstEdge = InsertNode;
            else {
                while( P->Next != NULL )
                    P = P->Next;
                P->Next = InsertNode;
            }
        }
    }

    /* free the memory */
    free( H->Elements );
    free( H );

    return G;


}

/* Hash function */
int Hash( int Key, int TableSize )
{
    return Key%TableSize;
}

/**
 * Topological sort and output
 * @param G Adjacency list to be topological-sorted
 */

void TopSort( AdjGraph G )
{
    int i;
    int flag = 0;   /* flag to control the space output format */
    PriorityQueue H;
    Vertex V;
    PtrToAdjVNode  P;

    H = Initialize( G->Nv );    /* Initialize the Priority-queue for topological sort */

    for( i = 0; i < G->Nv; i++ )
    {
        if( G->List[ i ].Indegree == 0 )    /* If a vertex's indegree is 0, put it into the priority queue */
            Insert( G->List[ i ].Element, i, H );
    }

    while( !IsEmpty( H ) )
    {
        V = DeleteMin( H ); /* Pop the current minimum element in the queue */

        /* Output in the required format */
        if( flag == 1 )
            printf(" ");
        printf("%d",G->List[V].Element);
        flag = 1;

        /* Traverse the adjacency list of the current node and decrements the node indegree by one.
         * If the node indegree becomes zero, insert it into the priority queue */
        P = G->List[ V ].FirstEdge;
        while( P != NULL )
        {
            if( --(G->List[ P->AdjV ].Indegree) == 0 )
                Insert( G->List[ P->AdjV ].Element, P->AdjV, H );
            P = P->Next;
        }

    }

    /* free the memory */
    Destroy( H );
    free( G->List );
    free( G );
}


