
/* Write a C program to implement a has table with function to insert, delete, display, and search for elements. 
Use separate chaingng for collision resolution */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10
#define CHAR_DATA_LENGTH 100

// Node shall be created as key-value pair of integer data and next node pointer


// Create a Node type
typedef struct Node
{
    int key;
    char value[CHAR_DATA_LENGTH];
    struct Node * next;
} Node_t;

typedef struct HashTable
{
    // array of pointers to Has Table Nodes
    Node_t * aHashTable[TABLE_SIZE];
} HashTable_t;

// Function declarations
static Node_t *  search(HashTable_t * myHashTable,  char * data);



static int hashFunction(int data)
{
    return data % TABLE_SIZE;
}

Node_t * creteNode(int key, char * data)
{
    Node_t * tempNode;

    // alocate a heap memory for new node
    tempNode = calloc(1, sizeof(Node_t));

    // set key value
    tempNode->key = key;

    // set data value of new node
    strncpy(tempNode->value, data, strlen(data));

    // set value of next node
    tempNode->next = NULL;
   
    // return pointer to newly created node element
    return tempNode;
}

static void insertHash(HashTable_t *table, char * data)
{
    Node_t * tempNode;

    Node_t * tempNextPtr;
    // get hasFunction 
    int key = hashFunction(strlen(data));

    // Create new node
    tempNode = creteNode(key, data);

    // check if key value already exists
    if(*(table->aHashTable + key) != NULL)
    {
        // there is already pointer stored in this array location
        // so new element shall be added as SEPARATE CHAINING Method
        tempNextPtr = (Node_t *) *(table->aHashTable + key);

        while(tempNextPtr->next != NULL)
        {
            tempNextPtr = tempNextPtr->next;
        }

        if(tempNextPtr != NULL)
        {
            tempNextPtr->next = tempNode;
        }
    }
    else
    {    // value of array of addresses point to new node
        *(table->aHashTable + key) = tempNode;
    }
}

static void delete(HashTable_t *table, char * data)
{
    // search for the node that shall be removed form the hash table
    Node_t * RemoveNodePtr = search(table, data);
    Node_t * tmpPtr = NULL;
    Node_t * parentPtr = NULL;

    // check if node ixists
    if(RemoveNodePtr != NULL)
    {
        // get pointer value of key
        tmpPtr = table->aHashTable[RemoveNodePtr->key];
       
        // if ptrs are the same remove from the list
        if(tmpPtr == RemoveNodePtr)
        {
            table->aHashTable[RemoveNodePtr->key] = RemoveNodePtr->next;
            free(RemoveNodePtr);
            return;
        }else
        {
            do
            {
                // if ptrs are the same remove from the list
                if(tmpPtr->next == RemoveNodePtr)
                {
                    tmpPtr->next = RemoveNodePtr->next;
                    free(RemoveNodePtr);
                    return;
                }else
                {
                    // move to the next element
                    tmpPtr = tmpPtr->next;
                }
            }
            while(tmpPtr != NULL);
        }
    }    
}

static Node_t *  search(HashTable_t * myHashTable,  char * data)
{
    // find the key from has table based on hash function
    int key = hashFunction(strlen(data));
    Node_t * tempNode;

    tempNode = *(myHashTable->aHashTable + key);

     // check if key value already exists
     if(tempNode != NULL)
     {
         while(tempNode != NULL)
         {
            if(strcmp(data, tempNode->value) == 0)
            {
                // if data are equal 
                printf("Data found\n");
                return tempNode;

            }else
            {
                tempNode = tempNode->next;
            }
         }
    }

    printf("Data not found\n");
    return NULL;
}

static void display(HashTable_t myHashTable)
{
    Node_t * nextNodePtr;
    // for each element from the list display the value if not null
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        if(myHashTable.aHashTable[i] != NULL)
        {
            printf("%d: -> %s\n", myHashTable.aHashTable[i]->key, myHashTable.aHashTable[i]->value);

            // check if linked list elements exists
            nextNodePtr = myHashTable.aHashTable[i]->next;
            while(nextNodePtr != NULL)
            {
                printf("%d: -> %s\n", myHashTable.aHashTable[i]->key, nextNodePtr->value);
                nextNodePtr = nextNodePtr->next;
            }
        }
    }
}

static void displayNode(HashTable_t myHashTable, Node_t * nodePtr)
{   
    // display value of node ptr
    printf("%d: -> %s\n", nodePtr->key, nodePtr->value);
}

int main(void)
{
    // Create a hashTable element
    HashTable_t myHashTable;

    Node_t * tempSearchNode = NULL;

    // initialize all myHashTable element values to NULL ptr
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        myHashTable.aHashTable[i] = NULL;
    }

    // string 
    char * helloWorld = "Hello world from string \0";
    printf("%s\n", helloWorld);

    // insert element to has table
    insertHash(&myHashTable, "This is one very good day\0");
    insertHash(&myHashTable, "This is one not_ good day\0");
    insertHash(&myHashTable, "But the night will be challenging\0");
    insertHash(&myHashTable, "Since it is cold we myst fight freezing temperatures\0");
    insertHash(&myHashTable, "The action was performed last night, we are waiting for the results\0");
    insertHash(&myHashTable, "It would need a week to see first results of icing conditions\0");
    insertHash(&myHashTable, "Nobody said it would be easy, but that's life\0");

    // display all values in Hash Table 
    display(myHashTable);

    
    tempSearchNode = search(&myHashTable, "Nobody said it would be easy, but that's life\0" );

    if(tempSearchNode != NULL)
    {
        // data found
        displayNode(myHashTable, tempSearchNode);
    }

    // Now try to delete an record
    delete(&myHashTable, "This is one not_ good day\0");
    delete(&myHashTable, "It would need a week to see first results of icing conditions\0");
    delete(&myHashTable, "It would need a week to see first results of icing conditions\0");

    display(myHashTable);

    insertHash(&myHashTable, "It would need a week to see first results of icing conditions\0");
    insertHash(&myHashTable, "It would need a week to see first results of icing conditions\0");
    insertHash(&myHashTable, "This is one not_ good day\0");

    display(myHashTable);.

    return 0;

}