
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
   \brief Private and protected interface of class 'PredicateExtractorBase'

   This file can be included only by derived and friend classes

   \sa PredicateExtractorBase.h
*/


#ifndef __NUSMV_CORE_COMPILE_PNE_PREDICATE_EXTRACTOR_BASE_PRIVATE_H__
#define __NUSMV_CORE_COMPILE_PNE_PREDICATE_EXTRACTOR_BASE_PRIVATE_H__

#include "nusmv/core/compile/pne/MasterCompilePredicateExtractor_private.h"

#include "nusmv/core/compile/pne/PredicateExtractorBase.h"
#include "nusmv/core/node/NodeWalker.h"
#include "nusmv/core/node/NodeWalker_private.h"
#include "nusmv/core/utils/defs.h"
#include "nusmv/core/compile/symb_table/SymbTable.h"
#include "nusmv/core/parser/symbols.h"

/*!
  \brief PredicateExtractorBase class definition derived from
         class MasterNodeWalker

  

  \sa Base class MasterNodeWalker
*/
typedef struct PredicateExtractorBase_TAG
{
  /* this MUST stay on the top */
  INHERITS_FROM(NodeWalker);

  /* -------------------------------------------------- */
  /*                  Private members                   */
  /* -------------------------------------------------- */

  /* See MasterCompilePredicateExtractor.h for private 
     and shared members between PredicateExtractors     */

  /* -------------------------------------------------- */
  /*                  Virtual methods                   */
  /* -------------------------------------------------- */
  Set_t (*compute_preds) (PredicateExtractorBase_ptr self,
                          MasterCompilePredicateExtractorSupport_ptr support,
                          node_ptr expr,
                          node_ptr context);

} PredicateExtractorBase;

/*---------------------------------------------------------------------------*/
/* Macro declarations                                                        */
/*---------------------------------------------------------------------------*/

/*!
  \brief Short way of calling predicate_extractor_base_throw_compute_preds

  Use this macro to recursively recall the compute_preds function
*/
#undef _THROW
#define _THROW(support, expr, context)                                        \
  predicate_extractor_base_throw_compute_preds(PREDICATE_EXTRACTOR_BASE(self),\
                                               support, expr, context)

/* ---------------------------------------------------------------------- */
/* Private methods to be used by derivated and friend classes only         */
/* ---------------------------------------------------------------------- */

/*!
  \methodof PredicateExtractorBase
  \brief The constructor creates a predicate-extractor

  See PredicateExtractorBase.h for more info on
   predicates and clusters.  The parameter 'checker' is a type checker
   used during predicate extraction and subsequent type checking of
   generated expressions.

   Parameter use_approx can be used to make the extractor
   give up when dealing with too-large expressions. This is
   currently used by the heuristics which extract the variable
   ordering out of the fsm.

   NOTE that the type checker remembers the type of checked
   expressions (free or reuse nodes with care).
*/
PredicateExtractorBase_ptr PredicateExtractorBase_create (const NuSMVEnv_ptr env,
                                                          const char* name, 
                                                          int low, 
                                                          size_t num,
                                                          boolean can_handle_null);

/*!
  \methodof PredicateExtractorBase
  \brief The PredicateExtractorBase class private initializer

  The PredicateExtractorBase class private initializer

  \sa PredicateExtractorBase_create
*/
void predicate_extractor_base_init (PredicateExtractorBase_ptr self, 
                                    const NuSMVEnv_ptr env, const char* name, 
                                    int low, size_t num, boolean can_handle_null);

/*!
  \methodof PredicateExtractorBase 
  \brief The PredicateExtractorBase class private deinitializer

  The PredicateExtractorBase class private deinitializer

  \sa PredicateExtractorBase_destroy
*/
void predicate_extractor_base_deinit (PredicateExtractorBase_ptr self);

/*!
  \methodof PredicateExtractorBase
  \brief The PredicateExtractorBase class private destructor

  The PredicateExtractorBase class private destructor

  \sa PredicateExtractorBase_destroy
*/
void predicate_extractor_base_destroy (PredicateExtractorBase_ptr self);

/*!
  \methodof PredicateExtractorBase
  \brief The function computes and collects
   the predicates of a given expression


*/
Set_t 
predicate_extractor_base_compute_preds(PredicateExtractorBase_ptr self,
                                       MasterCompilePredicateExtractorSupport_ptr support,
                                       node_ptr expr,
                                       node_ptr context);

/*!
  \methodof PredicateNormaliserCore
  \brief _THROW of compute_preds

  
*/
Set_t 
predicate_extractor_base_throw_compute_preds(PredicateExtractorBase_ptr self,
                                             MasterCompilePredicateExtractorSupport_ptr support,
                                             node_ptr expr,
                                             node_ptr context);

#endif /* __NUSMV_CORE_COMPILE_PNE_PREDICATE_EXTRACTOR_BASE_PRIVATE_H__ */
