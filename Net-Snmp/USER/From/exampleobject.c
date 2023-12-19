
struct simpleTable_entry *simpleTable_head; // 该链表结构体中存储了真实表格的数据

/** 初始化模块

 */
void init_exampleObject(void)
{
    // 表格初始化，还可以添加其他的初始化的内容
    initialize_table_simpleTable();
    initialize_table_generalTable();
}
/** 注册表格信息

 */
void initialize_table_simpleTable(void)
{
    const oid simpleTable_oid[] = {1, 3, 6, 1, 4, 1, 9999, 3, 9};
    const size_t simpleTable_oid_len = OID_LENGTH(simpleTable_oid);
    netsnmp_handler_registration *reg;
    netsnmp_iterator_info *iinfo;
    netsnmp_table_registration_info *table_info;
    DEBUGMSGTL(("exampleObject:init", "initializing table simpleTable\n"));
    // 注册OID的响应句柄

    reg = 
        netsnmp_create_handler_registration("simpleTable",
                                              simpleTable_handler,
                                              simpleTable_oid,
                                              simpleTable_oid_len,
                                              HANDLER_CAN_RWRITE);
    table_info = SNMP_MALLOC_TYPEDEF(netsnmp_table_registration_info);
    // 注册表格索引信息。该可变参函数，可以添加多个索引类型，此处为一个整型索引

    netsnmp_table_helper_add_indexes(table_info, ASN_INTEGER, 0);
    // 定义表格第一列和最后一列

    table_info->min_column = COLUMN_SIMPLETBCOLUM1;
    table_info->max_column = COLUMN_SIMPLETBCOLUM2;
    // 注册迭代器

    iinfo = SNMP_MALLOC_TYPEDEF(netsnmp_iterator_info);
    iinfo->get_first_data_point = simpleTable_get_first_data_point;
    iinfo->get_next_data_point = simpleTable_get_next_data_point;
    iinfo->table_reginfo = table_info;
    netsnmp_register_table_iterator(reg, iinfo);
    // 下面是针对某个OID实现缓存。当不提供缓存机制时可以不用实现

    // simpleTable_load为钩子函数，simpleTable_free为相应资源释放函数

        netsnmp_inject_handler_before(reg,
                                      netsnmp_get_cache_handler(SIMPLETABLE_TIMEOUT, simpleTable_load,
                                                                simpleTable_free, simpleTable_oid,
                                                                simpleTable_oid_len),
                                         TABLE_ITERATOR_NAME);
    // 其他初始化的内容
}
// 获取第一行：表结构链表netsnmp_variable_list *
simpleTable_get_first_data_point(void **my_loop_context,
                                 void **my_data_context,
                                 netsnmp_variable_list *put_index_data,
                                 netsnmp_iterator_info *mydata)
{
    // 只需要赋值表结构链表变量simpleTable_head

    *my_loop_context = simpleTable_head;
    return simpleTable_get_next_data_point(my_loop_context,
                                           my_data_context, put_index_data,
                                           mydata);
}
// 迭代器，获取下一行数据

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
        // 注册索引，可以有多个索引

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
// 处理请求的回调函数都类似：根据请求类型和列号进行查询

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