/* ---------------------------------------------------------------------------

  This file is part of the ``automata'' package.
  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Sergio Mover
  \brief Public interface of class 'AutomataTransition'

  \todo: Missing description

*/

#ifndef __NUXMV_CORE_AUTOMATA_AUTOMATA_TRANSITION_H__
#define __NUXMV_CORE_AUTOMATA_AUTOMATA_TRANSITION_H__

#include "nusmv/core/automata/automataInt.h"
#include "nusmv/core/automata/AutomataLoc_private.h"
#include "nusmv/core/automata/labels/AutomataLabel.h"

#include "nusmv/core/utils/utils.h"

/*!
  \brief To cast and check instances of class AutomataTransition

  These macros must be used respectively to cast and to check
  instances of class AutomataTransition
*/
#define AUTOMATA_TRANSITION(self) \
         ((AutomataTransition_ptr) self)

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define AUTOMATA_TRANSITION_CHECK_INSTANCE(self) \
         (nusmv_assert(AUTOMATA_TRANSITION(self) != AUTOMATA_TRANSITION(NULL)))


/**AutomaticStart*************************************************************/

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/* Constructors and Destructors ***********************************************/

/*!
  \methodof AutomataTransition
  \brief The AutomataTransition class constructor

  The AutomataTransition class constructor

  \sa AutomataTransition_destroy
*/
AutomataTransition_ptr AutomataTransition_create(void);

/*!
  \methodof AutomataTransition
  \brief Create a new transition where the end location is
  end_location and the label is label

  Returns a new transition with the end location
  pointer set to end_location and the label pointer set to label

  \sa AutomataTransition_create
*/
AutomataTransition_ptr
AutomataTransition_create_from_location_label(AutomataLoc_ptr end_location,
                                           AutomataLabel_ptr label);

/*!
  \methodof AutomataTransition
  \brief The AutomataTransition class destructor

  The AutomataTransition class destructor

  \sa AutomataTransition_create
*/
void AutomataTransition_destroy(AutomataTransition_ptr self);


/* Getters and Setters ********************************************************/

/*!
  \methodof AutomataTransition
  \brief Return the end location of transition

  
*/
AutomataLoc_ptr
AutomataTransition_get_end_location(AutomataTransition_ptr self);

/*!
  \methodof AutomataTransition
  \brief Returns the pointer to the label of the transition

  
*/
AutomataLabel_ptr
AutomataTransition_get_label(AutomataTransition_ptr self);

/*!
  \methodof AutomataTransition
  \brief Set the end location of transition to end_location

  
*/
void
AutomataTransition_set_end_location(AutomataTransition_ptr self,
                                 AutomataLoc_ptr end_location);

/*!
  \methodof AutomataTransition
  \brief Set the label of transition to label

  
*/
void AutomataTransition_set_label(AutomataTransition_ptr self,
                                         AutomataLabel_ptr label);


/**AutomaticEnd***************************************************************/



#endif /* __NUXMV_CORE_AUTOMATA_AUTOMATA_TRANSITION_H__ */
