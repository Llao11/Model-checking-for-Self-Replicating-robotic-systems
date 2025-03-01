
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
   \brief Public interface of class 'MasterCompilePredicateExtractor'

   

   \sa MasterCompilePredicateExtractor.c
*/


#ifndef __NUSMV_CORE_COMPILE_PNE_MASTER_COMPILE_PREDICATE_EXTRACTOR_H__
#define __NUSMV_CORE_COMPILE_PNE_MASTER_COMPILE_PREDICATE_EXTRACTOR_H__

#include "nusmv/core/compile/pne/MasterCompilePredicateExtractor.h"
#include "nusmv/core/utils/defs.h"
#include "nusmv/core/cinit/NuSMVEnv.h"
#include "nusmv/core/compile/FlatHierarchy.h" /* for FlatHierarchy_ptr */


/*!
  \struct MasterCompilePredicateExtractor
  \brief Definition of the public accessor for class MasterCompilePredicateExtractor
*/
typedef struct MasterCompilePredicateExtractor_TAG*  MasterCompilePredicateExtractor_ptr;
typedef struct MasterCompilePredicateExtractorSupport_TAG*  MasterCompilePredicateExtractorSupport_ptr;


/*!
  \brief To cast and check instances of class MasterCompilePredicateExtractor

  These macros must be used respectively to cast and to check
  instances of class MasterCompilePredicateExtractor

*/
#define MASTER_COMPILE_PREDICATE_EXTRACTOR(self) \
         ((MasterCompilePredicateExtractor_ptr) self)

#define MASTER_COMPILE_PREDICATE_EXTRACTOR_CHECK_INSTANCE(self) \
         (nusmv_assert(MASTER_COMPILE_PREDICATE_EXTRACTOR(self) != MASTER_COMPILE_PREDICATE_EXTRACTOR(NULL)))

#define MASTER_COMPILE_PREDICATE_EXTRACTOR_CORE_WALKERS "PredicateExtractorCoreWalkers"



/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \methodof MasterCompilePredicateExtractor
  \brief The MasterCompilePredicateExtractor class constructor

  The MasterCompilePredicateExtractor class constructor

  \sa MasterCompilePredicateExtractor_create
*/
MasterCompilePredicateExtractor_ptr MasterCompilePredicateExtractor_create (SymbTable_ptr st,
                                                                            boolean use_approx);


/*!
  \methodof MasterCompilePredicateExtractor
  \brief The MasterCompilePredicateExtractor class destructor

  The MasterCompilePredicateExtractor class destructor

  \sa MasterCompilePredicateExtractor_destroy
*/
void MasterCompilePredicateExtractor_destroy (MasterCompilePredicateExtractor_ptr self);

/*!
  \methodof MasterCompilePredicateExtractor
  \brief Init MasterCompilePredicateExtractorSupport structure


*/
void 
MasterCompilePredicateExtractor_support_init(MasterCompilePredicateExtractor_ptr self,
                                             SymbTable_ptr st,
                                             boolean use_approx);

/*!
  \methodof MasterCompilePredicateExtractor
  \brief De init MasterCompilePredicateExtractorSupport structure


*/
void
MasterCompilePredicateExtractor_support_deinit(MasterCompilePredicateExtractor_ptr self);

/*!
  \methodof MasterCompilePredicateExtractor
  \brief The function computes and collects
   the predicates of a given expression

  
   See MasterCompilePredicateExtractor.h for more info on predicates and clusters.

   Note: that normalization of the input expression is not done.  Only
   predicates are computed (the lesser things are done the lesser
   time/memory is spent). See class PredicateNormaliser if
   predicate-normalized expressions are required.

   To additionally get/compute clusters
   MasterCompilePredicateExtractor_get_all_clusters can be used.

   Input expressions may/may not be expanded/normalized/flattened,
   whereas the collected predicates are flattened, expanded and
   created with find_node, in particular all identifiers fully
   resolved.

   WARNING: memoization is done. Providing the same expression a second
   times does not produce any additional predicate.

   Collected clusters/predicates are stored internally and can be
   obtained with MasterCompilePredicateExtractor_get_all_preds and
   MasterCompilePredicateExtractor_get_all_clusters.  
*/
Set_t
MasterCompilePredicateExtractor_compute_preds(MasterCompilePredicateExtractor_ptr self,
                                              node_ptr expr);

