#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

static treeNode * Program(treeNode * tree);
static treeNode * MainFun(treeNode * tree);
static treeNode * Funct(treeNode * tree);
static treeNode * Declaration(treeNode * tree);
static treeNode * IntVar(treeNode * tree);
static treeNode * FunctType(treeNode * tree);
static treeNode * ResultType(treeNode * tree);
static treeNode * ParametersList(treeNode * tree);
static treeNode * FormalParamList(treeNode * tree);
static treeNode * FormalParamList1(treeNode * tree);
static treeNode * Statement(treeNode * tree);
static treeNode * AssignmentStmt(treeNode * tree);
static treeNode * Expr(treeNode * tree);
static treeNode * PlusExpr(treeNode * tree);
static treeNode * MinusExpr(treeNode * tree);
static treeNode * TimesExpr(treeNode * tree);
static treeNode * DivExpr(treeNode * tree);
static treeNode * FunctionCall(treeNode * tree);
static treeNode * ActualParams(treeNode * tree);
static treeNode * ParamsList(treeNode * tree);
static treeNode * ConditionalStmt(treeNode * tree);
static treeNode * BoolExp(treeNode * tree);
static treeNode * EqualityExp(treeNode * tree);
static treeNode * NotEqualityExp(treeNode * tree);
static treeNode * LTExp(treeNode * tree);
static treeNode * GTExp(treeNode * tree);
static treeNode * LEExp(treeNode * tree);
static treeNode * GEExp(treeNode * tree);
static treeNode * RepetitiveStmt(treeNode * tree);
static treeNode * ReturnStmt(treeNode * tree);
static treeNode * FunctionCallStmt(treeNode * tree);
static treeNode * IOStmt(treeNode * tree);
static treeNode * INStmt(treeNode * tree);
static treeNode * OUTStmt(treeNode * tree);


treeNode * genAst(treeNode * tree)
{
	int i;
	treeNode * p;
	if(tree!=NULL)
	{
		p = Program(tree);
	}		
	return p;					
}	

treeNode * Program(treeNode * tree)
{
	treeNode * t = (treeNode*)newNode(NONTERMINAL);
	if(strcmp(tree->attr.nt.name,"Programs")==0);
	{
		t->attr.nt.name = "Program";
	}
	tree=(treeNode *)tree->attr.nt.child[0];//functions ptr
	t->attr.nt.child[0]= (treeNode *)MainFun(tree->attr.nt.child[0]);//main ptr
	int i=1;
	while(tree->attr.nt.child[1]->attr.nt.child[0]!=NULL)
	{
		t->attr.nt.child[i] = (treeNode *)Funct(tree->attr.nt.child[1]->attr.nt.child[0]);
		i++;
		tree = tree->attr.nt.child[1];//other functionsptr
	}
	return t;
}

treeNode * MainFun(treeNode * tree)
{
	treeNode * t = (treeNode *)newNode(NONTERMINAL);
	tree = (treeNode *)tree->attr.nt.child[2];//funbody ptr
	treeNode * p = tree;
	t->attr.nt.name = "MainFun";
	int i =1;
	if(tree->attr.nt.numNode ==2)
	{	
		tree = (treeNode *)tree->attr.nt.child[0];//decls ptr
		if(tree->attr.nt.numNode == 2)
		{
			t->attr.nt.child[0] = (treeNode *)Declaration(tree->attr.nt.child[0]);
		
			while(tree->attr.nt.child[1]->attr.nt.child[0]!=NULL)
			{
				t->attr.nt.child[i] = (treeNode *)Declaration(tree->attr.nt.child[1]->attr.nt.child[0]);
				i++;
				tree = tree->attr.nt.child[1];
			}
		}
		p = (treeNode *)p->attr.nt.child[1];//otherstatements ptr
		//printf("%s",p->attr.nt.name);
		if(p->attr.nt.numNode==2)
		{
			//printf("msm");
			t->attr.nt.child[i]= (treeNode *)Statement(p->attr.nt.child[0]);
			i++;
			while(p->attr.nt.child[1]->attr.nt.child[0]!=NULL)
			{
				t->attr.nt.child[i] = (treeNode *)Statement(p->attr.nt.child[1]->attr.nt.child[0]);
				i++;
				p = p->attr.nt.child[1];
			}
		}
		
	}

	if(tree->attr.nt.numNode==1)
	{
		p = (treeNode *)p->attr.nt.child[0];//otherstatements ptr
		if(p->attr.nt.numNode==2)
		{
			t->attr.nt.child[i]= (treeNode *)Statement(p->attr.nt.child[0]);
			i++;
			while(p->attr.nt.child[1]->attr.nt.child[0]!=NULL)
			{
				t->attr.nt.child[i] = (treeNode *)Statement(p->attr.nt.child[1]->attr.nt.child[0]);
				i++;
				p = p->attr.nt.child[1];
			}
		}
	}	
	return t;
}

