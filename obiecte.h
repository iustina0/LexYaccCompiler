#pragma once

#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include<math.h>
#include<string.h>
#include <stdbool.h>
#include "arbore.h"


int yyerror(char * s);
int yylex();

void Verificare_Paremtrii(char *);
void dump_list(void);
void PrintInFile(void);
void PrintFunctii(void);
void DeclarareObiect(char *, char *);
int CautareInTabel(char *);
int CautareInFunctii(char *);
int CautareInClase(char *);
int yyerror(char * s);
int yylex();
void add_metode();
void dump_metode();
void DeclarareObiecte(char *);
void DeclarareFunctie(char *, char *, int);
void add_to_list(char *);
char * typeoff(char *);
void AtribuireValoareChar(char *, char *);
void AtribuireValoareString(char *, char *);
void add_para(char *, char *);
nod buildARB(nod, nod, char*, char*);




typedef struct Valoare{
    int nr;
    float frac;
    char lit;
    char sir[1000];
    bool bin;

}val;

typedef struct lista_char{
    char* i;
    int count;
}lista_char;

typedef struct parametrii{
    char * id;
    char * tip;
    int count;
}parametrii;

typedef struct obiect{
    char * id;
    char * type;
    val valoare;
    bool atribuit;
    bool array;
    int size;
}obiect;

typedef struct functii{
    char * type;
    char * id;
    parametrii parametrii[100]; //int a, bool b...
    int linia;
}functie;

typedef struct function_table{
    functie Functii[100];
    int count;
}function_table;

typedef struct clasa{
    char * id;
    parametrii para[100];
    function_table metode;
    int count;
}clasa;

typedef struct symbol_table{
    obiect Variabile[100];
    int count;
}symbol_table;

typedef struct  arrayObj{
    char * type;
    int index;
    char * value;
    bool atribuit;
}arrayObj;



nod radacina;
clasa Tabel_clase[100]; //tabelul de clasa
lista_char lista_obiecte[100];  //lista temp pt siruri de char
function_table Tabel_Functii;   //functiile declareate
symbol_table Tabel_Simboluri;  //variabilele declarate
parametrii lista_para[100]; //lista temp pt parametrii functiilor
parametrii lista_class[100];   //lista temp pt parametrii functiilor din clase
function_table lista_metode; //lista de metode din clasa


nod buildARB(nod right, nod left,  char * t, char * val){
    nod nod;
    char test[100];
    nod=(nods*)malloc(1000);
    nod->right=(nods*)malloc(sizeof(nod));
    nod->left=(nods*)malloc(sizeof(nod));
    nod->left=left;
    nod->right=right;
    nod->val[0]='\0';
    nod->tip[0]='\0';
    strcpy(nod->val, val);
    strcpy(nod->tip, t);
    nod->tip[strlen(nod->tip)+1]='\0';
    return nod;
}

