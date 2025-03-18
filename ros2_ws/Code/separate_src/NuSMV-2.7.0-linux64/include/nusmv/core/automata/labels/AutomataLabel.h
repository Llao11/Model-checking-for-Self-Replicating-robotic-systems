/* ---------------------------------------------------------------------------


  This file is part of the ``labels'' package.
  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Sergio Mover
  \brief Public interface of class 'AutomataLabel'

  \todo: Missing description

*/



#ifndef __NUXMV_CORE_AUTOMATA_LABELS_AUTOMATA_LABEL_H__
#define __NUXMV_CORE_AUTOMATA_LABELS_AUTOMATA_LABEL_H__

#include "nusmv/core/automata/automata.h"

#include "nusmv/core/wff/ExprMgr.h"
#include "nusmv/core/set/set.h"
#include "nusmv/core/utils/object.h"
#include "nusmv/core/utils/utils.h"

/*!
  \struct AutomataLabel
  \brief Definition of the public accessor for class AutomataLabel

  
*/
typedef struct AutomataLabel_TAG*  AutomataLabel_ptr;

/*!
  \brief To cast and check instances of class AutomataLabel

  These macros must be used respectively to cast and to check
  instances of class AutomataLabel
*/
#define AUTOMATA_LABEL(self) \
         ((AutomataLabel_ptr) self)

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define AUTOMATA_LABEL_CHECK_INSTANCE(self) \
         (nusmv_assert(AUTOMATA_LABEL(self) != AUTOMATA_LABEL(NULL)))

/*!
  \brief Assertion used to check if a label has the given type

  
*/
#define AUTOMATA_LABEL_CHECK_TYPE(self, type) \
  (nusmv_assert(AutomataLabel_get_label_type(self) == type))   

/**AutomaticStart*************************************************************/

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \methodof AutomataLabel
  \brief The AutomataLabel class constructor

  The AutomataLabel class constructor

  \sa AutomataLabel_destroy
*/
AutomataLabel_ptr AutomataLabel_create(void);

/*!
  \methodof AutomataLabel
  \brief The AutomataLabel class destructor

  The AutomataLabel class destructor

  \sa AutomataLabel_create
*/
void AutomataLabel_destroy(AutomataLabel_ptr self);

/*!
  \methodof AutomataLabel
  \brief Alternative AutomataLabel class constructor

  Construct an instance of AutomataLabel setting
  the expression of the label.

  \sa AutomataLabel_destroy
*/
AutomataLabel_ptr AutomataLabel_create_from_expr(Expr_ptr expr);

/*!
  \methodof AutomataLabel
  \brief Returns the expression contained in the label

  
*/
Expr_ptr
AutomataLabel_get_expr(AutomataLabel_ptr self);

/*!
  \methodof AutomataLabel
  \brief Sets a new expression for the label

  
*/
void AutomataLabel_set_expr(AutomataLabel_ptr self,
                                   Expr_ptr new_expr);

/*!
  \methodof AutomataLabel
  \brief Getter for the label type

  
*/
Automaton_Label_Type AutomataLabel_get_label_type(AutomataLabel_ptr self);

/*!
  \methodof AutomataLabel
  \brief Check if a label is satistiable

  Returns true if the label is satisfiable.

  \sa AutomataLabel_is_model, AutomataLabel_is_equivalent
*/
boolean AutomataLabel_is_sat(AutomataLabel_ptr self);

/*!
  \methodof AutomataLabel
  \brief Checks if expression is a model for the label

  The function checks if expression is a model for
  the label and returns true in this case. Otherwise function returns false. 

  \sa AutomataLabel_is_sat, AutomataLabel_is_equivalent
*/
boolean AutomataLabel_is_model(AutomataLabel_ptr self, 
                                      Expr_ptr expression);

/*!
  \methodof AutomataLabel
  \brief Checks if label is true

  

  \sa AutomataLabel_is_sat, AutomataLabel_is_equivalent
*/
boolean AutomataLabel_is_true(AutomataLabel_ptr self);

/*!
  \methodof AutomataLabel
  \brief Checks if two labels are equivalent.

  The function returns true if the label is
  equivalent to label2, otherwise returns false.

  \sa AutomataLabel_is_model, AutomataLabel_is_sat
*/
boolean AutomataLabel_is_equivalent(AutomataLabel_ptr self,
                                           AutomataLabel_ptr label2);

/*!
  \methodof AutomataLabel
  \brief Checks if self label is contained in label2.

  The function returns true if the label is
  contained in label2 (i.e. self -> label2), otherwise returns false.

  \sa AutomataLabel_is_model, AutomataLabel_is_sat
*/
boolean AutomataLabel_is_contained(AutomataLabel_ptr self,
                                          AutomataLabel_ptr label2);

/*!
  \methodof AutomataLabel
  \brief Intersect two labels

  Returns a new label that is the intersection of
  labels self and label2. The intersection is the conjunction of the
  expressions of the labels.

  \sa AutomataLabel_union, AutomataLabel_complement
*/
AutomataLabel_ptr AutomataLabel_intersection(AutomataLabel_ptr self,
                                                    AutomataLabel_ptr label2);

/*!
  \methodof AutomataLabel
  \brief Perform the union of two labels

  Returns a new label that is the union of
  labels self and label2. The union is the disjunction of the
  expressions of the labels.

  \sa AutomataLabel_intersect, AutomataLabel_complement
*/
AutomataLabel_ptr AutomataLabel_union(AutomataLabel_ptr self,
                                             AutomataLabel_ptr label2);

/*!
  \methodof AutomataLabel
  \brief Complements a label

  Returns a new label that is the complement of
  label self. The complement is the negation of the expression
  contained in the label.

  \sa AutomataLabel_intersect, AutomataLabel_union
*/
AutomataLabel_ptr AutomataLabel_complement(AutomataLabel_ptr self);

/*!
  \methodof AutomataLabel
  \brief Returns the set of atomic proposition contained
  in the expression of the label

  
*/
Set_t AutomataLabel_get_support(AutomataLabel_ptr self);

/*!
  \methodof AutomataLabel
  \brief Copy a label

  Return a new copy of the label
*/
AutomataLabel_ptr AutomataLabel_copy(AutomataLabel_ptr self);

/*!
  \methodof AutomataLabel
  \brief Prints label on a stream

  
*/
void AutomataLabel_print_label(AutomataLabel_ptr self,
                                      NuSMVEnv_ptr env,
                                      FILE* stream);

/**AutomaticEnd***************************************************************/



#endif /* __NUXMV_CORE_AUTOMATA_LABELS_AUTOMATA_LABEL_H__ */

