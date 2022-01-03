/**
 * Solution to Q3: Implement the AST parser here. Note that this
 * is essentially an extension of the solutions to Q2, so you 
 * may wish to copy and paste your solutions and extend that.
 * 
 * Add helper functions/code as you wish.
 */

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"
#include "tree.h"

//////////////////////////////////////////////////

// global variables

int symb;
extern int yylex(void);
extern char *yytext;
extern FILE *yyin;

//////////////////////////////////////////////////

// HELPER FUNCTIONS
//----------------------------------------------//

node * program();
node * methods();
node * args();
node * statements();
node * bop();
node * exps();

/**
 * Similar to showSimp from the lecture notes. 
 */
char *getSymb(int s){
   switch(s)
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
      case  IDENTIFY    : return "identify"  ;

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
{  printf("%s: found %s\n", rule, getSymb(symb));
   printf("%s: %s\n", rule, message);
   exit(0);
}
char * getChar(){
   if(yytext == NULL){
      error("getChar","yytext is null\n");
      return NULL;
   }
   else{
      return yytext;
   }
}
int getInt(){
   if(yytext == NULL){
      error("getChar","yytext is null\n");
      return 0;
   }
   else{
      return *yytext - '0';
   }
}



//-------------YOUR CODE BELOW THIS LINE----------------------//

/**
 *  This is where parser execution begins: it's the method for parsing programs.
 *  It corresponds to the top level, start symbol of FUNC grammars.
 */ 

//p ::= m
struct node *program(){
	extern node * methods();
   node * p;
   p = newInternalNode(symb);
   addBranch(p,methods());
   return p;
}
//m ::= 	method <id> ( [ a ] ) [ vars a ] begin s [ return <id>; ] endmethod; [m]
struct node * methods(){
   extern node * args();
   extern node * statements();
   extern node * methods();
   node * m;
   node * a;
   node * b;
   node * v;
   node * r;
   node * e;
	if(symb != METHOD)
		error("methods","method expected\n");
   m = newInternalNode(symb);
   lex();//METHOD
   if(symb!=ID){
		error("methods","ID expected\n");
   }
   addBranch(m, newIdLeaf(getChar()));//add ID
   lex();
   if(symb!=LBRACKET){
      error("methods","( expected\n");
   }     
   lex(); // )
   if(symb==ID){
      do{
         addBranch(m,args());          //adds all args as leaf nodes to the method node
      }while(symb==COMMA);
   }
   if(symb!=RBRACKET){ // )
      error("methods",") expected\n");
   }
   lex();
   if(symb==VAR){
      v = newInternalNode(VAR);
      addBranch(m,v);
      lex();
      do{
         addBranch(v,args()); 
      }while(symb==COMMA);
   }
   if(symb!=FBEGIN)
   	error("methods","begin expected\n");
   b = newInternalNode(FBEGIN);
   lex();
   addBranch(m,b);
   addBranch(b,statements());
   if(symb==RETURN){
      r = newInternalNode(RETURN);
      addBranch(m,r);
      lex();
      if(symb!=ID)
		   error("methods","ID expected\n");
      addBranch(r,newIdLeaf(getChar())); //ID of return statement
      lex();
      if(symb!=SEMI)
         error("methods","; expeceted\n");
      lex();
   }      
   if(symb!=ENDMETHOD)
   	error("methods","endmethod expected\n");
   e = newInternalNode(ENDMETHOD);
   addBranch(m,e);
   lex();

   if(symb!=SEMI){
   	error("methods","; expected\n");
   }

   lex();

   if(symb==METHOD){
      addBranch(m,methods());
      printf("%d",symb);
   }
   return m;
}
//a ::= <id>[,a] 
struct node * args(){
   node * a;
   if(symb == COMMA){
      lex();
   }
   if(symb!=ID)
		error("args","ID expected\n");
   a = newIdLeaf(getChar());
   lex();
   
   return a;
}
//s ::= 	<id> := e | if  b (es)  then s [else s] endif | while b (e) begin s endwhile | read <id> | write e | s; [ s ]
struct node * statements(){
   extern node * exps();
   extern node * statements();
   node * s;
   node * t;   //THEN
   node * e;   //ELSE
   node * ei;  //endif
   node * b;   //BEGIN
   node * ew;  //ENDWHILE

   switch (symb){
   case ID:
      s = newInternalNode(ASSIGN);// ::=
      addBranch(s,newIdLeaf(getChar())); // ID
      lex(); // ID
      lex();// ::=
      addBranch(s,exps()); // exp()
      break;
   case IF:
      s = newInternalNode(symb);// IF
      lex();
      addBranch(s,bop()); //</<=/=/!=
      if(symb!=LBRACKET)
      error("statements","( expected\n");
      lex();
      addBranch(s,exps()); //exps
      if(symb!=RBRACKET)
         error("statements",") expected\n");
      lex();
      if(symb!=THEN)
         error("statements",") expected\n");
      t = newInternalNode(symb); //THEN
      addBranch(s,t);
      lex();
      addBranch(t,statements());
      if(symb==ELSE){
         e = newInternalNode(symb);
         addBranch(s,e);
         lex();
         addBranch(e,statements());
      }
      if(symb!=ENDIF)
         error("statements","endif expected\n");
      ei = newInternalNode(symb);
      addBranch(s,ei);
      lex();
      break;
   case WHILE:
      s = newInternalNode(symb);
      lex();
      addBranch(s,bop()); //bop
      if(symb!=LBRACKET)
         error("statements","( expected\n");
      lex();
      addBranch(s,exps()); //exp
      if(symb!=RBRACKET)
         error("statements",") expected\n");
      lex();
      if(symb!=FBEGIN)
         error("statements","begin expected\n");
      b = newInternalNode(symb); //BEGIN
      addBranch(s,b);
      lex();
      addBranch(b,statements());    //statements
      if(symb!=ENDWHILE)
         error("statements","endwhile expected\n");
      ew = newInternalNode(symb); //ENDWHILE
      addBranch(s,ew);
      lex();
      break;
   case READ:
      s = newInternalNode(symb); //READ
      lex();
      addBranch(s,newIdLeaf(getChar()));  //ID
      break;
   case WRITE:
      s = newInternalNode(symb); //WRITE
      lex();
      addBranch(s,exps());  //exp
      break;
   default:
      error("statements","if/while/read/write expected\n");
      break;
   }
   if(symb!=SEMI)
      error("statements","; expected\n");
   lex();
   if(symb==ID||symb==IF||symb==WHILE||symb==READ||symb==WRITE)
      addBranch(s,statements());
   return s;
}
//b ::= less | lessEq | eq | nEq 
struct node * bop(){
   node * b;
   b = newInternalNode(symb);
   switch (symb){
      case LESS:
      case LESSEQUAL:
      case EQUAL:
      case NOTEQUAL:
         addBranch(b,newIdLeaf(getChar()));
         lex();
         break;
      default:
         error("bop",">/>/=/!= expected\n");
   }
   return b;

}
//es ::= <int> | <id> [ ( es ) ] | time ( es )  | divide ( es ) | plus( es ) | minus ( es ) | es [, es ]
struct node * exps(){
   extern node * exps();
   node * es;
   node * temp;
   //es = newInternalNode(symb);
   switch (symb) {
   case INT:
      es = newIntLeaf(getInt());
      lex();      
      break;
   case ID:
      es = newInternalNode(IDENTIFY);
      addBranch(es,newIdLeaf(getChar()));
      lex();
      if(symb == LBRACKET){
         lex();
         addBranch(es,exps());
         while(symb != RBRACKET){
            error("exp",") expected\n");
         }
         lex();
      }
      break;
   case TIMES:
   case DIVIDE:
   case PLUS:
   case MINUS:
      es = newInternalNode(symb);
      addBranch(es,newIdLeaf(getChar()));
      lex();
      if(symb != LBRACKET){
         error("exp","( expected");
      }
      lex();
      addBranch(es,exps());
      if(symb != RBRACKET){
         error("exp",") expected");
      }
      lex();
      break;
   default:
      break;
   }
      
   
   if(symb == COMMA ){
      lex();
      addBranch(es,exps());
   }
   return es;
}


/**
 * Execution starts here
 */
int main(int argc, char **argv){
	// open the file to be parsed, if possible
	if ((yyin = fopen(argv[1], "r")) == NULL)
	{
		printf("can't open %s\n", argv[1]);
		exit(0);
	}
   symb = yylex();

	struct node *progtree = program();
	if (progtree == NULL)
	{
		printf("program() returned null. Methods unimplemented?\n");
		return -1;
	}
	printTree(progtree);
	fclose(yyin);
}