char * evalNOD(nod node)
{
    if(node==NULL)
    {
        return "";
    }
    char eroare[100];
    char * rez;
    rez=(char*)malloc(100);
    char r[100];
    nod n=node;
    int index=CautareInFunctii(n->val);
    if(index!=-1)
    {
        if(!strcmp(n->tip, "int"))
        {
            sprintf(rez, "%d", 0);
            return rez;
        }
        if(!strcmp(n->tip, "float"))
        {
            sprintf(rez, "%f", 0.0);
            return rez;
        }
        if(!strcmp(n->tip, "bool"))
        {
            sprintf(rez, "%d", 0);
            return rez;
        }
        if(!strcmp(n->tip, "string"))
        {
            sprintf(rez, " ");
            return rez;
        }
        if(!strcmp(n->tip, "char"))
        {
            sprintf(rez, " ");
            return rez;
        }
    }
    if(!strcmp(n->tip, "int")||!strcmp(n->tip, "float")||!strcmp(n->tip, "bool")||!strcmp(n->tip, "string")||!strcmp(n->tip, "char"))
    {
        index=CautareInTabel(n->val);
        if(index!=-1)
        {
            if(Tabel_Simboluri.Variabile[index].atribuit==0)
            {
                sprintf(eroare, "Eroare operatie: Variabila %s nu este definita", Tabel_Simboluri.Variabile[index].id);
                yyerror(eroare);
                exit(0);
            }
            if(!strcmp(Tabel_Simboluri.Variabile[index].type, "int")){
                sprintf(rez, "%d", Tabel_Simboluri.Variabile[index].valoare.nr);
                return rez;
            }
            if(!strcmp(Tabel_Simboluri.Variabile[index].type, "float")){
                sprintf(rez, "%f", Tabel_Simboluri.Variabile[index].valoare.frac);
                return rez;
            }
            if(!strcmp(Tabel_Simboluri.Variabile[index].type, "bool")){
                sprintf(rez, "%d", Tabel_Simboluri.Variabile[index].valoare.bin);
                return rez;
            }
            if(!strcmp(Tabel_Simboluri.Variabile[index].type, "string")){
                sprintf(rez, "%s", Tabel_Simboluri.Variabile[index].valoare.sir);
                return rez;
            }
            if(!strcmp(Tabel_Simboluri.Variabile[index].type, "char")){
                sprintf(rez, "%c", Tabel_Simboluri.Variabile[index].valoare.lit);
                return rez;
            }
        }
        return n->val;
    }
    if(!strcmp(n->tip, "operator")){

        if(!strcmp(n->left->tip, "operator"))
        {
            nod st, s;
            s=n->left;
            st=(nods*)malloc(sizeof(nod));
            strcpy(st->val,evalNOD(s));
            strcpy(st->tip,typeoff(st->val));
            st->left=NULL;
            st->right=NULL;
            n->left=st;
        }

        if(!strcmp(n->right->tip, "operator"))
        {
            nod dr;
            dr=(nods*)malloc(sizeof(nod));
            strcpy(dr->val,evalNOD(n->right));
            strcpy(dr->tip,typeoff(dr->val));
            dr->right=NULL;
            dr->left=NULL;
            n->right=dr;
        }

        if(strcmp(n->right->tip, n->left->tip))
        {
            sprintf(eroare, "Eroare operatie: operatorii nu au acelasi tip");
            yyerror(eroare);
            exit(0);
        }
        if(!strcmp(n->right->tip, "int"))
        {  
            int a;
            if (strcmp(n->val, "+") == 0) {
                a=atoi(evalNOD(n->right))+atoi(evalNOD(n->left));
                sprintf(rez, "%d", a);
                return rez;
            } else if (strcmp(n->val, "-") == 0) {
                a=atoi(evalNOD(n->right))-atoi(evalNOD(n->left));
                sprintf(rez, "%d", a);
                return rez;
            } else if (strcmp(n->val, "*") == 0) {
                a=atoi(evalNOD(n->right))*atoi(evalNOD(n->left));
                sprintf(rez, "%d", a);
                return rez;
            } else if (strcmp(n->val, "/") == 0) {
                a=atoi(evalNOD(n->right))/atoi(evalNOD(n->left));
                sprintf(rez, "%d", a);
                return rez;
            }
        }
        if(!strcmp(n->right->tip, "float"))
        {  
            float a;
            if (strcmp(n->val, "+") == 0) {
                a=atof(evalNOD(n->right))+atof(evalNOD(n->left));
                sprintf(rez, "%f", a);
                return rez;
            } else if (strcmp(n->val, "-") == 0) {
                a=atof(evalNOD(n->right))-atof(evalNOD(n->left));
                sprintf(rez, "%f", a);
                return rez;
            } else if (strcmp(n->val, "*") == 0) {
                a=atof(evalNOD(n->right))*atof(evalNOD(n->left));
                sprintf(rez, "%f", a);
                return rez;
            } else if (strcmp(n->val, "/") == 0) {
                a=atof(evalNOD(n->right))/atof(evalNOD(n->left));
                sprintf(rez, "%f", a);
                return rez;
            }
        }
        sprintf(eroare, "Eroare operatie: nu se poate operatiia cu variabilele date");
        yyerror(eroare);
        exit(0);
    }

}

