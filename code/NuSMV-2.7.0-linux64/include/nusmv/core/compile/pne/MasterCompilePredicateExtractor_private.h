
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
   \brief Private and protected interface of class 'MasterCompilePredicateExtractor'

   This file can be included only by derived and friend classes

   \sa MasterCompilePredicateExtractor.h
*/


#ifndef __NUSMV_CORE_COMPILE_PNE_MASTER_COMPILE_PREDICATE_EXTRACTOR_PRIVATE_H__
#define __NUSMV_CORE_COMPILE_PNE_MASTER_COMPILE_PREDICATE_EXTRACTOR_PRIVATE_H__

#include "nusmv/core/compile/pne/MasterCompilePredicateExtractor.h"

#include "nusmv/core/node/MasterNodeWalker.h"
#include "nusmv/core/node/MasterNodeWalker_private.h"
#include "nusmv/core/utils/defs.h"
#include "nusmv/core/utils/assoc.h"
#include "nusmv/core/cinit/NuSMVEnv.h"
#include "nusmv/core/set/set.h"
#include "nusmv/core/compile/symb_table/SymbTable.h"
#include "nusmv/core/compile/type_checking/TypeChecker.h"


/*!
  \brief MasterCompilePredicateExtractor class definition derived from
         class MasterNodeWalker

  

  \sa Base class MasterNodeWalker
*/

/*!
  \struct MasterCompilePredicateExtractor
  \brief Definition of the private accessor for class MasterCompilePredicateExtractorSupport
*/

typedef struct MasterCompilePredicateExtractor_TAG
{
  /* this MUST stay on the top */
  INHERITS_FROM(MasterNodeWalker);

  /* -------------------------------------------------- */
  /*                  Private members                   */
  /* -------------------------------------------------- */
  MasterCompilePredicateExtractorSupport_ptr support_extractor;

  /* -------------------------------------------------- */
  /*                  Virtual methods                   */
  /* -------------------------------------------------- */

} MasterCompilePredicateExtractor;

typedef struct MasterCompilePredicateExtractorSupport_TAG
{
  Set_t all_preds;   /* all predicates : Set_t of node_ptr */
  Set_t unclustered_preds;   /* subset of all_preds for which clusters
                                were not computed : Set_t of node_ptr */
  Set_t all_clusters;   /* all clusters : Set_t of Set_t of node_ptr.
                           This is the actual owner of all clusters.*/

  hash_ptr var2cluster; /* var -> cluster it belongs to. node_ptr -> Set_t */
  hash_ptr cluster2preds;   /* cluster -> its predicates. Owner of preds sets.
                               Set_t -> Set_t of node_ptr */

  hash_ptr expr2preds; /* node_ptr -> Set_t of node_ptr.  For
                          not-boolean expr the associated value is set
                          of subparts of predicates in it.  For
                          processed boolean expressions the associated
                          value is one of PREDICATES_TRUE (if the
                          expression can be simplified to constant
                          true), PREDICATES_FALSE (if expression can
                          be simplified to FALSE) or
                          PREDICATES_ARBITRARY (for all other cases).
                          This hash is the owner of preds sets.
                       */
  Set_t special_word_preds[3]; /* array of 3 special predicates subparts:
                                  {0d1_0}, {0d1_1}, and {0d1_0,0d1_1} */

  TypeChecker_ptr checker; /* type-checker is used to get type info
                              of processed expressions and type check
                              generated expressions */
  SymbTable_ptr st;  /* the symbol table */
  boolean use_approx; /* if over-approximation has to be used when
                         extracting predicates (see issue 1934) */
} MasterCompilePredicateExtractorSupport;

/* ---------------------------------------------------------------------- */
/* Private methods to be used by derivated and friend classes only         */
/* ---------------------------------------------------------------------- */
/*!
  \methodof MasterCompilePredicateExtractor
  \brief The MasterCompilePredicateExtractor class private initializer

  The MasterCompilePredicateExtractor class private initializer

  \sa MasterCompilePredicateExtractor_create
*/
void master_compile_predicate_extractor_init (MasterCompilePredicateExtractor_ptr self,
                                              SymbTable_ptr st,
                                              boolean use_approx);


/*!
  \methodof MasterCompilePredicateExtractor 
  \brief The MasterCompilePredicateExtractor class private deinitializer

  The MasterCompilePredicateExtractor class private deinitializer

  \sa MasterCompilePredicateExtractor_destroy
*/
void master_compile_predicate_extractor_deinit (MasterCompilePredicateExtractor_ptr self);



#endif /* __NUSMV_CORE_COMPILE_PNE_MASTER_COMPILE_PREDICATE_EXTRACTOR_PRIVATE_H__ */
