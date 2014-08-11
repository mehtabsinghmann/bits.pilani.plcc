#ifndef _GLOBALS_H_
#define _GLOBALS_H_
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#define MAXRESERVED 13
typedef enum
{
	ERROR,ENDFILE,TK_KEY_BEGIN,TK_KEY_END,TK_KEY_MAIN,TK_KEY_FUN,TK_KEY_RESULT,TK_KEY_NONE,TK_KEY_INT,TK_KEY_IF,TK_KEY_CALL,TK_KEY_WHILE,TK_KEY_PRINT,TK_KEY_GET,TK_KEY_RETURN,
	TK_ID,TK_NUM,TK_OPEN,TK_CLOSE,TK_SEMI,TK_EQUAL,TK_NOTEQUAL,TK_PLUS,TK_MINUS,TK_TIMES,TK_DIV,TK_LT,TK_GT,TK_LEQ,TK_GEQ,TK_DOT,TK_COMMA
}tokenType;
extern FILE * source;
extern FILE * listing;
extern FILE * code;
extern int lineNo;
extern int pn;
extern int rtflag;
extern int numpar;
typedef enum{TERMINAL,NONTERMINAL}nodeType;
typedef enum{VOID,INT}dataType;
typedef enum{VAR,FUN}entryType;
extern char * currentScope;
#define MAXCHILDREN 200
typedef struct nonTerminal
{
	char * name;
	int numNode;
	struct treeNode * child[MAXCHILDREN];
}nonTerminal;

typedef struct terminal
{
	tokenType tt;
	char * val;
}terminal;
typedef struct treeNode
{
	nodeType nodt;
	int lineNo;
	union
	{
		struct terminal tm;
		struct nonTerminal nt;
	}attr;
}treeNode;	
extern int echoSource;
extern int traceScan;
extern int traceParse;
extern int error;
#endif

