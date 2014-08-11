#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"
#include "symtab.h"
static tokenType token;
static int rflag;
static treeNode * programs(void);
static treeNode * functions(void);
static treeNode * mainFunction(void);
static treeNode * otherFunctions(void);
static treeNode * funct(void);
static treeNode * resultType(void);
static treeNode * parameters(void);
static treeNode * parameter(void);
static treeNode * remainingParameters(void);
static treeNode * funBody(void);
static treeNode * declarations(void);
static treeNode * declaration(void);
static treeNode * funDeclTypes(void);
static treeNode * funDeclTypesRest(void);
static treeNode * otherStatements(void);
static treeNode * statement(void);
static treeNode * assignmentStmt(void);
static treeNode * expression(void);
static treeNode * eprime(void);
static treeNode * term(void);
static treeNode * factor(void);
static treeNode * tprime(void);
static treeNode * functionCall(void);
static treeNode * actualParams(void);
static treeNode * actualParamsRest(void);
static treeNode * remActualParamsRest(void);
static treeNode * conditionalStmt(void);
static treeNode * boolExp(void);
static treeNode * boolOps(void);
static treeNode * repetitiveStmt(void);
static treeNode * functionCallStmt(void);
static treeNode * returnStmt(void);
static treeNode * returnVal(void);
static treeNode * ioStmt(void);


static void syntaxError(char * message)
{
	fprintf(listing,"\n>>> ");
	fprintf(listing,"Syntax error at line %d: %s",lineNo,message);
	printf("\n>>> ");
	printf("Syntax error at line %d: Unexpected Token",lineNo);
	error = TRUE;
}

static void match(tokenType expected)
{
	if(token==expected)
		token = getToken();
	else
	{
		syntaxError("Unexpected Token  -> ");
		printToken(token,(char *)copyString(tokenString));
		fprintf(listing,"     ");
	}
}

treeNode * programs(void)
{
	treeNode * t = (treeNode*)newNode(NONTERMINAL);
	t->attr.nt.name = "Programs";
	t->attr.nt.numNode = 1;
	switch(token)
	{
		case TK_KEY_MAIN:
			(t->attr).nt.child[0]=functions();			break;
		default :
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
	}
	return t;
}

treeNode * functions(void)
{
	treeNode * t = (treeNode * )newNode(NONTERMINAL);
	t->attr.nt.name = "Functions";
	t->attr.nt.numNode = 2;
	switch(token)
	{
		case TK_KEY_MAIN:
			(t->attr).nt.child[0]=mainFunction();
			(t->attr).nt.child[1]=otherFunctions();
			break;
		default:
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
	}
	return t;
}

treeNode * mainFunction(void)
{
	treeNode * t = (treeNode * )newNode(NONTERMINAL);	
	t->attr.nt.name = "MainFun";
	t->attr.nt.numNode = 4;	
	rflag =0;	
	treeNode * t1 = (treeNode * )newNode(TERMINAL);
	switch(token)
	{

		case TK_KEY_MAIN:
			
			currentScope = "main";
			t1->attr.tm.tt = TK_KEY_MAIN;
			t1->attr.tm.val = (char *)copyString(tokenString);
			(t->attr).nt.child[0]=t1;
			match(TK_KEY_MAIN);
			
			treeNode * t2 = (treeNode * )newNode(TERMINAL);
			t2->attr.tm.tt = TK_KEY_BEGIN;
			t2->attr.tm.val = (char *)copyString(tokenString);
			match(TK_KEY_BEGIN);
			(t->attr).nt.child[1]=t2;
			(t->attr).nt.child[2] = funBody();
			
			treeNode * t3 = (treeNode * )newNode(TERMINAL);
			t3->attr.tm.tt = TK_KEY_END;
			t3->attr.tm.val = (char *)copyString(tokenString);
			match(TK_KEY_END);
			(t->attr).nt.child[3] = t3;
			break;
		default:
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
			
	}
	return t;
}

treeNode * otherFunctions(void)				
{
	treeNode * t=(treeNode * )newNode(NONTERMINAL);
	t->attr.nt.name = "OtherFuns";
	t->attr.nt.numNode = 2;
	switch(token)
	{
		case TK_KEY_FUN:
			(t->attr).nt.child[0]=funct();
			(t->attr).nt.child[1]=otherFunctions();
			break;
		case ENDFILE:
			t->attr.nt.numNode = 0;
			break;
		default:
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
	}
	return t;
}
			
