#pragma once
#include <iostream>
#include <string>
#include <cstdio>
#include <ctype.h>
#include <cstdlib>
#include <vector>
#include <stack>
#include <algorithm>
#include <unordered_map>
 
using namespace std;
 
enum type_of_lex {
  LEX_NULL,      /*0*/
  LEX_AND, LEX_BOOL, LEX_ELSE, LEX_IF, LEX_FALSE, LEX_INT,LEX_STRING,LEX_TAG, /*8*/
  LEX_NOT, LEX_OR, LEX_PROGRAM, LEX_READ, LEX_THEN, LEX_TRUE, LEX_GOTO, LEX_WHILE, LEX_WRITE,LEX_BREAK,LEX_TEXT,LEX_FOR,LEX_STRUCT, /*18*/
  LEX_FIN,       /*19*/
  LEX_SEMICOLON, LEX_COMMA, LEX_COLON, LEX_ASSIGN, LEX_LPAREN, LEX_RPAREN, LEX_EQ, LEX_LSS, /*27*/
  LEX_GTR, LEX_PLUS, LEX_MINUS, LEX_TIMES, LEX_SLASH, LEX_LEQ, LEX_NEQ, LEX_GEQ, LEX_FBRC_O, LEX_FBRC_C,LEX_DQUATES,LEX_UMINUS, /*38*/
  LEX_NUM,       /*39*/
  LEX_ID,        /*40*/
  POLIZ_LABEL,   /*41*/
  POLIZ_ADDRESS, /*42*/
  POLIZ_GO,      /*43*/
  POLIZ_FGO
};  

class Lex {
    type_of_lex  t_lex;
    int  v_lex;
public:
    Lex ( type_of_lex, int);
    type_of_lex  get_type () const;
    int  get_value () const;
  friend ostream & operator<< (ostream &s, Lex l);
};

class Ident {
    string name;
    bool declare;
    type_of_lex type;
    bool assign;
    int value;
public:
    Ident();
    bool operator==(const string& s) const { 
      return name == s;  //это лучше всего засунуть в cpp но пока не знаю как
    }
    Ident(const string);
    string get_name () const;
    bool get_declare () const;
    void put_declare ();
    type_of_lex get_type () const;
    void put_type ( type_of_lex t );
    bool get_assign () const ;
    void put_assign ();
    int  get_value () const ;
    void put_value (int v);
};

class Scanner 
{
private:
	FILE * fp;
    char c;
    enum state { H, IDENT, NUMB, COM,COM1,COM2, ALE, NEQ, FBRACK,DQUATES,STRING};
    state CS=H;
    int look ( const string& , const char **);
    void gc ();
    state get_CS();
    void set_CS(state);
	//void clear();
	//void add();
public:
    static const  char * TW[] , * TD [];
    Scanner ( const char * program ); 
    Lex get_lex ();
};

const char *
Scanner::TW    [] = {"", "and", "bool", "else", "if", "false", "int","string" ,"TAG", "not", "or", "program",
                            "read", "then", "true","goto", "while", "write","break","TEXT","for","struct", NULL};
 
const char *
Scanner::TD    [] = {"", ";", ",", ":", "=", "(", ")", "==", "<", ">", "+", "-", "*", "/", "<=", "!=", ">=","{","}","\"", NULL};