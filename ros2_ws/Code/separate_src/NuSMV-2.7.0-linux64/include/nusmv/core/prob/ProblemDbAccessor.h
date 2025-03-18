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
   \brief Public interface of class 'ProblemDbAccessor'

   Class ProblemDbAccessor is the proxy to access to the underlaying
   problem database. User never access the DB directly, it does it
   through an accessor. Each DB can be used by one or more accessors,
   which may be specialized to handle particular kind of problems. For
   example, in NuSMV the Properties are hold in the ProblemDb which is
   general wrt the kind of problems it contains. However, through the
   ProbDbAccessor, Prop instances are accessed and handled as Prop
   instances, and not only as general Problem instances.

   \sa ProblemDbAccessor.c
*/


#ifndef __NUSMV_CORE_PROB_PROBLEM_DB_ACCESSOR_H__
#define __NUSMV_CORE_PROB_PROBLEM_DB_ACCESSOR_H__


#include "nusmv/core/prob/ProblemDb.h"
#include "nusmv/core/utils/OStream.h"
#include "nusmv/core/utils/defs.h"
#include "nusmv/core/utils/Vector.h"


/*!
  \struct ProblemDbAccessor
  \brief Definition of the public accessor for class ProblemDbAccessor
*/
typedef struct ProblemDbAccessor_TAG*  ProblemDbAccessor_ptr;


/*!
  \brief To cast and check instances of class ProblemDbAccessor

  These macros must be used respectively to cast and to check
  instances of class ProblemDbAccessor

*/
#define PROBLEM_DB_ACCESSOR(self) \
         ((ProblemDbAccessor_ptr) self)

#define PROBLEM_DB_ACCESSOR_CHECK_INSTANCE(self) \
         (nusmv_assert(PROBLEM_DB_ACCESSOR(self) != PROBLEM_DB_ACCESSOR(NULL)))



/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \methodof ProblemDbAccessor
  \brief The ProblemDbAccessor class constructor

  Self uses the given db. The caller is still responsible for the db
  destruction, but this has happen after self has been destroyed.

  tags is the tag which make the filtering access to the DB.

  \sa ProblemDbAccessor_destroy
*/
ProblemDbAccessor_ptr ProblemDbAccessor_create(ProblemDb_ptr db,
                                               const long long tags);


/*!
  \methodof ProblemDbAccessor
  \brief The ProblemDbAccessor class destructor

  The ProblemDbAccessor class destructor

  \sa ProblemDbAccessor_create
*/
void ProblemDbAccessor_destroy (ProblemDbAccessor_ptr self);

/*!
  \methodof ProblemDbAccessor
  \brief Returns the associated ProblemDb instance
*/
ProblemDb_ptr ProblemDbAccessor_get_db(const ProblemDbAccessor_ptr self);

/*!
  \methodof ProblemDbAccessor

  \brief Returns the tags mask associated with self at construction
  time
*/
long long ProblemDbAccessor_get_tags_mask(const ProblemDbAccessor_ptr self);

/*!
  \methodof ProblemDbAccessor

  \brief Adds a problem to the underlaying db.
  Returns the index of the added problem
*/
int ProblemDbAccessor_add(ProblemDbAccessor_ptr self, Problem_ptr prob);

/*!
  \methodof ProblemDbAccessor

  \brief Remove from the DB all problems without tags or with tags
  compatible with self.

  Returns the number of removed problems.
*/
size_t ProblemDbAccessor_clean(ProblemDbAccessor_ptr self);

/*!
  \methodof ProblemDbAccessor
  \brief Returns true iff given index points a problem which is
  compatible with the tags mask in self.
*/
boolean ProblemDbAccessor_is_index_valid(const ProblemDbAccessor_ptr self,
                                         int idx);

/*!
  \methodof ProblemDbAccessor
  \brief Returns true iff given iterator points a problem which is
  compatible with the tags mask in self.

  \sa ProblemDbAccessor_is_index_valid
*/
boolean ProblemDbAccessor_is_iter_valid(const ProblemDbAccessor_ptr self,
                                        const struct ProblemDbIter* iter);

/*!
  \methodof ProblemDbAccessor
  \brief Returns lowest and highest
  indices in the db containg compatible problems

  Note: the interval may still contain invalid indices.
*/
void ProblemDbAccessor_get_indices_range(const ProblemDbAccessor_ptr self,
                                         int* low, int* high);

/*!
  \methodof ProblemDbAccessor

  \brief returns the number of problems in the db, matching the tags
  of self.

  This method wraps ProblemDb_count_problems

  \sa ProblemDb_count_problems
*/
size_t ProblemDbAccessor_count_problems(const ProblemDbAccessor_ptr self);

/*!
  \methodof ProblemDbAccessor

  \brief Returns a list of all indices of problems matching the
  internal tags.

  Returned vector must be disposed by the caller
*/
IntVector_ptr ProblemDbAccessor_get_problem_indices(
    const ProblemDbAccessor_ptr self);

/*!
  \methodof ProblemDbAccessor

  \brief returns the Problem instance found at given index

  This is like ProblemDb_get_problem_at, but returning NULL if given
  index does not contain a Problem tagged with compatible tag.
*/
Problem_ptr ProblemDbAccessor_get_problem_at_index(
    const ProblemDbAccessor_ptr self, int idx);

/*!
  \methodof ProblemDbAccessor

  \brief returns the Problem instance found at given iterator.

  \sa ProblemDbAccessor_get_problem_at_index
*/
Problem_ptr ProblemDbAccessor_get_problem_at_iter(
    const ProblemDbAccessor_ptr self, const struct ProblemDbIter* iter);


/*!
  \methodof ProblemDbAccessor
  \brief Returns the first entered problem in the DB

  Returns NULL if not found.
  If index is not NULL, it will contain the index of the returned
  problem (-1 if not found).

  \sa ProblemDbAccessor_get_last_problem
*/
Problem_ptr ProblemDbAccessor_get_first_problem(
    const ProblemDbAccessor_ptr self, int* index);

/*!
  \methodof ProblemDbAccessor
  \brief Returns the last entered problem in the DB

  Returns NULL if not found.
  If index is not NULL, it will contain the index of the returned
  problem (-1 if not found)

  \sa ProblemDbAccessor_get_first_problem
*/
Problem_ptr ProblemDbAccessor_get_last_problem(
    const ProblemDbAccessor_ptr self, int* index);

/*!
  \brief Prints to the given stream, all problems matching both given
  tags mask and internal tags mask provided at construction time.

  This method is virtual, currently ProblemDbAccessor class prints
  each matching problems in separate lines.
*/
VIRTUAL void ProblemDbAccessor_print(const ProblemDbAccessor_ptr self,
                                     OStream_ptr stream,
                                     long long tags_mask);
/*!
  \brief Use to iterate among the db's problems

  Iteration is limited to problems in self's tags or no tags */
#define PROBLEM_DB_ACCESSOR_FOREACH(self, iter)                         \
  for (ProblemDb_iter_begin(                                            \
           ProblemDbAccessor_get_db(PROBLEM_DB_ACCESSOR(self)),         \
           ProblemDbAccessor_get_tags_mask(PROBLEM_DB_ACCESSOR(self)),  \
           &iter);                                                      \
       !ProblemDb_iter_is_end(                                          \
           ProblemDbAccessor_get_db(PROBLEM_DB_ACCESSOR(self)), &iter); \
       ProblemDb_iter_next(                                             \
           ProblemDbAccessor_get_db(PROBLEM_DB_ACCESSOR(self)), &iter))


#endif /* __NUSMV_CORE_PROB_PROBLEM_DB_ACCESSOR_H__ */
