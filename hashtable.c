

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include "hashtable.h"



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



// add a string to the hashtable - return 0 on failure
int addToHashTable(struct hashTable *hashTable, int key, char *val)
{
    struct hLinkedList *list, *prev;
    char *value;
    
    value  = malloc(strlen(val));
    strcpy(value,val);

    // create hashcode
    key = key % 100;
    
    // pick the linked list
    list = hashTable->lists[key];
    
    if(!list)
    {
	
        // this list doesn't exist yet - create it
        if(!(list = (struct hLinkedList *)malloc(sizeof(struct hLinkedList))))
        {
            // couldn't get the memory
            return(-1);
        }
        *(hashTable->lists + key) = list;
        
        list->key = key;
		list->num = 0;
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
		if (strcmp(value,list->value))
			{
				list->num++;
			}		
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
	list->num = 0;
    list->value = value;
    list->next = NULL;
    prev->next = list;
    
    return(0);
}


// print all keys and values in a hashtable
int printAllKeysAndValues(struct hashTable *hashTable)
{
    if(NULL == hashTable)
    {
        return(0);
    }
    
    struct hLinkedList *list;
    int i;
    for(i=0; i<hashTable->size; i++)
    {
        list = hashTable->lists[i];
        while(list)
        {
            printf("%d -> %s - %d\n", list->key, list->value, list->num);
            list = list->next;
        }
    }
    
    return(1);
}
