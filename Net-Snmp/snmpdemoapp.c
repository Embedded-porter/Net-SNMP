#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <string.h>

// ��������:gcc -g snmpdemoapp.c -L/usr/local/snmp/lib -lnetsnmp -lrt -lm -o snmpdemoapp

#define MAX_OID_LEN 128

int main(int argc, char **argv)
{
    int status;

    int count = 1;
  
 
    /*session:���׼���Ự����Ϣ
     *ss:��¼���صĻỰ��Ϣ
     */
    netsnmp_session session, *ss;

    /*pdu ��¼��Զ�����������е���Ϣ*/
    netsnmp_pdu *pdu;
    /*response ��¼��Զ���������ص�PUD��Ϣ*/
    netsnmp_pdu *response;

    /*��¼OID�ڵ�λ����Ϣ*/
    oid anOID[MAX_OID_LEN];
    size_t anOID_len;

    /*�������б�(list���ݽṹ)*/
    netsnmp_variable_list *vars;

    /*��ʼ��SNMP ʼ����������MIB ����������㡢������Ϣ�ĳ�ʼ�������������ļ��ĳ�ʼ��(netsnmp_ds_register_config)��
     * ������ĳ�ʼ��;��ʱ���ĳ�ʼ������ȡ�����ļ�*/
    init_snmp("snmpdemoapp");

    /*session�ĳ�ʼ��:��ʼ��Ŀ�ĵ�ַ,snmp�汾Э��,��֤���Ƶȵ�*/
    snmp_sess_init(&session); /*��ʼ��*/

    session.peername = strdup("localhost");            /*����Ŀ���ַ*/
    session.version = SNMP_VERSION_1;                  /*����snmpЭ��汾*/
    session.community = "public";                      /*���ù�����*/
    session.community_len = strlen(session.community); /*���ù����峤��*/

    /*�����Ͱ󶨴����(TCP/UDP),�����Ự,���ػỰ���*/
    ss = snmp_open(&session); /*�򿪻Ự*/
    if (!ss)
    {
        snmp_sess_perror("snmpdemoapp", &session);
        exit(1);
    }
    /*����ָ�����͵�PDU ѡ��ִ�еĲ��� ��׼��ͨ�ŵ�OID*/
    pdu = snmp_pdu_create(SNMP_MSG_GET);
    anOID_len = MAX_OID_LEN; /*���ýڵ�OID�ĳ���,���鲻����128*/

    /*�˴�read_objid / snmp_parse_oid�������Ǽ��oID����ȷ�ԣ�������anoID��ȷ��ֵ,Ҳ�������������OID*/
    // read_objid("system.sysDescr.0", anOID, &anOID_len);
    //  if (!snmp_parse_oid(".1.3.6.1.2.1.1.1.0", anOID, &anOID_len))
    /*system.�ڵ�:
                sysDescr.0   
                sysObjectID.0
                sysContact.0
                sysName.0
                sysLocation.0
                sysServices.0
                sysORLastChange.0
                sysORTable.0 */

    if (!snmp_parse_oid("system.sysDescr.0", anOID, &anOID_len))
    {
        snmp_sess_perror(".1.3.6.1.2.1.1.1.1", &session); 
        exit(1);
    }
    printf("anOID = %ld\n", anOID[1]);
    /*��OID�󶨵�PDU,ͬʱ����һ��NULLֵ��Ϊ�����İ�*/
    snmp_add_null_var(pdu, anOID, anOID_len);

    /*ͬ�����ͱ���*/
    status = snmp_synch_response(ss, pdu, &response);

    /*�����صı���*/
    if (status == STAT_SUCCESS && response->errstat == SNMP_ERR_NOERROR)
    {
        for (vars = response->variables; vars; vars = vars->next_variable)
        {
            print_variable(vars->name, vars->name_length, vars);  //��ӡ�������б�
        }
        count = 1;
        
        for (vars = response->variables; vars; vars = vars->next_variable)
        {
            if (vars->type == ASN_OCTET_STR)
            {
                char *sp = (char *)malloc(1 + vars->val_len);
                memcpy(sp, vars->val.string, vars->val_len);
                sp[vars->val_len] = '\0';
                printf("value #%d is a string:%s\n", count++, sp);
                free(sp);
            }
            else
            {
                printf("value #%d is NOT a string\n", count++);
            }
        }
    }
    else
    {
        if (status == STAT_SUCCESS)
        {
            fprintf(stderr, "Error in packet\nReason: %s\n", snmp_errstring(response->errstat));
        }
        else if (status == STAT_TIMEOUT)
        {
            fprintf(stderr, "Timeout: No response from %s.\n", session.peername);
        }
        else
        {
            snmp_sess_perror("snmpdemoapp", ss);
        }
    }
    if (response)
    {
        snmp_free_pdu(response);    //�ͷ���Դ
    }
    snmp_close(ss);
    return 0;
}