treeNode * Funct(treeNode * tree)
{
	treeNode * t = (treeNode *)newNode(NONTERMINAL);
	t->attr.nt.name = (char *)tree->attr.nt.child[1]->attr.tm.val;
	t->attr.nt.child[0] = (treeNode *)newNode(TERMINAL);
	t->attr.nt.child[0]->attr.tm.val = (char *)tree->attr.nt.child[3]->attr.nt.child[0]->attr.tm.val;
	t->attr.nt.child[1] = (treeNode *)ParametersList(tree->attr.nt.child[5]);//parameters
	
	tree = (treeNode *)tree->attr.nt.child[8];//funbody ptr
	treeNode * p = tree;
	int i =3;
	if(tree->attr.nt.numNode ==2)
	{	
		//printf("h1");
		tree = (treeNode *)tree->attr.nt.child[0];//decls ptr
		if(tree->attr.nt.numNode == 2)
		{
			t->attr.nt.child[2] = (treeNode *)Declaration(tree->attr.nt.child[0]);
		
			while(tree->attr.nt.child[1]->attr.nt.child[0]!=NULL)
			{
				t->attr.nt.child[i] = (treeNode *)Declaration(tree->attr.nt.child[1]->attr.nt.child[0]);
				i++;
				tree = tree->attr.nt.child[1];
			}
		}
		p = (treeNode *)p->attr.nt.child[1];//otherstatements ptr
		if(p->attr.nt.numNode==2)
		{
			t->attr.nt.child[i]= (treeNode *)Statement(p->attr.nt.child[0]);
			i++;
			while(p->attr.nt.child[1]->attr.nt.child[0]!=NULL)
			{
				t->attr.nt.child[i] = (treeNode *)Statement(p->attr.nt.child[1]->attr.nt.child[0]);
				i++;
				p = p->attr.nt.child[1];
			}
		}
		
	}

	if(tree->attr.nt.numNode==1)
	{
		//printf("h2");
		p = (treeNode *)p->attr.nt.child[0];//otherstatements ptr
		if(p->attr.nt.numNode==2)
		{
			t->attr.nt.child[i]= (treeNode *)Statement(p->attr.nt.child[0]);
			i++;
			while(p->attr.nt.child[1]->attr.nt.child[0]!=NULL)
			{
				t->attr.nt.child[i] = (treeNode *)Statement(p->attr.nt.child[1]->attr.nt.child[0]);
				i++;
				p = p->attr.nt.child[1];
			}
		}
	}	

	return t;
}

treeNode * Declaration(treeNode * tree)
{
	treeNode * t = (treeNode *)newNode(NONTERMINAL);		
	t->attr.nt.name = "Declaration";
	if(tree->attr.nt.child[0]->attr.tm.tt==TK_KEY_INT)
	{
		t->attr.nt.child[0]= IntVar(tree->attr.nt.child[1]);
	}
	if(tree->attr.nt.child[0]->attr.tm.tt==TK_KEY_FUN)
		t->attr.nt.child[0] = FunctType(tree);
	return t;
}

treeNode * IntVar(treeNode * tree)
{
	treeNode * t = (treeNode *)newNode(NONTERMINAL);		
	t->attr.nt.name = "IntVar";
	t->attr.nt.child[0] = (treeNode *)newNode(TERMINAL);
	t->attr.nt.child[0]->attr.tm.val = tree->attr.tm.val;
	return t;
}

treeNode * FunctType(treeNode * tree)
{
	treeNode * t = (treeNode *)newNode(NONTERMINAL);		
	t->attr.nt.name = "FunctType";
	t->attr.nt.child[0] = (treeNode *)newNode(TERMINAL);
	t->attr.nt.child[0]->attr.tm.val = tree->attr.nt.child[1]->attr.tm.val;
	t->attr.nt.child[1] = (treeNode*)ResultType(tree->attr.nt.child[6]);
	t->attr.nt.child[2] = (treeNode*)ParametersList(tree->attr.nt.child[3]);//funcdecltypes
	return t;
}