void add_para_class(char * tip, char * id){
    lista_class[0].count++;
    size_t len=strlen(tip);
    lista_class[lista_class[0].count].tip=(char*)malloc(len*sizeof(char));
    strcpy(lista_class[lista_class[0].count].tip, tip);

    len=strlen(id);
    lista_class[lista_class[0].count].id=(char*)malloc(len*sizeof(char));
    strcpy(lista_class[lista_class[0].count].id, id);
    return;
}

void dump_para_class()
{
    lista_class[0].count=0;
}

void dump_para(){
    lista_para[0].count=0;
}

void add_para(char * tip, char * id){
    lista_para[0].count++;
    size_t len=strlen(tip);
    lista_para[lista_para[0].count].tip=(char*)malloc(len*sizeof(char));
    strcpy(lista_para[lista_para[0].count].tip, tip);

    len=strlen(id);
    lista_para[lista_para[0].count].id=(char*)malloc(len*sizeof(char));
    strcpy(lista_para[lista_para[0].count].id, id);
    return;
}

void dump_list(){
    lista_obiecte[0].count=0;
}

void add_to_list(char* sir){
    
    lista_obiecte[0].count++;
    size_t len=strlen(sir);
    lista_obiecte[lista_obiecte[0].count].i=(char*)malloc(len*sizeof(char));
    strcpy(lista_obiecte[lista_obiecte[0].count].i, sir);
    return;
}

void add_metode(char * tip, char * id)
{
    lista_metode.count++;
    size_t len=strlen(tip);
    lista_metode.Functii[lista_metode.count].type=(char*)malloc(len*sizeof(char));
    strcpy(lista_metode.Functii[lista_metode.count].type, tip);

    len=strlen(id);
    lista_metode.Functii[lista_metode.count].id=(char*)malloc(len*sizeof(char));
    strcpy(lista_metode.Functii[lista_metode.count].id, id);

    for(int i=0; i<=lista_para[0].count;i++)
    {
        lista_metode.Functii[lista_metode.count].parametrii[i]=lista_para[i];
    }
    dump_para();
    return;
}

void dump_metode(){
    lista_metode.count=0;
}

int CautareInTabel(char * id)
{
    for(int i=1;i<=Tabel_Simboluri.count;i++){
        if(!strcmp(id, Tabel_Simboluri.Variabile[i].id))
        {
            return i;
        }
    }
    return -1;
}

int CautareInClase(char * id)
{
    for(int i=1;i<=Tabel_clase[0].count;i++){
        if(!strcmp(id, Tabel_clase[i].id))
        {
            return i;
        }
    }
    return -1;
}

int CautareInFunctii(char * id)
{
    for(int i=1;i<=Tabel_Functii.count;i++){
        if(!strcmp(id, Tabel_Functii.Functii[i].id))
        {
            return i;
        }
    }
    return -1;
}

void DeclarareFunctie(char * tip, char * id, int linie)
{
    char eroare[100];
    size_t len;
    if(CautareInTabel(id)!=-1)
    {
        sprintf(eroare, "Eroare declaratie: id-ul deja declarat ca variabila");
        yyerror(eroare);
        exit(0);
        return;
    }
    if(CautareInClase(id)!=-1)
    {
        sprintf(eroare, "Eroare declaratie: id-ul deja declarat ca clasa");
        yyerror(eroare);
        exit(0);
        return;
    }
    if(CautareInFunctii(id)!=-1)
    {
        sprintf(eroare, "Eroare declaratie: id-ul deja declarat ca functie");
        yyerror(eroare);
        exit(0);
        return;
    }
    if(!strcmp(tip, "int")||!strcmp(tip, "float")||!strcmp(tip, "char")||!strcmp(tip, "string")||!strcmp(tip, "bool")){
        functie fun;  
        len=strlen(id);
        fun.id=(char*)malloc(len*sizeof(char));
        strcpy(fun.id, id);
        
        len=strlen(tip);
        fun.type=(char*)malloc(len*sizeof(char));
        strcpy(fun.type, tip);

        for(int i=0; i<=lista_para[0].count;i++)
        {
            fun.parametrii[i]=lista_para[i];
        }
        fun.linia=linie;

        Tabel_Functii.count++;
        Tabel_Functii.Functii[Tabel_Functii.count]=fun;
        PrintFunctii();
        dump_para();
        return;
        }
    else{
        strcpy(eroare, "Tipul nu este recunoscut");
        yyerror(eroare);
        exit(0);
        return;
    }
}

