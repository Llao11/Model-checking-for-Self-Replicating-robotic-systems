/* ---------------------------------------------------------------------------

  This file is part of the ``automata'' package.
  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Sergio Mover
  \brief Private and protected interface of class 'Automaton'

  This file can be included only by derived and friend classes

*/



#ifndef __NUXMV_CORE_AUTOMATA_AUTOMATON_PRIVATE_H__
#define __NUXMV_CORE_AUTOMATA_AUTOMATON_PRIVATE_H__


#include "nusmv/core/automata/Automaton.h"
#include "nusmv/core/automata/AbstractAutomaton.h"
#include "nusmv/core/automata/AbstractAutomaton_private.h"
#include "nusmv/core/utils/utils.h"

#include "nusmv/core/automata/AutomataTransition.h"
#include "nusmv/core/automata/labels/AutomataLabel.h"


/*!
  \brief Automaton class definition derived from
               class AbstractAutomaton

  Defines the structure of an automaton.
  The automaton contains:

    - sink_location: the location to be used as sink location for the automaton. This
  location is used to create a complete automaton, needed for complementation.

    - final_locations: a list that contains all the final locations of the
  automaton. This list is not ordered and is used to iterate over all
  the final locations. The function in the automaton class mantains this
  list updated.

  \sa Base class AbstractAutomaton
*/

typedef struct Automaton_TAG
{
  /* this MUST stay on the top */
  INHERITS_FROM(AbstractAutomaton);

  /* -------------------------------------------------- */
  /*                  Private members                   */
  /* -------------------------------------------------- */
  Slist_ptr final_locations;
  boolean is_complete;
  boolean keep_support_set_in_location;

  /* -------------------------------------------------- */
  /*                  Virtual methods                   */
  /* -------------------------------------------------- */
  void (*new_transition) (AutomataManager_ptr manager,
                          Automaton_ptr A,
                          int location_1_id,
                          int location_2_id,
                          Expr_ptr label_expr);

  Automaton_ptr (*automaton_union)(AutomataManager_ptr manager,
                                   Automaton_ptr A1,
                                   Automaton_ptr A2);

  Automaton_ptr (*intersection)(AutomataManager_ptr manager,
                                Automaton_ptr A1,
                                Automaton_ptr A2);

  Automaton_ptr (*and)(AutomataManager_ptr manager,
                       Automaton_ptr A1,
                       Automaton_ptr A2);

  Automaton_ptr (*concatenation)(AutomataManager_ptr manager,
                                 Automaton_ptr A1,
                                 Automaton_ptr A2);

  Automaton_ptr (*concatenation_n_times)(AutomataManager_ptr manager,
                                         Automaton_ptr A1,
                                         int n);

  Automaton_ptr (*kleene_star)(AutomataManager_ptr manager, Automaton_ptr A);

  Automaton_ptr (*kleene_plus)(AutomataManager_ptr manager, Automaton_ptr A);

  Automaton_ptr (*fusion)(AutomataManager_ptr manager,
                          Automaton_ptr A1,
                          Automaton_ptr A2);

  Automaton_ptr (*reverse)(AutomataManager_ptr manager, Automaton_ptr A);

  Automaton_ptr (*complement)(AutomataManager_ptr manager, Automaton_ptr A);

  Automaton_ptr (*difference)(AutomataManager_ptr manager,
                              Automaton_ptr A1,
                              Automaton_ptr A2);

  boolean (*containment)(AutomataManager_ptr manager,
                         Automaton_ptr A1,
                         Automaton_ptr A2);

  Automaton_ptr (*determinize)(AutomataManager_ptr manager, Automaton_ptr A);

  Automaton_ptr (*minimize)(AutomataManager_ptr manager, Automaton_ptr A1);

  Automaton_ptr (*nfa_reduction)(AutomataManager_ptr manager, Automaton_ptr A1);

  boolean (*equals)(AutomataManager_ptr manager,
                    Automaton_ptr A1,
                    Automaton_ptr A2);

  boolean (*emptyness_check)(AutomataManager_ptr manager, Automaton_ptr A);

  Automaton_ptr (*prune)(AutomataManager_ptr manager, Automaton_ptr self);

  Automaton_ptr (*prune_non_accepting)(AutomataManager_ptr manager,
                                       Automaton_ptr self);

  PslNode_ptr (*automa2sere)(AutomataManager_ptr manager, Automaton_ptr self);

  int (*automaton2smv)(AutomataManager_ptr manager,
                       Automaton_ptr A,
                       FILE* out_file);

} Automaton;



