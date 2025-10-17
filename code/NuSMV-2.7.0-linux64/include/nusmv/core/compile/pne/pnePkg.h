
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
   \brief Public header

   \todo: Missing description

   \sa pnePkg.c
*/


#ifndef __NUSMV_CORE_COMPILE_PNE_PNE_PKG_H__
#define __NUSMV_CORE_COMPILE_PNE_PNE_PKG_H__

#include "nusmv/core/compile/pne/PredicateNormaliserCore_private.h"
#include "nusmv/core/compile/pne/PredicateExtractorCore_private.h"
#include "nusmv/core/utils/defs.h"
#include "nusmv/core/cinit/NuSMVEnv.h"

/**AutomaticStart*************************************************************/

/*---------------------------------------------------------------------------*/
/* Constant declarations                                                     */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Type declarations                                                         */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Structure declarations                                                    */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Variable declarations                                                     */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Macro declarations                                                        */
/*---------------------------------------------------------------------------*/


/**AutomaticEnd***************************************************************/
/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \brief Initialization of the pne package.

  Initialization of the pne package.

  It associates a pne to the global environment.
*/
void PnePkg_init(NuSMVEnv_ptr env);

/*!
  \brief Deinitialization of the pne package


*/

void PnePkg_quit(NuSMVEnv_ptr env);

/*---------------------------------------------------------------------------*/
/* Predicate Normaliser                                                      */
/*---------------------------------------------------------------------------*/

/*!
  \brief Initialization of the predicate normaliser in the pne package.

  Initialization of the predicate normaliser in the pne package.

  It associates a predicate normaliser to the global environment.
*/
void PredicateNormaliserPkg_init(NuSMVEnv_ptr env);

/*!
  \brief Deinitialization of the predicate normaliser package


*/

void PredicateNormaliserPkg_quit(NuSMVEnv_ptr env);

/*!
  \brief Registration of the predicate normaliser walker.


*/
void 
PnePkg_register_predicate_normaliser_walker(NuSMVEnv_ptr env, 
                                                  PredicateNormaliserCoreWalker_ptr pn_core_walker);

/*!
  \brief Unregistration of the predicate normaliser walker.


*/
boolean 
PnePkg_unregister_predicate_normaliser_walker(NuSMVEnv_ptr env, 
                                                    const char* walker_name);

/*!
  \brief Initialization of the predicate normaliser list.

  Initialization of the predicate normaliser list package.

  It associates a predicate normaliser list to the global environment.
*/
void PnePkg_init_predicate_normaliser_walkers_list(NuSMVEnv_ptr env);

/*!
  \brief Deinitialization of the predicate normaliser list.


*/
void PnePkg_destroy_predicate_normaliser_walkers_list(NuSMVEnv_ptr env);

/*---------------------------------------------------------------------------*/
/* Predicate Extractor                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \brief Initialization of the predicate extractor in the predicate package.

  Initialization of the predicate extractor in the predicate package.

  It associates a predicate extractor to the global environment.
*/

void PredicateExtractorPkg_init(NuSMVEnv_ptr env);

/*!
  \brief Deinitialization of the predicate extractor package


*/
void PredicateExtractorPkg_quit(NuSMVEnv_ptr env);

/*!
  \brief Registration of the predicate extractor walker.


*/
void
PnePkg_register_predicate_extractor_walker(NuSMVEnv_ptr env,
                                                 PredicateExtractorCoreWalker_ptr pe_core_walker);

/*!
  \brief Unregistration of the predicate extractor walker.


*/
boolean 
PnePkg_unregister_predicate_extractor_walker(NuSMVEnv_ptr env, 
                                                   const char* walker_name);

/*!
  \brief Initialization of the predicate extractor list.

  Initialization of the predicate extractor list package.

  It associates a predicate extractor list to the global environment.
*/
void PnePkg_init_predicate_extractor_walkers_list(NuSMVEnv_ptr env);

/*!
  \brief Deinitialization of the predicate extractor list.


*/
void PnePkg_destroy_predicate_extractor_walkers_list(NuSMVEnv_ptr env);

#endif /* __NUSMV_CORE_COMPILE_PNE_PREDICATE_PKG_H__ */
