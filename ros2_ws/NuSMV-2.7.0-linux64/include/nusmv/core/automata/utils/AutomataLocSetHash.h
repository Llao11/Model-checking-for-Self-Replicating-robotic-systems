/* ---------------------------------------------------------------------------

  This file is part of the ``utils'' package.
  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Sergio Mover
  \brief Public interface of class 'AutomataLocSetHash'

  \todo: Missing description

*/

#ifndef __NUXMV_CORE_AUTOMATA_UTILS_AUTOMATA_LOC_SET_HASH_H__
#define __NUXMV_CORE_AUTOMATA_UTILS_AUTOMATA_LOC_SET_HASH_H__

#include "nusmv/core/automata/AutomataLoc.h"
#include "nusmv/core/automata/utils/AutomataLocSet.h"

#include "nusmv/core/set/set.h"
#include "nusmv/core/utils/utils.h"

/*!
  \struct AutomataLocSetHash
  \brief Definition of the public accessor for class AutomataLocSetHash

*/
typedef struct AutomataLocSetHash_TAG*  AutomataLocSetHash_ptr;

/*!
  \brief To cast and check instances of class AutomataLocSetHash

  These macros must be used respectively to cast and to check
  instances of class AutomataLocSetHash
*/
#define AUTOMATA_LOC_SET_HASH(self) \
         ((AutomataLocSetHash_ptr) self)

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define AUTOMATA_LOC_SET_HASH_CHECK_INSTANCE(self) \
         (nusmv_assert(AUTOMATA_LOC_SET_HASH(self) != AUTOMATA_LOC_SET_HASH(NULL)))



/**AutomaticStart*************************************************************/

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \methodof AutomataLocSetHash
  \brief The AutomataLocSetHash class constructor

  The AutomataLocSetHash class constructor

  \sa AutomataLocSetHash_destroy
*/
AutomataLocSetHash_ptr
AutomataLocSetHash_create(BoolEnc_ptr bool_enc, int number_of_locations);

/*!
  \methodof AutomataLocSetHash
  \brief The AutomataLocSetHash class destructor

  The AutomataLocSetHash class destructor

  \sa AutomataLocSetHash_create
*/
void AutomataLocSetHash_destroy(AutomataLocSetHash_ptr self);

/*!
  \methodof AutomataLocSetHash
  \brief Inserts a new association from location_set to value

  
*/
void 
AutomataLocSetHash_insert(AutomataLocSetHash_ptr self, 
                            AutomataLocSet_ptr location_set,
                            AutomataLoc_ptr value);

/*!
  \methodof AutomataLocSetHash
  \brief Finds the value associated with key in the hash

  Returns the value associated with key if it
  exists. If the association does not exist then the Null is returned

  \sa AutomataLocSetHash_insert
*/
AutomataLoc_ptr
AutomataLocSetHash_find(AutomataLocSetHash_ptr self,
                          AutomataLocSet_ptr location_set);

/*!
  \methodof AutomataLocSetHash
  \brief Returns true iff hash contains the key

  

  \sa AutomataLocSetHash_find
*/
boolean
AutomataLocSetHash_has_key(AutomataLocSetHash_ptr self,
                             AutomataLocSet_ptr location_set);

/**AutomaticEnd***************************************************************/



#endif /* __NUXMV_CORE_AUTOMATA_UTILS_AUTOMATA_LOC_SET_HASH_H__ */
