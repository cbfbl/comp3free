%{

/* Declarations section */
#include "parser.tab.hpp"
#include "hw3_output.hpp"
#include "types.hpp"

%}

%option yylineno
%option noyywrap

%%



void                            return new BasicType(yytext);
int                             return INT;
byte                            return BYTE;
b                               return B;
bool                            return BOOL;
and                             return AND;
or                              return OR;
not                             return NOT;
true                            return TRUE;
false                           return FALSE;
return                          return RETURN;
if                              return IF;
else                            return ELSE;
while                           return WHILE;
break                           return BREAK;
continue                        return CONTINUE;
;                               return SC;
,                               return COMMA;
\(                              return LPAREN;
\)                              return RPAREN;
\{                              return LBRACE;
\}                              return RBRACE;
=                               return ASSIGN;
\<|>|<=|>=                      return RELOP;
==|!=                           return RELEQ;
[\*\/]                          return BINOPH;
[\+\-]                          return BINOPL;
[a-zA-z][a-zA-z0-9]*            return ID;
0|[1-9][0-9]*                   return NUM;
\"([^\n\r\"\\]|\\[rnt"\\])+\"	  return STRING;
<<EOF>>                         return 0;
[\r\n\t ]|\/\/[^\r\n]*[\r|\n|\r\n]?	    ;
.                               output::errorLex(yylineno); exit(0);


%%
