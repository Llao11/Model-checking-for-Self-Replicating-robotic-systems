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
   \brief Public interface of class 'ProblemDb'

   \sa ProblemDb.c
*/


#ifndef __NUSMV_CORE_PROB_PROBLEM_DB_H__
#define __NUSMV_CORE_PROB_PROBLEM_DB_H__

#include "nusmv/core/prob/Problem.h"

#include "nusmv/core/cinit/NuSMVEnv.h"
#include "nusmv/core/utils/Vector.h"


/*---------------------------------------------------------------------------*/
/* Constant declarations                                                     */
/*---------------------------------------------------------------------------*/

/*!
  \brief use this tag to identify no tags
*/
#define PROBLEM_DB_NO_TAGS  \
   ((long long) 0)


/*!
  \brief use this tag to identify all tags
*/
#define PROBLEM_DB_ALL_TAGS  \
  (~((long long) 0))


/*---------------------------------------------------------------------------*/
/* Structures declarations                                                   */
/*---------------------------------------------------------------------------*/

/*!
  \struct ProblemDb
  \brief Definition of the public accessor for class ProblemDb
*/
typedef struct ProblemDb_TAG*  ProblemDb_ptr;


/*!
  \brief To cast and check instances of class ProblemDb

  These macros must be used respectively to cast and to check
  instances of class ProblemDb

*/
#define PROBLEM_DB(self) \
         ((ProblemDb_ptr) self)

#define PROBLEM_DB_CHECK_INSTANCE(self) \
         (nusmv_assert(PROBLEM_DB(self) != PROBLEM_DB(NULL)))


/*!
  \struct ProblemDbIter
  \brief This is the structure to be used when iterating through the
  Problems in the DB
*/
struct ProblemDbIter {
  int idx;
  long long tags_mask;
};


/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \methodof ProblemDb
  \brief The ProblemDb class constructor

  The ProblemDb class constructor

  \sa ProblemDb_destroy
*/
ProblemDb_ptr ProblemDb_create(NuSMVEnv_ptr env);

/*!
  \methodof ProblemDb
  \brief The ProblemDb class destructor

  The ProblemDb class destructor

  \sa ProblemDb_create
*/
void ProblemDb_destroy (ProblemDb_ptr self);

/*!
  \methodof ProblemDb

  \brief Returns the size of the DB, i.e. the number of stored Problem
  instances
*/
size_t ProblemDb_get_size(const ProblemDb_ptr self);

/*!
  \methodof ProblemDb

  \brief Returns the number or effectively stored Problems which have
  tags within given mask. Not-tagged problems are also counted.
*/
size_t ProblemDb_count_problems(const ProblemDb_ptr self,
                                const long long tags_mask);

/*!
  \methodof ProblemDb

  \brief Adds an instance of a Problem.

  A note about ownership: a Problem's instance can be added to many
  ProblemDb instances, and when the last owning ProblemDb instance
  gets destroyed, also the owned Problem will be destroyed.
  Returns the index of the added problem.
*/
int ProblemDb_add_problem(ProblemDb_ptr self, Problem_ptr problem);


/*!
  \methodof ProblemDb

  \brief Remove and releases an instance of a Problem.

  This may destroy the given problem, if self is the last owner.
  Returns the index of the removed problem, or -1 if not found.

  \sa ProblemDb_remove_problems
*/
int ProblemDb_remove_problem(ProblemDb_ptr self, Problem_ptr problem);

/*!
  \methodof ProblemDb

  \brief Empties the DB of Problems, all Problems associated with
  given tags.

  To remove all problems, use PROBLEM_DB_ALL_TAGS.

  Notice that remaining Problem will keep their indices, i.e. the
  database will not be compacted after problems removal.

  Returns the number of removed problems.

  \sa ProblemDb_remove_problem
*/
size_t ProblemDb_remove_problems(ProblemDb_ptr self,
                                 const long long tags_mask);

