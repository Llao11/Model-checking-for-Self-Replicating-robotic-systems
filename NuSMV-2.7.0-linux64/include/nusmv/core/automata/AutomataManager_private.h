/* ---------------------------------------------------------------------------

  This file is part of the ``automata'' package.
  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Sergio Mover
  \brief Private and protected interface of class 'AutomataManager'

  This file can be included only by derived and friend classes

*/

#ifndef __NUXMV_CORE_AUTOMATA_AUTOMATA_MANAGER_PRIVATE_H__
#define __NUXMV_CORE_AUTOMATA_AUTOMATA_MANAGER_PRIVATE_H__


#include "nusmv/core/automata/AutomataManager.h"
#include "nusmv/core/utils/EnvObject.h"
#include "nusmv/core/utils/EnvObject_private.h"
#include "nusmv/core/utils/assoc.h"
#include "nusmv/core/utils/utils.h"


/*!
  \brief AutomataManager class definition derived from
               class EnvObject

  

  \sa Base class EnvObject
*/

typedef struct AutomataManager_TAG
{
  /* this MUST stay on the top */
  INHERITS_FROM(EnvObject);

  /* -------------------------------------------------- */
  /*                  Private members                   */
  /* -------------------------------------------------- */
  BoolEnc_ptr bool_enc;
  BddEnc_ptr bdd_enc;
  Automaton_Algorithm_Type algorithm_type;
  Automaton_Label_Type label_type;
  Automaton_ReductionAlgorithm_Type red_algo_type;

  boolean keep_automaton_type;
  boolean keep_complete;
  boolean keep_support_set_in_location;
  boolean minimize_automaton;
  boolean use_sim_reduction;
  boolean use_length_abstraction;

  st_table* alphabet_hash;

  /* -------------------------------------------------- */
  /*                  Virtual methods                   */
  /* -------------------------------------------------- */
  Automaton_Algorithm_Type (*get_algorithm_type)(AutomataManager_ptr self);

  void (*set_algorithm_type)(AutomataManager_ptr self,
                             Automaton_Algorithm_Type type);

  Automaton_Label_Type (*get_label_type)(AutomataManager_ptr self);

  void(*set_label_type)(AutomataManager_ptr self,
                        Automaton_Label_Type label_type);

  Automaton_ReductionAlgorithm_Type (*get_reduction_algo_type)(AutomataManager_ptr self);

  void (*set_reduction_algo_type)(AutomataManager_ptr self,
                                  Automaton_ReductionAlgorithm_Type type);


  boolean (*is_keep_automaton_type)(AutomataManager_ptr self);

  void(*set_keep_automaton_type)(AutomataManager_ptr self,
                                 boolean keep_automaton_type);

  boolean (*is_keep_complete)(AutomataManager_ptr self);

  void(*set_keep_complete)(AutomataManager_ptr self,
                           boolean keep_complete);

  boolean (*is_keep_support_set_in_location)(AutomataManager_ptr self);

  void(*set_keep_support_set_in_location)(AutomataManager_ptr self,
                                       boolean keep_support_set_in_location);

  boolean (*is_use_length_abstraction)(AutomataManager_ptr self);

  void(*set_use_length_abstraction)(AutomataManager_ptr self,
                                    boolean use_length_abstraction);

  boolean (*is_minimize_automaton)(AutomataManager_ptr self);

  void(*set_minimize_automaton)(AutomataManager_ptr self,
                                boolean minimize_automaton);

  boolean (*is_use_sim_reduction)(AutomataManager_ptr self);

  void(*set_use_sim_reduction)(AutomataManager_ptr self,
                               boolean use_sim_reduction);


  Set_t(*get_alphabet)(AutomataManager_ptr self,
                       Set_t support_set);

} AutomataManager;



/* ---------------------------------------------------------------------- */
/* Private methods to be used by derivated and friend classes only         */
/* ---------------------------------------------------------------------- */

/*!
  \methodof AutomataManager
  \brief The AutomataManager class private initializer

  The AutomataManager class private initializer

  \sa AutomataManager_create
*/
void automata_manager_init(AutomataManager_ptr self, NuSMVEnv_ptr env);

/*!
  \methodof AutomataManager
  \brief The AutomataManager class private deinitializer

  The AutomataManager class private deinitializer

  \sa AutomataManager_destroy
*/
void automata_manager_deinit(AutomataManager_ptr self);

