#include <stdio.h>
#include <stdlib.h>
#include <string.h>
unsigned xor_hash(char* word);
void display_words(FILE* out, unsigned size, char** words);    
unsigned bad_hash(char* word);                                  
struct keyval {
				char* key;
				unsigned val;
				struct keyval* next;
};

struct ht {
				struct keyval** table;
				unsigned size;
};


void display_words(FILE* out, unsigned size, char** words)
{
				for (unsigned int i = 0; i < size; i++)
								fprintf(out, "%s\n", words[i]);
}


unsigned bad_hash(char* word)
{
				unsigned sum = 0;
				int i = 0;
				while(word[i])
				{
								sum += word[i];
								i++;
				}

				return sum;
}

struct ht* ht_malloc(unsigned size)
{
				struct ht *ht = malloc(sizeof (ht));
				ht->size = size;
				ht->table = malloc(sizeof (struct keyval) * size);
				for (unsigned i = 0; i < ht->size; ++i)
				{
								ht->table[i] = NULL;
				}

				return ht;
}


void ht_free(struct ht* table)
{
				for (unsigned i = 0; i < table->size; ++i)
				{
								free(table->table[i]);
				}
				free(table);
}

struct keyval* ht_find_or_put(char* word, unsigned value,
								struct ht* hashtable,
								unsigned (*hash)(char*))
#if 0
{
				unsigned index = hash(word)%hashtable->size;

				struct keyval* tmp = hashtable->table[index];
				struct keyval* tmp2;
				tmp2 = malloc(sizeof(struct keyval));
				tmp2->key = word;
				tmp2->val = value;
				tmp2->next = NULL;

				if (hashtable->table[index] != NULL)
				{
								do
								{
												if(strcmp(word,tmp->key) == 0)
												{
																tmp->val ++;
																return tmp;
												}
												if (tmp->next != NULL)
																tmp = tmp->next;
								} while  (tmp->next != NULL);

								tmp->next = tmp2;
								return tmp->next;
				}


				hashtable->table[index] = tmp2;
				return tmp;
}
#endif
{
	struct keyval *bucket = (struct keyval*)malloc(sizeof(struct keyval));    
	unsigned index = hash(word)%hashtable->size;     
  struct keyval *org_node = hashtable->table[index];                  
	struct keyval *tmp_node = org_node;
	bucket->key = word; 
	bucket->val = value; 
	bucket->next = NULL; 

				//check if the key exits 
	while (tmp_node != NULL)
	{              
					if (strcmp(word, tmp_node->key) == 0)      
					{          
									//tmp_node->val++;                   
									return tmp_node;  
					}      
					else 
					{     
									org_node = tmp_node;    
									tmp_node = tmp_node->next; 
					} 
	}    

				if (org_node != NULL)     
								org_node->next = bucket;    
				else  
				{  
							
								hashtable->table[index] = bucket;    
				}                                         
}


void ht_print(FILE* out, struct ht* hashtable)
{
				for (unsigned int i = 0; i < hashtable->size; ++i)
				{
								if (hashtable->table[i] != NULL)
								{
												fprintf(out,"Bucket[%d]:\t",i);
												struct keyval* tmp = hashtable->table[i];
												int bool = 0;
												while (tmp != NULL)
												{
																if (bool == 1)
																				fprintf(out, " -> ");

																fprintf(out,"(%s,%d)",tmp->key, tmp->val);
																tmp = tmp->next;

																bool = 1;
												}
												fprintf(out,"\n");
								}
				}
}

unsigned fvn_hash(char* word)
{
				unsigned  hash = 2166136261; // offset basis (32 bits)
				for (char* ptr = word; *ptr != '\0'; ptr++)
				{
								hash *= 16777619;   // prime (32 bits)
								hash ^= *ptr;       // xor    
				}
				return hash;
}

unsigned nb_collisions(struct ht* hashtable)
{
				int nb = 0;
				int tmp = 0;
				for (unsigned i = 0; i < hashtable->size; ++i)
				{
								if (hashtable->table[i] != NULL)
								{

												struct keyval* t = hashtable->table[i];

												while (t != NULL)
												{ 
																t = t->next;
																tmp ++;
												}
								}
								if (tmp > nb)
												nb = tmp;
								tmp = 0;
				}

				return nb;
}



struct ht* compute_histogram(char** words, unsigned words_size,
								unsigned ht_size, unsigned (*hash)(char*))
{
				struct ht* table = ht_malloc(ht_size);

				for (unsigned int i = 0; words[i]; ++i)
				{
								ht_find_or_put(words[i], 1, table, hash);
				}

				return table;
}

unsigned xor_hash(char* word)
{
	unsigned h = 0;
	while (*word)
		h ^= *word++;
		return h;				
}

unsigned xor_add_hash(char* word)
{
				unsigned h = 0;
				unsigned sum = 0;
				while (*(word++))
				{
								h ^= bad_hash(word);
								sum += h; 
				}
				return sum;	
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

#if 0
				/*test for compute_histogram------------------*/
				char* words[] = {"foo", "oof", "bar", "rab", "foorab", "barfoo",
								"oorabf", "foo"};
				struct ht* table = compute_histogram(words, 8, 100, bad_hash);
				ht_print(stdout, table);

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


				char* words[] = {"foo", "oof", "bar", "rab", "foorab", "barfoo",
				                 "oorabf", "foo"};
				struct ht* table;
				table = compute_histogram(words, 8, 100, bad_hash);
				ht_print(stdout, table);
				printf("nbcol : %d\n", nb_collisions(table));
				ht_free(table);
				table = compute_histogram(words, 8, 100, fvn_hash);
				ht_print(stdout, table);
				printf("nbcol : %d\n", nb_collisions(table));
				ht_free(table);
#endif
				return 0;
}

