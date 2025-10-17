/* ---------------------------------------------------------------------------

  This file is part of the ``prob'' package of NuSMV version 2.
  Copyright (C) 2015 by FBK-irst.

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
   \brief Private and protected interface of class 'ProblemDbAccessor'

   This file can be included only by derived and friend classes

   \sa ProblemDbAccessor.h
*/


#ifndef __NUSMV_CORE_PROB_PROBLEM_DB_ACCESSOR_PRIVATE_H__
#define __NUSMV_CORE_PROB_PROBLEM_DB_ACCESSOR_PRIVATE_H__


#include "nusmv/core/prob/ProblemDbAccessor.h"
#include "nusmv/core/utils/EnvObject.h"
#include "nusmv/core/utils/EnvObject_private.h"
#include "nusmv/core/utils/defs.h"


/*!
  \brief ProblemDbAccessor class definition derived from
         class EnvObject



  \sa Base class EnvObject
*/
typedef struct ProblemDbAccessor_TAG
{
  /* this MUST stay on the top */
  INHERITS_FROM(EnvObject);

  /* -------------------------------------------------- */
  /*                  Private members                   */
  /* -------------------------------------------------- */
  ProblemDb_ptr db;  /* the db being accessed by self */
  long long tags;  /* filtering tags */
  /* -------------------------------------------------- */
  /*                  Virtual methods                   */
  /* -------------------------------------------------- */
  VIRTUAL void (*print)(const ProblemDbAccessor_ptr self,
                        OStream_ptr stream,
                        long long tags_mask);
} ProblemDbAccessor;



/* ---------------------------------------------------------------------- */
/* Private methods to be used by derivated and friend classes only         */
/* ---------------------------------------------------------------------- */
/*!
  \methodof ProblemDbAccessor
  \brief The ProblemDbAccessor class private initializer

  The ProblemDbAccessor class private initializer

  \sa ProblemDbAccessor_create
*/
void problem_db_accessor_init(ProblemDbAccessor_ptr self,
                              ProblemDb_ptr db,
                              long long tags);


/*!
  \methodof ProblemDbAccessor
  \brief The ProblemDbAccessor class private deinitializer

  The ProblemDbAccessor class private deinitializer

  \sa ProblemDbAccessor_destroy
*/
void problem_db_accessor_deinit (ProblemDbAccessor_ptr self);

/*!
  \methodof ProblemDbAccessor
  \brief Base-class printer method.

  This is protected, as it may be useful to call it from derived
  classes when specializing print virtual method
*/
void problem_db_accessor_print(const ProblemDbAccessor_ptr self,
                               OStream_ptr stream,
                               long long tags_mask);

#endif /* __NUSMV_CORE_PROB_PROBLEM_DB_ACCESSOR_PRIVATE_H__ */
