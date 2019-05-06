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

    ostream & operator<< (ostream &s, Ident l){
  
    s << '(' <<"Name:"<< l.get_name() << ',' <<"Declare:" << l.get_declare() << ','<<"Assign:" << l.get_assign() << ");" << endl;
    return s;
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
type_of_lex loc_type; 
    if (c_type == LEX_INT || c_type == LEX_BOOL || c_type == LEX_STRING) {
        loc_type=c_type;// перменная для хранения типа LEX_TYPE
        //cout<<"CHECK"<<'\n';
        gl();
        if (c_type != LEX_ID) throw curr_lex;
        else {
            st_int.push ( c_val );
            dec(loc_type);
                    //cout<<"CHECK2"<<'\n';
            //check_id();
            //cout<<"CHECK3"<<'\n';
            gl();
            Z();
            while (c_type == LEX_COMMA) {
                gl();
                if (c_type != LEX_ID) throw curr_lex;
                else {
                st_int.push ( c_val );
                dec(loc_type);
                //check_id();
                gl();
                Z();
                }
            }
        }
    }

    if(c_type==LEX_STRUCT)
    {
        cout<<"D1::ENTER LEX_STRUCT"<<'\n';
        //dec(LEX_STRUCT);
        gl();
        STRUCT();
    }         
}

void Parser::Z(){
    if(c_type==LEX_ASSIGN)
    {
        gl();
        E();
       // eq_type();
    }    
}