char * typeoff(char * expr)
{
    char eroare[100];
    char * tip;
    tip=(char *)malloc(10);
    int index=CautareInTabel(expr);
    if(index!=-1)
    {
        strcpy(tip, Tabel_Simboluri.Variabile[index].type);
        return tip;
    }
    index=CautareInFunctii(expr);
    if(index!=-1)
    {
        strcpy(tip, Tabel_Functii.Functii[index].type);
        return tip;
    }

    char aux[50];
    strcpy(aux, expr);
    if(strchr(aux, '('))
    {
        char *p = strtok(aux, "(");
        strcpy(expr, p);
        index = CautareInFunctii(expr);
        if(index!=-1)
        {
            strcpy(tip, Tabel_Functii.Functii[index].type);
            return tip;
        }
    }

    if(strlen(expr)==3 && expr[strlen(expr)-1]=='\''&&expr[0]=='\'')
    {
        strcpy(tip, "char");
        return tip;
    }
    if(!strcmp(expr, "true")||!strcmp(expr, "TRUE")||!strcmp(expr, "false")||!strcmp(expr, "FALSE"))
    {
        strcpy(tip, "bool");
        return tip;
    }
    if(expr[strlen(expr)-1]=='\"'&&expr[0]=='\"')
    {
        strcpy(tip, "string");
        return tip;
    }
    bool ok_int=1, ok_float=1;
    bool dot=0;
    bool neg=0;
    int k=0;
    if(expr[0]=='-')
    {
        neg=1;
        k=1;
    }
    for(int i=k;i<strlen(expr);i++){
        if(!strchr("1234567890", expr[i]))
        {
            if(expr[i]=='.')
            {
                ok_int=0;
                if(dot==0)
                {
                    dot=1;
                }
                else{
                    ok_float=0;
                    sprintf(eroare, "Eroare in functia typeof: variabila %s nu este corecta sintactic", expr);
                    yyerror(eroare);
                    exit(0);
                    return "";
                }
            }
            else{
                ok_int=0;
                ok_float=0;
            }
        }
    }
    if(ok_int){
        strcpy(tip, "int");
        return tip;
    }
    if(ok_float)
    {
        strcpy(tip, "float");
        return tip;
    }
    sprintf(eroare, "Eroare in functia typeof: variabila %s nu este corecta sintactic", expr);
    yyerror(eroare);
    strcpy(tip, "");
    exit(0);
    return tip;
}

void DeclarareClasa(char * id){
    char eroare[100];
    size_t len;
    if(CautareInTabel(id)!=-1)
    {
        sprintf(eroare, "Eroare declaratie: id-ul deja declarat ca variabila");
        yyerror(eroare);
        exit(0);
        return;
    }
    if(CautareInClase(id)!=-1)
    {
        sprintf(eroare, "Eroare declaratie: id-ul deja declarat ca clasa");
        yyerror(eroare);
        exit(0);
        return;
    }
    if(CautareInFunctii(id)!=-1)
    {
        sprintf(eroare, "Eroare declaratie: id-ul deja declarat ca functie");
        yyerror(eroare);
        exit(0);
        return;
    }
    Tabel_clase[0].count++;
    clasa c;
    len=strlen(id);
    c.id=(char*)malloc(len*sizeof(char));
    strcpy(c.id, id);

    for(int i=0; i<=lista_class[0].count;i++)
    {
        c.para[i]=lista_class[i];
    }
    dump_para_class();
    c.metode=lista_metode;
    dump_metode();

    Tabel_clase[Tabel_clase[0].count]=c;
    return;
}

void DeclarareObiecte(char * tip)
{
    for(int i=1;i<=lista_obiecte[0].count;i++)
    {
        DeclarareObiect(tip, lista_obiecte[i].i);
    }
    dump_list();
}

