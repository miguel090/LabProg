#include <stdio.h>
#include "hash.h"
#include "Trab1.h"
#include <stdlib.h>
#include <string.h>
#define MULT 32 //31

unsigned int hash(char *s){
	unsigned int h;
	unsigned char *p;
	h=0;
	for(p=(unsigned char*) s; *p != '\0'; p++)
		h = MULT * h + *p;
	return h % HASH_SIZE;
}

CELL lookup(char *s){
	int index;
	CELL p;
	index = (int)hash(s);
	for(p=table[index];p!=NULL;p=p->next){
		if(strcmp(s,p->key)==0)
			return p;
	}
	return NULL;
}
LISTINSTR* lookupPointer(char *s){
	int index;
	CELL p;
	index = (int)hash(s);
	for(p=table[index];p!=NULL;p=p->next){
		if(strcmp(s,p->key)==0){
			return p->contents.pointer;
		}
	}
	return NULL;
}

void updateHash(char *s, int value){
	int index;
	CELL p;
	index = hash(s);
	for(p=table[index];p!=NULL;p=p->next){
		if(strcmp(s,p->key)==0){
			p->contents.value = value;
		}
	}
}

int findHashGetValue(char* s){
	int index;
	CELL p;
	index = hash(s);
	for(p=table[index];p!=NULL;p=p->next){
		if(strcmp(s,p->key)==0)
			return p->contents.value;
	}

	return 0;
}

void insert(char *s,int v){
	int index=(int)hash(s);
	CELL p = (CELL) malloc(sizeof(struct cell));
	p->key=s;
	p->contents.value=v;
	p->next=table[index];
	table[index]=p;
}

void insertPointer(char *s, LISTINSTR *pointer){
	int index=(int)hash(s);
	CELL p = (CELL) malloc(sizeof(struct cell));
	p->key=s;
	p->contents.pointer=pointer;
	p->next=table[index];
	table[index]=p;
}

void init_table(){
	for(int i=0;i<HASH_SIZE;i++)
		table[i]=NULL;
}

void insertOrUpdate(char*s, int value){
	if(lookup(s)==NULL){
		insert(s, value);
	}
	else{
		updateHash(s, value);
	}
}
