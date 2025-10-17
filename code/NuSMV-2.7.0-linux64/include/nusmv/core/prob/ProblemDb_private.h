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
   \brief Private and protected interface of class 'ProblemDb'

   This file can be included only by derived and friend classes

   \sa ProblemDb.h
*/


#ifndef __NUSMV_CORE_PROB_PROBLEM_DB_PRIVATE_H__
#define __NUSMV_CORE_PROB_PROBLEM_DB_PRIVATE_H__


#include "nusmv/core/prob/ProblemDb.h"

#include "nusmv/core/utils/EnvObject.h"
#include "nusmv/core/utils/EnvObject_private.h"
#include "nusmv/core/utils/assoc.h"
#include "nusmv/core/utils/UStringMgr.h"
#include "nusmv/core/utils/Vector.h"


/*---------------------------------------------------------------------------*/
/* Constant declarations                                                     */
/*---------------------------------------------------------------------------*/

/*! name of the 0 tag */
#define  NO_TAG_NAME "no-tag"

/*! name of the combination of all tags */
#define  ALL_TAGS_NAME "all-tags"


/*---------------------------------------------------------------------------*/
/* Structure declarations                                                    */
/*---------------------------------------------------------------------------*/

/*!
  \brief ProblemDb class definition derived from
         class EnvObject

  This class represents a container of Problem instances.

  TAGS
  ----

  Each contained Problem instance can be associated with one or more
  tags. Tags numeric values, each ProblemDb instance can contain up to
  64 different tags, and can be combined into bit-masks. Each tag or
  tags combination is associated to string names within each
  ProblemDb, and it is up to the user to define desired tags and tags
  combination with corresponding names.

  \sa Base class EnvObject
*/
typedef struct ProblemDb_TAG
{
  /* this MUST stay on the top */
  INHERITS_FROM(EnvObject);

  /* -------------------------------------------------- */
  /*                  Private members                   */
  /* -------------------------------------------------- */
  Vector_ptr problems;  /* the list of stored problems */

  /* keeps map of {Problem: index+1 in tags vector} */
  hash_ptr prob2tagidx;

  UStringMgr_ptr usmgr;  /* used for tag names */
  hash_ptr tagname2tagidx;  /* string_ptr -> tag_idx */
  Vector_ptr tagnames;  /* tag_idx -> string_ptr */
  LLVector_ptr tags;  /* idx2tag vector */
  int next_avail_tag;


  /* -------------------------------------------------- */
  /*                  Virtual methods                   */
  /* -------------------------------------------------- */

} ProblemDb;


/* ---------------------------------------------------------------------- */
/* Private methods to be used by derivated and friend classes only        */
/* ---------------------------------------------------------------------- */
/*!
  \methodof ProblemDb
  \brief The ProblemDb class private initializer

  The ProblemDb class private initializer

  \sa ProblemDb_create
*/
void problem_db_init (ProblemDb_ptr self, NuSMVEnv_ptr env);


/*!
  \methodof ProblemDb
  \brief The ProblemDb class private deinitializer

  The ProblemDb class private deinitializer

  \sa ProblemDb_destroy
*/
void problem_db_deinit (ProblemDb_ptr self);



#endif /* __NUSMV_CORE_PROB_PROBLEM_DB_PRIVATE_H__ */
