

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "hashtable.h"

// build the hash code for the input string


// create a hashtable - return 0 on failure
int createHashTable(unsigned int size, struct hashTable **hashTable)
{
    struct hashTable *ht;
    struct hLinkedList **lists;
    
    if(size <= 0)
    {
        // bad input
        return(0);
    }
    
    // create the hashtable
    if(!(ht = (struct hashTable*)malloc(sizeof(struct hashTable))))
    {
        *hashTable = NULL;
        return(0);
    }
    
    // create the linked lists
    if(!(lists = (struct hLinkedList**)malloc(sizeof(struct hLinkedList *) * size)))
    {
        free(ht);
        *hashTable = NULL;
        return(0);
    }
    
    ht->size = size;
    ht->lists = lists;
    
    *hashTable = ht;
    return(1);
}

// destroy a hashtable - return 0 on failure
int destroyHashTable(struct hashTable **ht)
{
    struct hashTable *hashTable;
    struct hLinkedList *list;
    struct hLinkedList *tempList;
    int i = 0;
    hashTable = *ht;
    if(NULL == hashTable)
    {
        return(1);
    }
    
    for(i=0; i<hashTable->size; i++)
    {
        list = *(hashTable->lists + i);
        while(list)
        {
            // keep track of this list
            tempList = list;
            
            // advance for looping
            list = list->next;
            
            // clean
            free(tempList);
        }
    }
    free(hashTable->lists);
    free(hashTable);
    *ht = NULL;
    return(1);
}

// add a string to the hashtable - return 0 on failure
int addToHashTable(struct hashTable *hashTable, int key, char *value)
{
    int hc;
    int offset;
    struct hLinkedList *list, *prev;
    
    // create hashcode
    hc = key;
    
    // pick the linked list
    offset = hc % hashTable->size;
    list = *(hashTable->lists + offset);
    
    if(!list)
    {
        // this list doesn't exist yet - create it
        if(!(list = (struct hLinkedList *)malloc(sizeof(struct hLinkedList))))
        {
            // couldn't get the memory
            return(0);
        }
        *(hashTable->lists + offset) = list;
        
        list->key = key;
        list->value = value;
        list->next = NULL;
        return(1);
    }
    
    // walk the list
    prev = list;
    while(list)
    {
        if(0 == strcmp(list->key, key))
        {
            // already exists in the list - update the value
            list->value = value;
            return(1);
        }
        
        prev = list;
        list = list->next;
    }
    
    // string doesn't yet exist in hashtable - add it. prev is at the end
    if(!(list = (struct hLinkedList *)malloc(sizeof(struct hLinkedList))))
    {
        // couldn't get the memory
        return(0);
    }
    list->key = key;
    list->value = value;
    list->next = NULL;
    prev->next = list;
    
    return(1);
}


// print all keys and values in a hashtable
int printAllKeysAndValues(struct hashTable *hashTable)
{
    struct hLinkedList *list;
    int i=0;
    if(NULL == hashTable)
    {
        return(0);
    }
    
    for(i=0; i<hashTable->size; i++)
    {
        list = *(hashTable->lists + i);
        while(list)
        {
            printf("%d -> %s\n", list->key, list->value);
            list = list->next;
        }
    }
    
    return(1);
}
