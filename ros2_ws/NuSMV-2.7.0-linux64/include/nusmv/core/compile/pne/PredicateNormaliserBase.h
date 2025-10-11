
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
  \brief Public base interface for a predicate-normaliser class

  
  The purpose of a predicate normaliser is to take a symbolic
  expression (node_ptr), normalise predicates and return a newly
  created expressions with normlised predicates.  A
  predicate-normalised expression is an expression where none of
  not-boolean subexpressions may have a boolean subexpression, i.e.
  only boolean expressions may have boolean subexpressions.
  Normalisation is done by (creating and) pushing IfThenElse
  expression up to the root of not-boolean subexpression.  For
  example,

     "case a : 3; 1 : 4; esac + 2 = 7"

  have boolean expression "a" as a subexpression of not-boolean
  expression "case ...".  The normalised version will look like
     "case a : 3 + 2 = 7; 1 : 4 + 2 = 7; esac"


  This is a stand-alone class. This class needs only a type checker
  -- to get the type of input expression and type check the generated
  (returned) expressions.
  
   \sa PredicateNormaliserBase.c
*/


#ifndef __NUSMV_CORE_COMPILE_PNE_PREDICATE_NORMALISER_BASE_H__
#define __NUSMV_CORE_COMPILE_PNE_PREDICATE_NORMALISER_BASE_H__

#include "nusmv/core/compile/pne/MasterCompilePredicateNormaliser.h"
#include "nusmv/core/utils/defs.h"
#include "nusmv/core/utils/object.h"
#include "nusmv/core/node/NodeWalker.h"
#include "nusmv/core/set/set.h"


/*!
  \struct PredicateNormaliserBase
  \brief Definition of the public accessor for class PredicateNormaliserBase
*/
typedef struct PredicateNormaliserBase_TAG*  PredicateNormaliserBase_ptr;


/*!
  \brief To cast and check instances of class PredicateNormaliserBase

  These macros must be used respectively to cast and to check
  instances of class PredicateNormaliserBase

*/
#define PREDICATE_NORMALISER_BASE(self) \
         ((PredicateNormaliserBase_ptr) self)

#define PREDICATE_NORMALISER_BASE_CHECK_INSTANCE(self) \
         (nusmv_assert(PREDICATE_NORMALISER_BASE(self) != PREDICATE_NORMALISER_BASE(NULL)))




/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \methodof PredicateNormaliserBase
  \brief The function performs predicate-normalisation of
   a generic boolean expression

  The function returns a new expression -- a
   predicate-normalised version of the given one.
   A predicate normalised expression is a symbolic expression (Sexp)
   whose not-boolean subexpressions do not encompass boolean subexpression.
   For example, not predicate-normalised expression
   "case a : 3; 1 : 4; esac + 2 = 7"
   after normalisatio becomes
   "case a : 3 + 2 = 7; 1 : 4 + 2 = 7; esac"

   The provided expression should be scalar (since there is no
   meaning to normalise booleanised expressions).  The given
   expression must be already type checked (by the type checker
   given to the constructor), but may be or may not be flattened
   and expanded.

   During normalisation the type checker (given during construction) is
   used to distinguish boolean from not-boolean expressions.
   Note that the generated expressions may be type checked, i.e. the type
   checker remember their types.

   The normaliser caches processed expressions. So, if the same expression is
   given, the same result will be returned.

   The returned expression is always flattened and expanded if the value 
   in 'expand' is True. Also, i is created by find_node function, therefore 
   it #include "nusmv/core/utils/utils.h" belongs to
   the node package (i.e. do not modify it).

   NOTE: if only predicates are required at the end and not the whole
   normalized expressions, then it is better to use PredicateExtractor
   class. 
*/
VIRTUAL 
node_ptr PredicateNormaliserBase_normalise_expr(PredicateNormaliserBase_ptr self,
                                                MasterCompilePredicateNormaliserSupport_ptr support,
                                                node_ptr expr,
                                                node_ptr context,
                                                boolean expand);

/*!
  \methodof PredicateNormaliser
  \brief The function performs predicate-normalisation of
   specification (SPEC, LTLSPEC, etc)

  This function does the same things as
   PredicateNormaliser_normalise_expr, except that the input expression
   must be a specification (such expression are returned by Prop_get_expr_core)
   
*/
VIRTUAL 
node_ptr PredicateNormaliserBase_normalise_specification(PredicateNormaliserBase_ptr self,
                                                         MasterCompilePredicateNormaliserSupport_ptr support,
                                                         node_ptr expr);

/*!
  \methodof PredicateNormaliserBase
  \brief The function adds to the given set the expression's
   predicates, i.e. subexpressions which have not-boolean operands.

  Only boolean expressions obtained with
   PredicateNormaliserBase_normalise_expr and with the same
   predicate-normaliser (i.e. 'self') can be given to this function.

   See function PredicateNormaliserCore_compute_predicates_and_clusters
   if only predicates are required without normalization of a whole expression.

   This function just walks the exressions, tries to find
   a subexpression with not-boolean operands then adds it to the given set.
   Every predicate is added only once.
   
*/
VIRTUAL
void PredicateNormaliserBase_get_predicates_only(const PredicateNormaliserBase_ptr self,
                                                 MasterCompilePredicateNormaliserSupport_ptr support,
                                                 Set_t* preds, node_ptr expr);

#endif /* __NUSMV_CORE_COMPILE_PNE_PREDICATE_NORMALISER_BASE_H__ */
