/*
 * MIT License © 2015 Alexandre Thebaldi
 * github.com/ahlechandre
*/

#include <stdio.h>

struct N {
    int content;
    struct N *left;
    struct N *right;
};

typedef struct N node;

// operations
node *insert( node *tree, int value );
void RED( node *tree );
void EDR( node *tree );
void ERD( node *tree );
node *search( node *tree, int value );
void freeAll( node *tree );
int getHeight( node *root );
int removeNode( node *toDestroy, node *dad, int childSide );
node *getRemoveNode( node *tree, int value );
node *searchChild( node *root, int value );

// helpers
node *init();
void showNode( node *treeNode );
void countNodes( node *tree, int *count );
void log( int option );

int main(void)
{
    int resp = 0, option = 0;
    node *tree;
    tree = init();

    do
    {
        printf("\n============ MENU ============\n");
        printf("\n0 - sair\n");
        printf("\n1 - inserir\n");
        printf("\n2 - buscar\n");
        printf("\n3 - remover\n");
        printf("\n4 - profundidade\n");
        printf("\n5 - altura\n");
        printf("\n6 - mostrar em pre-ordem (RED)\n");
        printf("\n7 - mostrar em pos-ordem (EDR)\n");
        printf("\n8 - mostrar em ordem simetrica (ERD)\n");
        printf("\n9 - remover todos\n\n");

        scanf("%i", &option);

        switch ( option ) {
        case 1: {
            // inserir
            int value;

            printf("\n====== Inserir ======\n");
            printf("\nEntre com um valor (inteiro): \n");
            scanf("%i", &value);

            tree = insert( tree, value );

            break;
        }
        case 2: {
            // buscar
            int value;

            node *found;

            printf("\n====== Buscar ======\n");
            printf("\nEntre com o conteudo (inteiro): \n");
            scanf("%i", &value);

            found = search( tree, value );

            showNode( found );
            break;
        }
        case 3: {
            // remover
            int value;

            int removed;

            printf("\n====== Remover ======\n");
            printf("\nQual conteudo do no deseja remover?: \n");
            scanf("%i", &value);

            removed = getRemoveNode( tree, value );

            if ( removed == 1 )
            {
                log(2);
            }
            else if ( removed == -1 )
            {
                log(3);
            }
            break;
        }
        case 4: {
            // profundidade
            break;
        }
        case 5: {
            // altura
            int option, height;

            printf("\n====== Altura ======\n");
            printf("\nAltura da arvore ou deseja buscar um elemento(no)? \n\n1 - Altura da arvore\n\n2 - Buscar elemento\n\n");

            scanf("%i", &option);
            if ( option == 1 )
            {
                // altura da arvore
                height = getHeight( tree );
            }
            else if ( option == 2 )
            {
                // buscar elemento
                int value;

                node *element;

                printf("\n====== Buscar ======\n");
                printf("\nEntre com o conteudo (inteiro): \n");
                scanf("%i", &value);

                element = search( tree, value );

                height = getHeight( element );
            }

            printf("\nAltura = %i\n", height);
            break;
        }
        case 6: {
            // mostrar em pre-ordem
            printf("\n====== Mostrar em pre-ordem ======\n");
            RED( tree );
            break;
        }
        case 7: {
            // mostrar em pos-ordem
            printf("\n====== Mostrar em pos-ordem ======\n");
            EDR( tree );
            break;
        }
        case 8: {
            // mostrar em ordem simetrica
            printf("\n====== Mostrar em ordem simetrica ======\n");
            ERD( tree );
            break;
        }
        case 9: {
            // remover todos
            int sure;

            printf("\n====== Remover todos ======\n");
            printf("\n\n TEM CERTEZA? \n\n1 - SIM \n\n0 - NAO\n\n");

            scanf("%i", &sure);

            if ( sure == 1 )
            {
                freeAll( tree );
                tree = init();
            }
            break;
        }
        case 0: {
            // sair
            exit(0);
        }
        }
        printf("\nDeseja continuar? \n\n1 - SIM \n\n0 - NAO\n\n");
        scanf("%i", &resp);
    } while ( resp != 0 );

    return 0;
}

