#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

#define SHIFT 4


int hash(char *key1,char *key2)
{
	int temp1 = 0;
	int i=0;
	while(key1[i]!='\0')
	{
		temp1 = ((temp1 << SHIFT) + key1[i]) % SIZE;
		++i;
	}
	i =0;
	int temp2=0;
	while(key2[i]!='\0')
	{
		temp2 = ((temp2 << SHIFT) + key2[i]) % SIZE;
		++i;
	}
	return (temp1 + i*temp2)%SIZE;
}



void stInsert(char *name,char *scope,entryType et)
{
	int h=0;
	h = hash(name,scope);
	struct symTabEntry * tp = symTable[h];
	while((tp!=NULL)&&(strcmp(name,tp->name) !=0))
		tp = tp->next;
	if(tp==NULL)
	{
		struct symTabEntry * st = (struct symTabEntry *) malloc(sizeof(struct symTabEntry));
		st->name = name;
		st->eType = et;
		st->scope = scope;
		tp = st;
		tp->next = symTable[h];
		symTable[h]=tp;
	}
	else
	{
		if((strcmp(scope,tp->scope)==0) && stLookUp(name,scope)==0)
		{
			fprintf(listing,"\n>>>ERROR in Line no. %d->The variable has already been declared in the current scope/No Overloading allowed for Methods",lineNo-1);
			printf("\n>>>ERROR in Line no. %d->The variable has already been declared in the current scope/No Overloading allowed for Methods",lineNo-1);			
			error = TRUE;
		}
		else
		{
			struct symTabEntry * st1 = (struct symTabEntry *) malloc(sizeof(struct symTabEntry));
			st1->name = name;
			st1->eType =et;
			st1->scope = scope;
			tp = st1;
			tp->next = symTable[h];
			symTable[h]=tp;
		}
	}
	sentry = tp;
}	



void printSymTab(FILE * listing)
{
	int i,j=0;
	fprintf(listing,"\n\n\t\tSYMBOL TABLE :\n");
	for(i=0;i<SIZE;++i)
	{
		if(symTable[i] != NULL)
		{
			struct symTabEntry * l = symTable[i];
			while(l != NULL)
			{
				if(l->eType==VAR)
				{
					fprintf(listing,"\nSymbol Type : Variable\t Name : %s\t Scope : %s\tDataType : INT\t",l->name,l->scope);
				}
				else if(l->eType==FUN)
				{
					
					fprintf(listing,"\nSymbol type : Function\t Name : %s\t Scope : %s\t" ,l->name,l->scope);
					
					if(l->data.fun.retType==INT)
						fprintf(listing,"Return Type : INT Parameters : ");	
					else
						fprintf(listing,"Return Type : NONE Parameters : ");		
					for(j=0;j<10;j++)
					{
						if(l->data.fun.param[j]==INT)
							fprintf(listing," INT\t");	
												
					}
					if(l->data.fun.param[0]==VOID)
							fprintf(listing,"NONE\t");								
					
				}
				fprintf(listing,"\n");
				l = (struct symTabEntry *) l->next;
			}
		}

	}
}

int stLookUp(char *name,char *scope)
{
	int h=0;
	h = hash(name,scope);
	struct symTabEntry * tp = symTable[h];
	while((tp!=NULL)&&(strcmp(name,tp->name) !=0)&&(strcmp(scope,tp->scope)!=0))
		tp = tp->next;
	if(tp!=NULL)
		return 0;
	else
	return 1;
}

int check(char *name,char *scope)
{
	int h=0;
	int i=0;
	h = hash(name,scope);
	struct symTabEntry * tp = symTable[h];
	while((tp!=NULL)&&(strcmp(name,tp->name)!=0)&&(strcmp(scope,tp->scope)!=0))
		tp=tp->next;
	if(tp!=NULL)
	{
		if(tp->eType==FUN)
		{
			while(tp->data.fun.param[i]==INT)
				i++;
			if(tp->data.fun.retType==INT)
			{
				if(rtflag==0)
				{
					error = TRUE;
					fprintf(listing,"\n>>>Error at line : %d -> The called function returns a value..No Assignment found.",lineNo);
					printf("\n>>>Error at line : %d -> The called function returns a value..No Assignment found.",lineNo);
				}
			}
			else
			{
				if(rtflag==1)
				{
					error = TRUE;
					fprintf(listing,"\n>>>Error at line : %d -> The called function does not return a value.",lineNo);
					printf("\n>>>Error at line : %d -> The called function does not return a value.",lineNo);
				}
			}					
		}
	}
	
	return i;
}

