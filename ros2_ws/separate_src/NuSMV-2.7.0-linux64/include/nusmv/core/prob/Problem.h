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
   \brief Public interface of class 'Problem'

   \sa Problem.c
*/


#ifndef __NUSMV_CORE_PROB_PROBLEM_H__
#define __NUSMV_CORE_PROB_PROBLEM_H__


#include "nusmv/core/utils/defs.h"
#include "nusmv/core/cinit/NuSMVEnv.h"
#include "nusmv/core/utils/OStream.h"
#include "nusmv/core/utils/object.h"


/*!
  \struct Problem
  \brief Definition of the public accessor for class Problem
*/
typedef struct Problem_TAG*  Problem_ptr;


/*!
  \brief To cast and check instances of class Problem

  These macros must be used respectively to cast and to check
  instances of class Problem

*/
#define PROBLEM(self) \
         ((Problem_ptr) self)

#define PROBLEM_CHECK_INSTANCE(self) \
         (nusmv_assert(PROBLEM(self) != PROBLEM(NULL)))




/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \methodof Problem
  \brief The Problem class constructor

  The Problem class constructor

  \sa Problem_destroy
*/
Problem_ptr Problem_create(const NuSMVEnv_ptr env);


/*!
  \methodof Problem
  \brief The Problem class destructor

  The Problem class destructor

  \sa Problem_create
*/
void Problem_destroy(Problem_ptr self);

/*!
  \methodof Problem
  \brief Prints given problem.

  This method is virtual, to be implemented by derived classes
*/
VIRTUAL void Problem_print(const Problem_ptr self, OStream_ptr stream);

#endif /* __NUSMV_CORE_PROB_PROBLEM_H__ */
