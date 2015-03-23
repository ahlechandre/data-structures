/*
 * MIT License © 2015 Alexandre Thebaldi
 * github.com/ahlechandre
*/

#include <stdio.h>

#define max 5

struct Dequeue
{
    int value[max];
    int head, tail, length, emptyIntoBegin, emptyIntoEnd;
};

typedef struct Dequeue dequeue;

// insert functions
void unshift( dequeue * );
void push( dequeue * );

// remove functions
void shift( dequeue * );
void pop( dequeue * );
void freeDeque( dequeue * );

// compact functions
void eject( dequeue *, int );
void inject( dequeue *, int );

// check functions
int isEmptyDeque( dequeue * );
int isFullDeque( dequeue * );

// search functions
void showItens( dequeue * );
int findItem( dequeue *, int );

// message functions
void showWarn( int );
void showErr( int );
void showSucess( int );

int main()
{
    int resp;

    dequeue deque;
    deque.head = -1;
    deque.tail = -1;

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
                if ( !isFullDeque( &deque ) )
                {
                    int insertInto;
                    printf("\ninsert at the (0) begin or (1) end? ");
                    scanf("%d", &insertInto);

                    if ( insertInto == 0 )
                    {
                        unshift( &deque );
                    }
                    else if ( insertInto == 1 )
                    {
                        push( &deque );
                    }
                }
                else
                {
                    // deque is full
                    showWarn(0);
                }
                break;
            }
            case 2:
            {
                // show
                if ( !isEmptyDeque( &deque ) )
                {
                    showItens( &deque );
                }
                else
                {
                    // deque is empty
                    showWarn(1);
                }
                break;
            }
            case 3:
            {
                // remove
                if ( !isEmptyDeque( &deque ) )
                {
                    int removeInto;
                    printf("\nremove at the (0) begin or (1) end? ");
                    scanf("%d", &removeInto);

                    if ( removeInto == 0 )
                    {
                        shift( &deque );
                    }
                    else if ( removeInto == 1 )
                    {
                        pop( &deque );
                    }
                }
                else
                {
                    // stack is empty
                    showWarn(1);
                }
                break;
            }
            case 4:
            {
                // search
                if ( !isEmptyDeque( &deque ) )
                {

                    int foundDeque;

                    int query;
                    printf("\nset query to find at deque: ");
                    scanf("%d", &query);

                    foundDeque = findItem( &deque, query );

                    if ( !foundDeque )
                    {
                        printf("\nresult:\n");
                        printf("\nvalue: %d\n", foundDeque);
                    }
                    else
                    {
                        // not found
                        showWarn(2);
                    }
                }
                else
                {
                    // deque is empty
                    showWarn(1);
                }
                break;
            }

            case 5:
            {
                // free all nodes
                if ( !isEmptyDeque( &deque ) )
                {
                    freeDeque( &deque );
                }
                else
                {
                    // stack is empty
                    showWarn(1);
                }
                break;
            }
        }
        // "0" to exit
        } while ( resp != 0 );
    return 0;
}


// insert functions
void unshift( dequeue *deque )
{
    if ( !isEmptyDeque( deque ) )
    {

    }
    else
    {

    }
}

void push( dequeue *deque )
{
    if ( !isEmptyDeque( deque ) )
    {
        deque->head = deque->head + 1;
        deque->tail = deque->tail + 1;
    }
    else
    {
        if ( deque->tail == (max-1) )
        {
            eject( deque, deque->head );

            deque->tail = (deque->tail - deque->head);
            deque->head = 0;
        }
        deque->tail = deque->tail + 1;
    }
    int value;
    printf("\nset value to insert: ");
    scanf("%d", &value);

    // DEBUG
    printf("\n============ DEBUG ===========\n");
    printf("\nhead = %d\n", deque->head);
    printf("\ntail = %d\n", deque->tail);
    printf("\n============ END DEBUG ===========\n");
    // END DEBUG

    deque->value[deque->tail] = value;
}

