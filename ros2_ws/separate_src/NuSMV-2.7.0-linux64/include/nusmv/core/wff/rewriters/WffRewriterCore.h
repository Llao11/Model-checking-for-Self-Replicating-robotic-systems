/* ---------------------------------------------------------------------------


  This file is part of the ``wff.rewriters''
  package of NuSMV version 2. Copyright (C) 2006 by FBK-irst.

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
  \brief Public interface of class 'WffRewriterCore'

  \todo: Missing description

*/



#ifndef NUSMV_CORE_WFF_REWRITERS_WFF_REWRITER_CORE_H__
#define NUSMV_CORE_WFF_REWRITERS_WFF_REWRITER_CORE_H__

#include "nusmv/core/utils/object.h"
#include "nusmv/core/cinit/NuSMVEnv.h"


/*---------------------------------------------------------------------------*/
/* Constant declarations                                                     */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Type declarations                                                         */
/*---------------------------------------------------------------------------*/

/*!
  \struct WffRewriterCore
  \brief Definition of the public accessor for class WffRewriterCore

*/
typedef struct WffRewriterCore_TAG*  WffRewriterCore_ptr;


/*---------------------------------------------------------------------------*/
/* Structure declarations                                                    */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Variable declarations                                                     */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Macro declarations                                                        */
/*---------------------------------------------------------------------------*/

/*!
  \brief To cast and check instances of class WffRewriterCore

  These macros must be used respectively to cast and to check
  instances of class WffRewriterCore
*/
#define WFF_REWRITER_CORE(self) \
  ((WffRewriterCore_ptr) self)

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define WFF_REWRITER_CORE_CHECK_INSTANCE(self) \
  (nusmv_assert(WFF_REWRITER_CORE(self) != WFF_REWRITER_CORE(NULL)))



/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \methodof WffRewriterCore
  \brief returns a newly allocated instance of WffRewriterCore.

  The WffRewriterCore public constructor.

  Signature must be compatible with typeWffRewriterCreate.

  \sa typeWffRewriterCreate
*/
WffRewriterCore_ptr WffRewriterCore_create(const NuSMVEnv_ptr env);

/*!
  \methodof WffRewriterCore
  \brief The WffRewriterCore class destructor

  The WffRewriterCore class destructor

  \sa WffRewriterCore_create
*/
VIRTUAL void WffRewriterCore_destroy(WffRewriterCore_ptr self);


/**AutomaticEnd***************************************************************/


#endif /* NUSMV_CORE_WFF_REWRITERS_WFF_REWRITER_CORE_H__ */
