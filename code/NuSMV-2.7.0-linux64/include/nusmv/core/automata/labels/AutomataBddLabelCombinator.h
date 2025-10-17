/* ---------------------------------------------------------------------------

  This file is part of the ``labels'' package.
  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Sergio Mover
  \brief Public interface of class 'AutomataBddLabelCombinator'

  \todo: Missing description

*/

#ifndef __NUXMV_CORE_AUTOMATA_LABELS_AUTOMATA_BDD_LABEL_COMBINATOR_H__
#define __NUXMV_CORE_AUTOMATA_LABELS_AUTOMATA_BDD_LABEL_COMBINATOR_H__

#include "nusmv/core/automata/labels/AutomataLabelCombinator.h"
#include "nusmv/core/utils/utils.h"

/*!
  \struct AutomataBddLabelCombinator
  \brief Definition of the public accessor for class AutomataBddLabelCombinator

  
*/
typedef struct AutomataBddLabelCombinator_TAG*  AutomataBddLabelCombinator_ptr;

/*!
  \brief To cast and check instances of class AutomataBddLabelCombinator

  These macros must be used respectively to cast and to check
  instances of class AutomataBddLabelCombinator
*/
#define AUTOMATA_BDD_LABEL_COMBINATOR(self) \
         ((AutomataBddLabelCombinator_ptr) self)

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define AUTOMATA_BDD_LABEL_COMBINATOR_CHECK_INSTANCE(self) \
         (nusmv_assert(AUTOMATA_BDD_LABEL_COMBINATOR(self) != AUTOMATA_BDD_LABEL_COMBINATOR(NULL)))



/**AutomaticStart*************************************************************/

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \methodof AutomataBddLabelCombinator
  \brief The AutomataBddLabelCombinator class constructor

  The AutomataBddLabelCombinator class constructor

  \sa AutomataBddLabelCombinator_destroy
*/
AutomataBddLabelCombinator_ptr
AutomataBddLabelCombinator_create(const NuSMVEnv_ptr env);

/*!
  \methodof AutomataBddLabelCombinator
  \brief The AutomataBddLabelCombinator class destructor

  The AutomataBddLabelCombinator class destructor

  \sa AutomataBddLabelCombinator_create
*/
void AutomataBddLabelCombinator_destroy(AutomataBddLabelCombinator_ptr self);


/**AutomaticEnd***************************************************************/



#endif /* __NUXMV_CORE_AUTOMATA_LABELS_AUTOMATA_BDD_LABEL_COMBINATOR_H__ */
