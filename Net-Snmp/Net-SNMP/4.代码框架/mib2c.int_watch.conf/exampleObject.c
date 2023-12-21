/*
 * Note: this file originally auto-generated by mib2c using
 *        $
 */

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include "exampleObject.h"

/*
 * The variables we want to tie the relevant OIDs to.
 * The agent will handle all GET and (if applicable) SET requests
 * to these variables automatically, changing the values as needed.
 */

long    exampleObject1 = 0;  /* XXX: set default value */
long    exampleObject2 = 0;  /* XXX: set default value */
long    exampleObject3 = 0;  /* XXX: set default value */

/*
 * Our initialization routine, called automatically by the agent 
 * (Note that the function name must match init_FILENAME()) 
 */
void
init_exampleObject(void)
{
  netsnmp_handler_registration *reg;

    const oid exampleObject1_oid[] = { 1,3,6,1,4,1,9999,3,1 };
  static netsnmp_watcher_info exampleObject1_winfo;
    const oid exampleObject2_oid[] = { 1,3,6,1,4,1,9999,3,2 };
  static netsnmp_watcher_info exampleObject2_winfo;
    const oid exampleObject3_oid[] = { 1,3,6,1,4,1,9999,3,3 };
  static netsnmp_watcher_info exampleObject3_winfo;
  static netsnmp_watcher_info exampleObject4_winfo;

  /*
   * a debugging statement.  Run the agent with -DexampleObject to see
   * the output of this debugging statement. 
   */
  DEBUGMSGTL(("exampleObject", "Initializing the exampleObject module\n"));


    /*
     * Register scalar watchers for each of the MIB objects.
     * The ASN type and RO/RW status are taken from the MIB definition,
     * but can be adjusted if needed.
     *
     * In most circumstances, the scalar watcher will handle all
     * of the necessary processing.  But the NULL parameter in the
     * netsnmp_create_handler_registration() call can be used to
     * supply a user-provided handler if necessary.
     *
     * This approach can also be used to handle Counter64, string-
     * and OID-based watched scalars (although variable-sized writeable
     * objects will need some more specialised initialisation).
     */
    DEBUGMSGTL(("exampleObject",
                "Initializing exampleObject1 scalar integer.  Default value = %d\n",
                exampleObject1));
    reg = netsnmp_create_handler_registration(
             "exampleObject1", NULL,
              exampleObject1_oid, OID_LENGTH(exampleObject1_oid),
              HANDLER_CAN_RONLY);
    netsnmp_init_watcher_info(&exampleObject1_winfo, &exampleObject1, sizeof(long),
			      ASN_INTEGER, WATCHER_FIXED_SIZE);
if (netsnmp_register_watched_scalar( reg, &exampleObject1_winfo ) < 0 ) {
        snmp_log( LOG_ERR, "Failed to register watched exampleObject1" );
    }

    DEBUGMSGTL(("exampleObject",
                "Initializing exampleObject2 scalar integer.  Default value = %d\n",
                exampleObject2));
    reg = netsnmp_create_handler_registration(
             "exampleObject2", NULL,
              exampleObject2_oid, OID_LENGTH(exampleObject2_oid),
              HANDLER_CAN_RWRITE);
    netsnmp_init_watcher_info(&exampleObject2_winfo, &exampleObject2, sizeof(long),
			      ASN_INTEGER, WATCHER_FIXED_SIZE);
if (netsnmp_register_watched_scalar( reg, &exampleObject2_winfo ) < 0 ) {
        snmp_log( LOG_ERR, "Failed to register watched exampleObject2" );
    }

    DEBUGMSGTL(("exampleObject",
                "Initializing exampleObject3 scalar integer.  Default value = %d\n",
                exampleObject3));
    reg = netsnmp_create_handler_registration(
             "exampleObject3", NULL,
              exampleObject3_oid, OID_LENGTH(exampleObject3_oid),
              HANDLER_CAN_RWRITE);
    netsnmp_init_watcher_info(&exampleObject3_winfo, &exampleObject3, sizeof(long),
			      ASN_INTEGER, WATCHER_FIXED_SIZE);
if (netsnmp_register_watched_scalar( reg, &exampleObject3_winfo ) < 0 ) {
        snmp_log( LOG_ERR, "Failed to register watched exampleObject3" );
    }


  DEBUGMSGTL(("exampleObject",
              "Done initalizing exampleObject module\n"));
}
