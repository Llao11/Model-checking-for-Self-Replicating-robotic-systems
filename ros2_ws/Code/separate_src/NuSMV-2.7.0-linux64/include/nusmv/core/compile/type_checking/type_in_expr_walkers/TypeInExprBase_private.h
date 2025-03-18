/* ---------------------------------------------------------------------------


  This file is part of the ``compile.type_checking.checkers'' package
  of NuSMV version 2. Copyright (C) 2006 by FBK-irst.

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
  \author Enrico Magnago
  \brief Private and protected interface of class 'TypeInExprBase'

  This file can be included only by derived and friend classes

*/



#ifndef NUSMV_CORE_COMPILE_TYPE_CHECKING_TYPE_IN_EXPR_WALKERS_TYPE_IN_EXPR_BASE_PRIVATE_H__
#define NUSMV_CORE_COMPILE_TYPE_CHECKING_TYPE_IN_EXPR_WALKERS_TYPE_IN_EXPR_BASE_PRIVATE_H__


#include "nusmv/core/compile/type_checking/type_in_expr_walkers/TypeInExprBase.h"

#include "nusmv/core/compile/type_checking/TypeChecker.h"
#include "nusmv/core/compile/type_checking/TypeChecker_private.h"


#include "nusmv/core/node/NodeWalker_private.h"

/*!
  \brief Short way of calling type_checking_find_type_in_expr

  Use this macro to recursively recall
  type_checking_find_type_in_expr. Must be used from within a method. This
  can be used when expressions that are node_ptr
*/

#define _THROW(self, exp, ctx, type)                                    \
  (NodeWalker_can_handle(NODE_WALKER(self), exp) ?                      \
   TYPE_IN_EXPR_BASE(self)->find_type_in_expr(self, exp, ctx, type) :   \
   TypeChecker_find_type_in_expr(self->type_checker, exp, ctx, type))

/*!
  \brief TypeInExprBase class definition derived from
               class node.NodeWalker

  \sa Base class NodeWalker
*/

typedef struct TypeInExprBase_TAG
{
  /* this MUST stay on the top */
  INHERITS_FROM(NodeWalker);

  /* -------------------------------------------------- */
  /*                  Private members                   */
  /* -------------------------------------------------- */

  TypeChecker_ptr type_checker;

  /* -------------------------------------------------- */
  /*                  Virtual methods                   */
  /* -------------------------------------------------- */

  node_ptr (*find_type_in_expr)(const TypeInExprBase_ptr self,
                                const node_ptr exp,
                                const node_ptr ctx,
                                const SymbType_ptr type);

} TypeInExprBase;



/* ---------------------------------------------------------------------- */
/* Private methods to be used by derivated and friend classes only         */
/* ---------------------------------------------------------------------- */

/*!
  \methodof TypeInExprBase
  \brief The TypeInExprBase class private initializer

  The TypeInExprBase class private initializer

  \sa type_in_expr_base_deinit
*/
void
type_in_expr_base_init(const TypeInExprBase_ptr self,
                       const TypeChecker_ptr type_checker,
                       const char* name, const int low, const size_t num,
                       const boolean can_handle_null);

/*!
  \methodof TypeInExprBase
  \brief The TypeInExprBase class private deinitializer

  The TypeInExprBase class private deinitializer

  \sa TypeInExprBase_destroy, type_in_expr_base_init
*/
void type_in_expr_base_deinit(TypeInExprBase_ptr self);

/*!
  \methodof TypeInExprBase
  \brief The TypeInExprBase class copy constructor

  The TypeInExprBase class private copy constructor.

  Important: copied master will be not registered to any master, and
  will have to be explicitly registered.

  \sa Object_copy, node_walker_copy_aux
*/
void type_in_expr_base_copy_aux(const TypeInExprBase_ptr self,
                                TypeInExprBase_ptr other);

/*!
  \methodof TypeInExprBase
  \brief raise error: unhandled node.
 */
node_ptr type_in_expr_base_find_type_in_expr(const TypeInExprBase_ptr self,
                                             const node_ptr exp,
                                             const node_ptr ctx,
                                             const SymbType_ptr type);

/*!
  \methodof TypeInExprBase
  \brief returns the type checker.
*/
TypeChecker_ptr type_in_expr_base_get_type_checker(const TypeInExprBase_ptr self);



#endif /* NUSMV_CORE_COMPILE_TYPE_CHECKING_TYPE_IN_EXPR_WALKERS_TYPE_IN_EXPR_BASE_PRIVATE_H__ */