// operations

node *insert( node *tree, int value )
{
    if ( tree == NULL )
    {
        int sizeOfTreeNode = sizeof( node );

        tree = ( node * ) malloc( sizeOfTreeNode );

        tree->content = value;
        tree->left = NULL;
        tree->right = NULL;
    }
    else
    {
        int leftSide = 0, rightSide = 0;

        countNodes( tree->left, &leftSide );
        countNodes( tree->right, &rightSide );

        if ( leftSide <= rightSide )
        {
            tree->left = insert( tree->left, value );
        }
        else
        {
            tree->right = insert( tree->right, value );
        }
    }

    return tree;
}

node *search( node *tree, int value )
{
    if ( tree != NULL )
    {
        if ( tree->content == value )
        {
            return tree;
        }

        node *find;

        find = search( tree->left, value );

        if ( find == NULL )
        {
            find = search( tree->right, value );
        }

        return find;
    }

    return NULL;
}

void RED( node *tree )
{
    if ( tree != NULL )
    {
        showNode( tree );
        RED( tree->left );
        RED( tree->right );
    }
}

void EDR( node *tree )
{
    if ( tree != NULL )
    {
        EDR( tree->left );
        EDR( tree->right );
        showNode( tree );
    }
}

void ERD( node *tree )
{
    if ( tree != NULL )
    {
        ERD( tree->left );
        showNode( tree );
        ERD( tree->right );
    }
}

void freeAll( node *tree )
{
    if ( tree != NULL )
    {
        freeAll( tree->left );
        freeAll( tree->right );
        free( tree );
    }
}

int getHeight ( node *root ) {

    if ( root != NULL )
    {
        int leftHeight = getHeight( root->left );
        int rightHeight = getHeight ( root->right );

        if ( leftHeight < rightHeight )
        {
            return rightHeight + 1;
        }
        else
        {
            return leftHeight + 1;
        }
    }

    return -1;
}

int removeNode( node *toDestroy, node *dad, int childSide )
{
    if ( toDestroy != NULL && dad != NULL )
    {

        if ( toDestroy->left != NULL && toDestroy->right != NULL )
        {
            // dois filhos
        }

        node *child;

        if ( toDestroy->left == NULL && toDestroy->right == NULL )
        {
            child = NULL;
        }

        if ( toDestroy->left != NULL && toDestroy->right == NULL )
        {
            child = toDestroy->left;
        }

        if ( toDestroy->left == NULL && toDestroy->right != NULL )
        {
            child = toDestroy->left;
        }

        if ( childSide == 0 )
        {
            dad->left = child;
        }
        else if ( childSide == 1 )
        {
            dad->right = child;
        }

        free( toDestroy );
        return 1;
    }

    return -1;
}

node *getRemoveNode( node *tree, int value )
{
    node *dad;

    if ( tree->content == value )
    {
        // remover a raiz da arvore
    }
    else
    {
        dad = searchChild( tree, value );
        if ( dad != NULL )
        {
            int removed;

            if ( dad->left->content == value )
            {
                removed = removeNode( dad->left, dad, 0);
            }
            else if ( dad->right->content == value )
            {
                removed = removeNode( dad->right, dad, 1);
            }

            return removed;
        }
    }

    return -1;
}

node *searchChild( node *root, int value )
{
    if ( root != NULL )
    {
        if ( root->left != NULL )
        {
            if ( root->left->content == value )
            {
                return root;
            }
        }

        if ( root->right != NULL )
        {
            if ( root->right->content == value )
            {
                return root;
            }
        }

        node *find;

        find = searchChild( root->left, value );

        if ( find == NULL )
        {
            find = searchChild( root->right, value );
        }

        return find;
    }

    return NULL;
}

