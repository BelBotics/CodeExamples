
/* Write a C program to implement a has table with function to insert, delete, display, and search for elements. 
Use separate chaingng for collision resolution */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10
#define CHAR_DATA_LENGTH 100

// Node shall be created as key-value pair of integer data and next node pointeta

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

static int hashFunction(int data)
{
    return data % TABLE_SIZE;
}

Node_t * creteNode(int key, char * data)
{
    Node_t * tempNode;

    // alocate a heap memory for new node
    tempNode = malloc(sizeof(Node_t));

    // set key value
    tempNode->key = key;

    // set data value of new node
    strncpy(tempNode->value, data, TABLE_SIZE);

    // set value of next node
    tempNode->next = NULL;
   
    // return pointer to newly created node element
    return tempNode;
}

static void insertHash(HashTable_t table, char * data)
{
    Node_t * tempNode;
    // get hasFunction 
    int key = hashFunction(strlen(data));

    // Create new node
    tempNode = creteNode(key, data);

    // value of array of addresses point to new node
    *(table.aHashTable + key) = tempNode;

}

static void delete()
{

}

static void search()
{

}

static void display(HashTable_t myHashTable)
{
    // for each element from the list display the value if not null
    for(int i = 0; i< TABLE_SIZE; i++)
    {
        if(myHashTable.aHashTable[i] != NULL)
        {
            printf("Value: %s\n", myHashTable.aHashTable[i]->value);
        }
    }
}

void main(void)
{
    // Create a hashTable element
    HashTable_t myHashTable;
    printf("Hello world\n");

    // insert element to has table
    insertHash(myHashTable, "This is one very good day\0");
    insertHash(myHashTable, "But the night will be challenging\0");
    insertHash(myHashTable, "Since it is cold we myst fight freezing temperatures\0");

    // display all values in Hash Table 
    display(myHashTable);

}