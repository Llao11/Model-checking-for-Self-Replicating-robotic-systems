/* ---------------------------------------------------------------------------

  This file is part of the ``automata'' package.
  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Sergio Mover
  \brief Public interface of class 'AutomataManager'

  \todo: Missing description

*/

#ifndef __NUXMV_CORE_AUTOMATA_AUTOMATA_MANAGER_H__
#define __NUXMV_CORE_AUTOMATA_AUTOMATA_MANAGER_H__


#include "nusmv/core/utils/object.h"
#include "nusmv/core/utils/utils.h"
#include "nusmv/core/enc/bool/BoolEnc.h"
#include "nusmv/core/enc/bdd/BddEnc.h"
#include "nusmv/core/set/set.h"
#include "nusmv/core/automata/automata.h"

/*!
  \struct AutomataManager
  \brief Definition of the public accessor for class AutomataManager

  
*/
typedef struct AutomataManager_TAG*  AutomataManager_ptr;

/*!
  \brief To cast and check instances of class AutomataManager

  These macros must be used respectively to cast and to check
  instances of class AutomataManager
*/
#define AUTOMATA_MANAGER(self) \
         ((AutomataManager_ptr) self)

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define AUTOMATA_MANAGER_CHECK_INSTANCE(self) \
         (nusmv_assert(AUTOMATA_MANAGER(self) != AUTOMATA_MANAGER(NULL)))



/**AutomaticStart*************************************************************/

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \methodof AutomataManager
  \brief The AutomataManager class constructor

  The AutomataManager class constructor

  \sa AutomataManager_destroy
*/
AutomataManager_ptr AutomataManager_create(NuSMVEnv_ptr env);

/*!
  \methodof AutomataManager
  \brief The AutomataManager class destructor

  The AutomataManager class destructor

  \sa AutomataManager_create
*/
void AutomataManager_destroy(AutomataManager_ptr self);

/*!
  \methodof AutomataManager
  \brief The AutomataManager bool enc getter

  The AutomataManager bool enc getter

  \sa AutomataManager_create
*/
BoolEnc_ptr AutomataManager_get_bool_enc(AutomataManager_ptr self);

/*!
  \methodof AutomataManager
  \brief The AutomataManager bool enc getter

  The AutomataManager bool enc getter

  \sa AutomataManager_create
*/
BddEnc_ptr AutomataManager_get_bdd_enc(AutomataManager_ptr self);

/*!
  \methodof AutomataManager
  \brief Gets the type of the algorithm to use.

  
*/
Automaton_Algorithm_Type
AutomataManager_get_algorithm_type(AutomataManager_ptr self);

/*!
  \methodof AutomataManager
  \brief Sets the type of algorithm to use.

  
*/
void
AutomataManager_set_algorithm_type(AutomataManager_ptr self,
                                   Automaton_Algorithm_Type type);

/*!
  \methodof AutomataManager
  \brief Get the label type set in the manager

  
*/
Automaton_Label_Type
AutomataManager_get_label_type(AutomataManager_ptr self);

/*!
  \methodof AutomataManager
  \brief Set the label type

  
*/
void
AutomataManager_set_label_type(AutomataManager_ptr self,
                               Automaton_Label_Type label_type);

/*!
  \methodof AutomataManager
  \brief Get the reduction algorithm type.

  
*/
Automaton_ReductionAlgorithm_Type
AutomataManager_get_reduction_algo_type(AutomataManager_ptr self);

/*!
  \methodof AutomataManager
  \brief Set the reduction algorithm to use.

  
*/
void
AutomataManager_set_reduction_algo_type(AutomataManager_ptr self,
                                        Automaton_ReductionAlgorithm_Type type);

/*!
  \methodof AutomataManager
  \brief Returns the value of keep_automaton_type flag.

  
*/
boolean
AutomataManager_is_keep_automaton_type(AutomataManager_ptr self);

/*!
  \methodof AutomataManager
  \brief Sets the value of keep_automaton_type flag.

  
*/
void
AutomataManager_set_keep_automaton_type(AutomataManager_ptr self,
                                        boolean keep_automaton_type);

/*!
  \methodof AutomataManager
  \brief Returns the value of keep_complete flag.

  
*/
boolean
AutomataManager_is_keep_complete(AutomataManager_ptr self);

/*!
  \methodof AutomataManager
  \brief Sets the value of keep_complete flag.

  
*/
void
AutomataManager_set_keep_complete(AutomataManager_ptr self,
                                  boolean keep_complete);

/*!
  \methodof AutomataManager
  \brief Returns the value of keep_support_set_in_location flag.

  
*/
boolean
AutomataManager_is_keep_support_set_in_location(AutomataManager_ptr self);

/*!
  \methodof AutomataManager
  \brief Sets the value of keep_support_set_in_location flag.

  
*/
void
AutomataManager_set_keep_support_set_in_location(AutomataManager_ptr self,
                                              boolean keep_support_set_in_location);

/*!
  \methodof AutomataManager
  \brief Returns the value of use_length_abstraction flag.

  
*/
boolean
AutomataManager_is_use_length_abstraction(AutomataManager_ptr self);

/*!
  \methodof AutomataManager
  \brief Sets the value of use_length_abstraction flag.

  
*/
void
AutomataManager_set_use_length_abstraction(AutomataManager_ptr self,
                                           boolean use_length_abstraction);

/*!
  \methodof AutomataManager
  \brief Returns the value of use_sim_reduction flag.

  
*/
boolean
AutomataManager_is_use_sim_reduction(AutomataManager_ptr self);

/*!
  \methodof AutomataManager
  \brief Sets the value of use_sim_reduction flag.

  
*/
void
AutomataManager_set_use_sim_reduction(AutomataManager_ptr self,
                                      boolean use_sim_reduction);

/*!
  \methodof AutomataManager
  \brief Returns the value of minimize_automaton flag.

  
*/
boolean
AutomataManager_is_minimize_automaton(AutomataManager_ptr self);

/*!
  \methodof AutomataManager
  \brief Sets the value of minimize_automaton flag.

  
*/
void
AutomataManager_set_minimize_automaton(AutomataManager_ptr self,
                                       boolean minimize_automaton);

/*!
  \methodof AutomataManager
  \brief Builds the alphabet given a set of atomic propositions.

  Given the support_set that contains atomic
  propositions, the power set of support_set is returned. The power
  set is the alphabet.
*/
Set_t
AutomataManager_get_alphabet(AutomataManager_ptr self,
                             Set_t support_set);

/**AutomaticEnd***************************************************************/



#endif /* __NUXMV_CORE_AUTOMATA_AUTOMATA_MANAGER_H__ */
