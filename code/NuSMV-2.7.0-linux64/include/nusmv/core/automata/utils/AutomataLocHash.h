/* ---------------------------------------------------------------------------

  This file is part of the ``utils'' package.
  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Sergio Mover
  \brief Public interface of class 'AutomataLocHash'

  \todo: Missing description

*/

#ifndef __NUXMV_CORE_AUTOMATA_UTILS_AUTOMATA_LOC_HASH_H__
#define __NUXMV_CORE_AUTOMATA_UTILS_AUTOMATA_LOC_HASH_H__

#include "nusmv/core/automata/AutomataLoc.h"
#include "nusmv/core/utils/utils.h"

/*!
  \struct AutomataLocHash
  \brief Definition of the public accessor for class AutomataLocHash

  
*/
typedef struct AutomataLocHash_TAG*  AutomataLocHash_ptr;

/*!
  \brief To cast and check instances of class AutomataLocHash

  These macros must be used respectively to cast and to check
  instances of class AutomataLocHash
*/
#define AUTOMATA_LOC_HASH(self) \
         ((AutomataLocHash_ptr) self)

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define AUTOMATA_LOC_HASH_CHECK_INSTANCE(self) \
         (nusmv_assert(AUTOMATA_LOC_HASH(self) != AUTOMATA_LOC_HASH(NULL)))



/**AutomaticStart*************************************************************/

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \methodof AutomataLocHash
  \brief The AutomataLocHash class constructor

  The AutomataLocHash class constructor

  \sa AutomataLocHash_destroy
*/
AutomataLocHash_ptr AutomataLocHash_create(void);

/*!
  \methodof AutomataLocHash
  \brief The AutomataLocHash class destructor

  The AutomataLocHash class destructor

  \sa AutomataLocHash_create
*/
void AutomataLocHash_destroy(AutomataLocHash_ptr self);

/*!
  \methodof AutomataLocHash
  \brief Inserts a new association in the hash

  Inserts the association from key to value in the
  hash table. If key is already associated with an element then this
  association is replaced with the new one.

  \se The hash table changes and the new association
  (key,value) is inserted or changed.

  \sa AutomataLocHash_find
*/
void 
AutomataLocHash_insert(AutomataLocHash_ptr self, 
                         AutomataLoc_ptr key,
                         AutomataLoc_ptr value);

/*!
  \methodof AutomataLocHash
  \brief Finds the value associated with key in the hash

  Returns the value associated with key if it
  exists. If the association does not exist then the Null is returned

  \sa AutomataLocHash_insert
*/
AutomataLoc_ptr
AutomataLocHash_find(AutomataLocHash_ptr self, AutomataLoc_ptr key);

/*!
  \methodof AutomataLocHash
  \brief Returns true iff hash contains the key

  

  \sa AutomataLocHash_find
*/
boolean
AutomataLocHash_has_key(AutomataLocHash_ptr self, AutomataLoc_ptr key);

/**AutomaticEnd***************************************************************/



#endif /* __NUXMV_CORE_AUTOMATA_UTILS_AUTOMATA_LOC_HASH_H__ */