treeNode * ResultType(treeNode * tree)
{
 	treeNode * t = (treeNode *)newNode(NONTERMINAL);
	t->attr.nt.name = "ResultType";		
	t->attr.nt.child[0] = (treeNode *)newNode(TERMINAL);	
	t->attr.nt.child[0]->attr.tm.val = tree->attr.nt.child[0]->attr.tm.val;
	return t;
}

treeNode * ParametersList(treeNode * tree)
{
 	treeNode * t = (treeNode *)newNode(NONTERMINAL);		
	t->attr.nt.name = "Parameters";	
	if(tree->attr.nt.numNode==1)
	{
		t->attr.nt.child[0] = (treeNode *)newNode(TERMINAL);
		t->attr.nt.child[0]->attr.tm.val = tree->attr.nt.child[0]->attr.tm.val;
	}
	else if (tree->attr.nt.numNode==2)
	{
		if(tree->attr.nt.child[0]->nodt == NONTERMINAL)
			t->attr.nt.child[0] = FormalParamList(tree);
		else
			t->attr.nt.child[0] = FormalParamList1(tree);
	}
	return t;
}

treeNode * FormalParamList1(treeNode * tree)
{
	treeNode * t  = (treeNode *)newNode(NONTERMINAL);
	t->attr.nt.name = "FormalParamList1";
	t->attr.nt.child[0] = (treeNode *)newNode(TERMINAL);
	t->attr.nt.child[0]->attr.tm.val = tree->attr.nt.child[0]->attr.tm.val;
	int i = 1;
	tree= tree->attr.nt.child[1];//funcparamrest
	while(tree->attr.nt.numNode==3)
	{
		t->attr.nt.child[i] = (treeNode *)newNode(TERMINAL);
		t->attr.nt.child[i]->attr.tm.val = (char * )tree->attr.nt.child[1]->attr.tm.val;
		i++;
		tree = (treeNode *)tree->attr.nt.child[2];
	}
	return t;
}

treeNode * FormalParamList(treeNode * tree)
{
	treeNode * t  = (treeNode *)newNode(NONTERMINAL);
	t->attr.nt.name = "FormalParamList";
	t->attr.nt.child[0] = (treeNode *)newNode(TERMINAL);
	t->attr.nt.child[0]->attr.tm.val = tree->attr.nt.child[0]->attr.nt.child[1]->attr.tm.val;
	int i = 1;
	tree= tree->attr.nt.child[1];
	while(tree->attr.nt.numNode==3)
	{
		t->attr.nt.child[i] = (treeNode *)newNode(TERMINAL);
		t->attr.nt.child[i]->attr.tm.val = (char * )tree->attr.nt.child[1]->attr.nt.child[1]->attr.tm.val;
		i++;
		tree = (treeNode *)tree->attr.nt.child[2];
	}
	return t;
}


treeNode * Statement(treeNode * tree)
{
	treeNode * t = (treeNode *)newNode(NONTERMINAL);
	t->attr.nt.name = "Statement";
	if(tree->attr.nt.numNode ==1)
	{
		//printf("msm here");
		if(tree->attr.nt.child[0]->attr.nt.child[0]->attr.tm.tt==TK_ID)
			t->attr.nt.child[0] = AssignmentStmt(tree->attr.nt.child[0]);
		if(tree->attr.nt.child[0]->attr.nt.child[0]->attr.tm.tt==TK_KEY_IF)
			t->attr.nt.child[0] = ConditionalStmt(tree->attr.nt.child[0]);
		if(tree->attr.nt.child[0]->attr.nt.child[0]->attr.tm.tt==TK_KEY_WHILE)
			t->attr.nt.child[0] = RepetitiveStmt(tree->attr.nt.child[0]);		 			
		if(tree->attr.nt.child[0]->attr.nt.child[0]->attr.tm.tt==TK_KEY_RETURN)
			t->attr.nt.child[0] = ReturnStmt(tree->attr.nt.child[0]);
		if((tree->attr.nt.child[0]->attr.nt.child[0]->attr.tm.tt==TK_KEY_GET)||(tree->attr.nt.child[0]->attr.nt.child[0]->attr.tm.tt==TK_KEY_PRINT))
			t->attr.nt.child[0] = IOStmt(tree->attr.nt.child[0]);
		if(tree->attr.nt.child[0]->attr.nt.child[0]->attr.tm.tt==TK_KEY_CALL)
			t->attr.nt.child[0] = FunctionCallStmt(tree->attr.nt.child[0]);
	}
	return t;
}

