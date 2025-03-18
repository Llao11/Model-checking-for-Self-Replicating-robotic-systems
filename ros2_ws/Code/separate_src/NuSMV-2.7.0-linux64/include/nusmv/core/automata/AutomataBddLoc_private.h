/* ---------------------------------------------------------------------------


  This file is part of the ``automata'' package.
  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Chun Tian
  \brief Implementation of class 'AutomataBddLoc'
 */

#ifndef __NUXMV_CORE_AUTOMATA_AUTOMATA_BDD_LOC_PRIVATE_H__
#define __NUXMV_CORE_AUTOMATA_AUTOMATA_BDD_LOC_PRIVATE_H__

#include "nusmv/core/enc/bdd/BddEnc.h"
#include "nusmv/core/enc/bdd/bdd.h"

/*!
  \brief AutomataBddLoc class definition derived from
         class AutomataNamedLoc (instead of AutomataLoc)

  An AutomataBddLoc is simply an AutomataLoc with an extra
  field name which is used to store the original BddStates in BddFsm.

  \sa Base class AutomataNamedLoc
*/

typedef struct AutomataBddLoc_TAG
{
  /* this MUST stay on the top */
  INHERITS_FROM(AutomataNamedLoc);

  /* -------------------------------------------------- */
  /*                  Private members                   */
  /* -------------------------------------------------- */
  BddEnc_ptr bdd_enc;
  BddStates  bdd_states;

} AutomataBddLoc;

void automata_bdd_loc_init (AutomataBddLoc_ptr self,
			    Automaton_Label_Type label_type,
			    boolean keep_support_location,
			    BddEnc_ptr bdd_enc);

void automata_bdd_loc_deinit(AutomataBddLoc_ptr self);

#endif /* __NUXMV_CORE_AUTOMATA_AUTOMATA_BDD_LOC_PRIVATE_H__ */
