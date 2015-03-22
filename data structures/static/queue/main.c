/*
 * MIT License © 2015 Alexandre Thebaldi
 * github.com/ahlechandre
*/

#include <stdio.h>

#define max 5

void insertInto( int *, int *, int * );
void removeInto( int *, int *, int * );
void compressQueue( int *, int , int );
void freeQueue( int *, int *, int * );
void searchQueue( int *, int , int );
int isFullQueue( int , int );
int isEmptyQueue( int , int );
void showQueue( int *, int, int );
void showErr( int );
void showSucess( int );

int main()
{
    int queue[max],
            resp,
            begin = -1,
            end = -1;
    do
    {
        // menu of options
        printf("\n\n0 - exit | 1 - insert | 2 - show | 3 - remove | 4 - search | 5 - free queue \n\n");
        scanf("%d",&resp);

        switch ( resp )
        {
            case 1:
            {
                // insert
                insertInto( queue, &begin, &end );
                break;
            }
            case 2:
            {
                // show
                if ( !isEmptyQueue( begin, end ) )
                {
                    showQueue( queue, begin, end );
                }
                else
                {
                    // is empty queue
                    showErr(1);
                }
                break;
            }
            case 3:
            {
                // remove
                if ( !isEmptyQueue( begin, end ) )
                {
                    removeInto( queue, &begin, &end );
                }
                else
                {
                    // is empty queue
                    showErr(1);
                }
                break;
            }
            case 4:
            {
                // search
                if ( !isEmptyQueue( begin, end ) )
                {
                    searchQueue( queue, begin, end );
                }
                else
                {
                    // is empty queue
                    showErr(1);
                }
                break;
            }

            case 5:
            {
                // free all nodes
                if ( !isEmptyQueue( begin, end ) )
                {
                    freeQueue( queue, &begin, &end );
                }
                else
                {
                    // is empty queue
                    showErr(1);
                }
                break;
            }
        }
        // "0" to exit
        } while ( resp != 0 );
    return 0;
}


// function to insert into queue
void insertInto( int *queue, int *begin, int *end )
{
   if ( !isFullQueue( *begin, *end ) )
   {
        if ( !isEmptyQueue( *begin, *end ) )
        {
            if ( *end == (max-1) )
            {
                compressQueue( queue, *begin, *end );
                *end = (*end - *begin) + 1;
                *begin = 0;
            }
            else
            {
                *end = *end + 1;
            }
        }
        else
        {
            // is empty queue
            *begin = *begin + 1;
            *end = *end + 1;
        }
   }
   else
   {
       // is full queue
       showErr(0);
       return;
   }

   int value;

   printf("insert value at queue: ");
   scanf("%d", &value);
   queue[*end] = value;
   // node added
   showSucess(0);
   return;
}

// function to remove (first) node of queue
void removeInto( int *queue, int *begin, int *end )
{
   if ( *begin < *end )
   {
        *begin = *begin + 1;
   }
   else if ( *begin == *end )
   {
        if ( *begin != 0)
        {
            compressQueue( queue, *begin, *end );
        }
        *begin = -1;
        *end = -1;
        showSucess(1);
        return;
   }
}

// function to show all nodes of queue
void showQueue( int *queue, int begin, int end )
{
    int i;

    for ( i = begin; i <= end; i++ )
    {
        printf("\n%d - value: %d\n", i, queue[i]);
    }
}

// function to compress queue
void compressQueue( int *queue, int begin, int end )
{
    int i, j;

    for ( i = 0; i < begin; i++ )
    {
        for ( j = 0; j < (end - i); j++ )
        {
            queue[j] = queue[j+1];
        }
    }
}

// function to search some node at the queue
void searchQueue( int *queue, int begin, int end )
{
    int i, query;

    printf("\ninsert value to search at the queue: ");
    scanf("%d", &query);

    for ( i = begin; i <= end; i++ )
    {
        if ( queue[i] == query )
        {
            printf("\n%d - value: %d\n", i, queue[i]);
        }
    }
}

// function to free all nodes of queue
void freeQueue( int *queue, int *begin, int *end )
{
    compressQueue( queue, (max-1), (max-1) );
    *begin = -1;
    *end = -1;
    showSucess(2);
    return;
}

// function to check if queue is full
int isFullQueue( int begin, int end )
{
    return ( begin == 0 && end == (max - 1) );
}


// function to check if queue is empty
int isEmptyQueue( int begin, int end )
{
    return ( begin == -1 && end == -1 );
}

void showErr( int id )
{
    switch ( id )
    {
        case 0:
        {
            printf("\nHey! The queue is full.\n");
            break;
        }
        case 1:
        {
            printf("\nOps, the queue is empty!\n");
            break;
        }
    }
    return;
}

void showSucess( int id )
{
    switch ( id )
    {
        case 0:
        {
            printf("\nWell! Node added with successfully!\n");
            break;
        }
        case 1:
        {
            printf("\nGood! Node removed with successfully!\n");
            break;
        }
        case 2:
        {
            printf("\nHahaha! The queue it is free now!\n");
            break;
        }
    }
    return;
}
