
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
   \brief Private and protected interface of class 'MasterCompilePredicateNormaliser'

   This file can be included only by derived and friend classes

   \sa MasterCompilePredicateNormaliser.h
*/


#ifndef __NUSMV_CORE_COMPILE_PNE_MASTER_COMPILE_PREDICATE_NORMALISER_PRIVATE_H__
#define __NUSMV_CORE_COMPILE_PNE_MASTER_COMPILE_PREDICATE_NORMALISER_PRIVATE_H__


#include "nusmv/core/compile/pne/MasterCompilePredicateNormaliser.h"
#include "nusmv/core/node/MasterNodeWalker.h"
#include "nusmv/core/node/MasterNodeWalker_private.h"
#include "nusmv/core/utils/defs.h"
#include "nusmv/core/set/set.h"
#include "nusmv/core/utils/utils.h"
#include "nusmv/core/utils/defs.h"
#include "nusmv/core/wff/ExprMgr.h"
#include "nusmv/core/utils/utils.h"
#include "nusmv/core/utils/WordNumberMgr.h"
#include "nusmv/core/compile/symb_table/SymbTable.h"


/*!
  \brief MasterCompilePredicateNormaliser class definition derived from
         class MasterCompilePredicateNormaliser

  

  \sa Base class MasterCompilePredicateNormaliser
*/
typedef struct MasterCompilePredicateNormaliser_TAG
{
  /* this MUST stay on the top */
  INHERITS_FROM(MasterNodeWalker);

  /* -------------------------------------------------- */
  /*                  Private members                   */
  /* -------------------------------------------------- */
  MasterCompilePredicateNormaliserSupport_ptr support_normaliser;

  /* -------------------------------------------------- */
  /*                  Virtual methods                   */
  /* -------------------------------------------------- */

} MasterCompilePredicateNormaliser;

typedef struct MasterCompilePredicateNormaliserSupport_TAG
{
  hash_ptr expr2normalisedPredicate; /* hash of
                                        expr -> predicate-normalised expr */
  TypeChecker_ptr checker; /* type-checker is used to get type info
                              of processed expressions and type check
                              generated expressions */
  SymbTable_ptr st;  /* the symbol table */
} MasterCompilePredicateNormaliserSupport;

/* ---------------------------------------------------------------------- */
/* Private methods to be used by derivated and friend classes only         */
/* ---------------------------------------------------------------------- */
/*!
  \methodof MasterCompilePredicateNormaliser
  \brief The MasterCompilePredicateNormaliser class private initializer

  The MasterCompilePredicateNormaliser class private initializer

  \sa MasterCompilePredicateNormaliser_create
*/
void master_compile_predicate_normaliser_init (MasterCompilePredicateNormaliser_ptr self,
									                             SymbTable_ptr st);


/*!
  \methodof MasterCompilePredicateNormaliser 
  \brief The MasterCompilePredicateNormaliser class private deinitializer

  The MasterCompilePredicateNormaliser class private deinitializer

  \sa MasterCompilePredicateNormaliser_destroy
*/
void master_compile_predicate_normaliser_deinit (MasterCompilePredicateNormaliser_ptr self);



#endif /* __NUSMV_CORE_COMPILE_PNE_MASTER_COMPILE_PREDICATE_NORMALISER_PRIVATE_H__ */
