
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
   \brief Public interface of class 'PredicateExtractorCore'

   

   \sa PredicateExtractorCore.c
*/


#ifndef __NUSMV_CORE_COMPILE_PNE_PREDICATE_EXTRACTOR_CORE_H__
#define __NUSMV_CORE_COMPILE_PNE_PREDICATE_EXTRACTOR_CORE_H__

#include "nusmv/core/compile/pne/MasterCompilePredicateExtractor_private.h"
#include "nusmv/core/compile/pne/PredicateExtractorBase.h"
#include "nusmv/core/utils/defs.h"
#include "nusmv/core/compile/FlatHierarchy.h" /* for FlatHierarchy_ptr */
#include "nusmv/core/set/set.h"
#include "nusmv/core/utils/utils.h"


/*!
  \struct PredicateExtractorCore
  \brief Definition of the public accessor for class PredicateExtractorCore
*/
typedef struct PredicateExtractorCore_TAG*  PredicateExtractorCore_ptr;
typedef struct PredicateExtractorCoreWalker_TAG*  PredicateExtractorCoreWalker_ptr;

/*!
  \brief To cast and check instances of class PredicateExtractorCore

  These macros must be used respectively to cast and to check
  instances of class PredicateExtractorCore

*/
#define PREDICATE_EXTRACTOR_CORE(self) \
         ((PredicateExtractorCore_ptr) self)

#define PREDICATE_EXTRACTOR_CORE_CHECK_INSTANCE(self) \
         (nusmv_assert(PREDICATE_EXTRACTOR_CORE(self) != PREDICATE_EXTRACTOR_CORE(NULL)))

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \methodof PredicateExtractorCore
  \brief The constructor creates a predicate-extractor

  See PredicateExtractorBase.h for more info on
   predicates and clusters.  The parameter 'checker' is a type checker
   used during predicate extraction and subsequent type checking of
   generated expressions.
*/
PredicateExtractorCore_ptr PredicateExtractorCore_create (const NuSMVEnv_ptr env,
                                                          const char* name);

/*!
  \methodof PredicateExtractorCore 
  \brief The PredicateExtractorCore class private deinitializer

  The PredicateExtractorCore class private deinitializer

  \sa PredicateExtractorCore_destroy
*/
void PredicateExtractorCore_destroy (PredicateExtractorCore_ptr self);

#endif /* __NUSMV_CORE_COMPILE_PNE_PREDICATE_EXTRACTOR_CORE_H__ */
