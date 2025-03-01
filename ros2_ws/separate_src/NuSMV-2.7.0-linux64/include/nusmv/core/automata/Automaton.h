/* ---------------------------------------------------------------------------

   This file is part of the ``automata'' package.
   %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Sergio Mover
  \brief Public interface of class 'Automaton'

  \todo: Missing description

*/



#ifndef __NUXMV_CORE_AUTOMATA_AUTOMATON_H__
#define __NUXMV_CORE_AUTOMATA_AUTOMATON_H__

#include "nusmv/core/automata/AbstractAutomaton.h"
#include "nusmv/core/automata/automata.h"
#include "nusmv/core/automata/AutomataManager.h"
#include "nusmv/core/automata/AutomataLoc.h"

#include "nusmv/core/parser/psl/pslNode.h"
#include "nusmv/core/utils/object.h"
#include "nusmv/core/utils/utils.h"
#include "nusmv/core/utils/Slist.h"
#include "nusmv/core/automata/utils/AutomataPredecessorsList.h"


/*!
  \brief Controls the way the xmi is printed out

  AUTOMATA_XMI_FORMAT_EA specificies an output that works with
  Enterprise Architect
*/

typedef enum AutomataXmiFormat_TAG {
  AUTOMATA_XMI_FORMAT_STANDARD,
  AUTOMATA_XMI_FORMAT_EA
} AutomataXmiFormat;

/*!
  \struct Automaton
  \brief Definition of the public accessor for class Automaton

  
*/
typedef struct Automaton_TAG*  Automaton_ptr;

/*!
  \brief To cast and check instances of class Automaton

  These macros must be used respectively to cast and to check
   instances of class Automaton
*/
#define AUTOMATON(self)                         \
  ((Automaton_ptr) self)

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define AUTOMATON_CHECK_INSTANCE(self)                  \
  (nusmv_assert(AUTOMATON(self) != AUTOMATON(NULL)))


/**AutomaticStart*************************************************************/

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/* Constructors **************************************************************/

/*!
  \methodof Automaton
  \brief The Automaton class constructor

  The Automaton class constructor

  \sa Automaton_destroy, Automaton_create_from_expr,
   Automaton_create_empty, Automaton_create_empty_word,
   Automaton_create_from_sere
*/
Automaton_ptr Automaton_create(void);

/*!
  \methodof Automaton
  \brief Creates an automaton from an expression

  Creates the automaton that recognize the word
   encoded by expr. The resulting automaton consists of an initial and a
   final location with a transition from initial to final location with expr
   as label.

  \sa Automaton_create, Automaton_create_empty,
   Automaton_create_empty_word
*/
Automaton_ptr
Automaton_create_from_expr(AutomataManager_ptr manager,
                           Expr_ptr expr);

/*!
  \methodof Automaton
  \brief Creates an automaton that recognize the empty language

  Creates the automaton that recognize the empty
   language. The resulting automaton is formed only by an initial location

  \sa Automaton_create, Automaton_create_from_expr,
   Automaton_create_empty_word
*/
Automaton_ptr
Automaton_create_empty(AutomataManager_ptr manager);

/*!
  \methodof Automaton
  \brief Creates an automaton that recognize the empty word

  Creates the automaton that recognize the empty
   word. The resulting automaton is formed only by a location that is
   either initial and final.

  \sa Automaton_create, Automaton_create_from_expr,
   Automaton_create_empty
*/
Automaton_ptr
Automaton_create_empty_word(AutomataManager_ptr manager);

/*!
  \methodof Automaton
  \brief Given a SERE expression the corresponding
   automaton is returned

  From a regular expression SERE is built the
   correspondent automaton. SERE is a PSL regular expression

  \sa Automaton_create, Automaton_create_from_expr,
   Automaton_create_empty, Automaton_create_empty_word
*/
Automaton_ptr Automaton_create_from_sere(AutomataManager_ptr manager,
                                                PslNode_ptr sere);



/* Destructors ****************************************************************/

/*!
  \methodof Automaton
  \brief The Automaton class destructor

  The Automaton class destructor

  \sa Automaton_create
*/
void Automaton_destroy(Automaton_ptr self);



/* Getters ********************************************************************/
AutomataLoc_ptr
Automaton_get_unique_init_loc(Automaton_ptr const self);

/* Setters ********************************************************************/



/* Checkers *******************************************************************/