// remove functions
void shift( dequeue *deque )
{
    if ( deque->head < deque->tail )
    {
        deque->head = deque->head + 1;
    }
    else if ( deque->head == deque->tail )
    {
        if ( deque->head != 0 )
        {
            eject( deque, deque->head );
        }
        deque->head = -1;
        deque->tail = -1;
    }
    // DEBUG
    printf("\n============ DEBUG ===========\n");
    printf("\nhead = %d\n", deque->head);
    printf("\ntail = %d\n", deque->tail);
    printf("\n============ DEBUG ===========\n");
    // END DEBUG
    return;
}

void pop( dequeue *deque )
{
    if ( deque->tail > deque->head )
    {
        deque->tail = deque->tail - 1;
    }
    else if ( deque->tail == deque->head )
    {
        if ( deque->tail != 0 )
        {
            eject( deque, deque->head );
        }
        deque->head = -1;
        deque->tail = -1;
    }
    // DEBUG
    printf("\n============ DEBUG ===========\n");
    printf("\nhead = %d\n", deque->head);
    printf("\ntail = %d\n", deque->tail);
    printf("\n============ DEBUG ===========\n");
    // END DEBUG
    return;
}
void freeDeque( dequeue *deque )
{
    // could also be something like this: eject( deque, deque->tail )
    eject( deque, (max-1) );

    deque->head = -1;
    deque->tail = -1;
    // DEBUG
    printf("\n============ DEBUG ===========\n");
    printf("\nhead = %d\n", deque->head);
    printf("\ntail = %d\n", deque->tail);
    printf("\n============ DEBUG ===========\n");
    // END DEBUG
    return;
}

// compact functions
void eject( dequeue *deque, int ejects )
{
//    if ( ejects <= deque->emptyIntoBegin ) {}
    int i, j;

    for ( i = 0; i < ejects; i++ )
    {
        for ( j = 0; j < deque->tail; j++ )
        {
            deque[j] = deque[j+1];
        }
    }
    return;
}

void inject( dequeue *deque, int injects )
{
    // emptyIntoEnd = (max - tail) - 1

    if ( injects <= deque->emptyIntoEnd )
    {
        int i, j;

        for ( i = 0; i < injects; i++ )
        {
            for ( j = 0; j < deque->tail; j++ )
            {
                deque[j+1] = deque[j];
            }
        }
    }
    else
    {
        // exceeded limit of injects
        showErr(0);
    }
    return;
}

// check functions
int isEmptyDeque( dequeue *deque )
{
    return ( deque->head == -1 && deque->tail == -1 );
}

int isFullDeque( dequeue *deque )
{
    return ( deque->head == 0 && deque->tail == (max-1) );
}

// search functions
void showItens( dequeue *deque )
{
    int i;

    for ( i = deque->head; i <= deque->tail; i++ )
    {
        printf("\n%d - value: %d\n", i, deque->value[i]);
    }
    return;
}

int findItem( dequeue *deque, int query)
{
    int i;

    for ( i = deque->head; i <= deque->tail; i++ )
    {
        if ( deque->value[i] == query )
        {
            return deque->value[i];
        }
    }
    return 0;
}

// messages functions
void showWarn( int id )
{
    switch ( id )
    {
        case 0:
        {
            printf("\nHey! The stack is full.\n");
            break;
        }
        case 1:
        {
            printf("\nOps, the stack is empty!\n");
            break;
        }
        case 2:
        {
            printf("\nSorry, but this node not found :(\n");
            break;
        }
    }
    return;
}

void showErr( int id )
{
    switch ( id )
    {
        case 0:
        {
            printf("\nOhhh! exceeded the limit of the deque\n");
            break;
        }
        case 1:
        {
//            printf("\nGood! Node removed with successfully!\n");
            break;
        }
        case 2:
        {
//            printf("\nHahaha! The stack it is free now!\n");
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
            printf("\nHahaha! The stack it is free now!\n");
            break;
        }
    }
    return;
}
