/* ---------------------------------------------------------------------------
  This file is part of the ``prop'' package.
  %COPYRIGHT%
-----------------------------------------------------------------------------*/

/*!
  \author Roberto Cavada
  \brief Module header file for utilities of prop shell
*/


#ifndef __NUSMV_SHELL_PROP_PROP_H__
#define __NUSMV_SHELL_PROP_PROP_H__

#include "nusmv/core/prob/prop/PropDbAccessor.h"

/*---------------------------------------------------------------------------*/
/* Constant declarations                                                     */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Type declarations                                                         */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Structure declarations                                                    */
/*---------------------------------------------------------------------------*/

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

  \brief Checks given property index to be valid. Reports errors if
  not valid.

  Returns 1 if index is invalid, and 0 if ok
*/
int PropShell_check_prop_index(const PropDbAccessor_ptr pdba, int idx);


/*!
  \brief returns the index of a property, given its index as string.

  Reports errors if the given index is invalid, or it does not
  corresponds to a property in the problem database, and returns -1.
*/
int PropShell_get_prop_index_from_string(const PropDbAccessor_ptr pda,
                                         const char* idx);

#endif /* __NUSMV_SHELL_PROP_PROP_H__ */
