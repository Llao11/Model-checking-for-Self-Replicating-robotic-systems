/* ---------------------------------------------------------------------------


   %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Michele Dorigatti
  \brief Private and protected interface of class 'AbstractAutomaton'

  This file can be included only by derived and friend classes

*/

#ifndef __NUXMV_CORE_AUTOMATA_ABSTRACT_AUTOMATON_PRIVATE_H__
#define __NUXMV_CORE_AUTOMATA_ABSTRACT_AUTOMATON_PRIVATE_H__

#include "nusmv/core/automata/AbstractAutomaton.h"
#include "nusmv/core/utils/object.h"
#include "nusmv/core/utils/object_private.h"
#include "nusmv/core/utils/utils.h"

#include "nusmv/core/set/set.h"
#include "nusmv/core/utils/Slist.h"
#include "nusmv/core/automata/AutomataManager.h"
#include "nusmv/core/automata/AutomataLoc.h"
#include "nusmv/core/automata/AutomataTransition.h"
#include "nusmv/core/automata/labels/AutomataLabel.h"

/*---------------------------------------------------------------------------*/
/* Macro declarations                                                        */
/*---------------------------------------------------------------------------*/
/* For printing */

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define INDENT_STRING "  "

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define START_TAG 0

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define EMPTY_TAG 1

/* An ID of a location or a trans needs at most 13 bytes to be represented: */
/* "_s" (2) + string dimension of UINT_MAX (10) + \0 (1) */

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define ID_SIZE 13

/*!
  \brief AbstractAutomaton class definition derived from
   class Object

  This is a base abstract class. It provides a common interface to
   several specialized automata. An effort has been made to keep it as general
   as possible, so it includes only field and methods about locations,
   transitions and generic labels.  The AbstractAutomaton contains:

   - initial_locations: the initial location of the abstract_automaton. In this
   representation only one initial location is allowed. All algorithms performed
   on <tt>Automaton_TAG</tt> rely on this assumption.

   - location_count: the total number of locations of the abstract_automaton

   - locations: a list that contains all the locations of the abstract_automaton. The
   list is not ordered with any criteria and is mainly used as iterator on all
   the locations.

   - type: the type of the abstract_automaton. The abstract_automaton can be deterministic,
   non-deterministic or its type is unknown.

   - label_type: the implementation of label used in the abstract_automaton.

  \sa Base class Object
*/

typedef struct AbstractAutomaton_TAG
{
  /* this MUST stay on the top */
  INHERITS_FROM(Object);

  /* -------------------------------------------------- */
  /*                  Private members                   */
  /* -------------------------------------------------- */
  AutomataLoc_ptr sink_location;
  Set_t initial_locations;
  unsigned int location_count;
  Slist_ptr locations;
  Automaton_Type type;
  Automaton_Label_Type label_type;

  /* -------------------------------------------------- */
  /*                  Virtual methods                   */
  /* -------------------------------------------------- */
  Slist_ptr (*get_location_list)(AbstractAutomaton_ptr self);

  Set_t (*get_initial_locations)(AbstractAutomaton_ptr self);

  void (*add_initial_location)(AbstractAutomaton_ptr const self,
                               AutomataLoc_ptr const location);

  unsigned int (*get_location_count) (AbstractAutomaton_ptr A);

  long (*get_transitions_count) (AbstractAutomaton_ptr A);

  int (*new_location) (AutomataManager_ptr manager,
                       AbstractAutomaton_ptr A,
                       boolean is_final);

  void (*print)(AbstractAutomaton_ptr A, NuSMVEnv_ptr env, FILE* out_file);

  void (*print_dot)(AbstractAutomaton_ptr A, NuSMVEnv_ptr env, FILE* out_file);

  void (*print_xmi)(AbstractAutomaton_ptr self, FILE* out_file);

  AutomataLoc_ptr (*create_location)(AbstractAutomaton_ptr self,
                                     Automaton_Label_Type label_type,
                                     boolean keep_support_location);

  AutomataLoc_ptr (*create_location_from_manager)(AbstractAutomaton_ptr self,
                                                  AutomataManager_ptr manager);

  void (*add_location)(AbstractAutomaton_ptr self,
                       AutomataLoc_ptr location);

  int (*get_transitions_duplicate_count) (AbstractAutomaton_ptr A);

  void (*set_sink_location)(AbstractAutomaton_ptr self,
                            AutomataLoc_ptr location);

  AutomataLoc_ptr (*get_sink_location)(AbstractAutomaton_ptr self);

} AbstractAutomaton;



