/* ---------------------------------------------------------------------------

  This file is part of the ``automata'' package.
  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author 
  \brief Public interface of class 'AutomataModeLoc'

  \todo: Missing description

*/

#ifndef __NUXMV_CORE_AUTOMATA_AUTOMATA_MODE_LOC_H__
#define __NUXMV_CORE_AUTOMATA_AUTOMATA_MODE_LOC_H__

#include "nusmv/core/automata/AutomataLoc.h"
#include "nusmv/core/automata/Automaton.h"

#include "nusmv/core/utils/utils.h"

/*!
  \struct AutomataModeLoc
  \brief Definition of the public accessor for class AutomataModeLoc


*/
typedef struct AutomataModeLoc_TAG*  AutomataModeLoc_ptr;

/*!
  \brief To cast and check instances of class AutomataModeLoc

  These macros must be used respectively to cast and to check
  instances of class AutomataModeLoc
*/
#define AUTOMATA_MODE_LOC(self) \
         ((AutomataModeLoc_ptr) self)

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define AUTOMATA_MODE_LOC_CHECK_INSTANCE(self) \
         (nusmv_assert(AUTOMATA_MODE_LOC(self) != \
                       AUTOMATA_MODE_LOC(NULL)))



/**AutomaticStart*************************************************************/

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/* Constructors and Destructors ***********************************************/

/*!
  \methodof AutomataModeLoc
  \brief The AutomataModeLoc class constructor from manager

  The AutomataModeLoc class constructor from
  manager. It constructs location and set parameters from the manager
  object.

  The parameter that is set is keep_support_set, that enable or
  disable the hashing of support set in a location.
  Another parameter is the type of labels that will be used.

  \sa AutomataModeLoc_destroy
*/
AutomataModeLoc_ptr
AutomataModeLoc_create_from_manager(AutomataManager_ptr manager);

/*!
  \methodof AutomataModeLoc
  \brief The AutomataModeLoc class constructor

  The AutomataModeLoc class constructor

  \sa AutomataModeLoc_destroy
*/
AutomataModeLoc_ptr
AutomataModeLoc_create(Automaton_Label_Type label_type,
                          boolean keep_support_location);

/*!
  \methodof AutomataModeLoc
  \brief Create a mode location and add it to automaton

  Create a mode location and add it to automaton
*/
AutomataModeLoc_ptr
AutomataModeLoc_create_and_add_to_automaton(const AutomataManager_ptr manager,
                                               const Automaton_ptr automaton,
                                               const boolean is_final,
                                               const Expr_ptr location_expr);

/*!
  \methodof AutomataModeLoc
  \brief The AutomataModeLoc class destructor

  The AutomataModeLoc class destructor

  \sa AutomataModeLoc_create
*/
void AutomataModeLoc_destroy(AutomataModeLoc_ptr self);



/* Getters and Setters ********************************************************/

/*!
  \methodof AutomataModeLoc
  \brief Sets the expression of the location

  Sets the expression of the location
*/
void AutomataModeLoc_set_expr(AutomataModeLoc_ptr self,
                                        Expr_ptr expr);

/*!
  \methodof AutomataModeLoc
  \brief Gets the expression of the location

  Gets the expression of the location
*/
Expr_ptr AutomataModeLoc_get_expr(AutomataModeLoc_ptr self);


/* Checkers *******************************************************************/

/*!
  \brief required

  optional

  \se required

  \sa optional
*/
boolean
AutomataModeLoc_have_same_expression(AutomataModeLoc_ptr first,
                                     AutomataModeLoc_ptr second);



/**AutomaticEnd***************************************************************/



#endif /* __NUXMV_CORE_AUTOMATA_AUTOMATA_MODE_LOC_H__ */
