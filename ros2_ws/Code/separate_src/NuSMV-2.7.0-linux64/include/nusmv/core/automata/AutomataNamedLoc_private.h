/* ---------------------------------------------------------------------------

  This file is part of the ``automata'' package.
  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Michele Dorigatti
  \brief Private and protected interface of class 'AutomataNamedLoc'

  This file can be included only by derived and friend classes

*/



#ifndef __NUXMV_CORE_AUTOMATA_AUTOMATA_NAMED_LOC_PRIVATE_H__
#define __NUXMV_CORE_AUTOMATA_AUTOMATA_NAMED_LOC_PRIVATE_H__


#include "nusmv/core/automata/AutomataNamedLoc.h"
#include "nusmv/core/automata/AutomataLoc.h" /* fix this */
#include "nusmv/core/automata/AutomataLoc_private.h" /* fix this */
#include "nusmv/core/utils/utils.h"


/*!
  \brief AutomataNamedLoc class definition derived from
               class AutomataLoc

  An AutomataNamedLoc is simply an AutomataLoc with an extra
  field name which is used to store the assigments variable=value
  characterizing the location.

  \sa Base class AutomataLoc
*/

typedef struct AutomataNamedLoc_TAG
{
  /* this MUST stay on the top */
  INHERITS_FROM(AutomataLoc);

  /* -------------------------------------------------- */
  /*                  Private members                   */
  /* -------------------------------------------------- */
  char* name;

} AutomataNamedLoc;



/* ---------------------------------------------------------------------- */
/* Private methods to be used by derivated and friend classes only         */
/* ---------------------------------------------------------------------- */

/*!
  \methodof AutomataNamedLoc
  \brief The AutomataNamedLoc class private initializer

  The AutomataNamedLoc class private initializer

  \sa AutomataNamedLoc_create
*/
void automata_named_loc_init(AutomataNamedLoc_ptr self,
                                      Automaton_Label_Type label_type,
                                      boolean keep_support_location);

/*!
  \methodof AutomataNamedLoc
  \brief The AutomataNamedLoc class private deinitializer

  The AutomataNamedLoc class private deinitializer

  \sa AutomataNamedLoc_destroy
*/
void automata_named_loc_deinit(AutomataNamedLoc_ptr self);



#endif /* __NUXMV_CORE_AUTOMATA_AUTOMATA_NAMED_LOC_PRIVATE_H__ */
