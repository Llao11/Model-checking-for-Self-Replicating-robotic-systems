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
   \brief Public interface of class 'PredicateNormaliserCore'

  (Implementation of modularity by Elia Rigo)

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

   \sa PredicateNormaliserCore.c
*/


#ifndef __NUSMV_CORE_COMPILE_PNE_PREDICATE_NORMALISER_CORE_H__
#define __NUSMV_CORE_COMPILE_PNE_PREDICATE_NORMALISER_CORE_H__


#include "nusmv/core/compile/pne/MasterCompilePredicateNormaliser.h"
#include "nusmv/core/compile/pne/MasterCompilePredicateNormaliser_private.h"

#include "nusmv/core/compile/pne/PredicateNormaliserBase.h"
#include "nusmv/core/utils/defs.h"
#include "nusmv/core/compile/symb_table/SymbTable.h"

/*!
  \struct PredicateNormaliserCore
  \brief Definition of the public accessor for class PredicateNormaliserCore
*/
typedef struct PredicateNormaliserCore_TAG*  PredicateNormaliserCore_ptr;


/*!
  \brief To cast and check instances of class PredicateNormaliserCore

  These macros must be used respectively to cast and to check
  instances of class PredicateNormaliserCore

*/
#define PREDICATE_NORMALISER_CORE(self) \
         ((PredicateNormaliserCore_ptr) self)

#define PREDICATE_NORMALISER_CORE_CHECK_INSTANCE(self) \
         (nusmv_assert(PREDICATE_NORMALISER_CORE(self) != PREDICATE_NORMALISER_CORE(NULL)))




/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \methodof PredicateNormaliserCore
  \brief The constructor creates a predicate-normaliser

  See PredicateNormaliserBase.h for more info on
   predicate normalisation.  The paramer 'checker' is a type checker
   used during predication-normalisation, and subsequent type checking of
   generated expressions.
   NOTE that the type checker remember the type of checked expressions.
*/
PredicateNormaliserCore_ptr PredicateNormaliserCore_create(NuSMVEnv_ptr env,
                                                           const char* name);


/*!
  \methodof PredicateNormaliserCore
  \brief The PredicateNormaliserCore class destructor

  The PredicateNormaliserCore class destructor

  \sa PredicateNormaliserCore_create
*/
void PredicateNormaliserCore_destroy (PredicateNormaliserCore_ptr self);


#endif /* __NUSMV_CORE_COMPILE_PNE_PREDICATE_NORMALISER_CORE_H__ */
