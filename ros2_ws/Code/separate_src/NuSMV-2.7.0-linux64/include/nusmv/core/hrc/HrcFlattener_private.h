/* ---------------------------------------------------------------------------


  This file is part of the ``hrc'' package of NuSMV version 2.
  Copyright (C) 2013 by FBK-irst.

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
  \author Alessandro Mariotti, Michele Dorigatti
  \brief Private and protected interface of class 'HrcFlattener'

  This file can be included only by derived and friend classes
*/

#ifndef __NUSMV_CORE_HRC_HRC_FLATTENER_PRIVATE_H__
#define __NUSMV_CORE_HRC_HRC_FLATTENER_PRIVATE_H__

/* Base class */
#include "nusmv/core/utils/EnvObject.h"
#include "nusmv/core/utils/EnvObject_private.h"

/* fields */
#include "nusmv/core/cinit/NuSMVEnv.h"
#include "nusmv/core/compile/FlatHierarchy.h"
#include "nusmv/core/compile/symb_table/SymbTable.h"
#include "nusmv/core/compile/symb_table/SymbLayer.h"
#include "nusmv/core/hrc/HrcNode.h"

/*!
  \brief HrcFlattener class definition derived from
  class EnvObject

  \sa Base class EnvObject
*/
typedef struct HrcFlattener_TAG
{
  /* -------------------------------------------------- */
  /*                  Private members                   */
  /* -------------------------------------------------- */
  INHERITS_FROM(EnvObject);

  /* -------------------------------------------------- */
  /*                  Private members                   */
  /* -------------------------------------------------- */

  FlatHierarchy_ptr hierarchy;
  SymbTable_ptr symb_table;
  SymbLayer_ptr layer;
  HrcNode_ptr root_node;

  boolean build_hierarchy;
  boolean populate_symb_table;
  boolean allow_symb_table_update;

  /* -------------------------------------------------- */
  /*                  Virtual methods                   */
  /* -------------------------------------------------- */
  void (*populate_model)(HrcFlattener_ptr self,
                         HrcNode_ptr node,
                         node_ptr context);

} HrcFlattener;


/*!
  \methodof HrcFlattener
  \brief The HrcFlattener class private initializer

  The HrcFlattener class private initializer

  \sa HrcFlattener_create
*/
void hrc_flattener_init(HrcFlattener_ptr self,
                        const NuSMVEnv_ptr env,
                        HrcNode_ptr node,
                        SymbTable_ptr symb_table,
                        SymbLayer_ptr layer);

/*!
  \methodof HrcFlattener
  \brief The HrcFlattener class private deinitializer

  The HrcFlattener class private deinitializer

  \sa HrcFlattener_destroy
*/
void hrc_flattener_deinit(HrcFlattener_ptr self);

/*!
  \methodof HrcFlattener
  \brief Adds to the hierarchy model informations of the
  given hrc node into the given context

  Does the actual flattening and contextualization
  of expressions and properties.

  \sa hrc_flattener_flatten_recur
*/
void hrc_flattener_populate_model(HrcFlattener_ptr self,
                                  HrcNode_ptr node,
                                  node_ptr context);



#endif /* __NUSMV_CORE_HRC_HRC_FLATTENER_PRIVATE_H__ */
