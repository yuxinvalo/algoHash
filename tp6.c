#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int hash(char* key, int size)
{
	int rect = 0;
	while (*key != '\0')
	{
		rect += *key;
		key++;				
	}			
	return rect%size;
}

void display_words(FILE* out, unsigned size, char** words)
{
	for (unsigned i = 0; i < size; i++)
		fprintf(out, "%s\n", words[i]);				
}

unsigned bad_hash(char* word)
{
	unsigned sum = 0;
	unsigned i = 0;
	while (*(word + i) != NULL)
	{
	  sum += word[i];	
		i++;			
	}
	return sum;
}

struct keyval {
	char* key;
	unsigned val;
	struct keyval* next;
};

struct ht{
	struct keyval** table;
	unsigned size;			
};

struct ht* ht_malloc(unsigned size)
{
	struct ht* ht = malloc(sizeof(struct ht));
	ht->size = size;
	ht->table = malloc(size * sizeof(void *));
	for (unsigned i = 0; i < ht->size; i++)
		ht->table[i] = NULL;
	return ht;
}

void ht_free(struct ht* table)
{			
	for (unsigned i = 0; i < table->size; i ++)
	{
	  free(table->table[i]);				
	}
	free(table->table);
	free(table);	
}

struct keyval* ht_find_or_put(char* word, unsigned value,
								struct ht* hashtable,
								unsigned (*hash)(char*))
{
	int index = hash(word, hashtable->size);

}

int main()
{
/*test for display words-------------------------------*/
#if 0	 
display_words(stdout, argc-1, argv+1); 
#endif

/*test for bad_hash------------------------------------*/
#if 0
printf("%u\n", bad_hash("foo"));
printf("%u\n", bad_hash("bar"));
printf("%u\n", bad_hash("foobar"));	 
#endif

/*test for ht_free------------------------------------*/
	 return 0;
}
