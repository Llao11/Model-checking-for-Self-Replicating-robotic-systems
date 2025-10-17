/* ---------------------------------------------------------------------------


  This file is part of the ``automata'' package.
  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Chun Tian
  \brief Implementation of class 'AutomataBddLoc'
 */

#ifndef __NUXMV_CORE_AUTOMATA_AUTOMATA_BDD_LOC_H__
#define __NUXMV_CORE_AUTOMATA_AUTOMATA_BDD_LOC_H__

#include "nusmv/core/automata/AutomataLoc.h"
#include "nusmv/core/automata/Automaton.h"
#include "nusmv/core/utils/utils.h"

/*!
  \struct AutomataBddLoc
  \brief Definition of the public accessor for class AutomataBddLoc

 */
typedef struct AutomataBddLoc_TAG* AutomataBddLoc_ptr;

/*!
  \brief To cast and check instances of class AutomataBddLoc

  These macros must be used respectively to cast and to check
  instances of class AutomataBddLoc
*/
#define AUTOMATA_BDD_LOC(self) ((AutomataBddLoc_ptr) self)

#define AUTOMATA_BDD_LOC_CHECK_INSTANCE(self) \
         (nusmv_assert(AUTOMATA_BDD_LOC(self) != AUTOMATA_BDD_LOC(NULL)))

/*!
  \brief Create a BDD-based Automata location
*/
AutomataBddLoc_ptr AutomataBddLoc_create (boolean, BddEnc_ptr);

/*!
  \brief Create a BDD-based Automata location (from Autamata manager)
*/
AutomataBddLoc_ptr AutomataBddLoc_create_from_manager (AutomataManager_ptr);

/*!
  \brief Destroy a BDD-based Autamata location
*/
void AutomataBddLoc_destroy (AutomataBddLoc_ptr);

/*!
  \brief Set the underlying BDD of a BDD-based Autamata location
*/
void AutomataBddLoc_set_states (AutomataBddLoc_ptr, BddStates);

/*!
  \brief Get the underlying BDD of a BDD-based Autamata location

  It returns a BDD with the ref count increased so that it must be freed by
  the caller.
*/
BddStates AutomataBddLoc_get_states (AutomataBddLoc_ptr);

#endif /* __NUXMV_CORE_AUTOMATA_AUTOMATA_BDD_LOC_H__ */
