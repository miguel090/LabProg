#include <stdio.h>
#include <stdlib.h>
#include "Trab1.h"
#include "hash.h"
#include <ctype.h>
#include <string.h>

LISTINSTR* ler_dados(FILE *f);
void runList(LISTINSTR* list);
void getValuesFromInstr(Instr *curInstr,int *n1,int *n2);
LISTINSTR* jumpToLabel(LISTINSTR* li, char* label);


int main(int argc, char* argv[]){
  FILE *input = fopen(argv[1],"r");
  LISTINSTR* mainList = ler_dados(input);
  //printList(mainList);
  runList(mainList);

return 0;
}

void runList(LISTINSTR* list){
  LISTINSTR *cur = list;
  while(cur->next!=NULL){

    cur = cur->next;
    Instr* curInstr = cur->instr;
    switch(curInstr->kind){
      case MAIN:{
        printf("tou na main");
        break;
      }
      case ATRIB:{
        if(curInstr->second.kind==STRING){
          insertOrUpdate(curInstr->first.contents.name, findHashGetValue(curInstr->second.contents.name));
        }else{
          insertOrUpdate(curInstr->first.contents.name, curInstr->second.contents.val);
        }
        break;
      }
      case ADD:{

        int n1, n2;
        getValuesFromInstr(cur->instr, &n1, &n2);
        int res = n1+n2;
        insertOrUpdate(curInstr->first.contents.name, res);
        break;
      }
      case SUB:{
        int n1, n2;
        getValuesFromInstr(cur->instr, &n1, &n2);
        int res = n1-n2;
        insertOrUpdate(curInstr->first.contents.name, res);
        break;
      }
      case MUL:{
        int n1, n2;
        getValuesFromInstr(cur->instr, &n1, &n2);
        int res = n1*n2;
        insertOrUpdate(curInstr->first.contents.name, res);
        break;
      }
      case DIV:{
        int n1, n2;
        getValuesFromInstr(cur->instr, &n1, &n2);
        int res = n1/n2;
        insertOrUpdate(curInstr->first.contents.name, res);
        break;
      }
      case IF_I:{
        if(lookup(curInstr->first.contents.name)!=NULL&&findHashGetValue(curInstr->first.contents.name)!=0){
          cur = lookupPointer(curInstr->second.contents.name);
        }
        break;
      }
      case PRINT:{
        printf("%d\n", findHashGetValue(curInstr->first.contents.name));
        break;
      }
      case READ:{
        int n1;
        scanf("%d", &n1);
        insertOrUpdate(curInstr->first.contents.name, n1);
        break;
      }
      case GOTO_I:{
        cur = lookupPointer(curInstr->first.contents.name);
        break;
      }
      case LABEL:{
        break;
      }
      case QUIT:{
        break;
      }
    }
  }
}

LISTINSTR* ler_dados(FILE *f){
  init_table();
  LISTINSTR *lista = mkList(mkInstr(MAIN, empty(),empty(),empty()),NULL);
  LISTINSTR *cur = lista;
  char string[51];
  char* nome = (char*)malloc(sizeof(char)*51);
  char* tag = (char*)malloc(sizeof(char)*51);
  long int offset = 0;

  while( fgets(string,100 ,f) != NULL){
    if (!strcmp("quit\n",string)) {
      break;
    }


    if(sscanf(string,"ler(%s)", nome)){
      char *p = strtok(nome,")");
      nome = p;
      Instr* instr = mkInstr(READ, mkVar(nome),empty(),empty());
      cur = add(cur, instr);
    }

    else if(sscanf(string,"escrever(%s)", nome)){
      char *p = strtok(nome,")");
      nome = p;
      Instr* instr = mkInstr(PRINT, mkVar(nome), empty(), empty());
      cur = add(cur, instr);
    }

    else if(sscanf(string,"goto %s", nome)){
      char *s = strtok(nome,"\n");
      nome = s;
      Instr* instr = mkInstr(GOTO_I, mkVar(nome), empty(), empty());
      cur = add(cur, instr);
    }

    else if(sscanf(string,"label %s", nome)){
      char *s = strtok(nome,"\n");
      nome = s;
      Instr* instr = mkInstr(LABEL, mkVar(nome), empty(), empty());
      cur = add(cur, instr);
      insertPointer(strdup(nome), cur);
    }

    else if(sscanf(string,"if %s goto %s", tag, nome)){
      char *s = strtok(nome,"\n");
      nome = s;
      char *t = strtok(tag,"\0");
      tag = t;
      Instr* instr = mkInstr(IF_I, mkVar(tag), mkVar(nome), empty());
      cur = add(cur, instr);
    }

    else {
      char* array[100];
      int i = 0;
      for (i = 0 ; i < 100 ; i++)
      array[i] = (char*) malloc(sizeof(char) * 100);
      i=0;
      char *p = strtok(string," ");

      while(p!=NULL)
      {
        strcpy(array[i],p);
        p = strtok(NULL," ");
        i++;
      }
      if(i > 3){
        char *temp = strtok(array[4],"\n");
        strcpy(array[4],temp);

        Elem Felem = mkVar(array[0]);
        Elem Selem;
        if(isdigit(array[2][0])){
          Selem = mkInt(atoi(array[2]));
        }

        else{
          Selem = mkVar(array[2]);
        }
        Elem Telem;
        if(isdigit(array[4][0])){
          Telem = mkInt(atoi(array[4]));
        }

        else{
          Telem = mkVar(array[4]);
        }
        Instr *instr;
        switch(array[3][0]){
          case '+':{
            instr = mkInstr(ADD,Felem, Selem, Telem);
            break;
          }
          case '-':{
            instr = mkInstr(SUB,Felem, Selem, Telem);
            break;
          }
          case '/':{
            instr = mkInstr(DIV,Felem, Selem, Telem);
            break;
          }
          case '*':{
            instr = mkInstr(MUL,Felem, Selem, Telem);
            break;
          }
        }
        cur = add(cur,instr);
      }

      else{


        Elem Felem = mkVar(array[0]);
        Elem Selem;
        char *temp = strtok(array[2],"\n");
        strcpy(array[2],temp);
        if( isdigit(*(array[2])) ) {
          Selem = mkInt(atoi(array[2]));
        }

        else{
          Selem = mkVar(array[2]);
        }
        Instr* instr = mkInstr(ATRIB,Felem, Selem, empty());
        cur = add(cur,instr);
      }
    }
  }
  Instr* instr = mkInstr(QUIT,empty(), empty(), empty());
  cur = add(cur,instr);

  return lista;
}

void getValuesFromInstr(Instr *curInstr,int *n1,int *n2){
  if(curInstr->second.kind==STRING){
    *n1 = findHashGetValue(curInstr->second.contents.name);
  }else{
    *n1 = curInstr->second.contents.val;
  }

  if(curInstr->third.kind==STRING){
    *n2 = findHashGetValue(curInstr->third.contents.name);
  }else{
    *n2 = curInstr->third.contents.val;
  }
  return;
}
