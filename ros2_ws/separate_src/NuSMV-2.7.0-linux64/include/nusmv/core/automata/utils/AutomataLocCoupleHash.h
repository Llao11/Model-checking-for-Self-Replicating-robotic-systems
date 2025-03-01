/* ---------------------------------------------------------------------------

  This file is part of the ``utils'' package.
  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Sergio Mover
  \brief Public interface of class 'AutomataLocCoupleHash'

  \todo: Missing description

*/

#ifndef __NUXMV_CORE_AUTOMATA_UTILS_AUTOMATA_LOC_COUPLE_HASH_H__
#define __NUXMV_CORE_AUTOMATA_UTILS_AUTOMATA_LOC_COUPLE_HASH_H__

#include "nusmv/core/automata/AutomataLoc.h"
#include "nusmv/core/node/node.h"
#include "nusmv/core/utils/utils.h"

/*!
  \struct AutomataLocCoupleHash
  \brief Definition of the public accessor for class
  AutomataLocCoupleHash

  
*/
typedef struct AutomataLocCoupleHash_TAG*  AutomataLocCoupleHash_ptr;

/*!
  \brief To cast and check instances of class AutomataLocCoupleHash

  These macros must be used respectively to cast and to check
  instances of class AutomataLocCoupleHash
*/
#define AUTOMATA_LOC_COUPLE_HASH(self) \
         ((AutomataLocCoupleHash_ptr) self)

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define AUTOMATA_LOC_COUPLE_HASH_CHECK_INSTANCE(self) \
  (nusmv_assert(AUTOMATA_LOC_COUPLE_HASH(self) != AUTOMATA_LOC_COUPLE_HASH(NULL)))



/**AutomaticStart*************************************************************/

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \methodof AutomataLocCoupleHash
  \brief The AutomataLocCoupleHash class constructor

  The AutomataLocCoupleHash class constructor

  \sa AutomataLocCoupleHash_destroy
*/
AutomataLocCoupleHash_ptr
AutomataLocCoupleHash_create(const NuSMVEnv_ptr env);

/*!
  \methodof AutomataLocCoupleHash
  \brief The AutomataLocCoupleHash class destructor

  The AutomataLocCoupleHash class destructor

  \sa AutomataLocCoupleHash_create
*/
void AutomataLocCoupleHash_destroy(AutomataLocCoupleHash_ptr self);

/*!
  \methodof AutomataLocCoupleHash
  \brief Inserts a new association in the hash

  Inserts the association from (first_key,
  second_key) to value. If (first_key, second_key) is already
  associated with an element then this association is replaced with
  the new one.

  \sa AutomataLocCoupleHash_find
*/
void 
AutomataLocCoupleHash_insert(AutomataLocCoupleHash_ptr self, 
                               AutomataLoc_ptr first_key,
                               AutomataLoc_ptr second_key,
                               void* value);

/*!
  \methodof AutomataLocCoupleHash
  \brief Finds the value associated with
  (first_key,second_key) in the hash

  Returns the value associated with (first_key, second_key) if it
  exists. If the association does not exist then the Null is returned

  \sa AutomataLocCoupleHash_insert
*/
void*
AutomataLocCoupleHash_find(AutomataLocCoupleHash_ptr self, 
                             AutomataLoc_ptr first_key,
                             AutomataLoc_ptr second_key);

/*!
  \methodof AutomataLocCoupleHash
  \brief Returns true iff hash contains the key

  

  \sa AutomataLocCoupleHash_find
*/
boolean
AutomataLocCoupleHash_has_key(AutomataLocCoupleHash_ptr self, 
                                AutomataLoc_ptr first_key,
                                AutomataLoc_ptr second_key);

/*!
  \methodof AutomataLocCoupleHash
  \brief Returns the list of keys contained in the hash.

  Returns the list of keys contained in the hash.

  Caller has to free the returned node list using free_list.
  Couples nodes (CONS node elements of the list) must NOT be freed
  since they are created using find_node.
*/
node_ptr 
AutomataLocCoupleHash_get_keys(AutomataLocCoupleHash_ptr self);

/**AutomaticEnd***************************************************************/



#endif /* __NUXMV_CORE_AUTOMATA_UTILS_AUTOMATA_LOC_COUPLE_HASH_H__ */