// helpers

node *init()
{
    return NULL;
}

void showNode( node *treeNode )
{
    if ( treeNode != NULL )
    {
        printf("\nCONTEUDO = %i\n", treeNode->content);
        if ( treeNode->left == NULL )
        {
            printf("\n  FILHO A ESQUERDA = NULL\n");
        }
        else
        {
            printf("\n  FILHO A ESQUERDA = %i\n", treeNode->left->content);
        }

        if ( treeNode->right == NULL )
        {
            printf("\n  FILHO A DIREITA = NULL\n");
        }
        else
        {
            printf("\n  FILHO A DIREITA = %i\n", treeNode->right->content);
        }
    }
    else
    {
        log(1);
    }
}

void countNodes( node *tree, int *count )
{
    if ( tree != NULL )
    {
        *count += 1;
        countNodes( tree->left, count );
        countNodes( tree->right, count );
    }
}

void log( int option )
{
    switch ( option ) {
    case 1:
    {
        printf("\n\nEsse node nao existe!\n\n");
        break;
    }
    case 2:
    {
        printf("\n\nNode removido com sucesso!\n\n");
        break;
    }
    case 3:
    {
        printf("\n\nNode nao foi removido!\n\n");
        break;
    }

    }
}


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

// TREEE

#include <stdio.h>

struct Node {
    int content;
    struct Node *left;
    struct Node *right;
};

typedef struct Node node;

node *insertBb( node *, int );
node *insert( node *, int );

