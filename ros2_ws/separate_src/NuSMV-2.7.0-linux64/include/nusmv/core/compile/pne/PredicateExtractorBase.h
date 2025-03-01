
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
  (Implementation of modularity by Elia Rigo)
  \brief Public interface for a predicate-extractor class

  The purpose of PredicateExtractor class is to extract predicates and
  clusters from expressions. This class is similar to
  PredicateNormaliser but does not normalize the whole input expressions,
  just create predicates and cluster.

  Thus if normalization of the input expression is not required it is
  more efficient to use this class.

  A few definitions:

  predicate -- is a boolean expression which have only scalar (not
    boolean) subexpressions. See PredicateNormaliser.h for more info about
    predicate normalization.

  cluster -- is a set of variables met in one predicates. If a
    variable is met in 2 different predicates then their clusters are
    united in one.  Implicitly, clusters divide predicates in groups,
    i.e. every group is a set of predicates that caused this cluster.

  Note that from the definitions both clusters and predicates can be
  only over scalar (not boolean) variables.

  This class allows computation of only predicate or both predicates
  and cluster.

  Initially, I ([AT]) tried to implement an option to compute clusters
  only without predicates but this did not work. The problem is that
  1) it is necessary to memoize the results, 2) clusters may disappear
  during computation (i.e. be merged with others). Because of 1) it is
  necessary to hash expr->clusters-in-it. Because of 2) it is
  necessary to hash cluster->expr-where-is-came-from and then any
  merge of clusters may require to update huge number of elements in
  the both above hashes.
  Right now a hash expr->predicate-subparts-in-it is created. This
  allows to get clusters through getting dependencies. Any other
  solution I through of was of about the same efficiency. Thus I
  decided to use the most straightforward one.



  This is a stand-alone class. This class needs only a type checker --
  to get the type of input expression and type check the generated
  (returned) expressions.

   \sa PredicateExtractorBase.c
*/


#ifndef __NUSMV_CORE_COMPILE_PNE_PREDICATE_EXTRACTOR_BASE_H__
#define __NUSMV_CORE_COMPILE_PNE_PREDICATE_EXTRACTOR_BASE_H__

#include "nusmv/core/compile/pne/MasterCompilePredicateExtractor_private.h"
#include "nusmv/core/node/MasterNodeWalker.h"
#include "nusmv/core/utils/defs.h"

/*---------------------------------------------------------------------------*/
/* Macro declarations                                                        */
/*---------------------------------------------------------------------------*/

/*!
  \brief These are special values to mark expressions
   which have been analyzed and which do not have predicate subparts

  Any boolean expression cannot have predicate subparts because
   boolean may have only complete predicates, not its subparts.
   Apparently, only not-boolean operation expressions may have
   predicates subparts.  These values are used in self->support_extractor->expr2preds
   hash.
   For better optimizations simplifications 3 values are introduced:
   PREDICATES_TRUE -- represent a set of predicates, consisting of {TRUE} only.
   PREDICATES_FALSE -- represent a set of predicates, consisting of {FALSE} only.
   PREDICATES_ARBITRARY -- represent arbitrary set of predicates.

   PREDICATES_OVERAPPROX -- represent approximanted value (to give
   up the extraction)

*/
#define PREDICATES_TRUE ((Set_t)1)

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define PREDICATES_FALSE ((Set_t)2)

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define PREDICATES_ARBITRARY ((Set_t)3)

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define PREDICATES_OVERAPPROX ((Set_t)4)

/*!
  \brief The threshold used when deciding whether over approximate
   or not the predicate extraction


*/
#define OVER_APPROX_THRESHOLD 600000


/* below macro is TRUE iff the set is not an actually a Set_t,
   i.e. it is a valide predicate constant or the constant
   indicating the overapproximation.
   Note: that expression 'set' should not include function call. */

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define IS_FLAG_PREDICATES(set)                                 \
 (IS_FLAG_VALID_PREDICATES(set) || IS_OVER_APPROX(set))

/* below macro is TRUE iff the set is not an actually a Set_t,
   i.e. it is one of the constant values PREDICATES_TRUE,
   PREDICATES_FALSE or PREDICATES_ARBITRARY.
   Note: that expression 'set' should not include function call. */

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define IS_FLAG_VALID_PREDICATES(set)                           \
 ((set)==PREDICATES_TRUE||(set)==PREDICATES_FALSE||(set)==PREDICATES_ARBITRARY)



/* below macro is TRUE iff the set is not an actually a Set_t, but it represents
   an over-approximation, i.e. it is PREDICATES_OVERAPPROX */

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define IS_OVER_APPROX(set)                     \
  ((set)==PREDICATES_OVERAPPROX)

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define IS_ARBITRARY(set)                     \
  ((set)==PREDICATES_ARBITRARY)


/*!
  \struct PredicateExtractorBase
  \brief Definition of the public accessor for class PredicateExtractorBase
*/
typedef struct PredicateExtractorBase_TAG*  PredicateExtractorBase_ptr;


/*!
  \brief To cast and check instances of class PredicateExtractorBase

  These macros must be used respectively to cast and to check
  instances of class PredicateExtractorBase

*/
#define PREDICATE_EXTRACTOR_BASE(self) \
         ((PredicateExtractorBase_ptr) self)

#define PREDICATE_EXTRACTOR_BASE_CHECK_INSTANCE(self) \
         (nusmv_assert(PREDICATE_EXTRACTOR_BASE(self) != PREDICATE_EXTRACTOR_BASE(NULL)))




/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \methodof PredicateExtractorBase
  \brief The function computes and collects
   the predicates of a given expression

  
   See PredicateExtractorBase.h for more info on predicates and clusters.

   Note: that normalization of the input expression is not done.  Only
   predicates are computed (the lesser things are done the lesser
   time/memory is spent). See class PredicateNormaliser if
   predicate-normalized expressions are required.

   To additionally get/compute clusters
   PredicateExtractorBase_get_all_clusters can be used.

   Input expressions may/may not be expanded/normalized/flattened,
   whereas the collected predicates are flattened, expanded and
   created with find_node, in particular all identifiers fully
   resolved.

   WARNING: memoization is done. Providing the same expression a second
   times does not produce any additional predicate.

   Collected clusters/predicates are stored internally and can be
   obtained with PredicateExtractorBase_get_all_preds and
   PredicateExtractorBase_get_all_clusters.  
*/

VIRTUAL Set_t
PredicateExtractorBase_compute_preds(PredicateExtractorBase_ptr self,
                                     MasterCompilePredicateExtractorSupport_ptr support,
                                     node_ptr expr,
                                     node_ptr context);

#endif /* __NUSMV_CORE_COMPILE_PNE_PREDICATE_EXTRACTOR_BASE_H__ */
