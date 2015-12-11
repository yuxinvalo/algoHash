#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

void display_words(FILE* out, unsigned size, char** words);
unsigned bad_hash(char* word);

void display_words(FILE* out, unsigned size, char** words)
{
	for (unsigned i = 0; i < size; i++)
		fprintf(out, "%s\n", words[i]);				
}

unsigned bad_hash(char* word)
{
	unsigned sum = 0;
	unsigned i = 0;
	while (word[i])
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
	unsigned index = hash(word)%hashtable->size;
	struct keyval *org_node = hashtable->table[index];
	struct keyval *tmp_node = org_node;
	
	//check if the key exits
	while (tmp_node != NULL)
	{
		if (strcmp(word, tmp_node->key) == 0)
		{
			tmp_node->val = value;				
		}
		tmp_node = tmp_node->next;
	} 

	struct keyval *bucket = (struct keyval*)malloc(sizeof(struct keyval));
	
	bucket->key = word;
	bucket->val = value;
	bucket->next = NULL;
	
	if (org_node != NULL)
	{
		bucket->next = org_node;				
	}

	hashtable->table[index] = bucket;
	return bucket;
}


/*ht_print-----------------------------------------*/
void ht_print(FILE* out, struct ht* hashtable)
{
  
	struct keyval *next;
  unsigned index;
	for (index = 0; index < hashtable->size; index++)
	{
		if (hashtable->table[index] != NULL)
		{
		  fprintf(out, "Bucket[%d]\t", index);
			fprintf(out, "(%s,%d) ", hashtable->table[index]->key, 
			hashtable->table[index]->val);	
		
			next = hashtable->table[index];
			next = next->next;
			while (next != NULL)
		  {
			  if (next->key != NULL)
				fprintf (out, "-> (%s,%d) ", next->key, next->val);
				next = next->next;
		  }
		 fprintf(out,"\n");
     }
	 }				
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

/*test for ht_print------------------------------------*/
struct ht* table = ht_malloc(10);
ht_find_or_put("foo", 1,  table, bad_hash);
ht_find_or_put("bar", 42, table, bad_hash);
printf("------------ Dump table ------------\n");
ht_print(stdout, table);

struct keyval* ptr = ht_find_or_put("foo", 12, table, bad_hash);
printf("------------ Dump table ------------\n");
ht_print(stdout, table);

ptr->val = 21;
printf("------------ Dump table ------------\n");
ht_print(stdout, table);

ht_find_or_put("oof", 1,  table, bad_hash);
printf("------------ Dump table ------------\n");
ht_print(stdout, table);

ht_free(table);
return 0;
}
