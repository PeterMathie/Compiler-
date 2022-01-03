/**
 * Solutions to Q2: Implement your Recursive Decent Parser here.
 * Note here you do not need to produce an AST as output.
 * 
 * Add helper functions/code as you wish.
 */

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

//////////////////////////////////////////////////

// global variables

int symb;
extern int yylex(void);
extern char *yytext;
extern FILE *yyin;


void method(int);
void methods(int);
void args(int);
void statements(int);
void statement(int);
void rw(int);
void assign(int);
void ifcmd(int);
void whilecmd(int);
void cond(int);
void bop(int);
void exps(int);
void expcmd(int);
void intcmd(int);
void id(int);
void inttuple(int);


//////////////////////////////////////////////////

// 
//----------------HELPER FUNCTIONS------------//
/**
 * Similar to showSymb() from the lecture notes. 
 */
char * getSymb(int s)
{  switch(s)
   {  
      case  METHOD      : return "METHOD"    ;
      case  LBRACKET    : return "("         ;
      case  RBRACKET    : return ")"         ;
      case  VAR         : return "VAR"       ;
      case  FBEGIN      : return "FBEGIN"    ;       
      case  RETURN      : return "RETURN"    ;
      case  ENDMETHOD   : return "ENDMETHOD" ;
      case  READ        : return "READ"      ;
      case  WRITE       : return "WRITE"     ;
      case  ASSIGN      : return ":="        ;
      case  IF          : return "IF"        ;
      case  THEN        : return "THEN"      ;
      case  ELSE        : return "ELSE"      ;
      case  ENDIF       : return "ENDIF"     ;
      case  WHILE       : return "WHILE"     ;
      case  ENDWHILE    : return "ENDWHILE"  ;
      case  LESS        : return "less"      ;
      case  LESSEQUAL   : return "lessEQ"    ;
      case  GREATER     : return "greater"   ;
      case  GREATEREQUAL: return "greaterEq" ;
      case  EQUAL       : return "eq"        ;
      case  NOTEQUAL    : return "nEq"       ;
      case  SEMI        : return ";"         ;
      case  COMMA       : return ","         ;
      case  PLUS        : return "plus"      ;
      case  MINUS       : return "minus"     ;
      case  TIMES       : return "times"     ;  
      case  DIVIDE      : return "divide"    ;
      case  ID          : return "ID"        ;
      case  INT         : return "INT"       ;
      case  EOF         : return "EOF"       ;

      default: 
         printf("bad symbol: %d",s);
         return NULL;
   }
}

void printSymb(){
   char * s;
   printf("%s ",getSymb(symb));
   if(symb == ID || symb == INT){
      if(yytext == NULL){
         printf("Error: yytext is NULL");
      }
      else
         printf("%s\n",yytext);
   }
   else
      printf("\n");
}

void lex(){
   printSymb();
   symb = yylex();
}
void error(char * rule, char * message)
{  printf("%s: found %s\n",rule,getSymb(symb));
   printf("%s: %s\n",rule,message);
   exit(0);
}
void rule(char * name, int depth){
   int i;
   for(i=0;i<depth;i++)
      printf(" ");
      printf("%s\n",name);
   
}


//-------------YOUR CODE BELOW THIS LINE----------------------//

/**
 *  This is where parser execution begins: it's the method for parsing programs.
 */ 

//<program> ::= <methods>
void program(int depth){
   rule("program",depth);
   methods(depth+1);
}

//<methods> ::= <method>;[<methods>]
void methods(int depth){
   rule("methods",depth);
   method(depth+1);
   if(symb != SEMI){
      error("methods","; expected\n");
   }
   lex();
   if(symb == METHOD){
      methods(depth+1);
   }
}

//<method> ::= method <id>([<args>]) [vars <args>] begin <statements> [return <id>;] endmethod
void method(int depth){
    rule("method",depth);
    if(symb != METHOD){
        error("method","method expected\n");
    }
    lex();
    id(depth+1);
    if(symb != LBRACKET){
        error("method","( expected\n");
    }
    lex();
    if(symb == ID){
        args(depth+1);
    }
    if(symb != RBRACKET){
        if(symb)
        error("method",") expected\n");
    }
    lex();
    if(symb == VAR){
        lex();
        args(depth+1);
    }
    if(symb != FBEGIN){
        error("method","begin expected\n");
    }
    lex();
    statements(depth+1);
    if(symb == RETURN){
        lex();
        id(depth+1);
        if(symb != SEMI){
            printf("weed");
            error("method","; expected\n");
        }
        lex();
    }
    
    if(symb!= ENDMETHOD){
            error("method","endmethod expected\n");
        }
    lex();
    
}

//<args> ::= <id>[,<args>]
void args(int depth){
   rule("args",depth);
   if(symb != ID){
      error("args","arg expected\n");
   }
   id(depth+1);
   if(symb == COMMA){
      lex();
      args(depth+1);
   }
}

