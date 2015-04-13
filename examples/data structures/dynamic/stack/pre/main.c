#include <stdio.h>

struct Node
{
    int value;
    struct Node *next;
};

typedef struct Node node;

// insert
node *push( node *stack, int value );

// remove
node *pop( node *stack );

// initialize
node *initialize();

// show
void showNodes( node *stack );

// check
int isEmpty( node *stack );

// messages
void showWarn( int id );
void showSuccess( int id );

int main(void)
{
    int resp;

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
            int value;

            printf("\nvalue of node: ");

            scanf("%d", &value);

            stack = push( stack, value );

            break;
        }
        case 2:
        {
            // show
            if ( !isEmpty( stack ) )
            {
                showNodes( stack );
            }
            else
            {
                showWarn(0);
            }
            break;
        }
        case 3:
        {
            // remove
            if ( !isEmpty( stack ) )
            {
                stack = pop( stack );
            }
            else
            {
                showWarn(0);
            }
            break;
        }
        case 4:
        {
            // search
            if ( !isEmpty( stack ) )
            {
            }
            else
            {
                showWarn(0);
            }
            break;
        }

        case 5:
        {
            // free all nodes
            if ( !isEmpty( stack ) )
            {
            }
            else
            {
                showWarn(0);
            }
            break;
        }
        }
        // "0" to exit
    } while ( resp != 0 );
    return 0;
}

// insert
node *push( node *stack, int value )
{
    node *newNode;

    newNode = ( node * ) malloc( sizeof( node ) );

    newNode->value = value;

    if ( !isEmpty( stack ) )
    {
        node *prev, *top;

        top = stack;

        while( top != NULL )
        {
            prev = top;
            top = top->next;
        }

        newNode->next = NULL;
        prev->next = newNode;
        // added
        showSuccess(0);
        return stack;
    }

    newNode->next = stack;
    // added
    showSuccess(0);
    return newNode;
}

// remove
node *pop( node *stack )
{
    node *top, *middle, *bottom;

    top = stack;
    middle = NULL;

    while( top != NULL )
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
    }

    free(middle);
    return stack;
}

// initialize
node *initialize()
{
    return NULL;
}

// show
void showNodes( node *stack )
{
    node *index;
    int i;

    index = stack;
    i = 0;

    while( index != NULL )
    {
        printf("\n%d || address: %d || value: %d || next: %d\n", i, index, index->value, index->next );
        index = index->next;
        i++;
    }
    return;
}

// check
int isEmpty( node *stack )
{
    return ( stack == NULL );
}

// messages
void showWarn( int id )
{
    switch( id )
    {
    case 0:
    {
        printf("\nstack is empty!\n");
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
        printf("\nnode added!\n");
        break;
    }

    }
}
