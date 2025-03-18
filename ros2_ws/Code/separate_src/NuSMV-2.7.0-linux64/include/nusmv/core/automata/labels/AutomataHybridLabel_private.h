/* ---------------------------------------------------------------------------

  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Michele Dorigatti
  \brief Private and protected interface of class 'AutomataHybridLabel'

  This file can be included only by derived and friend classes

*/

#ifndef __NUXMV_CORE_AUTOMATA_LABELS_AUTOMATA_HYBRID_LABEL_PRIVATE_H__
#define __NUXMV_CORE_AUTOMATA_LABELS_AUTOMATA_HYBRID_LABEL_PRIVATE_H__

#include "nusmv/core/automata/labels/AutomataHybridLabel.h"
#include "nusmv/core/automata/labels/AutomataLabel.h"
#include "nusmv/core/automata/labels/AutomataLabel_private.h"

#include "nusmv/core/utils/utils.h"
#include "nusmv/core/utils/Olist.h"
#include "nusmv/core/wff/ExprMgr.h"

/*!
  \brief AutomataHybridLabel class definition derived from
               class AutomataLabel

  This class represents the label of a hybrid automaton. The field
  expression inherited from AutomataLabel here is the conjunction of the
  elements stored in the other fields:

  - event:
    The action that identify a switch, on which automata must synchronize

  - guards:
    The boolean conditions over clocks that enables the switch

  - effects:
    Some action performed when a switch is triggered, typically the reset of
    some clocks.


  \sa Base class AutomataLabel
*/

typedef struct AutomataHybridLabel_TAG
{
  /* this MUST stay on the top */
  INHERITS_FROM(AutomataLabel);

  /* -------------------------------------------------- */
  /*                  Private members                   */
  /* -------------------------------------------------- */
  Expr_ptr event;
  Olist_ptr guards;
  Olist_ptr effects;

  /* -------------------------------------------------- */
  /*                  Virtual methods                   */
  /* -------------------------------------------------- */

} AutomataHybridLabel;



/* ---------------------------------------------------------------------- */
/* Private methods to be used by derivated and friend classes only         */
/* ---------------------------------------------------------------------- */

/*!
  \methodof AutomataHybridLabel
  \brief The AutomataHybridLabel class private initializer

  The AutomataHybridLabel class private initializer

  \sa AutomataHybridLabel_create
*/
void automata_hybrid_label_init(AutomataHybridLabel_ptr self);

/*!
  \methodof AutomataHybridLabel
  \brief The AutomataHybridLabel class private deinitializer

  The AutomataHybridLabel class private deinitializer

  \sa AutomataHybridLabel_destroy
*/
void automata_hybrid_label_deinit(AutomataHybridLabel_ptr self);

/*!
  \methodof AutomataHybridLabel
  \brief Sets a new expression for the label

  This function must not be called: the expression member
  has to be computed from the other paramaters
*/
void automata_hybrid_label_set_expr(AutomataLabel_ptr self,
                                           Expr_ptr new_expr);

#endif /* __NUXMV_CORE_AUTOMATA_LABELS_AUTOMATA_HYBRID_LABEL_PRIVATE_H__ */