treeNode * funct(void)
{
	treeNode * t =(treeNode * )newNode(NONTERMINAL);
	t->attr.nt.name = "Funct";
	t->attr.nt.numNode = 10;
	treeNode * t1 = (treeNode * )newNode(TERMINAL);
	switch(token)
	{

		case TK_KEY_FUN:
			
			pn = 0;
			t1->attr.tm.tt = TK_KEY_FUN;
			t1->attr.tm.val = (char *)copyString(tokenString);
			match(TK_KEY_FUN);
			(t->attr).nt.child[0]=t1;

			treeNode * t2 = (treeNode * )newNode(TERMINAL);
			t2->attr.tm.tt = TK_ID;
			currentScope = (char *)copyString(tokenString);
			match(TK_ID);
			(t->attr).nt.child[1]=t2;
			treeNode * t3 = (treeNode * )newNode(TERMINAL);
			t3->attr.tm.tt = TK_KEY_RESULT;
			t3->attr.tm.val = (char *)copyString(tokenString);
			match(TK_KEY_RESULT);
			(t->attr).nt.child[2]=t3;
			(t->attr).nt.child[3]=resultType();
			treeNode * t4 = (treeNode * )newNode(TERMINAL);
			t4->attr.tm.tt = TK_OPEN;
			t4->attr.tm.val = (char *)copyString(tokenString);
			match(TK_OPEN);
			(t->attr).nt.child[4]=t4;
			(t->attr).nt.child[5]=parameters();

			treeNode * t5 = (treeNode * )newNode(TERMINAL);
			t5->attr.tm.tt = TK_CLOSE;
			t5->attr.tm.val = (char *)copyString(tokenString);
			match(TK_CLOSE);
			(t->attr).nt.child[6]=t5;

			treeNode * t6 = (treeNode * )newNode(TERMINAL);
			t6->attr.tm.tt = TK_KEY_BEGIN;
			t6->attr.tm.val = (char *)copyString(tokenString);
			match(TK_KEY_BEGIN);
			(t->attr).nt.child[7]=t6;
			(t->attr).nt.child[8]=funBody();
			if(rflag==1)
			{
				error = TRUE;
				fprintf(listing,"\n>>>Error at line %d -> Missing Return Statement.",lineNo);
				rflag = 0;
				printf("\n>>>Error at line %d -> Missing Return Statement.",lineNo);
			}
			treeNode * t7 = (treeNode * )newNode(TERMINAL);
			t7->attr.tm.tt = TK_KEY_END;
			t7->attr.tm.val = (char *)copyString(tokenString);
			match(TK_KEY_END);
			(t->attr).nt.child[9]=t7;
			break;			
		default:
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
	}
	return t;
}

treeNode * resultType(void)
{
	treeNode * t =(treeNode * )newNode(NONTERMINAL);
	t->attr.nt.name = "ResultType";
	t->attr.nt.numNode = 1;
	treeNode * t1 = (treeNode * )newNode(TERMINAL);	
	treeNode * t2 = (treeNode * )newNode(TERMINAL);
	switch(token)
	{

		case TK_KEY_NONE:

			rflag = 0;
			t1->attr.tm.tt = TK_KEY_NONE;
			t1->attr.tm.val = (char *)copyString(tokenString);
			match(token);
			(t->attr).nt.child[0]=t1;
			break;
		case TK_KEY_INT:

			rflag =1;
			t2->attr.tm.tt = TK_KEY_INT;
			t2->attr.tm.val = (char *)copyString(tokenString);
			match(token);
			(t->attr).nt.child[0]=t2;
			break;
		default:
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
	}
	return t;}
	
treeNode * parameters(void)
{
	treeNode * t = (treeNode * )newNode(NONTERMINAL);
	t->attr.nt.name = "Parameters";
	t->attr.nt.numNode = 2;
			treeNode * t1 = (treeNode * )newNode(TERMINAL);
	switch(token)
	{
		case TK_KEY_NONE:
			
			pn = 0;
			t1->attr.tm.tt = TK_KEY_NONE;
			t1->attr.tm.val = (char *)copyString(tokenString);
			match(token);			
			(t->attr).nt.child[0]=t1;
			t->attr.nt.numNode =1;
			break;
		case TK_KEY_INT:
			(t->attr).nt.child[0]=parameter();
			(t->attr).nt.child[1]=remainingParameters();
			break;
		default:
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
	}
	return t;
}
		
treeNode * parameter(void)
{
	treeNode * t = (treeNode * )newNode(NONTERMINAL);
	t->attr.nt.name = "Parameter";
	t->attr.nt.numNode = 2;
			treeNode * t1 = (treeNode * )newNode(TERMINAL);
			treeNode * t2 = (treeNode * )newNode(TERMINAL);
	switch(token)
	{
		case TK_KEY_INT:

			pn++;
			t1->attr.tm.tt = TK_KEY_INT;
			t1->attr.tm.val = (char *)copyString(tokenString);
			match(TK_KEY_INT);
			(t->attr).nt.child[0]=t1;


			t2->attr.tm.tt = TK_ID;
			t2->attr.tm.val = (char *)copyString(tokenString);
			stInsert(t2->attr.tm.val,currentScope,VAR);
			match(TK_ID);
			(t->attr).nt.child[1]=t2;
			break;
		default:
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
	}
	return t;
}
treeNode * remainingParameters(void)
{
	treeNode * t =(treeNode * )newNode(NONTERMINAL);
	t->attr.nt.name = "Remaining Parameters";
	t->attr.nt.numNode = 3;
			treeNode * t1 = (treeNode * )newNode(TERMINAL);
	switch(token)
	{
		case TK_COMMA:
		

			t1->attr.tm.tt = TK_COMMA;
			t1->attr.tm.val = (char *)copyString(tokenString);
			match(TK_COMMA);		
			(t->attr).nt.child[0]=t1;
			(t->attr).nt.child[1]=parameter();
			(t->attr).nt.child[2]=remainingParameters();
			break;
		case TK_CLOSE:
			t->attr.nt.numNode = 0;
			break;
		default:
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
	}
	return t;
}

treeNode * funBody(void)
{
	treeNode * t=(treeNode * )newNode(NONTERMINAL);
	t->attr.nt.name = "FunBody";
	t->attr.nt.numNode = 2;
	switch(token)
	{
		case TK_KEY_FUN:
		case TK_KEY_INT:
			(t->attr).nt.child[0]=declarations();
			(t->attr).nt.child[1]=otherStatements();
			break;
		case TK_ID:
		case TK_KEY_IF:
		case TK_KEY_WHILE:
		case TK_KEY_CALL:
		case TK_KEY_RETURN:
		case TK_KEY_GET:
		case TK_KEY_PRINT:
			(t->attr).nt.child[0]=otherStatements();
			(t->attr).nt.numNode =1;
			break;
		case TK_KEY_END:
			(t->attr).nt.numNode = 0;
			break;
		default:
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
	}
	return t;	
}
	
