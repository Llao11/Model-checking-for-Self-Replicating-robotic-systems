
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
   \author Elia Rigo
   \brief Private and protected interface of class 'PredicateNormaliserBase'

   This file can be included only by derived and friend classes

   \sa PredicateNormaliserBase.h
*/


#ifndef __NUSMV_CORE_COMPILE_PNE_PREDICATE_NORMALISER_BASE_PRIVATE_H__
#define __NUSMV_CORE_COMPILE_PNE_PREDICATE_NORMALISER_BASE_PRIVATE_H__

#include "nusmv/core/compile/pne/MasterCompilePredicateNormaliser.h"
#include "nusmv/core/compile/pne/PredicateNormaliserBase.h"

#include "nusmv/core/compile/symb_table/SymbTable.h"
#include "nusmv/core/compile/type_checking/TypeChecker.h"
#include "nusmv/core/node/NodeWalker.h"
#include "nusmv/core/node/NodeWalker_private.h"
#include "nusmv/core/utils/assoc.h"
#include "nusmv/core/utils/defs.h"


/*!
  \brief PredicateNormaliserBase class definition derived from
         class PredicateNormaliserBase

  

  \sa Base class PredicateNormaliserBase
*/
typedef struct PredicateNormaliserBase_TAG
{
  /* this MUST stay on the top */
  INHERITS_FROM(NodeWalker);

  /* -------------------------------------------------- */
  /*                  Private members                   */
  /* -------------------------------------------------- */
  
  /* -------------------------------------------------- */
  /*                  Virtual methods                   */
  /* -------------------------------------------------- */
  node_ptr (*normalise_expr) (PredicateNormaliserBase_ptr self,
                              MasterCompilePredicateNormaliserSupport_ptr support,
                              node_ptr expr,
                              node_ptr context,
                              boolean expand);

  node_ptr (*normalise_specification) (PredicateNormaliserBase_ptr self,
                                       MasterCompilePredicateNormaliserSupport_ptr support,
                                       node_ptr expr);

  void (*get_predicates_only) (const PredicateNormaliserBase_ptr self,
                               MasterCompilePredicateNormaliserSupport_ptr support,
                               Set_t* preds, node_ptr expr);
} PredicateNormaliserBase;

/*---------------------------------------------------------------------------*/
/* Macro declarations                                                        */
/*---------------------------------------------------------------------------*/

/*!
  \brief Short way of calling predicate_normaliser_base_throw_normalise_expr

  Use this macro to recursively recall the normalise_expr function
*/
#undef _THROW
#define _THROW(support, expr, context, expand)                                   \
  predicate_normaliser_base_throw_normalise_expr(PREDICATE_NORMALISER_BASE(self),\
                                                 support, expr, context, expand)

/*!
  \brief Short way of calling 
    predicate_normaliser_base_throw_get_predicates_only

  Use this macro to recursively recall the get_predicates_only function
*/

#define _THROW_GET_PREDS_ONLY(support, preds, expr, already_processed)                \
  predicate_normaliser_base_throw_get_predicates_only(PREDICATE_NORMALISER_BASE(self),\
                                                      support, preds, expr)

/* ---------------------------------------------------------------------- */
/* Private methods to be used by derivated and friend classes only         */
/* ---------------------------------------------------------------------- */

/*!
  \methodof PredicateNormaliserBase
  \brief The PredicateNormaliserBase class constructor

  The PredicateNormaliserBase class constructor

  \sa PredicateNormaliserBase_destroy
*/
PredicateNormaliserBase_ptr 
PredicateNormaliserBase_create (const NuSMVEnv_ptr env, const char* name, 
                                int low, size_t num, boolean can_handle_null);

/*!
  \methodof PredicateNormaliserBase
  \brief The PredicateNormaliserBase class private initializer

  The PredicateNormaliserBase class private initializer

  \sa PredicateNormaliserBase_create
*/
void 
predicate_normaliser_base_init (PredicateNormaliserBase_ptr self, 
                                const NuSMVEnv_ptr env, const char* name, 
                                int low, size_t num, boolean can_handle_null);

/*!
  \methodof PredicateNormaliserBase
  \brief The PredicateNormaliserBase class destructor

  The PredicateNormaliserBase class destructor

  \sa PredicateNormaliserBase_create
*/
void PredicateNormaliserBase_destroy (PredicateNormaliserBase_ptr self);

/*!
  \methodof PredicateNormaliserBase 
  \brief The PredicateNormaliserBase class private deinitializer

  The PredicateNormaliserBase class private deinitializer

  \sa PredicateNormaliserBase_destroy
*/
void predicate_normaliser_base_deinit (PredicateNormaliserBase_ptr self);

/*!
  \methodof PredicateNormaliserBase
  \brief The function performs predicate-normalisation of
   a generic boolean expression

  
*/
node_ptr 
predicate_normaliser_base_normalise_expr(PredicateNormaliserBase_ptr self,
                                         MasterCompilePredicateNormaliserSupport_ptr support,
                                         node_ptr expr,
                                         node_ptr context,
                                         boolean expand);

/*!
  \methodof PredicateNormaliserBase
  \brief The function performs predicate-normalisation of
   specification (SPEC, LTLSPEC, etc)

  
*/
node_ptr 
predicate_normaliser_base_normalise_specification(PredicateNormaliserBase_ptr self,
                                                  MasterCompilePredicateNormaliserSupport_ptr support,
                                                  node_ptr expr);

/*!
  \methodof PredicateNormaliserCore
  \brief The function adds to the given set the expression's
   predicates, i.e. subexpressions which have not-boolean operands.

  
*/
void
predicate_normaliser_base_get_predicates_only(const PredicateNormaliserBase_ptr self,
                                              MasterCompilePredicateNormaliserSupport_ptr support,
                                              Set_t* preds, node_ptr expr);

/*!
  \methodof PredicateNormaliserCore
  \brief The function adds to the given set the expression's
   predicates, i.e. subexpressions which have not-boolean operands.

  
*/
node_ptr 
predicate_normaliser_base_throw_normalise_expr(PredicateNormaliserBase_ptr self,
                                               MasterCompilePredicateNormaliserSupport_ptr support,
                                               node_ptr expr,
                                               node_ptr context,
                                               boolean expand);

/*!
  \methodof PredicateNormaliserCore
  \brief _THROW of get_predicates_only function

  
*/
void 
predicate_normaliser_base_throw_get_predicates_only(PredicateNormaliserBase_ptr self,
                                                    MasterCompilePredicateNormaliserSupport_ptr support,
                                                    Set_t* preds, node_ptr expr);
                                                    
#endif /* __NUSMV_CORE_COMPILE_PNE_PREDICATE_NORMALISER_BASE_PRIVATE_H__ */
