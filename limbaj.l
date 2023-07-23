%{
#include <stdio.h>
#include "arbore.h"
#include "y.tab.h"
%}
%option noyywrap
%%
"int"|"float"|"char"|"string"|"bool" {yylval.sir=strdup(yytext);return TIP;}
"int main()" {return MAIN;}
"[" {return PARANTEZAPD;}
"]" {return PARANTEZAPI;}
"{" {return BGIN;}
"const" {return CONST;}
"}" {return END;}
"class" {return CLASA;}
"if" {return IF;}
"for" {return FOR;}
"while" {return WHILE;}
"return" {return RETURN;}
"TypeOf" {return TYPEOF;}
"Eval" {return EVAL;}
"true"|"TRUE"|"false"|"FALSE" {yylval.sir=strdup(yytext);return BOOLvaloare;}
[_a-zA-Z][_a-zA-Z0-9]* {yylval.sir=strdup(yytext);return ID;}
"+" {return PLUS;}
"-" {return MINUS;}
"/" {return IMPARTIRE;}
"*" {return INMULTIRE;}
"=" {return ASSIGN;}
"++"|"--" {return INCdec;}
[0-9]+ {yylval.sir=strdup(yytext);return NR;}
[0-9]+\.[0-9]* {yylval.sir=strdup(yytext);return FRAC;}
\'.\' {yylval.sir=strdup(yytext);return LIT;}
\".+\" {yylval.sir=strdup(yytext);return SIR;}
"=="|"!="|"<"|"<="|">"|">=" {return BOOLCOMP;}
"&&" {return BOOLAND;}
"||" {return BOOLOR;}
"!" {return BOOLNOT;}

[ \t] ;
\n {yylineno++;}
. {return yytext[0];}
