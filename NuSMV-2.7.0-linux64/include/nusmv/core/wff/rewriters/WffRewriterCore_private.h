/* ---------------------------------------------------------------------------


  This file is part of the ``wff.rewriters'' package
  of NuSMV version 2. Copyright (C) 2006 by FBK-irst.

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
  \brief Private and protected interface of class 'WffRewriteCore'

  This file can be included only by derived and friend classes

*/



#ifndef NUSMV_CORE_WFF_REWRITERS_WFF_REWRITER_CORE_PRIVATE_H__
#define NUSMV_CORE_WFF_REWRITERS_WFF_REWRITER_CORE_PRIVATE_H__


#include "nusmv/core/wff/rewriters/WffRewriterCore.h"
#include "nusmv/core/wff/rewriters/WffRewriterBase_private.h"

/* name associated to the WffRewriterCore node walker */
#define WFF_REWRITER_CORE_NAME "Wff rewriter core"


/*!
  \brief WffRewriterCore class definition derived from
               class WffRewriterBase



  \sa Base class WffRewriterBase
*/

typedef struct WffRewriterCore_TAG
{
  /* this MUST stay on the top */
  INHERITS_FROM(WffRewriterBase);

  /* -------------------------------------------------- */
  /*                  Private members                   */
  /* -------------------------------------------------- */

  /* -------------------------------------------------- */
  /*                  Virtual methods                   */
  /* -------------------------------------------------- */

} WffRewriterCore;



/* ---------------------------------------------------------------------- */
/* Private methods to be used by derivated and friend classes only         */
/* ---------------------------------------------------------------------- */

/*!
  \methodof WffRewriterCore
  \brief The WffRewriterCore class private initializer

  The WffRewriterCore class private initializer

  \sa WffRewriterCore_create
*/
void
wff_rewriter_core_init(WffRewriterCore_ptr self, const NuSMVEnv_ptr env,
                       const char* name, const int low, const size_t num,
                       const boolean handle_null);

/*!
  \methodof WffRewriterCore
  \brief The WffRewriterCore class private deinitializer

  The WffRewriterCore class private deinitializer

  \sa WffRewriterCore_destroy
*/
void wff_rewriter_core_deinit(WffRewriterCore_ptr self);

/*!
  \methodof WffRewriterCore
  \brief The WffRewriterCore class copy constructor

  The WffRewriterCore class private copy constructor.

  Important: copied master will be not registered to any master, and
  will have to be explicitly registered.

  \sa Object_copy, node_walker_copy_aux
*/
void wff_rewriter_core_copy_aux(const WffRewriterCore_ptr self,
                                WffRewriterCore_ptr other);

/*!
  \brief  implementation of virtual method rewrite_formula

  Recursively walk over the expressions and returns
  the kind of the expression, i.e. if it is temporal or with input vars or next
  operators

  A copy of the provided expression is created and
  returned in the same pointer "expr". The copy may be exact or
  already rewritten (to remove inputs or next operator in temporal
  expressions).

  "new_var_exprs" is a list of Pairs of a new state var
  introduced during rewriting and an expression associated with that
  state variable.

  Precondition: the expression have to be correctly typed.

  NOTE FOR DEVELOPERS: This function creates new expression using the
  same approach as flattener_core_flatten, i.e. consts and ids are
  find_atom-ed and operations are new_node-ed. Both functions should be
  changed synchronously.

  \sa WffRewriterBase_rewrite_formula, PropRewriteFormulaKind
*/

WffRewriteFormulaKind
wff_rewriter_core_rewrite_formula(const WffRewriterBase_ptr self,
                                  const WffRewriteMethod method,
                                  const SymbLayer_ptr layer,
                                  const FlatHierarchy_ptr outfh,
                                  node_ptr* const expr,
                                  const short int spec_type,
                                  const NodeList_ptr new_var_exprs);

/*!
  \methodof WffRewriterCore
  \brief implementation of virtual method is_rewriting_needed

  \sa WffRewriterBase_is_rewriting_needed
*/
boolean wff_rewriter_core_is_rewriting_needed(const WffRewriterBase_ptr self,
                                              const SymbTable_ptr st,
                                              const WffRewriterExpectedProperty eproptype,
                                              const node_ptr wff,
                                              const node_ptr context);

#endif /* NUSMV_CORE_WFF_WFF_REWRITER_CORE_PRIVATE_H__ */
