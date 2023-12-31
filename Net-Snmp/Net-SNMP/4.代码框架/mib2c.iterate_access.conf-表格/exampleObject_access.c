
/*
 * Note: this file originally auto-generated by mib2c using
 *        $
 */

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include "exampleObject_access.h"
#include "exampleObject_enums.h"


/** returns the first data point within the simpleTable table data.

    Set the my_loop_context variable to the first data point structure
    of your choice (from which you can find the next one).  This could
    be anything from the first node in a linked list, to an integer
    pointer containing the beginning of an array variable.

    Set the my_data_context variable to something to be returned to
    you later that will provide you with the data to return in a given
    row.  This could be the same pointer as what my_loop_context is
    set to, or something different.

    The put_index_data variable contains a list of snmp variable
    bindings, one for each index in your table.  Set the values of
    each appropriately according to the data matching the first row
    and return the put_index_data variable at the end of the function.
*/
netsnmp_variable_list *
simpleTable_get_first_data_point(void **my_loop_context, void **my_data_context,
                          netsnmp_variable_list *put_index_data,
                          netsnmp_iterator_info *mydata)
{

    netsnmp_variable_list *vptr;

    *my_loop_context = /** XXX */;
    *my_data_context = /** XXX */;

    vptr = put_index_data;
    
    snmp_set_var_value(vptr, /** XXX: simpleTbColum1 data */, /** XXX: length of simpleTbColum1 data */);
    vptr = vptr->next_variable;

    return put_index_data;
}

/** functionally the same as simpleTable_get_first_data_point, but
   my_loop_context has already been set to a previous value and should
   be updated to the next in the list.  For example, if it was a
   linked list, you might want to cast it to your local data type and
   then return my_loop_context->next.  The my_data_context pointer
   should be set to something you need later and the indexes in
   put_index_data updated again. */
netsnmp_variable_list *
simpleTable_get_next_data_point(void **my_loop_context, void **my_data_context,
                         netsnmp_variable_list *put_index_data,
                         netsnmp_iterator_info *mydata)
{

    netsnmp_variable_list *vptr;

    *my_loop_context = /** XXX */;
    *my_data_context = /** XXX */;

    vptr = put_index_data;
    
    snmp_set_var_value(vptr, /** XXX: simpleTbColum1 data */, /** XXX: length of simpleTbColum1 data */);
    vptr = vptr->next_variable;

    return put_index_data;
}

/** Create a data_context for non-existent rows that SETs are performed on.
 *  return a void * pointer which will be passed to subsequent get_XXX
 *  and set_XXX functions for data retrieval and modification during
 *  this SET request.
 *
 *  The indexes are encoded (in order) into the index_data pointer,
 *  and the column object which triggered the row creation is available
 *  via the column parameter, if it would be helpful to use that information.
 */
void *
simpleTable_create_data_context(netsnmp_variable_list *index_data, int column) {
    return NULL; /* XXX: you likely want to return a real pointer */
}

/** If the implemented set_* functions don't operate directly on the
   real-live data (which is actually recommended), then this function
   can be used to take a given my_data_context pointer and "commit" it
   to whereever the modified data needs to be put back to.  For
   example, if this was a routing table you could publish the modified
   routes back into the kernel at this point.

   new_or_del will be set to 1 if new, or -1 if it should be deleted
   or 0 if it is just a modification of an existing row.

   If you free the data yourself, make sure to *my_data_context = NULL */
int
simpleTable_commit_row(void **my_data_context, int new_or_del)
{
    /** Add any necessary commit code here */
    /*  */

    /* return no errors.  And there shouldn't be any!!!  Ever!!!  You
    should have checked the values long before this. */
    return SNMP_ERR_NOERROR;
}


/* User-defined data access functions (per column) for data in table simpleTable */
/*
 * NOTE:
 * - these get_ routines MUST return data that will not be freed (ie,
 *   use static variables or persistent data).  It will be copied, if
 *   needed, immediately after the get_ routine has been called.
 * - these SET routines must copy the incoming data and can not take
 *   ownership of the memory passed in by the val pointer.
 */
/** XXX: return a data pointer to the data for the simpleTbColum1 column and set
         ret_len to its proper size in bytes. */
      long *get_simpleTbColum1(void *data_context, size_t *ret_len) {
      return NULL; /** XXX: replace this with a pointer to a real value */
      }
/** XXX: return a data pointer to the data for the simpleTbColum2 column and set
         ret_len to its proper size in bytes. */
      long *get_simpleTbColum2(void *data_context, size_t *ret_len) {
      return NULL; /** XXX: replace this with a pointer to a real value */
      }
/** XXX: Set the value of the simpleTbColum2 column and return
         SNMP_ERR_NOERROR on success
         SNMP_ERR_XXX     for SNMP deterministic error codes
         SNMP_ERR_GENERR  on generic failures (a last result response). */
      int set_simpleTbColum2(void *data_context, long *val, size_t val_len) {
        return SNMP_ERR_NOERROR;  /** XXX: change if an error occurs */
      }
    

