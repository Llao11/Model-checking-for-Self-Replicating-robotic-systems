/* ---------------------------------------------------------------------------

  This file is part of the ``labels'' package.
  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Sergio Mover
  \brief Private and protected interface of class 'AutomataBddLabelCombinator'

  This file can be included only by derived and friend classes

*/

#ifndef __NUXMV_CORE_AUTOMATA_LABELS_AUTOMATA_BDD_LABEL_COMBINATOR_PRIVATE_H__
#define __NUXMV_CORE_AUTOMATA_LABELS_AUTOMATA_BDD_LABEL_COMBINATOR_PRIVATE_H__

#include "nusmv/core/automata/labels/AutomataBddLabelCombinator.h" 
#include "nusmv/core/automata/labels/AutomataLabelCombinator.h" /* fix this */ 
#include "nusmv/core/automata/labels/AutomataLabelCombinator_private.h" /* fix this */ 
#include "nusmv/core/utils/utils.h" 

/*!
  \brief AutomataBddLabelCombinator class definition derived from
               class AutomataLabelCombinator

  

  \sa Base class AutomataLabelCombinator
*/

typedef struct AutomataBddLabelCombinator_TAG
{
  /* this MUST stay on the top */
  INHERITS_FROM(AutomataLabelCombinator); 

  /* -------------------------------------------------- */
  /*                  Private members                   */
  /* -------------------------------------------------- */


  /* -------------------------------------------------- */
  /*                  Virtual methods                   */
  /* -------------------------------------------------- */

} AutomataBddLabelCombinator;



/* ---------------------------------------------------------------------- */
/* Private methods to be used by derivated and friend classes only         */
/* ---------------------------------------------------------------------- */

/*!
  \methodof AutomataBddLabelCombinator
  \brief The AutomataBddLabelCombinator class private initializer

  The AutomataBddLabelCombinator class private initializer

  \sa AutomataBddLabelCombinator_create
*/
void
automata_bdd_label_combinator_init(AutomataBddLabelCombinator_ptr self,
                                   const NuSMVEnv_ptr env);

/*!
  \methodof AutomataBddLabelCombinator
  \brief The AutomataBddLabelCombinator class private deinitializer

  The AutomataBddLabelCombinator class private deinitializer

  \sa AutomataBddLabelCombinator_destroy
*/
void automata_bdd_label_combinator_deinit(AutomataBddLabelCombinator_ptr self);



#endif /* __NUXMV_CORE_AUTOMATA_LABELS_AUTOMATA_BDD_LABEL_COMBINATOR_PRIVATE_H__ */
