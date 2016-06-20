

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "hashtable.h"

// build the hash code for the input string


// create a hashtable - return 0 on failure
struct hashTable * createHashTable(unsigned int size)
{
  struct hashTable * hashTable;
    struct hLinkedList **lists;
   
    if(size <= 0)
          {
        // bad input
        return(0);
    }
    
    // create the hashtable
    if(!(hashTable = (struct hashTable*)calloc(1,sizeof(struct hashTable))))
    {
	 printf("Error\n");
        return(0);
    }
  
    // create the linked lists
    if(!(lists = (struct hLinkedList**)calloc(1,sizeof(struct hLinkedList ) * size)))
    {
 	printf("error\n");
        free(hashTable);
        return(0);
    }
   
    hashTable->size = size;
    hashTable->lists = lists;
    
    return(hashTable);
}


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
    struct hLinkedList *list, *prev;
    
    // create hashcode
	key = key % 100;
    
    // pick the linked list
    list = hashTable->lists[key];
    
    if(!list)
    {
	printf("Enter\n");
        // this list doesn't exist yet - create it
        if(!(list = (struct hLinkedList *)malloc(sizeof(struct hLinkedList))))
        {
            // couldn't get the memory
            return(-1);
        }
        *(hashTable->lists + key) = list;
        
        list->key = key;
        list->value = value;
        list->next = NULL;
        return(0);
    }
    
    // walk the list
    prev = list;
    while(list)
    {
        if(key = list->key)
        {
            // already exists in the list - update the value
            list->value = value;
            return(-1);
        }
        
        prev = list;
        list = list->next;
    }
    
    // string doesn't yet exist in hashtable - add it. prev is at the end
    if(!(list = (struct hLinkedList *)malloc(sizeof(struct hLinkedList))))
    {
        // couldn't get the memory
        return(-1);
    }
    list->key = key;
    list->value = value;
    list->next = NULL;
    prev->next = list;
    
    return(0);
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
