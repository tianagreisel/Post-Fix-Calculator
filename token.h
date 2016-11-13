// ------------------------------------------------ token.h ------------------------------------------------------- -
// Tiana Greisel CSS 342
// Creation Date:  May 20, 2016
// Date of Last Modification:  May 24, 2016
// --------------------------------------------------------------------------------------------------------------------
// Purpose - The Token class interface. Enumerate operators and operands as TokenType.
// --------------------------------------------------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions:
//			- Assume that EXP ( ^ ) is above MULT ( * ) in the order of precedence.
// --------------------------------------------------------------------------------------------------------------------

#ifndef TOKEN_H
#define TOKEN_H

using namespace std;

enum TokenType {
  EOL,         // end of line                   the same as the original
  VALUE,       // constant                      the same as the original
  OPAREN,      // (                             the same as the original
  CPAREN,      // )                             the same as the original

  NOT,         // ! (logical negation)          reserved for PROG 5
  BIT_COMP,    // ~                             reserved for PROG 5

  UN_MINUS,    // -                             reserved for PROG 5
  UN_PLUS,     // +                             reserved for PROG 5

  EXP,		   //^								exponent

  MULT,        // *                             the same as the original
  DIV,         // /                             the same as the original
  MODULUS,     // %

  PLUS,        // -                             the same as the original
  MINUS,       // +                             the same as the original

  SHIFT_L,     // <<
  SHIFT_R,     // >>
  LT,          // <
  LE,          // <=
  GT,          // >
  GE,          // >=

  EQUAL,       // ==
  NOTEQUAL,    // !=

  BIT_AND,     // &

  BIT_IOR,     // |

  LOG_AND,     // &&
  LOG_OR,      // ||
  ASSIGNMENT,  // =
  VAR_A,       // variable a
  VAR_B,       // variable b
  VAR_C        // variable c
};

// the class definition is the same as the original
template <class NumericType>
class Token {
 public:
  Token( TokenType tt = EOL, const NumericType & nt = 0 )
    : theType( tt ), theValue( nt ) {
  }

  TokenType getType( ) const {
    return theType;
  }
  const NumericType &getValue( ) const {
    return theValue;
  }

 private:
  TokenType   theType;
  NumericType theValue;
};

#endif



