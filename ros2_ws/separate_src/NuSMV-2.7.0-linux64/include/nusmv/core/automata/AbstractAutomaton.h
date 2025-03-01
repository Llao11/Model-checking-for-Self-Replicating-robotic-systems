/* ---------------------------------------------------------------------------


   %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Michele Dorigatti
  \brief Public interface of class 'AbstractAutomaton'

  \todo: Missing description

*/



#ifndef __NUXMV_CORE_AUTOMATA_ABSTRACT_AUTOMATON_H__
#define __NUXMV_CORE_AUTOMATA_ABSTRACT_AUTOMATON_H__

#include "nusmv/core/automata/AutomataLoc.h"

#include "nusmv/core/utils/object.h"
#include "nusmv/core/utils/utils.h"
#include "nusmv/core/utils/Slist.h"

/*!
  \struct AbstractAutomaton
  \brief Definition of the public accessor for class AbstractAutomaton

  
*/
typedef struct AbstractAutomaton_TAG*  AbstractAutomaton_ptr;

/*!
  \brief To cast and check instances of class AbstractAutomaton

  These macros must be used respectively to cast and to check
   instances of class AbstractAutomaton
*/
#define ABSTRACT_AUTOMATON(self)                \
  ((AbstractAutomaton_ptr) self)

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define ABSTRACT_AUTOMATON_CHECK_INSTANCE(self)                         \
  (nusmv_assert(ABSTRACT_AUTOMATON(self) != ABSTRACT_AUTOMATON(NULL)))



/**AutomaticStart*************************************************************/

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \methodof AbstractAutomaton
  \brief \todo Missing synopsis

  \todo Missing description
*/
AbstractAutomaton_ptr AbstractAutomaton_create(void);

/*!
  \methodof AbstractAutomaton
  \brief The AbstractAutomaton class destructor

  The AbstractAutomaton class destructor

  \sa AbstractAutomaton_create
*/
void AbstractAutomaton_destroy(AbstractAutomaton_ptr self);

/*!
  \methodof AbstractAutomaton
  \brief Returns a list that contains all the locations of
   automaton.

  Returns a list that contains all the locations of
   automaton.
*/
Slist_ptr
AbstractAutomaton_get_location_list(AbstractAutomaton_ptr self);

/*!
  \methodof AbstractAutomaton
  \brief Return the initial locations of automaton

  
*/
Set_t
AbstractAutomaton_get_initial_locations(AbstractAutomaton_ptr self);

/*!
  \methodof AbstractAutomaton
  \brief Returns the total number of transitions duplicated.

  Returns the total number of transitions duplicated.

   self transition is duplicated if there is another transition that has
   the same initial and final locations.

   This should be avoided and this function is used to test if it
   happens.
*/
int
AbstractAutomaton_get_transitions_duplicate_count(AbstractAutomaton_ptr self);

/*!
  \methodof AbstractAutomaton
  \brief Returns the number of locations of automaton.

  
*/
unsigned int
AbstractAutomaton_get_location_count(AbstractAutomaton_ptr self);

/*!
  \methodof AbstractAutomaton
  \brief Returns the number of transitions of automaton.

  WARNING: This is not for free. self loop over the locations is
   performed
*/
long
AbstractAutomaton_get_transitions_count(AbstractAutomaton_ptr self);

/*!
  \brief Adds a location of the automaton.

  Adds a location of the automaton.
   is_final determines if the added location is final or not. The function
   returns the location id of the automaton.
*/
int AbstractAutomaton_new_location(AutomataManager_ptr manager,
                                          AbstractAutomaton_ptr self,
                                          boolean is_final);

/*!
  \methodof AbstractAutomaton
  \brief Adds a location to the automaton.

  Adds a location to the automaton.
*/
void AbstractAutomaton_add_location(AbstractAutomaton_ptr self,
                                           AutomataLoc_ptr location);

/*!
  \brief Set the initial location

  
*/
void
AbstractAutomaton_add_initial_location(AbstractAutomaton_ptr const self,
                                       AutomataLoc_ptr const location);

/*!
  \brief Set sink location
 */
void AbstractAutomaton_set_sink_location (AbstractAutomaton_ptr self,
                                          AutomataLoc_ptr location);

/*!
  \brief Get sink location
 */
AutomataLoc_ptr
AbstractAutomaton_get_sink_location (AbstractAutomaton_ptr self);

/*!
  \brief Prints automaton on out_file

  
*/
void AbstractAutomaton_print(AbstractAutomaton_ptr A,
                                    NuSMVEnv_ptr env,
                                    FILE* out_file);

/*!
  \brief Prints automaton on out_file in dot format

  The function raises an error (AUTOMATA_ERROR_NULL_OUTPUT_FILE_MSG) if
  the output file pointer (out_file) is NULL.
*/
void AbstractAutomaton_print_dot(AbstractAutomaton_ptr A,
                                 NuSMVEnv_ptr env,
                                 FILE* out_file);

/**AutomaticEnd***************************************************************/



#endif /* __NUXMV_CORE_AUTOMATA_ABSTRACT_AUTOMATON_H__ */
