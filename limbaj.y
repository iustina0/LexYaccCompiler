%{
#define _GNU_SOURCE
#include <stdio.h>
#include "obiecte.h"


extern FILE* yyin;
extern char* yytext;
extern int yylineno;

%}

%union{
     nod nod;
     char* sir;
     float frac;
     int nr;
}
%token<sir> ID EVAL NR FRAC TIP MAIN END RETURN ASSIGN CLASA TYPEOF INCdec CONST BOOLeq BOOLCOMP BOOLOR BOOLAND BOOLNOT IF FOR WHILE BGIN LIT SIR BOOLvaloare PLUS MINUS INMULTIRE IMPARTIRE PARANTEZAPD PARANTEZAPI

%type <nod> expresie
%type<sir> class_obj list_ID array_name type_atribut param lista_param boolean_expr boolean_term boolean_factor
%left PLUS
%left MINUS
%left IMPARTIRE
%left INMULTIRE
%left BOOLandor
%left '('
%left ')'
%start progr
%%
progr: declaratii bloc {printf("program corect sintactic\n");}
     ;

declaratii :  declaratie ';'
	   | declaratii declaratie ';'
	   ;

declaratii_clasa :  declaratie_clasa ';'
     | declaratii_clasa declaratie_clasa ';'
     ;   

declaratie_clasa : TIP ID {add_para_class($1, $2); }
           | TIP array_name {add_para_class($1, $2); }
           | TIP ID '(' lista_param ')' BGIN list END {add_metode($1, $2);}
           | TIP ID '(' ')' BGIN list END {add_metode($1, $2);}
           ;

declaratie : TIP list_ID {DeclarareObiecte($1); }
           | TIP ID {DeclarareObiect($1, $2);}
           | TIP ID ASSIGN SIR {DeclarareObiect($1, $2); AtribuireValoareString($2, $4); }
           | TIP ID ASSIGN LIT {DeclarareObiect($1, $2); AtribuireValoareChar($2, $4);}
           | TIP ID ASSIGN BOOLvaloare {DeclarareObiect($1, $2); AtribuireValoareBool($2, $4);}
           | TIP ID ASSIGN expresie {DeclarareObiect($1, $2); AtribuireValoare($2, $4);}
           | TIP ID '(' lista_param ')' {DeclarareFunctie($1, $2, yylineno);}
           | TIP ID '(' lista_param ')' BGIN list END {DeclarareFunctie($1, $2, yylineno);}
           | TIP ID '(' ')' {DeclarareFunctie($1, $2, yylineno);}
           | TIP ID '(' ')' BGIN list END {DeclarareFunctie($1, $2, yylineno);}
           | ID ID {DeclarareVarClasa($1, $2);}
           | CONST TIP const_list  {DeclarareObiecte($2);}
           | CLASA ID BGIN declaratii_clasa END {DeclarareClasa($2);}
           ;

lista_param : param
            | lista_param ','  param 
            ;
param : TIP ID {add_para($1, $2);}
      ; 

list_ID : ID ',' ID {add_to_list($1); add_to_list($3);}
          | ID ',' array_name  {add_to_list($1); add_to_list($3);}
          | list_ID ',' ID {add_to_list($3);}
          | list_ID ',' array_name {add_to_list($3);}
          | array_name {add_to_list($1);}
          ;
const_list : const_list ',' ID '=' NR {add_to_list($3);}
          | ID '=' NR {add_to_list($1);}
          ;
array_name : ID PARANTEZAPD NR PARANTEZAPI {
     char * s=strdup($1);
     strcat(s, "[");
     strcat(s, $3);
     strcat(s, "]");
     $$=s;
}
          ;
      
/* bloc */
bloc : MAIN BGIN list END  
     ;
     
/* lista instructiuni */
list :  statement ';' 
     | list statement ';'
     ;
