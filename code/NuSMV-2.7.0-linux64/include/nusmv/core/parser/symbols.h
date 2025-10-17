/* ---------------------------------------------------------------------------


  This file is part of the ``parser'' package of NuSMV version 2.
  Copyright (C) 2005 by FBK-irst.

  NuSMV version 2 is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

  NuSMV version 2 is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA.

  For more information on NuSMV see <http://nusmv.fbk.eu>
  or email to <nusmv-users@fbk.eu>.
  Please report bugs to <nusmv-users@fbk.eu>.

  To contact the NuSMV development board, email to <nusmv@fbk.eu>.

-----------------------------------------------------------------------------*/

/*!
  \author Nusmv Team
  \brief Parse-tree symbols set

  This file defines an enum containing all the core parse
  tree symbols set

*/



#ifndef __NUSMV_CORE_PARSER_SYMBOLS_H__
#define __NUSMV_CORE_PARSER_SYMBOLS_H__

enum NUSMV_CORE_SYMBOLS {
  NUSMV_CORE_SYMBOL_FIRST = 100,

  /* ---------------------------------------------------------------------- */
  NUSMV_STATEMENTS_SYMBOL_FIRST = NUSMV_CORE_SYMBOL_FIRST,

  TRANS,
  INIT,
  INVAR,
  ASSIGN,
  FAIRNESS,
  JUSTICE,
  COMPASSION,
  SPEC,
  LTLSPEC,
  PSLSPEC,
  INVARSPEC,
  COMPUTE,
  DEFINE,
  ISA,
  GOTO,
  CONSTRAINT,
  MODULE,
  PROCESS,
  MODTYPE,
  LAMBDA,
  CONSTANTS,

  /* To be moved to nuXmv */
  URGENT,
  PRED,
  ATTIME,
  PREDS_LIST,
  MIRROR,
  PSYNTH_PROB,
  KLTL_PROB,
  PLUS_INFINITY,

  /* End to be moved to nuXmv */

  DEFINE_PROPERTY,

  SYNTAX_ERROR,

  NUSMV_STATEMENTS_SYMBOL_LAST,
  /* ---------------------------------------------------------------------- */


  /* ---------------------------------------------------------------------- */
  NUSMV_EXPR_SYMBOL_FIRST,

  FAILURE,
  CONTEXT,
  EU,
  AU,
  EBU,
  ABU,
  MINU,
  MAXU,
  VAR,
  FROZENVAR,
  IVAR,
  BOOLEAN,
  CLOCK,
  NON_CONTINUOUS,
  ARRAY,
  SCALAR,
  CONS,
  BDD,
  SEMI,
  EQDEF,
  TWODOTS,
  FALSEEXP,
  TRUEEXP,
  SELF,
  CASE,
  COLON,
  IFTHENELSE,
  SIMPWFF,
  NEXTWFF,
  LTLWFF,
  CTLWFF,
  COMPWFF,
  ATOM,
  NUMBER,
  COMMA,
  IMPLIES,
  IFF,
  OR,
  XOR,
  XNOR,
  AND,
  NOT,
  EX,
  AX,
  EF,
  AF,
  EG,
  AG,
  SINCE,
  BOUNDED_SINCE,
  UNTIL,
  BOUNDED_UNTIL,
  TRIGGERED,
  BOUNDED_TRIGGERED,
  RELEASES,
  BOUNDED_RELEASES,
  EBF,
  EBG,
  ABF,
  ABG,
  OP_NEXT,
  OP_GLOBAL,
  OP_FUTURE,
  OP_PREC,
  OP_NOTPRECNOT,
  OP_HISTORICAL,
  OP_ONCE,
  EQUAL,
  NOTEQUAL,
  LT,
  GT,
  LE,
  GE,
  UNION,
  SETIN,
  MOD,
  PLUS,
  MINUS,
  TIMES,
  DIVIDE,
  UMINUS,
  NEXT,
  SMALLINIT,
  DOT,
  BIT,
  RANGE,
  UNSIGNED_WORD, /* identifies expressions and types */
  SIGNED_WORD,   /* identifies types */
  INTEGER,
  REAL,
  CONTINUOUS,
  NUMBER_UNSIGNED_WORD, /* identifies constants */
  NUMBER_SIGNED_WORD,   /* identifies constants */
  NUMBER_FRAC,
  NUMBER_REAL,
  NUMBER_EXP,
  LSHIFT,
  RSHIFT,
  LROTATE,
  RROTATE,
  BIT_SELECTION,
  CONCATENATION,
  CAST_BOOL,
  CAST_WORD1,
  CAST_SIGNED,
  CAST_UNSIGNED,
  EXTEND, /* extend the width of a word (signed or unsigned) */
  WORDARRAY,
  WAREAD,
  WAWRITE,
  UWCONST, /* these are removed by the flattener, so */
  SWCONST, /* after flattening they do not exist anywhere */
  WRESIZE,
  WSIZEOF,
  CAST_TOINT,

  COMPID, /* Used for comparing properties ids */

  ARRAY_TYPE, /* Used to represent generic array type */
  ARRAY_DEF,  /* Define obtained via Matrix-Define */

  NFUNCTION,
  NFUNCTION_TYPE, 
  FUN,

  COUNT,
  FLOOR,

  ITYPE, /* used to represent an internal type as read from the parser */

  WORDARRAY_TYPE, /* Represent generic array type with word indices */
  INTERNAL_ARRAY_STRUCT, /* Internal representation of the array structure
                    for processing the write function of arrays */
  CONST_ARRAY, /* Constant array */
  INTARRAY,
  INTARRAY_TYPE, /* Represent generic array type with integer indices */
  TYPEOF, /* function for returning the type of variable */

  CAST_TO_UNSIGNED_WORD, /* integer to bv conversion */

  /* to be moved in nuXmv */
  TIME,
   /* time_until and time_since are allowed only in timed models,
     during the untiming they are translated into at_next and at_last */
  TIME_UNTIL,
  TIME_SINCE,

  OP_TIMED_NEXT,
  OP_TIMED_PREC,

  /* End to be moved in nuXmv */

  NUSMV_EXPR_SYMBOL_LAST, 
  /* ---------------------------------------------------------------------- */

  NUSMV_CORE_SYMBOL_LAST,  

};


#endif /* __NUSMV_CORE_PARSER_SYMBOLS_H__ */
