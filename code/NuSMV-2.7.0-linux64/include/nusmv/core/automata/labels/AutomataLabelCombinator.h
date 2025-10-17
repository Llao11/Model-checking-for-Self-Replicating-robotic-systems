/* ---------------------------------------------------------------------------

  This file is part of the ``labels'' package.
  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Sergio Mover
  \brief Public interface of class 'AutomataLabelCombinator'

  \todo: Missing description

*/

#ifndef __NUXMV_CORE_AUTOMATA_LABELS_AUTOMATA_LABEL_COMBINATOR_H__
#define __NUXMV_CORE_AUTOMATA_LABELS_AUTOMATA_LABEL_COMBINATOR_H__


#include "nusmv/core/set/set.h"
#include "nusmv/core/utils/object.h"
#include "nusmv/core/utils/utils.h"

/*!
  \struct AutomataLabelCombinator
  \brief Definition of the public accessor for class AutomataLabelCombinator

  
*/
typedef struct AutomataLabelCombinator_TAG*  AutomataLabelCombinator_ptr;

/*!
  \brief To cast and check instances of class AutomataLabelCombinator

  These macros must be used respectively to cast and to check
  instances of class AutomataLabelCombinator
*/
#define AUTOMATA_LABEL_COMBINATOR(self) \
         ((AutomataLabelCombinator_ptr) self)

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define AUTOMATA_LABEL_COMBINATOR_CHECK_INSTANCE(self) \
         (nusmv_assert(AUTOMATA_LABEL_COMBINATOR(self) != AUTOMATA_LABEL_COMBINATOR(NULL)))



/**AutomaticStart*************************************************************/

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \methodof AutomataLabelCombinator
  \brief The AutomataLabelCombinator class constructor

  The AutomataLabelCombinator class constructor

  \sa AutomataLabelCombinator_destroy
*/
AutomataLabelCombinator_ptr
AutomataLabelCombinator_create(const NuSMVEnv_ptr env);

/*!
  \methodof AutomataLabelCombinator
  \brief The AutomataLabelCombinator class destructor

  The AutomataLabelCombinator class destructor

  \sa AutomataLabelCombinator_create
*/
void AutomataLabelCombinator_destroy(AutomataLabelCombinator_ptr self);

/*!
  \methodof AutomataLabelCombinator
  \brief Creates all the possible combinations of labels
  contained in label_location_set.

  Creates all the possible combinations of labels
  contained in label_location_set.

  label_location_set is a set of couples (label, location). Couples are
  CONS node_ptr where car is the label and cdr is location.

  The function returns the set of couples (label, location_set), where
  label is a possible combination of the initial set of label and
  location_set is the set of locations that are reachable with label.

  The function prunes the UNSAT combinations of labels.
  
*/
Set_t AutomataLabelCombinator_combine(AutomataLabelCombinator_ptr self,
                                             Set_t label_location_set);

/**AutomaticEnd***************************************************************/



#endif /* __NUXMV_CORE_AUTOMATA_LABELS_AUTOMATA_LABEL_COMBINATOR_H__ */
