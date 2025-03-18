/* ---------------------------------------------------------------------------

  This file is part of the ``prop'' package of NuSMV version 2.
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
  \brief Public interface of class 'PropDbAccessor'

  \todo: Missing description

*/


#ifndef __NUSMV_CORE_PROP_PROP_DB_ACCESSOR_H__
#define __NUSMV_CORE_PROP_PROP_DB_ACCESSOR_H__

#include "nusmv/core/prob/ProblemDbAccessor.h"
#include "nusmv/core/prob/ProblemDb.h"
#include "nusmv/core/prob/prop/Prop.h"

#include "nusmv/core/utils/object.h"
#include "nusmv/core/utils/utils.h"
#include "nusmv/core/utils/list.h"
#include "nusmv/core/utils/ErrorMgr.h"


/*---------------------------------------------------------------------------*/
/* Constant declarations                                                     */
/*---------------------------------------------------------------------------*/

/*!
  \struct PropDbAccessor
  \brief Definition of the public accessor for class PropDbAccessor


*/
typedef struct PropDbAccessor_TAG*  PropDbAccessor_ptr;

/*!
  \brief To cast and check instances of class PropDbAccessor

  These macros must be used respectively to cast and to check
  instances of class PropDbAccessor
*/
#define PROP_DB_ACCESSOR(self) \
         ((PropDbAccessor_ptr) self)

/*!
  \brief \todo Missing synopsis

  \todo Missing description
*/
#define PROP_DB_ACCESSOR_CHECK_INSTANCE(self) \
         (nusmv_assert(PROP_DB_ACCESSOR(self) != PROP_DB_ACCESSOR(NULL)))

/*!
  \brief Name of the tag used in problem database for tagging properties
*/
#define  PROP_DB_ACCESSOR_TAGS_NAME  \
  "_tags_properties"


/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

/* Constructors, Destructors, Copiers and Cleaners ****************************/

/*!
  \methodof PropDbAccessor
  \brief The PropDbAccessor class constructor

  The PropDbAccessor class constructor

  \sa PropDbAccessor_destroy
*/
PropDbAccessor_ptr PropDbAccessor_create(ProblemDb_ptr db);

/*!
  \methodof PropDbAccessor
  \brief The PropDbAccessor class destructor

  The PropDbAccessor class destructor

  \sa PropDbAccessor_create
*/
void PropDbAccessor_destroy(PropDbAccessor_ptr self);

/*!
  \methodof PropDbAccessor
  \brief Return the list of properties of a given type
  Returned list to be disposed by the caller.
*/
lsList PropDbAccessor_get_props_of_type(const PropDbAccessor_ptr self,
                                        const Prop_Type type);

/*!
  \methodof PropDbAccessor
  \brief Return the list of properties of a given type,
                      ordered by COI size

  Returned list must be disposed by the caller.
*/
lsList PropDbAccessor_get_ordered_props_of_type(
    const PropDbAccessor_ptr self,
    const FlatHierarchy_ptr hierarchy,
    const Prop_Type type);

/*!
  \methodof PropDbAccessor
  \brief Get the list of properties ordered by COI size

  Get the list of properties ordered by COI size.

                      List elements are couples made using cons: the
                      car part points to the property, while the cdr
                      part points to the COI. The list and it's
                      elements (cons nodes and COI sets) should be
                      freed by the caller

                      Note: here "cons" could be substituted by Pair
*/
NodeList_ptr
PropDbAccessor_get_ordered_properties(const PropDbAccessor_ptr self,
                                      const FlatHierarchy_ptr hierarchy);

/*!
  \methodof PropDbAccessor
  \brief Get the list of properties, grouped by COI

  Get the list of properties, grouped by COI.
                      A list of couples is returned. The left part of
                      the couple is the COI (represented as a
                      Set_t). The right part of the couple is a Set
                      containing all properties with that COI.  The
                      returned list is ordered by COI size.  The list,
                      all couples and all sets should be freed by the
                      caller

  \sa PropDbAccessor_get_ordered_properties
*/
NodeList_ptr
PropDbAccessor_get_coi_grouped_properties(const PropDbAccessor_ptr self,
                                          const FlatHierarchy_ptr hierarchy);

