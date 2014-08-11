#ifndef _SYMTAB_H_
#define _SYMTAB_H_
#include "globals.h"
#define SIZE 256
typedef struct variable
{
	int val;
	dataType type;
}variable;


typedef struct function
{
	//int numPar;
	dataType param[10];
	dataType retType;
}function;

typedef struct symTabEntry
{
	char * name;	
	union
	{
		struct variable var;
		struct function fun;
	}data;
	entryType eType;
	char * scope;
	struct symTabEntry * next;
}symTabEnt;

static struct symTabEntry * symTable[SIZE];
extern struct symTabEntry * sentry;
int hash(char *,char *);

void stInsert(char *,char *,entryType);
int stLookUp(char * ,char *);
void printSymTab(FILE *);
int check(char *,char *);
#endif