/*!
  \methodof ProblemDb

  \brief Searches for given problem (comparing the pointers).

  Returns the index (>=0) if found, or -1 if not found.
*/
int ProblemDb_find_problem(const ProblemDb_ptr self,
                           const Problem_ptr problem);


/*!
  \methodof ProblemDb

  \brief Returns the last entered problem in the DB
  Returned instance belongs to self, do NOT destroy it.
  NULL is returned if the DB is empty.
*/
Problem_ptr ProblemDb_get_last_problem(const ProblemDb_ptr self);

/*!
  \methodof ProblemDb
  \brief Returns the Problem at given index

  Returns the Problem instance whose index is provided in
  input.
  Returns NULL if given index corresponds to a problem which has been
  removed.
  Raises an exception if given problem index does not exists.
  Returned instance belongs to self, do NOT destroy it
*/
Problem_ptr ProblemDb_get_problem_at(const ProblemDb_ptr self,
                                     int idx);

/*!
  \methodof ProblemDb
  \brief Produces a Vector of Problem instances from a delimited
  string containing problem indices

  Indices are names separated by ':' or ','
  A range can be specified with 'A-B' where B >= A.
  This can be handy in commands.

  tags_mask can also be specified, to get only Problems whose tags are
  contained in given mask (use PROBLEM_DB_ALL_TAGS for including all
  possible tags, those with no tags as well).

  In case of error in input, an exception is raised.

  Returned Vector must be disposed by the caller, NOT its content.
*/
Vector_ptr ProblemDb_get_problems_at_indices(const ProblemDb_ptr self,
                                             const char* indices,
                                             const long long tags_mask);

/*!
  \methodof ProblemDb
  \brief Returns true iff given index points within the database
*/
boolean ProblemDb_is_index_valid(const ProblemDb_ptr self, int idx);

/*!
  \methodof ProblemDb

  \brief Returns the tags information attached to a Problem instance

  Gets a tag or a tags-combination previously attached to the given
  problem. If no association is found, 0 is returned (no tags).
*/
long long ProblemDb_get_problem_tags(const ProblemDb_ptr self,
                                     const Problem_ptr problem);

/*!
  \methodof ProblemDb

  \brief tags a Problem instance

  Sets a tag or a tags-combination attaching it to the given problem.
  The problem itself will be not changed, tagging information is kept
  in self. When called on the same problem, associated tags will be
  overwritten by the last call.
*/
void ProblemDb_set_problem_tags(ProblemDb_ptr self,
                                const Problem_ptr problem,
                                const long long tags);

/*!
  \methodof ProblemDb

  \brief Adds tags to a Problem instance

  Adds a tag or a tags-combination to the given problem.
  The problem itself will be not changed, tagging information is kept
  in self.
*/
void ProblemDb_add_problem_tags(ProblemDb_ptr self,
                                const Problem_ptr problem,
                                const long long tags);

/*!
  \methodof ProblemDb

  \brief Removes given tags from a Problem instance

  Removes a tag or a tags-combination from the given problem.
  The problem itself will be not changed, tagging information is kept
  in self.
*/
void ProblemDb_remove_problem_tags(ProblemDb_ptr self,
                                   const Problem_ptr problem,
                                   const long long tags);

/*!
  \methodof ProblemDb

  \brief Creates a new valid tag, which can be used in masks.

  The returned tag is guaranteed to be unique within self. Notice that
  once this method gets called, the returned tag is taken, and cannot
  be freed, so call this method only when you are using it with
  ProblemDb_set_tags.

  If you need to create a new tag and give it a name, you can use
  directly ProblemDb_get_tags instead of the sequence
  ProblemDb_new_tag + ProblemDb_set_tags.
*/
long long ProblemDb_new_tag(ProblemDb_ptr self);