treeNode * AssignmentStmt(treeNode * tree)
{
	treeNode * t = (treeNode *)newNode(NONTERMINAL);
	t->attr.nt.name = "AssignmentStmt";
	t->attr.nt.child[0]= (treeNode *)newNode(TERMINAL);	
	t->attr.nt.child[0]->attr.tm.val = tree->attr.nt.child[0]->attr.tm.val;
	t->attr.nt.child[1] = Expr(tree->attr.nt.child[2]);
	return t;
}

treeNode * Expr(treeNode * tree)
{
	treeNode * t = (treeNode *)newNode(NONTERMINAL);
	treeNode * p = tree;
	t->attr.nt.name = "Expr";
	//printf("%s",tree->attr.nt.name);
	if(tree!=NULL)
	{
		if((tree->attr.nt.child[0]!=NULL )&&(tree->attr.nt.child[1]!=NULL ))
		{
			if(tree->attr.nt.child[1]->attr.nt.numNode == 3)
			{
				switch(tree->attr.nt.child[1]->attr.nt.child[0]->attr.tm.tt)
				{
					case TK_PLUS:
						//p->attr.nt.child[0] = NULL;
						t->attr.nt.child[0] = PlusExpr(p);
						break;
					case TK_MINUS:
						//p->attr.nt.child[0] = NULL;
						t->attr.nt.child[0] = MinusExpr(p);
						break;
					default:
						break;
				}
			}
			//printf("%s",tree->attr.nt.child[0]->attr.nt.name);
			else
			{		
				if(tree->attr.nt.child[0]->attr.nt.child[1]->attr.nt.numNode==3)
				{
					
					switch(tree->attr.nt.child[0]->attr.nt.child[1]->attr.nt.child[0]->attr.tm.tt)	
					{
						case TK_TIMES:
							t->attr.nt.child[0] = TimesExpr(p);
							break;
						case TK_DIV:
							t->attr.nt.child[0] = DivExpr(p);
							break;
						default:
							break;
					}				
	
				}
				else
				{
					if(tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.numNode==3)
					{
						t->attr.nt.child[0] = Expr(tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[1]);
					}
					else
					{	
						//printf("hi");
						if(tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->nodt==TERMINAL)						
						{	
							t->attr.nt.child[0] = (treeNode *)newNode(TERMINAL);						
							switch(tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.tm.tt)
							{
								case TK_ID:
								case TK_NUM:
									t->attr.nt.child[0]->attr.tm.val = tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]->attr.tm.val;
									break;
								default:
									break;
							}			
						}
						else
						{
							t->attr.nt.child[0] = FunctionCall(tree->attr.nt.child[0]->attr.nt.child[0]->attr.nt.child[0]);
						}

					}
				}
			}
		}	
	}
	return t;
	
}

treeNode * PlusExpr(treeNode * tree)
{
	treeNode * t = (treeNode*)newNode(NONTERMINAL);
	t->attr.nt.name = "PlusExpr";
	//treeNode * p1 = tree->attr.nt.child[0];
	tree->attr.nt.child[1]->attr.nt.numNode = 0;
	treeNode * p2 = (treeNode*)newNode(NONTERMINAL);
	p2->attr.nt.child[0] = tree->attr.nt.child[1]->attr.nt.child[1];
	p2->attr.nt.child[1] = tree->attr.nt.child[1]->attr.nt.child[2];
	t->attr.nt.child[0] = Expr(tree);
	t->attr.nt.child[1] = Expr(p2);
	return t;
	
}

treeNode * MinusExpr(treeNode * tree)
{
	treeNode * t = (treeNode*)newNode(NONTERMINAL);
	t->attr.nt.name = "MinusExpr";
	//treeNode * p1 = tree->attr.nt.child[0];
	tree->attr.nt.child[1]->attr.nt.numNode = 0;
	treeNode * p2 = (treeNode*)newNode(NONTERMINAL);
	p2->attr.nt.child[0] = tree->attr.nt.child[1]->attr.nt.child[1];
	p2->attr.nt.child[1] = tree->attr.nt.child[1]->attr.nt.child[2];
	t->attr.nt.child[0] = Expr(tree);
	t->attr.nt.child[1] = Expr(p2);
	return t;
}