void Parser::S () { //ОператорЫ
//cout << "S::ENTER"<<'\n';
  S1();
 // gl();
 //cout << "S::AFTER S1" << '\n';
  while (c_type == LEX_SEMICOLON) { //было так   while (c_type == LEX_SEMICOLON) {
            gl();
            S1();
        }
    //cout << "S::AFTER WHILE S1" << '\n';
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
        //cout<<"S1:: ENTER LEX_ID "<<c_type<<'\n';
        check_id();
        gl();
        //cout << "S1::AFTER LEX_ID" << '\n';        
        if(c_type==LEX_ASSIGN)
        {
            //cout<<"S1::ENTER LEX_ASSIGN"<<'\n';

            gl();
            E();
            eq_type();
        
            while(c_type==LEX_ASSIGN)
            {
                gl();
                E();
                //eq_type();
            }
        }
        
        else
        {
            throw curr_lex;
        }   
    }

    else if(c_type==LEX_IF)
    {
                //cout<<"S1::ENTER IF"<<'\n';
            
            gl();
            if(c_type==LEX_LPAREN)
            {
                //cout<<"S1::ENTER LPAREN"<<'\n';
                gl();
                E();
                //eq_bool();
                if(c_type==LEX_RPAREN)
                {
                    //cout<<"S1::ENTER RPAREN"<<'\n';
                    gl();
                    S1();
                    if(c_type == LEX_ELSE)
                    {
                       // cout<<"S1::ENTER ELSE"<<'\n';
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
           // eq_bool();
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
                //check_id_in_read();
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
            //check_id();
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
         if(c_type == LEX_SEMICOLON)
        {
            gl();

        }
        else
        {
            throw curr_lex;
        }
    } 
        //здесь возможно должно быть что-то еще 

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
        //throw curr_lex;
        B();
    } */ 
}

 /* void Parser::B () { // Блок
    cout<<"B::ENTER"<<'\n';
    if(c_type == LEX_FBRC_O)
    {
        cout<<"B::ENTER FBRC_O"<<'\n';
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
         cout<<"B::ERR"<<'\n';
        throw curr_lex; 
    }
}  */ 

void Parser::E ()
{
    //cout<<"E::ENTER"<<'\n';
        E1();
        E2();
        //cout<<"E::CHECK_OP!"<<'\n';
}

void Parser::E1()
{
    //cout<<"E1::ENTER"<<'\n';
    T();
    while(c_type==LEX_PLUS || c_type==LEX_MINUS || c_type==LEX_OR)
    {
        //cout<<curr_lex<<'\n';
        st_lex.push(c_type);
        cout<<st_lex.top()<<'\n';
        //cout<<"E1::TRUE"<<'\n';
        gl();
        T();
        check_op();
    }
    //здесь надо какой-то троу?
    
}

void Parser::E2 ()
{
    //cout<<"E2::ENTER"<<'\n';
    if ( c_type == LEX_EQ || c_type == LEX_LSS || c_type == LEX_GTR ||
       c_type == LEX_LEQ || c_type == LEX_GEQ || c_type == LEX_NEQ ) 
    {
        st_lex.push(c_type);
        cout<<st_lex.top()<<'\n';
        //cout<<"E2::TRUE"<<'\n';
        
        gl(); 
        E1(); 
        E2();
        check_op();//Есть проблема так как здесь вызов посути E то непонятно какую операцию брать
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
        st_lex.push(c_type);
        cout<<st_lex.top()<<'\n';
        gl();
        F();
        check_op();
    }
}

void Parser::F ()
{
    //cout<<"F::ENTER"<<'\n';
    if ( c_type == LEX_ID )
    {
        cout<<"F::"<<curr_lex<<'\n';
        check_id();
        
        //cout<<"F::TRUE LEX_ID"<<'\n';
        gl();
    }
    else if ( c_type == LEX_NUM ) 
    {
        st_lex.push ( LEX_INT );
        cout<<st_lex.top()<<'\n';
        //cout<<"F::TRUE LEX_NUM"<<'\n';
        gl();
    }
    else if(c_type == LEX_DQUATES)
    {
        gl();
        if(c_type==LEX_TEXT)
        {
            st_int.push(LEX_STRING);
            cout<<"F::"<<curr_lex<<'\n';
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
        st_lex.push ( LEX_BOOL );
        
        gl();
    }
    else if ( c_type == LEX_FALSE) 
    {
        st_lex.push ( LEX_BOOL );
        gl();
    }
    else if (c_type == LEX_NOT) 
    {
        gl(); 
        F();
        check_not(); 
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


////////////////////////////////////////////////////////////////
 
void Parser::dec ( type_of_lex type ) {
  int i;
  while ( !st_int.empty()) {
    i = st_int.top();
    st_int.pop();
    if ( TID[i].get_declare() ) 
      throw "twice";
    else {
      TID[i].put_declare();
      TID[i].put_type(type);
    }
  }
}
 
void Parser::check_id () {

  if ( TID[c_val].get_declare() )
  {
    st_lex.push ( TID[c_val].get_type() );
    cout<<st_lex.top()<<'\n';
    cout<<"CHEK_ID::OUT"<<'\n';
      
  }
    
  else 
  {
    throw "not declared";  
  }
    
}
 
void Parser::check_op () { //хз как описать STRING и много операции
  type_of_lex t1, t2, op, t = LEX_INT, r = LEX_BOOL,s = LEX_STRING;

 /*  cout<<"STACK"<<'\n';
   st_lex.printStack(); */

  cout<<"CHECK_OP:: Befor DECLARE"<<'\n';


  t2 = st_lex.top();
  st_lex.pop();
  op = st_lex.top();
  st_lex.pop();
  t1 = st_lex.top();
  st_lex.pop();
  cout<<"CHECK_OP:: AFTER DECLARE"<<'\n';


    cout<<" t1="<<t1<<" t2="<<t2<<" op="<<op<<'\n';
  if((t1= LEX_STRING)&& (t2 == LEX_STRING))
  {
      
      if(op==LEX_PLUS)
      {
          
          r=LEX_STRING;
          t=LEX_STRING;
      }
  }
  cout<<"CHECK_OP:: INT"<<'\n';
  if ((op == LEX_PLUS || op == LEX_MINUS || op == LEX_TIMES || op == LEX_SLASH)&&((t1==LEX_INT)&&(t2==LEX_INT)))
    r = LEX_INT;
  if (op == LEX_OR || op == LEX_AND)
    t = LEX_BOOL;
  if (t1 == t2  &&  t1 == t) 
    st_lex.push(r);
  else
    throw "wrong types are in operation";
  poliz.push_back (Lex (op) );
}
 
void Parser::check_not () {
  if (st_lex.top() != LEX_BOOL)
    throw "wrong type is in not";
  else  
    poliz.push_back (Lex (LEX_NOT));
}
 
void Parser::eq_type () {
  type_of_lex t = st_lex.top();
  st_lex.pop();
  if ( t != st_lex.top())
    throw "wrong types are in :=";
  st_lex.pop();
}
 
void Parser::eq_bool () {
  if ( st_lex.top() != LEX_BOOL )
    throw "expression is not boolean";
  st_lex.pop();
}
 
void Parser::check_id_in_read () {
  if ( !TID [c_val].get_declare() )
    throw "not declared";
}
 
////////////////////////////////////////////////////////////////








int main(int argc, char* argv[])
{
  vector<Ident>::iterator vs;
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

         cout<<"TID"<<'\n';
        vs=TID.begin();
        while(vs!=TID.end())
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