/*!
  \methodof ProblemDb
  \brief Returns a tag or tag combination from the tag(s) name.

  This method searches in previously set tag or tag-combinations, from
  the name. If the tag is not found, a new tag will be created and
  associated to the given name.

  This method can be used to create new tags, instead of using
  ProblemDb_new_tag + ProblemDb_set_tags.
*/
long long ProblemDb_get_tags(const ProblemDb_ptr self,
                             const char* name);

/*!
  \methodof ProblemDb

  \brief Returns true iff given tag name has
  been registered within self.

  \sa ProblemDb_get_tags
*/
boolean ProblemDb_tag_name_exists(const ProblemDb_ptr self,
                                  const char* name);

/*!
  \methodof ProblemDb

  \brief Associates given name to the tag or tag-combination.

  If the name was already used, the previously associated value gets
  overwritten before being returned.

  The associated value can be later retrieved with ProblemDb_get_tags.
  Returns the previously associated tags, 0 if not associated.
*/
long long ProblemDb_set_tags(const ProblemDb_ptr self,
                             const char* name,
                             const long long tags);

/*!

  \methodof ProblemDb

  \brief Returns the string name previously associated of given tag or
  tag-combination.

  Do NOT free returned string. Returns NULL if tags not found.
*/
const char* ProblemDb_tags_to_name(ProblemDb_ptr self,
                                   long long tags);

/*!
  \methodof ProblemDb
  \brief Inizializes the iteration with given tags mask.

  Use this method to begin an iteration among problems, limiting the
  iteration among problems tagged with tags in the given mask.

  \sa ProblemDb_iter_get_problem
  \sa ProblemDb_iter_next
  \sa ProblemDb_iter_is_end
*/
void ProblemDb_iter_begin(const ProblemDb_ptr self,
                          const long long tags_mask,
                          /* output: */
                          struct ProblemDbIter* iter);

/*!
  \methodof ProblemDb

  \brief Inizializes the iteration with given tags mask, starting the
  iteration at given index

  Use this method to begin an iteration among problems, limiting the
  iteration among problems tagged with tags in the given mask.

  \sa ProblemDb_iter_get_problem
  \sa ProblemDb_iter_next
  \sa ProblemDb_iter_is_end
*/
void ProblemDb_iter_begin_at(const ProblemDb_ptr self,
                             const int start_idx,
                             const long long tags_mask,
                             /* output: */
                             struct ProblemDbIter* iter);

/*!
  \methodof ProblemDb
  \brief Returns the problem pointed by given iterator.

  Returned Probloem instance belongs to self, do not destroy it.

  \sa ProblemDb_iter_begin
  \sa ProblemDb_iter_next
  \sa ProblemDb_iter_is_end
*/
Problem_ptr ProblemDb_iter_get_problem(const ProblemDb_ptr self,
                                       const struct ProblemDbIter* iter);

/*!
  \methodof ProblemDb
  \brief Make the oteration advance by one position, according to the
  tags involved in the iteration.

  \sa ProblemDb_iter_is_end
  \sa ProblemDb_iter_get_problem
  \se iterator gets changed.
*/
void ProblemDb_iter_next(const ProblemDb_ptr self,
                         /* input/output: */
                         struct ProblemDbIter* iter);

/*!
  \methodof ProblemDb
  \brief Returns true iff iteration is over.

  \sa ProblemDb_iter_next
  \sa ProblemDb_iter_get_problem
*/
boolean ProblemDb_iter_is_end(const ProblemDb_ptr self,
                              const struct ProblemDbIter* iter);

/*!
  \brief Use this macro to iterate among tagged problems
  \sa ProblemDbIter
  \sa ProblemDb_iter_begin
  \sa ProblemDb_iter_next
  \sa ProblemDb_iter_is_end
*/
#define PROBLEM_DB_ITER_FOREACH(self, tags_mask, iter)        \
  for (ProblemDb_iter_begin(self, tags_mask, &iter);          \
       !ProblemDb_iter_is_end(self, &iter);                   \
       ProblemDb_iter_next(self, &iter))



#endif /* __NUSMV_CORE_PROB_PROBLEM_DB_H__ */