treeNode * declarations(void)
{
	treeNode * t =(treeNode * )newNode(NONTERMINAL);
	t->attr.nt.name = "Declarations";
	t->attr.nt.numNode = 2;
	switch(token)
	{
		case TK_KEY_INT:
		case TK_KEY_FUN:
			(t->attr).nt.child[0]=declaration();
			(t->attr).nt.child[1]=declarations();
			break;
		case TK_ID:
		case TK_KEY_IF:
		case TK_KEY_WHILE:
		case TK_KEY_CALL:
		case TK_KEY_RETURN:
		case TK_KEY_GET:
		case TK_KEY_PRINT:
			t->attr.nt.numNode = 0;			
			break;
		default:
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
	}
	return t;
}

treeNode * declaration(void)
{
	treeNode * t=(treeNode * )newNode(NONTERMINAL);
	t->attr.nt.name = "Declaration";
	t->attr.nt.numNode = 8; 
			treeNode * t1 = (treeNode * )newNode(TERMINAL);
			treeNode * t4 = (treeNode * )newNode(TERMINAL);
	switch(token)
	{
		case TK_KEY_INT:


			t1->attr.tm.tt = TK_KEY_INT;
			t1->attr.tm.val = (char *)copyString(tokenString);
			match(token);
			(t->attr).nt.child[0]=t1;
			
			treeNode * t2 = (treeNode * )newNode(TERMINAL);
			t2->attr.tm.tt = TK_ID;
			t2->attr.tm.val = (char *)copyString(tokenString);
			match(TK_ID);
			(t->attr).nt.child[1]=t2;

			treeNode * t3 = (treeNode * )newNode(TERMINAL);
			t3->attr.tm.tt = TK_SEMI;
			t3->attr.tm.val = (char *)copyString(tokenString);
			match(TK_SEMI);
			(t->attr).nt.child[2]=t3;
			t->attr.nt.numNode = 3;
			stInsert(t2->attr.tm.val,currentScope,VAR);
			break;
		case TK_KEY_FUN:
			
			pn=0;
			t4->attr.tm.tt = TK_KEY_FUN;
			t4->attr.tm.val = (char *)copyString(tokenString);
			match(token);
			(t->attr).nt.child[0]=t4;

			treeNode * t5 = (treeNode * )newNode(TERMINAL);
			t5->attr.tm.tt = TK_ID;
			t5->attr.tm.val = (char *)copyString(tokenString);
			match(TK_ID);
			(t->attr).nt.child[1]=t5;
			if(strcmp(t5->attr.tm.val,currentScope)==0)
			{
				error = TRUE;
				fprintf(listing,"\n>>>Error at line %d -> Variable/function with name same as function cannot be declared",lineNo);
				printf("\n>>>Error at line %d -> Variable/function with name same as function cannot be declared",lineNo);
			}

			stInsert(t5->attr.tm.val,currentScope,FUN);

			treeNode * t6 = (treeNode * )newNode(TERMINAL);
			t6->attr.tm.tt = TK_OPEN;
			t6->attr.tm.val = (char *)copyString(tokenString);
			match(TK_OPEN);
			(t->attr).nt.child[2]=t6;
			(t->attr).nt.child[3]=funDeclTypes();
			
			treeNode * t7 = (treeNode * )newNode(TERMINAL);
			t7->attr.tm.tt = TK_CLOSE;
			t7->attr.tm.val = (char *)copyString(tokenString);
			match(TK_CLOSE);
			(t->attr).nt.child[4]=t7;

			treeNode * t8 = (treeNode * )newNode(TERMINAL);
			t8->attr.tm.tt = TK_KEY_RESULT;
			t8->attr.tm.val = (char *)copyString(tokenString);
			match(TK_KEY_RESULT);
			(t->attr).nt.child[5]=t8;
			(t->attr).nt.child[6]=resultType();
			treeNode * t9 = (treeNode * )newNode(TERMINAL);

			if(t->attr.nt.child[6]->attr.nt.child[0]->attr.tm.tt==TK_KEY_INT)
				sentry->data.fun.retType = INT;
			else
				sentry->data.fun.retType = VOID;
			t9->attr.tm.tt = TK_SEMI;
			t9->attr.tm.val = (char *)copyString(tokenString);
			match(TK_SEMI);
			(t->attr).nt.child[7]=t9;
			break;
		default:
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
	}
	return t;}

treeNode * funDeclTypes(void)
{
	treeNode * t =(treeNode * )newNode(NONTERMINAL);
	t->attr.nt.name = "FunDeclTypes";
	t->attr.nt.numNode = 2;
			treeNode * t1 = (treeNode * )newNode(TERMINAL);
			treeNode * t2 = (treeNode * )newNode(TERMINAL);
	switch(token)
	{
		case TK_KEY_NONE:
			
			sentry->data.fun.param[pn] = VOID;
			pn++;
			t1->attr.tm.tt = TK_KEY_NONE;
			t1->attr.tm.val = (char *)copyString(tokenString);
			match(token);
			(t->attr).nt.child[0]=t1;
			t->attr.nt.numNode =1;
			
			break;
		case TK_KEY_INT:

			sentry->data.fun.param[pn]=INT;
			pn++;
			t2->attr.tm.tt = TK_KEY_INT;
			t2->attr.tm.val = (char *)copyString(tokenString);
			match(token);
			(t->attr).nt.child[0]=t2;
			(t->attr).nt.child[1]=funDeclTypesRest();
			break;
		default:
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
	}
	return t;
}
				