/*!
  \methodof PropDbAccessor
  \brief Wrapper for PropDbAccessor_get_ordered_props_of_type,
  PropDbAccessor_get_props_of_type

  Call the correct PropDbAccessor_get...props_of_type depending on
  opt_use_coi_size_sorting.
  the list must be freed by the user.
*/
lsList PropDbAccessor_prepare_prop_list(const PropDbAccessor_ptr self,
                                        const Prop_Type type);

/* ---------------------------------------------------------------------------*/
/* Property ------------------------------------------------------------------*/

/*!
  \methodof PropDbAccessor
  \brief Returns the last entered property in the DB

  Returns the last entered property in the DB of
                      properties.
*/
Prop_ptr PropDbAccessor_get_last(const PropDbAccessor_ptr self);

/*!
  \methodof PropDbAccessor
  \brief Returns the property indexed by index

  Returns the property located at given index within the db.
  Returns NULL if index is not found, or if at given index, there is
  not a property.

  \sa PropDbAccessor_get_prop_at_iter
*/
Prop_ptr PropDbAccessor_get_prop_at_index(const PropDbAccessor_ptr self,
                                          int num);

/*!
  \methodof PropDbAccessor
  \brief Returns the property indexed by given iterator

  Returns the property located at given iterator within the db.
  Returns NULL if iterator is not found, or if at given iterator there
  is not a property.

  \sa PropDbAccessor_get_prop_at_index
*/
Prop_ptr PropDbAccessor_get_prop_at_iter(const PropDbAccessor_ptr self,
                                         const struct ProblemDbIter* iter);

/*!
  \methodof PropDbAccessor
  \brief Produces a set of properties from a delimited string
  containing properties indices

  Indices are names separated by ':' or ','
  A range can be specified with 'A-B' where B >= A.
  This can be handy in commands.

  In case of error in input, an exception is raised.

  Returned set must be disposed by the caller
*/
Set_t PropDbAccessor_get_props_at_indices(const PropDbAccessor_ptr self,
                                          const char* indices);

/* ---------------------------------------------------------------------------*/
/* Index ---------------------------------------------------------------------*/

/*!
  \methodof PropDbAccessor
  \brief Returns the property with the given name

  Returns the property with the given name, rapresented
  as flattened nodes hierarchy, -1 if not found.
*/
int PropDbAccessor_get_prop_name_index(const PropDbAccessor_ptr self,
                                       const node_ptr name);

/*!
  \methodof PropDbAccessor
  \brief Returns the index of the property associated to a trace.

  Returns the index of the property associated to a trace.
  -1 if no property is associated to the given trace.
*/
int PropDbAccessor_get_prop_index_from_trace_index(
    const PropDbAccessor_ptr self,
    const int trace_idx);
/* ---------------------------------------------------------------------------*/

/*!
  \methodof PropDbAccessor
  \brief Given a string representing a property name,
                      returns the property index, if it exists

  Parses the given name, builds it's node_ptr
                      interpretation and looks into the PropDbAccessor if the
                      property exists.

  \sa PropDbAccessor_get_prop_name_index
*/
int PropDbAccessor_prop_parse_name(const PropDbAccessor_ptr self,
                                   const char* str);

/*!
  \methodof PropDbAccessor
  \brief Sets the current print format

  When printing, the given format will be used.
  Returns the previously set format.

  \sa PropDbAccessor_get_print_fmt
*/
PropDb_PrintFmt
PropDbAccessor_set_print_fmt(const PropDbAccessor_ptr self,
                             PropDb_PrintFmt new_fmt);


/* Printing********************************************************************/

