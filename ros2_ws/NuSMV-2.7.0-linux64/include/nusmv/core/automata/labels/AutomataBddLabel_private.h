/* ---------------------------------------------------------------------------

  This file is part of the ``labels'' package.
  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Sergio Mover
  \brief Private and protected interface of class 'AutomataBddLabel'

  This file can be included only by derived and friend classes

*/

#ifndef __NUXMV_CORE_AUTOMATA_LABELS_AUTOMATA_BDD_LABEL_PRIVATE_H__
#define __NUXMV_CORE_AUTOMATA_LABELS_AUTOMATA_BDD_LABEL_PRIVATE_H__

#include "nusmv/core/automata/labels/AutomataBddLabel.h"
#include "nusmv/core/automata/labels/AutomataLabel.h"
#include "nusmv/core/automata/labels/AutomataLabel_private.h"

#include "nusmv/core/enc/bdd/bdd.h"
#include "nusmv/core/set/set.h"
#include "nusmv/core/utils/utils.h"

/*!
  \brief AutomataBddLabel class definition derived from
               class AutomataLabel

  \sa Base class AutomataLabel
*/

typedef struct AutomataBddLabel_TAG
{
  /* this MUST stay on the top */
  INHERITS_FROM(AutomataLabel);

  /* -------------------------------------------------- */
  /*                  Private members                   */
  /* -------------------------------------------------- */
  BddEnc_ptr bdd_enc;
  bdd_ptr bdd_expr;

  /* -------------------------------------------------- */
  /*                  Virtual methods                   */
  /* -------------------------------------------------- */

} AutomataBddLabel;



/* ---------------------------------------------------------------------- */
/* Private methods to be used by derivated and friend classes only         */
/* ---------------------------------------------------------------------- */
/*!
  \methodof AutomataBddLabel
  \todo
*/
void automata_bdd_label_init(AutomataBddLabel_ptr self, BddEnc_ptr enc);
/*!
  \methodof AutomataBddLabel
  \todo
*/
void automata_bdd_label_deinit(AutomataBddLabel_ptr self);

void automata_bdd_label_set_expr(AutomataLabel_ptr automata_label,
                                 Expr_ptr expression);

Expr_ptr automata_bdd_label_get_expr(AutomataLabel_ptr automata_label);

boolean automata_bdd_label_is_sat(AutomataLabel_ptr automata_label);

boolean automata_bdd_label_is_model(AutomataLabel_ptr automata_label,
                                    Expr_ptr expression);

boolean automata_bdd_label_is_true(AutomataLabel_ptr automata_label);


boolean automata_bdd_label_is_equivalent(AutomataLabel_ptr automata_label,
                                         AutomataLabel_ptr automata_label2);

boolean automata_bdd_label_is_contained(AutomataLabel_ptr automata_label,
                                        AutomataLabel_ptr automata_label2);

AutomataLabel_ptr automata_bdd_label_intersection(AutomataLabel_ptr automata_label,
                                                  AutomataLabel_ptr automata_label2);

AutomataLabel_ptr automata_bdd_label_union(AutomataLabel_ptr automata_label,
                                           AutomataLabel_ptr automata_label2);

AutomataLabel_ptr automata_bdd_label_complement(AutomataLabel_ptr automata_label);

Set_t automata_bdd_label_get_support(AutomataLabel_ptr automata_label);

AutomataLabel_ptr automata_bdd_label_copy(AutomataLabel_ptr automata_label);

/* The method signature is inherited from AutomataLabel "class" in which
   there's no "bdd_enc" to retrieve back the "env", which has to be a
   parameter here.
 */
void automata_bdd_label_print_label(AutomataLabel_ptr self,
				    NuSMVEnv_ptr env,
				    FILE* outfile);

#endif /* __NUXMV_CORE_AUTOMATA_LABELS_AUTOMATA_BDD_LABEL_PRIVATE_H__ */
