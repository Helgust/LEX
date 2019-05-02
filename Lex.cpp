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
  {LEX_STRUCT,"struct"},
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
                           //cout << "LEX_FIN CASE COM1" << '\n';
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
                           //cout << "LEX_FIN CASE COM2" << '\n';
                          throw c;
                        }
                                
                      break;
               case DQUATES:   //cout<<"Case COM"<<" "<<c<<'\n';
                        if ( c == '"' ) {
                           //cout << "CASE DQUATES True" << '\n';
                            //buf.push_back(c);
                            set_CS(H);
                            return Lex(LEX_DQUATES) ;
                        }
                          else
                        {
                          //cout << "CASE DQUATES False" << '\n';
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
                          //cout << " CASE String True" << '\n';
                          if (c==EOF) 
                                    {
                                      //cout << " CASE String  EOF True" << '\n';
                                      throw c;
                                    }
                                    
                          else
                          {
                           //cout << " CASE String  EOF False" << '\n'; 
                            buf.push_back(c);
                          }

                        }
                        else
                        {
                          //cout << " CASE String False" << '\n';
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
    void  S1();
    void  E();
    void  E1();
    void  E2();
    void  T();
    void  F();
    void  Z();
    void STRUCT();
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

void Parser::analyze () {
    gl();
    P();
    if (c_type != LEX_FIN)
        throw curr_lex;
    //for_each( poliz.begin(), poliz.end(), [](Lex l){ cout << l; });
      /* for (Lex l : poliz) 
          cout << l; */
    cout << endl << "Yes!!!" << endl;
}

void Parser::P () { // Программа
    if (c_type == LEX_PROGRAM){
        gl();
    }
    else 
        throw curr_lex;      
    if (c_type == LEX_FBRC_O)
        gl();
    else
        throw curr_lex;
    D();
    S();
    cout << "P:: CHECK1" << '\n';
    if(c_type== LEX_FBRC_C) 
    {
    cout << "P:: CHECK2" << '\n';
       gl();// что здесь писать в случае правды?
    }
    else
    {
        cout << "P:: CHECK3" << '\n';
        throw curr_lex;
    }
    
   
    
    

}

void Parser::D () { //описаниЯ
//cout << "D::ENTER" << '\n';        

  D1();
 // gl();
  while (c_type == LEX_SEMICOLON) {
            gl();
            D1();
        }
  //что будет являться концом?      

}

void Parser::D1 () { // описаниЕ
//cout << "D1::ENTER" << '\n';  
    if (c_type == LEX_INT || c_type == LEX_BOOL || c_type == LEX_STRING) {
        //dec ( LEX_INT );
        gl();
        if (c_type != LEX_ID) throw curr_lex;
        else {
            gl();
            Z();
            while (c_type == LEX_COMMA) {
                gl();
                if (c_type != LEX_ID)
                     throw curr_lex;
                else {
                gl();
                Z();
                }
            }
        }
    }

    if(c_type==LEX_STRUCT)
    {
        cout<<"D1::ENTER LEX_STRUCT"<<'\n';
        gl();
        STRUCT();
    }         
}

void Parser::Z(){
    if(c_type==LEX_ASSIGN)
    {
        gl();
        E();
    }    
}

void Parser::S () { //ОператорЫ
cout << "S::ENTER"<<'\n';
  S1();
 // gl();
 cout << "S::AFTER S1" << '\n';
  while (c_type == LEX_SEMICOLON) { //было так   while (c_type == LEX_SEMICOLON) {
            gl();
            S1();
        }
    cout << "S::AFTER WHILE S1" << '\n';
    /* if(c_type== LEX_FBRC_C)
    {
        gl();
        if(c_type != LEX_ELSE)
        {
          gl();
          S1();  
        }
        
    } */
    
        
  //что будет являться концом?      

}
void Parser::S1 () { // ОператоР
         

    if (c_type == LEX_ID)
    {
        gl();
        cout << "S1::AFTER LEX_ID" << '\n';        
        if(c_type==LEX_ASSIGN)
        {
            //cout<<"S1::ENTER LEX_ASSIGN"<<'\n';

            gl();
            E();
        
            while(c_type==LEX_ASSIGN)
            {
                gl();
                E();
            }
        }
        
        else
        {
            throw curr_lex;
        }   
    }

    else if(c_type==LEX_IF)
    {
                cout<<"S1::ENTER IF"<<'\n';
            gl();
            if(c_type==LEX_LPAREN)
            {
                //cout<<"S1::ENTER LPAREN"<<'\n';
                gl();
                E();
                if(c_type==LEX_RPAREN)
                {
                    //cout<<"S1::ENTER RPAREN"<<'\n';
                    gl();
                    S1();
                    if(c_type == LEX_ELSE)
                    {
                        cout<<"S1::ENTER ELSE"<<'\n';
                        gl();
                        S1();
                    }
                    else
                    throw curr_lex;
                }
                else
                {
                    throw curr_lex;
                }
            }
            else
            {
                throw curr_lex;
            }  
    }

    else if(c_type==LEX_WHILE)
    {
        cout<<"S1::ENTER LEX_WHILE"<<'\n';
        gl();
        if(c_type==LEX_LPAREN)
        {
            gl();
            E();
            if(c_type==LEX_RPAREN)
            {
                gl();
                S1();
            }
            else
            {
                throw curr_lex;
            }
            
        }
        else
        {
            throw curr_lex;
        }
                
    }

    else if(c_type == LEX_READ)
    {
        cout << "S1::LEX_READ ENTER" << '\n';
        gl();
        if(c_type==LEX_LPAREN)
        {
            gl();
            if(c_type==LEX_ID)
            {
                gl();
                if(c_type==LEX_RPAREN)
                {
                    gl();  
                }
                else
                {
                    throw curr_lex;
                }
            }
            else
            {
                throw curr_lex;
            }
                
        }
        else
        {
            throw curr_lex;
        }
        
    }
    else if(c_type == LEX_WRITE)
    {
        cout << "S1::LEX_WRITE ENTER" << '\n';
        gl();
        if(c_type == LEX_LPAREN)
        {
            gl();
            E();
            while(c_type==LEX_COMMA)
            {
                gl();
                E();
            }
            
            if(c_type == LEX_RPAREN)
            {
                gl();
                //cout << "S1::LEX_WRITE TRUE LEX_PAREN" << '\n';
            }
            else
            {
               // cout << "S1::LEX_WRITE FALSE LEX_RPAREN" << '\n';
                throw curr_lex;
            }
            
        }
        else
        {
           //cout << "S::LEX_WRITE OUT"<<'\n';
           throw curr_lex; 
        }
        
        
    }

    

    else if (c_type == LEX_GOTO)
    {
        gl();
        if(c_type == LEX_ID)
        {
            gl();
        }
        else
        {
            throw curr_lex;
        }
        
    }

    else if(c_type == LEX_BREAK)
    {
        gl();
        /* if(c_type == LEX_SEMICOLON)
        {
            gl();

        }
        else
        {
            throw curr_lex;
        } */
        //здесь возможно должно быть что-то еще 
    }

    else if(c_type == LEX_FOR)
    {
        gl();
        if(c_type == LEX_LPAREN)
        {
            gl();
            E();
            if(c_type == LEX_SEMICOLON)
            {
                gl();
                E();
                if(c_type == LEX_SEMICOLON)
                {
                    gl();
                    E();
                    if(c_type == LEX_RPAREN)
                    {
                        gl();
                        S1();
                    }
                    else
                    {
                        throw curr_lex;
                    }
                    
                }
                else
                {
                    throw curr_lex;
                }               
            }
            else
            {
                throw curr_lex;
            }
        }
        else
        {
            throw curr_lex;
        }
    }
    else if (c_type == LEX_MINUS)//унарный минус
    {
        gl();
        E();
    }

    else if(c_type == LEX_FBRC_O)//составной оператор
    {
       cout<<"B::ENTER FBRC_O"<<'\n';
       gl();
       S();
        if (c_type == LEX_FBRC_C)
        {
            cout<<"B::ENTER FBRC_C"<<'\n';
            gl();
            S();//очень спорное решениеы FIX IT
        }
        else 
        {
            throw curr_lex;
        } 
    }
    /* else
    {
        throw curr_lex;
    } */
}

/* void Parser::B () { // Блок
    cout<<"B::ENTER"<<'\n';
    if(c_type == LEX_FBRC_O)
    {
       gl();
       S();
        if (c_type == LEX_FBRC_C)
        {
            cout<<"B::ENTER FBRC_C"<<'\n';
            gl();
        }
        else 
        {
            throw curr_lex;
        } 
    }
    else
    {
        throw curr_lex;
    }
} */

void Parser::E ()
{
    //cout<<"E::ENTER"<<'\n';
    if(c_type==LEX_DQUATES)
    {
        gl();
        if(c_type==LEX_TEXT)
        {
            gl();
            if(c_type==LEX_DQUATES)
            {
                gl();
            }
            else
            {
                throw curr_lex;
            }
        }
        else
        {
            throw curr_lex;
        } 
    }

    else
    {
        E1();
        E2();
    }
    
}

void Parser::E1()
{
    //cout<<"E1::ENTER"<<'\n';
    T();
    while(c_type==LEX_PLUS || c_type==LEX_MINUS || c_type==LEX_OR)
    {
        //cout<<"E1::TRUE"<<'\n';
        gl();
        T();
    }
    //здесь надо какой-то троу?
    
}

void Parser::E2 ()
{
    //cout<<"E2::ENTER"<<'\n';
    if ( c_type == LEX_EQ || c_type == LEX_LSS || c_type == LEX_GTR ||
       c_type == LEX_LEQ || c_type == LEX_GEQ || c_type == LEX_NEQ ) 
    {
        //cout<<"E2::TRUE"<<'\n';
        
        gl(); 
        E1(); 
        E2();
    }
   // cout<<c_type<<'\n';
}

void Parser::T ()
{
    //cout<<"T::ENTER"<<'\n';
    F();
    while ( c_type == LEX_TIMES || c_type == LEX_SLASH || c_type == LEX_AND) 
    {
        //cout<<"T::ENTER WHILE"<<'\n';
        gl();
        F();
    }
}

void Parser::F ()
{
    //cout<<"F::ENTER"<<'\n';
    if ( c_type == LEX_ID )
    {
        //cout<<"F::TRUE LEX_ID"<<'\n';
        gl();
    }
    else if ( c_type == LEX_NUM ) 
    {
        //cout<<"F::TRUE LEX_NUM"<<'\n';
        gl();
    }
    else if(c_type == LEX_DQUATES)
    {
        gl();
        if(c_type==LEX_TEXT)
        {
            //cout<<"F::TRUE LEX_TEXT"<<'\n';
            gl();
            if(c_type==LEX_DQUATES)
            {
                gl();
            }
            else
            {
                throw curr_lex;
            }
            
        }
        else
        {
            
            throw curr_lex;
        }  
    }
    else if ( c_type == LEX_TRUE ) 
    {
        
        gl();
    }
    else if ( c_type == LEX_FALSE) 
    {
        gl();
    }
    else if (c_type == LEX_NOT) 
    {
        gl(); 
        F(); 
    }
     else if ( c_type == LEX_LPAREN ) 
    {
        gl(); 
        E();
        if ( c_type == LEX_RPAREN)
        gl();
        else
        {
            throw curr_lex;
        }
    } 
  else 
    throw curr_lex;
}

void Parser::STRUCT ()
{
        if(c_type == LEX_ID)
        {
            gl();
            if(c_type == LEX_FBRC_O)
            {
                gl();
                D1();
                while(c_type==LEX_SEMICOLON)
                {
                    gl();
                    D1();
                }

                if(c_type == LEX_FBRC_C)
                {
                    gl();

                }
                else
                {
                    throw curr_lex;
                }
            }
            else
            {
                throw curr_lex;
            }
           
                
        }
        else
        {
            throw curr_lex;
        }
}








int main(int argc, char* argv[])
{
  vector<string>::iterator vs;
try {
        
        Parser pars(argv[1]);
        pars.analyze();

        /* cout<<"TOT"<<'\n';
        vs=TOT.begin();
        while(vs!=TOT.end())
        {
          cout<<*vs<<'\n';
          vs++;
        } */

        
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