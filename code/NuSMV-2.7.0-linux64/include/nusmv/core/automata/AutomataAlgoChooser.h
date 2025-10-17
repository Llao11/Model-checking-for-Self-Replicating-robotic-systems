/* ---------------------------------------------------------------------------

  This file is part of the ``automata'' package.
  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Sergio Mover
  \brief Public interface of class 'AutomataAlgoChooser'

  \todo: Missing description

*/

#ifndef __NUXMV_CORE_AUTOMATA_AUTOMATA_ALGO_CHOOSER_H__
#define __NUXMV_CORE_AUTOMATA_AUTOMATA_ALGO_CHOOSER_H__

#include "nusmv/core/automata/automata.h"
#include "nusmv/core/automata/AutomataManager.h"
#include "nusmv/core/automata/AutomataLoc.h"
#include "nusmv/core/automata/AutomataTransition.h"
#include "nusmv/core/automata/utils/AutomataLocSet.h"

#include "nusmv/core/utils/utils.h"

/*!
  \struct AutomataAlgoChooser
  \brief Definition of the public accessor for class AutomataAlgoChooser

  
*/
typedef struct AutomataAlgoChooser_TAG*  AutomataAlgoChooser_ptr;

/*!
  \brief To cast and check instances of class AutomataAlgoChooser

  These macros must be used respectively to cast and to check
  instances of class AutomataAlgoChooser
*/
#define AUTOMATA_ALGO_CHOOSER(self) \
         ((AutomataAlgoChooser_ptr) self)

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define AUTOMATA_ALGO_CHOOSER_CHECK_INSTANCE(self) \
         (nusmv_assert(AUTOMATA_ALGO_CHOOSER(self) != AUTOMATA_ALGO_CHOOSER(NULL)))



/**AutomaticStart*************************************************************/

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \methodof AutomataAlgoChooser
  \brief The AutomataAlgoChooser class constructor

  The AutomataAlgoChooser class constructor

  \sa AutomataAlgoChooser_destroy
*/
AutomataAlgoChooser_ptr AutomataAlgoChooser_create(void);

/*!
  \methodof AutomataAlgoChooser
  \brief The AutomataAlgoChooser class destructor

  The AutomataAlgoChooser class destructor

  \sa AutomataAlgoChooser_create
*/
void AutomataAlgoChooser_destroy(AutomataAlgoChooser_ptr self);

/*!
  \methodof AutomataAlgoChooser
  \brief Set a location that must be always taken in account
  when choosing the algorithm type.

  Set a location that must be always taken in account
  when choosing the algorithm type.

  This allow to compute the support of the location and memoizing it.
  This is useful in fusion operation on automaton, when the support of
  the initial location of the second automaton is used in every check.

  Note that support is computed only if the type of method that the
  user wants to use is HEURISTIC_BASED or ALPHABET_BASED
*/
void
AutomataAlgoChooser_set_permanent_location(AutomataAlgoChooser_ptr self,
                                         AutomataManager_ptr manager,
                                         AutomataLoc_ptr permanent_location);

/*!
  \methodof AutomataAlgoChooser
  \brief Given two locations choose the algorithm type that
  will be used combining them.

  Given the manger, and two locations, s1 and s2,
  computes the type of algorithm to be used.
*/
Automaton_Algorithm_Type 
AutomataAlgoChooser_choose_from_location_couple(AutomataAlgoChooser_ptr self,
                                             AutomataManager_ptr manager,
                                             AutomataLoc_ptr s1,
                                             AutomataLoc_ptr s2);

/*!
  \methodof AutomataAlgoChooser
  \brief Given a transition choose the algorithm type to use

  Given the manger and a transition computes the
  type of algorithm to be used
*/
Automaton_Algorithm_Type
AutomataAlgoChooser_choose_from_trans(AutomataAlgoChooser_ptr self,
                                      AutomataManager_ptr manager,
                                      AutomataTransition_ptr trans);

/*!
  \methodof AutomataAlgoChooser
  \brief Given a set of locations choose the algorithm type that
  will be used combining them.

  Given the manger and a set of locations computes
  the type of algorithm to be used.
*/
Automaton_Algorithm_Type
AutomataAlgoChooser_choose_from_location_set(AutomataAlgoChooser_ptr self,
                                          AutomataManager_ptr manager,
                                          AutomataLocSet_ptr location_set);

/*!
  \methodof AutomataAlgoChooser
  \brief Returns the last support set computed by
  chooser.

  Returns the last support set computed by
  chooser. This is needed to reuse the support set computed when
  computing the heuristic.
  
  The caller MUST NOT destroy the obtained set, that will be destroyed
  by the chooser
*/
Set_t
AutomataAlgoChooser_get_last_support(AutomataAlgoChooser_ptr self);

/**AutomaticEnd***************************************************************/



#endif /* __NUXMV_CORE_AUTOMATA_AUTOMATA_ALGO_CHOOSER_H__ */
