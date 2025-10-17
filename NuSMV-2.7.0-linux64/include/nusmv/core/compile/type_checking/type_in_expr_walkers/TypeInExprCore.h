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
  \author Enrico Magnago
  \brief Public interface of class 'TypeInExprCore'

  Find and return a sub-expression of the given type.
  If no such sub-expression exists, Nil is returned.
*/

#ifndef NUSMV_CORE_COMPILE_TYPE_CHECKING_TYPE_IN_EXPR_WALKERS_TYPE_IN_EXPR_CORE_H__
#define NUSMV_CORE_COMPILE_TYPE_CHECKING_TYPE_IN_EXPR_WALKERS_TYPE_IN_EXPR_CORE_H__

#include "nusmv/core/cinit/NuSMVEnv.h"
#include "nusmv/core/node/NodeMgr.h"
#include "nusmv/core/compile/symb_table/SymbType.h"
#include "nusmv/core/compile/type_checking/TypeChecker.h"

/*!
  \struct TypeInExprCore
  \brief Definition of the public accessor for class TypeInExprCore


*/
typedef struct TypeInExprCore_TAG*  TypeInExprCore_ptr;

/*!
  \brief To cast instances of class TypeInExprCore

  This macro must be used to cast instances of class TypeInExprCore
*/
#define TYPE_IN_EXPR_CORE(self) \
         ((TypeInExprCore_ptr) self)

/*!
   \brief To check instances of class TypeInExprCore

   This macro must be used to check instances of class TypeInExprCore
*/
#define TYPE_IN_EXPR_CORE_CHECK_INSTANCE(self) \
         (nusmv_assert(TYPE_IN_EXPR_CORE(self) != TYPE_IN_EXPR_CORE(NULL)))



/**AutomaticStart*************************************************************/

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \methodof TypeInExprCore
  \brief The TypeInExprCore class constructor

  The TypeInExprCore class constructor

  \sa TypeInExprBase_destroy
*/
TypeInExprCore_ptr TypeInExprCore_create(const TypeChecker_ptr type_checker);

/*!
  \methodof TypeInExprCore
  \brief The TypeInExprCore class de-constructor

*/
void TypeInExprCore_destroy(TypeInExprCore_ptr self);


/**AutomaticEnd***************************************************************/



#endif /* NUSMV_CORE_COMPILE_TYPE_CHECKING_TYPE_IN_EXPR_WALKERS_TYPE_IN_EXPR_CORE_H__ */