void DeclarareObiect(char * tip, char * nume_variabila)
{
    char eroare[1000];
    size_t len;
    if(CautareInTabel(nume_variabila)!=-1)
    {
        sprintf(eroare, "Eroare declaratie: id-ul deja declarat ca variabila");
        yyerror(eroare);
        exit(0);
        return;
    }
    if(CautareInClase(nume_variabila)!=-1)
    {
        sprintf(eroare, "Eroare declaratie: id-ul deja declarat ca clasa");
        yyerror(eroare);
        exit(0);
        return;
    }
    if(CautareInFunctii(nume_variabila)!=-1)
    {
        sprintf(eroare, "Eroare declaratie: id-ul deja declarat ca functie");
        yyerror(eroare);
        exit(0);
        return;
    }
    obiect obj;
    if( !strcmp(tip,"int")||!strcmp(tip,"float")||!strcmp(tip,"char")||!strcmp(tip,"string")||!strcmp(tip,"bool" ))
    {
        if(strchr(nume_variabila, '[')&&strchr(nume_variabila, ']'))
        {
            char * nume;
            len=strlen(nume_variabila);
            nume=(char*)malloc(len*sizeof(char));
            strcpy(nume, nume_variabila);

            char * nr=strchr(nume_variabila, '[');   //nr=[NR]
            nume[strlen(nume)-strlen(nr)]='\0';
            strcpy(nr, nr+1);
            nr[strlen(nr)-1]='\0';
            int size = atoi(nr);
            
            len=strlen(nume);
            obj.id=(char*)malloc(len*sizeof(char));
            strcpy(obj.id, nume);

            obj.type=(char*)malloc(100);
            strcpy(obj.type, tip);
            strcat(obj.type, " array");

            obj.atribuit=0;
            obj.array=1;
            obj.size=size;
            Tabel_Simboluri.count++;
            Tabel_Simboluri.Variabile[Tabel_Simboluri.count]=obj;

            for(int i=0; i<size;i++){
                
                char n[100];
                snprintf(n, sizeof n, "%s[%d]", nume, i);
                len=strlen(n);
                obj.id=(char*)malloc(len*sizeof(char));
                strcpy(obj.id, n);

                len = strlen(tip);
                obj.type=(char*)malloc(len * sizeof(char));
                strcpy(obj.type, tip);

                obj.atribuit=0;
                obj.array=0;
                obj.size=0;
                obj.valoare.bin=0;
                obj.valoare.frac=0;
                obj.valoare.lit='\0';
                obj.valoare.nr=0;
                strcpy(obj.valoare.sir, "");
                Tabel_Simboluri.count++;
                Tabel_Simboluri.Variabile[Tabel_Simboluri.count]=obj;

            }
            PrintInFile();
        }
        else{

            len=strlen(nume_variabila);
            obj.id=(char*)malloc(len*sizeof(char));
            strcpy(obj.id, nume_variabila);  

            len = strlen(tip);
            obj.type=(char*)malloc(len * sizeof(char));
            strcpy(obj.type, tip);

            obj.atribuit=0;
            obj.array=0;
            obj.size=0;
            obj.valoare.bin=0;
            obj.valoare.frac=0;
            obj.valoare.lit='\0';
            obj.valoare.nr=0;
            strcpy(obj.valoare.sir, "");
            Tabel_Simboluri.count++;
            Tabel_Simboluri.Variabile[Tabel_Simboluri.count]=obj;
            PrintInFile();
        }
    }
    else{
        sprintf(eroare, "Eroare declaratie: tipul nu este definti");
        yyerror(eroare);
        exit(0);
        return;
    }
}

