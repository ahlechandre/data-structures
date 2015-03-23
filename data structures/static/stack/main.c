/*
 * MIT License © 2015 Alexandre Thebaldi
 * github.com/ahlechandre
*/

#include <stdio.h>

#define max 5

struct Stack
{
    int item[max];
    int bottom, top;
};

typedef struct Stack tstack;

void push( int *, int *, int * );
void pop( int *, int *, int * );
void freeStack( int *, int * );
void showStack( int *, int );
int find( int *, int );
int isEmptyStack( int, int );
int isFullStack( int, int );
void showWarn( int );
void showSucess( int );

int main()
{
    int resp;

    tstack stack;

    stack.bottom = -1;
    stack.top = -1;

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
                if ( !isFullStack( stack.bottom, stack.top ) )
                {
                    push( stack.item, &stack.bottom, &stack.top );
                }
                else
                {
                    // stack is full
                    showWarn(0);
                }
                break;
            }
            case 2:
            {
                // show
                if ( !isEmptyStack( stack.bottom, stack.top ) )
                {
                    showStack( stack.item, stack.top );
                }
                else
                {
                    // stack is empty
                    showWarn(1);
                }
                break;
            }
            case 3:
            {
                // remove
                if ( !isEmptyStack( stack.bottom, stack.top ) )
                {
                    pop( stack.item, &stack.bottom, &stack.top );
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
                if ( !isEmptyStack( stack.bottom, stack.top ) )
                {
                    int found;

                    found = find( stack.item, stack.top );
                    // find() returns -1 when has not found
                    if ( found != -1 )
                    {
                        printf("\nitem: %d\n", stack.item[found]);
                    }
                    else
                    {
                        // not found
                        showWarn(2);
                    }
                }
                else
                {
                    // stack is empty
                    showWarn(1);
                }
                break;
            }

            case 5:
            {
                // free all nodes
                if ( !isEmptyStack( stack.bottom, stack.top ) )
                {
                    freeStack( &stack.bottom, &stack.top );
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

void push( int *stack, int *bottom, int *top )
{
    if ( isEmptyStack( *bottom, *top ) )
    {
        *bottom = *bottom + 1;
        *top = *top + 1;
    }
    else
    {
        *top = *top + 1;
    }
    int value;

    printf("\ninsert value to stack: ");
    scanf("%d", &value);

    stack[*top] = value;

    printf("\nbottom: %d | top: %d\n", *bottom, *top);
    // added node
    showSucess(0);
    return;
}

void pop( int *stack, int *bottom, int *top )
{
    if ( *top > *bottom )
    {
        *top = *top - 1;
    }
    else if ( *top == 0 )
    {
        *bottom = -1;
        *top = -1;
    }
    printf("\nbottom: %d | top: %d\n", *bottom, *top);
    // removed
    showSucess(1);
    return;
}

void freeStack( int *bottom, int *top )
{
    *bottom = -1;
    *top = -1;
    // it is free
    showSucess(2);
    return;
}

void showStack( int *stack, int top )
{
    int i;

    for ( i = 0; i <= top; i++ )
    {
        printf("\n%d - item: %d\n", i, stack[i]);
    }

    return;
}

int find( int *stack, int top )
{
    int i, query, found = -1;

    printf("\nsearch by value: ");
    scanf("%d", &query);

    for ( i = 0; i <= top; i++ )
    {
       if (stack[i] == query)
       {
           found = i;
           break;
       }
    }

    return found;
}

int isEmptyStack( int bottom, int top )
{
    return ( bottom == -1 && top == -1 );
}

int isFullStack( int bottom, int top )
{
    return ( bottom == 0 && top == (max-1) );
}


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
            printf("\Sorry, but this node not found :(\n");
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
