
// ------------------------------------------------ tokenizer.cpp.h ------------------------------------------------------- -
// Tiana Greisel CSS 342
// Creation Date:  May 20, 2016
// Date of Last Modification:  May 24, 2016
// --------------------------------------------------------------------------------------------------------------------
// Purpose - The Tokenizer class interface.  Responsible for getting the characters in the input steam using
//				getChar and can return the Token with method getToken.  It includes the getToken routine for returning the
//				next token in the input stream.
// --------------------------------------------------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions:
//			- Has TokenType prevToken as a private data member of tokenizer.h and whenever tokenizer.cpp.h returns a token type,
//			  	it gets memorized in prevToken.
//			- When encountering '+' or '-', tokenizer.cpp.h must check prevToken if the previous token was '('. If so, you can return
//				the unary '+' or unary '-'. Otherwise, it should return the binary '+' or binary '-'.
//			- Note that prevToken is initialized with OPAREN (i.e, '(') so that tokenizer.cpp.h can accept the very first '+' or '-' as a
//				unary operator even in case if they do not follow an open parenthesis.
// --------------------------------------------------------------------------------------------------------------------

template <class NumericType>
bool Tokenizer<NumericType>::getChar( char &ch ) {
  char tmp;

  // skip blanks
  while ( in.get( tmp ) && tmp == ' ' );

  // read a char
  if ( in.good( ) && tmp != '\n'&& tmp != '\0' ) {
    ch = tmp;
    return true; // if it is not a delimiter
  }
  else
    return false; // if it's a delimitter
}

template <class NumericType>
Token<NumericType> Tokenizer<NumericType>::getToken( ) {

  char ch;

  NumericType theValue;

  if ( getChar( ch ) == true ) {
    switch( ch ) {
    case 'a':
		prevToken = VAR_A;
    	return Token<NumericType>(VAR_A, 0);
    case 'b':
    	prevToken = VAR_B;
    	return Token<NumericType>(VAR_B, 0);
    case 'c':
    	prevToken = VAR_C;
    	return Token<NumericType>(VAR_C, 0);
    case '/':
    	prevToken = DIV;
    	return DIV;
    case '*':
    	prevToken = MULT;
    	return MULT;
    case '(':
    	prevToken = OPAREN;
    	return OPAREN;
    case ')':
    	prevToken = CPAREN;
    	return CPAREN;
    case '+':
    	if(prevToken == OPAREN){				//if prevToken is ( then unary operator +
    		prevToken = UN_PLUS;
    		return UN_PLUS;
    	}
    	else{									//if not unary operator +, return binary operator
    		prevToken = PLUS;
    		return PLUS;
    	}
    case '-':
    	if(prevToken == OPAREN){				//if prevToken is ( then unary operator -
    		prevToken = UN_MINUS;
    		return UN_MINUS;
    	}
    	else{									//if not unary operator -, return binary operator -
    		prevToken = MINUS;
    		return MINUS;
    	}
    case '~':
    	prevToken = BIT_COMP;
    	return BIT_COMP;
    case '^':
    	prevToken = EXP;
    	return EXP;
    case '%':
    	prevToken = MODULUS;
    	return MODULUS;
    case '<':
    	getChar(ch);
    	if(ch == '<'){							//if <<
    		prevToken = SHIFT_L;
    		return SHIFT_L;
    	}
    	else if( ch == '='){      				//if <=
    		prevToken = LE;
    		return LE;
    	}
    	else{
    		in.putback(ch);					//just < so putback next character  that istream read and return just <
    		prevToken = LT;
    		return LT;
    	}
    case '>':
    	getChar(ch);
    	if( ch == '>')						// >>
    	{
    		prevToken = SHIFT_R;
    		return SHIFT_R;
    	}
    	else if( ch == '='){				// >=
    		prevToken = GE;
    		return GE;
    	}
    	else{								// >
    		in.putback (ch);
    		prevToken = GT;
    		return GT;
    	}
    case '=':
    	getChar( ch );							// ==  need to check if next character is an = for ==
    	if(ch == '='){
    		prevToken = EQUAL;
    		return EQUAL;
    	}
    	else{
    		in.putback( ch );					// = assignment
    		prevToken = ASSIGNMENT;
    		return ASSIGNMENT;
    	}
    case '!':
		getChar( ch );
    	if( ch  == '='){						// != if next character is = then return NOTEQUAL because !=
			prevToken = NOTEQUAL;
			return NOTEQUAL;
		}
		else{
			in.putback( ch );					//if not, then put character back because it is NOT !
			prevToken = NOT;
			return NOT;
		}
    case '&':
    	getChar(ch);
    	if(  ch  == '&'){						//&&
    		prevToken = LOG_AND;
    		return LOG_AND;
    	}
    	else{									//&
    		in.putback( ch );
    		prevToken = BIT_AND;
    		return BIT_AND;
    	}
    case '|':
    	getChar(ch);
    	if(  ch  == '|'){						// ||
    		prevToken = LOG_OR;
    		return LOG_OR;
    	}
    	else{									// |
    		in.putback( ch );
    		prevToken = BIT_IOR;
    		return BIT_IOR;
    	}
    default:
      in.putback( ch );
      if ( !( in >> theValue ) ) {
	cerr << "Parse error" << endl;
	prevToken = EOL;
	return EOL;
      }
      prevToken = VALUE;						//prevToken is VALUE
      return Token<NumericType>( VALUE, theValue );
    }
  }
  prevToken = EOL;
  return EOL;
}


