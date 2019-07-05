#ifndef TRAB_H
#define TRAB_H

typedef enum {MAIN, ATRIB, ADD, SUB, MUL, DIV, IF_I, PRINT, READ, GOTO_I, LABEL, QUIT} OpKind;

typedef enum {EMPTY, INT_CONST, STRING} ElemKind;

typedef struct
{
  ElemKind kind;
  union
  {
    int val;
    char* name;
  } contents;
} Elem;

typedef struct
{
  OpKind kind;
  Elem first, second, third;
} Instr;

typedef struct list{
  Instr *instr;
  struct list *next;
} LISTINSTR;

Elem mkVar(char *s);
Elem mkInt(int x);
Elem empty();
Instr* mkInstr(OpKind k, Elem x, Elem y, Elem z);
LISTINSTR* mkList( Instr* head, LISTINSTR *tail);
LISTINSTR* add(LISTINSTR* linst, Instr* inst);
void printList(LISTINSTR* l);
void printInstr(Instr* i);
void printElem(Elem e);
#endif
