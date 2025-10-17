/* ---------------------------------------------------------------------------

  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Michele Dorigatti
  \brief Public interface of class 'AutomataHybridLabel'

  \todo: Missing description

*/

#ifndef __NUXMV_CORE_AUTOMATA_LABELS_AUTOMATA_HYBRID_LABEL_H__
#define __NUXMV_CORE_AUTOMATA_LABELS_AUTOMATA_HYBRID_LABEL_H__

#include "nusmv/core/automata/labels/AutomataLabel.h"
#include "nusmv/core/utils/utils.h"
#include "nusmv/core/utils/Olist.h"
#include "nusmv/core/node/NodeMgr.h"

/*!
  \struct AutomataHybridLabel
  \brief Definition of the public accessor for class AutomataHybridLabel

  
*/
typedef struct AutomataHybridLabel_TAG*  AutomataHybridLabel_ptr;

/*!
  \brief To cast and check instances of class AutomataHybridLabel

  These macros must be used respectively to cast and to check
  instances of class AutomataHybridLabel
*/
#define AUTOMATA_HYBRID_LABEL(self) \
         ((AutomataHybridLabel_ptr) self)

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define AUTOMATA_HYBRID_LABEL_CHECK_INSTANCE(self) \
         (nusmv_assert(AUTOMATA_HYBRID_LABEL(self) != AUTOMATA_HYBRID_LABEL(NULL)))



/**AutomaticStart*************************************************************/

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/* Constructors and Destructors ***********************************************/

/*!
  \methodof AutomataHybridLabel
  \brief The AutomataHybridLabel class constructor

  The AutomataHybridLabel class constructor

  \sa AutomataHybridLabel_destroy
*/
AutomataHybridLabel_ptr AutomataHybridLabel_create(void);

/*!
  \methodof AutomataHybridLabel
  \brief The AutomataHybridLabel class destructor

  The AutomataHybridLabel class destructor

  \sa AutomataHybridLabel_create
*/
void AutomataHybridLabel_destroy(AutomataHybridLabel_ptr self);


/* Getters ********************************************************************/

/*!
  \brief Getter for event

  
*/
Expr_ptr
AutomataHybridLabel_get_event(AutomataHybridLabel_ptr const self);

/*!
  \brief Getter for guards

  
*/
Olist_ptr
AutomataHybridLabel_get_guards(AutomataHybridLabel_ptr const self);

/*!
  \brief Getter for effects

  
*/
Olist_ptr
AutomataHybridLabel_get_effects(AutomataHybridLabel_ptr const self);

/* This is a setter, too */

/*!
  \methodof AutomataHybridLabel
  \brief Getter and setter for the member expression

  expression is a conjunction of the event, guards and
  effects. It is created the first time is required. It is in reversed order
  w.r.t. the lists.
*/
Expr_ptr
AutomataHybridLabel_compute_expr(AutomataHybridLabel_ptr self,
                                 NodeMgr_ptr nodemgr);


/* Setters ********************************************************************/

/*!
  \methodof AutomataHybridLabel
  \brief Setter for event

  self->expr is deinitialized
*/
void AutomataHybridLabel_set_event(AutomataHybridLabel_ptr self,
                                          Expr_ptr const event);

/*!
  \methodof AutomataHybridLabel
  \brief Add a guard to the internal list

  self->expr is deinitialized
*/
void AutomataHybridLabel_add_guard(AutomataHybridLabel_ptr self,
                                          Expr_ptr const guard);

/*!
  \methodof AutomataHybridLabel
  \brief Add an effect to the internal list

  self->expr is deinitialized
*/
void AutomataHybridLabel_add_effect(AutomataHybridLabel_ptr self,
                                           Expr_ptr const effect);

/**AutomaticEnd***************************************************************/



#endif /* __NUXMV_CORE_AUTOMATA_LABELS_AUTOMATA_HYBRID_LABEL_H__ */
