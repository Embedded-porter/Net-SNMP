
struct simpleTable_entry *simpleTable_head; // ������ṹ���д洢����ʵ��������

/** ��ʼ��ģ��

 */
void init_exampleObject(void)
{
    // ����ʼ������������������ĳ�ʼ��������
    initialize_table_simpleTable();
    initialize_table_generalTable();
}
/** ע������Ϣ

 */
void initialize_table_simpleTable(void)
{
    const oid simpleTable_oid[] = {1, 3, 6, 1, 4, 1, 9999, 3, 9};
    const size_t simpleTable_oid_len = OID_LENGTH(simpleTable_oid);
    netsnmp_handler_registration *reg;
    netsnmp_iterator_info *iinfo;
    netsnmp_table_registration_info *table_info;
    DEBUGMSGTL(("exampleObject:init", "initializing table simpleTable\n"));
    // ע��OID����Ӧ���

    reg = 
        netsnmp_create_handler_registration("simpleTable",
                                              simpleTable_handler,
                                              simpleTable_oid,
                                              simpleTable_oid_len,
                                              HANDLER_CAN_RWRITE);
    table_info = SNMP_MALLOC_TYPEDEF(netsnmp_table_registration_info);
    // ע����������Ϣ���ÿɱ�κ�����������Ӷ���������ͣ��˴�Ϊһ����������

    netsnmp_table_helper_add_indexes(table_info, ASN_INTEGER, 0);
    // �������һ�к����һ��

    table_info->min_column = COLUMN_SIMPLETBCOLUM1;
    table_info->max_column = COLUMN_SIMPLETBCOLUM2;
    // ע�������

    iinfo = SNMP_MALLOC_TYPEDEF(netsnmp_iterator_info);
    iinfo->get_first_data_point = simpleTable_get_first_data_point;
    iinfo->get_next_data_point = simpleTable_get_next_data_point;
    iinfo->table_reginfo = table_info;
    netsnmp_register_table_iterator(reg, iinfo);
    // ���������ĳ��OIDʵ�ֻ��档�����ṩ�������ʱ���Բ���ʵ��

    // simpleTable_loadΪ���Ӻ�����simpleTable_freeΪ��Ӧ��Դ�ͷź���

        netsnmp_inject_handler_before(reg,
                                      netsnmp_get_cache_handler(SIMPLETABLE_TIMEOUT, simpleTable_load,
                                                                simpleTable_free, simpleTable_oid,
                                                                simpleTable_oid_len),
                                         TABLE_ITERATOR_NAME);
    // ������ʼ��������
}
// ��ȡ��һ�У���ṹ����netsnmp_variable_list *
simpleTable_get_first_data_point(void **my_loop_context,
                                 void **my_data_context,
                                 netsnmp_variable_list *put_index_data,
                                 netsnmp_iterator_info *mydata)
{
    // ֻ��Ҫ��ֵ��ṹ�������simpleTable_head

    *my_loop_context = simpleTable_head;
    return simpleTable_get_next_data_point(my_loop_context,
                                           my_data_context, put_index_data,
                                           mydata);
}
// ����������ȡ��һ������

netsnmp_variable_list *
simpleTable_get_next_data_point(void **my_loop_context,
                                void **my_data_context,
                                netsnmp_variable_list *put_index_data,
                                netsnmp_iterator_info *mydata)
{
    struct simpleTable_entry *entry =
        (struct simpleTable_entry *)*my_loop_context;
    netsnmp_variable_list *idx = put_index_data;
    if (entry)
    {
        // ע�������������ж������

        snmp_set_var_typed_integer(idx, ASN_INTEGER,
                                   entry->simpleTbColum1);
        idx = idx->next_variable;
        *my_data_context = (void *)entry;
        *my_loop_context = (void *)entry->next;
        return put_index_data;
    }
    else
    {
        return NULL;
    }
}
// ��������Ļص����������ƣ������������ͺ��кŽ��в�ѯ

int simpleTable_handler(netsnmp_mib_handler *handler,
                        netsnmp_handler_registration *reginfo,
                        netsnmp_agent_request_info *reqinfo,
                        netsnmp_request_info *requests)
{
    switch (reqinfo->mode)
    {
    case MODE_GET:
        ......
    }
    ......
}