#include <stdio.h>

struct Node
{
  int value;
  struct Node *next;
};

typedef struct Node node;

// prototypes
node *initialize();
node *insert( node * );
node *removeInto( node * );
node *freeStack( node * );
int isEmptyStack( node * );
void showStack( node * );
void searchStack( node * );
void showErr( int );
void showSuccess( int );

int main(void)
{
    printf("\n============================\n");
    printf("* ");
    printf("basic stack in c");
    printf(" *");
    printf("\n============================\n");

    int resp;

    // stack declaration
    node *stack;

    stack = initialize();

    do
    {
        // menu of options
        printf("\n\n0 - exit | 1 - insert | 2 - show | 3 - remove | 4 - search | 5 - free stack \n\n");
        scanf("%d",&resp);

        switch ( resp )
        {
            case 1:
            {
                // insert
                stack = insert( stack );
                break;
            }
            case 2:
            {
                // show
                if ( !isEmptyStack( stack ) )
                {
                    showStack( stack );
                }
                else
                {
                    showErr(0);
                }
                break;
            }
            case 3:
            {
                // remove
                if ( !isEmptyStack( stack ) )
                {
                    stack = removeInto( stack );
                }
                else
                {
                    showErr(0);
                }
                break;
            }
            case 4:
            {
                // search
                if ( !isEmptyStack( stack ) )
                {
                    searchStack( stack );
                }
                else
                {
                    showErr(0);
                }
                break;
            }

            case 5:
            {
                // free all nodes
                if ( !isEmptyStack( stack ) )
                {
                    stack = freeStack( stack );
                }
                else
                {
                    showErr(0);
                }
                break;
            }
        }

    // "0" to exit
    } while ( resp != 0 );
    return 0;
}

node *initialize ()
{
    return NULL;
}

node *insert ( node *stack )
{
    int value;
    printf("value to insert on stack: ");
    scanf("%d", &value);

    node *newStack;
    newStack = ( node * ) malloc( sizeof( node ) );
    newStack->value = value;

    if ( !isEmptyStack( stack ) )
    {
        node *bottom = NULL;
        node *top = stack;

        newStack->next = NULL;

        while ( top != NULL )
        {
            bottom = top;
            top = top->next;
        }

        bottom->next = newStack;
        showSuccess(0);
        return stack;
    } else
    {
        newStack->next = stack;
        showSuccess(0);
        return newStack;
    }
}

node *removeInto( node *stack )
{
    node *bottom;
    node *middle = NULL;
    node *top = stack;

    while ( top != NULL )
    {
        bottom = middle;
        middle = top;
        top = top->next;
    }
    if ( bottom == NULL )
    {
        stack = middle->next;
    }
    else
    {
        bottom->next = middle->next;
        free(middle);
    }
    showSuccess(1);
    return stack;
}
int isEmptyStack( node *stack )
{
    return ( stack == NULL );
}

void searchStack( node *stack )
{
    node *index = stack;
    int i = 0, find = 0, value;
    printf("\ninsert value to search: ");
    scanf("%d", &value);

    while ( index != NULL )
    {
        i++;
        if ( index->value == value)
        {
            printf("\n%d - value: %d\n", i, index->value);
            find = 1;
        }
        index = index->next;
    }

    if ( find == 0)
    {
        showErr(1);
    }
}

node *freeStack( node *stack )
{
    node *bottom = NULL;
    node *top = stack;

    while ( top != NULL )
    {
        bottom = top->next;
        free(top);
        top = bottom;
    }
    stack = bottom;
    showSuccess(2);
    return stack;
}

void showStack( node *stack )
{
    node *index = stack;
    int i = 0;

    while ( index != NULL )
    {
        i++;
        printf("\n%d - value: %d\n", i, index->value );
        index = index->next;
    }
}

void showErr( int id )
{
    printf("\nERRO %d:", id);
    switch( id )
    {
        case 0:
        {
            printf("\n\nEmpty! Please, insert into stack.\n\n");
            break;
        }
        case 1:
        {
            printf("\n\nOps! This node not exists. Retry.\n\n");
            break;
        }
    }
}


void showSuccess( int id )
{
    switch( id )
    {
        case 0:
        {
            printf("\n\nNice! Successfully added node.");
            break;
        }
        case 1:
        {
            printf("\n\nGreat! Node has been removed.\n\n");
            break;
        }
        case 2:
        {
            printf("\n\nGood news! Stack released with success.\n\n");
            break;
        }
    }
}