treeNode * funDeclTypesRest(void)				
{
	treeNode * t=(treeNode * )newNode(NONTERMINAL);
	t->attr.nt.name = "FunDeclTypesRest";
	t->attr.nt.numNode = 3;
			treeNode * t1 = (treeNode * )newNode(TERMINAL);
	switch(token)
	{
		case TK_COMMA:


			t1->attr.tm.tt = TK_COMMA;
			t1->attr.tm.val = (char *)copyString(tokenString);
			match(token);
			(t->attr).nt.child[0]=t1;
			sentry->data.fun.param[pn]=INT;
			pn++;
			treeNode * t2 = (treeNode * )newNode(TERMINAL);
			t2->attr.tm.tt = TK_KEY_INT;
			t2->attr.tm.val = (char *)copyString(tokenString);
			match(TK_KEY_INT);
			(t->attr).nt.child[1]=t2;
			(t->attr).nt.child[2]=funDeclTypesRest();
			break;
		case TK_CLOSE:
			t->attr.nt.numNode =0;
			break;
		default:
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
	}
	return t;
}
	
treeNode * otherStatements(void)
{
	treeNode * t = (treeNode * )newNode(NONTERMINAL);	
	t->attr.nt.name = "OtherStatements";
	t->attr.nt.numNode = 2;
	switch(token)
	{
		case TK_ID:
		case TK_KEY_IF:
		case TK_KEY_WHILE:
		case TK_KEY_CALL:
		case TK_KEY_RETURN:
		case TK_KEY_GET:
		case TK_KEY_PRINT:
			(t->attr).nt.child[0]=statement();
			(t->attr).nt.child[1]=otherStatements();
			break;
		case TK_KEY_END:
			t->attr.nt.numNode = 0;
			break;
		default:
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
					
	}
	return t;
}

treeNode * statement(void)
{
	treeNode * t = (treeNode *)newNode(NONTERMINAL);
	t->attr.nt.name = "Statement";
	t->attr.nt.numNode =1;
	switch(token)
	{
		case TK_ID:
			(t->attr).nt.child[0]=assignmentStmt();
			break;
		case TK_KEY_IF:
			(t->attr).nt.child[0]=conditionalStmt();
			break;
		case TK_KEY_WHILE:
			(t->attr).nt.child[0]=repetitiveStmt();
			break;
		case TK_KEY_RETURN:
			if(rflag==1)
				rflag =0;
			else
			{
				error = TRUE;
				fprintf(listing,"\n>>>Error at line %d ->function %s cannot have a return statement.",lineNo,currentScope);
				printf("\n>>>Error at line %d ->function %s cannot have a return statement.",lineNo,currentScope);
			}
			(t->attr).nt.child[0]=returnStmt();
			break;
		case TK_KEY_GET:
		case TK_KEY_PRINT:
			(t->attr).nt.child[0]=ioStmt();
			break;
		case TK_KEY_CALL:
			(t->attr).nt.child[0]=functionCallStmt();
			break;
		default:
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
	}
	return t;
}

treeNode * assignmentStmt(void)
{
	treeNode * t = (treeNode * )newNode(NONTERMINAL);
	t->attr.nt.name ="AssignmentStmt";
	t->attr.nt.numNode = 4;
			treeNode * t1 = (treeNode * )newNode(TERMINAL);
	switch(token)
	{
		case TK_ID:


			t1->attr.tm.tt = TK_ID;
			t1->attr.tm.val = (char *)copyString(tokenString);
			if(stLookUp(t1->attr.tm.val,currentScope)==1)
			{
				error = TRUE;
				fprintf(listing,"\n>>>Error at line : %d ->Variable %s undeclared",lineNo,t1->attr.tm.val);
				printf("\n>>>Error at line : %d ->Variable %s undeclared",lineNo,t1->attr.tm.val);
			}
			match(token);
			(t->attr).nt.child[0]=t1;

			treeNode * t2 = (treeNode * )newNode(TERMINAL);
			t2->attr.tm.tt = TK_EQUAL;
			t2->attr.tm.val = (char *)copyString(tokenString);
			match(TK_EQUAL);
			(t->attr).nt.child[1]=t2;
			(t->attr).nt.child[2]=expression();

			treeNode * t3 = (treeNode * )newNode(TERMINAL);
			t3->attr.tm.tt = TK_SEMI;
			t3->attr.tm.val = (char *)copyString(tokenString);
			match(TK_SEMI);
			(t->attr).nt.child[3]=t3;
			break;
		default:
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
	}
	return t;
}


treeNode * expression(void)
{
	treeNode * t=(treeNode * )newNode(NONTERMINAL);
	t->attr.nt.name = "Expression";
	t->attr.nt.numNode =2;
	switch(token)
	{
		case TK_OPEN:
		case TK_NUM:
		case TK_ID:
		case TK_KEY_CALL:
			(t->attr).nt.child[0]=term();
			(t->attr).nt.child[1]=eprime();
			break;
		default:
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
	}
	return t;
}

treeNode * eprime(void)
{
	treeNode * t =(treeNode * )newNode(NONTERMINAL);
	t->attr.nt.name = "EPrime";
	t->attr.nt.numNode = 3;
			treeNode * t1 = (treeNode * )newNode(TERMINAL);
	switch(token)
	{
		case TK_MINUS:
 		case TK_PLUS:


			t1->attr.tm.tt = token;
			t1->attr.tm.val = (char *)copyString(tokenString);
			match(token);
			(t->attr).nt.child[0]=t1;
			(t->attr).nt.child[1]=term();
			(t->attr).nt.child[2]=eprime();
			break;
		case TK_SEMI:
		case TK_CLOSE:
			t->attr.nt.numNode = 0;
			break;
		default:
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
	}
	return t;}
	
treeNode * term(void)
{
	treeNode * t=(treeNode * )newNode(NONTERMINAL);
	t->attr.nt.name ="Term";
	t->attr.nt.numNode = 2;
	switch(token)
	{
		case TK_OPEN:
		case TK_NUM:
		case TK_ID:
		case TK_KEY_CALL:
			(t->attr).nt.child[0]=factor();
			(t->attr).nt.child[1]=tprime();
			break;
		default:
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
	}
	return t;
}

