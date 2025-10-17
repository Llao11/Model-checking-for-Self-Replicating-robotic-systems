/* ---------------------------------------------------------------------------


  This file is part of the ``wff.rewriters''
  package of NuSMV version 2. Copyright (C) 2006 by FBK-irst.

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
  \brief Public interface of class 'WffRewriterBase'

  \todo: Missing description

*/



#ifndef NUSMV_CORE_WFF_REWRITERS_WFF_REWRITER_BASE_H__
#define NUSMV_CORE_WFF_REWRITERS_WFF_REWRITER_BASE_H__

#include "nusmv/core/wff/rewriters/MasterWffRewriter.h"

#include "nusmv/core/compile/FlatHierarchy.h"
#include "nusmv/core/compile/symb_table/SymbTable.h"
#include "nusmv/core/compile/symb_table/SymbLayer.h"


/*---------------------------------------------------------------------------*/
/* Constant declarations                                                     */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Type declarations                                                         */
/*---------------------------------------------------------------------------*/

/*!
  \struct WffRewriterBase
  \brief Definition of the public accessor for class WffRewriterBase


*/
typedef struct WffRewriterBase_TAG*  WffRewriterBase_ptr;

/*!
  \brief WffRewriter constructor function type.
*/
typedef WffRewriterBase_ptr(*typeWffRewriterCreate)(const NuSMVEnv_ptr);

/*---------------------------------------------------------------------------*/
/* Structure declarations                                                    */
/*---------------------------------------------------------------------------*/

/*!
  \brief Enumeration of possible sub-expressions kinds

*/
typedef enum WffRewriteFormulaKind_TAG {
  WFF_REWRITE_FORMULA_KIND_FIRST = 0,
  WFF_REWRITE_FORMULA_KIND_STATE = 1, /* non-temporal and without input vars or
                                         next operator */
  WFF_REWRITE_FORMULA_KIND_INPUT = 1 << 1, /* non-temporal but with input vars */
  WFF_REWRITE_FORMULA_KIND_NEXT = 1 << 2, /* non-temporal but with next operator */
  WFF_REWRITE_FORMULA_KIND_INPUT_NEXT =
  WFF_REWRITE_FORMULA_KIND_INPUT |
  WFF_REWRITE_FORMULA_KIND_NEXT, /* non-temporal but with input vars
                                    and next operator */
  WFF_REWRITE_FORMULA_KIND_TEMP = 1 << 3, /* temporal (it must be without input
                                             vars or next operator) */
  WFF_REWRITE_FORMULA_KIND_LAST = 1 << 4
} WffRewriteFormulaKind;


/*---------------------------------------------------------------------------*/
/* Variable declarations                                                     */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Macro declarations                                                        */
/*---------------------------------------------------------------------------*/

/*!
  \brief To cast and check instances of class WffRewriterBase

  These macros must be used respectively to cast and to check
  instances of class WffRewriterBase
*/
#define WFF_REWRITER_BASE(self) \
  ((WffRewriterBase_ptr) self)

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define WFF_REWRITER_BASE_CHECK_INSTANCE(self) \
  (nusmv_assert(WFF_REWRITER_BASE(self) != WFF_REWRITER_BASE(NULL)))



/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \methodof WffRewriterBase
  \brief The WffRewriterBase class destructor

  The WffRewriterBase class destructor

*/
VIRTUAL void WffRewriterBase_destroy(WffRewriterBase_ptr self);

/*!
  \methodof WffRewriterBase
  \brief Return an equivalent specification, without input vars
  and next operators


  The equivalence is kept by making side effects on layer
  and outfh. layer must belong to the outfh symbol table. When the
  WFF_REWRITE_METHOD_DEADLOCK_FREE is selected, then
  initialize_monitor_to_true control the value the monitor variable
  is initialized to. I.e. if true it is initialized to TRUE, else to FALSE.

  \se layer and outfh are possibly modified

  \sa master_wff_rewriter_rewrite
*/
VIRTUAL WffRewriteFormulaKind
WffRewriterBase_rewrite_formula(const WffRewriterBase_ptr self,
                                const WffRewriteMethod method,
                                const SymbLayer_ptr layer,
                                const FlatHierarchy_ptr outfh,
                                node_ptr* const expr,
                                const short int spec_type,
                                const NodeList_ptr new_var_exprs);

/*!
  \methodof WffRewriterBase
  \brief Checks if "wff" contains input variables or next
  operators, i.e. it is a generalized wff

*/
VIRTUAL boolean
WffRewriterBase_is_rewriting_needed(const WffRewriterBase_ptr self,
                                    const SymbTable_ptr st,
                                    const WffRewriterExpectedProperty eproptype,
                                    const node_ptr wff,
                                    const node_ptr context);

/**AutomaticEnd***************************************************************/


#endif /* NUSMV_CORE_WFF_REWRITERS_WFF_REWRITER_BASE_H__ */