/* ---------------------------------------------------------------------- */
/* Private methods to be used by derivated and friend classes only         */
/* ---------------------------------------------------------------------- */

/*!
  \methodof AbstractAutomaton
  \brief The AbstractAutomaton class private initializer

  The AbstractAutomaton class private initializer

  \sa AbstractAutomaton_create
*/
void abstract_automaton_init(AbstractAutomaton_ptr self);

/*!
  \methodof AbstractAutomaton
  \brief The AbstractAutomaton class private deinitializer

  The AbstractAutomaton class private deinitializer

  \sa AbstractAutomaton_destroy
*/
void abstract_automaton_deinit(AbstractAutomaton_ptr self);


/* Getters and Setters ********************************************************/

/*!
  \methodof AbstractAutomaton
  \brief Return a list of locations of abstract_automaton.

  Returns a list of locations of abstract_automaton.
*/
Slist_ptr
abstract_automaton_get_location_list(AbstractAutomaton_ptr self);

/*!
  \methodof AbstractAutomaton
  \brief Return the initial locations of the abstract_automaton.

  
*/
Set_t
abstract_automaton_get_initial_locations(AbstractAutomaton_ptr self);

/*!
  \brief Set the initial location

  
*/
void
abstract_automaton_add_initial_location(AbstractAutomaton_ptr const self,
                                        AutomataLoc_ptr const location);


/* Miscellaneous **************************************************************/

/*!
  \methodof AbstractAutomaton
  \brief Creates a location

  Creates a location

  \sa AutomataLoc_create
*/
AutomataLoc_ptr
abstract_automaton_create_loc(AbstractAutomaton_ptr self,
                              Automaton_Label_Type label_type,
                              boolean keep_support_location);

/*!
  \methodof AbstractAutomaton
  \brief Creates a location using the information stored in the manager

  The parameter that is set is keep_support_set, that enable or
   disable the hashing of support set in a location.
   Another parameter is the type of labels that will be used.

  \sa AutomataLoc_create_from_manager
*/
AutomataLoc_ptr
abstract_automaton_create_loc_from_manager(AbstractAutomaton_ptr self,
                                           AutomataManager_ptr manager);

/*!
  \brief Pure virtual function, prints abstract_automaton on
   out_file.

  Every derived class must overwrite this function.
*/
void abstract_automaton_print(AbstractAutomaton_ptr A,
                                     NuSMVEnv_ptr env,
                                     FILE* out_file);

/*!
  \brief Pure virtual function, prints abstract_automaton on
   out_file in dot format.

  Every derived class must overwrite this function.
*/
void abstract_automaton_print_dot(AbstractAutomaton_ptr A,
                                         NuSMVEnv_ptr env,
                                         FILE* out_file);

/*!
  \brief Returns the total number of transitions duplicated.

  Returns the total number of transitions duplicated.

   A transition is duplicated if there is another transition that has
   the same initial and final locations.

   This should be avoided and this function is used to test if it
   happens.
*/
int
abstract_automaton_get_transitions_duplicate_count(AbstractAutomaton_ptr A);

/*!
  \brief Returns the number of locations of abstract_automaton.

  
*/
unsigned int
abstract_automaton_get_location_count(AbstractAutomaton_ptr A);

/*!
  \brief Returns the number of transitions of abstract_automaton.

  
*/
long
abstract_automaton_get_transitions_count(AbstractAutomaton_ptr A);

/*!
  \brief Adds a new location to the abstract_automaton.

  
*/
int abstract_automaton_new_loc(AutomataManager_ptr manager,
                                      AbstractAutomaton_ptr A,
                                      boolean is_final);

/*!
  \methodof AbstractAutomaton
  \brief Adds location to the abstract_automaton

  Adds location to the list of locations of
   abstract_automaton. This function is useful to keep count of the number of
   locations of the abstract_automaton.
*/
void abstract_automaton_add_loc(AbstractAutomaton_ptr self,
                                       AutomataLoc_ptr location);

void abstract_automaton_set_sink_location(AbstractAutomaton_ptr self,
                                          AutomataLoc_ptr location);

AutomataLoc_ptr
abstract_automaton_get_sink_location(AbstractAutomaton_ptr self);

#endif /* __NUXMV_CORE_AUTOMATA_ABSTRACT_AUTOMATON_PRIVATE_H__ */