/* instructiune */
statement : array_name ASSIGN TYPEOF '(' type_atribut ')'  {
               if(!strcmp(typeoff($1), "string")){
                    AtribuireValoareString($1, (typeoff($5)));
                    PrintInFile();
                    }
               } 
          | ID ASSIGN TYPEOF '(' type_atribut ')'  {
               if(!strcmp(typeoff($1), "string")){
                    AtribuireValoareString($1, (typeoff($5)));
                    PrintInFile();
                    }
               } 

          | array_name ASSIGN expresie {AtribuireValoare($1, $3);}
          | ID ASSIGN expresie  {AtribuireValoare($1, $3);} 
          | class_obj ASSIGN expresie  {AtribuireValoare($1, $3);} 

          | array_name ASSIGN LIT {AtribuireValoareChar($1, $3);}
          | ID ASSIGN LIT  {AtribuireValoareChar($1, $3);} 
          | class_obj ASSIGN LIT  {AtribuireValoareChar($1, $3);} 

          | array_name ASSIGN SIR  {AtribuireValoareString($1, $3);} 
          | ID ASSIGN SIR  {AtribuireValoareString($1, $3);} 
          | class_obj ASSIGN SIR  {AtribuireValoareString($1, $3);} 

          | array_name ASSIGN BOOLvaloare  {AtribuireValoareBool($1, $3);} 
          | ID ASSIGN BOOLvaloare  {AtribuireValoareBool($1, $3);} 

          | ID {dump_list();}'(' lista_apel ')'  {Verificare_Paremtrii($1);} 
          | IF '(' boolean_expr ')' BGIN list END
          | WHILE '(' boolean_expr ')' BGIN list END
          | FOR '(' ID ASSIGN NR ';' boolean_expr ';' ID INCdec ')' BGIN list END
          | RETURN expresie
          ;
class_obj : ID '.' ID {
     char * s=strdup($1);
     strcat(s, ".");
     strcat(s, $3);
     $$=s;
}
          | ID '.' array_name {
     char * s=strdup($1);
     strcat(s, ".");
     strcat(s, $3);
     $$=s;
}

type_atribut :   expresie {$$=strdup($1->val);}
               | LIT
               | SIR
               | BOOLvaloare
               ;
boolean_expr : boolean_term
             | boolean_expr BOOLOR boolean_term
             | expresie {$$=strdup($1->val);}
             ;

boolean_term : boolean_factor
             | boolean_term BOOLAND boolean_factor
             ;

boolean_factor : PARANTEZAPD boolean_expr PARANTEZAPI
               | expresie BOOLCOMP expresie {$$=strdup("false");}
               | BOOLNOT PARANTEZAPD boolean_expr PARANTEZAPI
               ;
                  ;
expresie : expresie PLUS expresie {$$=buildARB($1, $3, "operator", "+");}
          | '-' NR {char s[100]; strcpy(s, "-"); strcat(s, $2); $$=buildARB(NULL, NULL, "int", s);}
          | expresie MINUS expresie {$$=buildARB($1, $3, "operator", "-");}
          | expresie INMULTIRE expresie {$$=buildARB($1, $3, "operator", "*");}
          | expresie IMPARTIRE expresie {$$=buildARB($1, $3, "operator", "/");}
          | ID {$$=buildARB(NULL, NULL, typeoff($1), $1);}
          | EVAL '(' expresie ')'  {$$=$3;}
          | class_obj {$$=buildARB(NULL, NULL, typeoff($1), $1);}
          | ID '(' lista_apel ')' { Verificare_Paremtrii($1); $$=buildARB(NULL, NULL, typeoff($1), $1);}
          | ID '(' ')' {dump_list(); Verificare_Paremtrii($1); $$=buildARB(NULL, NULL, typeoff($1), $1);}
          | NR {char * aux; aux=strdup("int"); $$=buildARB(NULL, NULL, aux, $1);}
          | FRAC {$$=buildARB(NULL, NULL, "float", $1);}
          | array_name {$$=buildARB(NULL, NULL, typeoff($1), $1);}
          | '(' expresie ')'  {$$=$2;}
          ;

lista_apel : expresie {add_to_list($1->val);}
           | lista_apel ',' expresie {add_to_list($3->val);}
           ;
%%
int yyerror(char * s){
printf("eroare: %s la linia:%d\n",s,yylineno);
}

int main(int argc, char** argv){
yyin=fopen(argv[1],"r");
yyparse();
} 