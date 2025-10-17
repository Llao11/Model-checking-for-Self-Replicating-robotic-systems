/* ---------------------------------------------------------------------------

  This file is part of the ``labels'' package.
  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Sergio Mover
  \brief Private and protected interface of class 'AutomataLabel'

  This file can be included only by derived and friend classes

*/

#ifndef __NUXMV_CORE_AUTOMATA_LABELS_AUTOMATA_LABEL_PRIVATE_H__
#define __NUXMV_CORE_AUTOMATA_LABELS_AUTOMATA_LABEL_PRIVATE_H__

#include "nusmv/core/automata/labels/labelsInt.h"
#include "nusmv/core/automata/labels/AutomataLabel.h"

#include "nusmv/core/wff/ExprMgr.h"
#include "nusmv/core/set/set.h"
#include "nusmv/core/utils/object.h"
#include "nusmv/core/utils/object_private.h"
#include "nusmv/core/utils/utils.h"

/*!
  \brief AutomataLabel class definition derived from
               class Object

  

  \sa Base class Object
*/

typedef struct AutomataLabel_TAG
{
  /* this MUST stay on the top */
  INHERITS_FROM(Object);

  /* -------------------------------------------------- */
  /*                  Private members                   */
  /* -------------------------------------------------- */
  Automaton_Label_Type label_type;
  Expr_ptr expression;


  /* -------------------------------------------------- */
  /*                  Virtual methods                   */
  /* -------------------------------------------------- */
  void (*set_expr)(AutomataLabel_ptr self, Expr_ptr new_expr);
  Expr_ptr (*get_expr)(AutomataLabel_ptr self);
  Automaton_Label_Type (*get_label_type)(AutomataLabel_ptr self);
  boolean (*is_sat)(AutomataLabel_ptr self);
  boolean (*is_model)(AutomataLabel_ptr self, Expr_ptr expression);
  boolean (*is_true)(AutomataLabel_ptr self);
  boolean (*is_equivalent)(AutomataLabel_ptr self, AutomataLabel_ptr label2);
  boolean (*is_contained)(AutomataLabel_ptr self, AutomataLabel_ptr label2);
  AutomataLabel_ptr (*intersection)(AutomataLabel_ptr self,
                                    AutomataLabel_ptr label2);
  AutomataLabel_ptr (*label_union)(AutomataLabel_ptr self,
                                   AutomataLabel_ptr label2);
  AutomataLabel_ptr (*complement)(AutomataLabel_ptr self);
  void (*simplify)(AutomataLabel_ptr self);
  Set_t (*get_support)(AutomataLabel_ptr self);
  AutomataLabel_ptr (*copy)(AutomataLabel_ptr self);
  void (*print_label)(AutomataLabel_ptr self, NuSMVEnv_ptr env, FILE* stream);

} AutomataLabel;



/* ---------------------------------------------------------------------- */
/* Private methods to be used by derivated and friend classes only         */
/* ---------------------------------------------------------------------- */

/*!
  \methodof AutomataLabel
  \brief The AutomataLabel class private initializer

  The AutomataLabel class private initializer

  \sa AutomataLabel_create
*/
void automata_label_init(AutomataLabel_ptr self);

/*!
  \methodof AutomataLabel
  \brief The AutomataLabel class private deinitializer

  The AutomataLabel class private deinitializer

  \sa AutomataLabel_destroy
*/
void automata_label_deinit(AutomataLabel_ptr self);

/*!
  \methodof AutomataLabel
  \brief Replace the reference of expression with new_expr

  
*/
void
automata_label_set_expr(AutomataLabel_ptr self, Expr_ptr new_expr);

/*!
  \methodof AutomataLabel
  \brief Returns the expression of the label

  
*/
Expr_ptr automata_label_get_expr(AutomataLabel_ptr self);

/*!
  \methodof AutomataLabel
  \brief Set the type of the label. This function is
  called only by frient and derivative classes.

  
*/
void
automata_label_set_label_type(AutomataLabel_ptr self,
                              Automaton_Label_Type label_type);

