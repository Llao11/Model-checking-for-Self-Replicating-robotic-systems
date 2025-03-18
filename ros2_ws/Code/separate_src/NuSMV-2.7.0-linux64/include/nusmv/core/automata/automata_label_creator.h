/* ---------------------------------------------------------------------------

  This file is part of the ``automata'' package.
  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Sergio Mover
  \brief header file for automata_label_creator.c

  \todo: Missing description

*/


#ifndef __NUXMV_CORE_AUTOMATA_AUTOMATA_LABEL_CREATOR_H__
#define __NUXMV_CORE_AUTOMATA_AUTOMATA_LABEL_CREATOR_H__

#include "nusmv/core/automata/automataInt.h"
#include "nusmv/core/automata/automata.h"
#include "nusmv/core/automata/labels/AutomataLabel.h"
#include "nusmv/core/automata/labels/AutomataLabelCombinator.h"

/*---------------------------------------------------------------------------*/
/* Constant declarations                                                     */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Type declarations                                                         */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Structure declarations                                                    */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Variable declarations                                                     */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Macro declarations                                                        */
/*---------------------------------------------------------------------------*/


/**AutomaticStart*************************************************************/

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \brief Create a label given its type

  Given the type of the label create a new
  instance of that type. BddEnc can bel NULL unless label_type is BDD_LABEL
*/
AutomataLabel_ptr
automata_create_label(Automaton_Label_Type label_type, BddEnc_ptr enc);

/*!
  \brief Given a type of label and an expression creates
  a new instance of that type with the given expression

  BddEnc can be NULL unless label_type is BDD_LABEL. label
  type cannot be HYBRID_LABEL
*/
AutomataLabel_ptr
automata_create_label_from_expr(Automaton_Label_Type label_type,
                                BddEnc_ptr enc,
                                Expr_ptr expr);

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
AutomataLabelCombinator_ptr
automata_create_combinator(Automaton_Label_Type label_type,
                           BddEnc_ptr bdd_enc);

/**AutomaticEnd***************************************************************/

#endif /* __NUXMV_CORE_AUTOMATA_AUTOMATA_LABEL_CREATOR_H__ */
