/* ---------------------------------------------------------------------------

  This file is part of the ``automata'' package.
  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Sergio Mover
  \brief Interface for <tt>automata</tt> package

  This package contains the generic interface to access
  the automata package.

*/


#include "nusmv/core/utils/utils.h"
#include "nusmv/core/cinit/NuSMVEnv.h"


#ifndef __NUXMV_CORE_AUTOMATA_AUTOMATA_H__
#define __NUXMV_CORE_AUTOMATA_AUTOMATA_H__

/*---------------------------------------------------------------------------*/
/* Nested includes                                                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Constant declarations                                                     */
/*---------------------------------------------------------------------------*/
//#define DEBUG_AUTOMATA

/*---------------------------------------------------------------------------*/
/* Structure declarations                                                    */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Type declarations                                                         */
/*---------------------------------------------------------------------------*/
/*!
  \brief Type of the automaton

  The types of automaton defines if the automaton is
  deterministic, non-deterministic or if this information is unknown.
*/

enum Automaton_Type_TAG{
  DETERMINISTIC=0,
  NON_DETERMINISTIC=1,
  UNKNOWN=2
};
typedef enum Automaton_Type_TAG Automaton_Type;

/*!
  \brief Type of automata algorithm

  The types of automata algorithm defines if the
  automaton the type of algorithm to be used. Available types are
  ALPHABET_BASED, TRANSITION_BASED, HEURISTIC_BASED.
*/

enum Automaton_Algorithm_Type_TAG{
  ALPHABET_BASED=0,
  TRANSITIONS_BASED=1,
  HEURISTIC_BASED=2
};
typedef enum Automaton_Algorithm_Type_TAG Automaton_Algorithm_Type;

/*!
  \brief Type of labels implementation

  The types of label implementation that is used in an automaton.
*/

enum Automaton_Label_Type_TAG{
  BASE_LABEL=-1, /* Value used to detect the base class of the label */
  BDD_LABEL=0,
  HYBRID_LABEL = 1,
  SYNTH_LABEL = 2,
};
typedef enum Automaton_Label_Type_TAG Automaton_Label_Type;

/*!
  \brief Type of reduction algorithm

  The types of reduction algorithm used when reduce an
  automaton.
*/

enum Automaton_ReductionAlgorithm_Type_TAG{
  AUT_RED_ALG_BISIMULATION=0, /* Bisimulation based reduction algorithm */
  AUT_RED_ALG_BRZOZOWSKI=1 /* Use brzozowsky minimization. */
};
typedef enum Automaton_ReductionAlgorithm_Type_TAG Automaton_ReductionAlgorithm_Type;

/**AutomaticStart*************************************************************/

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \brief Initializes the addon

  
*/
void Automata_init(NuSMVEnv_ptr env);

/*!
  \brief Reinitializes the addon

  
*/
void Automata_reset(NuSMVEnv_ptr env);

/*!
  \brief Deinitializes the addon

  
*/
void Automata_quit(NuSMVEnv_ptr env);

/**AutomaticEnd***************************************************************/

#endif /* __NUXMV_CORE_AUTOMATA_AUTOMATA_H__ */
