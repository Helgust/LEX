//#include "Lex.hpp"
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
  LEX_AND, LEX_BOOL, LEX_DO, LEX_ELSE, LEX_IF, LEX_FALSE, LEX_INT,LEX_STRING, /*8*/
  LEX_NOT, LEX_OR, LEX_PROGRAM, LEX_READ, LEX_THEN, LEX_TRUE, LEX_GOTO, LEX_WHILE, LEX_WRITE,LEX_BREAK, /*18*/
  LEX_FIN,       /*19*/
  LEX_SEMICOLON, LEX_COMMA, LEX_COLON, LEX_ASSIGN, LEX_LPAREN, LEX_RPAREN, LEX_EQ, LEX_LSS, /*27*/
  LEX_GTR, LEX_PLUS, LEX_MINUS, LEX_TIMES, LEX_SLASH, LEX_LEQ, LEX_NEQ, LEX_GEQ, LEX_FBRC_O, LEX_FBRC_C,LEX_DQUATES, /*38*/
  LEX_NUM,       /*39*/
  LEX_ID,        /*40*/
  POLIZ_LABEL,   /*41*/
  POLIZ_ADDRESS, /*42*/
  POLIZ_GO,      /*43*/
  POLIZ_FGO
}; 
 
/////////////////////////  Класс Lex  //////////////////////////
 
class Lex {
    type_of_lex  t_lex;
    int  v_lex;
public:
    Lex ( type_of_lex t = LEX_NULL, int v = 0): t_lex (t), v_lex (v)  { }
    type_of_lex  get_type () const { 
    	  return t_lex; 
    }
    int  get_value () const { 
    	  return v_lex; 
    }
  friend ostream & operator<< (ostream &s, Lex l);
};
 
/////////////////////  Класс Ident  ////////////////////////////
 
class Ident {
    string name;
    bool declare;
    type_of_lex type;
    bool assign;
    int value;
public:
    Ident() { 
      declare = false; 
      assign = false; 
    }
    bool operator==(const string& s) const { 
      return name == s; 
    }
    Ident(const string n) {
        name = n;
        declare = false; 
        assign = false;
    }
    string get_name () const { 
      return name; 
    }
    bool get_declare () const { 
      return declare; 
    }
    void put_declare () { 
      declare = true; 
    }
    type_of_lex get_type () const { 
      return type; 
    }
    void put_type ( type_of_lex t ) { 
      type = t; 
    }
    bool get_assign () const { 
      return assign; 
    }
    void put_assign (){ 
      assign = true; 
    }
    int  get_value () const { 
      return value; 
    }
    void put_value (int v){ 
      value = v; 
    }
};
 
//////////////////////  TID  ///////////////////////
 
vector<Ident> TID;
 
int put ( const string & buf ){
    vector<Ident>::iterator k;
 
    if ( (k = find(TID.begin(), TID.end(), buf)) != TID.end())
            return k - TID.begin();
    TID.push_back(Ident(buf));
    return TID.size() - 1;
}

//////////////////////  TOT (Table Of Text)  ///////////////////////
 
 vector<string> TOT;

 //////////////////////////////////////////////////////////////////
  

std::unordered_map <type_of_lex,const std::string> TD_map = 
{
  {LEX_AND,"and"},
  {LEX_BOOL,"bool"},
  {LEX_DO,"do"},
  {LEX_ELSE,"else"},
  {LEX_IF,"if"},
  {LEX_FALSE,"false"},
  {LEX_INT,"int"},
  {LEX_STRING,"string"},
  {LEX_NOT,"not"},
  {LEX_OR,"or"},
  {LEX_PROGRAM,"program"},
  {LEX_READ,"read"},
  {LEX_THEN,"then"},
  {LEX_TRUE,"true"},
  {LEX_GOTO,"goto"},
  {LEX_WHILE,"while"},
  {LEX_WRITE,"write"},
  {LEX_BREAK,"break"},
  {LEX_FIN,"FIN"},
  {LEX_SEMICOLON,";"},
  {LEX_COMMA,","},
  {LEX_COLON,":"},
  {LEX_ASSIGN,"="},
  {LEX_LPAREN,"("},
  {LEX_RPAREN,")"},
  {LEX_EQ,"=="},
  {LEX_LSS,"<"},
  {LEX_GTR,">"},
  {LEX_PLUS,"+"},
  {LEX_MINUS,"-"},
  {LEX_SLASH,"/"},
  {LEX_LEQ,"<="},
  {LEX_NEQ,"!="},
  {LEX_GEQ,">="},
  {LEX_FBRC_O,"{"},
  {LEX_FBRC_C,"}"},
  {LEX_DQUATES,"\""},
  {LEX_NUM,"NUM"},
  {LEX_ID,"ID"},
  {LEX_NULL,""},
};


 
/////////////////////////////////////////////////////////////////
 
