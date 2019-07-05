#include <stdio.h>
#include <stdlib.h>
#include "Trab1.h"
#include <string.h>
Elem mkVar(char *s){
  Elem elem;
  elem.kind = STRING;
  elem.contents.name = strdup(s);
  return elem;
}
Elem mkInt(int x){
  Elem elem;
  elem.kind = INT_CONST;
  elem.contents.val = x;
  return elem;
}
Elem empty(){
  Elem elem;
  elem.kind=EMPTY;
  return elem;
}
Instr *mkInstr(OpKind k, Elem x, Elem y, Elem z){
  Instr* instr = (Instr*)malloc(sizeof(Instr));
  instr->kind=k;
  instr->first =x;
  instr->second =y;
  instr->third =z;
  return instr;
}
LISTINSTR *mkList( Instr* head, LISTINSTR* tail){
  LISTINSTR* ls = (LISTINSTR*)malloc(sizeof(LISTINSTR));
  ls->instr = head;
  ls->next = tail;
  return ls;
}
LISTINSTR* add(LISTINSTR* linst, Instr* inst){
LISTINSTR* ls = mkList(inst,NULL);
linst->next=ls;
return ls;
}
void printList(LISTINSTR* l){
  while(l->next != NULL){
    printInstr(l->instr);
    l = l->next;
  }
  printInstr(l->instr);
}
void printInstr(Instr* i){
  switch(i->kind){
    case ATRIB:
      printf("ATRIB: ");
      break;
    case ADD:
      printf("ADD: ");
      break;
    case SUB:
      printf("SUB: ");
      break;
    case MUL:
      printf("MUL: ");
      break;
    case DIV:
      printf("DIV: ");
      break;
    case IF_I:
      printf("IF_I: ");
      break;
    case PRINT:
      printf("PRINT: ");
      break;
    case READ:
      printf("READ: ");
      break;
    case GOTO_I:
      printf("GOTO_I: ");
      break;
    case LABEL:
      printf("LABEL: ");
      break;
    case MAIN:
      printf("MAIN: ");
      break;
    case QUIT:
    printf("QUIT: ");
    break;
  }
  printElem(i->first);
  printElem(i->second);
  printElem(i->third);
  printf("\n");
}
void printElem(Elem e){
  switch(e.kind){
    case EMPTY:
    printf("EMPTY ");
    break;
    case INT_CONST:
      printf("INT_CONST %d ", e.contents.val);
    break;
    case STRING:
    printf("STRING %s ", e.contents.name);
    break;
  }
}
