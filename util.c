#include "globals.h"
#include "util.h"

char tokenList[][15]={
"ERROR","ENDFILE","TK_KEY_BEGIN","TK_KEY_END","TK_KEY_MAIN","TK_KEY_FUN","TK_KEY_RESULT","TK_KEY_NONE","TK_KEY_INT","TK_KEY_IF","TK_KEY_CALL","TK_KEY_WHILE","TK_KEY_PRINT","TK_KEY_GET","TK_KEY_RETURN","TK_ID","TK_NUM","TK_OPEN","TK_CLOSE","TK_SEMI","TK_EQUAL","TK_NOTEQUAL","TK_PLUS","TK_MINUS","TK_TIMES","TK_DIV","TK_LT","TK_GT","TK_LEQ","TK_GEQ","TK_DOT","TK_COMMA"
};

void printToken(tokenType token,const char* tokenString)
{
	switch(token)
	{ 
		case TK_KEY_BEGIN:
		case TK_KEY_END:
		case TK_KEY_MAIN:
		case TK_KEY_FUN:
		case TK_KEY_RESULT:
		case TK_KEY_NONE:
		case TK_KEY_INT:
		case TK_KEY_IF:
		case TK_KEY_CALL:
		case TK_KEY_WHILE:
		case TK_KEY_PRINT:
		case TK_KEY_RETURN:
		case TK_KEY_GET:
			fprintf(listing,"reserved word : %s\n",tokenString);
			break;
		case TK_ID:
			fprintf(listing,"TK_ID,name=%s\n",tokenString);
			break;
		case TK_NUM:
			fprintf(listing,"TK_NUM, value = %s\n",tokenString);
			break;
		case TK_OPEN:
			fprintf(listing,"(\n");
			break;
		case TK_CLOSE:
			fprintf(listing,")\n");
			break;
		case TK_SEMI:
			fprintf(listing,";\n");
			break;
		case TK_EQUAL:
			fprintf(listing,"=\n");
			break;
		case TK_NOTEQUAL:
			fprintf(listing,"!=\n");
			break;
		case TK_PLUS:
			fprintf(listing,"+\n");
			break;
		case TK_MINUS:
			fprintf(listing,"-\n");
			break;
		case TK_TIMES:
			fprintf(listing,"*\n");
			break;
		case TK_DIV:
			fprintf(listing,"/\n");
			break;
		case TK_LT:
			fprintf(listing,"<\n");
			break;
		case TK_GT:
			fprintf(listing,">\n");
			break;
		case TK_LEQ:
			fprintf(listing,"<=\n");
			break;
		case TK_GEQ:
			fprintf(listing,">=\n");
			break;
		case TK_DOT:
			fprintf(listing,".\n");
			break;
		case TK_COMMA:
			fprintf(listing,",\n");
			break;
		case ERROR:
			fprintf(listing,"ERROR : %s\n",tokenString);
			break;
		case ENDFILE:
			fprintf(listing,"EOF\n");
			break;
		default:
			fprintf(listing,"Unknown Token: %d\n",token);
	}
}


treeNode * newNode(nodeType nodet)
{
	treeNode  *t = (treeNode *) malloc(sizeof(treeNode));
	if(t==NULL)
	fprintf(listing,"Out of memory error at line %d\n",lineNo);
	else
	{
		t->nodt=nodet;
		t->lineNo = lineNo;
	}	
	return t;
}

void printTree(treeNode * tree)
{
	int i;
	treeNode * p;
	p = tree;
	if(p->nodt==NONTERMINAL && (p->attr).nt.child[0] !=NULL)
	{	
		fprintf(listing,"\n");
		for(i=0;i<((p->attr).nt.numNode);i++)
		{
			if((p->attr.nt.child[i]->nodt) == NONTERMINAL)
				fprintf(listing,"%s\t",(((p->attr).nt.child[i])->attr).nt.name);
			else
				fprintf(listing,"%s ('%s')\t",tokenList[((p->attr).nt.child[i]->attr).tm.tt],p->attr.nt.child[i]->attr.tm.val);
		}
		for(i=0;i<((p->attr).nt.numNode);i++)
		{
			if((p->attr).nt.child[i]->nodt == NONTERMINAL)
				printTree((p->attr).nt.child[i]);
		}
		
	}
}


char * copyString(char * s)
{
	int n;
	char *t;
	if(s==NULL)
		return NULL;
	n= strlen(s)+1;
	t = malloc(n);
	if(t==NULL)
		fprintf(listing,"Out of memory error at line %d\n",lineNo);
	else
		strcpy(t,s);
	return t;
}


void printABSTree(treeNode * tree)
{
	int i;
	treeNode * p;
	p = tree;
	if(p->nodt==NONTERMINAL && (p->attr).nt.child[0] !=NULL)
	{	
		fprintf(listing,"\n");
		for(i=0;i<200;i++)
		{
			if(p->attr.nt.child[i]!=NULL)
			{
				if((p->attr).nt.child[i]->nodt == NONTERMINAL)
					fprintf(listing,"%s\t",(((p->attr).nt.child[i])->attr).nt.name);
				else
					fprintf(listing,"%s\t",p->attr.nt.child[i]->attr.tm.val);
			}
		}		
		for(i=0;i<200;i++)
		{
			if(p->attr.nt.child[i]!=NULL)
				printABSTree((p->attr).nt.child[i]);
		}
		
	}
}