treeNode * TimesExpr(treeNode * tree)
{
	treeNode * t = (treeNode*)newNode(NONTERMINAL);
	t->attr.nt.name = "TimesExpr";
	treeNode * p1;
	p1 = tree->attr.nt.child[0]->attr.nt.child[1]->attr.nt.child[1];
	treeNode * p2;
	p2 = tree->attr.nt.child[0]->attr.nt.child[1]->attr.nt.child[2];
	tree->attr.nt.child[0]->attr.nt.child[1]->attr.nt.numNode = 0;
	treeNode * ptr = (treeNode *)newNode(NONTERMINAL);
	ptr->attr.nt.child[0] = (treeNode *)newNode(NONTERMINAL);
	ptr->attr.nt.child[1] = (treeNode *)newNode(NONTERMINAL);
	ptr->attr.nt.child[0]->attr.nt.child[0] = p1;
	ptr->attr.nt.child[0]->attr.nt.child[1] = p2;
	ptr->attr.nt.child[1]->attr.nt.numNode = 0;
	t->attr.nt.child[0] = Expr(tree);
	t->attr.nt.child[1] = Expr(ptr);
	return t;
}

treeNode * DivExpr(treeNode * tree)
{
	treeNode * t = (treeNode*)newNode(NONTERMINAL);
	t->attr.nt.name = "DivExpr";
	treeNode * p1;
	p1 = tree->attr.nt.child[0]->attr.nt.child[1]->attr.nt.child[1];
	treeNode * p2;
	p2 = tree->attr.nt.child[0]->attr.nt.child[1]->attr.nt.child[2];
	tree->attr.nt.child[0]->attr.nt.child[1]->attr.nt.numNode = 0;
	treeNode * ptr = (treeNode *)newNode(NONTERMINAL);
	ptr->attr.nt.child[0] = (treeNode *)newNode(NONTERMINAL);
	ptr->attr.nt.child[1] = (treeNode *)newNode(NONTERMINAL);
	ptr->attr.nt.child[0]->attr.nt.child[0] = p1;
	ptr->attr.nt.child[0]->attr.nt.child[1] = p2;
	ptr->attr.nt.child[1]->attr.nt.numNode = 0;
	t->attr.nt.child[0] = Expr(tree);
	t->attr.nt.child[1] = Expr(ptr);
	return t;
}

treeNode * FunctionCall(treeNode * tree)
{	
	treeNode * t = (treeNode *)newNode(NONTERMINAL);
	t->attr.nt.name = "FunctionCall";
	t->attr.nt.child[0] = (treeNode *)newNode(TERMINAL);
	t->attr.nt.child[0]->attr.tm.val = tree->attr.nt.child[1]->attr.tm.val;
	t->attr.nt.child[1] = ActualParams(tree->attr.nt.child[3]);
	return t;
}

treeNode * ActualParams(treeNode * tree)
{
	treeNode * t = (treeNode *)newNode(NONTERMINAL);
	t->attr.nt.name = "ActualParams";
	if(tree->attr.nt.child[0]->attr.tm.tt==TK_KEY_NONE)
	{
		t->attr.nt.child[0] = (treeNode *)newNode(TERMINAL);
		t->attr.nt.child[0]->attr.tm.val = "TK_KEY_NONE";
	}
	else
	{
		t->attr.nt.child[0] = ParamsList(tree);		
	}
	return t;
}
treeNode * ParamsList(treeNode * tree)
{
	treeNode * t = (treeNode *)newNode(NONTERMINAL);
	t->attr.nt.name = "ParamsList";
	t->attr.nt.child[0] = (treeNode *)newNode(TERMINAL);
	t->attr.nt.child[0]->attr.tm.val = tree->attr.nt.child[0]->attr.tm.val;
	tree = tree->attr.nt.child[1];
	int i =1;
	if(tree->attr.nt.child[1]->attr.nt.numNode==0)
	{
		return t;	
	}
	else
	{	while(tree->attr.nt.child[1]->attr.nt.numNode==2)
		{
			tree = tree->attr.nt.child[1];
			t->attr.nt.child[i]=(treeNode *)newNode(TERMINAL);
			t->attr.nt.child[i]->attr.tm.val = tree->attr.nt.child[0]->attr.tm.val;		
		}
	}
	return t;
}


