#include "Lex.hpp"

 
/////////////////////////  Класс Lex  //////////////////////////
 
    Lex::Lex ( type_of_lex t = LEX_NULL, int v = 0): t_lex (t), v_lex (v)  { }

    type_of_lex  Lex::get_type () const { 
    	  return t_lex; 
    }
    int  Lex::get_value () const { 
    	  return v_lex; 
    }
/*   friend ostream & operator<< (ostream &s, Lex l);
}; */
 
/////////////////////  Класс Ident  ////////////////////////////
 
    Ident::Ident() { 
      declare = false; 
      assign = false; 
    }
  
    Ident::Ident(const string n) {
        name = n;
        declare = false; 
        assign = false;
    }
    string Ident::get_name () const { 
      return name; 
    }
    bool Ident::get_declare () const { 
      return declare; 
    }
    void Ident::put_declare () { 
      declare = true; 
    }
    type_of_lex Ident::get_type () const { 
      return type; 
    }
    void Ident::put_type ( type_of_lex t ) { 
      type = t; 
    }
    bool Ident::get_assign () const { 
      return assign; 
    }
    void Ident::put_assign (){ 
      assign = true; 
    }
    int  Ident::get_value () const { 
      return value; 
    }
    void Ident::put_value (int v){ 
      value = v; 
    }

 
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
  {LEX_BOOL,"boolean"},
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
  {LEX_TEXT,"TEXT"},
  {LEX_FOR,"for"},
  {LEX_NULL,""},
};


 
////////////////////////////CLASS SCANNER/////////////////////////////////

    int Scanner::look ( const string&  buf, const char ** list ) {
        int i = 0;
        while (list[i]) {
            if (buf == list[i])
                return i;
            ++i;
        }
        return 0;
    }
    void Scanner::gc () {
        c = fgetc (fp);
    }

    Scanner::state Scanner::get_CS()
    {
      return CS;
    }
    void Scanner::set_CS(state N)
    {
      CS=N;
    }

    //void makeLex(type_of_lex type) { lex = Lex(type, buf); };
    //static const char * TW [], * TD [];
    Scanner::Scanner ( const char * program ) 
    {
        fp = fopen ( program, "r" );
    }
 

 
