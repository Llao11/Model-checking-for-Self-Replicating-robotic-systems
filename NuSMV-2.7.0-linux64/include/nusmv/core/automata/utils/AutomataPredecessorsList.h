/* ---------------------------------------------------------------------------


  This file is part of the ``utils'' package.
  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Sergio Mover
  \brief Public interface of class 'AutomataPredecessorsList'

  \todo: Missing description

*/



#ifndef __NUXMV_CORE_AUTOMATA_UTILS_AUTOMATA_PREDECESSORS_LIST_H__
#define __NUXMV_CORE_AUTOMATA_UTILS_AUTOMATA_PREDECESSORS_LIST_H__

#include "nusmv/core/automata/AutomataLoc.h"

#include "nusmv/core/utils/utils.h" 
#include "nusmv/core/utils/Slist.h"

/*!
  \struct AutomataPredecessorsList
  \brief Definition of the public accessor for class AutomataPredecessorsList

  
*/
typedef struct AutomataPredecessorsList_TAG*  AutomataPredecessorsList_ptr;

/*!
  \brief To cast and check instances of class AutomataPredecessorsList

  These macros must be used respectively to cast and to check
  instances of class AutomataPredecessorsList
*/
#define AUTOMATA_PREDECESSORS_LIST(self) \
         ((AutomataPredecessorsList_ptr) self)

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define AUTOMATA_PREDECESSORS_LIST_CHECK_INSTANCE(self) \
         (nusmv_assert(AUTOMATA_PREDECESSORS_LIST(self) != AUTOMATA_PREDECESSORS_LIST(NULL)))



/**AutomaticStart*************************************************************/

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \methodof AutomataPredecessorsList
  \brief The AutomataPredecessorsList class constructor

  The AutomataPredecessorsList class constructor

  \sa AutomataPredecessorsList_destroy
*/
AutomataPredecessorsList_ptr 
AutomataPredecessorsList_create(int location_count);

/*!
  \methodof AutomataPredecessorsList
  \brief The AutomataPredecessorsList class destructor

  The AutomataPredecessorsList class destructor

  \sa AutomataPredecessorsList_create
*/
void AutomataPredecessorsList_destroy(AutomataPredecessorsList_ptr self);

/*!
  \methodof AutomataPredecessorsList
  \brief Insert a predecessor in the predecessor list

  
*/
void AutomataPredecessorsList_insert(AutomataPredecessorsList_ptr self,
                                            AutomataLoc_ptr location,
                                            AutomataLoc_ptr predecessor);

/*!
  \methodof AutomataPredecessorsList
  \brief Get the predecessors list of location

  
*/
Slist_ptr 
AutomataPredecessorsList_get_predecessor(AutomataPredecessorsList_ptr self,
                                         AutomataLoc_ptr location);

/*!
  \methodof AutomataPredecessorsList
  \brief Adds the predeccessors of location to predeccessors_list

  

  \se predeccessors_list is changed.
*/
void 
AutomataPredecessorsList_add_pred_to_list(AutomataPredecessorsList_ptr self,
                                          AutomataLoc_ptr location,
                                          Slist_ptr predeccessors_list);

/**AutomaticEnd***************************************************************/



#endif /* __NUXMV_CORE_AUTOMATA_UTILS_AUTOMATA_PREDECESSORS_LIST_H__ */
