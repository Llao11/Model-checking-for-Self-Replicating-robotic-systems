/* ---------------------------------------------------------------------------

  This file is part of the ``automata'' package.
  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Sergio Mover
  \brief Public interface of class 'AutomataLoc'

  \todo: Missing description

*/

#ifndef __NUXMV_CORE_AUTOMATA_AUTOMATA_LOC_H__
#define __NUXMV_CORE_AUTOMATA_AUTOMATA_LOC_H__

#include "nusmv/core/automata/automata.h"
#include "nusmv/core/automata/automataInt.h"
#include "nusmv/core/automata/AutomataManager.h"
#include "nusmv/core/automata/labels/AutomataLabel.h"

#include "nusmv/core/utils/assoc.h"
#include "nusmv/core/utils/Slist.h"
#include "nusmv/core/utils/utils.h"

/*!
  \struct AutomataLoc
  \brief Definition of the public accessor for class AutomataNamedLoc

  
*/
typedef struct AutomataLoc_TAG*  AutomataLoc_ptr;

/*!
  \brief To cast and check instances of class AutomataLoc

  These macros must be used respectively to cast and to check
  instances of class AutomataLoc
*/
#define AUTOMATA_LOC(self) \
         ((AutomataLoc_ptr) self)

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define AUTOMATA_LOC_CHECK_INSTANCE(self) \
         (nusmv_assert(AUTOMATA_LOC(self) != AUTOMATA_LOC(NULL)))



/**AutomaticStart*************************************************************/

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \methodof AutomataLoc
  \brief The AutomataLoc class constructor

  The AutomataLoc class constructor

  \sa AutomataLoc_destroy
*/
AutomataLoc_ptr
AutomataLoc_create(Automaton_Label_Type label_type,
                     boolean keep_support_location);

/*!
  \methodof AutomataLoc
  \brief The AutomataLoc class constructor from manager

  The AutomataLoc class constructor from
   manager. It constructs location and set parameters from the manager
   object.

   The parameter that is set is keep_support_set, that enable or
   disable the hashing of support set in a location.
   Another parameter is the type of labels that will be used.

  \sa AutomataLoc_destroy
*/
AutomataLoc_ptr
AutomataLoc_create_from_manager(AutomataManager_ptr manager);

/*!
  \methodof AutomataLoc
  \brief The AutomataLoc class destructor

  The AutomataLoc class destructor

  \sa AutomataLoc_create
*/
void AutomataLoc_destroy(AutomataLoc_ptr self);

/*!
  \methodof AutomataLoc
  \brief Returns the id of the location

  
*/
int AutomataLoc_get_id(AutomataLoc_ptr self);

/*!
  \methodof AutomataLoc
  \brief required

  optional

  \se required

  \sa optional
*/
void
AutomataLoc_set_id(AutomataLoc_ptr self, int id);

/*!
  \methodof AutomataLoc
  \brief Returns true if the location is final, false otherwise

  
*/
boolean AutomataLoc_is_final(AutomataLoc_ptr self);

/*!
  \methodof AutomataLoc
  \brief Set/Unset the final flag of the location

  
*/
void
AutomataLoc_set_final(AutomataLoc_ptr self, boolean final);

/*!
  \methodof AutomataLoc
  \brief Returns the type of the location

  
*/
Automaton_Type AutomataLoc_get_type(AutomataLoc_ptr self);

/*!
  \methodof AutomataLoc
  \brief Set the type of the location

  
*/
void AutomataLoc_set_type(AutomataLoc_ptr self,
                                   const Automaton_Type new_type);

/*!
  \methodof AutomataLoc
  \brief Returns the value of the is_complete flag

  
*/
boolean AutomataLoc_is_complete(AutomataLoc_ptr self);

/*!
  \methodof AutomataLoc
  \brief Set the is_complete flag

  
*/
void AutomataLoc_set_is_complete(AutomataLoc_ptr self,
                                          boolean is_complete);

/*!
  \methodof AutomataLoc
  \brief Create a new transition that leaves the location

  Creates a new transition that ends in end_location
   with label, and adds this transition to the transition that leaves
   self location.
*/
AutomataTransition_ptr
AutomataLoc_create_transition(AutomataLoc_ptr self,
                                AutomataLoc_ptr end_location,
                                AutomataLabel_ptr label,
                                ErrorMgr_ptr errmgr);

/*!
  \methodof AutomataLoc
  \brief Returns the number of transitions contained in
   the location.

  
*/
int AutomataLoc_get_transitions_count(AutomataLoc_ptr self);

/*!
  \methodof AutomataLoc
  \brief Returns all the transitions that start from the
   location

  Returns the stack that contains all the
   transItion that starts from self location. The caller does not belongs
   the stack.
*/
Slist_ptr
AutomataLoc_get_transitions(AutomataLoc_ptr self);

/*!
  \methodof AutomataLoc
  \brief All the transitions of the location are deleted.

  All the transitions fo the location are deleted.

  \se Internal transition of the location are delted.
*/
void
AutomataLoc_reset_transitions(AutomataLoc_ptr self);

/*!
  \methodof AutomataLoc
  \brief Creates and return a copy of location. The final
   flag on location is copied only if keep_final is true, and all the
   transitions are copied only if keep_trans is true.

  Creates and return a copy of location. The final
   flag on location is copied only if keep_final is true. Note that type
   information and is_complete information are not copied in the new location
*/
AutomataLoc_ptr AutomataLoc_copy(AutomataLoc_ptr self,
                                            boolean keep_final_info,
                                            Automaton_Label_Type label_type,
                                            boolean keep_support_set);

/*!
  \methodof AutomataLoc
  \brief Merge duplicate transitions

  
*/
void AutomataLoc_merge_duplicates(AutomataLoc_ptr self);

/*!
  \methodof AutomataLoc
  \brief Updates the type of the location, checking if it is
   deterministic. The found type is returned,

  

  \se The type of the location is updated
*/
Automaton_Type AutomataLoc_update_type(AutomataLoc_ptr self);

/*!
  \methodof AutomataLoc
  \brief Check if location is complete. If a location is not
   complete then it is completed creating a true transition to the sink location

  Sink location must be created previously. True is
   returend if self was changed, so if at least a new transition is
   created to a sink location.   The BddEnc can be null if the type of self is not BDD_LABEL
*/
boolean AutomataLoc_update_is_complete(AutomataLoc_ptr self,
                                                AutomataLoc_ptr sink,
                                                BddEnc_ptr bdd_enc);

/*!
  \methodof AutomataLoc
  \brief Returns the support set of the location

  The support set for the location is returned. If
   the location memoize the set the memoized set is returned. If no set is
   memoized then the support set is computed

  \sa automata_loc_compute_support_set
*/
Set_t AutomataLoc_get_support_set(AutomataLoc_ptr self);

/*!
  \methodof AutomataLoc
  \brief Prints a the location on a stream

  Prints the location on a stream.
*/
void AutomataLoc_print(AutomataLoc_ptr self,
                              NuSMVEnv_ptr env,
                              FILE* outfile);

/*!
  \methodof AutomataLoc
  \brief Prints a the location on a stream in dot format

  Prints the location on a stream in dot format.
*/
void AutomataLoc_print_dot(AutomataLoc_ptr self,
                                  NuSMVEnv_ptr env,
                                  FILE* outfile);

/**AutomaticEnd***************************************************************/



#endif /* __NUXMV_CORE_AUTOMATA_AUTOMATA_LOC_H__ */