treeNode * tprime(void)
{
	treeNode * t=(treeNode * )newNode(NONTERMINAL);
	t->attr.nt.name = "TPrime";
	t->attr.nt.numNode = 3;
			treeNode * t1 = (treeNode * )newNode(TERMINAL);
			treeNode * t2 = (treeNode * )newNode(TERMINAL);
	switch(token)
	{	
		case TK_TIMES:


			t1->attr.tm.tt = TK_TIMES;
			t1->attr.tm.val = (char *)copyString(tokenString);
			match(token);
			(t->attr).nt.child[0]=t1;
			(t->attr).nt.child[1]=factor();
			(t->attr).nt.child[2]=tprime();
			break;
		case TK_DIV:


			t2->attr.tm.tt = TK_DIV;
			t2->attr.tm.val = (char *)copyString(tokenString);
			match(token);
			(t->attr).nt.child[0]=t2;
			(t->attr).nt.child[1]=factor();
			(t->attr).nt.child[2]=tprime();
			break;
		case TK_PLUS:
		case TK_MINUS:
			t->attr.nt.numNode=0;
			break;
		default:
			t->attr.nt.numNode=0;
			break;			
	}
	return t;
}

treeNode * factor(void)
{
	treeNode * t=(treeNode * )newNode(NONTERMINAL);
	t->attr.nt.name = "Factor";
	t->attr.nt.numNode =3;
			treeNode * t1 = (treeNode * )newNode(TERMINAL);
			treeNode * t2 = (treeNode * )newNode(TERMINAL);
			treeNode * t3 = (treeNode * )newNode(TERMINAL);
			treeNode * t4 = (treeNode * )newNode(TERMINAL);
	switch(token)
	{
		case TK_OPEN:


			t1->attr.tm.tt = TK_OPEN;
			t1->attr.tm.val = (char *)copyString(tokenString);
			match(token);
			(t->attr).nt.child[0]=t1;
			(t->attr).nt.child[1]=expression();

			t2->attr.tm.tt = TK_CLOSE;
			t2->attr.tm.val = (char *)copyString(tokenString);
			match(TK_CLOSE);
			(t->attr).nt.child[2]=t2;
			break;
		case TK_ID:


			t3->attr.tm.tt = TK_ID;
			t3->attr.tm.val = (char *)copyString(tokenString);
			if(stLookUp(t3->attr.tm.val,currentScope)==1)
			{
				error = TRUE;
				fprintf(listing,"\n>>>Error at line : %d ->Variable %s undeclared",lineNo,t3->attr.tm.val);
				printf("\n>>>Error at line : %d ->Variable %s undeclared",lineNo,t3->attr.tm.val);
			}
			match(token);
			(t->attr).nt.child[0]=t3;
			t->attr.nt.numNode = 1;
			break;
		case TK_NUM:


			t4->attr.tm.tt = TK_NUM;
			t4->attr.tm.val = (char *)copyString(tokenString);
			match(token);
			(t->attr).nt.child[0]=t4;
			t->attr.nt.numNode = 1;
			break;
		case TK_KEY_CALL:
			rtflag = 1;
			(t->attr).nt.child[0]=functionCall();
			t->attr.nt.numNode =1;
			break;
		default:
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
	}
	return t;
}

treeNode * functionCall(void)
{
	treeNode * t=(treeNode * )newNode(NONTERMINAL);
	t->attr.nt.name = "FunctionCall";
	t->attr.nt.numNode = 5;
			treeNode * t1 = (treeNode * )newNode(TERMINAL);
	switch(token)
	{
		case TK_KEY_CALL:


			t1->attr.tm.tt = TK_KEY_CALL;
			t1->attr.tm.val = (char *)copyString(tokenString);
			match(token);
			(t->attr).nt.child[0]=t1;

			treeNode * t2 = (treeNode * )newNode(TERMINAL);
			t2->attr.tm.tt = TK_ID;
			t2->attr.tm.val = (char *)copyString(tokenString);
			if(stLookUp(t2->attr.tm.val,currentScope)==1 )
			{
				error = TRUE;
				if(strcmp(t2->attr.tm.val,currentScope)==0)
				{
					//error = TRUE;
					fprintf(listing,"\n>>>Error at line : %d ->Reference to same function not allowed",lineNo);
					printf("\n>>>Error at line : %d ->Reference to same function not allowed",lineNo);
				}
				else
				{
					//error = TRUE;
					fprintf(listing,"\n>>>Error at line : %d ->Variable %s undeclared",lineNo,t2->attr.tm.val);
					printf("\n>>>Error at line : %d ->Variable %s undeclared",lineNo,t2->attr.tm.val);				
				}
			}
			int np = check(t2->attr.tm.val,currentScope);
			
			match(TK_ID);
			(t->attr).nt.child[1]=t2;

			treeNode * t3 = (treeNode * )newNode(TERMINAL);
			t3->attr.tm.tt = TK_OPEN;
			t3->attr.tm.val = (char *)copyString(tokenString);
			match(TK_OPEN);
			(t->attr).nt.child[2]=t3;
			numpar = 0;
			(t->attr).nt.child[3]=actualParams();

			treeNode * t4 = (treeNode * )newNode(TERMINAL);
			t4->attr.tm.tt = TK_CLOSE;
			if(np!=numpar)
			{
				error = TRUE;
				fprintf(listing,"\n>>>Error at line %d -> Invalid number of arguments supplied for the function %s . Required no- %d . Provided no - %d",lineNo,t2->attr.tm.val,np,numpar); 
				printf("\n>>>Error at line %d -> Invalid number of arguments supplied for the function %s . Required no- %d . Provided no - %d",lineNo,t2->attr.tm.val,np,numpar); 			
			}
			t4->attr.tm.val = (char *)copyString(tokenString);			
			match(TK_CLOSE);
			(t->attr).nt.child[4]=t4;
			break;
		default:
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
	}
	return t;
}

