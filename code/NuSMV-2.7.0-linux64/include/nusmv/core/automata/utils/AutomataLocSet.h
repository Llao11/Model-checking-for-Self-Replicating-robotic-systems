/* ---------------------------------------------------------------------------

  This file is part of the ``utils'' package.
  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Sergio Mover
  \brief Public interface of class 'AutomataLocSet'

  \todo: Missing description

*/

#ifndef __NUXMV_CORE_AUTOMATA_UTILS_AUTOMATA_LOC_SET_H__
#define __NUXMV_CORE_AUTOMATA_UTILS_AUTOMATA_LOC_SET_H__

#include "nusmv/core/automata/AutomataLoc.h"

#include "nusmv/core/set/set.h"
#include "nusmv/core/node/node.h"
#include "nusmv/core/utils/utils.h"

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define STATE_SET_FOREACH(set, iter)                                    \
  for (iter=AutomataLocSet_get_first_iter(set);                       \
       !Set_IsEndIter(iter);                                            \
       iter=Set_GetNextIter(iter))

/*!
  \struct AutomataLocSet
  \brief Definition of the public accessor for class AutomataLocSet

  
*/
typedef struct AutomataLocSet_TAG*  AutomataLocSet_ptr;

/*!
  \brief To cast and check instances of class AutomataLocSet

  These macros must be used respectively to cast and to check
  instances of class AutomataLocSet
*/
#define AUTOMATA_LOC_SET(self) \
         ((AutomataLocSet_ptr) self)

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define AUTOMATA_LOC_SET_CHECK_INSTANCE(self) \
         (nusmv_assert(AUTOMATA_LOC_SET(self) != AUTOMATA_LOC_SET(NULL)))



/**AutomaticStart*************************************************************/

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \methodof AutomataLocSet
  \brief The AutomataLocSet class constructor

  The AutomataLocSet class constructor

  \sa AutomataLocSet_destroy
*/
AutomataLocSet_ptr AutomataLocSet_create(const NuSMVEnv_ptr env);

/*!
  \methodof AutomataLocSet
  \brief The AutomataLocSet class destructor

  The AutomataLocSet class destructor

  \sa AutomataLocSet_create
*/
void AutomataLocSet_destroy(AutomataLocSet_ptr self);

/*!
  \methodof AutomataLocSet
  \brief Add a new location to the set

  Add location to the set. Adding the location also
  updates the id list.
*/
void AutomataLocSet_add_element(AutomataLocSet_ptr self,
                                         AutomataLoc_ptr location);

/*!
  \methodof AutomataLocSet
  \brief Performs the union of self with location_set

  Performs the union of self with location_set. This
  operations change self, storing in it the union.
*/
void AutomataLocSet_union(AutomataLocSet_ptr self,
                                   AutomataLocSet_ptr location_set);

/*!
  \methodof AutomataLocSet
  \brief Return true if the set is empty

  
*/
boolean AutomataLocSet_is_empty(AutomataLocSet_ptr self);

/*!
  \methodof AutomataLocSet
  \brief Returns the set of location used by
  AutomataLocSet to store locations.

  Returns the set of location used by
  AutomataLocSet to store locations.

  There are some issues about returning the set used internally by the
  class that needs to be considered.
*/
Set_t AutomataLocSet_get_set(AutomataLocSet_ptr self);

/*!
  \methodof AutomataLocSet
  \brief Get the iterator to the first element of the
  location set.

  
*/
Set_Iterator_t 
AutomataLocSet_get_first_iter(AutomataLocSet_ptr self);

/*!
  \methodof AutomataLocSet
  \brief Get the element in the location set pointed by the
  iterator iter.

  
*/
AutomataLoc_ptr 
AutomataLocSet_get_member(AutomataLocSet_ptr self,
                            Set_Iterator_t iter);

/*!
  \methodof AutomataLocSet
  \brief Returns true if the set contains a location with
  the given id.

  
*/
boolean 
AutomataLocSet_is_member_from_id(AutomataLocSet_ptr self,
                                   int id);

/*!
  \methodof AutomataLocSet
  \brief Returns true if the id_list contains id_node.

  
*/
boolean 
AutomataLocSet_is_member_from_id_node(AutomataLocSet_ptr self,
                                        node_ptr id_node);

/*!
  \methodof AutomataLocSet
  \brief Returns true if location is an element of the set.

  
*/
boolean AutomataLocSet_is_memeber(AutomataLocSet_ptr self,
                                           AutomataLoc_ptr location);

/*!
  \methodof AutomataLocSet
  \brief Return the maximum id stored in the set.

  
*/
int AutomataLocSet_get_max_id(AutomataLocSet_ptr self);

/*!
  \methodof AutomataLocSet
  \brief Creates a copy of the AutomataLocSet self

  
*/
AutomataLocSet_ptr AutomataLocSet_copy(AutomataLocSet_ptr self);



/**AutomaticEnd***************************************************************/



#endif /* __NUXMV_CORE_AUTOMATA_UTILS_AUTOMATA_LOC_SET_H__ */