class Scanner {
    FILE * fp;
    char c;
    //string buf;
    //Lex lex;
    int look ( const string&  buf, const char ** list ) {
        int i = 0;
        while (list[i]) {
            if (buf == list[i])
                return i;
            ++i;
        }
        return 0;
    }
    void gc () {
        c = fgetc (fp);
    }

    //void makeLex(type_of_lex type) { lex = Lex(type, buf); };
public:
    static const char * TW [], * TD [];
    Scanner ( const char * program ) {
        fp = fopen ( program, "r" );
    }
    Lex get_lex ();
};
 
const char *
Scanner::TW    [] = {"", "and", "bool","do", "else", "if", "false", "int","string" , "not", "or", "program",
                            "read", "then", "true","goto", "while", "write","break", NULL};
 
const char *
Scanner::TD    [] = {"@", ";", ",", ":", "=", "(", ")", "==", "<", ">", "+", "-", "*", "/", "<=", "!=", ">=","{","}","\"", NULL};
 
Lex Scanner::get_lex () {
    enum state { H, IDENT, NUMB, COM,COM1,COM2, ALE, NEQ, FBRACK,DQUATES,STRING};
    int d, j;
    string buf;
    state CS = H;
    do {
        gc();
        if(c==EOF) return Lex(LEX_NULL);
        switch(CS) {
            case H: //cout<<"Case H"<<'\n';
                    if ( c==' ' || c == '\n' || c== '\r' || c == '\t' ); //gc();
                    else if ( isalpha(c) ) {
                             buf.push_back(c);
                             //sgc();
                             CS = IDENT;
                         }
                    else if ( isdigit(c) ) {
                             d = c - '0';
                             //gc();
                             CS = NUMB;
                         } 
                    else if ( c== '{' ) {
                              //CS=FBRACK;
                              return Lex(LEX_FBRC_O);
                         }
                    else if ( c== '}' ) {
                              //CS=FBRACK;
                              return Lex(LEX_FBRC_C);
                         }
                    else if ( c== '"' ) {
                              CS=DQUATES;
                              return Lex(LEX_DQUATES);
                         }
                    else if ( c== '=' || c== '<' || c== '>' ) { 
                             buf.push_back(c);
                             CS = ALE; 
                         }
                    /* else if (c == '@')
                             return Lex(LEX_FIN); */
                    else if (c == '!') {
                             buf.push_back(c);
                             CS = NEQ;
                         }
                    else if (c == '!') {
                             buf.push_back(c);
                             CS = NEQ;
                         }
                    else if (c == '/') {
                             //buf.push_back(c);
                             CS = COM;
                         }
                    else {
                        buf.push_back(c);
                        if ( (j = look ( buf, TD)) ){
                            return Lex ( (type_of_lex)(j+(int)LEX_FIN), j );
                        }
                        else
                            throw c;
                    }
                    break;
            case IDENT: //cout<<"Case IDENT"<<" "<<c<<'\n';
                        if ( isalpha(c) || isdigit(c) ) {
                            buf.push_back(c);
                            //gc(); 
                        }
                        else {
                            ungetc (c, fp);
                            if ( (j = look (buf, TW)) ){
                                return Lex ((type_of_lex)j, j);
                             }
                             else {
                                j = put(buf);
                                return Lex (LEX_ID, j);
                             }
                        }
                        break;
            case NUMB: //cout<<"Case NUMB"<<'\n';
                        if ( isdigit(c) ) {
                           d = d * 10 + (c - '0'); 
                           //gc();
                       }
                       else {
                           ungetc (c, fp);
                           return Lex ( LEX_NUM, j);
                      }
                       break;
            case COM:   //cout<<"Case COM"<<" "<<c<<'\n';
                        if ( c == '*' ) {
                            //gc();
                            CS = COM1;
                        }
                      break;
            case COM1:   //cout<<"Case COM"<<" "<<c<<'\n';
                        if ( c == '*' ) {
                            //gc();
                            CS = COM2; // не работает коомметнраии 
                        }
                        else if (c == EOF || c == '/' )
                               throw c;
                        

                      break;
            case COM2:   //cout<<"Case COM"<<" "<<c<<'\n';
                        if ( c == '/' ) {
                            gc();
                            CS = H;
                        }
                        else if (c == '*' || c == EOF )
                                throw c;
                      break;
             case DQUATES:   //cout<<"Case COM"<<" "<<c<<'\n';
                        if ( c == '"' ) {
                            buf.push_back(c);
                            CS = STRING;
                        }
                          else
                        {
                          ungetc (c, fp);
                          buf.clear();
                          //return Lex(LEX_DQUATES) ;
                        } 
                        
                      break;
            case STRING:   //cout<<"Case COM"<<" "<<c<<'\n';
                        gc();
                        while(c!='"')
                        {
                          buf.push_back(c);
                        }

                        TOT.push_back(buf);
                        CS=H;
                        return Lex(LEX_DQUATES);
                        
                        
                      break;

            case ALE: //cout<<"Case ALE"<<'\n';
                      if ( c== '=') {
                          buf.push_back(c);
                          j = look ( buf, TD );
                          return Lex ( (type_of_lex)(j+(int)LEX_FIN), j);
                      }
                      else {
                          ungetc (c, fp);
                          j = look ( buf, TD );
                          return Lex ( (type_of_lex)(j+(int)LEX_FIN), j );
                      }
                      break;
            case NEQ: // cout<<"Case NEQ"<<'\n';
                      if (c == '=') {
                          buf.push_back(c);
                          j = look ( buf, TD );
                          return Lex ( LEX_NEQ, j );
                      }
                      else
                          throw '!';
                      break;
    }//end switch
  } while (true);
}
 