/*!
  \methodof PropDbAccessor
  \brief Prints the header of the property list

  This method has to be called before
  PropDbAccessor_print_list_footer.

  \se PropDbAccessor_print_list_footer
*/
void PropDbAccessor_print_list_header(const PropDbAccessor_ptr self,
                                      OStream_ptr file);

/*!
  \methodof PropDbAccessor
  \brief Prints the footer of the property list

  This method has to be called after
  PropDbAccessor_print_list_header.

  \se PropDbAccessor_print_list_header
*/
void PropDbAccessor_print_list_footer(const PropDbAccessor_ptr self,
                                      OStream_ptr file);

/*!
  \methodof PropDbAccessor
  \todo
*/
int PropDbAccessor_print_prop_at_index(const PropDbAccessor_ptr self,
                                       OStream_ptr file, const int index);

/*!
  \methodof PropDbAccessor
  \brief Prints all the properties stored in the DB

  Prints on the given file stream all the property
  stored in the DB of properties.
*/
void PropDbAccessor_print_all(const PropDbAccessor_ptr self,
                              OStream_ptr file);

/*!
  \methodof PropDbAccessor
  \brief Prints all the properties stored in the DB

  Prints on the given file stream all the property
  stored in the DB of properties whose type match the requested one.
*/
void PropDbAccessor_print_all_type(const PropDbAccessor_ptr self,
                                   OStream_ptr file, Prop_Type type);

/*!
  \methodof PropDbAccessor
  \brief Prints all the properties stored in the DB

  Prints on the given file stream all the property
  stored in the DB of properties whose status match the requested one.
*/
void PropDbAccessor_print_all_status(const PropDbAccessor_ptr self,
                                     OStream_ptr file, Prop_Status status);

/*!
  \methodof PropDbAccessor
  \brief Prints all the properties stored in the DB

  Prints on the given file stream all the property
  stored in the DB of properties whose type and status match the
  requested ones. Prop_NoStatus and Prop_NoType serve as wildcards.
*/
void PropDbAccessor_print_all_status_type(const PropDbAccessor_ptr self,
                                          OStream_ptr file,
                                          Prop_Status status,
                                          Prop_Type type);


/* Verify**********************************************************************/

/*!
  \methodof PropDbAccessor
  \brief Checks properties

  Check the property type and the property index and calls
  the proper ProbDb_verify_* function.
*/
int
PropDbAccessor_check_property(const PropDbAccessor_ptr self,
                              const Prop_Type pt,
                              const char* formula,
                              const int prop_no);

/*!
  \methodof PropDbAccessor
  \brief Verifies all the properties in the DB

  All the properties stored in the database not
  yet verified will be verified. The properties are verified following
  the order CTL/COMPUTE/LTL/INVAR.
*/
void PropDbAccessor_verify_all(const PropDbAccessor_ptr self);

/*!
  \methodof PropDbAccessor
  \brief Verifies all properties of a given type

  The DB of properties is searched for a property
  of the given type. All the found properties are then verified
  calling the appropriate model checking algorithm. Properties already
  checked will be ignored.
*/
void PropDbAccessor_verify_all_type(const PropDbAccessor_ptr self,
                                    Prop_Type type);

/*!
  \methodof PropDbAccessor
  \brief Verifies all the properties in the DB

  All the properties stored in the database not
  yet verified will be verified. The properties are verified following
  the COI size order (from smaller to bigger)
*/
void PropDbAccessor_ordered_verify_all(const PropDbAccessor_ptr self,
                                       const FlatHierarchy_ptr hierarchy);

/*!
  \methodof PropDbAccessor
  \brief Verifies all properties of a given type, ordered by COI
                      size

  The DB of properties is searched for a property
  of the given type. All the found properties are then verified
  calling the appropriate model checking algorithm. Properties already
  checked will be ignored. Properties found with the given type are checked
  in order, based on the COI size. If type is Prop_NoType, all properties
  are checked
*/
void
PropDbAccessor_ordered_verify_all_type(const PropDbAccessor_ptr self,
                                       const FlatHierarchy_ptr hierarchy,
                                       const Prop_Type type);

