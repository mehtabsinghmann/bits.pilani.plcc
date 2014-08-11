#include "globals.h"
#include "symtab.h"
#include "cgen.h"

static int lblcnt = 0;
static void cGen(treeNode * tree);
static void decAsm(treeNode * tree);
static void genExp(treeNode * tree);
static void genStmt(treeNode * tree);
static void genStmt(treeNode * tree)
{
	if(strcmp(tree->attr.nt.child[0]->attr.nt.name,"AssignmentStmt")==0)
	{
			genExp(tree->attr.nt.child[0]->attr.nt.child[1]);
			fprintf(code,"\nPOP AX\nMOV BX,Offset %s\nMOV [BX],AX",tree->attr.nt.child[0]->attr.nt.child[0]->attr.tm.val);
	}

	if(strcmp(tree->attr.nt.child[0]->attr.nt.name,"ConditionalStmt")==0)
	{
		if(strcmp(tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.name,"EqualityExp")==0)
		{
			fprintf(code,"\nMOV AX,%s\nMOV BX,%s\nCMP AX,BX",tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.tm.val,tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[1]->attr.tm.val);
			int i=1;
			int lbl;
			lbl = lblcnt;
			lblcnt++;			
			fprintf(code,"\nJNE label%d",lbl);
			while(tree->attr.nt.child[0]->attr.nt.child[i]!=NULL)
			{
				genStmt(tree->attr.nt.child[0]->attr.nt.child[i]);
				i++;				
			}
			fprintf(code,"\nlabel%d :",lbl);
		}
		if(strcmp(tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.name,"NotEqualityExp")==0)
		{
			fprintf(code,"\nMOV AX,%s\nMOV BX,%s\nCMP AX,BX",tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.tm.val,tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[1]->attr.tm.val);
			int i =1;
			int lbl;
			lbl = lblcnt;
			lblcnt++;			
			fprintf(code,"\nJE label%d",lbl);
			while(tree->attr.nt.child[0]->attr.nt.child[i]!=NULL)
			{
				genStmt(tree->attr.nt.child[0]->attr.nt.child[i]);
				i++;				
			}
			fprintf(code,"\nlabel%d :",lbl);
		}
		if(strcmp(tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.name,"LTExp")==0)
		{
			fprintf(code,"\nMOV AX,%s\nMOV BX,%s\nCMP AX,BX",tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.tm.val,tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[1]->attr.tm.val);
			int i =1;
			int lbl;
			lbl = lblcnt;
			lblcnt++;			
			fprintf(code,"\nJGE label%d",lbl);
			while(tree->attr.nt.child[0]->attr.nt.child[i]!=NULL)
			{
				genStmt(tree->attr.nt.child[0]->attr.nt.child[i]);
				i++;				
			}
			fprintf(code,"\nlabel%d :",lbl);
		}
		if(strcmp(tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.name,"GTExp")==0)
		{
			fprintf(code,"\nMOV AX,%s\nMOV BX,%s\nCMP AX,BX",tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.tm.val,tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[1]->attr.tm.val);
			int i =1;
			int lbl;
			lbl = lblcnt;
			lblcnt++;			
			fprintf(code,"\nJLE label%d",lbl);
			while(tree->attr.nt.child[0]->attr.nt.child[i]!=NULL)
			{
				genStmt(tree->attr.nt.child[0]->attr.nt.child[i]);
				i++;				
			}
			fprintf(code,"\nlabel%d :",lbl);
		}
		if(strcmp(tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.name,"LEExp")==0)
		{
			fprintf(code,"\nMOV AX,%s\nMOV BX,%s\nCMP AX,BX",tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.tm.val,tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[1]->attr.tm.val);
			int i=1;
			int lbl;
			lbl = lblcnt;
			lblcnt++;			
			fprintf(code,"\nJG label%d",lbl);
			while(tree->attr.nt.child[0]->attr.nt.child[i]!=NULL)
			{
				genStmt(tree->attr.nt.child[0]->attr.nt.child[i]);
				i++;				
			}
			fprintf(code,"\nlabel%d :",lbl);
		}
		if(strcmp(tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.name,"GEExp")==0)
		{
			fprintf(code,"\nMOV AX,%s\nMOV BX,%s\nCMP AX,BX",tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.tm.val,tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[1]->attr.tm.val);
			int i=1;
			int lbl;
			lbl = lblcnt;
			lblcnt++;			
			fprintf(code,"\nJL label%d",lbl);
			while(tree->attr.nt.child[0]->attr.nt.child[i]!=NULL)
			{
				genStmt(tree->attr.nt.child[0]->attr.nt.child[i]);
				i++;				
			}
			fprintf(code,"\nlabel%d :",lbl);
		}
	}
	if(strcmp(tree->attr.nt.child[0]->attr.nt.name,"RepetitiveStmt")==0)
	{
		int lblr;
		lblr = lblcnt;
		lblcnt++;
		fprintf(code,"\nlabel%d :",lblr);
		if(strcmp(tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.name,"EqualityExp")==0)
		{
			fprintf(code,"\nMOV AX,%s\nMOV BX,%s\nCMP AX,BX",tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.tm.val,tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[1]->attr.tm.val);
			int i=1;
			int lbl;
			lbl = lblcnt;
			lblcnt++;			
			fprintf(code,"\nJNE label%d",lbl);
			while(tree->attr.nt.child[0]->attr.nt.child[i]!=NULL)
			{
				genStmt(tree->attr.nt.child[0]->attr.nt.child[i]);
				i++;				
			}
			fprintf(code,"\nJMP label%d",lblr);
			fprintf(code,"\nlabel%d :",lbl);
		}
		if(strcmp(tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.name,"NotEqualityExp")==0)
		{
			fprintf(code,"\nMOV AX,%s\nMOV BX,%s\nCMP AX,BX",tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.tm.val,tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[1]->attr.tm.val);
			int i=1;
			int lbl;
			lbl = lblcnt;
			lblcnt++;			
			fprintf(code,"\nJE label%d",lbl);
			while(tree->attr.nt.child[0]->attr.nt.child[i]!=NULL)
			{
				genStmt(tree->attr.nt.child[0]->attr.nt.child[i]);
				i++;				
			}
			fprintf(code,"\nJMP label%d",lblr);
			fprintf(code,"\nlabel%d :",lbl);
		}
		if(strcmp(tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.name,"LTExp")==0)
		{
			fprintf(code,"\nMOV AX,%s\nMOV BX,%s\nCMP AX,BX",tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.tm.val,tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[1]->attr.tm.val);
			int i=1;
			int lbl;
			lbl = lblcnt;
			lblcnt++;			
			fprintf(code,"\nJGE label%d",lbl);
			while(tree->attr.nt.child[0]->attr.nt.child[i]!=NULL)
			{
				genStmt(tree->attr.nt.child[0]->attr.nt.child[i]);
				i++;				
			}
			fprintf(code,"\nJMP label%d",lblr);
			fprintf(code,"\nlabel%d :",lbl);
		}
		if(strcmp(tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.name,"GTExp")==0)
		{
			fprintf(code,"\nMOV AX,%s\nMOV BX,%s\nCMP AX,BX",tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.tm.val,tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[1]->attr.tm.val);
			int i=1;
			int lbl;
			lbl = lblcnt;
			lblcnt++;			
			fprintf(code,"\nJLE label%d",lbl);
			while(tree->attr.nt.child[0]->attr.nt.child[i]!=NULL)
			{
				genStmt(tree->attr.nt.child[0]->attr.nt.child[i]);
				i++;				
			}
			fprintf(code,"\nJMP label%d",lblr);
			fprintf(code,"\nlabel%d :",lbl);
		}
		if(strcmp(tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.name,"LEExp")==0)
		{
			fprintf(code,"\nMOV AX,%s\nMOV BX,%s\nCMP AX,BX",tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.tm.val,tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[1]->attr.tm.val);
			int i=1;
			int lbl;
			lbl = lblcnt;
			lblcnt++;			
			fprintf(code,"\nJG label%d",lbl);
			while(tree->attr.nt.child[0]->attr.nt.child[i]!=NULL)
			{
				genStmt(tree->attr.nt.child[0]->attr.nt.child[i]);
				i++;				
			}
			fprintf(code,"\nJMP label%d",lblr);
			fprintf(code,"\nlabel%d :",lbl);
		}
		if(strcmp(tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.name,"GEExp")==0)
		{
			fprintf(code,"\nMOV AX,%s\nMOV BX,%s\nCMP AX,BX",tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.tm.val,tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[1]->attr.tm.val);
			int i=1;
			int lbl;
			lbl = lblcnt;
			lblcnt++;			
			fprintf(code,"\nJL label%d",lbl);
			while(tree->attr.nt.child[0]->attr.nt.child[i]!=NULL)
			{
				genStmt(tree->attr.nt.child[0]->attr.nt.child[i]);
				i++;				
			}
			fprintf(code,"\nJMP label%d",lblr);
			fprintf(code,"\nlabel%d :",lbl);
		}
		
	}
	if(strcmp(tree->attr.nt.child[0]->attr.nt.name,"IOStmt")==0)
	{
		int lbl;
		lbl=lblcnt;
		lblcnt++;
		if(strcmp(tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.name,"INStmt")==0)
		{
			fprintf(code,"\nMOV %s,0\nMOV CX,0\nlabel%d:\nMOV AX,%s\nMOV BX,10\nIMUL BX\nMOV %s,AX\nADD %s,CX\nMOV AH,1H\nINT 21h\nMOV AH,0\nMOV BX,13\nMOV CX,AX\nSUB CX,30H\nCMP AX,BX\nJNE label%d\n",tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.tm.val,lbl,tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.tm.val,tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.tm.val,tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.tm.val,lbl);
			
		}
		else
		{
			fprintf(code,"\nMOV BX,Offset %s\nMOV CX,[BX]\nMOV AX,[BX]\nAND DX,0\nMOV temp,0\nlabel%d:\nMOV BX,10\nCWD\nIDIV BX\nMOV CX,AX\nAND DH,0\nADD DL,30H\nPUSH DX\nADD temp,1\nMOV BX,0\nMOV AX,CX\nCMP CX,BX\nJNE label%d\nlabel%d:\nPOP DX\nMOV AH,2H\nINT 21H\nSUB temp,1\nCMP temp,BX\n JNE label%d ",tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.tm.val,lbl,lbl,lbl+1,lbl+1);
		lblcnt++;	
		}
	}
}