void DeclarareVarClasa(char * cla, char * id){
     char eroare[1000];
    size_t len;
    if(CautareInTabel(id)!=-1)
    {
        sprintf(eroare, "Eroare declaratie: id-ul deja declarat ca variabila");
        yyerror(eroare);
        exit(0);
        return;
    }
    if(CautareInClase(id)!=-1)
    {
        sprintf(eroare, "Eroare declaratie: id-ul deja declarat ca clasa");
        yyerror(eroare);
        exit(0);
        return;
    }
    if(CautareInFunctii(id)!=-1)
    {
        sprintf(eroare, "Eroare declaratie: id-ul deja declarat ca functie");
        yyerror(eroare);
        exit(0);
        return;
    }
    int index=CautareInClase(cla);
    if(index==-1)
    {
        sprintf(eroare, "Eroare declaratie: clasa %s nu este definita", cla);
        yyerror(eroare);
        exit(0);
        return;
    }
    char nume[100];
    for(int i=1; i<=Tabel_clase[index].para[0].count;i++)
    {
        sprintf(nume, "%s.%s", id, Tabel_clase[index].para[i].id);
        DeclarareObiect(Tabel_clase[index].para[i].tip, nume);
    }

    functie fun;
    char n[100];
    for(int i=1; i<=Tabel_clase[index].metode.count;i++)
    {

        fun=Tabel_clase[index].metode.Functii[i];

        strcpy(n, id);
        strcat(n, ".");
        strcat(n, fun.id);

        strcpy(fun.id, n);

        Tabel_Functii.count++;
        Tabel_Functii.Functii[Tabel_Functii.count]=fun;
        PrintFunctii();
    }

}

void PrintInFile(){
    FILE* Symb_table;
    Symb_table=fopen("simbol.txt", "w+");
    fprintf(Symb_table, "ID\t\tTIP\t\tVALOARE\n");
    for(int i=1; i<Tabel_Simboluri.count+1;i++){
        fprintf(Symb_table, "\n%s\t\t%s", Tabel_Simboluri.Variabile[i].id,Tabel_Simboluri.Variabile[i].type);
        if(!strcmp(Tabel_Simboluri.Variabile[i].type, "int"))
        {
            fprintf(Symb_table, "\t\t%d", Tabel_Simboluri.Variabile[i].valoare.nr);
        }
        if(!strcmp(Tabel_Simboluri.Variabile[i].type, "float"))
        {
            fprintf(Symb_table, "\t\t%f", Tabel_Simboluri.Variabile[i].valoare.frac);
        }
        if(!strcmp(Tabel_Simboluri.Variabile[i].type, "char"))
        {
            fprintf(Symb_table, "\t\t%c", Tabel_Simboluri.Variabile[i].valoare.lit);
        }
        if(!strcmp(Tabel_Simboluri.Variabile[i].type, "string"))
        {
            fprintf(Symb_table, "\t\t%s", Tabel_Simboluri.Variabile[i].valoare.sir);
        }
        if(!strcmp(Tabel_Simboluri.Variabile[i].type, "bool"))
        {
            fprintf(Symb_table, "\t\t%d", Tabel_Simboluri.Variabile[i].valoare.bin);
        }
    }
    fclose(Symb_table);
    
}

void PrintFunctii()
{
    FILE * funct;
    funct=fopen("functii.txt", "w+");

    fprintf(funct, "TIP\t\t\tID\t\t\tPARAMETRII\n");
    for(int i=1;i<=Tabel_Functii.count;i++)
    {
        fprintf(funct, "%s\t\t%s\t\t", Tabel_Functii.Functii[i].type, Tabel_Functii.Functii[i].id);
        for(int j=1; j<=Tabel_Functii.Functii[i].parametrii[0].count; j++)
        {
            fprintf(funct, "%s %s\t", Tabel_Functii.Functii[i].parametrii[j].id, Tabel_Functii.Functii[i].parametrii[j].tip);
        } 
        fprintf(funct, "\n");
    }
    return;

}

