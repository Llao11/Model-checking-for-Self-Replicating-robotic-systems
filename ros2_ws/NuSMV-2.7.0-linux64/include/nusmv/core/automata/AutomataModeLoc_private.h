/* ---------------------------------------------------------------------------

  This file is part of the ``automata'' package.
  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author
  \brief Private and protected interface of class 'AutomataModeLoc'

  This file can be included only by derived and friend classes

*/

#ifndef __NUXMV_CORE_AUTOMATA_AUTOMATA_MODE_LOC_PRIVATE_H__
#define __NUXMV_CORE_AUTOMATA_AUTOMATA_MODE_LOC_PRIVATE_H__


#include "nusmv/core/automata/AutomataModeLoc.h"
#include "nusmv/core/automata/AutomataLoc.h" /* fix this */
#include "nusmv/core/automata/AutomataLoc_private.h" /* fix this */
#include "nusmv/core/utils/utils.h"


/*!
  \brief AutomataModeLoc class definition derived from
               class AutomataLoc

  An AutomataModeLoc is simply an AutomataLoc with an extra
  field expr which is used to store information about system
  mode that the location represents.
  System mode is an expression over state variables.

  \sa Base class AutomataLoc
*/

typedef struct AutomataModeLoc_TAG
{
  /* this MUST stay on the top */
  INHERITS_FROM(AutomataLoc);

  /* -------------------------------------------------- */
  /*                  Private members                   */
  /* -------------------------------------------------- */
  Expr_ptr expr;

} AutomataModeLoc;



/* ---------------------------------------------------------------------- */
/* Private methods to be used by derivated and friend classes only         */
/* ---------------------------------------------------------------------- */

/*!
  \methodof AutomataModeLoc
  \brief The AutomataModeLoc class private initializer

  The AutomataModeLoc class private initializer

  \sa AutomataModeLoc_create
*/
void automata_mode_loc_init(AutomataModeLoc_ptr self,
                                      Automaton_Label_Type label_type,
                                      boolean keep_support_location);

/*!
  \methodof AutomataModeLoc
  \brief The AutomataModeLoc class private deinitializer

  The AutomataModeLoc class private deinitializer

  \sa AutomataModeLoc_destroy
*/
void automata_mode_loc_deinit(AutomataModeLoc_ptr self);



#endif /* __NUXMV_CORE_AUTOMATA_AUTOMATA_MODE_LOC_PRIVATE_H__ */
