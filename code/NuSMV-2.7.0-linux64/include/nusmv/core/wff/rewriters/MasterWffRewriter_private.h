/* ---------------------------------------------------------------------------

  This file is part of the ``wff.rewriters'' package of NuSMV version 2.
  Copyright (C) 2014 by FBK-irst.

  NuSMV version 2 is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

  NuSMV version 2 is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA.

  For more information on NuSMV see <http://nusmv.fbk.eu>
  or email to <nusmv-users@fbk.eu>.
  Please report bugs to <nusmv-users@fbk.eu>.

  To contact the NuSMV development board, email to <nusmv@fbk.eu>.

-----------------------------------------------------------------------------*/

/*!
   \author Enrico Magnago
   \brief Private and protected interface of class 'MasterWffRewriter'

   This file can be included only by derived and friend classes

*/


#ifndef NUSMV_CORE_WFF_REWRITERS_MASTER_WFF_REWRITER_PRIVATE_H__
#define NUSMV_CORE_WFF_REWRITERS_MASTER_WFF_REWRITER_PRIVATE_H__

#include "nusmv/core/wff/rewriters/MasterWffRewriter.h"

#include "nusmv/core/wff/rewriters/WffRewriterBase.h"
#include "nusmv/core/node/MasterNodeWalker.h"
#include "nusmv/core/node/MasterNodeWalker_private.h"

/*---------------------------------------------------------------------------*/
/* Constant declarations                                                     */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Type declarations                                                         */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Structure declarations                                                    */
/*---------------------------------------------------------------------------*/

/*!
  \brief MasterCompilePredicateNormaliser class definition derived from
         class MasterCompilePredicateNormaliser



  \sa Base class MasterCompilePredicateNormaliser
*/
typedef struct MasterWffRewriter_TAG
{
  /* this MUST stay on the top */
  INHERITS_FROM(MasterNodeWalker);

  /* -------------------------------------------------- */
  /*                  Private members                   */
  /* -------------------------------------------------- */

  /* -------------------------------------------------- */
  /*                  Virtual methods                   */
  /* -------------------------------------------------- */

} MasterWffRewriter;


/*---------------------------------------------------------------------------*/
/* Variable declarations                                                     */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Macro declarations                                                        */
/*---------------------------------------------------------------------------*/

#define MASTER_WFF_REWRITER_MONITOR_PREFIX "__WFF_MONITOR_"

/* ---------------------------------------------------------------------- */
/* Private methods to be used by derivated and friend classes only        */
/* ---------------------------------------------------------------------- */

/*!
  \methodof MasterWffRewriter
  \brief The MasterWffRewriter class private initializer

  The MasterWffRewriter class private initializer

  \sa MasterWffRewriter_create
*/
void master_wff_rewriter_init(MasterWffRewriter_ptr self,
                              const NuSMVEnv_ptr env);

/*!
  \methodof MasterWffRewriter
  \brief The MasterWffRewriter class private deinitializer

  The MasterWffRewriter class private deinitializer

  \sa MasterWffRewriter_destroy
*/
void master_wff_rewriter_deinit(MasterWffRewriter_ptr self);

/*!
  \brief Call registered walker over the expression.

  returns the kind of the expression,
  i.e. if it is temporal or with input vars or next operators

  A copy of the provided expression is created and
  returned in the same pointer "expr". The copy may be exact or
  already rewritten (to remove inputs or next operator in temporal
  expressions).

  "new_var_exprs" is a list of Pairs of a new state var
  introduced during rewriting and an expression associated with that
  state variable.

  Precondition: the expression have to be correctly typed.

*/
WffRewriteFormulaKind
master_wff_rewriter_rewrite(const MasterWffRewriter_ptr self,
                            const WffRewriteMethod method,
                            const SymbLayer_ptr layer,
                            const FlatHierarchy_ptr outfh,
                            node_ptr* const expr,
                            const short int spec_type,
                            const NodeList_ptr new_var_exprs);

/*!
  \brief Creates a new state variable and add a pair <var id, expr>
  to the list "new_var_exprs"

  The purpose of the function is to create a substitution
  for the given expression in an LTL formula.

  The function returns:
  if rewrite_type is
      WFF_REWRITE_METHOD_STANDARD : new identifiers.
      WFF_REWRITE_METHOD_DEADLOCK_FREE: "X new_identifier"

  [AT] Optimization
  The input expression comes from flattener_core_flatten
  (e.g.  through Compile_FlattenSexpExpandDefine). That function, currently,
  does not applies find_node to the operation node.  If, in future, it does
  then it will be possible to check here if a given expression has already
  associated var and do not create a new one
*/
node_ptr
master_wff_rewriter_create_substitution(const MasterWffRewriter_ptr self,
                                        const WffRewriteMethod method,
                                        const FlatHierarchy_ptr outfh,
                                        const node_ptr spec,
                                        const short int spec_type,
                                        const NodeList_ptr new_var_exprs);

#endif /* NUSMV_CORE_WFF_REWRITERS_MASTER_WFF_REWRITER_PRIVATE_H__ */
