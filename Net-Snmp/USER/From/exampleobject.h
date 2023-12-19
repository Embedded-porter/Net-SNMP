
#ifndef EXAMPLEOBJECT_H
#define EXAMPLEOBJECT_H
// 函数声明

void init_exampleObject(void);
void initialize_table_simpleTable(void);
Netsnmp_Node_Handler simpleTable_handler;
Netsnmp_First_Data_Point simpleTable_get_first_data_point;
Netsnmp_Next_Data_Point simpleTable_get_next_data_point;
void initialize_table_generalTable(void);
Netsnmp_Node_Handler generalTable_handler;
Netsnmp_First_Data_Point generalTable_get_first_data_point;
Netsnmp_Next_Data_Point generalTable_get_next_data_point;
// simpleTable节点下的每列定义

#define COLUMN_SIMPLETBCOLUM1 1
#define COLUMN_SIMPLETBCOLUM2 2
// generalTable节点下的每列定义

#define COLUMN_GENERALTBCOLUM1 1
#define COLUMN_GENERALTBCOLUM2 2
#define COLUMN_GENERALTBCOLUM3 3
#define COLUMN_GENERALTBCOLUM4 4
#endif /* EXAMPLEOBJECT_H */