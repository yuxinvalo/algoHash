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
			tmp_node->val = value;				
		tmp_node = tmp_node->next;
	} 

	struct keyval *bucket = (struct keyval*)malloc(sizeof(struct keyval));
	
	bucket->key = word;
	bucket->val = value;
	bucket->next = NULL;
	
	if (org_node != NULL)
		bucket->next = org_node;				
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
#if 0
struct ht* compute_histogram(char** words, unsigned words_size,
                             unsigned ht_size, unsigned (*hash)(char*))
{
	struct ht* new = (struct ht*)malloc(sizeof(struct ht));
				
  return new; 				
}
#endif

unsigned xor_hash(char* word)
{
	unsigned h = 0;
	while (*word)
		h ^= *word++;
	return h;				
}

/*
xor_add_hash is wrong
unsigned xor_add_hash(char* word)
{
	unsigned h = 0;
	unsigned sum = 0;
	while (*word)
	{
		h ^= bad_hash(word);
		sum += h; 
	}
	return sum;	
}

unsigned djb_hash(char* word)
{
	return 0;				
}
*/

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
#if 0
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
#endif

/*test for compute_histogram------------------*/
#if 0
char* words[] = {"foo", "oof", "bar", "rab", "foorab", "barfoo",
                  "oorabf", "foo"};
struct ht* table = compute_histogram(words, 8, 100, bad_hash);
ht_print(stdout, table);
#endif

/*test for xor_hash and add xor hash and djb_hash*/
#if 0
printf("%s : %u\n", "foo", xor_add_hash("foo"));
printf("%s : %u\n", "ofo", xor_add_hash("ofo"));
printf("%s : %u\n", "bar", xor_add_hash("bar"));
printf("%s : %u\n", "foobar", xor_add_hash("foobar"));*/

printf("%s : %u\n", "foo", djb_hash("foo"));
printf("%s : %u\n", "ofo", djb_hash("ofo"));
printf("%s : %u\n", "bar", djb_hash("bar"));
printf("%s : %u\n", "foobar", djb_hash("foobar"));
#endif


return 0;
}
