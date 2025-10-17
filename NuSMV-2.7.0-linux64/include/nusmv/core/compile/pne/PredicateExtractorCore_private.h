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
   \brief Private and protected interface of class 'PredicateExtractorCore'

   This file can be included only by derived and friend classes

   \sa PredicateExtractorCore.h
*/


#ifndef __NUSMV_CORE_COMPILE_PNE_PREDICATE_EXTRACTOR_CORE_PRIVATE_H__
#define __NUSMV_CORE_COMPILE_PNE_PREDICATE_EXTRACTOR_CORE_PRIVATE_H__


#include "nusmv/core/compile/pne/PredicateExtractorBase.h"
#include "nusmv/core/compile/pne/PredicateExtractorCore.h"
#include "nusmv/core/compile/pne/PredicateExtractorBase_private.h"
#include "nusmv/core/utils/defs.h"


#define PREDICATE_EXTRACTOR_CORE_NAME "Predicate Extractor core"

/*!
  \brief PredicateExtractorCore class definition derived from
         class PredicateExtractorBase



  \sa Base class PredicateExtractorBase
*/

typedef
PredicateExtractorCore_ptr(*typeFunctionPredicateExtractorCreate)(const NuSMVEnv_ptr,
                                                                  const char*);

typedef struct PredicateExtractorCore_TAG
{
  /* this MUST stay on the top */
  INHERITS_FROM(PredicateExtractorBase);

  /* -------------------------------------------------- */
  /*                  Private members                   */
  /* -------------------------------------------------- */


  /* -------------------------------------------------- */
  /*                  Virtual methods                   */
  /* -------------------------------------------------- */

} PredicateExtractorCore;

typedef struct PredicateExtractorCoreWalker_TAG
{
  char* pecw_name;
  typeFunctionPredicateExtractorCreate pecw_function_create;
} PredicateExtractorCoreWalker;

/* ---------------------------------------------------------------------- */
/* Private methods to be used by derivated and friend classes only        */
/* ---------------------------------------------------------------------- */
/*!
  \methodof PredicateExtractorCore
  \brief The PredicateExtractorCore class private initializer

  The PredicateExtractorCore class private initializer

  \sa PredicateExtractorCore_create
*/
void predicate_extractor_core_init (PredicateExtractorCore_ptr self,
                                    const NuSMVEnv_ptr env, const char* name,
                                    int low, size_t num, boolean can_handle_null);

/*!
  \methodof PredicateExtractorCore
  \brief The PredicateExtractorCore class private deinitializer

  The PredicateExtractorCore class private deinitializer

  \sa PredicateExtractorCore_destroy
*/
void predicate_extractor_core_deinit (PredicateExtractorCore_ptr self);

/*!
  \methodof PredicateExtractorCore
  \brief Do the actual compute pred

*/
Set_t
predicate_extractor_core_compute_preds(PredicateExtractorBase_ptr self,
                                       MasterCompilePredicateExtractorSupport_ptr support,
                                       node_ptr expr,
                                       node_ptr context);

#endif /* __NUSMV_CORE_COMPILE_PNE_PREDICATE_EXTRACTOR_CORE_PRIVATE_H__ */