/*!
  \brief Checks if L(A1) is contained in L(A2)

  Returns true if L(A1) is contained in
   L(A2). This operation is performe using complement and intersection,
   checking if the intersection of L(A1) with the complement of L(A2)
   is empty

  \sa Automaton_intersection, Automaton_complement
*/
boolean Automaton_containment(AutomataManager_ptr manager,
                                     Automaton_ptr A1,
                                     Automaton_ptr A2);

/*!
  \brief Checks if two automata are equals

  Returns true if A1 and A2 are equals. Two
   automata are equals if they recognize the same language
*/
boolean Automaton_equals(AutomataManager_ptr manager,
                                Automaton_ptr A1,
                                Automaton_ptr A2);

/*!
  \brief Checks if the language recognized by self is the
   empty language

  Returns true if the language recognized by self is
   empty. This happens if no final locations are reached traversing the automaton
*/
boolean Automaton_emptyness_check(AutomataManager_ptr manager,
                                         Automaton_ptr A);



/* Conversion to other formats or types ***************************************/

/*!
  \brief Given an automaton a regular expression in the
   PSL syntax is returned

  Construct a regular expression from an
   automaton
*/
PslNode_ptr Automaton_automa2sere(AutomataManager_ptr manager,
                                         Automaton_ptr self);

/*!
  \brief Translate an automaton in smv

  
*/
int Automaton_automaton2smv(AutomataManager_ptr manager,
                                   Automaton_ptr A,
                                   FILE* out_file);



/* Others *********************************************************************/

/*!
  \brief Adds a transition from src_location to dst_location to
   self.

  Adds to automaton self the transition from location_1
   to location_2 with the given label.

   The location with the given id must be already be created in the automaton.
*/
void Automaton_new_transition(AutomataManager_ptr manager,
                                     Automaton_ptr self,
                                     int location_1_id,
                                     int location_2_id,
                                     Expr_ptr label_expr);

/*!
  \brief Returns the automaton that recognize the union
   language of A1 and A2

  Creates the automaton that recognize the union
   language of A1 and A2

  \sa Automaton_intersection
*/
Automaton_ptr
Automaton_union(AutomataManager_ptr manager,
                Automaton_ptr A1,
                Automaton_ptr A2);

/*!
  \brief Returns the automaton that recognize the intersection
   language of A1 and A2

  Creates the automaton that recognize the intersection
   language of A1 and A2

  \sa Automaton_and, Automaton_union
*/
Automaton_ptr
Automaton_intersection(AutomataManager_ptr manager,
                       Automaton_ptr A1,
                       Automaton_ptr A2);

/*!
  \brief Creates the automaton that recognize the
   conjunction of languages of A1 and A2

  Creates the automaton that recognize the
   conjunction of languages of A1 and A2

  \sa Automaton_intersection, Automaton_union
*/
Automaton_ptr Automaton_and(AutomataManager_ptr manager,
                                   Automaton_ptr A1,
                                   Automaton_ptr A2);

/*!
  \brief Creates the automaton that recognize the
   concatenation of languages of A1 and A2

  Creates the automaton that recognize the
   concatenation of languages of A1 and A2

  \sa Automaton_concatenation_n_times, Automaton_fusion
*/
Automaton_ptr Automaton_concatenation(AutomataManager_ptr manager,
                                             Automaton_ptr A1,
                                             Automaton_ptr A2);

/*!
  \brief Creates the automaton that recognize the
   concatenation of language of self n times

  Creates the automaton that recognize the
   concatenation of language of self n times

  \sa Automaton_concatenation, Automaton_fusion
*/
Automaton_ptr
Automaton_concatenation_n_times(AutomataManager_ptr manager,
                                Automaton_ptr A1,
                                int n);

/*!
  \brief Creates the automaton that recognize the Kleene
   star language of language self

  Creates the automaton that recognize the Kleene
   star language of language self. The Kleene star language is the
   language obtained repeating zero or more times a word in L(self)

  \sa Automaton_kleene_plus
*/
Automaton_ptr Automaton_kleene_star(AutomataManager_ptr manager,
                                           Automaton_ptr A);

/*!
  \brief Creates the automaton that recognize the Kleene
   plus language of language self

  Creates the automaton that recognize the Kleene
   plus language of language self. The Kleene plus language is the
   language obtained repeating one or more times a word in L(self)

  \sa Automaton_kleene_star
*/
Automaton_ptr Automaton_kleene_plus(AutomataManager_ptr manager,
                                           Automaton_ptr A);