treeNode * functionCallStmt(void)
{
	treeNode * t=(treeNode * )newNode(NONTERMINAL);
	t->attr.nt.name = "FunctionCallStmt";
	t->attr.nt.numNode = 2;
	
	switch(token)
	{
		case TK_KEY_CALL:
			rtflag = 0;
			(t->attr).nt.child[0] = functionCall();

			treeNode * t1 = (treeNode * )newNode(TERMINAL);
			t1->attr.tm.tt = TK_SEMI;
			t1->attr.tm.val = (char *)copyString(tokenString);
			match(TK_SEMI);
			(t->attr).nt.child[1]=t1;
			break;
		default:
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
	}
	return t;
}

treeNode * actualParams(void)
{
	treeNode * t=(treeNode * )newNode(NONTERMINAL);	
	t->attr.nt.name = "ActualParams";
	t->attr.nt.numNode = 2;
			treeNode * t1 = (treeNode * )newNode(TERMINAL);
			treeNode * t2 = (treeNode * )newNode(TERMINAL);
			treeNode * t3 = (treeNode * )newNode(TERMINAL);
	switch(token)
	{
		case TK_NUM:

			numpar++;
			t1->attr.tm.tt = TK_NUM;
			t1->attr.tm.val = (char *)copyString(tokenString);
			match(token);
			(t->attr).nt.child[0]=t1;
			(t->attr).nt.child[1]=actualParamsRest();
			break;
		case TK_ID:
	
			numpar++;
			t2->attr.tm.tt = TK_ID;
			t2->attr.tm.val = (char *)copyString(tokenString);
			
			match(token);
			(t->attr).nt.child[0]=t2;
			(t->attr).nt.child[1]=actualParamsRest();
			break;
		case TK_KEY_NONE:


			t3->attr.tm.tt = TK_KEY_NONE;
			t3->attr.tm.val = (char *)copyString(tokenString);
			match(TK_KEY_NONE);
			(t->attr).nt.child[0]=t3;
			t->attr.nt.numNode =1;
			break;
		default:
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
	}
	return t;
}

treeNode * actualParamsRest(void)
{
	treeNode * t=(treeNode * )newNode(NONTERMINAL);
	t->attr.nt.name = "ActualParamsRest";
	t->attr.nt.numNode = 2;
			treeNode * t1 = (treeNode * )newNode(TERMINAL);
	switch(token)
	{
		case TK_COMMA:


			t1->attr.tm.tt = TK_COMMA;
			t1->attr.tm.val = (char *)copyString(tokenString);			
			match(token);
			(t->attr).nt.child[0]=t1;

			(t->attr).nt.child[1]=remActualParamsRest();
			break;
		case TK_CLOSE:
			t->attr.nt.numNode =0;
			break;
		default:
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
	}
	return t;
}

treeNode * remActualParamsRest(void)
{
	treeNode * t=(treeNode * )newNode(NONTERMINAL);
	t->attr.nt.name = "RemActualParamsrest";
	t->attr.nt.numNode = 2;
			treeNode * t1 = (treeNode * )newNode(TERMINAL);
			treeNode * t2 = (treeNode * )newNode(TERMINAL);
	switch(token)
	{
		case TK_ID:

			numpar++;
			t1->attr.tm.tt = TK_ID;
			t1->attr.tm.val = (char *)copyString(tokenString);
			match(token);
			(t->attr).nt.child[0]=t1;
			(t->attr).nt.child[1]=actualParamsRest();
			break;
		case TK_NUM:

			numpar++;
			t2->attr.tm.tt = TK_NUM;
			t2->attr.tm.val = (char *)copyString(tokenString);
			match(token);
			(t->attr).nt.child[0]=t2;
			(t->attr).nt.child[1]=actualParamsRest();
			break;
		default:
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
	}
	return t;
}

treeNode * conditionalStmt(void)
{
	treeNode * t=(treeNode * )newNode(NONTERMINAL);
	t->attr.nt.name = "ConditionalStmt";
	t->attr.nt.numNode = 7;
			treeNode * t1 = (treeNode * )newNode(TERMINAL);
	switch(token)
	{
		case TK_KEY_IF:


			t1->attr.tm.tt = TK_KEY_IF;	
			t1->attr.tm.val = (char *)copyString(tokenString);
			match(token);			
			(t->attr).nt.child[0]=t1;
			treeNode * t2 = (treeNode * )newNode(TERMINAL);
			t2->attr.tm.tt = TK_OPEN;
			t2->attr.tm.val = (char *)copyString(tokenString);
			(t->attr).nt.child[1]=t2;
			match(TK_OPEN);
			(t->attr).nt.child[2]=boolExp();
			
			treeNode * t3 = (treeNode * )newNode(TERMINAL);
			t3->attr.tm.tt = TK_CLOSE;
			t3->attr.tm.val = (char *)copyString(tokenString);
			match(TK_CLOSE);
			(t->attr).nt.child[3]=t3;
			treeNode * t4 = (treeNode * )newNode(TERMINAL);
			t4->attr.tm.tt = TK_KEY_BEGIN;
			t4->attr.tm.val = (char *)copyString(tokenString);
			(t->attr).nt.child[4]=t4;
			match(TK_KEY_BEGIN);
			(t->attr).nt.child[5]=otherStatements();
			treeNode * t5 = (treeNode * )newNode(TERMINAL);
			t5->attr.tm.tt = TK_KEY_END;
			t5->attr.tm.val = (char *)copyString(tokenString);
			(t->attr).nt.child[6]=t5;
			match(TK_KEY_END);
			break;
		default:
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
	}
	return t;
}
		