/*!
  \methodof AutomataLabel
  \brief Returns the enumeration that represents the type of the
  label

  
*/
Automaton_Label_Type
automata_label_get_label_type(AutomataLabel_ptr self);

/*!
  \methodof AutomataLabel
  \brief Pure virtual function, checks if the label is
  satisfiable.

  It is a pure virtual function and AutomataLabel
  is an abstract base class. Every derived class must ovewrwrite this function.
*/
boolean automata_label_is_sat(AutomataLabel_ptr self);

/*!
  \methodof AutomataLabel
  \brief Pure virtual function, checks if expression is a
  model for the label self.

  It is a pure virtual function and AutomataLabel
  is an abstract base class. Every derived class must ovewrwrite this function.
*/
boolean automata_label_is_model(AutomataLabel_ptr self,
                                       Expr_ptr expression);

/*!
  \methodof AutomataLabel
  \brief Pure virtual function, checks if true.

  It is a pure virtual function and AutomataLabel
  is an abstract base class. Every derived class must ovewrwrite this function.
*/
boolean automata_label_is_true(AutomataLabel_ptr self);

/*!
  \methodof AutomataLabel
  \brief Pure virtual function, checks if two labels are
  equivalent.

  It is a pure virtual function and AutomataLabel
  is an abstract base class. Every derived class must ovewrwrite this
  function.
*/
boolean automata_label_is_equivalent(AutomataLabel_ptr self,
                                            AutomataLabel_ptr label2);

/*!
  \methodof AutomataLabel
  \brief Pure virtual function, checks if self is
  contained in label2.

  It is a pure virtual function and AutomataLabel
  is an abstract base class. Every derived class must ovewrwrite this
  function.
*/
boolean automata_label_is_contained(AutomataLabel_ptr self,
                                           AutomataLabel_ptr label2);

/*!
  \methodof AutomataLabel
  \brief Pure virtual function, performs the intersection
  of two labels.

  It is a pure virtual function and AutomataLabel
  is an abstract base class. Every derived class must ovewrwrite this function.
*/
AutomataLabel_ptr
automata_label_intersection(AutomataLabel_ptr self,
                            AutomataLabel_ptr label2);

/*!
  \methodof AutomataLabel
  \brief Pure virtual function, performs the union of two
  labels.

  It is a pure virtual function and AutomataLabel
  is an abstract base class. Every derived class must ovewrwrite this
  function.
*/
AutomataLabel_ptr
automata_label_union(AutomataLabel_ptr self,
                     AutomataLabel_ptr label2);

/*!
  \methodof AutomataLabel
  \brief Pure virtual function, performs the complement
  of the label.

  It is a pure virtual function and AutomataLabel
  is an abstract base class. Every derived class must ovewrwrite this
  function.
*/
AutomataLabel_ptr
automata_label_complement(AutomataLabel_ptr self);

/*!
  \methodof AutomataLabel
  \brief \todo Missing synopsis

  \todo Missing description
*/
void automata_label_simplify(AutomataLabel_ptr self);

/*!
  \methodof AutomataLabel
  \brief Pure virtual function, returns the set of atomic
  propositions contained in the formula of the label.

  It is a pure virtual function and AutomataLabel
  is an abstract base class. Every derived class must ovewrwrite this function.
*/
Set_t automata_label_get_support(AutomataLabel_ptr self);

/*!
  \methodof AutomataLabel
  \brief Pure virtual function, returns a copy of the label.

  It is a pure virtual function and AutomataLabel
  is an abstract base class. Every derived class must ovewrwrite this function.
*/
AutomataLabel_ptr automata_label_copy(AutomataLabel_ptr self);

/*!
  \methodof AutomataLabel
  \brief \todo Missing synopsis

  \todo Missing description
*/
void automata_label_print_label(AutomataLabel_ptr self,
                                       NuSMVEnv_ptr env,
                                       FILE* stream);

#endif /* __NUXMV_CORE_AUTOMATA_LABELS_AUTOMATA_LABEL_PRIVATE_H__ */
