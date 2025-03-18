/* ---------------------------------------------------------------------------


  This file is part of the ``compile.type_checking'' package of NuSMV
  version 2. Copyright (C) 2006 by FBK-irst.

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
  \brief Private interface of class 'TypeChecker'

   This interface is part of the private relationship
  among the TypeChecker and the checkes it contains and controls.


*/



#ifndef __NUSMV_CORE_COMPILE_TYPE_CHECKING_TYPE_CHECKER_PRIVATE_H__
#define __NUSMV_CORE_COMPILE_TYPE_CHECKING_TYPE_CHECKER_PRIVATE_H__


#include "nusmv/core/compile/type_checking/TypeChecker.h"
#include "nusmv/core/compile/type_checking/type_checkingInt.h"
#include "nusmv/core/compile/symb_table/SymbType.h"
#include "nusmv/core/compile/symb_table/SymbTable.h"
#include "nusmv/core/node/MasterNodeWalker_private.h"
#include "nusmv/core/utils/utils.h"


typedef struct TypeChecker_TAG
{
  /* this MUST stay on the top */
  INHERITS_FROM(MasterNodeWalker);

  /* -------------------------------------------------- */
  /*                  Private members                   */
  /* -------------------------------------------------- */
  int memoizing_counter; /* if 0, memoizing is enabled */
  SymbTable_ptr symbolTable; /* symbol table to look for symbols */
  hash_ptr expressionTypeMapping; /* type of checked expression's */
  boolean freshly_cleared; /* Used to avoid calling more than once
                              clear_assoc, when invoked by the
                              trigger */

  MasterNodeWalker_ptr type_in_expr_walkers;

} TypeChecker;


/*!
  \methodof TypeChecker
  \brief The TypeChecker class copy constructor

  The TypeChecker class private copy constructor

  \sa Object_copy
*/
void type_checker_copy_aux(const TypeChecker_ptr self,
                           const TypeChecker_ptr other,
                           const SymbTable_ptr other_st);

/*!
  \brief Creates the association between an expression and
   its type, if memoizing is enabled

  There should be not existing associated type
   for a given expression.

   Note: if there is (not null) context then the expression
   must be wrapped into CONTEXT expression. For example,
   for an expression exp and not null context ctx, the
   expression provided for this function should be find_node(nodemgr, CONTEXT, ctx, exp).
   The expression should not be wrapped into Nil context.

  \sa tc_lookup_expr_type
*/
SymbType_ptr
tc_set_expression_type(TypeChecker_ptr self,
                 node_ptr expression, SymbType_ptr type);

/*!
  \brief Looks up the internal type memoizing for expression's type
   and returns the associated type, or nullType if the expression was not
   previously checked

  If memoizing is not enabled, nullType will always be
   returned

  \sa tc_set_expression_type
*/
SymbType_ptr
tc_lookup_expr_type(TypeChecker_ptr self, node_ptr expression);

/*!
  \methodof TypeChecker
  \brief Perform type checking of an expression, and returns its
   type

  This function is the core of the expression type
   checking.

   The expression may by unmodified (after compilation), flattened or
   flattened+expanded.

   The return value is the type of the expression.  If an expression
   violates the type system, the violation handler function is invoked
   and "error" type is returned (not NULL).



   NB: As it is said in TypeChecker.h, the expression type checking package
   uses only memory-shared types (SymbTablePkg_..._type).

   NB: This function does not perform the type checking on already
   checked expressions (even if they were erroneous), but just returns
   their types (possibly error-type). This avoids multiple error and warning
   messages for the same subexpression.

  \sa type_checking_violation_handler
*/
SymbType_ptr
type_checker_check_expression(TypeChecker_ptr self,
                    node_ptr expression, node_ptr context);

/*!
  \methodof TypeChecker
  \brief Prints whther an error or a warning message, depending on
   the given parameter

  This private funciont is called by violation handler
   into checkers and self, to print a uniform message when type errors
   and warnings occur
*/
void
type_checker_print_error_message(TypeChecker_ptr self,
                       node_ptr expr, boolean is_error);

/*!
  \methodof TypeChecker
  \brief Enables or disables internal type memoizing

  This method is used by checkers to temporary disable
   internal type memoizing that associates each sub-expression to its
   type.  This can be used to force an already checked formula to be
   re-checked.  For example the PSL checker while checking 'forall'
   expressions requires the repeated formula to be checked as many times as
   the id has a range of possible values.

   Important: memoizing is enabled by default and re-enabled every time
   the user calls the top level checking method. However, it is good
   behaviour for checkers to re-enable memoizing after disabling it
*/
void type_checker_enable_memoizing(TypeChecker_ptr self,
                        boolean enabled);

/*!
  \methodof TypeChecker
  \brief Returns true if memoizing is currently enabled, false
   otherwise


*/
boolean
type_checker_is_memoizing_enabled(const TypeChecker_ptr self);

/*!
  \methodof TypeChecker
  \brief The type checker violation handler.

   This violation handler outputs an error and warning message to
   errstream. A warning is output if the detected violation is
   TC_VIOLATION_DUPLICATE_CONSTANTS and
   the system variable "type_checking_backward_compatibility" is
   true. Only in this case the false value is returned, indicating that
   this is NOT an error. Otherwise the true value is returned,
   indicating that this is an error.

   Also, if the system variable "type_check_warning_on" is false,
   warning messages are not output.

   NB: if the expression is checked in some context (context is not null) then
   before providing the expression to this function the expression should be
   wrapped into context, i.e. with find_node(nodemgr, CONEXT, context, expr)

  \sa TypeSystemViolation
*/
boolean type_checker_viol_handler(TypeChecker_ptr self,
                                  TypeSystemViolation violation,
                                  node_ptr expression);

/*!
  \methodof TypeChecker
  \brief returns a pointer to the internal master node walker

  returns a pointer to the internal master node walker for type in expr walkers.
*/
MasterNodeWalker_ptr
type_checker_get_type_in_expr_walkers(const TypeChecker_ptr self);

#endif /* __NUSMV_CORE_COMPILE_TYPE_CHECKING_TYPE_CHECKER_PRIVATE_H__ */