treeNode * ConditionalStmt(treeNode * tree)
{
	treeNode * t = (treeNode *)newNode(NONTERMINAL);
	t->attr.nt.name = "ConditionalStmt";
	t->attr.nt.child[0] = BoolExp(tree->attr.nt.child[2]);
	int i = 1;
	tree = (treeNode *)tree->attr.nt.child[5];//otherstatements ptr
	if(tree->attr.nt.numNode==2)
	{
		t->attr.nt.child[i]= (treeNode *)Statement(tree->attr.nt.child[0]);
		i++;
		while(tree->attr.nt.child[1]->attr.nt.child[0]!=NULL)
		{
			t->attr.nt.child[i] = (treeNode *)Statement(tree->attr.nt.child[1]->attr.nt.child[0]);
			i++;
			tree = tree->attr.nt.child[1];
		}
	}
	return t;
}

treeNode * BoolExp(treeNode * tree)
{
	treeNode * t = (treeNode *)newNode(NONTERMINAL);
	t->attr.nt.name = "BoolExp";
	switch(tree->attr.nt.child[2]->attr.nt.child[0]->attr.tm.tt)
	{
		case TK_EQUAL:
			t->attr.nt.child[0] = (treeNode *)EqualityExp(tree);
			break;
		case TK_NOTEQUAL:
			t->attr.nt.child[0] = (treeNode *)NotEqualityExp(tree);
			break;
		case TK_LT:
			t->attr.nt.child[0] = (treeNode *)LTExp(tree);
			break;
		case TK_GT:
			t->attr.nt.child[0] = (treeNode *)GTExp(tree);
			break;
		case TK_LEQ:
			t->attr.nt.child[0] = (treeNode *)LEExp(tree);
			break;
		case TK_GEQ:
			t->attr.nt.child[0] = (treeNode *)GEExp(tree);		
			break;
		default:
			break;
	}
	return t;
}
treeNode * EqualityExp(treeNode * tree)
{
	treeNode * t = (treeNode *)newNode(NONTERMINAL);
	t->attr.nt.name = "EqualityExp";
	t->attr.nt.child[0] = (treeNode *)newNode(TERMINAL);
	t->attr.nt.child[1] = (treeNode *)newNode(TERMINAL);
	t->attr.nt.child[0]->attr.tm.val = tree->attr.nt.child[0]->attr.tm.val;
 	t->attr.nt.child[1]->attr.tm.val = tree->attr.nt.child[4]->attr.tm.val;
	return t;
}

treeNode * NotEqualityExp(treeNode * tree)
{
	treeNode * t = (treeNode *)newNode(NONTERMINAL);
	t->attr.nt.name = "NotEqualityExp";
	t->attr.nt.child[0] = (treeNode *)newNode(TERMINAL);
	t->attr.nt.child[1] = (treeNode *)newNode(TERMINAL);
	t->attr.nt.child[0]->attr.tm.val = tree->attr.nt.child[0]->attr.tm.val;
 	t->attr.nt.child[1]->attr.tm.val = tree->attr.nt.child[4]->attr.tm.val;
	return t;
}

treeNode * LTExp(treeNode * tree)
{	
	treeNode * t = (treeNode *)newNode(NONTERMINAL);
	t->attr.nt.name = "LTExp";
	t->attr.nt.child[0] = (treeNode *)newNode(TERMINAL);
	t->attr.nt.child[1] = (treeNode *)newNode(TERMINAL);
	t->attr.nt.child[0]->attr.tm.val = tree->attr.nt.child[0]->attr.tm.val;
 	t->attr.nt.child[1]->attr.tm.val = tree->attr.nt.child[4]->attr.tm.val;
	return t;
}



treeNode * GTExp(treeNode * tree)
{
	treeNode * t = (treeNode *)newNode(NONTERMINAL);
	t->attr.nt.name = "GTExp";
	t->attr.nt.child[0] = (treeNode *)newNode(TERMINAL);
	t->attr.nt.child[1] = (treeNode *)newNode(TERMINAL);
	t->attr.nt.child[0]->attr.tm.val = tree->attr.nt.child[0]->attr.tm.val;
 	t->attr.nt.child[1]->attr.tm.val = tree->attr.nt.child[4]->attr.tm.val;
	return t;
}

