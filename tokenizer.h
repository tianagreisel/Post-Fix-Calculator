
// ------------------------------------------------ tokenizer.h ------------------------------------------------------- -
// Tiana Greisel CSS 342
// Creation Date:  May 20, 2016
// Date of Last Modification:  May 24, 2016
// --------------------------------------------------------------------------------------------------------------------
// Purpose - The Tokenizer class interface.  Responsible for getting the characters in the input steam using
//				getChar and can return the Token with method getToken.
// --------------------------------------------------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions:
//			- Has TokenType prevToken as a private data member of tokenizer.h and whenever tokenizer.cpp.h returns a token type,
//			  	it gets memorized in prevToken.
//			- When encountering '+' or '-', tokenizer.cpp.h must check prevToken if the previous token was '('. If so, you can return
//				the unary '+' or unary '-'. Otherwise, it should return the binary '+' or binary '-'.
//			- Note that prevToken is initialized with OPAREN (i.e, '(') so that tokenizer.cpp.h can accept the very first '+' or '-' as a
//				unary operator even in case if they do not follow an open parenthesis.
// --------------------------------------------------------------------------------------------------------------------

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>

#include "token.h"
using namespace std;

template <class NumericType>
class Tokenizer {
 public:
  Tokenizer( istream &is ) : in( is ), prevToken( OPAREN ) {	//initialize prevtoken to OPAREN so very first unary operator +/-
  }																//is evaluated correctly
  Token<NumericType> getToken( );

 private:
  istream &in;
  bool getChar( char &ch );

  TokenType prevToken; // it may be necessary for the programming assignment 6
};

#include "tokenizer.cpp.h"
#endif