static void genExp(treeNode *tree)
{
	if(tree->attr.nt.child[0]->nodt==TERMINAL)
	{
		fprintf(code,"\nMOV AX, %s\nPUSH AX",tree->attr.nt.child[0]->attr.tm.val);

	}
	else
	{	
		if(strcmp(tree->attr.nt.child[0]->attr.nt.name,"PlusExpr")==0)
		{
			genExp(tree->attr.nt.child[0]->attr.nt.child[0]);
			fprintf(code,"\nPOP AX\nMOV BX,AX\nPUSH BX");
			genExp(tree->attr.nt.child[0]->attr.nt.child[1]);
			fprintf(code,"\nPOP AX\nPOP BX\nADD AX,BX\nPUSH AX");
		}
		if(strcmp(tree->attr.nt.child[0]->attr.nt.name,"MinusExpr")==0)
		{
			genExp(tree->attr.nt.child[0]->attr.nt.child[0]);
			fprintf(code,"\nPOP AX\nMOV BX,AX\nPUSH BX");
			genExp(tree->attr.nt.child[0]->attr.nt.child[1]);
			fprintf(code,"\nPOP AX\nPOP BX\nSUB BX,AX\nMOV AX,BX\nPUSH AX");
		}
		if(strcmp(tree->attr.nt.child[0]->attr.nt.name,"TimesExpr")==0)
		{
			genExp(tree->attr.nt.child[0]->attr.nt.child[0]);
			fprintf(code,"\nPOP AX\nMOV BX,AX\nPUSH BX");
			genExp(tree->attr.nt.child[0]->attr.nt.child[1]);
			fprintf(code,"\nPOP AX\nPOP BX\nIMUL BX\nPUSH AX");
		}
		if(strcmp(tree->attr.nt.child[0]->attr.nt.name,"DivExpr")==0)
		{
			genExp(tree->attr.nt.child[0]->attr.nt.child[0]);
			fprintf(code,"\nPOP AX\nMOV BX,AX\nPUSH BX");
			genExp(tree->attr.nt.child[0]->attr.nt.child[1]);
			fprintf(code,"\nPOP BX\nPOP AX\nCWD\nIDIV BX\nPUSH AX");
		}
	}	
}

static void cGen(treeNode * tree)
{
	int i =0;
	if(tree!=NULL)
	{
		while(tree->attr.nt.child[i]!=NULL)
		{
			if(strcmp(tree->attr.nt.child[i]->attr.nt.name,"Statement")==0)
			{
				genStmt(tree->attr.nt.child[i]);
			}
			i++;
		}
	}
}


void codeGen(treeNode *ast)
{
	fprintf(code,".model small\n.data\n.stack");
	decAsm(ast->attr.nt.child[0]);	
	fprintf(code,"\n.code\n.startup");
	cGen(ast->attr.nt.child[0]);
	fprintf(code,"\n.EXIT\nEND\n");
}

static void decAsm(treeNode * tree)
{
	int i =0;
	if(tree!=NULL)
	{
		while(tree->attr.nt.child[i]!=NULL)	
		{
			if(strcmp(tree->attr.nt.child[i]->attr.nt.name,"Declaration")==0)
			{
				fprintf(code,"\n%s   dw ?",tree->attr.nt.child[i]->attr.nt.child[0]->attr.nt.child[0]->attr.tm.val);
			}
			i++;
		}
	}
	fprintf(code,"\ntemp dw ?");
}		