/** returns the first data point within the generalTable table data.

    Set the my_loop_context variable to the first data point structure
    of your choice (from which you can find the next one).  This could
    be anything from the first node in a linked list, to an integer
    pointer containing the beginning of an array variable.

    Set the my_data_context variable to something to be returned to
    you later that will provide you with the data to return in a given
    row.  This could be the same pointer as what my_loop_context is
    set to, or something different.

    The put_index_data variable contains a list of snmp variable
    bindings, one for each index in your table.  Set the values of
    each appropriately according to the data matching the first row
    and return the put_index_data variable at the end of the function.
*/
netsnmp_variable_list *
generalTable_get_first_data_point(void **my_loop_context, void **my_data_context,
                          netsnmp_variable_list *put_index_data,
                          netsnmp_iterator_info *mydata)
{

    netsnmp_variable_list *vptr;

    *my_loop_context = /** XXX */;
    *my_data_context = /** XXX */;

    vptr = put_index_data;
    
    snmp_set_var_value(vptr, /** XXX: generalTbColum1 data */, /** XXX: length of generalTbColum1 data */);
    vptr = vptr->next_variable;
    snmp_set_var_value(vptr, /** XXX: generalTbColum2 data */, /** XXX: length of generalTbColum2 data */);
    vptr = vptr->next_variable;

    return put_index_data;
}

/** functionally the same as generalTable_get_first_data_point, but
   my_loop_context has already been set to a previous value and should
   be updated to the next in the list.  For example, if it was a
   linked list, you might want to cast it to your local data type and
   then return my_loop_context->next.  The my_data_context pointer
   should be set to something you need later and the indexes in
   put_index_data updated again. */
netsnmp_variable_list *
generalTable_get_next_data_point(void **my_loop_context, void **my_data_context,
                         netsnmp_variable_list *put_index_data,
                         netsnmp_iterator_info *mydata)
{

    netsnmp_variable_list *vptr;

    *my_loop_context = /** XXX */;
    *my_data_context = /** XXX */;

    vptr = put_index_data;
    
    snmp_set_var_value(vptr, /** XXX: generalTbColum1 data */, /** XXX: length of generalTbColum1 data */);
    vptr = vptr->next_variable;
    snmp_set_var_value(vptr, /** XXX: generalTbColum2 data */, /** XXX: length of generalTbColum2 data */);
    vptr = vptr->next_variable;

    return put_index_data;
}

/** Create a data_context for non-existent rows that SETs are performed on.
 *  return a void * pointer which will be passed to subsequent get_XXX
 *  and set_XXX functions for data retrieval and modification during
 *  this SET request.
 *
 *  The indexes are encoded (in order) into the index_data pointer,
 *  and the column object which triggered the row creation is available
 *  via the column parameter, if it would be helpful to use that information.
 */
void *
generalTable_create_data_context(netsnmp_variable_list *index_data, int column) {
    return NULL; /* XXX: you likely want to return a real pointer */
}

/** If the implemented set_* functions don't operate directly on the
   real-live data (which is actually recommended), then this function
   can be used to take a given my_data_context pointer and "commit" it
   to whereever the modified data needs to be put back to.  For
   example, if this was a routing table you could publish the modified
   routes back into the kernel at this point.

   new_or_del will be set to 1 if new, or -1 if it should be deleted
   or 0 if it is just a modification of an existing row.

   If you free the data yourself, make sure to *my_data_context = NULL */
int
generalTable_commit_row(void **my_data_context, int new_or_del)
{
    /** Add any necessary commit code here */
    /*  */

    /* return no errors.  And there shouldn't be any!!!  Ever!!!  You
    should have checked the values long before this. */
    return SNMP_ERR_NOERROR;
}


/* User-defined data access functions (per column) for data in table generalTable */
/*
 * NOTE:
 * - these get_ routines MUST return data that will not be freed (ie,
 *   use static variables or persistent data).  It will be copied, if
 *   needed, immediately after the get_ routine has been called.
 * - these SET routines must copy the incoming data and can not take
 *   ownership of the memory passed in by the val pointer.
 */
/** XXX: return a data pointer to the data for the generalTbColum1 column and set
         ret_len to its proper size in bytes. */
      u_long *get_generalTbColum1(void *data_context, size_t *ret_len) {
      return NULL; /** XXX: replace this with a pointer to a real value */
      }
/** XXX: return a data pointer to the data for the generalTbColum2 column and set
         ret_len to its proper size in bytes. */
      u_long *get_generalTbColum2(void *data_context, size_t *ret_len) {
      return NULL; /** XXX: replace this with a pointer to a real value */
      }
/** XXX: return a data pointer to the data for the generalTbColum3 column and set
         ret_len to its proper size in bytes. */
      char *get_generalTbColum3(void *data_context, size_t *ret_len) {
      return NULL; /** XXX: replace this with a pointer to a real value */
      }
/** XXX: Set the value of the generalTbColum3 column and return
         SNMP_ERR_NOERROR on success
         SNMP_ERR_XXX     for SNMP deterministic error codes
         SNMP_ERR_GENERR  on generic failures (a last result response). */
      int set_generalTbColum3(void *data_context, char *val, size_t val_len) {
        return SNMP_ERR_NOERROR;  /** XXX: change if an error occurs */
      }
/** XXX: return a data pointer to the data for the generalTbColum4 column and set
         ret_len to its proper size in bytes. */
      long *get_generalTbColum4(void *data_context, size_t *ret_len) {
      return NULL; /** XXX: replace this with a pointer to a real value */
      }
/** XXX: Set the value of the generalTbColum4 column and return
         SNMP_ERR_NOERROR on success
         SNMP_ERR_XXX     for SNMP deterministic error codes
         SNMP_ERR_GENERR  on generic failures (a last result response). */
      int set_generalTbColum4(void *data_context, long *val, size_t val_len) {
        return SNMP_ERR_NOERROR;  /** XXX: change if an error occurs */
      }
    

