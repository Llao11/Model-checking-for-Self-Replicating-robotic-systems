/* ---------------------------------------------------------------------------

  This file is part of the ``automata'' package.
  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Michele Dorigatti
  \brief Public interface of class 'AutomataNamedLoc'

  \todo: Missing description

*/

#ifndef __NUXMV_CORE_AUTOMATA_AUTOMATA_NAMED_LOC_H__
#define __NUXMV_CORE_AUTOMATA_AUTOMATA_NAMED_LOC_H__


#include "nusmv/core/automata/AutomataLoc.h"
#include "nusmv/core/automata/Automaton.h"

#include "nusmv/core/utils/utils.h"

/*!
  \struct AutomataNamedLoc
  \brief Definition of the public accessor for class AutomataNamedLoc

  
*/
typedef struct AutomataNamedLoc_TAG*  AutomataNamedLoc_ptr;

/*!
  \brief To cast and check instances of class AutomataNamedLoc

  These macros must be used respectively to cast and to check
  instances of class AutomataNamedLoc
*/
#define AUTOMATA_NAMED_LOC(self) \
         ((AutomataNamedLoc_ptr) self)

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define AUTOMATA_NAMED_LOC_CHECK_INSTANCE(self) \
         (nusmv_assert(AUTOMATA_NAMED_LOC(self) != \
                       AUTOMATA_NAMED_LOC(NULL)))



/**AutomaticStart*************************************************************/

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/* Constructors and Destructors ***********************************************/

/*!
  \methodof AutomataNamedLoc
  \brief The AutomataNamedLoc class constructor from manager

  The AutomataNamedLoc class constructor from
  manager. It constructs location and set parameters from the manager
  object.

  The parameter that is set is keep_support_set, that enable or
  disable the hashing of support set in a location.
  Another parameter is the type of labels that will be used.

  \sa AutomataNamedLoc_destroy
*/
AutomataNamedLoc_ptr
AutomataNamedLoc_create_from_manager(AutomataManager_ptr manager);

/*!
  \methodof AutomataNamedLoc
  \brief The AutomataNamedLoc class constructor

  The AutomataNamedLoc class constructor

  \sa AutomataNamedLoc_destroy
*/
AutomataNamedLoc_ptr
AutomataNamedLoc_create(Automaton_Label_Type label_type,
                          boolean keep_support_location);

/*!
  \methodof AutomataNamedLoc
  \brief Create a named location and add it to automaton

  Create a named location and add it to automaton
*/
AutomataNamedLoc_ptr
AutomataNamedLoc_create_and_add_to_automaton(const AutomataManager_ptr manager,
                                               const Automaton_ptr automaton,
                                               const boolean is_final,
                                               const char* location_str);

/*!
  \methodof AutomataNamedLoc
  \brief The AutomataNamedLoc class destructor

  The AutomataNamedLoc class destructor

  \sa AutomataNamedLoc_create
*/
void AutomataNamedLoc_destroy(AutomataNamedLoc_ptr self);



/* Getters and Setters ********************************************************/

/*!
  \methodof AutomataNamedLoc
  \brief Sets the name of the location

  Sets the name of the location
*/
void AutomataNamedLoc_set_name(AutomataNamedLoc_ptr self,
                                        char* name);

/*!
  \methodof AutomataNamedLoc
  \brief Gets the name of the location

  Gets the name of the location
*/
char* AutomataNamedLoc_get_name(AutomataNamedLoc_ptr self);


/* Checkers *******************************************************************/

/*!
  \brief required

  optional

  \se required

  \sa optional
*/
boolean
AutomataNamedLoc_have_same_name(AutomataNamedLoc_ptr first,
                                  AutomataNamedLoc_ptr second);



/**AutomaticEnd***************************************************************/



#endif /* __NUXMV_CORE_AUTOMATA_AUTOMATA_NAMED_LOC_H__ */
