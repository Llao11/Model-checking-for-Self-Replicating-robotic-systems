/* ---------------------------------------------------------------------------

  This file is part of the ``automata'' package.
  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Sergio Mover
  \brief Private and protected interface of class 'AutomataLoc'

  This file can be included only by derived and friend classes

*/

#ifndef __NUXMV_CORE_AUTOMATA_AUTOMATA_LOC_PRIVATE_H__
#define __NUXMV_CORE_AUTOMATA_AUTOMATA_LOC_PRIVATE_H__

#include "nusmv/core/automata/AutomataLoc.h" /* fix this */
#include "nusmv/core/utils/utils.h"
#include "nusmv/core/utils/object.h"
#include "nusmv/core/utils/object_private.h"

/*!
  \brief AutomataLoc class definition

  A location in an automaton.

  The location has an id. The id is assigned to the location in the
  Automaton class. When the location is not in an automaton (i.e. when
  the location has been just created) its id is -1.

  The location contains the boolean variable <tt>final</tt> that is true
  if one of the final locations in the automaton.

  The location has a type. The different types of a location are
  deterministic, non-deterministic and unknown.
  A location is flagged as:
    - deterministic: if all the transitions that leave the location can
  never be triggered together. When labels are represented
  symbolically this means that for all the transitions all the labels
  don't have any truth assignment in commmon.
    - non-deterministic: if the location is not deterministic.
    - unknown: this flag is assigned to a location if the library does not
  mantain the deterministic/non-deterministic information about the
  locations.

  The label_type is initially set to BASE_LABEL. When the first
  transition is created the type does not change anymore.

  The location can be complete. A location is complete if there exists a
  transition for every symbol of the alphabet. In the symbolic case it
  means that there is a transition for every possible truth assigment.

  The location contains in a stack all the transitions that leave the
  location.
*/


typedef struct AutomataLoc_TAG
{
  /* this MUST stay on the top */
  INHERITS_FROM(Object);

  /* -------------------------------------------------- */
  /*                  Private members                   */
  /* -------------------------------------------------- */
  int id;
  boolean final;
  Automaton_Type type;
  Automaton_Label_Type label_type;
  boolean is_complete;
  int transitions_count;
  Slist_ptr transitions_list;
  boolean keep_support_set;
  Set_t support_set;

} AutomataLoc;


/* ---------------------------------------------------------------------- */
/* Private methods to be used by derivated and friend classes only         */
/* ---------------------------------------------------------------------- */

/*!
  \methodof AutomataLoc
  \brief The AutomataLoc class private initializer

  The AutomataLoc class private initializer

  \sa AutomataLoc_create
*/
void automata_loc_init(AutomataLoc_ptr self,
                                Automaton_Label_Type label_type,
                                boolean keep_support_location);

/*!
  \methodof AutomataLoc
  \brief The AutomataLoc class private deinitializer

  The AutomataLoc class private deinitializer

  \sa AutomataLoc_destroy
*/
void automata_loc_deinit(AutomataLoc_ptr self);



#endif /* __NUXMV_CORE_AUTOMATA_AUTOMATA_LOC_PRIVATE_H__ */