int main(void)
{
    node *tree = NULL;
    int value, menu;

    do
    {
        printf("\nEntre com o valor: \n");
        scanf( "%i", &value );
        tree = insert( tree, value );
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

node *insert( node *tree, int value )
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
        int subLeft = 0, subRight = 0;

        nodeCount( tree->left, &subLeft );
        nodeCount( tree->right, &subRight );

        if ( subLeft <= subRight )
        {
            tree->left = insert( tree->left, value );
        }
        else
        {
            tree->right = insert( tree->right, value );
        }
    }
    return tree;
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

void nodeCount( node *tree, int *count )
{
    if ( tree != NULL )
    {
        *count += 1;
        nodeCount( tree->left, count );
        nodeCount( tree->right, count );
    }
}

void red ( node *tree )
{
    if ( tree != NULL )
    {
        printf( "\nContent = %d \n", tree->content );

        if ( tree->left == NULL )
        {
            printf("\nContentLeft = NULL\n");
        }
        else
        {
            printf( "\nContentLeft = %d \n", tree->left->content );
        }

        if ( tree->right == NULL )
        {
            printf("\nContentRight = NULL\n");
        }
        else
        {
            printf( "\nContentRight = %d \n", tree->right->content );
        }
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

// other tree

#include <stdio.h>

struct N {
    int content;
    struct N *left;
    struct N *right;
};

typedef struct N node;

// operations
node *insert( node *tree, int value );
void RED( node *tree );
void EDR( node *tree );
void ERD( node *tree );
node *search( node *tree, int value );
void freeAll( node *tree );
int getHeight( node *root );
int removeNode( node *toDestroy, node *dad, int childSide );
node *getRemoveNode( node *tree, int value );
node *searchChild( node *root, int value );

// helpers
node *init();
void showNode( node *treeNode );
void countNodes( node *tree, int *count );
void log( int option );

int main(void)
{
    int resp = 0, option = 0;
    node *tree;
    tree = init();

    do
    {
        printf("\n============ MENU ============\n");
        printf("\n0 - sair\n");
        printf("\n1 - inserir\n");
        printf("\n2 - buscar\n");
        printf("\n3 - remover\n");
        printf("\n4 - profundidade\n");
        printf("\n5 - altura\n");
        printf("\n6 - mostrar em pre-ordem (RED)\n");
        printf("\n7 - mostrar em pos-ordem (EDR)\n");
        printf("\n8 - mostrar em ordem simetrica (ERD)\n");
        printf("\n9 - remover todos\n\n");

        scanf("%i", &option);

        switch ( option ) {
        case 1: {
            // inserir
            int value;

            printf("\n====== Inserir ======\n");
            printf("\nEntre com um valor (inteiro): \n");
            scanf("%i", &value);

            tree = insert( tree, value );

            break;
        }
        case 2: {
            // buscar
            int value;

            node *found;

            printf("\n====== Buscar ======\n");
            printf("\nEntre com o conteudo (inteiro): \n");
            scanf("%i", &value);

            found = search( tree, value );

            showNode( found );
            break;
        }
        case 3: {
            // remover
            int value;

            int removed;

            printf("\n====== Remover ======\n");
            printf("\nQual conteudo do no deseja remover?: \n");
            scanf("%i", &value);

            removed = getRemoveNode( tree, value );

            if ( removed == 1 )
            {
                log(2);
            }
            else if ( removed == -1 )
            {
                log(3);
            }
            break;
        }
        case 4: {
            // profundidade
            break;
        }
        case 5: {
            // altura
            int option, height;

            printf("\n====== Altura ======\n");
            printf("\nAltura da arvore ou deseja buscar um elemento(no)? \n\n1 - Altura da arvore\n\n2 - Buscar elemento\n\n");

            scanf("%i", &option);
            if ( option == 1 )
            {
                // altura da arvore
                height = getHeight( tree );
            }
            else if ( option == 2 )
            {
                // buscar elemento
                int value;

                node *element;

                printf("\n====== Buscar ======\n");
                printf("\nEntre com o conteudo (inteiro): \n");
                scanf("%i", &value);

                element = search( tree, value );

                height = getHeight( element );
            }

            printf("\nAltura = %i\n", height);
            break;
        }
        case 6: {
            // mostrar em pre-ordem
            printf("\n====== Mostrar em pre-ordem ======\n");
            RED( tree );
            break;
        }
        case 7: {
            // mostrar em pos-ordem
            printf("\n====== Mostrar em pos-ordem ======\n");
            EDR( tree );
            break;
        }
        case 8: {
            // mostrar em ordem simetrica
            printf("\n====== Mostrar em ordem simetrica ======\n");
            ERD( tree );
            break;
        }
        case 9: {
            // remover todos
            int sure;

            printf("\n====== Remover todos ======\n");
            printf("\n\n TEM CERTEZA? \n\n1 - SIM \n\n0 - NAO\n\n");

            scanf("%i", &sure);

            if ( sure == 1 )
            {
                freeAll( tree );
                tree = init();
            }
            break;
        }
        case 0: {
            // sair
            exit(0);
        }
        }
        printf("\nDeseja continuar? \n\n1 - SIM \n\n0 - NAO\n\n");
        scanf("%i", &resp);
    } while ( resp != 0 );

    return 0;
}

// operations

node *insert( node *tree, int value )
{
    if ( tree == NULL )
    {
        int sizeOfTreeNode = sizeof( node );

        tree = ( node * ) malloc( sizeOfTreeNode );

        tree->content = value;
        tree->left = NULL;
        tree->right = NULL;
    }
    else
    {
        int leftSide = 0, rightSide = 0;

        countNodes( tree->left, &leftSide );
        countNodes( tree->right, &rightSide );

        if ( leftSide <= rightSide )
        {
            tree->left = insert( tree->left, value );
        }
        else
        {
            tree->right = insert( tree->right, value );
        }
    }

    return tree;
}

node *search( node *tree, int value )
{
    if ( tree != NULL )
    {
        if ( tree->content == value )
        {
            return tree;
        }

        node *find;

        find = search( tree->left, value );

        if ( find == NULL )
        {
            find = search( tree->right, value );
        }

        return find;
    }

    return NULL;
}

void RED( node *tree )
{
    if ( tree != NULL )
    {
        showNode( tree );
        RED( tree->left );
        RED( tree->right );
    }
}

void EDR( node *tree )
{
    if ( tree != NULL )
    {
        EDR( tree->left );
        EDR( tree->right );
        showNode( tree );
    }
}

void ERD( node *tree )
{
    if ( tree != NULL )
    {
        ERD( tree->left );
        showNode( tree );
        ERD( tree->right );
    }
}

void freeAll( node *tree )
{
    if ( tree != NULL )
    {
        freeAll( tree->left );
        freeAll( tree->right );
        free( tree );
    }
}

int getHeight ( node *root ) {

    if ( root != NULL )
    {
        int leftHeight = getHeight( root->left );
        int rightHeight = getHeight ( root->right );

        if ( leftHeight < rightHeight )
        {
            return rightHeight + 1;
        }
        else
        {
            return leftHeight + 1;
        }
    }

    return -1;
}

int removeNode( node *toDestroy, node *dad, int childSide )
{
    if ( toDestroy != NULL && dad != NULL )
    {

        if ( toDestroy->left != NULL && toDestroy->right != NULL )
        {
            // dois filhos
        }

        node *child;

        if ( toDestroy->left == NULL && toDestroy->right == NULL )
        {
            child = NULL;
        }

        if ( toDestroy->left != NULL && toDestroy->right == NULL )
        {
            child = toDestroy->left;
        }

        if ( toDestroy->left == NULL && toDestroy->right != NULL )
        {
            child = toDestroy->left;
        }

        if ( childSide == 0 )
        {
            dad->left = child;
        }
        else if ( childSide == 1 )
        {
            dad->right = child;
        }

        free( toDestroy );
        return 1;
    }

    return -1;
}

node *getRemoveNode( node *tree, int value )
{
    node *dad;

    if ( tree->content == value )
    {
        // remover a raiz da arvore
    }
    else
    {
        dad = searchChild( tree, value );
        if ( dad != NULL )
        {
            int removed;

            if ( dad->left->content == value )
            {
                removed = removeNode( dad->left, dad, 0);
            }
            else if ( dad->right->content == value )
            {
                removed = removeNode( dad->right, dad, 1);
            }

            return removed;
        }
    }

    return -1;
}

node *searchChild( node *root, int value )
{
    if ( root != NULL )
    {
        if ( root->left != NULL )
        {
            if ( root->left->content == value )
            {
                return root;
            }
        }

        if ( root->right != NULL )
        {
            if ( root->right->content == value )
            {
                return root;
            }
        }

        node *find;

        find = searchChild( root->left, value );

        if ( find == NULL )
        {
            find = searchChild( root->right, value );
        }

        return find;
    }

    return NULL;
}

// helpers

node *init()
{
    return NULL;
}

void showNode( node *treeNode )
{
    if ( treeNode != NULL )
    {
        printf("\nCONTEUDO = %i\n", treeNode->content);
        if ( treeNode->left == NULL )
        {
            printf("\n  FILHO A ESQUERDA = NULL\n");
        }
        else
        {
            printf("\n  FILHO A ESQUERDA = %i\n", treeNode->left->content);
        }

        if ( treeNode->right == NULL )
        {
            printf("\n  FILHO A DIREITA = NULL\n");
        }
        else
        {
            printf("\n  FILHO A DIREITA = %i\n", treeNode->right->content);
        }
    }
    else
    {
        log(1);
    }
}

void countNodes( node *tree, int *count )
{
    if ( tree != NULL )
    {
        *count += 1;
        countNodes( tree->left, count );
        countNodes( tree->right, count );
    }
}

void log( int option )
{
    switch ( option ) {
    case 1:
    {
        printf("\n\nEsse node nao existe!\n\n");
        break;
    }
    case 2:
    {
        printf("\n\nNode removido com sucesso!\n\n");
        break;
    }
    case 3:
    {
        printf("\n\nNode nao foi removido!\n\n");
        break;
    }

    }
}