treeNode * boolExp(void)
{
	treeNode * t=(treeNode * )newNode(NONTERMINAL);
	t->attr.nt.name = "BoolExp";
	t->attr.nt.numNode = 5;	
			treeNode * t1 = (treeNode * )newNode(TERMINAL);
	switch(token)
	{
		case TK_ID:


			t1->attr.tm.tt = TK_ID;
			t1->attr.tm.val = (char *)copyString(tokenString);
			if(stLookUp(t1->attr.tm.val,currentScope)==1)
			{
				error = TRUE;
				fprintf(listing,"\n>>>Error at line : %d ->Variable %s undeclared",lineNo,t1->attr.tm.val);
				printf("\n>>>Error at line : %d ->Variable %s undeclared",lineNo,t1->attr.tm.val);
			}
			match(token);
			(t->attr).nt.child[0]=t1;
			treeNode * t2 = (treeNode * )newNode(TERMINAL);
			t2->attr.tm.tt = TK_DOT;
			t2->attr.tm.val = (char *)copyString(tokenString);
			(t->attr).nt.child[1]=t2;
			match(TK_DOT);
			(t->attr).nt.child[2]=boolOps();
			treeNode * t3 = (treeNode * )newNode(TERMINAL);
			t3->attr.tm.tt = TK_DOT;
			t3->attr.tm.val = (char *)copyString(tokenString);
			(t->attr).nt.child[3]=t3;
			match(TK_DOT);
			treeNode * t4 = (treeNode * )newNode(TERMINAL);
			t4->attr.tm.tt = TK_ID;
			t4->attr.tm.val = (char *)copyString(tokenString);
			if(stLookUp(t4->attr.tm.val,currentScope)==1)
			{
				error = TRUE;
				fprintf(listing,"\n>>>Error at line : %d ->Variable %s undeclared",lineNo,t4->attr.tm.val);
				printf("\n>>>Error at line : %d ->Variable %s undeclared",lineNo,t4->attr.tm.val);
			}
			(t->attr).nt.child[4]=t4;
			match(TK_ID);
			break;
		default:
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
	}
	return t;
}

treeNode * boolOps(void)
{
	treeNode * t=(treeNode * )newNode(NONTERMINAL);
	t->attr.nt.name = "BoolOps";
	t->attr.nt.numNode = 1;
			treeNode * t1 = (treeNode * )newNode(TERMINAL);
			treeNode * t2 = (treeNode * )newNode(TERMINAL);
			treeNode * t3 = (treeNode * )newNode(TERMINAL);
			treeNode * t4 = (treeNode * )newNode(TERMINAL);
			treeNode * t5 = (treeNode * )newNode(TERMINAL);
			treeNode * t6 = (treeNode * )newNode(TERMINAL);
	switch(token)
	{
		case TK_EQUAL:


			t1->attr.tm.tt = TK_EQUAL;
			t1->attr.tm.val = "=";
			match(token);
			(t->attr).nt.child[0]=t1;
			break;
		case TK_NOTEQUAL:


			t2->attr.tm.tt = TK_NOTEQUAL;
			t2->attr.tm.val = "!=";
			match(token);
			(t->attr).nt.child[0]=t2;
			break;
		case TK_LT:


			t3->attr.tm.tt = TK_LT;
			t3->attr.tm.val = "<";
			match(token);
			(t->attr).nt.child[0]=t3;
			break;
		case TK_GT:


			t4->attr.tm.tt = TK_GT;
			t4->attr.tm.val = ">";
			match(token);
			(t->attr).nt.child[0]=t4;
			break;
		case TK_LEQ:


			t5->attr.tm.tt = TK_LEQ;
			t5->attr.tm.val = "<=";
			match(token);
			(t->attr).nt.child[0]=t5;
			break;
		case TK_GEQ:		


			t6->attr.tm.tt = TK_GEQ;
			t6->attr.tm.val = ">=";
			match(token);
			(t->attr).nt.child[0]=t6;
			break;
		default:
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
	}
	return t;
}

treeNode * repetitiveStmt(void)
{
	treeNode * t=(treeNode * )newNode(NONTERMINAL);
	t->attr.nt.name ="RepetitiveStmt";
	t->attr.nt.numNode = 7;
			treeNode * t1 = (treeNode * )newNode(TERMINAL);
	switch(token)
	{
		case TK_KEY_WHILE:


			t1->attr.tm.tt = TK_KEY_WHILE;
			t1->attr.tm.val = (char *)copyString(tokenString);
			match(token);
			(t->attr).nt.child[0]=t1;
			treeNode * t2 = (treeNode * )newNode(TERMINAL);
			t2->attr.tm.tt = TK_OPEN;
			t2->attr.tm.val = (char *)copyString(tokenString);
			(t->attr).nt.child[1]=t2;
 			match(TK_OPEN);
			(t->attr).nt.child[2]=boolExp();
			treeNode * t3 = (treeNode * )newNode(TERMINAL);
			t3->attr.tm.tt = TK_CLOSE;
			t3->attr.tm.val = (char *)copyString(tokenString);
			(t->attr).nt.child[3]=t3;
			match(TK_CLOSE);
			treeNode * t4 = (treeNode * )newNode(TERMINAL);
			t4->attr.tm.tt = TK_KEY_BEGIN;
			t4->attr.tm.val = (char *)copyString(tokenString);
			(t->attr).nt.child[4]=t4;
			match(TK_KEY_BEGIN);
			(t->attr).nt.child[5]=otherStatements();

			treeNode * t5 = (treeNode * )newNode(TERMINAL);
			t5->attr.tm.tt = TK_KEY_END;
			t5->attr.tm.val = (char *)copyString(tokenString);
			match(TK_KEY_END);
			(t->attr).nt.child[6]=t5;
			break;
		default:
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
	}
	return t;
}

