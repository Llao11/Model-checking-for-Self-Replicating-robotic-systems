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
  \brief Private and protected interface of class 'CheckerCore'

  This file can be included only by derived and friend classes

*/



#ifndef __NUSMV_CORE_COMPILE_TYPE_CHECKING_CHECKERS_CHECKER_CORE_PRIVATE_H__
#define __NUSMV_CORE_COMPILE_TYPE_CHECKING_CHECKERS_CHECKER_CORE_PRIVATE_H__

#include "nusmv/core/compile/type_checking/checkers/CheckerCore.h"

#include "nusmv/core/compile/type_checking/checkers/CheckerBase.h"
#include "nusmv/core/compile/type_checking/checkers/CheckerBase_private.h"

#include "nusmv/core/utils/utils.h"

/* name associated to the checker_core node walker */
#define CHECKER_CORE_NAME "Core SMV Type Checker"

/*!
  \brief Short way of calling tc_set_expression_type

  Use this macro to set an expression type within the
  master type checker. Must be used from within a method. This
  can be used when expressions that are node_ptr
*/

#define _SET_TYPE(expr, type) \
   tc_set_expression_type(TYPE_CHECKER(NODE_WALKER(self)->master), expr, type)


/*!
  \brief Short way of calling tc_lookup_expr_type

  Use this macro to get an expression type from the
  master type checker. Must be used from within a method. This
  can be used when expressions that are node_ptr
*/

#define _GET_TYPE(expr) \
   tc_lookup_expr_type(TYPE_CHECKER(NODE_WALKER(self)->master), expr)


/*!
  \brief Short way of calling checker_base_manage_violation

  Use this macro to manage a violation at the master
  type checker level. Must be used from within a method. This
  can be used when expressions that are node_ptr
*/

#define _VIOLATION(viol_id, expr) \
   checker_base_manage_violation(CHECKER_BASE(self), viol_id, expr)



/*!
  \brief Short way of calling type_checker_print_error_message

  Use this macro to recursively call
  type_checking_check_expression into violation handlers. This
  can be used when expressions that are node_ptr
*/

#define _PRINT_ERROR_MSG(exp, is_error)                                      \
   type_checker_print_error_message(TYPE_CHECKER(NODE_WALKER(self)->master), \
                                 exp, is_error)




/*!
  \brief CheckerCore class definition derived from
               class CheckerBase



  \sa Base class CheckerBase
*/

typedef struct CheckerCore_TAG
{
  /* this MUST stay on the top */
  INHERITS_FROM(CheckerBase);

  /* -------------------------------------------------- */
  /*                  Private members                   */
  /* -------------------------------------------------- */


  /* -------------------------------------------------- */
  /*                  Virtual methods                   */
  /* -------------------------------------------------- */

} CheckerCore;



/* ---------------------------------------------------------------------- */
/* Private methods to be used by derivated and friend classes only         */
/* ---------------------------------------------------------------------- */

/*!
  \methodof CheckerCore
  \brief The CheckerCore class private initializer

  The CheckerCore class private initializer

  \sa CheckerCore_create
*/
void checker_core_init(CheckerCore_ptr self, const NuSMVEnv_ptr env,
                       const char* name, int low, size_t num);

/*!
  \methodof CheckerCore
  \brief The CheckerCore class private deinitializer

  The CheckerCore class private deinitializer
*/
void checker_core_deinit(CheckerCore_ptr self);

/*!
  \methodof CheckerCore
  \brief performs type checking and returns type of expression

*/
SymbType_ptr checker_core_check_expr(CheckerBase_ptr self,
                                     node_ptr expr, node_ptr context);

/*!
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
   TC_VIOLATION_TYPE_BACK_COMP and the system variable
   "type_checking_backward_compatibility" is true. Also the
   TC_VIOLATION_TYPE_WARNING violation outputs a warning. Only in
   this case the false value is returned, indicating that this is NOT
   an error. Otherwise the true value is returned, indicating that this
   is an error.

   Also, if the system variable "type_check_warning_on" is false,
   warning messages are not output.

   NB: if the expression is checked in some context (context is not null) then
   before providing the expression to this function the expression should be
   wrapped into context, i.e. with find_node(nodemgr, CONTEXT, context, expr)

  \sa TypeSystemViolation
*/
boolean
checker_core_viol_handler(CheckerBase_ptr self,
                          TypeSystemViolation violation, node_ptr expression);

/*!
  \brief prints an expression's operator to output_stream

  This function is the almost the same as
   print_sexp, except this function does not print the children of the node.
   The expr must be a correct expression.
   The function is used in printing of an error messages only.

  \se None
  \sa print_sexp
*/
void checker_core_print_operator(CheckerBase_ptr self, FILE* output_stream,
                                 node_ptr expr);

/*!
  \brief returns true if the given range is valid.
*/
boolean checker_core_check_range(const CheckerBase_ptr self,
                                 const node_ptr range);



#endif /* __NUSMV_CORE_COMPILE_TYPE_CHECKING_CHECKERS_CHECKER_CORE_PRIVATE_H__ */