Lex Scanner::get_lex () {
    int d, j;
    string buf;
    do {
        gc();
        /* if(c==EOF) 
        {
          cout << "LEX_NULL Before Switch" << '\n';
          return Lex(LEX_NULL);
        } */
       // if(c=='"') return Lex(DQUATES);
        switch(CS) {
            case H: //cout<<"Case H"<<'\n';
                    if ( c==' ' || c == '\n' || c== '\r' || c == '\t' ); //gc();
                    else if ( isalpha(c) ) {
                             buf.push_back(c);
                             //CS = IDENT;
                             set_CS(IDENT);
                         }
                    else if ( isdigit(c) ) {
                             d = c - '0';
                             //gc();
                             //CS = NUMB;
                             set_CS(NUMB);
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
                              //gc();   
                              //CS=STRING;
                              set_CS(STRING);
                              //cout<< "CASE STRING" << ' '<< CS << '\n';
                              return Lex(LEX_DQUATES);
                         }
                    else if ( c== '=' || c== '<' || c== '>' ) { 
                             buf.push_back(c);
                             //CS = ALE; 
                             set_CS(ALE);
                         }
                     else if (c == EOF)
                     {
                       cout << "LEX_FIN CASE H" << '\n';
                       return Lex(LEX_FIN);
                      }

                              
                    else if (c == '!') {
                             buf.push_back(c);
                             //CS = NEQ;
                             set_CS(NEQ);
                         }
                    else if (c == '/') {
                             //buf.push_back(c);
                             //CS = COM;
                             set_CS(COM);
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
                              set_CS(H);
                                return Lex ((type_of_lex)j, j);
                             }
                             else {
                                j = put(buf);
                                set_CS(H);
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
                           set_CS(H);
                           return Lex ( LEX_NUM, d);
                      }
                       break;
            case COM:   //cout<<"Case COM"<<" "<<c<<'\n';
                        if ( c == '*' ) {
                            //gc();
                            //CS = COM1;
                            set_CS(COM1);
                        }
                      break;
            case COM1:   //cout<<"Case COM"<<" "<<c<<'\n';
                        if ( c == '*' ) {
                            //gc();
                            //CS = COM2;
                            set_CS(COM2); 
                        }
                        else if (c == EOF || c == '/' )
                        {
                           cout << "LEX_FIN CASE COM1" << '\n';
                          throw c;
                        }

                               
                        

                      break;
            case COM2:   //cout<<"Case COM"<<" "<<c<<'\n';
                        if ( c == '/' ) {
                            gc();
                            // CS = H;
                            set_CS(H);
                        }
                        else if (c == '*' || c == EOF )
                        {
                           cout << "LEX_FIN CASE COM2" << '\n';
                          throw c;
                        }
                                
                      break;
               case DQUATES:   //cout<<"Case COM"<<" "<<c<<'\n';
                        if ( c == '"' ) {
                           cout << "CASE DQUATES True" << '\n';
                            //buf.push_back(c);
                            set_CS(H);
                            return Lex(LEX_DQUATES) ;
                        }
                          else
                        {
                          cout << "CASE DQUATES False" << '\n';
                           //cout << "LEX_FIN CASE DQUATES2" << '\n';
                          //set_CS(H);
                          //ungetc(c,fp);
                          throw c;
                        } 
                        
                      break;  
            case STRING:   
                       //cout<<"CHECK"<<'\n';
                        if(c!='"')
                        {
                          cout << " CASE String True" << '\n';
                          if (c==EOF) 
                                    {
                                      cout << " CASE String  EOF True" << '\n';
                                      throw c;
                                    }
                                    
                          else
                          {
                           cout << " CASE String  EOF False" << '\n'; 
                            buf.push_back(c);
                          }

                        }
                        else
                        {
                          cout << " CASE String False" << '\n';
                           //cout << c << '\n';
                            ungetc(c,fp); 
                            TOT.push_back(buf);
                            set_CS(DQUATES);
                            return Lex(LEX_TEXT); 
                        }

                        
                      break;

            case ALE: //cout<<"Case ALE"<<'\n';
                      if ( c== '=') {
                          buf.push_back(c);
                          j = look ( buf, TD );
                          set_CS(H);
                          return Lex ( (type_of_lex)(j+(int)LEX_FIN), j);
                      }
                      else {
                          ungetc (c, fp);
                          j = look ( buf, TD );
                          set_CS(H);
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
                          throw c;
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
    s << '(' << got->second << ',' << got->first << ',' << l.v_lex << ");" << endl;
  }
    return s;
}


/////////////////////////////////////////////////////////////

///////////////////////////  Класс Parser  /////////////////////////////////
 
class Parser {
    Lex          curr_lex;
    type_of_lex  c_type;
    int          c_val;
    Scanner      scan;
    stack < int >   st_int;
    stack < type_of_lex >  st_lex;
    void  P();
    void  D1();
    void  D();
    void  B();
    void  S();
    void  E();
    void  E1();
    void  T();
    void  F();
    void  dec ( type_of_lex type);
    void  check_id ();
    void  check_op ();
    void  check_not ();
    void  eq_type ();
    void  eq_bool ();
    void  check_id_in_read ();
    void  gl () {
              curr_lex = scan.get_lex();
              c_type = curr_lex.get_type();
              c_val = curr_lex.get_value();
    }
public:
    vector <Lex> poliz;
    Parser (const char *program ) : scan (program) { }
    void  analyze();
};







int main(int argc, char* argv[])
{
  vector<string>::iterator vs;
try {
        Scanner c(argv[1]);
        Lex l;
        l=c.get_lex();
        cout<<l<<'\n';
        while(true)
        {
            
            l=c.get_lex();
            cout<<l<<'\n';
            if(l.get_type()==LEX_FIN) 
            {
              
              break;
            }
        }

        cout<<"TOT"<<'\n';
        vs=TOT.begin();
        while(vs!=TOT.end())
        {
          cout<<*vs<<'\n';
          vs++;
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