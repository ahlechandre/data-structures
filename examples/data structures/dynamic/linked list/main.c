/*
 * MIT License © 2015 Alexandre Thebaldi
 * github.com/ahlechandre
*/

#include <stdio.h>

// node of list
struct Node
{
    int value;
    struct Node *next;
};

typedef struct Node node;

// prototypes
node *initialize();
node *insert( node * );
node *freeList( node * );
node *removeInto( node * );
void searchList( node * );
void showList( node * );
int isEmptyList( node * );
void showErr( int );

int main(void)
{

    printf("\n============================\n");
    printf("* ");
    printf("basic linked-list in c");
    printf(" *");
    printf("\n============================\n");

    int resp;

    // list declaration
    node *list;

    // initializing with a NULL node
    list = initialize();

    do
    {
        // menu of options
        printf("\n\n0 - exit | 1 - insert | 2 - show | 3 - remove | 4 - search | 5 - free list \n\n");
        scanf("%d",&resp);

        switch ( resp )
        {
            case 1:
            {
                // insert
                list = insert(list);
                break;
            }
            case 2:
            {
                // show

                // first, verify if list is empty
                if ( !isEmptyList( list ) )
                {
                    showList(list);
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

                // first, verify if list is empty
                if ( !isEmptyList( list ) )
                {
                    list = removeInto( list );
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

                // first, verify if list is empty
                if ( !isEmptyList( list ) )
                {
                    searchList(list);
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

                // first, verify if list is empty
                if ( !isEmptyList( list ) )
                {
                    list = freeList(list);
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

node *initialize()
{
    return NULL;
}

node *insert( node *list )
{
    int value, resp;
    printf("\nvalue to insert into: ");
    scanf("%d", &value);

    // if list it's empty
    if ( list == NULL )
    {
        resp = 1;
    }
    else
    {
        printf("\ninsert at the beginning or end? 1 - beginning | 2 - end \n");
        scanf("%d", &resp);
    }

    // declaring new node to add at the list
    node *newList;
    // allocating dynamically new node
    newList = (node *) malloc( sizeof( node ) );
    // assigning value to new node
    newList->value = value;

    if ( resp == 1 )
    {
        // add node at beginning

        newList->next = list;
        showSuccess(0);
        return newList;
    }
    else if ( resp == 2 )
    {
        // add node at end

        node *prev = NULL;
        node *next = list;

        newList->next = NULL;

        while ( next != NULL )
        {
            prev = next;
            next = next->next;
        }
        prev->next = newList;
        showSuccess(0);
        return list;
    }

}

node *removeInto( node *list )
{
    int toRemove;
    printf("\nselect value to remove: ");
    scanf("%d", &toRemove);

    node *prev = NULL;
    node *next = list;

    while ( next != NULL && next->value != toRemove)
    {
        prev = next;
        next = next->next;
    }

    if ( next == NULL )
    {
        // case not found value to remove
        showErr(1);
        return list;
    }
    else if ( prev == NULL )
    {
        // case value to remove it's first of list
        list = next->next;
    }
    else
    {
        // case value to remove it's in the middle or at the end
        prev->next = next->next;
        // free node
        free(next);
    }
    showSuccess(1);
    return list;
}

node *freeList( node *list )
{
   node *atual = list;
   node *next = NULL;

   while ( atual != NULL )
   {
        next = atual->next;
        free(atual);
        atual = next;
   }
   showSuccess(2);
   return atual;

}

void searchList( node *list )
{
    node *index = list;
    int query, find = 0;
    printf("\nsearch node by value: ");
    scanf("%d", &query);

    while( index != NULL )
    {
        if ( index->value == query )
        {
            printf("\naddress: %d | value: %d | pointer: %d\n", index, index->value, index->next);
            find = 1;
        }

        index = index->next;
    }

    if ( find == 0 )
    {
        showErr(1);
    }
}

void showList( node *list )
{
    node *indexList = list;

    while ( indexList != NULL )
    {
        printf("\naddress: %d | value: %d | pointer: %d\n", indexList, indexList->value, indexList->next);
        indexList = indexList->next;
    }

    /*
     * recursive version

    if ( isEmptyList(list) )
    {
        return;
    }

    printf("\naddress: %d | value: %d | pointer: %d\n", list, list->value, list->next);

    showList( list->next );
    */

}

int isEmptyList( node *list )
{
    // false returns 0 / true returns 1
    return (list == NULL);
}

void showErr( int id )
{
    printf("\nERRO %d:", id);
    switch( id )
    {
        case 0:
        {
            printf("\n\nEmpty! Please, insert into list.\n\n");
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
            printf("\n\nGood news! List released with success.\n\n");
            break;
        }
    }
}

// TREE

#include <stdio.h>

struct Node {
    int content;
    struct Node *left;
    struct Node *right;
};

typedef struct Node node;

node *insertBb( node *, int );

int main(void)
{
    node *tree = NULL;
    int value, menu;

    do
    {
        printf("\nEntre com o valor: \n");
        scanf( "%i", &value );
        tree = insertBb( tree, value );
        printf("\nDeseja continuar? N- 0 S- 1\n");
        scanf( "%i", &menu );
    } while( menu != 0 );

    printf("\n ====== RED ===== \n");
    red( tree );

    printf("\n ====== ERD ===== \n");
    erd( tree );

    printf("\n ====== EDR ===== \n");
    edr( tree );

    return 0;
}

node *insertBb( node *tree, int value )
{
    if ( tree == NULL )
    {
        tree = ( node * ) malloc( sizeof( node ) );
        tree->content = value;
        tree->left = NULL;
        tree->right = NULL;
    }
    else
    {
        node *newNode;
        if ( value < tree->content )
        {
            newNode = insertBb( tree->left, value );
            tree->left = newNode;
        }
        else
        {
            newNode = insertBb( tree->right, value );
            tree->right = newNode;
        }
    }
    return tree;
}

void red ( node *tree )
{
    if ( tree != NULL )
    {
        printf( "\nContent = %d \n", tree->content );
        red( tree->left );
        red( tree->right );
    }
}

void erd ( node *tree )
{
    if ( tree != NULL )
    {
        erd( tree->left );
        printf( "\nContent = %d \n", tree->content );
        erd( tree->right );
    }
}

void edr ( node *tree )
{
    if ( tree != NULL )
    {
        edr( tree->left );
        edr( tree->right );
        printf( "\nContent = %d \n", tree->content );
    }
}