/*!
  \methodof PropDbAccessor
  \brief Verifies a given property

  The DB of properties is searched for a property
  whose unique identifier match the identifier provided and then if
  such a property exists it will be verified calling the appropriate
  model checking algorithm. If the property was checked before, then
  the property is not checked again.
*/
void PropDbAccessor_verify_prop_at_index(const PropDbAccessor_ptr self,
                                         const int index);

/*!
  \brief Wrapper for PropDbAccessor_verify_all_type,
  PropDbAccessor_ordered_verify_all_type

  Call the correct PropDbAccessor_..._verify_all_type depending on
  opt_use_coi_size_sorting.
*/
void PropDbAccessor_verify_all_type_wrapper(PropDbAccessor_ptr const self,
                                            const Prop_Type type);

/* Miscellaneous **************************************************************/

/*!
  \methodof PropDbAccessor
  \brief Add a property to the database from a string and a type

  Parses and creates a property of a given type from
  a string. If the formula is correct, it is added to the
  property database and its index is returned.
  Otherwise, -1 is returned.
  Valid types are Prop_Ctl, Prop_Ltl, Prop_Psl, Prop_Invar and Prop_Compute.
  If expr_name is not NULL, it is set as the name of the property.
*/
int PropDbAccessor_prop_parse_and_add(const PropDbAccessor_ptr self,
                                      SymbTable_ptr symb_table,
                                      const char* str,
                                      const Prop_Type type,
                                      const node_ptr expr_name);

/*!
  \methodof PropDbAccessor
  \brief Returns the currently set print format

  When printing, the currenlty set format is used.

  \sa PropDbAccessor_set_print_fmt
*/
PropDb_PrintFmt
PropDbAccessor_get_print_fmt(const PropDbAccessor_ptr self);

/*!
  \methodof PropDbAccessor
  \brief Fills the DB of properties

  Given for each kind of property a list of
  respective formulae, this function is responsible to fill the DB with
  them. Returns 1 if an error occurred, 0 otherwise
*/
int
PropDbAccessor_fill(PropDbAccessor_ptr self, SymbTable_ptr symb_table,
                    node_ptr ctlspec, node_ptr computespec,
                    node_ptr ltlspec, node_ptr pslspec,
                    node_ptr invarspec);

/*!
  \methodof PropDbAccessor
  \brief Inserts a property in the DB of properties

  Insert a property in the DB of properties.
  If not previously set, sets the property index.
  Returns the insert index
*/
int PropDbAccessor_add(PropDbAccessor_ptr self, Prop_ptr prop);

/*!
  \methodof PropDbAccessor
  \brief Inserts a property in the DB of properties

  Given a formula and its type, a property is
  created and stored in the DB of properties. It returns either -1 in
  case of failure, or the index of the inserted property.

*/
int
PropDbAccessor_prop_create_and_add(PropDbAccessor_ptr self,
                                   SymbTable_ptr symb_table,
                                   node_ptr spec, Prop_Type type);

/*!
  \methodof PropDbAccessor
  \brief Shows the currently stored properties

  Shows the currently stored properties.
  If type is Prop_NoType, all properties will be printed.
  If status is Prop_NoStatus, all status will be considered.
*/
int
PropDbAccessor_show_property(const PropDbAccessor_ptr self,
                             const boolean print_props_num,
                             const PropDb_PrintFmt fmt,
                             const Prop_Type type,
                             const Prop_Status status,
                             const int prop_no,
                             FILE* outstream);

/*!
  \methodof PropDbAccessor
  \brief Checks if "prop" is registered within self
*/
boolean
PropDbAccessor_is_prop_registered(PropDbAccessor_ptr self,
                                  Prop_ptr prop);


#endif /* __NUSMV_CORE_PROP_PROP_DB_ACCESSOR_H__ */