/* 
void AtribuireValoareInt(char * id, int atribuit)
{
    char eroare[100];
    int index_tabel=CautareInTabel(id);
    if(index_tabel==-1)
    {
        sprintf(eroare, "Variabila %s nu este declarata", id);
        yyerror(eroare);
        return;
    }
    if(strstr(Tabel_Simboluri.Variabile[index_tabel].type, "array"))
    {
        sprintf(eroare, "Variabila %s este declarata ca vector de valori", id);
        yyerror(eroare);
        return;
    }
    if(strcmp(Tabel_Simboluri.Variabile[index_tabel].type, "int"))
    {
        sprintf(eroare, "Variabila %s nu este declarata ca int", id);
        yyerror(eroare);
        return;
    }
    Tabel_Simboluri.Variabile[index_tabel].valoare.nr=atribuit;
    Tabel_Simboluri.Variabile[index_tabel].atribuit=1;
    PrintInFile();
}


void AtribuireValoareFloat(char * id, float atribuit)
{
    char eroare[100];
    int index_tabel=CautareInTabel(id);
    if(index_tabel==-1)
    {
        sprintf(eroare, "Variabila %s nu este declarata", id);
        yyerror(eroare);
        return;
    }
    if(strstr(Tabel_Simboluri.Variabile[index_tabel].type, "array"))
    {
        sprintf(eroare, "Variabila %s este declarata ca vector de valori", id);
        yyerror(eroare);
        return;
    }
    if(strcmp(Tabel_Simboluri.Variabile[index_tabel].type, "float"))
    {
        sprintf(eroare, "Variabila %s nu este declarata ca float", id);
        yyerror(eroare);
        return;;
    }
    Tabel_Simboluri.Variabile[index_tabel].valoare.frac=atribuit;
    Tabel_Simboluri.Variabile[index_tabel].atribuit=1;
    PrintInFile();
}
 */

void AtribuireValoareChar(char * id, char * atribuit)
{
    char eroare[100];
    int index_tabel=CautareInTabel(id);
    if(index_tabel==-1)
    {
        sprintf(eroare, "Variabila %s nu este declarata", id);
        yyerror(eroare);
        exit(0);
        return;
    }
    if(strstr(Tabel_Simboluri.Variabile[index_tabel].type, "array"))
    {
        sprintf(eroare, "Variabila %s este declarata ca vector de valori", id);
        yyerror(eroare);
        exit(0);
        return;
    }
    if(strcmp(Tabel_Simboluri.Variabile[index_tabel].type, "char"))
    {
        sprintf(eroare, "Variabila %s nu este declarata ca char", id);
        yyerror(eroare);
        exit(0);
        return;
    }
    Tabel_Simboluri.Variabile[index_tabel].valoare.lit=atribuit[1];
    Tabel_Simboluri.Variabile[index_tabel].atribuit=1;
    PrintInFile();
}

void AtribuireValoareString(char * id, char * atribuit)
{
    char eroare[100];
    int index_tabel=CautareInTabel(id);
    if(index_tabel==-1)
    {
        sprintf(eroare, "Variabila %s nu este declarata", id);
        yyerror(eroare);
        exit(0);
        return;
    }
    if(strstr(Tabel_Simboluri.Variabile[index_tabel].type, "array"))
    {
        sprintf(eroare, "Variabila %s este declarata ca vector de valori", id);
        yyerror(eroare);
        exit(0);
        return;
    }
    if(strcmp(Tabel_Simboluri.Variabile[index_tabel].type, "string"))
    {
        sprintf(eroare, "Variabila %s nu este declarata ca string", id);
        yyerror(eroare);
        exit(0);
        return;
    }
    strcpy(Tabel_Simboluri.Variabile[index_tabel].valoare.sir, atribuit);
    Tabel_Simboluri.Variabile[index_tabel].atribuit=1;
    PrintInFile();  
}

void AtribuireValoareBool(char * id, char * atribuit)
{
    char eroare[100];
    int index_tabel=CautareInTabel(id);
    if(index_tabel==-1)
    {
        sprintf(eroare, "Variabila %s nu este declarata", id);
        yyerror(eroare);
        exit(0);
        return;
    }
    if(strstr(Tabel_Simboluri.Variabile[index_tabel].type, "array"))
    {
        sprintf(eroare, "Variabila %s este declarata ca vector de valori", id);
        yyerror(eroare);
        exit(0);
        return;
    }
    if(strcmp(Tabel_Simboluri.Variabile[index_tabel].type, "bool"))
    {
        sprintf(eroare, "Variabila %s nu este declarata ca bool", id);
        yyerror(eroare);
        exit(0);
        return;
    }

    if(!strcmp(atribuit, "true")||!strcmp(atribuit, "TRUE"))    //verificam daca atribuirea e de tipul bool
    {
        Tabel_Simboluri.Variabile[index_tabel].valoare.bin=true;
        Tabel_Simboluri.Variabile[index_tabel].atribuit=1;
    }
    if(!strcmp(atribuit, "false")||!strcmp(atribuit, "FALSE"))   //verificam daca atribuirea e de tipul bool
    {
        Tabel_Simboluri.Variabile[index_tabel].valoare.bin=false;
        Tabel_Simboluri.Variabile[index_tabel].atribuit=1;
    }
    PrintInFile();
}

