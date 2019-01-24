#include "Reconstruct.h"

int main(){

    int N;
    scanf( "%d", &N );  /* Input the Size of the hash table */

    HashTable H = InitHashTable( N );   /* Construct the hash table from the input */

    AdjGraph G =  BuildAdjGraph( H );   /* Convert hash table into adjacency list */

    TopSort( G );   /* Topological sort and output */

    return 0;
}


