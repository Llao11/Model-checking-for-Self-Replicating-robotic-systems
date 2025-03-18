/* ---------------------------------------------------------------------------

  This file is part of the ``labels'' package.
  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Sergio Mover
  \brief Private and protected interface of class 'AutomataLabelCombinator'

  This file can be included only by derived and friend classes

*/

#ifndef __NUXMV_CORE_AUTOMATA_LABELS_AUTOMATA_LABEL_COMBINATOR_PRIVATE_H__
#define __NUXMV_CORE_AUTOMATA_LABELS_AUTOMATA_LABEL_COMBINATOR_PRIVATE_H__

#include "nusmv/core/automata/labels/AutomataLabelCombinator.h"
#include "nusmv/core/automata/automata.h"

#include "nusmv/core/utils/EnvObject.h"
#include "nusmv/core/utils/EnvObject_private.h"
#include "nusmv/core/utils/utils.h"


/*!
  \brief AutomataLabelCombinator class definition derived from
               class Object

  label_type is used internally to raise an error if the
  label type of input is not the same as the type managed by the combinator.

  \sa Base class Object
*/

typedef struct AutomataLabelCombinator_TAG
{
  /* this MUST stay on the top */
  INHERITS_FROM(EnvObject);

  /* -------------------------------------------------- */
  /*                  Private members                   */
  /* -------------------------------------------------- */
  Automaton_Label_Type label_type;

  /* -------------------------------------------------- */
  /*                  Virtual methods                   */
  /* -------------------------------------------------- */
  Set_t (*combine)(AutomataLabelCombinator_ptr self,
                   Set_t label_location_set);

} AutomataLabelCombinator;



/* ---------------------------------------------------------------------- */
/* Private methods to be used by derivated and friend classes only         */
/* ---------------------------------------------------------------------- */

/*!
  \methodof AutomataLabelCombinator
  \brief The AutomataLabelCombinator class private initializer

  The AutomataLabelCombinator class private initializer

  \sa AutomataLabelCombinator_create
*/
void automata_label_combinator_init(AutomataLabelCombinator_ptr self,
                                           const NuSMVEnv_ptr env);

/*!
  \methodof AutomataLabelCombinator
  \brief The AutomataLabelCombinator class private deinitializer

  The AutomataLabelCombinator class private deinitializer

  \sa AutomataLabelCombinator_destroy
*/
void automata_label_combinator_deinit(AutomataLabelCombinator_ptr self);

/*!
  \methodof AutomataLabelCombinator
  \brief Set the label type managed by this combinator.

  Set the label type managed by this
  combinator. This method is used by derivate classes to set their own
  managed label type
*/
void automata_label_combinator_set_label_type(AutomataLabelCombinator_ptr self,
                                                     Automaton_Label_Type type);

/*!
  \methodof AutomataLabelCombinator
  \brief Creates all the possible combinations of labels
  contained in label_location_set.

  Creates all the possible combinations of labels
  contained in label_location_set.

  label_location_set is a set of couples (label, location). The function
  returns the set of couples (label, location_set), where label is a
  possible combination of the initial set of label and location_set is
  the set of locations that are reachable with label.

  The function prunes the UNSAT combinations of labels.
*/
Set_t automata_label_combinator_combine(AutomataLabelCombinator_ptr self,
                                               Set_t label_location_set);

#endif /* __NUXMV_CORE_AUTOMATA_LABELS_AUTOMATA_LABEL_COMBINATOR_PRIVATE_H__ */