ostream & operator<< (ostream &s, Lex l){
  string t;
  std::unordered_map <type_of_lex,const std::string>::const_iterator got = TD_map.find (l.t_lex);

  if (got == TD_map.end()) 
  {
    s << '(' << l.t_lex << ',' << "not found "<< ");" << endl;
  }
  else
  {
    s << '(' << got->second << ',' << got->first << ',' << l.t_lex << ");" << endl;
  }
  
  /* if (l.t_lex <= 18)
    t = Scanner::TW[l.t_lex];
  else if (l.t_lex >= 19 && l.t_lex <= 38)
      t = Scanner::TD[l.t_lex-19];
    else if (l.t_lex == 39)
        t = "NUMB";
      else if (l.t_lex == 40)
          t = TID[l.v_lex].get_name();
        else if (l.t_lex == 41)
          t = "Label";
        else if(l.t_lex == 42)
          t = "Addr";
        else if (l.t_lex == 43)
          t = "!";
        else if (l.t_lex == 44) 
          t = "!F";
        else
          throw l; 
    s << '(' << t << ',' << << ");" << endl; */
    return s;
}




int main(int argc, char* argv[])
{
try {
        Scanner c(argv[1]);
        Lex l;
        l=c.get_lex();
        cout<<l<<'\n';
        while(true)
        {
            
            l=c.get_lex();
            cout<<l<<'\n';
            if(l.get_type()==0) break;
        }
    } 
  catch (char c) {
      cout << "unexpected symbol " << c << endl;
      return 1;
  }
  catch (Lex l) {
      cout << "unexpected lexeme" << l << endl;
      return 1;
  }
  catch ( const char *source ) {
      cout << source << endl;
      return 1;
  }
}