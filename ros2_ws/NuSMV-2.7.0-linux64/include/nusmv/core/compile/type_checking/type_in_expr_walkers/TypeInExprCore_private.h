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
  \brief Private and protected interface of class 'TypeInExprCore'

  This file can be included only by derived and friend classes

*/



#ifndef NUSMV_CORE_COMPILE_TYPE_CHECKING_TYPE_IN_EXPR_WALKERS_TYPE_IN_EXPR_CORE_PRIVATE_H__
#define NUSMV_CORE_COMPILE_TYPE_CHECKING_TYPE_IN_EXPR_WALKERS_TYPE_IN_EXPR_CORE_PRIVATE_H__


#include "nusmv/core/compile/type_checking/type_in_expr_walkers/TypeInExprCore.h"
#include "nusmv/core/compile/type_checking/type_in_expr_walkers/TypeInExprBase_private.h"

#include "nusmv/core/utils/assoc.h"

/* name associated to the type_in_expr_code node walker */
#define TYPE_IN_EXPR_CORE_NAME "Type In Expr Core"

/*!
  \brief TypeInExprCore class definition derived from
               class TypeInExprBase

  \sa Base class TypeInExprBase
*/

typedef struct TypeInExprCore_TAG
{
  /* this MUST stay on the top */
  INHERITS_FROM(TypeInExprBase);

  /* -------------------------------------------------- */
  /*                  Private members                   */
  /* -------------------------------------------------- */

  hash_ptr cache;
  SymbType_ptr last_seach_type;
  node_ptr marker; /* node used as value in cache to signal that
                      the type is not contained into expression */

  /* -------------------------------------------------- */
  /*                  Virtual methods                   */
  /* -------------------------------------------------- */

} TypeInExprCore;



/* ---------------------------------------------------------------------- */
/* Private methods to be used by derivated and friend classes only         */
/* ---------------------------------------------------------------------- */

/*!
  \methodof TypeInExprCore
  \brief The TypeInExprCore class private initializer

  The TypeInExprCore class private initializer

  \sa type_in_expr_core_deinit
*/
void
type_in_expr_core_init(const TypeInExprCore_ptr self,
                       const TypeChecker_ptr type_checker,
                       const char* name, const int low, const size_t num,
                       const boolean can_handle_null);

/*!
  \methodof TypeInExprCore
  \brief The TypeInExprCore class private deinitializer

  The TypeInExprCore class private deinitializer

  \sa TypeInExprCore_destroy, type_in_expr_core_init
*/
void type_in_expr_core_deinit(TypeInExprCore_ptr self);

/*!
  \methodof TypeInExprCore
  \brief The TypeInExprCore class copy constructor

  The TypeInExprCore class private copy constructor.

  Important: copied master will be not registered to any master, and
  will have to be explicitly registered.

  \sa Object_copy, node_walker_copy_aux
*/
void type_in_expr_core_copy_aux(const TypeInExprCore_ptr self,
                                TypeInExprCore_ptr other);

/*!
  \methodof TypeInExprCore
  \brief implementation of virtual method find_type_in_expr
 */
node_ptr type_in_expr_core_find_type_in_expr(const TypeInExprBase_ptr self,
                                             const node_ptr exp,
                                             const node_ptr ctx,
                                             const SymbType_ptr type);

/*!
  \methodof TypeInExprCore
  \brief Return true iff the given node is equal to the marker node.

  The marker node is a special internal node used in the cache to signal
  that the expression used as key does not contain a sub-expression
  of the desired type.
*/
boolean type_in_expr_core_is_marker(const TypeInExprCore_ptr self,
                                    const node_ptr node);

#endif /* NUSMV_CORE_COMPILE_TYPE_CHECKING_TYPE_IN_EXPR_WALKERS_TYPE_IN_EXPR_CORE_PRIVATE_H__ */
