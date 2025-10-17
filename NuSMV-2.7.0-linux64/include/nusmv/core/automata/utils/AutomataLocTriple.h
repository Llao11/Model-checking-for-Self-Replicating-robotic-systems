/* ---------------------------------------------------------------------------

  This file is part of the ``utils'' package.
  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Sergio Mover
  \brief Public interface of class 'AutomataLocTriple'

  \todo: Missing description

*/

#ifndef __NUXMV_CORE_AUTOMATA_UTILS_AUTOMATA_LOC_TRIPLE_H__
#define __NUXMV_CORE_AUTOMATA_UTILS_AUTOMATA_LOC_TRIPLE_H__

#include "nusmv/core/utils/utils.h"
#include "nusmv/core/automata/AutomataLoc.h"

/*!
  \struct AutomataLocTriple
  \brief Definition of the public accessor for class AutomataLocTriple

*/
typedef struct AutomataLocTriple_TAG*  AutomataLocTriple_ptr;

/*!
  \brief To cast and check instances of class AutomataLocTriple

  These macros must be used respectively to cast and to check
  instances of class AutomataLocTriple
*/
#define AUTOMATA_LOC_TRIPLE(self) \
         ((AutomataLocTriple_ptr) self)

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define AUTOMATA_LOC_TRIPLE_CHECK_INSTANCE(self) \
         (nusmv_assert(AUTOMATA_LOC_TRIPLE(self) != AUTOMATA_LOC_TRIPLE(NULL)))



/**AutomaticStart*************************************************************/

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \methodof AutomataLocTriple
  \brief The AutomataLocTriple class constructor

  The AutomataLocTriple class constructor

  \sa AutomataLocTriple_destroy
*/
AutomataLocTriple_ptr AutomataLocTriple_create(void);

/*!
  \methodof AutomataLocTriple
  \brief The AutomataLocTriple class destructor

  The AutomataLocTriple class destructor

  \sa AutomataLocTriple_create
*/
void AutomataLocTriple_destroy(AutomataLocTriple_ptr self);

/*!
  \methodof AutomataLocTriple
  \brief Creates a triple from its three elements.

  
*/
AutomataLocTriple_ptr 
AutomataLocTriple_create_from_locations(AutomataLoc_ptr first,
                                       AutomataLoc_ptr second,
                                       AutomataLoc_ptr third);

/*!
  \brief Set the first element in the triple

  
*/
void
AutomataLocTriple_set_first(AutomataLocTriple_ptr triple,
                              AutomataLoc_ptr first_element);

/*!
  \brief Gets the first element in the triple

  
*/
AutomataLoc_ptr
AutomataLocTriple_get_first(AutomataLocTriple_ptr triple);

/*!
  \brief Set the second element in the triple

  
*/
void
AutomataLocTriple_set_second(AutomataLocTriple_ptr triple,
                               AutomataLoc_ptr second_element);

/*!
  \brief Gets the second element in the triple

  
*/
AutomataLoc_ptr
AutomataLocTriple_get_second(AutomataLocTriple_ptr triple);

/*!
  \brief Set the third element in the triple

  
*/
void
AutomataLocTriple_set_third(AutomataLocTriple_ptr triple,
                              AutomataLoc_ptr third_element);

/*!
  \brief Gets the third element in the triple

  
*/
AutomataLoc_ptr
AutomataLocTriple_get_third(AutomataLocTriple_ptr triple);

/**AutomaticEnd***************************************************************/



#endif /* __NUXMV_CORE_AUTOMATA_UTILS_AUTOMATA_LOC_TRIPLE_H__ */
