

#include <stdio.h>
#include <assert.h>
#include <strings.h>
#include "hashtable.h"

#define SIZE 100

int main(int argc, const char * argv[])
{
    struct hashTable *ht;
    char *value;
    
    createHashTable(100, &ht);


		FILE *mf; 
	
	
		char word[100];
		int num;

	
	int key = 0;
	int i = 0 ;
	mf=fopen(argv[2],"r");

	while (fscanf (mf, "%s", word) != EOF)
	{

	num = 0;
		i = 0;
  		key = 0;

		while ((word[i] != '\0') && (word[i] != ',')
			&& (word[i] != '.') && (word[i] != '!') 
			&& (word[i] != ':') && (word[i] != '?')
			&& (word[i] != ';'))
 		{
		
			key = key + (word[i]*(i+1));
			i++;	
		}
		word[i] = '\0';
		key = key/SIZE;
	addToHashTable(ht, key, word);

	printf("%s %d %d\n", word, num, key);
	
	};
	fclose(mf);
	printAllKeysAndValues(ht);
	return 0;
}
