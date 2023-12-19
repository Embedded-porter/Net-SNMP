/*
 * Note: this file originally auto-generated by mib2c using
 *        $
 */

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include "a.h"

/** Initializes the a module */
void
init_a(void)
{
    const oid test_oid[] = { 1,3,6,1,4,1,1,1,1 };

  DEBUGMSGTL(("a", "Initializing\n"));

    netsnmp_register_scalar(
        netsnmp_create_handler_registration("test", handle_test,
                               test_oid, OID_LENGTH(test_oid),
                               HANDLER_CAN_RWRITE
        ));
}

int
handle_test(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    int ret;
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */
    int value = 10;
    int setValue;
    switch(reqinfo->mode) {

        case MODE_GET: //�����Ƕ�ȡ�ڵ�����
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &value /*���Ӷ�ȡ������*/ /* XXX: a pointer to the scalar's data */,
                                     4 /*���ݳ���*/ /* XXX: the length of the data in bytes */);
            break;

        /*
         * SET REQUEST
         *
         * multiple states in the transaction.  See:
         * http://www.net-snmp.org/tutorial-5/toolkit/mib_module/set-actions.jpg
         */
        case MODE_SET_RESERVE1:
                /* or you could use netsnmp_check_vb_type_and_size instead */
            ret = netsnmp_check_vb_type(requests->requestvb, ASN_INTEGER);
            if ( ret != SNMP_ERR_NOERROR ) {
                netsnmp_set_request_error(reqinfo, requests, ret );
            }
            break;

        case MODE_SET_RESERVE2:
            /* XXX malloc "undo" storage buffer */
            if (0 /*���������������*/) {
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_RESOURCEUNAVAILABLE);
            }
            break;

        case MODE_SET_FREE:
            /* XXX: free resources allocated in RESERVE1 and/or
               RESERVE2.  Something failed somewhere, and the states
               below won't be called. */
            break;

        case MODE_SET_ACTION: //����������test�ڵ㣬��������ֻ�Ǵ�ӡһ��Ҫ���õ�ֵ��ʵ�ʸ���ҵ��������д���
            //��ȡ���õ�ֵ,�������͵����ݿ��Ե�net-snmp������requests�ṹ��ĳ�Ա
            setValue = *requests->requestvb->val.integer;
            printf("setvalue:%d\n", setValue);
            if (0/*�������������*/) {
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_BADVALUE/*�����ĺ�,snmp�����ɲ�*/);
            }
            break;

        case MODE_SET_COMMIT:
            /* XXX: delete temporary storage */
            if (0 /*��������*/) {
                /* try _really_really_ hard to never get to this point */
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
            }
            break;

        case MODE_SET_UNDO:
            /* XXX: UNDO and return to previous value for the object */
            if (0 /*��������*/) {
                /* try _really_really_ hard to never get to this point */
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_UNDOFAILED);
            }
            break;

        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_test\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