/* ---------------------------------------------------------------------- */
/* Private methods to be used by derivated and friend classes only         */
/* ---------------------------------------------------------------------- */

/*!
  \methodof Automaton
  \brief The Automaton class private initializer

  The Automaton class private initializer

  \sa Automaton_create
*/
void automaton_init(Automaton_ptr self);

/*!
  \methodof Automaton
  \brief The Automaton class private deinitializer

  The Automaton class private deinitializer

  \sa Automaton_destroy
*/
void automaton_deinit(Automaton_ptr self);

/* Getters and Setters ********************************************************/

/*!
  \methodof Automaton
  \brief Return the initial location of the automaton.

  
*/
Set_t automaton_get_initial_locations(AbstractAutomaton_ptr self);

/*!
  \brief Set the initial location

  The initial locations must be empty.
                       Automaton class handle EXACTLY ONE initial location. If
                       you need more than one, either add one fake initial
                       state or use another implementation of
                       AbstractAutomaton, for example HybridAutomaton
*/
void
automaton_add_initial_location(AbstractAutomaton_ptr const self,
                               AutomataLoc_ptr const location);

/*!
  \methodof Automaton
  \brief Adds location to the automaton

  Adds location to the list of locations of automaton. This
   function is useful to keep count of the number of locations of the automaton.
*/
void automaton_add_loc(AbstractAutomaton_ptr self,
                              AutomataLoc_ptr location);


/* Miscellaneous **************************************************************/

/*!
  \brief Adds a new transition to the automaton

  
*/
void automaton_new_transition(AutomataManager_ptr manager,
                                     Automaton_ptr A,
                                     int location_1_id,
                                     int location_2_id,
                                     Expr_ptr label_expr);

/*!
  \brief Prints automaton on out_file.

  
*/
void automaton_print(AbstractAutomaton_ptr A,
                            NuSMVEnv_ptr env,
                            FILE* out_file);

/*!
  \brief Prints automaton on out_file in dot format.

  
*/
void automaton_print_dot(AbstractAutomaton_ptr A,
                                NuSMVEnv_ptr env,
                                FILE* out_file);

/*!
  \brief Returns the automaton that recognize the union
   language of A1 and A2

  Creates a new automaton that recognize the union
   of languages of A1 and A2. The union is performed creating a new
   initial location for automaton that copies the output transitions from
   the initial locations of A1 and A2.
*/
Automaton_ptr automaton_union(AutomataManager_ptr manager,
                                     Automaton_ptr A1,
                                     Automaton_ptr A2);

/*!
  \brief Returns the automaton that recognize the intersection
   language of A1 and A2

  
*/
Automaton_ptr automaton_intersection(AutomataManager_ptr manager,
                                            Automaton_ptr A1,
                                            Automaton_ptr A2);

/*!
  \brief Returns the automaton that recognize the conjunction
   language of A1 and A2

  
*/
Automaton_ptr automaton_and(AutomataManager_ptr manager,
                                   Automaton_ptr A1,
                                   Automaton_ptr A2);

/*!
  \brief Creates the automaton that recognize the
   concatenation of languages of A1 and A2

  
*/
Automaton_ptr automaton_concatenation(AutomataManager_ptr manager,
                                             Automaton_ptr A1,
                                             Automaton_ptr A2);

/*!
  \brief Creates the automaton that recognize the
   concatenation of language of self n times

  Creates an automaton that recognizes the
   concatenation of language of self n times.
   Now this operation is done trivially, calling n times the
   concatenation operation.
*/
Automaton_ptr
automaton_concatenation_n_times(AutomataManager_ptr manager,
                                Automaton_ptr A1,
                                int n);

/*!
  \brief Creates the automaton that recognize the Kleene
   star language of language self

  Kleene_star operator is implemented building the
   automaton for kleene_plus operator and making the initial location
   final, so the empty language is recognized.
*/
Automaton_ptr automaton_kleene_star(AutomataManager_ptr manager,
                                           Automaton_ptr A);

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
Automaton_ptr automaton_kleene_plus(AutomataManager_ptr manager,
                                           Automaton_ptr A);

/*!
  \brief Creates the automaton that recognize the
   language obtained by the fusion of languages recognized by A1 and A1

  
*/
Automaton_ptr automaton_fusion(AutomataManager_ptr manager,
                                      Automaton_ptr A1,
                                      Automaton_ptr A2);

