#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <string.h>

// 编译命令:gcc -g snmpdemoapp.c -L/usr/local/snmp/lib -lnetsnmp -lrt -lm -o snmpdemoapp

#define MAX_OID_LEN 128

int main(int argc, char **argv)
{
    int status;

    int count = 1;
  
 
    /*session:填充准备会话的信息
     *ss:记录返回的会话信息
     */
    netsnmp_session session, *ss;

    /*pdu 记录了远程主机的所有的信息*/
    netsnmp_pdu *pdu;
    /*response 记录了远程主机返回的PUD信息*/
    netsnmp_pdu *response;

    /*记录OID节点位置信息*/
    oid anOID[MAX_OID_LEN];
    size_t anOID_len;

    /*变量绑定列表(list数据结构)*/
    netsnmp_variable_list *vars;

    /*初始化SNMP 始化互斥量、MIB 解析、传输层、调试信息的初始化、解析配置文件的初始化(netsnmp_ds_register_config)、
     * 各句柄的初始化;定时器的初始化、读取配置文件*/
    init_snmp("snmpdemoapp");

    /*session的初始化:初始化目的地址,snmp版本协议,认证机制等等*/
    snmp_sess_init(&session); /*初始化*/

    session.peername = strdup("localhost");            /*设置目标地址*/
    session.version = SNMP_VERSION_1;                  /*设置snmp协议版本*/
    session.community = "public";                      /*设置共用体*/
    session.community_len = strlen(session.community); /*设置共用体长度*/

    /*开启和绑定传输层(TCP/UDP),建立会话,返回会话句柄*/
    ss = snmp_open(&session); /*打开会话*/
    if (!ss)
    {
        snmp_sess_perror("snmpdemoapp", &session);
        exit(1);
    }
    /*创建指定类型的PDU 选择执行的操作 绑定准备通信的OID*/
    pdu = snmp_pdu_create(SNMP_MSG_GET);
    anOID_len = MAX_OID_LEN; /*设置节点OID的长度,建议不超过128*/

    /*此处read_objid / snmp_parse_oid的作用是检查oID的正确性，并赋予anoID正确的值,也就是最终请求的OID*/
    // read_objid("system.sysDescr.0", anOID, &anOID_len);
    //  if (!snmp_parse_oid(".1.3.6.1.2.1.1.1.0", anOID, &anOID_len))
    /*system.节点:
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
    /*将OID绑定到PDU,同时赋予一个NULL值作为变量的绑定*/
    snmp_add_null_var(pdu, anOID, anOID_len);

    /*同步发送报文*/
    status = snmp_synch_response(ss, pdu, &response);

    /*处理返回的报文*/
    if (status == STAT_SUCCESS && response->errstat == SNMP_ERR_NOERROR)
    {
        for (vars = response->variables; vars; vars = vars->next_variable)
        {
            print_variable(vars->name, vars->name_length, vars);  //打印变量绑定列表
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
        snmp_free_pdu(response);    //释放资源
    }
    snmp_close(ss);
    return 0;
}