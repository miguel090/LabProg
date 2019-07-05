#define HASH_SIZE 101
#include "Trab1.h"

typedef struct cell{
	char *key;
	struct cell *next;
	union{
		int value;
		LISTINSTR* pointer;
	}contents;
}*CELL;

CELL lookup(char *s);
LISTINSTR* lookupPointer(char *s);
void insert(char *s, int value);
void insertPointer(char *s, LISTINSTR *pointer);
void init_table();
int findHashGetValue(char* s);
void updateHash(char *s, int value);
void insertOrUpdate(char*s, int value);

CELL table[HASH_SIZE];
