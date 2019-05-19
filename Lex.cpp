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
	void Ident::put_goto_place (int v){ 
	  goto_place = v; 
	}
	int Ident::get_goto_place () const{ 
	  return goto_place; 
	}

	ostream & operator<< (ostream &s, Ident l){
  
	s << '(' <<"Name:"<< l.get_name() << ',' <<"Declare:" << l.get_declare() << ','<<"Assign:" << l.get_assign() << " Value:"<<l.get_value()<<" Goto_place:"<<l.get_goto_place()<< ");" << endl;
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

//////////////////////  (Tables Of Somthings)  ///////////////////////
 
 vector< string > TOT; //table of texts

 int put_text ( const string & buf ){
	vector<string>::iterator k;
 
	if ( (k = find(TOT.begin(), TOT.end(), buf)) != TOT.end())
			return k - TOT.begin();
	TOT.push_back(buf); 
	return TOT.size() - 1;
 }


 vector< int > TOB;//table  of breaks
 vector < Ident > TOL; // table of lables

 //////////////////////////////////////////////////////////////////
  

std::unordered_map <type_of_lex,const std::string> TD_map = 
{
  {LEX_AND,"and"},
  {LEX_BOOL,"boolean"},
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
  {LEX_NUM,"NUM"},
  {LEX_ID,"ID"},
  {LEX_TEXT,"TEXT"},
  {LEX_FOR,"for"},
  {LEX_STRUCT,"struct"},
  {LEX_NULL,""},
  {LEX_TAG,"TAG"},
  {LEX_UMINUS,"@-"},
  {POLIZ_LABEL,"POLIZ_LABEL"},   
  {POLIZ_ADDRESS,"POLIZ_ADDR"}, 
  {POLIZ_GO,"POLIZ_GO"},      
  {POLIZ_FGO,"POLIZ_FGO"},

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
						 }
					else if ( c== '=' || c== '<' || c== '>' ) { 
							 buf.push_back(c);
							 //CS = ALE; 
							 set_CS(ALE);
						 }
					 else if (c == EOF)
					 {
					   //cout << "LEX_FIN CASE H" << '\n';
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
							//return Lex(LEX_DQUATES) ;
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
							j=put_text(buf);
							set_CS(DQUATES);
							return Lex(LEX_TEXT,j); 
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
	int in_cycle =0;
	void  P();
	void  D1();
	void  D();
	void  V();//переменная
	void  C();//const
	void  N();//sign
	void  B();
	void  S();
	void  S1();
	void  E();
	void  E1();
	void  E2();
	void  T();
	void  F();
	void GOTO();
	void STRUCT();
	void  dec ( type_of_lex type);
	void  check_id ();
	void  check_op ();
	void  check_not ();
	void check_uminus();
	void  eq_type ();
	void  eq_bool ();
	void  check_id_in_read ();
	void  gl () {
			  curr_lex = scan.get_lex();
			  c_type = curr_lex.get_type();
			  c_val = curr_lex.get_value();
			  //cout<<curr_lex<<'\n'; //added cout of lex step
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
	vector <Ident> ::iterator p=TOL.begin();
	int i=0;
	while (p!=TOL.end())
	{
		if(TOL[i].get_value()<0) throw "GOTO:NOT EXIST LABEL FOR GOTO JUMP";
		p++;
		i++;
	}
	   
		for (Lex l : poliz) 
		  cout << l;  

	cout << endl << "Yes!!!" << endl;
	cout<< "-----------------"<<'\n';
	cout << "Executing starting..."<<'\n';
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
	//cout << "P:: CHECK1" << '\n';
	if(c_type== LEX_FBRC_C) 
	{
	//cout << "P:: CHECK2" << '\n';
	   gl();// что здесь писать в случае правды?
	}
	else
	{
		//cout << "P:: CHECK3" << '\n';
		throw curr_lex;
	}
	
   
	
	

}

 void Parser::D () { //описаниЯ
//cout << "D::ENTER" << '\n';        

  /* D1();
  if(c_type != LEX_SEMICOLON)
  {
	  throw curr_lex;
  }
  else
  { */
	//gl();
	 while(c_type == LEX_INT || c_type == LEX_STRING || c_type == LEX_BOOL) 
	{ 
		D1();
		if(c_type != LEX_SEMICOLON)
		{
		  throw curr_lex;
		} 
		else
		{
			gl(); 
		}
			
	}
  }
  //что будет являться концом?
//} 

void Parser:: D1(){
	type_of_lex tmp = LEX_FIN;
	//st_int.reset();
	if(c_type == LEX_INT || c_type == LEX_STRING || c_type == LEX_BOOL) {
		tmp = c_type;
		gl();
	}
	else
		throw curr_lex;
	st_lex.push(tmp);
	V();
	while(c_type == LEX_COMMA) 
	{
		gl();
		st_lex.push(tmp);
		V();
	}
	if(tmp != LEX_FIN)
	{
		dec(tmp); 
	}
	   
	else
		throw curr_lex;
}

void Parser:: V(){
	Lex tmp = curr_lex;
	if(c_type != LEX_ID)
	{
		throw curr_lex;
	}
	else
	{
		st_int.push(c_val);
		//cout<<c_val<<'\n';
		gl();
	}
	if(c_type == LEX_ASSIGN){
		poliz.push_back(Lex(POLIZ_ADDRESS,tmp.get_value()));
		gl();
		C();
		//eq_type();//DANGER!
		poliz.push_back(Lex(LEX_ASSIGN));
	}
}

void Parser:: C(){
	if(c_type == LEX_PLUS || c_type == LEX_MINUS || c_type == LEX_NUM) 
	{
		N();
		st_lex.push(LEX_INT);
		eq_type();
	}
	else if(c_type == LEX_TEXT) 
	{
		poliz.push_back(curr_lex);
		gl();
		st_lex.push(LEX_STRING);
		eq_type();
		
	}
	else if(c_type == LEX_TRUE){
		poliz.push_back(curr_lex);
		gl();
		st_lex.push(LEX_BOOL);
		eq_type();
	}
	else if(c_type == LEX_FALSE){
		poliz.push_back(curr_lex);
		gl();
		st_lex.push(LEX_BOOL);
		eq_type();
	}
	else
	{
		throw curr_lex;
	}
		
}

void Parser:: N(){
	if(c_type == LEX_PLUS || c_type == LEX_MINUS)
	{
	   gl();
	}
		
	if(c_type == LEX_NUM)
	{
	  poliz.push_back(curr_lex);
		gl();
	}
	else
	{
		throw curr_lex;
	}
}



void Parser::S () { //ОператорЫ
//cout << "S::ENTER"<<'\n';
  S1();
 // gl();
 //cout << "S::AFTER S1" << '\n';
  while (c_type != LEX_FBRC_C) { //было так   while (c_type == LEX_SEMICOLON) {
			//gl();
			S1();
		}
}
void Parser::S1 () { // ОператоР
Lex temp;
int pl0, pl1, pl2, pl3;
vector <Ident> :: iterator p=TOL.begin();
bool W=false;
int i=0;

//cout<<"S1 ENTER"<<'\n';

	if (c_type == LEX_ID)
	{
		temp=curr_lex;
		//cout<<"TID NAME "<<TID[c_val].get_name()<<'\n';

		//cout<<"S1:: ENTER LEX_ID "<<c_type<<'\n';
		//check_id();
		gl();
		//cout << "S1::AFTER LEX_ID" << '\n';        
		if(c_type==LEX_ASSIGN)
		{
			c_type = temp.get_type();
			c_val = temp.get_value(); // обошли момент с проверкой LEX_ID
			check_id();// проверку будем делать здесь чтобы проходила проверка Goto
			//cout<<"S1::ENTER LEX_ASSIGN"<<'\n';
			poliz.push_back (Lex ( POLIZ_ADDRESS, temp.get_value()) );

			gl();
			E();
			eq_type();
			poliz.push_back (Lex (LEX_ASSIGN) );
		
			while(c_type==LEX_ASSIGN)
			{
				poliz.push_back (Lex ( POLIZ_ADDRESS, c_val) ); //попытка сделать вот такое a=b=v=10
				gl();
				E();
				eq_type();
				poliz.push_back (Lex (LEX_ASSIGN) );
			}

			if (c_type == LEX_SEMICOLON)
			{
				gl();
			}
			else
			{
				throw curr_lex;
			}
			
		}
		else if(c_type == LEX_COLON)
		{
			c_type = temp.get_type();
			c_val = temp.get_value();
			st_lex.push(LEX_TAG);
			st_int.push(temp.get_value()); // вот здесь короче объявление метки
			//cout<<curr_lex<<'\n';
			dec(LEX_TAG);
			check_id();
			//poliz.push_back();
			// ситуация мы нашли метку 

			vector <Ident> :: iterator p=TOL.begin();
			bool W=false;
			int i=0;
			cout<<"TID NAME "<<TID[c_val].get_name()<<'\n';
			while (p!=TOL.end())
			{
				//cout<<TID[c_val].get_name()<<'\n';
				if(TID[c_val].get_name()==TOL[i].get_name())
				{
					W=true;
					break;

				}
				p++;
				i++;
				
			}
			if(W==false)
			{
				cout<<"LABEL: LABLE WAS  NOT FIND IN TOL"<<'\n';
				TOL.push_back(TID[c_val]);
				TOL[TOL.size()-1].put_value(poliz.size()); //запоминаю место прыжка метки
				TOL[TOL.size()-1].put_goto_place(-1); //запоминаю место метки в стэке полиза
			}
			else
			{
				cout<<"LABEL: LABLE WAS FIND IN TOL "<<"i= "<<i<<'\n';
				//cout<<"poliz[]"<<poliz[TOL[i].get_goto_place()];
				poliz[TOL[i].get_goto_place()]=Lex(POLIZ_LABEL,poliz.size());
				TOL[i].put_value(poliz.size()); 
			}
			
			gl();
		
			S1();
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
			eq_bool();
			pl2 = poliz.size();
			poliz.push_back (Lex());
			poliz.push_back (Lex(POLIZ_FGO));
			if(c_type==LEX_RPAREN)
			{
				//cout<<"S1::ENTER RPAREN"<<'\n';
				gl();
				S1();
				pl3 = poliz.size();
				poliz.push_back (Lex());
 
				poliz.push_back (Lex(POLIZ_GO));
				poliz[pl2] = Lex(POLIZ_LABEL, poliz.size());
				if(c_type == LEX_ELSE)
				{
					// cout<<"S1::ENTER ELSE"<<'\n';
					gl();
					S1();
					poliz[pl3] = Lex(POLIZ_LABEL, poliz.size());
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

	else if(c_type==LEX_WHILE)
	{
		//cout<<"S1::ENTER LEX_WHILE"<<'\n';
		gl();
		if(c_type==LEX_LPAREN)
		{
			pl0=poliz.size();
			//poliz.push_back (Lex());
			gl();
			E();
			eq_bool();
			pl1=poliz.size(); 
			poliz.push_back (Lex());
			poliz.push_back (Lex(POLIZ_FGO));
			if(c_type==LEX_RPAREN)
			{
				gl();
				in_cycle++;
				S1();
				poliz.push_back(Lex (POLIZ_LABEL,pl0));
				poliz.push_back (Lex ( POLIZ_GO));
				poliz[pl1] = Lex ( POLIZ_LABEL, poliz.size());

				vector<int>::iterator p=TOB.begin();
				while(p!=TOB.end())
				{
					poliz[*p] = Lex (POLIZ_LABEL,poliz.size());
					p++;
				}
				TOB.clear();
				in_cycle--;
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
		//cout << "S1::LEX_READ ENTER" << '\n';
		gl();
		if(c_type==LEX_LPAREN)
		{
			gl();
			if(c_type==LEX_ID)
			{
				check_id_in_read();
				poliz.push_back (Lex( POLIZ_ADDRESS, c_val));
				gl();
				if(c_type==LEX_RPAREN)
				{
					gl(); 
					if(c_type == LEX_SEMICOLON)
					{
						gl();
						poliz.push_back (Lex (LEX_READ));
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
	else if(c_type == LEX_WRITE)
	{
		//cout << "S1::LEX_WRITE ENTER" << '\n';
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
				if(c_type == LEX_SEMICOLON)
				{
					gl();
					poliz.push_back (Lex(LEX_WRITE));
				}
				else
				{
					throw curr_lex;
				}
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
		//cout<<"ENTER GOTO"<<'\n';
		gl();
		if(c_type == LEX_ID)
		{
			//check_id(); // нужен ли в GOTO check_id учитывая что метка может стоить до GOTO то не нужно

			//Cитуация мы нашли GOTO
			vector <Ident> :: iterator p=TOL.begin();
			bool W=false;
			int i=0;
			
			while (p!=TOL.end())
			{
				
				if(TID[c_val].get_name()==TOL[i].get_name())
				{
					W=true;
					break;

				}
				p++;
				i++;
				
			}
			if(W==false)
			{
				cout<<"GOTO: LABLE WAS NOT FIND IN TOL"<<'\n';
				
				TOL.push_back(TID[c_val]);
			TOL[TOL.size()-1].put_value(-1); //запоминаю место прыжка метки
			TOL[TOL.size()-1].put_goto_place(poliz.size()); //запоминаю место метки в стэке полиза
			poliz.push_back(Lex());
			poliz.push_back(Lex(POLIZ_GO));
			
			}
			else
			{
				cout<<"GOTO: LABLE WAS FIND IN TOL"<<'\n';
				poliz.push_back (Lex(POLIZ_LABEL,TOL[i].get_value()));
				poliz.push_back (Lex(POLIZ_GO));
				TOL[TOL.size()-1].put_goto_place(poliz.size());
			}

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
		else
		{
			throw curr_lex;
		}
		
	}

	else if(c_type == LEX_BREAK)
	{
		if(in_cycle==0) throw "BREAK can appear only in cycle body.";
		gl();
		 if(c_type == LEX_SEMICOLON)
		{
			TOB.push_back(poliz.size());
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
				pl0=poliz.size(); // метка на возвращение на условие
				gl();
				E();
				eq_bool();
				pl1=poliz.size(); // метка для лжи
				poliz.push_back (Lex());
				poliz.push_back (Lex(POLIZ_FGO));
				pl2=poliz.size();//метка для правды для того чтобы перескачить инкремент
				poliz.push_back (Lex());
				poliz.push_back (Lex(POLIZ_GO));
				
				if(c_type == LEX_SEMICOLON)
				{
					pl3=poliz.size();
					gl();
					E();
					poliz.push_back(Lex (POLIZ_LABEL,pl0));
					poliz.push_back (Lex ( POLIZ_GO));//прыжок на условие 
					if(c_type == LEX_RPAREN)
					{
						gl();
						poliz[pl2]= Lex (POLIZ_LABEL,poliz.size());
						in_cycle++;
						S1();
						poliz.push_back (Lex(POLIZ_LABEL,pl3));
						poliz.push_back (Lex ( POLIZ_GO));//прыжок на инкермент
						poliz[pl1] = Lex ( POLIZ_LABEL, poliz.size());

						vector<int>::iterator p=TOB.begin();
						while(p!=TOB.end())
						{
							poliz[*p] = Lex (POLIZ_LABEL,poliz.size());
							p++;
						}
						TOB.clear();
						in_cycle--;
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
	else if(c_type == LEX_FBRC_O)//составной оператор
	{
	   //cout<<"B::ENTER FBRC_O"<<'\n';
	   gl();
	   S();
		if (c_type == LEX_FBRC_C)
		{
			//cout<<"B::ENTER FBRC_C"<<'\n';
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


void Parser::E ()
{
	Lex temp;
	//cout<<"E::ENTER"<<'\n';
	E1();
	 while (c_type == LEX_ASSIGN)
	{   
		temp=poliz[poliz.size()-1];//Attencion!
		poliz.pop_back();
		poliz.push_back(Lex(POLIZ_ADDRESS,temp.get_value()));
		gl();
		E();
		poliz.push_back(Lex(LEX_ASSIGN));
		
	} 
	
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
		//cout<<st_lex.top()<<'\n';
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
	   c_type == LEX_LEQ || c_type == LEX_GEQ || c_type == LEX_NEQ) //есть вариант сюда добавить LEX_ASSIGN  чтобы в for (i=1;i<10;i=i+1)
	{
		st_lex.push(c_type);
		//cout<<st_lex.top()<<'\n';
		//cout<<"E2::TRUE"<<'\n';
		
		gl(); 
		E1();
		check_op(); 
		E2();
		;//Есть проблема так как здесь вызов посути E то непонятно какую операцию брать
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
		//cout<<st_lex.top()<<'\n';
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
		//cout<<"F::"<<curr_lex<<'\n';
		check_id();
		poliz.push_back (Lex (LEX_ID, c_val));
		//cout<<"F::TRUE LEX_ID"<<'\n';
		gl();
	}
	else if ( c_type == LEX_NUM ) 
	{
		st_lex.push ( LEX_INT );
		poliz.push_back ( curr_lex );
		//cout<<st_lex.top()<<'\n';
		//cout<<"F::TRUE LEX_NUM"<<'\n';
		gl();
	}
	else if(c_type == LEX_TEXT)
	{
		
			st_lex.push(LEX_STRING);
			poliz.push_back ( curr_lex );// не знаю как  правильно реальзовать полиз в со стрингом
			//cout<<"F::"<<curr_lex<<'\n';
			//cout<<"F::TRUE LEX_TEXT"<<'\n';
			gl();
			
	}
	else if ( c_type == LEX_TRUE ) 
	{
		st_lex.push ( LEX_BOOL );
		poliz.push_back (Lex (LEX_TRUE, 1) );
		gl();
	}
	else if ( c_type == LEX_FALSE) 
	{
		st_lex.push ( LEX_BOOL );
		poliz.push_back (Lex (LEX_FALSE, 0) );
		gl();
	}
	else if (c_type == LEX_NOT) 
	{
		gl(); 
		F();
		check_not(); 
	}
	else if (c_type == LEX_MINUS)
	{
		gl();
		F();
		check_uminus();// хз что здесь должно быть
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
	  throw "DEC:: twice";
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
	//cout<<st_lex.top()<<'\n';
  }
	
  else 
  {
	throw "CHECK_ID:: not declared";  
  }
	
}
 
void Parser::check_op () { //хз как описать STRING и много операции
  type_of_lex t1, t2, op, t = LEX_INT, r = LEX_BOOL;

 /*  cout<<"STACK"<<'\n';
   st_lex.printStack(); */

  //cout<<"CHECK_OP:: Befor DECLARE"<<'\n';


   t2 = st_lex.top();
  st_lex.pop();
  op = st_lex.top();
  st_lex.pop();
  t1 = st_lex.top();
  st_lex.pop(); 
  //cout<<"CHECK_OP:: AFTER DECLARE"<<'\n';

  /* cout<<"STACK ST_LEX"<<'\n';
  while(!st_lex.empty())
  {
	  cout<<st_lex.top()<<'\n';
	  st_lex.pop();
  } */


	//cout<<" t1="<<t1<<" t2="<<t2<<" op="<<op<<'\n';
  if((t1== LEX_STRING)&& (t2 == LEX_STRING))
  {
	  t=LEX_STRING;
	  if(op==LEX_PLUS)
	  {
		  r=LEX_STRING;  
	  }
		if((op != LEX_LSS && op != LEX_GTR && op != LEX_EQ && op != LEX_NEQ && op != LEX_PLUS))
		{
		  //t=LEX_BOOL;  cout<<"TRUE"<<t<<'\n';
		  throw "not allowing operation for string.";
		  
		}  
  }

  
  //cout<<"CHECK_OP:: INT"<<'\n';
  if ((op == LEX_PLUS || op == LEX_MINUS || op == LEX_TIMES || op == LEX_SLASH)&&((t1==LEX_INT)&&(t2==LEX_INT)))
  {
	  r = LEX_INT;
	
  }
	
  if (op == LEX_OR || op == LEX_AND)
  {
	t = LEX_BOOL; 
  }
	 
  if ((t1 == t2  &&  t1 == t))
  {
	  
	st_lex.push(r);
  } 
	
  else
	throw "CHECK_OP:: wrong types are in operation";
  poliz.push_back (Lex (op) );
}
 
void Parser::check_not () {
  if (st_lex.top() != LEX_BOOL)
	throw "CHECK_NOT:: wrong type is in not";
  else  
	poliz.push_back (Lex (LEX_NOT));
}

void Parser::check_uminus () {
  if (st_lex.top() != LEX_INT)
	throw "CHECK_UMINUS:: wrong type is in not";
  else  
	poliz.push_back (Lex (LEX_UMINUS));
}
 
void Parser::eq_type () {
  type_of_lex t = st_lex.top();
  st_lex.pop();
  //cout<<"t="<<t<<"st_lex"<<st_lex.top()<<'\n';
  if ( t != st_lex.top())
	throw "EQ_TYPE:: wrong types are in =";
  st_lex.pop();
}
 
void Parser::eq_bool () {
  if ( st_lex.top() != LEX_BOOL )
	throw "EQ_BOOL:: expression is not boolean";
  st_lex.pop();
}
 
void Parser::check_id_in_read () {
  if ( !TID [c_val].get_declare() )
	throw "CHECK_ID:: not declared";
}
 
////////////////////////////////////////////////////////////////

class Executer
{
	Lex pc_el;
public:
	void execute(vector <Lex>& poliz);
};

void Executer::execute(vector <Lex> & poliz)
{
	stack < int > args;
	bool str = false;
	int i, j, index = 0, size = poliz.size();

	while (index < size)
	{
		pc_el = poliz[index];
		bool flag = false;
		switch (pc_el.get_type())
		{
		case LEX_TRUE:
		case LEX_FALSE:
		case LEX_NUM:
		case POLIZ_LABEL:
			args.push(pc_el.get_value());
			break;
		case POLIZ_ADDRESS:
			i = pc_el.get_value();
			if (TID[i].get_type() == LEX_STRING)
			{
				flag = true;
			}
			args.push(pc_el.get_value());
			break;
		case LEX_TEXT:
			args.push(pc_el.get_value());
			flag = true;
			break;
		case LEX_ID:
			i = pc_el.get_value();
			/* if (TID[i].if_label())
			{
				args.push(TID[i].get_poliz_val()); // здесь возожно что-то связанное с метками
				break;
			} */
			if (TID[i].get_assign())
			{
				if (TID[i].get_type() == LEX_STRING)
				{
					flag = true;
				}
				args.push(TID[i].get_value());	
				break;
			}
			else
			{
				throw "indefinite identifier";
			}
		case LEX_NOT:
			i = args.top();
		args.pop();
		args.push( !i );
			break;
		case LEX_OR:
			i = args.top();
		args.pop();
		j = args.top();
		args.pop();
		args.push ( j || i );
			break;
		case LEX_AND:
			i = args.top();
		args.pop();
		j = args.top();
		args.pop();
		args.push ( j && i );
			break;
		case POLIZ_GO:
			i = args.top();
		args.pop();
		index = i - 1;
		break;
			break;
		case POLIZ_FGO:
			i = args.top();
		args.pop();
		j = args.top();
		args.pop();
		if ( !j ) index = i-1;
			break;
		case LEX_WRITE:
			if (str)
			{
		j = args.top();
		args.pop();
				cout << TOT[j] << endl;
			}
			else
			{
		j = args.top();
		args.pop();
				cout << j << endl;
			}
			break;
		case LEX_READ:
		{
			int k;
			i = args.top();
	  args.pop();
			if (str)
			{
				char s[100];
				cout << "Input string value for " << TID[i].get_name() << endl;
				cin >> s;
				k = put_text(s); // Заполняем текст в ТОТ
			}
			else if (TID[i].get_type() == LEX_INT)
			{
				cout << "Input int value for " << TID[i].get_name() << endl;
				cin >> k;
			}
			else
			{
				char j[20];
			rep:
				cout << "Input boolean value (true or false) for " << TID[i].get_name() << endl;
				cin >> j;
				if (!strcmp(j, "true"))
				{
					k = 1;
				}
				else if (!strcmp(j, "false"))
				{
					k = 0;
				}
				else
				{
					cout << "Error in input: true/false";
					cout << endl;
					goto rep;
				}
			}
			TID[i].put_value(k);
			TID[i].put_assign();
			break;
		}
		case LEX_PLUS:
			if (str)
			{
		string buf;
				i = args.top();
		args.pop();
		j = args.top();
		args.pop();
		buf.append(TOT[i]);
		buf.append(TOT[j]);
				args.push(put_text(buf));
				flag = true;
			}
			else
			{
				i = args.top();
		args.pop();
		j = args.top();
		args.pop();
		args.push ( i + j );
			}
			break;

	  case LEX_TIMES:
		i = args.top();
		args.pop();
		j = args.top();
		args.pop();
		args.push ( i * j );
		break;

		case LEX_MINUS:
			i = args.top();
		args.pop();
		j = args.top();
		args.pop();
		args.push ( j - i );
			break;
		case LEX_SLASH:
			i = args.top();
		args.pop();
		j = args.top();
		args.pop();
		if (!i) {
		  args.push(j / i);
		  break;
		}
		else
		{
		  throw "POLIZ:divide by zero";
		}
		  
		case LEX_EQ:
			if (str)
			{
				string buf1;
		string buf2;
				i = args.top();
		args.pop();
		j = args.top();
		args.pop();
		buf1.append(TOT[i]);
		buf2.append(TOT[j]);
		args.push(buf1==buf2);
			}
			else
			{
				i = args.top();
		args.pop();
		j = args.top();
		args.pop();
		args.push ( i == j);
		break;
			}
			break;
		case LEX_LSS:
			if (str)
			{
				string buf1;
		string buf2;
				i = args.top();
		args.pop();
		j = args.top();
		args.pop();
		buf1.append(TOT[i]);
		buf2.append(TOT[j]);
		args.push(buf1<buf2);
			}
			else
			{
				i = args.top();
		args.pop();
		j = args.top();
		args.pop();
		args.push ( j < i);
			}
			break;
		case LEX_GTR:
			if (str)
			{
				string buf1;
		string buf2;
				i = args.top();
		args.pop();
		j = args.top();
		args.pop();
		buf1.append(TOT[i]);
		buf2.append(TOT[j]);
		args.push(buf1>buf2);
			}
			else
			{
				i = args.top();
		args.pop();
		j = args.top();
		args.pop();
		args.push ( j > i);
			}
			break;
		case LEX_LEQ:
		i = args.top();
		args.pop();
		j = args.top();
		args.pop();
		args.push ( j <= i );
			break;
		case LEX_GEQ:
			i = args.top();
		args.pop();
		j = args.top();
		args.pop();
		args.push ( j >= i );
			break;
		case LEX_NEQ:
			if (str)
			{
				string buf1;
		string buf2;
				i = args.top();
		args.pop();
		j = args.top();
		args.pop();
		buf1.append(TOT[i]);
		buf2.append(TOT[j]);
		args.push(buf1!=buf2);
			}
			else
			{
				i = args.top();
		args.pop();
		j = args.top();
		args.pop();
		args.push ( j != i );
			}
			break;
		case LEX_ASSIGN:
			i = args.top();
		args.pop();
		j = args.top();
		args.pop();
		TID[j].put_value(i);
		TID[j].put_assign();
			if (str)
			{
				flag = true;
			}
			break;
		default:
			throw "POLIZ: unexpected lexeme";
			break;
		}
		if (flag)
		{
			str = true;
		}
		else
		{
			str = false;
		}
		++index;
	}
	cout << "Finish of executing!!!"<<'\n';
}

class Interpretator {
  Parser   pars;
  Executer E;
public:
  Interpretator  (const char* program): pars (program) {}
  void     interpretation ();
};

void Interpretator::interpretation () {
  pars.analyze ();
  E.execute ( pars.poliz );
}
 
double ff(const double & d){return d;}

////////////////////////////////////////////////////////////////








int main(int argc, char* argv[])
{
  vector<Ident>::iterator vi;
  vector<Ident>::iterator vl;
  vector<string>::iterator vs;
try {
		
		/* Parser pars(argv[1]);
		pars.analyze(); */

		int dd = 5;
	  cout << "result ff(i) = " << ff(dd) << endl;   
	  Interpretator I (argv[1]);
	  I.interpretation ();
	  
		cout <<'\n'<<"-------------------"<< '\n';
		 cout<<"TOT"<<'\n';
		vs=TOT.begin();
		while(vs!=TOT.end())
		{
		  cout<<*vs<<'\n';
		  vs++;
		} 

		cout <<'\n'<<"-------------------"<< '\n';
		 cout<<"TID"<<'\n';
		vi=TID.begin();
		while(vi!=TID.end())
		{
		  cout<<*vi<<'\n';
		  vi++;
		}

		cout <<'\n'<<"-------------------"<< '\n';
		cout<<"TOL"<<'\n';
		vl=TOL.begin();
		while(vl!=TOL.end())
		{
		  cout<<*vl<<'\n';
		  vl++;
		}  

		return 0;
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