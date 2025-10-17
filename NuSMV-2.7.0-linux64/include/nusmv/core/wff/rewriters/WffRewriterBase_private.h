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
  \brief Private and protected interface of class 'WffRewriteBase'

  This file can be included only by derived and friend classes

*/



#ifndef NUSMV_CORE_WFF_REWRITERS_WFF_REWRITER_BASE_PRIVATE_H__
#define NUSMV_CORE_WFF_REWRITERS_WFF_REWRITER_BASE_PRIVATE_H__


#include "nusmv/core/wff/rewriters/WffRewriterBase.h"

#include "nusmv/core/node/NodeWalker.h"
#include "nusmv/core/node/NodeWalker_private.h"

/*!
  \brief WffRewriterBase class definition derived from
               class node.NodeWalker



  \sa Base class node.NodeWalker
*/

typedef struct WffRewriterBase_TAG
{
  /* this MUST stay on the top */
  INHERITS_FROM(NodeWalker);

  /* -------------------------------------------------- */
  /*                  Private members                   */
  /* -------------------------------------------------- */
  /* -------------------------------------------------- */
  /*                  Virtual methods                   */
  /* -------------------------------------------------- */

  WffRewriteFormulaKind (*rewrite_formula)(const WffRewriterBase_ptr self,
                                           const WffRewriteMethod method,
                                           const SymbLayer_ptr layer,
                                           const FlatHierarchy_ptr outfh,
                                           node_ptr* const expr,
                                           const short int spec_type,
                                           const NodeList_ptr new_var_exprs);

  boolean (*is_rewriting_needed)(const WffRewriterBase_ptr self,
                                 const SymbTable_ptr st,
                                 const WffRewriterExpectedProperty eproptype,
                                 const node_ptr wff,
                                 const node_ptr context);

} WffRewriterBase;

/*---------------------------------------------------------------------------*/
/* Macro declarations                                                        */
/*---------------------------------------------------------------------------*/

/*!
  \brief Short way of calling wff_rewriter_base_throw_rewrite_formula

  Use this macro to recursively recall the rewrite_formula function
*/
#undef _THROW
#define _THROW_REWRITE(self, method, layer, outfh, expr,                \
                       spec_type, new_var_exprs)                        \
  wff_rewriter_base_throw_rewrite_formula(WFF_REWRITER_BASE(self),      \
                                          method, layer, outfh,         \
                                          expr, spec_type,              \
                                          new_var_exprs)

/*!
  \brief Short way of calling
    wff_rewriter_base_throw_is_rewriting_needed

  Use this macro to recursively recall the is_rewriting_needed function
*/

#define _THROW_IS_REWRITING_NEEDED(self, st, eproptype, wff, context)   \
  wff_rewriter_base_throw_is_rewriting_needed(WFF_REWRITER_BASE(self),  \
                                              st, eproptype, wff, context)


/* ---------------------------------------------------------------------- */
/* Private methods to be used by derivated and friend classes only         */
/* ---------------------------------------------------------------------- */

/*!
  \methodof WffRewriterBase
  \brief The WffRewriterBase class private initializer

  The WffRewriterBase class private initializer

  \sa WffRewriterBase_create
*/
void
wff_rewriter_base_init(WffRewriterBase_ptr self, const NuSMVEnv_ptr env,
                       const char* name, const int low, const size_t num,
                       const boolean handle_null);

/*!
  \methodof WffRewriterBase
  \brief The WffRewriterBase class private deinitializer

  The WffRewriterBase class private deinitializer

  \sa WffRewriterBase_destroy
*/
void wff_rewriter_base_deinit(WffRewriterBase_ptr self);

/*!
  \methodof WffRewriterBase
  \brief The WffRewriterBase class copy constructor

  The WffRewriterBase class private copy constructor.

  Important: copied master will be not registered to any master, and
  will have to be explicitly registered.

  \sa Object_copy, node_walker_copy_aux
*/
void wff_rewriter_base_copy_aux(const WffRewriterBase_ptr self,
                                WffRewriterBase_ptr other);

/*!
  \methodof WffRewriterBase
  \brief Helper method to make recursive calls on the master node walker.

  \sa _THROW_REWRITE
*/
WffRewriteFormulaKind
wff_rewriter_base_throw_rewrite_formula(const WffRewriterBase_ptr self,
                                        const WffRewriteMethod method,
                                        const SymbLayer_ptr layer,
                                        const FlatHierarchy_ptr outfh,
                                        node_ptr* const expr,
                                        const short int spec_type,
                                        const NodeList_ptr new_var_exprs);

boolean
wff_rewriter_base_throw_is_rewriting_needed(const WffRewriterBase_ptr self,
                                            const SymbTable_ptr st,
                                            const WffRewriterExpectedProperty eproptype,
                                            const node_ptr wff,
                                            const node_ptr context);

#endif /* NUSMV_CORE_WFF_WFF_REWRITER_BASE_PRIVATE_H__ */