/*!
  \methodof AutomataManager
  \brief Gets the type of the algorithm to use.

  
*/
Automaton_Algorithm_Type
automata_manager_get_algorithm_type(AutomataManager_ptr self);

/*!
  \methodof AutomataManager
  \brief Sets the type of algorithm to use.

  
*/
void
automata_manager_set_algorithm_type(AutomataManager_ptr self,
                                    Automaton_Algorithm_Type type);

/*!
  \methodof AutomataManager
  \brief Get the label type set in the manager.

  
*/
Automaton_Label_Type
automata_manager_get_label_type(AutomataManager_ptr self);

/*!
  \methodof AutomataManager
  \brief Sets the type of label that the manager will
  force to use.

  
*/
void
automata_manager_set_label_type(AutomataManager_ptr self,
                                Automaton_Label_Type label_type);

/*!
  \methodof AutomataManager
  \brief Gets the type of the reduction algorithm to use.

  
*/
Automaton_ReductionAlgorithm_Type
automata_manager_get_reduction_algo_type(AutomataManager_ptr self);

/*!
  \methodof AutomataManager
  \brief Sets the type of reduction algorithm to use.

  
*/
void
automata_manager_set_reduction_algo_type(AutomataManager_ptr self,
                                         Automaton_ReductionAlgorithm_Type type);

/*!
  \methodof AutomataManager
  \brief Returns the value of keep_automaton_type flag.

  
*/
boolean
automata_manager_is_keep_automaton_type(AutomataManager_ptr self);

/*!
  \methodof AutomataManager
  \brief Sets the value of keep_automaton_type flag.

  
*/
void
automata_manager_set_keep_automaton_type(AutomataManager_ptr self,
                                         boolean keep_automaton_type);

/*!
  \methodof AutomataManager
  \brief Returns the value of keep_complete flag.

  
*/
boolean
automata_manager_is_keep_complete(AutomataManager_ptr self);

/*!
  \methodof AutomataManager
  \brief Sets the value of keep_complete flag.

  
*/
void
automata_manager_set_keep_complete(AutomataManager_ptr self,
                                   boolean keep_complete);

/*!
  \methodof AutomataManager
  \brief Returns the value of keep_support_set_in_location flag.

  
*/
boolean
automata_manager_is_keep_support_set_in_location(AutomataManager_ptr self);

/*!
  \methodof AutomataManager
  \brief Sets the value of keep_support_set_in_location flag.

  
*/
void
automata_manager_set_keep_support_set_in_location(AutomataManager_ptr self,
                                               boolean keep_support_set_in_location);

/*!
  \methodof AutomataManager
  \brief Returns the value of use_length_abstraction flag.

  
*/
boolean
automata_manager_is_use_length_abstraction(AutomataManager_ptr self);

/*!
  \methodof AutomataManager
  \brief Sets the value of use_length_abstraction flag.

  
*/
void
automata_manager_set_use_length_abstraction(AutomataManager_ptr self,
                                           boolean use_length_abstraction);

/*!
  \methodof AutomataManager
  \brief Returns the value of minimize_automaton flag.

  
*/
boolean
automata_manager_is_minimize_automaton(AutomataManager_ptr self);

/*!
  \methodof AutomataManager
  \brief Sets the value of minimize_automaton flag.

  
*/
void
automata_manager_set_minimize_automaton(AutomataManager_ptr self,
                                        boolean minimize_automaton);

/*!
  \methodof AutomataManager
  \brief Returns the value of use_sim_reduction flag.

  
*/
boolean
automata_manager_is_use_sim_reduction(AutomataManager_ptr self);

/*!
  \methodof AutomataManager
  \brief Sets the value of use_sim_reduction flag.

  
*/
void
automata_manager_set_use_sim_reduction(AutomataManager_ptr self,
                                       boolean use_sim_reduction);

/*!
  \methodof AutomataManager
  \brief Builds the alphabet that is formed by
  propositions contained in support_set, a set of atomic propositions.

  Builds the alphabet formed by propositions
  contained in support_list, a set of atomic propositions. The
  alphabet is the power set of support_set.
  The power set is built calling automata_manager_get_alphabet_from_iter.

  \sa automata_manager_get_alphabet_from_iter
*/
Set_t
automata_manager_get_alphabet(AutomataManager_ptr self,
                             Set_t support_set);


#endif /* __NUXMV_CORE_AUTOMATA_AUTOMATA_MANAGER_PRIVATE_H__ */