/*!
  \brief Creates the automaton that recognize the
   reverse language of self

  Creates the automaton that recognize the reverse
   language of the language of self.
   Step performed by reverse:
   1. self new automaton is created with an initial and a final location. The
   initial location of self is mapped to the final location of the result
   automaton.
   2. self DFS is performed on self. Traversing self its locations and transitions
   are copied to the result automaton.
   - The transition are copied swapping the source and the end location
   - If the end location of the transition is final the new location in the
   result automaton is not final and a new transition is created from
   the initial location of the result automaton to the source location of
   transition.
   3. The result automaton needs to be pruned to delete non-reachable locations.
*/
Automaton_ptr automaton_reverse(AutomataManager_ptr manager,
                                       Automaton_ptr A);

/*!
  \brief Creates the automaton that recognize the
   complement language of A1

  Creates a new automaton that recognize the
   complement language of self.
   The complementation first determinize and makes complete the
   automaton, then swap final with non-final locations.
*/
Automaton_ptr automaton_complement(AutomataManager_ptr manager,
                                          Automaton_ptr A);

/*!
  \brief Creates the automaton that recognize the
   difference language L of A1 and A2, so L=L(A1)\L(A2)

  Creates a new automaton that recognize the
   language difference of A1 and A2.
   L(A1)\L(A2) is performed computing "L(A1) intersect neg(L(B))".
*/
Automaton_ptr automaton_difference(AutomataManager_ptr manager,
                                          Automaton_ptr A1,
                                          Automaton_ptr A2);

/*!
  \brief Checks if L(A1) is contained in L(A2)

  Language containment is performed checking if
   the difference of A1 and A2 is empty
*/
boolean automaton_containment(AutomataManager_ptr manager,
                                     Automaton_ptr A1,
                                     Automaton_ptr A2);

/*!
  \brief Creates the DFA of automaton self

  
*/
Automaton_ptr automaton_determinize(AutomataManager_ptr manager,
                                           Automaton_ptr A);

/*!
  \brief Creates the minimum DFA of self

  
*/
Automaton_ptr automaton_minimize(AutomataManager_ptr manager,
                                        Automaton_ptr A1);

/*!
  \brief Creates a new automaton from A1 reducing its
   locations.

  Creates a new automaton from A1 applying a
   reduction technique, thus possibly getting a smaller automaton.

   The algorithm used for reduction is specified in manager class.
*/
Automaton_ptr automaton_nfa_reduction(AutomataManager_ptr manager,
                                             Automaton_ptr A1);

/*!
  \brief Checks if two automata are equals

  
*/
boolean automaton_equals(AutomataManager_ptr manager,
                                Automaton_ptr A1,
                                Automaton_ptr A2);

/*!
  \brief Checks if the language recognized by self is the
   empty language

  Performs a DFS on self starting from its initial
   location. The recognized language is empty iff no final locations are
   reached.
*/
boolean automaton_emptyness_check(AutomataManager_ptr manager,
                                         Automaton_ptr A);

/*!
  \brief Creates a new automaton that is obtained pruning
   automaton self

  Creates a new automaton that is the pruned
   version of self.
   The pruning is performed copying self with a DFS. Non reachable locations
   are not copied, so the resulting automaton is pruned.

  \sa automaton_copy_reachable_from_loc
*/
Automaton_ptr automaton_prune(AutomataManager_ptr manager,
                                     Automaton_ptr self);

/*!
  \brief Prune the non accepting paths of automaton self.

  Builds a new automaton where paths that do not
   lead to an accepting location are removed.
*/
Automaton_ptr
automaton_prune_non_accepting_paths(AutomataManager_ptr manager,
                                    Automaton_ptr self);

/*!
  \brief Given an automaton a regular expression in the
   PSL syntax is returned

  
*/
PslNode_ptr automaton_automa2sere(AutomataManager_ptr manager,
                                         Automaton_ptr self);

/*!
  \brief Translate an automaton in smv

  
*/
int automaton_automaton2smv(AutomataManager_ptr manager,
                                   Automaton_ptr A,
                                   FILE* out_file);

/*!
  \methodof Automaton
  \brief Initialize the type of automaton using the
   manager information

  
*/
void automaton_init_type_complete(Automaton_ptr self,
                                         AutomataManager_ptr manager);

#endif /* __NUXMV_CORE_AUTOMATA_AUTOMATON_PRIVATE_H__ */
