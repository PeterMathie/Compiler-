/*
 *This is where you specify the rules for your FUNC lexical analyser. Once you have completed
 * it, you will need to use FLEX to generate a lexical analyser from this file.
 */
 
%{
/*USER DEFINITIONS*/
#include "tokens.h"
%}

/*LEX DEFINITIONS*/
DIGIT [0-9]
INDENT [a-zA-Z][A-Za-z0-9]*

%%
"method"        { return METHOD;}
"("             { return LBRACKET;}
")"             { return RBRACKET;}
"vars"          { return VAR;}
"begin"         { return FBEGIN;}
"return"        { return RETURN;}
"endmethod"     { return ENDMETHOD;}
"read"          { return READ;}
"write"         { return WRITE;}
":="            { return ASSIGN;}
"if"            { return IF;}
"then"          { return THEN;}
"else"          { return ELSE;}
"endif"         { return ENDIF;}
"while"         { return WHILE;}
"endwhile"      { return ENDWHILE;}
"less"          { return LESS;}
"lessEq"        { return LESSEQUAL;}
"greater"       { return GREATER;}
"greaterEq"     { return GREATEREQUAL;}
"eq"            { return EQUAL;}
"nEq"           { return NOTEQUAL;} 
";"             { return SEMI;}
","             { return COMMA;}
"plus"          { return PLUS;}
"miuns"         { return MINUS;}
"times"         { return TIMES;}
"divide"        { return DIVIDE;}
"identify"      { return IDENTIFY;}
{INDENT}        { return ID;}
{DIGIT}+        { return INT;}
<<EOF>>         { return EOF;}

[ \t\n]+
%%

/*USER FUNCTIONS*/

int yywrap() { return EOF; }

