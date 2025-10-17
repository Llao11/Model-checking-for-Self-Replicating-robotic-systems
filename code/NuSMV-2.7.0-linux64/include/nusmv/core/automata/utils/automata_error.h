/* ---------------------------------------------------------------------------


  This file is part of the ``utils'' package.
  %COPYRIGHT%

-----------------------------------------------------------------------------*/

/*!
  \author Sergio Mover
  \brief header of the automata_error.c file

  \todo: Missing description

*/


#ifndef __NUXMV_CORE_AUTOMATA_UTILS_AUTOMATA_ERROR_H__
#define __NUXMV_CORE_AUTOMATA_UTILS_AUTOMATA_ERROR_H__

#include "nusmv/core/automata/automata.h"
#include "nusmv/core/parser/psl/pslNode.h"
#include "nusmv/core/utils/error.h"

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

/*!
  \brief This macro is a string represeting the error unknown
  label type

  \todo Missing description
*/
#define AUTOMATA_ERROR_UNKOWN_LABEL_TYPE_MSG "Unknown type of label"

/*!
  \brief This macro is a string represeting the error unknown
  algorithm type

  \todo Missing description
*/
#define AUTOMATA_ERROR_UNKOWN_ALGORITHM_TYPE_MSG "Unknown type of algorithm"

/*!
  \brief This macro is a string represeting the error unknown
  reduction algorithm type

  \todo Missing description
*/
#define AUTOMATA_ERROR_UNKOWN_REDALGO_TYPE_MSG "Unknown type of reduction algorithm"

/*!
  \brief This macro is a string represeting the error unknown
  operator in a SERE expression

  \todo Missing description
*/
#define AUTOMATA_ERROR_UNKOWN_SERE_OP "Unknown operator in sere"

/*!
  \brief This macro is the error string show when different
  types of labels are used in the same operation.

  \todo Missing description
*/
#define AUTOMATA_ERROR_WRONG_LABEL_TYPE_MSG     \
  "Different label types used in an operation"

/*!
  \brief This macro is a string represeting that the output file pointer
  is NULL when trying to print automata labels to it.
*/
#define AUTOMATA_ERROR_NULL_OUTPUT_FILE_MSG "File point is NULL"


/**AutomaticStart*************************************************************/

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/*!
  \brief Error function called when the label type is not found

  

  \se Cause nusmv to exit
*/
void 
automata_error_unknown_label_type(ErrorMgr_ptr errmgr,
                                  Automaton_Label_Type label_type);

/*!
  \brief Error function called when in an operations
  different labels are used.

  

  \se Cause nusmv to exit
*/
void 
automata_error_wrong_label_type(ErrorMgr_ptr errmgr,
                                Automaton_Label_Type used_label_type,
                                Automaton_Label_Type new_label_type);

/*!
  \brief Error function called when an algorithm type is
  not found

  

  \se Cause nusmv to exit
*/
void 
automata_error_unknown_algorithm_type(ErrorMgr_ptr errmgr,
                                      Automaton_Algorithm_Type algorithm_type);

/*!
  \brief Error function called when the reduction algorithm type is
  not found

  

  \se Cause nusmv to exit
*/
void 
automata_error_unknown_reduction_algo_type(ErrorMgr_ptr errmgr,
                                           Automaton_ReductionAlgorithm_Type type);

/*!
  \brief Error function called when a psl node of a sere
  is not recognized.

  

  \se Cause nusmv to exit
*/
void 
automata_error_unknown_sere_operator(ErrorMgr_ptr errmgr,
                                     PslOp psl_op);

/*!
  \brief Error function called when the output file pointer is NULL

  \se Cause nusmv to exit
*/
void automata_error_null_output_file (ErrorMgr_ptr errmgr);

/**AutomaticEnd***************************************************************/

#endif /* __NUXMV_CORE_AUTOMATA_UTILS_AUTOMATA_ERROR_H__ */
