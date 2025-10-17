/* ---------------------------------------------------------------------------


  This file is part of the ``compile.symb_table'' package of NuSMV
  version 2.  Copyright (C) 2004 by FBK-irst.

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
  \author Roberto Cavada

  \brief Declarations for utility functions used in filters of
  SymbTable, and SymbLayer.

  Filters that can be used with symbol iterators in symbol tables and
  symb layers can be declared here, to factorize code when needed.

  However, for specific cases, do not add functions which are likely
  used only once.
*/


#ifndef __NUSMV_CORE_COMPILE_SYMB_TABLE_FILTERS_H__
#define __NUSMV_CORE_COMPILE_SYMB_TABLE_FILTERS_H__


#include "nusmv/core/compile/symb_table/SymbTable.h"
#include "nusmv/core/utils/NodeList.h"
#include "nusmv/core/node/node.h"


/*!
  \brief Preset iterator filter: Input symbols

  Preset iterator filter: Input symbols.
  Only defines that predicate over input variables
  or input variables themselfs satisfy this
  filter.
*/
boolean
SymbTableIterFilterFun_take_i_symbols(const SymbTable_ptr st,
                                      const node_ptr sym,
                                      void* arg);

/*!
  \brief Preset iterator filter: State, Frozen and Input symbols

  Preset iterator filter: State, Frozen and Input symbols.
  Only defines that predicate over state or frozen
  AND input variables or variables themselfs
  satisfy this filter.
*/
boolean
SymbTableIterFilterFun_take_sf_i_symbols(const SymbTable_ptr st,
                                         const node_ptr sym,
                                         void* arg);

/*!
  \methodof SymbTable
  \brief Preset iterator filter: State, Frozen symbols

  Preset iterator filter: State, Frozen symbols.
  Only defines that predicate over state or frozen
  variables or state / frozen variables themselfs
  satisfy this filter.
*/
boolean
SymbTableIterFilterFun_take_sf_symbols(const SymbTable_ptr st,
                                       const node_ptr sym,
                                       void* arg);

/*!
  \brief Preset iterator filter: skips var array elements

  Variables declared from an array are skipped
*/
boolean SymbTableIterFilterFun_skip_var_array_elems(const SymbTable_ptr st,
                                                    const node_ptr sym,
                                                    void* arg);

/*!
  \brief Variable Array Element filter

  SymbLayer built-in filter: Returns false iff the symbol
  is a var array element (a variable internally declared from a finite array
  declaration).

  WARNING: argument *must* be the SymbTable containing the layer,
  which means that `SymbLayer_iter_set_filter` has to be called with
  the symbol table instance when creating the SymbLayerIter.
*/
boolean SymbLayerIterFilterFun_skip_var_array_elems(const SymbLayer_ptr st,
                                                    const node_ptr sym,
                                                    void* arg_st);

/*!
  \brief Boolean Variables filter

  SymbTable built-in filter: Returns true iff the symbol
  is a boolean variable.
*/
boolean SymbTableIterFilterFun_take_bool_vars(const SymbTable_ptr st,
                                              const node_ptr sym,
                                              void* arg);
/*!
  \brief Boolean Variables filter

  SymbLayer built-in filter: Returns true iff the symbol
  is a boolean variable.

  WARNING: argument *must* be the SymbTable containing the layer,
  which means that `SymbLayer_iter_set_filter` has to be called with
  the symbol table instance when creating the SymbLayerIter.
*/
boolean
SymbLayerIterFilterFun_take_bool_vars(const SymbLayer_ptr layer,
                                      const node_ptr sym,
                                      void* symbol_table);


#endif  /* __NUSMV_CORE_COMPILE_SYMB_TABLE_FILTERS_H__ */
