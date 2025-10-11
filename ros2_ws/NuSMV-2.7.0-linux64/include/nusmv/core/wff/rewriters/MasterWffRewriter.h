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
   \brief Public interface of class 'MasterWffRewriter'

*/

#ifndef NUSMV_CORE_WFF_REWRITERS_MASTER_WFF_REWRITER_H__
#define NUSMV_CORE_WFF_REWRITERS_MASTER_WFF_REWRITER_H__

#include "nusmv/core/cinit/NuSMVEnv.h"
#include "nusmv/core/utils/Pair.h"
#include "nusmv/core/compile/FlatHierarchy.h"


/*---------------------------------------------------------------------------*/
/* Constant declarations                                                     */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Type declarations                                                         */
/*---------------------------------------------------------------------------*/

/*!
  \brief Rewriting methods


  WFF_REWRITE_STANDARD:

  The LTL formula is rewritten by substituting a fresh boolean state
  variable sv for Phi and adding a new transition relation TRANS sv
  <-> Phi. For example, LTL formula

  G (s < i);

  becomes

  G sv;

  and the model is augmented by

  VAR sv : boolean;
  TRANS sv <-> (s < i);

  Note 1: new deadlocks are introduced after the rewriting (because
  new vars are assigned a value before the value of input vars are
  known).  For example, with "TRANS s <i" the original model does
  not have a deadlock but after rewriting it does.  For BDD LTL this
  is not a problem because all paths with deadlocks are ignored and
  all original paths are kept by the rewriting.


  Note 2: the validity of an old and a new LTL formulas is the same
  on *infinite* paths. On finite paths the semantics of formulas is
  different because of the deadlocks.  For above example, if there
  is additionally "TRANS s < i" then on infinite paths "G sv" and "G
  s < i" are both valid whereas there is finite path which violate
  "G sv" and there is NO such finite path for "G s<i".

  This thing happens with BMC (which looks for finite path violating
  a formula) vs BDD (which checks only infinite paths). See next
  rewrite method for a possible solution.

  WFF_REWRITE_DEADLOCK_FREE method:

  The LTL formula is rewriten by substituting Phi with "X sv", where
  sv is a fresh boolean state variable, and adding a new transition
  relation "TRANS next(sv) <-> Phi" and a new initial condition
  "INIT sv"; For example, LTL formula

  G (s < i)

  becomes

  G (X sv)

  and the model is augmented by

  VAR sv : boolean;
  INIT sv;
  TRANS next(sv) <-> (s < i);
*/
typedef enum {
  WFF_REWRITE_METHOD_STANDARD,
  WFF_REWRITE_METHOD_DEADLOCK_FREE,
} WffRewriteMethod;


/*! \brief The type of expected input property.

  The input property to be converted is a generalized invar
  (WFF_REWRITER_REWRITE_INPUT_NEXT) with at least one next/input
  variable in the invariant, or an LTL property to be converted if
  possible into an invariant to be checked (modulo a proper extension
  of the transition system (e.g. p -> G q, .. G(p) -> G(q)), ....)
*/
typedef enum {
  WFF_REWRITER_REWRITE_INPUT_NEXT,
  WFF_REWRITER_LTL_2_INVAR
} WffRewriterExpectedProperty;


/*!
  \struct MasterWffRewriter
  \brief Definition of the public accessor for class MasterWffRewriter
*/
typedef struct MasterWffRewriter_TAG*  MasterWffRewriter_ptr;

/*---------------------------------------------------------------------------*/
/* Structure declarations                                                    */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Variable declarations                                                     */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Macro declarations                                                        */
/*---------------------------------------------------------------------------*/

#define ENV_WFF_REWRITER_LIST "ENV_WFF_REWRITER_LIST"


/*!
  \brief To cast and check instances of class MasterWffRewriter

  These macros must be used respectively to cast and to check
  instances of class MasterWffRewriter

*/
#define MASTER_WFF_REWRITER(self) \
         ((MasterWffRewriter_ptr) self)

#define MASTER_WFF_REWRITER_CHECK_INSTANCE(self) \
         (nusmv_assert(MASTER_WFF_REWRITER(self) != MASTER_WFF_REWRITER(NULL)))

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \methodof MasterWffRewriter
  \brief The MasterWffRewriter class constructor

  The MasterWffRewriter class constructor

  \sa MasterWffRewriter_destroy
*/
MasterWffRewriter_ptr MasterWffRewriter_create(const NuSMVEnv_ptr env);


/*!
  \methodof MasterWffRewriter
  \brief The MasterWffRewriter class destructor

  The MasterWffRewriter class destructor

  \sa MasterWffRewriter_create
*/
void MasterWffRewriter_destroy(MasterWffRewriter_ptr self);

/*!
  \methodof MasterWffRewriter
  \brief Return an equivalent specification, without input vars
  and next operators

  The equivalence is kept by making side effects on layer
  and outfh. layer must belong to the outfh symbol table. When the
  WFF_REWRITE_METHOD_DEADLOCK_FREE is selected, then
  initialize_monitor_to_true control the value the monitor variable
  is initialized to. I.e. if true it is initialized to TRUE, else to FALSE.

  \se layer and outfh are possibly modified

  \sa Prop_Rewriter_private.h
*/
Pair_ptr MasterWffRewriter_rewrite_formula(const MasterWffRewriter_ptr self,
                                           const WffRewriteMethod method,
                                           const WffRewriterExpectedProperty eproptype,
                                           const SymbLayer_ptr layer,
                                           const FlatHierarchy_ptr outfh,
                                           const node_ptr spec,
                                           const short int spec_type,
                                           const boolean initialize_monitor_to_true,
                                           const boolean ltl2invar_negate_property);

/*!
  \methodof MasterWffRewriter
  \brief Checks if "wff" needs to be rewritten

*/
boolean MasterWffRewriter_is_rewriting_needed(MasterWffRewriter_ptr self,
                                              const SymbTable_ptr st,
                                              const WffRewriterExpectedProperty eproptype,
                                              const node_ptr wff,
                                              const node_ptr context);


#endif /* NUSMV_CORE_WFF_REWRITERS_MASTER_WFF_REWRITER_H__ */
