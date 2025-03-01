/* ---------------------------------------------------------------------------


  This file is part of the ``hrc'' package of NuSMV version 2.
  Copyright (C) 2009 by FBK.

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
  \author Sergio Mover, Enrico Magnago
  \brief Private and protected interface of 'hrc' module

*/

#ifndef NUSMV_CORE_HRC_HRC_PRIVATE_H__
#define NUSMV_CORE_HRC_HRC_PRIVATE_H__

#include "nusmv/core/hrc/hrc.h"

/*---------------------------------------------------------------------------*/
/* Constant declarations                                                     */
/*---------------------------------------------------------------------------*/

#define ENV_HRC_DUMPER_FACTORIES "ENV_HRC_DUMPER_FACTORIES"

/*---------------------------------------------------------------------------*/
/* Type declarations                                                         */
/*---------------------------------------------------------------------------*/

/*!
\brief generic signature of HrcDumper constructor.

*/
typedef HrcDumper_ptr (*HrcDumperFactory)(const NuSMVEnv_ptr env, FILE* fout);

typedef struct HrcDumperFactories_TAG*  HrcDumperFactories_ptr;

/*!
  \brief To cast and check instances of class HrcDumperFactories

  These macros must be used respectively to cast and to check
  instances of class HrcDumperFactories
*/
#define HRC_DUMPER_FACTORIES(self) \
  ((HrcDumperFactories_ptr) self)

#define HRC_DUMPER_FACTORIES_CHECK_INSTANCE(self) \
  (nusmv_assert(HRC_DUMPER_FACTORIES(self) != HRC_DUMPER_FACTORIES(NULL)))

/*---------------------------------------------------------------------------*/
/* Structure declarations                                                    */
/*---------------------------------------------------------------------------*/

typedef struct HrcDumperFactories_TAG
{
  HrcDumperFactory smv;
  HrcDumperFactory xml;
  HrcDumperFactory debug;
} HrcDumperFactories;

/*---------------------------------------------------------------------------*/
/* Variable declarations                                                     */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Macro declarations                                                        */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \methodof HrcDumperFactories
  \brief The HrcDumperFactories class constructor

  \sa HrcDumperFactories_destroy
*/
HrcDumperFactories_ptr HrcDumperFactories_create();

/*!
  \brief set factory for the given HrcDumper type.
*/
void HrcDumperFactories_set_factory(const HrcDumperFactories_ptr self,
                                    HrcDumperFactory factory,
                                    const HrcDumpFormat type);
/*!
  \brief return factory method for the given HrcDumper type.

  returns NULL if no factory has been registered for the given type.
*/
HrcDumperFactory HrcDumperFactories_get_factory(const HrcDumperFactories_ptr self,
                                                const HrcDumpFormat type);

/*!
  \methodof HrcDumperFactories
  \brief The HrcDumperFactories class destructor

  The HrcDumperFactories class destructor

  \sa HrcDumperFactories_create
*/
void HrcDumperFactories_destroy(HrcDumperFactories_ptr self);



#endif /* NUSMV_CORE_HRC_HRC_PRIVATE_H__ */
