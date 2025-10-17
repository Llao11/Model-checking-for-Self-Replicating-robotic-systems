/* ---------------------------------------------------------------------------

  This file is part of the ``utils'' package.
  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Sergio Mover
  \brief Public interface of class 'AutomataSimRel'

  \todo: Missing description

*/

#ifndef __NUXMV_CORE_AUTOMATA_UTILS_AUTOMATA_SIM_REL_H__
#define __NUXMV_CORE_AUTOMATA_UTILS_AUTOMATA_SIM_REL_H__

#include "nusmv/core/automata/AutomataLoc.h"
#include "nusmv/core/node/node.h"
#include "nusmv/core/utils/utils.h"

/*!
  \struct AutomataSimRel
  \brief Definition of the public accessor for class AutomataSimRel

  
*/
typedef struct AutomataSimRel_TAG*  AutomataSimRel_ptr;

/*!
  \brief To cast and check instances of class AutomataSimRel

  These macros must be used respectively to cast and to check
  instances of class AutomataSimRel
*/
#define AUTOMATA_SIM_REL(self) \
         ((AutomataSimRel_ptr) self)

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define AUTOMATA_SIM_REL_CHECK_INSTANCE(self) \
         (nusmv_assert(AUTOMATA_SIM_REL(self) != AUTOMATA_SIM_REL(NULL)))



/**AutomaticStart*************************************************************/

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \methodof AutomataSimRel
  \brief The AutomataSimRel class constructor

  The AutomataSimRel class constructor

  \sa AutomataSimRel_destroy
*/
AutomataSimRel_ptr AutomataSimRel_create(int n_locations);

/*!
  \methodof AutomataSimRel
  \brief The AutomataSimRel class destructor

  The AutomataSimRel class destructor

  \sa AutomataSimRel_create
*/
void AutomataSimRel_destroy(AutomataSimRel_ptr self);

/*!
  \methodof AutomataSimRel
  \brief Inserts couple (first_key, second_key) in the
  simulation relation.

  Inserts couple (first_key, second_key) in the
  simulation relation.
*/
void AutomataSimRel_insert(AutomataSimRel_ptr self, 
                                  AutomataLoc_ptr first_key,
                                  AutomataLoc_ptr second_key);

/*!
  \methodof AutomataSimRel
  \brief Returns true iff (first_key, second_key) is in
  the simulation relation.

  
*/
boolean AutomataSimRel_has_key(AutomataSimRel_ptr self, 
                                      AutomataLoc_ptr first_key,
                                      AutomataLoc_ptr second_key);

/*!
  \methodof AutomataSimRel
  \brief \todo Missing synopsis

  \todo Missing description
*/
node_ptr AutomataSimRel_get_keys(AutomataSimRel_ptr self);

/*!
  \methodof AutomataSimRel
  \brief Returns the representative location for the
  equivalence class of location.

  Returns the representative location for the
  equivalence class of location.
*/
AutomataLoc_ptr 
AutomataSimRel_get_representative(AutomataSimRel_ptr self,
                                  AutomataLoc_ptr location);

/*!
  \methodof AutomataSimRel
  \brief Returns the set of representants for each eq class.

  
*/
Set_t AutomataSimRel_get_all_rep(AutomataSimRel_ptr self);

/*!
  \brief Print couples contained in the simulation relation.

  
*/
void 
AutomataSimRel_print(AutomataSimRel_ptr sim_rel, FILE* out);

/*!
  \methodof AutomataSimRel
  \brief Inserts all location in bisimilar_locations list in
  the same bisimulation relation.

  Inserts all location in bisimilar_locations list in
  the same bisimulation relation.

  The representant location passed is used as representant of the
  equivalence classes. It has to be the location with the lower id.
*/
void 
AutomataSimRel_insert_bisimilar_list(AutomataSimRel_ptr self, 
                                     Slist_ptr bisimilar_locations,
                                     AutomataLoc_ptr representant);

/*!
  \methodof AutomataSimRel
  \brief Debug function used to check if bisimulation
  relation is consistent.

  Debug function used to check if bisimulation
  relation is consistent.

  It checks that each representative location of an equivalence class has
  itself as representative.
*/
void AutomataSimRel_check_consistency(AutomataSimRel_ptr self);

/**AutomaticEnd***************************************************************/



#endif /* __NUXMV_CORE_AUTOMATA_UTILS_AUTOMATA_SIM_REL_H__ */
