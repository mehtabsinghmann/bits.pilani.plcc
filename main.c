#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"
#include "symtab.h"
#include "ast.h"
#include "cgen.h"
int lineNo = 0;
int pn = 0;
int rtflag=0;
int numpar = 0;
struct symTabEntry * sentry=NULL;
FILE * source;
char * currentScope = NULL;
FILE * listing;
FILE * code;
int echoSource = TRUE;
int traceScan =TRUE;
int traceParse = TRUE;
int error = FALSE;
int main(int argc ,char * argv[])
{
	treeNode * syntaxTree;	
	pn=0;
	char pgm[20];
	if(argc !=2)
	{
		fprintf(stderr,"Usage : %s <filename>\n",argv[0]);
		exit(1);
	}
	strcpy(pgm,argv[1]);
	source = fopen(pgm,"r");
	if(source==NULL)
	{
		fprintf(stderr,"FILE %s not found\n",pgm);
		exit(1);
	}
//	source = fopen("input.txt","r");
	listing = fopen("output.txt","w");
	syntaxTree = (treeNode * )parse();
	if(traceParse)
	{
		fprintf(listing,"\n\t\t\tSyntax Tree : \n");
		fprintf(listing,"%s",(syntaxTree->attr).nt.name);
		printTree(syntaxTree);
	}
	treeNode * abstractSTree;
	printSymTab(listing);
	if(error==FALSE)
	{
	//	printf("Successfully Scanned and Parsed ...");
		abstractSTree = (treeNode *)genAst(syntaxTree);
		fprintf(listing,"\n\n\t\t\t ABSTRACT SYNTAX TREE\n");
		fprintf(listing,"%s",(abstractSTree->attr).nt.name);
		printABSTree(abstractSTree);
		char * codefile;
		//codefile = "output.asm";
		int fnlen = strcspn(pgm,".");
		codefile = (char *) calloc(fnlen + 4,sizeof(char));
		strncpy(codefile,pgm,fnlen);
		strcat(codefile,".asm");
		code = fopen(codefile,"w");
		codeGen(abstractSTree);
		fclose(code);
		printf("Compiled Successfully...");
	}
	fclose(listing);
	fclose(source);		
	return 0;
}