treeNode * returnStmt(void)
{
	treeNode * t=(treeNode * )newNode(NONTERMINAL);
	t->attr.nt.name ="ReturnStmt";
	t->attr.nt.numNode = 3;
			treeNode * t1 = (treeNode * )newNode(TERMINAL);
	switch(token)
	{
		case TK_KEY_RETURN:

			if(strcmp(currentScope,"main")==0)
			{
				fprintf(listing,"\n>>>Error at line %d -> Return Statement not allowed in main function",lineNo);
				printf("\n>>>Error at line %d -> Return Statement not allowed in main function",lineNo);
				error = TRUE;
			}
			t1->attr.tm.tt = TK_KEY_RETURN;
			t1->attr.tm.val = (char *)copyString(tokenString);
			match(token);
			(t->attr).nt.child[0]=t1;
			(t->attr).nt.child[1]=returnVal();
			treeNode * t2 = (treeNode * )newNode(TERMINAL);
			t2->attr.tm.tt = TK_SEMI;
			t2->attr.tm.val = (char *)copyString(tokenString);
			(t->attr).nt.child[2]=t2;
			match(TK_SEMI);
			break;
		default:
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
	}
	return t;
}

treeNode * returnVal(void)
{
	treeNode * t=(treeNode * )newNode(NONTERMINAL);
	t->attr.nt.name ="ReturnVal";
	t->attr.nt.numNode = 1;
			treeNode * t1 = (treeNode * )newNode(TERMINAL);
			treeNode * t2 = (treeNode * )newNode(TERMINAL);
	switch(token)
	{
		case TK_ID:


			t1->attr.tm.tt = TK_ID;
			t1->attr.tm.val = (char *)copyString(tokenString);
			if(stLookUp(t1->attr.tm.val,currentScope)==1)
			{
				error = TRUE;
				fprintf(listing,"\n>>>Error at line : %d ->Variable %s undeclared",lineNo,t1->attr.tm.val);
				printf("\n>>>Error at line : %d ->Variable %s undeclared",lineNo,t1->attr.tm.val);
			}
			match(token);
			(t->attr).nt.child[0]=t1;			
			break;
		case TK_NUM:


			t2->attr.tm.tt = TK_NUM;
			t2->attr.tm.val = (char *)copyString(tokenString);
			match(token);
			(t->attr).nt.child[0]=t2;			
			break;
		default:
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
	}
	return t;
}

treeNode * ioStmt(void)
{
	treeNode * t = (treeNode * )newNode(NONTERMINAL);
	t->attr.nt.name = "IO_Stmt";
	t->attr.nt.numNode =3;
			treeNode * t1 = (treeNode * )newNode(TERMINAL);
			treeNode * t4 = (treeNode * )newNode(TERMINAL);
	switch(token)
	{
		case TK_KEY_PRINT:


			t1->attr.tm.tt = TK_KEY_PRINT;
			t1->attr.tm.val = (char *)copyString(tokenString);
			match(token);			
			(t->attr).nt.child[0]=t1;
			treeNode * t2 = (treeNode * )newNode(TERMINAL);
			t2->attr.tm.tt = TK_ID;
			t2->attr.tm.val = (char *)copyString(tokenString);
			if(stLookUp(t2->attr.tm.val,currentScope)==1)
			{
				error = TRUE;
				fprintf(listing,"\n>>>Error at line : %d ->Variable %s undeclared",lineNo,t2->attr.tm.val);
				printf("\n>>>Error at line : %d ->Variable %s undeclared",lineNo,t2->attr.tm.val);
			}
			(t->attr).nt.child[1]=t2;
			match(TK_ID);
			treeNode * t3 = (treeNode * )newNode(TERMINAL);
			t3->attr.tm.tt = TK_SEMI;
			t3->attr.tm.val = (char *)copyString(tokenString);
			(t->attr).nt.child[2]=t3;
			match(TK_SEMI);
			break;
		case TK_KEY_GET:


			t4->attr.tm.tt = TK_KEY_GET;
			t4->attr.tm.val = (char *)copyString(tokenString);
			match(token);			
			(t->attr).nt.child[0]=t4;
			treeNode * t5 = (treeNode * )newNode(TERMINAL);
			t5->attr.tm.tt = TK_ID;
			t5->attr.tm.val = (char *)copyString(tokenString);
			if(stLookUp(t5->attr.tm.val,currentScope)==1)
			{
				error = TRUE;
				fprintf(listing,"\n>>>Error at line : %d ->Variable %s undeclared",lineNo,t5->attr.tm.val);
				printf("\n>>>Error at line : %d ->Variable %s undeclared",lineNo,t5->attr.tm.val);
			}
			(t->attr).nt.child[1]=t5;
			match(TK_ID);
			treeNode * t6 = (treeNode * )newNode(TERMINAL);
			t6->attr.tm.tt = TK_SEMI;
			t6->attr.tm.val = (char *)copyString(tokenString);
			(t->attr).nt.child[2]=t6;
			match(TK_SEMI);
			break;
		default:
			syntaxError("Unexpected Token -> ");
			printToken(token,(char *)copyString(tokenString));
			token=getToken();
			break;
	}
	return t;
}

treeNode * parse(void)
{
	token = getToken();
	treeNode * t = programs();
	if(token!=ENDFILE)
		syntaxError("Code ends before file \n");
	return t;
}
