/* ---------------------------------------------------------------------------

  This file is part of the ``compile.pne'' package of NuSMV version 2.
  Copyright (C) 2014 by FBK-irst.

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
   \author Andrei Tchaltsev
   \brief Private and protected interface of class 'PredicateNormaliserCore'

   (Implementation of modularity by Elia Rigo)

   This file can be included only by derived and friend classes

   \sa PredicateNormaliserCore.h
*/


#ifndef __NUSMV_CORE_COMPILE_PNE_PREDICATE_NORMALISER_CORE_PRIVATE_H__
#define __NUSMV_CORE_COMPILE_PNE_PREDICATE_NORMALISER_CORE_PRIVATE_H__


#include "nusmv/core/compile/pne/PredicateNormaliserBase.h"
#include "nusmv/core/compile/pne/PredicateNormaliserCore.h"
#include "nusmv/core/compile/pne/PredicateNormaliserBase_private.h"

#include "nusmv/core/utils/defs.h"

/* name used to register PredicateNormaliserCore walker */
#define PREDICATE_NORMALISER_CORE_NAME "Predicate Normaliser core"

/*!
  \brief PredicateNormaliserCore class definition derived from
         class PredicateNormaliserBase



  \sa Base class PredicateNormaliserBase
*/

typedef PredicateNormaliserCore_ptr(*typeFunctionPredicateNormaliserCreate)(NuSMVEnv_ptr,
                                                                            const char*);

/*!
  \struct PredicateNormaliserCore
  \brief Definition of the private accessor for class PredicateNormaliserCoreSupport
*/
typedef struct PredicateNormaliserCoreWalker_TAG* PredicateNormaliserCoreWalker_ptr;

typedef struct PredicateNormaliserCore_TAG
{
  /* this MUST stay on the top */
  INHERITS_FROM(PredicateNormaliserBase);

  /* -------------------------------------------------- */
  /*                  Private members                   */
  /* -------------------------------------------------- */

  /* -------------------------------------------------- */
  /*                  Virtual methods                   */
  /* -------------------------------------------------- */

} PredicateNormaliserCore;

typedef struct PredicateNormaliserCoreWalker_TAG
{
  char* pncw_name;
  typeFunctionPredicateNormaliserCreate pncw_function_create;
} PredicateNormaliserCoreWalker;

/* ---------------------------------------------------------------------- */
/* Private methods to be used by derivated and friend classes only         */
/* ---------------------------------------------------------------------- */
/*!
  \methodof PredicateNormaliserCore
  \brief The PredicateNormaliserCore class private initializer

  The PredicateNormaliserCore class private initializer

  \sa PredicateNormaliserCore_create
*/
void predicate_normaliser_core_init (PredicateNormaliserCore_ptr self,
                                     const NuSMVEnv_ptr env, const char* name,
                                     int low, size_t num, boolean can_handle_null);


/*!
  \methodof PredicateNormaliserCore
  \brief The PredicateNormaliserCore class private deinitializer

  The PredicateNormaliserCore class private deinitializer

  \sa PredicateNormaliserCore_destroy
*/
void predicate_normaliser_core_deinit (PredicateNormaliserCore_ptr self);


/*!
  \brief Performs the predicate-normalisation of an expression

  See predicate_normaliser_core_normalise_expr
   for more info on predicate-normalisation.
   This function is the main part of normalisation.

   NB for developers: the main idea behind this function is that
   if a not-boolean operation is applied (to one or two not-boolean operands),
   then ITE from operands must be pushed up to the root of the expression.
   For example,
   "case a : 3; true : 5; esac + 400"
   is converted to
   "case a : 3 + 400; true : 5 + 400; esac"
   i.e. after convertion not-boolean operand will not have ITE, and
   therefore will not have boolean subexpression.

   Boolean expressions are not changed since boolean expressions
   may have any subexpression.


  \sa predicate_normaliser_core_normalise_expr
*/
node_ptr
predicate_normaliser_core_normalise_expr(PredicateNormaliserBase_ptr self,
                                         MasterCompilePredicateNormaliserSupport_ptr support,
                                         node_ptr expr,
                                         node_ptr context,
                                         boolean expand);

/*!
  \methodof PredicateNormaliserCore
  \brief The function performs predicate-normalisation of
   specification (SPEC, LTLSPEC, etc)


*/
node_ptr
predicate_normaliser_core_normalise_specification(PredicateNormaliserBase_ptr self,
                                                  MasterCompilePredicateNormaliserSupport_ptr support,
                                                  node_ptr expr);
/*!
  \methodof PredicateNormaliserCore
  \brief The function adds to the given set the expression's
   predicates, i.e. subexpressions which have not-boolean operands.


*/
void
predicate_normaliser_core_get_predicates_only(const PredicateNormaliserBase_ptr self,
                                              MasterCompilePredicateNormaliserSupport_ptr support,
                                              Set_t* preds, node_ptr expr);

#endif /* __NUSMV_CORE_COMPILE_PNE_PREDICATE_NORMALISER_CORE_PRIVATE_H__ */
