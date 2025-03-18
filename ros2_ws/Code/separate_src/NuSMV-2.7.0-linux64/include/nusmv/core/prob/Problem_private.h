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
   \brief Private and protected interface of class 'Problem'

   This file can be included only by derived and friend classes

   \sa Problem.h
*/


#ifndef __NUSMV_CORE_PROB_PROBLEM_PRIVATE_H__
#define __NUSMV_CORE_PROB_PROBLEM_PRIVATE_H__


#include "nusmv/core/prob/Problem.h"

#include "nusmv/core/utils/EnvObject.h"
#include "nusmv/core/utils/EnvObject_private.h"

/*!
  \brief Problem class definition derived from
         class Object

  \sa Base class Object
*/
typedef struct Problem_TAG
{
  /* this MUST stay on the top */
  INHERITS_FROM(EnvObject);

  /* -------------------------------------------------- */
  /*                  Private members                   */
  /* -------------------------------------------------- */
  /* this is used to count how many ProblemDb own the instance, to
   * handle deallocation */
  size_t owners;

  /* -------------------------------------------------- */
  /*                  Virtual methods                   */
  /* -------------------------------------------------- */
  VIRTUAL void (*print)(const Problem_ptr self, OStream_ptr stream);

} Problem;



/* ---------------------------------------------------------------------- */
/* Private methods to be used by derivated and friend classes only         */
/* ---------------------------------------------------------------------- */
/*!
  \methodof Problem
  \brief The Problem class private initializer

  The Problem class private initializer

  \sa Problem_create
*/
void problem_init(Problem_ptr self, const NuSMVEnv_ptr env);


/*!
  \methodof Problem
  \brief The Problem class private deinitializer

  The Problem class private deinitializer

  \sa Problem_destroy
*/
void problem_deinit(Problem_ptr self);


/*!
  \methodof Problem
  \brief increments the number of owners
  This is used internally by ProblemDb instances, and the user should
  never call this method
*/
void problem_inc_owners(Problem_ptr self);

/*!
  \methodof Problem
  \brief decrements the number of owners
  This is used internally by ProblemDb instances, and the user should
  never call this method
*/
void problem_dec_owners(Problem_ptr self);

/*!
  \methodof Problem
  \brief Private copy method aux
*/
void problem_copy_aux(const Problem_ptr self,
                      Problem_ptr other);

#endif /* __NUSMV_CORE_PROB_PROBLEM_PRIVATE_H__ */