/*!
  \methodof MasterCompilePredicateExtractor
  \brief This function applies PredicateExtractorBase_compute_preds
   to every element of an hierarchy

  Note that symbol table in self has to correspond to
   the hierarchy, i.e. contains all the required symbols
*/
void
MasterCompilePredicateExtractor_compute_preds_from_hierarchy(MasterCompilePredicateExtractor_ptr self,
                                                             FlatHierarchy_ptr fh);

/*!
  \methodof MasterCompilePredicateExtractor
  \brief Returns the set of predicates computed so far

  Predicates are fully expanded and resolved expressions
   created with find_node, i.e. no freeing or modifications are allowed.
   Returned Set_t belongs to self.
*/
Set_t
MasterCompilePredicateExtractor_get_all_preds(const MasterCompilePredicateExtractor_ptr self);

/*!
  \methodof MasterCompilePredicateExtractor
  \brief Returns the set of clusters for all so far collected
   predicates

  This function computes and returns clusters for all so far
   computed predicates.

   Returned result is Set_t of Set_t of fully resolved variables.
   Everything returned belongs to self.

   Note that this function perform computation and may take some time
   (though intermediate results are remembered between calls).

   It is possible to get a group of predicates responsible for a given
   cluster with MasterCompilePredicateExtractor_get_preds_of_a_cluster.

   NOTE: subsequent call of MasterCompilePredicateExtractor_compute_preds makes any
   data returned by this function invalid.
*/
Set_t
MasterCompilePredicateExtractor_get_all_clusters(const MasterCompilePredicateExtractor_ptr self);

/*!
  \methodof MasterCompilePredicateExtractor
  \brief Given a fully resolved var name the function
   returns a cluster the variable belongs to

  If clusters were not computed before this function
   triggers the cluster computation.

   Returned result is Set_t of fully resolved variables.
   Everything returned belongs to self.

   If a var was not met in any of predicates then NULL is
   returned. (This is always so for boolean vars since boolean vars
   cannot be in predicates).

   NOTE: subsequent call of MasterCompilePredicateExtractor_compute_preds makes any
   data returned by this function invalid.
*/
Set_t
MasterCompilePredicateExtractor_get_var_cluster(const MasterCompilePredicateExtractor_ptr self,
                                                node_ptr var);

/*!
  \methodof MasterCompilePredicateExtractor
  \brief Returns a set of predicates responsible for a given cluster

  Given a cluster (Set_t of vars) returned by
   MasterCompilePredicateExtractor_get_all_clusters this function
   returns a set of predicates which caused the given cluster.

   Returned result is not-empty Set_t of fully expanded/resolved expressions
   and belongs to self.

   NOTE: subsequent call of MasterCompilePredicateExtractor_compute_preds makes any
   data returned by this function or
   MasterCompilePredicateExtractor_get_all_clusters invalid.
*/
Set_t MasterCompilePredicateExtractor_get_preds_of_a_cluster(const MasterCompilePredicateExtractor_ptr self,
                                                             Set_t cluster);

/*!
  \methodof MasterCompilePredicateExtractor
  \brief The function prints out the predicates collected so far
   and clusters computed.

  Options printPredicates and printClusters
   control what should be printed.
   At least one of them has to be set up.

   If only predicates are printed, then they are printed in the order
   they were obtained.

   Otherwise, clusters are printed and if additionally printPredicates
   is up then the after every cluster its predicates are printed.

   Note that if clusters were not computed so far but asked to be
   printed, they will be computed.
   
*/
void
MasterCompilePredicateExtractor_print(const MasterCompilePredicateExtractor_ptr self,
                                      FILE* stream,
                                      boolean printPredicates,
                                      boolean printClusters);

#endif /* __NUSMV_CORE_COMPILE_PNE_MASTER_COMPILE_PREDICATE_EXTRACTOR_H__ */
