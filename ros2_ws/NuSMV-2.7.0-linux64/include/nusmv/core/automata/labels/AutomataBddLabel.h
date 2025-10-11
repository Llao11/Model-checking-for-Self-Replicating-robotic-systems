/* ---------------------------------------------------------------------------

  This file is part of the ``labels'' package.
  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Sergio Mover
  \brief Public interface of class 'AutomataBddLabel'

  \todo: Missing description

*/

#ifndef __NUXMV_CORE_AUTOMATA_LABELS_AUTOMATA_BDD_LABEL_H__
#define __NUXMV_CORE_AUTOMATA_LABELS_AUTOMATA_BDD_LABEL_H__

#include "nusmv/core/automata/labels/AutomataLabel.h"

#include "nusmv/core/set/set.h"
#include "nusmv/core/utils/utils.h"
#include "nusmv/core/enc/bdd/BddEnc.h"

/*!
  \struct AutomataBddLabel
  \brief Definition of the public accessor for class AutomataBddLabel

  
*/
typedef struct AutomataBddLabel_TAG*  AutomataBddLabel_ptr;

/*!
  \brief To cast and check instances of class AutomataBddLabel

  These macros must be used respectively to cast and to check
  instances of class AutomataBddLabel
*/
#define AUTOMATA_BDD_LABEL(self) \
         ((AutomataBddLabel_ptr) self)

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define AUTOMATA_BDD_LABEL_CHECK_INSTANCE(self) \
         (nusmv_assert(AUTOMATA_BDD_LABEL(self) != AUTOMATA_BDD_LABEL(NULL)))



/**AutomaticStart*************************************************************/

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \methodof AutomataBddLabel
  \brief The AutomataBddLabel class constructor

  The AutomataBddLabel class constructor

  \sa AutomataBddLabel_destroy
*/
AutomataBddLabel_ptr AutomataBddLabel_create(BddEnc_ptr bdd_enc);

/*!
  \methodof AutomataBddLabel
  \brief The AutomataBddLabel class destructor

  The AutomataBddLabel class destructor

  \sa AutomataBddLabel_create
*/
void AutomataBddLabel_destroy(AutomataBddLabel_ptr self);

/*!
  \methodof AutomataBddLabel
  \brief Alternative AutomataBddLabel class constructor

  Construct an instance of AutomataBddLabel setting
  the expression of the label.

  \sa AutomataBddLabel_destroy
*/
AutomataBddLabel_ptr AutomataBddLabel_create_from_expr(BddEnc_ptr bdd_enc,
						       Expr_ptr expr);

/*!
  \methodof AutomataBddLabel
  \brief Alternative AutomataBddLabel class constructor

  Construct an instance of AutomataBddLabel setting
  the BDD-based label.
*/
AutomataBddLabel_ptr AutomataBddLabel_create_from_bdd(BddEnc_ptr bdd_enc,
						      bdd_ptr bdd);

/*!
  \methodof AutomataBddLabel
  \brief Getting the underlying BDD from an AutomataBddLabel
*/
bdd_ptr AutomataBddLabel_get_bdd(AutomataBddLabel_ptr);

/*!
  \methodof AutomataBddLabel
  \brief (Re)setting the underlying BDD of an AutomataBddLabel
*/
void AutomataBddLabel_set_bdd(AutomataBddLabel_ptr, bdd_ptr);

/**AutomaticEnd***************************************************************/

#endif /* __NUXMV_CORE_AUTOMATA_LABELS_AUTOMATA_BDD_LABEL_H__ */
