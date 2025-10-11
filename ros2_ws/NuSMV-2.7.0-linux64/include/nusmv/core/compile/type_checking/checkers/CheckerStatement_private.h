/* ---------------------------------------------------------------------------


  This file is part of the ``compile.type_checking.checkers'' package of NuSMV version 2.
  Copyright (C) 2006 by FBK-irst.

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
  \author Roberto Cavada
  \brief Private and protected interface of class 'CheckerStatement'

  This file can be included only by derived and friend classes

*/



#ifndef __NUSMV_CORE_COMPILE_TYPE_CHECKING_CHECKERS_CHECKER_STATEMENT_PRIVATE_H__
#define __NUSMV_CORE_COMPILE_TYPE_CHECKING_CHECKERS_CHECKER_STATEMENT_PRIVATE_H__


#include "nusmv/core/compile/type_checking/checkers/CheckerStatement.h"

#include "nusmv/core/compile/type_checking/checkers/CheckerCore.h"
#include "nusmv/core/compile/type_checking/checkers/CheckerCore_private.h"

#include "nusmv/core/utils/utils.h"

/* name associated to the checker_statement node walker */
#define CHECKER_STATEMENT_NAME "Statements SMV Type Checker"

/*!
  \brief CheckerStatement class definition derived from
               class CheckerCore

  \sa Base class CheckerCore
*/

typedef struct CheckerStatement_TAG
{
  /* this MUST stay on the top */
  INHERITS_FROM(CheckerCore);

  /* -------------------------------------------------- */
  /*                  Private members                   */
  /* -------------------------------------------------- */
  boolean inside_attime; /* to check ATTIME is not nested */

  /* -------------------------------------------------- */
  /*                  Virtual methods                   */
  /* -------------------------------------------------- */

} CheckerStatement;



/* ---------------------------------------------------------------------- */
/* Private methods to be used by derivated and friend classes only         */
/* ---------------------------------------------------------------------- */

/*!
  \methodof CheckerStatement
  \brief The CheckerStatement class private initializer

  The CheckerStatement class private initializer

  \sa CheckerStatement_create
*/
void checker_statement_init(CheckerStatement_ptr self, const NuSMVEnv_ptr env,
                            const char* name, int low, size_t num);

/*!
  \methodof CheckerStatement
  \brief The CheckerStatement class private deinitializer

  The CheckerStatement class private deinitializer

  \sa CheckerStatement_destroy
*/
void checker_statement_deinit(CheckerStatement_ptr self);

/*!
  \methodof CheckerStatement
  \brief performs type checking and returns type of statement

*/
SymbType_ptr checker_statement_check_expr(CheckerBase_ptr self,
                                          node_ptr expression, node_ptr context);

/*!
  \methodof CheckerStatement
  \brief The type core violation handler.

  The violation handler is implemented as
  a virtual method, which is invoked by the checker when an expression
  being checked violates the type system.
  See the violation handler TypeCheckingViolationHandler_ptr
  for more explanations.

  The below function is the default violation handler, and a
  user can potentially define its own violation handler, by deriving
  a new class from this class and by overriding this virtual method.

  This violation handler outputs an error and warning message to
  errstream. A warning is output if the detected violation is
  TC_VIOLATION_TYPE_BACK_COMP or TC_VIOLATION_DUPLICATE_CONSTANTS and
  the system variable "type_checking_backward_compatibility" is
  true. Also the TC_VIOLATION_TYPE_WARNING violation outputs a
  warning. Only in this case the false value is returned, indicating
  that this is NOT an error. Otherwise the true value is returned,
  indicating that this is an error.

  Also, if the system variable "type_check_warning_on" is false,
  warning messages are not output.

  NB: if the expression is checked in some context (context is not null) then
  before providing the expression to this function the expression should be
  wrapped into context, i.e. with find_node(nodemgr, CONEXT, context, expr)

  \sa TypeSystemViolation
*/
boolean checker_statement_viol_handler(CheckerBase_ptr checker,
                                       TypeSystemViolation violation,
                                       node_ptr expression);

/*!
  \brief prints an expression's operator to output_stream

  This function is the almost the same as
  print_sexp, except this function does not print the children of the node.
  The expr must be a correct expression.
  The function is used in printing of an error messages only.

  \se None
  \sa print_sexp
*/
void checker_statement_print_operator(const CheckerBase_ptr self, FILE* output_stream,
                                      const node_ptr expr);




#endif /* __NUSMV_CORE_COMPILE_TYPE_CHECKING_CHECKERS_CHECKER_STATEMENT_PRIVATE_H__ */
