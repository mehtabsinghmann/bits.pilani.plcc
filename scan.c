#include "globals.h"
#include "util.h"
#include "scan.h"

typedef enum
{
	START,INNEQ,INLEQ,INGEQ,INNUM,INID,DONE
}stateType;

char tokenString[MAXTOKENLEN+1];

#define BUFLEN 256
static char lineBuf[BUFLEN];
static int linePos = 0;
static int bufSize = 0;

static char getNextChar(void)
{
	if(!(linePos<bufSize))
	{
		lineNo++;
		if(fgets(lineBuf,BUFLEN-1,source))
		{
			if(echoSource)
				fprintf(listing,"%4d: %s",lineNo,lineBuf);
			bufSize = strlen(lineBuf);
			linePos =0;
			return lineBuf[linePos++];
		}
		else 
			return EOF;
	}
	else
		return lineBuf[linePos++];
}

static void ungetNextChar(void)
{
	linePos--;
}
 
static struct{
	char * str;
	tokenType tok;
}reservedWords[MAXRESERVED]
	={{"begin",TK_KEY_BEGIN},{"end",TK_KEY_END},{"main",TK_KEY_MAIN},{"function",TK_KEY_FUN},
	{"result",TK_KEY_RESULT}, {"none",TK_KEY_NONE},{"int",TK_KEY_INT},{"if",TK_KEY_IF},{"call",TK_KEY_CALL},
	{"while",TK_KEY_WHILE},{"print",TK_KEY_PRINT},{"get",TK_KEY_GET},{"return",TK_KEY_RETURN}};

static tokenType reservedLookup(char *s)
{
	int i;
	for(i=0;i<MAXRESERVED;i++)
	{
		if(!strcmp(s,reservedWords[i].str))
			return reservedWords[i].tok;
	}
	return TK_ID;
}

tokenType getToken(void)
{
	int tokenStringIndex =0;
	tokenType currentToken;
	stateType state = START;
	int save;
	while(state!=DONE)
	{
		char c  = getNextChar();
		save = TRUE;
		switch(state)
		{
			case START:
				if(isdigit(c))
					state = INNUM;
				else if (isalpha(c))
					state = INID;
				else if((c==' ') || (c=='\t') || (c=='\n')|| ( c==13))
					save = FALSE;
				else if(c=='!')
				{	
					c = getNextChar();
					state =DONE;
					if(c=='=')
						currentToken = TK_NOTEQUAL;
					else
						
					{
						currentToken = ERROR;		
						ungetNextChar();
					}					
				}
				else if(c=='<')
				{
					state =DONE;					
					c = getNextChar();
					if(c=='=')
						currentToken = TK_LEQ;
					else
						
					{
						currentToken = TK_LT;		
						ungetNextChar();
					}					
				}
				else if(c=='>')
				{
					state =DONE;					
					c = getNextChar();
					if(c=='=')
						currentToken = TK_GEQ;
					else
						
					{
						currentToken = TK_GT;		
						ungetNextChar();
					}					
				}
				else
				{
					state = DONE;
					switch(c)
					{
						case EOF:
							save = FALSE;
							currentToken = ENDFILE;
							break;
						case '=':
							currentToken = TK_EQUAL;
							break;
						case '(':
							currentToken = TK_OPEN;
							break;
						case ')':
							currentToken = TK_CLOSE;
							break;
						case ';':
							currentToken = TK_SEMI;
							break;
						case '+':
							currentToken = TK_PLUS;
							break;
						case '-':
							currentToken = TK_MINUS;
							break;
						case '*':
							currentToken = TK_TIMES;
							break;
						case '/':
							currentToken = TK_DIV;
							break;
						case '.':
							currentToken = TK_DOT;
							break;
						case ',':
							currentToken = TK_COMMA;
							break;	
						default:
							currentToken = ERROR;
						break;
					}
				}
				break;
		case INNUM:
			if(!isdigit(c))
			{			
				ungetNextChar();
				save = FALSE;
				state = DONE;
				currentToken = TK_NUM;
			}
			break;
		case INID:
			if(!isalpha(c))
			{	
				ungetNextChar();
				save = FALSE;
				state = DONE;
				currentToken = TK_ID;
			}
			break;
		case DONE:
			break;
		default:
			fprintf(listing,"Scanner Bug: state = %d\n",state);
			state = DONE;
			currentToken = ERROR;
			break;
		}
		if((save) && (tokenStringIndex <= MAXTOKENLEN))
			tokenString[tokenStringIndex++] = c;
		if(state==DONE)
		{
			tokenString[tokenStringIndex] = '\0';
			if(currentToken == TK_ID)
				currentToken = reservedLookup(tokenString);
		}
	}

	if(traceScan)
	{
		fprintf(listing,"\t%d: ",lineNo);
		printToken(currentToken,tokenString);
	}
	return currentToken;
}