void AtribuireValoare(char * id, nod n)
{

    char eroare[1000];
    char * atribuit;
    atribuit=(char*)malloc(100);
    strcpy(atribuit, evalNOD(n));
    int index_tabel=CautareInTabel(id);
    if(index_tabel==-1)
    {
        sprintf(eroare, "Variabila %s nu este declarata", id);
        yyerror(eroare);
        exit(0);
        return;
    }
    if(strstr(Tabel_Simboluri.Variabile[index_tabel].type, "array"))
    {
        sprintf(eroare, "Variabila %s este declarata ca vector de valori de tipul %s", id, Tabel_Simboluri.Variabile[index_tabel].type);
        yyerror(eroare);
        exit(0);
        return;
    }
    if(!strcmp(Tabel_Simboluri.Variabile[index_tabel].type, "int"))
    {
        for(int i=0;i<strlen(atribuit);i++){
            if(!strchr("1234567890", atribuit[i]))
            {
                sprintf(eroare, "Eroare atribuire: variabila %s este de tipul int", id);
                yyerror(eroare);
                exit(0);
                return;
            }
        }
        Tabel_Simboluri.Variabile[index_tabel].valoare.nr=atoi(atribuit);
        Tabel_Simboluri.Variabile[index_tabel].atribuit=1;
        PrintInFile();
        return;
    }
    if(!strcmp(Tabel_Simboluri.Variabile[index_tabel].type, "float"))
    {
        bool dot=0;
        for(int i=0;i<strlen(atribuit);i++){
            if(!strchr("1234567890", atribuit[i]))
            {
                if(atribuit[i]=='.')
                {
                    if(dot==0)
                        dot=1;
                    else{
                        sprintf(eroare, "Eroare atribuire: variabila %s este de tipul float", id);
                        yyerror(eroare);
                        exit(0);
                        return;
                    }
                }
                else{
                    sprintf(eroare, "Eroare atribuire: variabila %s este de tipul float", id);
                    yyerror(eroare);
                    exit(0);
                    return;
                }
            }
        }
        Tabel_Simboluri.Variabile[index_tabel].valoare.frac=atof(atribuit);
        Tabel_Simboluri.Variabile[index_tabel].atribuit=1;
        PrintInFile();
        return;
    }
}

void Verificare_Paremtrii(char * id)
{
    char eroare[100];
    int index = CautareInFunctii(id);
    if(index == -1)
    {
        sprintf(eroare, "Eroare de apel: functia nu este declarata!");
        dump_list();
        yyerror(eroare);
        exit(0);
        return;
    }
    
    if(lista_obiecte[0].count != Tabel_Functii.Functii[index].parametrii[0].count)
    {
        sprintf(eroare, "Eroare de apel: Numarul de paramentrului nu coincide cu cel al functiei!");
        dump_list();
        yyerror(eroare);
        exit(0);
        return;
    }

    for(int i = 1; i <= lista_obiecte[0].count; i++)
    {
        char tip[100];
        strcpy(tip, typeoff(lista_obiecte[i].i));
        
        if (strcmp(tip, Tabel_Functii.Functii[index].parametrii[i].tip))
        {
            sprintf(eroare, "Eroare de apel: Tipul paramentrului nu coincide cu cel al functiei!");
            dump_list();
            yyerror(eroare);
            exit(0);
            return;
        }
    }
    dump_list();
    return;
}

