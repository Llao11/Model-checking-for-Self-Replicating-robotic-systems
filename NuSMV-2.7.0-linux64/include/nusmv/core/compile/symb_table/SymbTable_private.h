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
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.

   For more information on NuSMV see <http://nusmv.fbk.eu>
   or email to <nusmv-users@fbk.eu>.
   Please report bugs to <nusmv-users@fbk.eu>.

   To contact the NuSMV development board, email to <nusmv@fbk.eu>.

   --------------------------------------------------------------------------*/


/*!
  \author Enrico Magnago
  \brief Private and protected interface of class 'SymbTable'

  This file can be included only by derived and friend classes

*/

#ifndef NUSMV_CORE_COMPILE_SYMB_TABLE_SYMB_TABLE_PRIVATE_H__
#define NUSMV_CORE_COMPILE_SYMB_TABLE_SYMB_TABLE_PRIVATE_H__

#include "nusmv/core/utils/EnvObject_private.h"

#include "nusmv/core/opt/OptsHandler.h"
#include "nusmv/core/compile/symb_table/SymbTable.h"
#include "nusmv/core/compile/symb_table/SymbLayer.h"
#include "nusmv/core/compile/type_checking/TypeChecker.h"
#include "nusmv/core/utils/StreamMgr.h"

/*!
  \brief SymbTable class definition derived from
               class EnvObject

  \sa Base class EnvObject
*/
typedef struct SymbTable_TAG
{
  INHERITS_FROM(EnvObject);

  OptsHandler_ptr options;
  StreamMgr_ptr streams;
  NodeMgr_ptr nodes;
  MasterPrinter_ptr printer;
  UStringMgr_ptr strings;

  SymbCache_ptr cache;
  hash_ptr categories;

  int temp_layer_name_suffix; /* used to create temporary names for layers */

  NodeList_ptr layers; /* the list of owned layers */

  hash_ptr class_layers; /* the list of layers organized by class */
  NodeList_ptr class_names; /* the list of class names */
  const char* default_class_name; /* name of the default class name */

  hash_ptr name2layer; /* to associate layers and names */

  /* A counter for declaration of determinization variables */
  size_t det_counter;

  TypeChecker_ptr tc; /* this is the type checker owned by the ST */

  ResolveSymbol_ptr resolver;

  hash_ptr handled_structures;

  Set_t non_continuous_vars;

} SymbTable;


/* ---------------------------------------------------------------------- */
/* Private methods to be used by derivated and friend classes only         */
/* ---------------------------------------------------------------------- */

/*!
  \methodof SymbTable
  \brief The SymbTable class private initializer

  The SymbTable class private initializer

  \sa SymbTable_create, symb_table_deinit
*/
void symb_table_init(SymbTable_ptr self, NuSMVEnv_ptr env);

/*!
  \methodof SymbTable
  \brief The SymbTable class private deinitializer

  The SymbTable class private deinitializer

  \sa SymbTable_destroy, symb_table_init
*/
void symb_table_deinit(SymbTable_ptr self);


#endif /* NUSMV_CORE_COMPILE_SYMB_TABLE_SYMB_TABLE_PRIVATE_H__ */
