
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
   \brief Public interface of class 'MasterCompilePredicateNormaliser'

   

   \sa MasterCompilePredicateNormaliser.c
*/


#ifndef __NUSMV_CORE_COMPILE_PNE_MASTER_COMPILE_PREDICATE_NORMALISER_H__
#define __NUSMV_CORE_COMPILE_PNE_MASTER_COMPILE_PREDICATE_NORMALISER_H__


#include "nusmv/core/utils/defs.h"
#include "nusmv/core/cinit/NuSMVEnv.h"
#include "nusmv/core/node/NodeMgr.h"
#include "nusmv/core/set/set.h"
#include "nusmv/core/compile/symb_table/SymbTable.h"

/*!
  \struct MasterCompilePredicateNormaliser
  \brief Definition of the public accessor for class MasterCompilePredicateNormaliser
*/
typedef struct MasterCompilePredicateNormaliser_TAG*  MasterCompilePredicateNormaliser_ptr;
typedef struct MasterCompilePredicateNormaliserSupport_TAG*  MasterCompilePredicateNormaliserSupport_ptr;


/*!
  \brief To cast and check instances of class MasterCompilePredicateNormaliser

  These macros must be used respectively to cast and to check
  instances of class MasterCompilePredicateNormaliser

*/
#define MASTER_COMPILE_PREDICATE_NORMALISER(self) \
         ((MasterCompilePredicateNormaliser_ptr) self)

#define MASTER_COMPILE_PREDICATE_NORMALISER_CHECK_INSTANCE(self) \
         (nusmv_assert(MASTER_COMPILE_PREDICATE_NORMALISER(self) != MASTER_COMPILE_PREDICATE_NORMALISER(NULL)))

#define MASTER_COMPILE_PREDICATE_NORMALISER_CORE_WALKERS "PredicateNormaliserCoreWalkers"



/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \methodof MasterCompilePredicateNormaliser
  \brief The MasterCompilePredicateNormaliser class constructor

  The MasterCompilePredicateNormaliser class constructor

  \sa MasterCompilePredicateNormaliser_destroy
*/
MasterCompilePredicateNormaliser_ptr MasterCompilePredicateNormaliser_create (SymbTable_ptr st);


/*!
  \methodof MasterCompilePredicateNormaliser
  \brief The MasterCompilePredicateNormaliser class destructor

  The MasterCompilePredicateNormaliser class destructor

  \sa MasterCompilePredicateNormaliser_create
*/
void MasterCompilePredicateNormaliser_destroy (MasterCompilePredicateNormaliser_ptr self);

/*!
  \methodof MasterCompilePredicateNormaliser

  Ininitialization of MasterCompilePredicateNormaliserSupport structure
*/
void
MasterCompilePredicateNormaliser_support_init(MasterCompilePredicateNormaliser_ptr self,
                                              SymbTable_ptr st);

/*!
  \methodof MasterCompilePredicateNormaliser

  Deininitialization of MasterCompilePredicateNormaliserSupport structure
*/
void
MasterCompilePredicateNormaliser_support_deinit(MasterCompilePredicateNormaliser_ptr self);

/*!
  \methodof MasterCompilePredicateNormaliser
  \brief The function performs predicate-normalisation of
   a generic boolean expression. It is possibile
   to set if is necessary to expand or not.

*/
node_ptr
MasterCompilePredicateNormaliser_normalise_expr(MasterCompilePredicateNormaliser_ptr self,
                                                node_ptr expr,
                                                boolean expand);

/*!
  \methodof PredicateNormaliser
  \brief The function performs predicate-normalisation of
   specification (SPEC, LTLSPEC, etc)

  This function does the same things as
   PredicateNormaliser_normalise_expr, except that the input expression
   must be a specification (such expression are returned by Prop_get_expr_core)

*/
node_ptr
MasterCompilePredicateNormaliser_normalise_specification(MasterCompilePredicateNormaliser_ptr self,
                                                         node_ptr expr);

/*!
  \methodof MasterCompilePredicateNormaliser
  \brief The function adds to the given set the expression's
   predicates, i.e. subexpressions which have not-boolean operands.

*/
void
MasterCompilePredicateNormaliser_get_predicates_only(const MasterCompilePredicateNormaliser_ptr self,
                                                     Set_t* preds, node_ptr expr);

/*!
  \methodof MasterCompilePredicateNormaliser
  \brief The function prints out the expressions's
   predicates, i.e. subexpressions which
   have not-boolean operands.

*/
void
MasterCompilePredicateNormaliser_print_predicates_only(const MasterCompilePredicateNormaliser_ptr self,
                                                       FILE* stream, node_ptr expr);

#endif /* __NUSMV_CORE_COMPILE_PNE_MASTER_COMPILE_PREDICATE_NORMALISER_NORMALISER_H__ */
