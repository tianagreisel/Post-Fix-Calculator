
// ------------------------------------------------ tokenizer.cpp.h ------------------------------------------------------- -
// Tiana Greisel CSS 342
// Creation Date:  May 20, 2016
// Date of Last Modification:  May 24, 2016
// --------------------------------------------------------------------------------------------------------------------
// Purpose - The calculator's, (i.e., Evaluator's) implementation that includes getValue( ), getTop( ), binaryOp( ),
//				and processToken( ).
// --------------------------------------------------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions:
//			- The order in PREC_TABLE matches with TokenType defined in token.h.
// --------------------------------------------------------------------------------------------------------------------

// Public routine that performs the evaluation. Examines the postfix machine
// to see if a single result is left and if so, return it; otherwise prints
// error.
template<class NumericType>
NumericType Evaluator<NumericType>::getValue( ) {

  Tokenizer<NumericType> tok( str );
  Token<NumericType> lastToken;

  do {
    lastToken = tok.getToken( );
    processToken( lastToken );
  } while ( lastToken.getType( ) != EOL );

  if ( postFixStack.empty( ) ) {
    cerr << "Missing operand!" << endl;
    return 0;
  }

  NumericType theResult = postFixStack.back( );
  postFixStack.pop_back( );
  if ( !postFixStack.empty( ) )
    cerr << "Warning: missing operators!" << endl;

  return theResult;
}

// After token is read, use operator precedence parsing algorithm to process
// it; missing opening parentheses are detected here.
template<class NumericType>
void Evaluator<NumericType>::
processToken( const Token<NumericType> &lastToken ) {
  TokenType topOp;
  TokenType lastType = lastToken.getType( );

  switch( lastType ) {
  case VALUE:											//if VALUE
    postFixStack.push_back( lastToken.getValue( ) );	//push value on postFixStack
    postFixVarStack.push_back( ' ' );					//use a ' ' so postFixStack and postFixVarStack grow and shrink together
    return;

  case VAR_A:											//if VAR_A
	  postFixStack.push_back( var_a );					//push var_a onto postFixStack
	  postFixVarStack.push_back( 'a' );					//push 'a' onto postFixVarStack
	  return;

  case VAR_B:											//if VAR_B
	  postFixStack.push_back( var_b );					//push var_b onto postFixStack
	  postFixVarStack.push_back( 'b' );					//push 'b' on postFixVarStack
	  return;

  case VAR_C:											//if VAR_C
  	  postFixStack.push_back( var_c );					//push var_c onto postFixStack
  	  postFixVarStack.push_back( 'c' );					//push 'c' on postFixVarStack
  	  return;

  case CPAREN:
    while( ( topOp = opStack.back( ) ) != OPAREN &&
	   topOp != EOL )
      binaryOp( topOp );
    if ( topOp == OPAREN )
      opStack.pop_back( ); // get rid of opening parenthesis
    else
      cerr << "Missing open parenthesis" << endl;
    break;

  default: // general operator case
    while ( PREC_TABLE[ lastType ].inputSymbol <=
	    PREC_TABLE[ topOp = opStack.back( ) ].topOfStack )
      binaryOp( topOp );

    if ( lastToken.getType( ) != EOL )
      opStack.push_back( lastType );

    break;
  }
}