//<statements> ::= <statement>;[<statements>]
void statements(int depth){
   rule("statements",depth);
   statement(depth+1);
   if(symb != SEMI){
      error("statements","; expected\n");
   }
   lex();
   if(symb == ID ||symb == IF ||symb == WHILE ||symb == READ ||symb == WRITE ){
      statements(depth+1);
   }
}

//<statement> ::= <assign> | <if> | <while> | <rw>
void statement(int depth){
   rule("statement",depth);
   switch (symb) {
   case ID:
         assign(depth+1);
         break;
   case IF:
         ifcmd(depth+1);
         break;
   case WHILE:
         whilecmd(depth+1);
         break;
   case READ:
         rw(depth+1);
         break;
   case WRITE:
         rw(depth+1);
         break;
   default:
         error("statement","assign/if/while/read/write expected\n");
         break;
   }
}

//<rw> ::= read <id> | write <exp>
void rw(int depth){
   rule("rw",depth);
   switch (symb)
   {
   case READ:
         lex();
         id(depth+1);
         break;
   case WRITE:
         lex();
         expcmd(depth+1);
         break;
   default:
         error("rw","read/write expected");
         break;
   }
}

//<assign> ::= <id> := <exp>
void assign(int depth){
   rule("assign",depth);
   id(depth + 1);
   if(symb != ASSIGN){
      error("assign",":= expected");
   }
   lex();
   expcmd(depth+1);
}

//<if> ::= if  <cond> then <statements> [else <statements>] endif
void ifcmd(int depth){
   rule("if",depth);
   if(symb != IF){
      error("if","if expected\n");
   }
   lex();
   cond(depth+1);
   if(symb != THEN){
      error("if","then expected\n");
   }
   lex();
   statements(depth+1);
   if(symb == ELSE){
      lex();
      statements(depth+1);
   }
   if(symb != ENDIF){
      error("if","endif expected\n");
   }
   lex();
}

//<while> ::= while <cond> begin <statements> endwhile
void whilecmd(int depth){
   rule("while",depth);
   if(symb != WHILE){
      error("while","while expected\n");
   }
   lex();
   cond(depth+1);
   if(symb != FBEGIN){
      error("while","begin expected\n");
   }
   lex();
   statements(depth+1);
   if(symb != ENDWHILE){
      error("while","endwhile expected\n");
   }
   lex();
}

//<cond> ::= <bop> ( <exps> )
void cond(int depth){
   rule("cond",depth);
   bop(depth+1);
   if(symb != LBRACKET){
      error("cond","( expected\n");
   }
   lex();
   if(symb == ID || symb == INT){
      exps(depth+1);
   }
   if(symb != RBRACKET){
      if(symb)
      error("cond",") expected\n");
   }
   lex();
}

//<bop> ::= less | lessEq | eq | nEq
void bop(int depth){
   rule("bop",depth);
   switch (symb){
   case LESS:
   case LESSEQUAL:
   case EQUAL:
   case NOTEQUAL:
      lex();
      break;
   default:
      error("bop","</<=/=/!= expected\n");
   }
}

//<exps> ::= <exp> [,<exps>]
void exps(int depth){
   rule("exps",depth);
   expcmd(depth+1);
   if(symb==COMMA){
      lex();
      exps(depth+1);
   }
}

//<exp> ::= <id>[( <exps> )] | <int> | times ( <exps> )| divide ( <exps> ) | plus ( <exps> ) | minus ( <exps> )
void expcmd(int depth){
    rule("exp",depth);
    switch(symb){
        case ID:
            id(depth+1);
            if(symb == LBRACKET){
                lex();
                exps(depth+1);
                if(symb != RBRACKET){
                error("exp",") expected\n");
                }
                lex();
            }
            break;
        case INT:
            intcmd(depth+1);
            break;
        case TIMES:
        case DIVIDE:
        case PLUS:
        case MINUS:
            lex();
            if(symb != LBRACKET){
               error("inttuple","( expected\n");
            }
            lex();
            exps(depth+1);
            if(symb != RBRACKET){
               error("inttuple",") expected\n");
            }
            lex();
            break;
        default:
            error("exp","id/int expected\n");
            break;
    }
}

void id(int depth){
   rule("id",depth);
   if(symb != ID){
      error("id","id expected\n");
   }

   lex();
}

void intcmd(int depth){
   rule("int",depth);
   if(symb != INT ){
      error("int","int expected\n");
   }

   lex();
}

//////////////////////////////////////////////////



/**
 * Execution starts here
 */
int main(int argc, char **argv){
	// open the file to be parsed, if possible
	if ((yyin = fopen(argv[1], "r")) == NULL){
		printf("can't open %s\n", argv[1]);
		exit(0);
	}
   symb = yylex();
   program(0);
   printSymb();
   while(symb!=EOF){
      symb = yylex();
      printSymb();
   }
   fclose(yyin);
}