treeNode * LEExp(treeNode * tree)
{
	treeNode * t = (treeNode *)newNode(NONTERMINAL);
	t->attr.nt.name = "LEExp";
	t->attr.nt.child[0] = (treeNode *)newNode(TERMINAL);
	t->attr.nt.child[1] = (treeNode *)newNode(TERMINAL);
	t->attr.nt.child[0]->attr.tm.val = tree->attr.nt.child[0]->attr.tm.val;
 	t->attr.nt.child[1]->attr.tm.val = tree->attr.nt.child[4]->attr.tm.val;
	return t;
}

treeNode * GEExp(treeNode * tree)
{
	treeNode * t = (treeNode *)newNode(NONTERMINAL);
	t->attr.nt.name = "GEExp";
	t->attr.nt.child[0] = (treeNode *)newNode(TERMINAL);
	t->attr.nt.child[1] = (treeNode *)newNode(TERMINAL);
	t->attr.nt.child[0]->attr.tm.val = tree->attr.nt.child[0]->attr.tm.val;
 	t->attr.nt.child[1]->attr.tm.val = tree->attr.nt.child[4]->attr.tm.val;
	return t;
}


treeNode * RepetitiveStmt(treeNode * tree)
{
	treeNode * t = (treeNode *)newNode(NONTERMINAL);
	t->attr.nt.name = "RepetitiveStmt";
	t->attr.nt.child[0] = BoolExp(tree->attr.nt.child[2]);
	int i =1;
	tree = (treeNode *)tree->attr.nt.child[5];//otherstatements ptr
	if(tree->attr.nt.numNode==2)
	{
		t->attr.nt.child[i]= (treeNode *)Statement(tree->attr.nt.child[0]);
		i++;
		while(tree->attr.nt.child[1]->attr.nt.child[0]!=NULL)
		{
			t->attr.nt.child[i] = (treeNode *)Statement(tree->attr.nt.child[1]->attr.nt.child[0]);
			i++;
			tree = tree->attr.nt.child[1];
		}
	}
	return t;
}

treeNode * ReturnStmt(treeNode * tree)
{
	treeNode * t = (treeNode *)newNode(NONTERMINAL);
	t->attr.nt.name = "ReturnStmt";
	t->attr.nt.child[0] = (treeNode *)newNode(TERMINAL);
	if(tree->attr.nt.child[1]->attr.nt.child[0]!=NULL)
		t->attr.nt.child[0]->attr.tm.val = tree->attr.nt.child[1]->attr.nt.child[0]->attr.tm.val;
	else
		t->attr.nt.child[0]->attr.tm.val = "TK_KEY_NONE";
	return t;
}

treeNode * FunctionCallStmt(treeNode * tree)
{
	treeNode * t = (treeNode *)newNode(NONTERMINAL);
	t->attr.nt.name = "FunctionCallStmt";
	t->attr.nt.child[0] = FunctionCall(tree->attr.nt.child[0]);
	return t;
}

treeNode * IOStmt(treeNode * tree)
{
	treeNode * t = (treeNode *)newNode(NONTERMINAL);
	t->attr.nt.name = "IOStmt";
	if(tree->attr.nt.child[0]->attr.tm.tt == TK_KEY_PRINT)
	{
		t->attr.nt.child[0] = OUTStmt(tree);
	}
	else if(tree->attr.nt.child[0]->attr.tm.tt == TK_KEY_GET)
	{
		t->attr.nt.child[0] = INStmt(tree);
	}
	return t;
}

treeNode * INStmt(treeNode * tree)
{
	treeNode * t = (treeNode *)newNode(NONTERMINAL);
	t->attr.nt.name = "INStmt";
	t->attr.nt.child[0] = (treeNode *)newNode(TERMINAL);
	t->attr.nt.child[0]->attr.tm.val = tree->attr.nt.child[1]->attr.tm.val;
	return t;
}


treeNode * OUTStmt(treeNode * tree)
{
	treeNode * t = (treeNode *)newNode(NONTERMINAL);
	t->attr.nt.name = "OUTStmt";
	t->attr.nt.child[0] = (treeNode *)newNode(TERMINAL);
	t->attr.nt.child[0]->attr.tm.val = tree->attr.nt.child[1]->attr.tm.val;
	return t;
}