// Process an operator by taking two items off the postfix stack, applying
// the operator, and pushing the result.
// Print error if missing closing parenthesis or division by 0.
template<class NumericType>
void Evaluator<NumericType>::binaryOp( TokenType topOp ) {
  if ( topOp == OPAREN ) {
    cerr << "Unbalanced parenthesis" << endl;
    opStack.pop_back( );
    return;
  }

  NumericType rhs;								//rhs top of postFixStack
  NumericType lhs;								//lhs top of postFixStack - declare because don't use in unary operation, only rhs

  //UNARY OPERATOR								//if unary operator, evaluate differently. Only one operand
  if(topOp == UN_MINUS || topOp == UN_PLUS || topOp == NOT || topOp == BIT_COMP){
	  rhs = getTop( );							//get the rhs from top of postFixStack
	  if(topOp == UN_MINUS){					//if unary -
		  postFixStack.push_back( -rhs );		// perform unary - on rhs and push result onto postFixStack
	  }
	  else if(topOp == UN_PLUS){				// if unary +
		  postFixStack.push_back( +rhs );		// perform unary + on rhs and push result onto postFixStack
	  }
	  else if(topOp == BIT_COMP){				// if unary ~
		  postFixStack.push_back( ~rhs );		// perform unary ~ on rhs and push result onto postFixStack
	  }
	  else if(topOp == NOT){					// if unary !
		  postFixStack.push_back( !rhs );		// perform unary ! on rhs and push result onto postFixStack
	  }
  }
  //BINARY OPERATOR								//two operands
  else{
	  rhs = getTop();							//get rhs from top of postFixVarStack
	  lhs = getTop();							//get lhs from top of postFixVarStack

  if (topOp == ASSIGNMENT){						// if = (assignment operator)
	  if(lhs == var_a){							//if on variable a
		  var_a = rhs;							//set evaluator member var_a to rhs so when access variable again the value is stored
		  postFixStack.push_back(rhs);			//push result onto postFixVarStack
	  }
	  else if(lhs == var_b){					//if variable b
		  var_b = rhs;							//set evaluator member var_b to rhs so when access variable again the value is stored
		  postFixStack.push_back(rhs);			//push result onto postFixVarStack
	  }
	  else if(lhs == var_c){					//if varable c
		  var_c = rhs;							//set evaluator member var_c to rhs so when access variable again the value is stored
		  postFixStack.push_back(rhs);			//push result onto postFixVarStack
	  }
  }
  else if ( topOp == PLUS )							//+
	  	  postFixStack.push_back( lhs + rhs );
  else if ( topOp == MINUS )						//-
	  	  postFixStack.push_back( lhs - rhs );
  else if (topOp == EXP)							//^
	  	  postFixStack.push_back(pow(lhs, rhs));
  else if (topOp == SHIFT_L)						//<<
	  	  postFixStack.push_back(lhs << rhs);
  else if (topOp == SHIFT_R)						//>>
  	  	  postFixStack.push_back(lhs >> rhs);
  else if (topOp == LT)								//<
  	  	  postFixStack.push_back(lhs < rhs);
  else if (topOp == LE)								//<=
	  	  postFixStack.push_back(lhs <= rhs);
  else if (topOp == GT)								//>
	  	  postFixStack.push_back(lhs > rhs);
  else if (topOp == GE)								//>=
  	  	  postFixStack.push_back(lhs >= rhs);
  else if (topOp == EQUAL)							//==
  	  	  postFixStack.push_back(lhs == rhs);
  else if (topOp == NOTEQUAL)						//!=
  	  	  postFixStack.push_back(lhs != rhs);
  else if (topOp == BIT_AND)						//&
    	  postFixStack.push_back(lhs & rhs);
  else if (topOp == BIT_IOR)						//|
    	  postFixStack.push_back(lhs | rhs);
  else if (topOp == LOG_AND)						//&&
    	  postFixStack.push_back(lhs && rhs);
  else if (topOp == LOG_OR)							//||
    	  postFixStack.push_back(lhs || rhs);
  else if (topOp == MODULUS)						//%
      	  postFixStack.push_back(lhs % rhs);
  else if ( topOp == MULT )							//*
	  	  postFixStack.push_back( lhs * rhs );
  else if ( topOp == DIV )							// /
    if ( rhs != 0 )
    	postFixStack.push_back( lhs / rhs );
    else {
    	cerr << "Division by zero" << endl;
    	postFixStack.push_back( lhs );
    }
  }
  opStack.pop_back( );
  postFixVarStack.push_back( ' ' );					//push a ' ' blank space onto postFixStack so postFixVarStack and postFixStack
}													//grow and shrink together

// top and pop the postfix machine stack; return the result.
// If the stack is empty, print an error message.
template<class NumericType>
NumericType Evaluator<NumericType>::getTop( ) {
  if ( postFixStack.empty( ) ) {
    cerr << "Missing operand" << endl;
    return 0;
  }

  NumericType tmp = postFixStack.back( );
  postFixStack.pop_back( );
  postFixVarStack.pop_back();				//pop element off of postFixVarStack at same top pop something off postFixStack so postFixVarStack
  	  	  	  	  	  	  	  	  	  	  	//and postFixStack grow and shrink together
  return tmp;
}