/*!
  \brief Creates the automaton that recognize the
   language obtained by the fusion of languages recognized by A1 and A1

  Creates a new automaton that recognize the
   language L. self word w is in L if exists a w1 such that w1.l is in
   L(A1) and exists a w2 such that l.w2 is in L(A2), where l is a
   symbol of the alphabet. This operator is needed when dealing with
   PSL fusion operator (:)

  \sa Automaton_concatenation,
   Automaton_concatenation_n_times
*/
Automaton_ptr Automaton_fusion(AutomataManager_ptr manager,
                                      Automaton_ptr A1,
                                      Automaton_ptr A2);

/*!
  \brief Creates the automaton that recognize the
   reverse language of self

  Creates a new automaton that recognize the
   reverse language of self. If a word w1=l1,l2,...ln is recognized by
   self, then reverse(self) recognize the word w2=ln,ln-1,...,l1
*/
Automaton_ptr Automaton_reverse(AutomataManager_ptr manager,
                                       Automaton_ptr A);

/*!
  \brief Creates the automaton that recognize the
   complement language of A1

  Creates a new automaton that recognize the
   complement language of A1

  \sa Automaton_determinization
*/
Automaton_ptr Automaton_complement(AutomataManager_ptr manager,
                                          Automaton_ptr A);

/*!
  \brief Creates the automaton that recognize the
   difference language L of A1 and A2, so L=L(A1)\L(A2)

  Creates a new automaton that recognize the
   language L=L(A1)\L(A2). Difference is obtained using intersection
   and complement operation, performing intersection of L(A1) with the
   complement of L(A2)

  \sa Automaton_intersection, Automaton_complement
*/
Automaton_ptr Automaton_difference(AutomataManager_ptr manager,
                                          Automaton_ptr A1,
                                          Automaton_ptr A2);

/*!
  \brief Creates the DFA of automaton self

  Returns a new automaton that is the DFA of self
*/
Automaton_ptr Automaton_determinize(AutomataManager_ptr manager,
                                           Automaton_ptr A);

/*!
  \brief Creates the minimum DFA of self

  Returns a new automaton that is the minimum DFA of self
*/
Automaton_ptr Automaton_minimize(AutomataManager_ptr manager,
                                        Automaton_ptr A1);

/*!
  \brief Reduces locations of the input automaton A1.

  Returns a new automaton obtained reducing the
   number of locations of input automaton A1.

   The algorithm used to reduce the automaton is set in automata
   manager class.
*/
Automaton_ptr Automaton_nfa_reduction(AutomataManager_ptr manager,
                                             Automaton_ptr A1);

/*!
  \brief Creates a new automaton that is obtained pruning
   automaton self

  The new automaton is obtained pruning locations in
   automaton self that are not reachable from the intial location
*/
Automaton_ptr Automaton_prune(AutomataManager_ptr manager,
                                     Automaton_ptr self);

/*!
  \brief Creates a new automaton that is obtained from
   the automaton self removing all paths that cannot reach an accepting location.

  Creates a new automaton that is obtained from
   the automaton self removing all paths that cannot reach an accepting location.
*/
Automaton_ptr
Automaton_prune_non_accepting_paths(AutomataManager_ptr manager,
                                    Automaton_ptr self);

/*!
  \methodof Automaton
  \brief Builds the AutomataPredecessorsList

  Builds the AutomataPredecessorsList

  \sa utils/AutomataPredecessorsList.c
*/
AutomataPredecessorsList_ptr
Automaton_build_predecessors_list(Automaton_ptr self);

/*!
  \methodof Automaton
  \brief Populate an hash that associates each transition with
   its source location

  Populate an hash that associates each transition with
   its source location
*/
void
Automaton_compute_all_trans_source_location(Automaton_ptr self,
                                            hash_ptr trans2source);


/* Printing *******************************************************************/

/*!
  \methodof Automaton
  \brief Prints automaton on out_file in xmi format.

  Prints automaton on out_file in xmi format.
*/
void Automaton_print_xmi(const Automaton_ptr self,
                                const NuSMVEnv_ptr env,
                                FILE* out_file,
                                AutomataXmiFormat format);


/**AutomaticEnd***************************************************************/



#endif /* __NUXMV_CORE_AUTOMATA_AUTOMATON_H__ */
